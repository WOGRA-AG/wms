/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwqQmlEditor.h
 ** Started Implementation: 2013/09/02
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QQuickView>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <qtextcodec.h>
#include <QDesktopServices>

// WMS Includes
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "CdmClass.h"

// WMS QML INcludes
#include "CwqQmlObjectViewer.h"

// Own Includes
#include "CwmsQmlPreviewDlg.h"
#include "jshighlighter.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsQmlEditor.h"

/** +-=---------------------------------------------------------Mo 23. Sep 21:25:22 2013----------*
 * @method  CwmsQmlEditor::CwmsQmlEditor                     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pParent                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 21:25:22 2013----------*/
CwmsQmlEditor::CwmsQmlEditor(QWidget* p_pParent)
   : QWidget(p_pParent)
{
   setupUi(this);
   connect(&m_FileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(FileChangedSlot(QString)));
}

/** +-=---------------------------------------------------------Mo 23. Sep 21:25:33 2013----------*
 * @method  CwmsQmlEditor::~CwmsQmlEditor                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwqQmlEditor                                                  *
 *----------------last changed: --------------------------------Mo 23. Sep 21:25:33 2013----------*/
CwmsQmlEditor::~CwmsQmlEditor()
{
    if (IsModified())
    {
        if (!CdmMessageManager::Ask(tr("Änderungen speichern?"),
                                    tr("Sie haben Änderungen an der Benutezroberfläche durchgeführt. Wollen Sie diese Speichern?")))
        {
            Save();
        }
    }
}

/** +-=---------------------------------------------------------Mo 23. Sep 21:25:46 2013----------*
 * @method  CwmsQmlEditor::FillDialog                        // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsFormUserDefined p_Form                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 21:25:46 2013----------*/
void CwmsQmlEditor::FillDialog(CwmsFormUserDefined p_Form)
{
   m_Form = p_Form;

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
       QString qstrClassUri = m_Form.GetClassUri();
      CdmClass* pClass = static_cast<CdmClass*>(pManager->GetUriObject(qstrClassUri));

      if (pClass)
      {
         m_pqleClass->setText(pClass->GetKeyname());
      }
   }

   switch(m_Form.GetContext())
   {
      case eWmsFormContextObject:
         m_pqrbObject->setChecked(true);
         break;
      case eWmsFormContextContainer:
         m_pqrbObjectContainer->setChecked(true);
         break;
      case eWmsFormContextWms:
         m_pqrbWmsContext->setChecked(true);
         break;
   }

   switch (m_Form.GetFormType())
   {
      case eWmsFormTypeDialog:
         m_pqrbDialog->setChecked(true);
         break;
      case eWmsFormTypeWidget:
         m_pqrbWidget->setChecked(true);
         break;
      case eWmsFormTypeMainWindow:
         m_pqrbMainWindow->setChecked(true);
         break;
   }

   m_pqleName->setText(m_Form.GetName());
   m_pqteCode->setTextWrapEnabled(false);
   m_pqteCode->setCodeFoldingEnabled(true);
   m_pqteCode->setLineNumbersVisible(true);
   m_qstrOriginalCode = m_Form.GetUICode();
   m_pqteCode->setPlainText(m_qstrOriginalCode);
   m_pqteCode->document()->setModified(false);
   m_pqchbDesktop->setChecked(m_Form.GetDesktopForm());
   m_pqchbMobile->setChecked(m_Form.GetMobileForm());
   m_pqchbTablet->setChecked(m_Form.GetTabletForm());
   m_pqchbWeb->setChecked(m_Form.GetWebForm());
   m_pqchbDefault->setChecked(m_Form.GetDefault());
}

/** +-=---------------------------------------------------------Mo 23. Sep 21:26:31 2013----------*
 * @method  CwmsQmlEditor::Validate                          // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 21:26:31 2013----------*/
bool CwmsQmlEditor::Validate()
{
   bool success = true;

   if (m_pqleName->text().isEmpty())
   {
      CdmMessageManager::critical(tr("Validierung fehlgeschlagen"),tr("Name ist Pflichtfeld."));
      success = false;
   }

   if (m_pqleClass->text().isEmpty() && !m_pqrbWmsContext->isChecked())
   {
      CdmMessageManager::critical(tr("Validierung fehlgeschlagen"),tr("Wenn Wms Kontext nicht ausgewählt ist, muss eine Klasse selektiert werden."));
      success = false;
   }

   if (!m_pqchbDesktop->isChecked() && !m_pqchbMobile->isChecked() && !m_pqchbTablet->isChecked())
   {
      CdmMessageManager::critical(tr("Validierung fehlgeschlagen"), tr("Es muss eine Verwendungsart für den Dialog gewählt werden."));
      success = false;
   }

   if (m_pqteCode->toPlainText().isEmpty())
   {
      CdmMessageManager::critical(tr("Validierung fehlgeschlagen"), tr("Der Dialogcode muss gefüllt sein."));
      success = false;
   }
   
   return success;
}

void CwmsQmlEditor::SaveClickedSlot()
{
    if (Validate())
    {
        Save();
    }
}

/** +-=---------------------------------------------------------Mo 23. Sep 21:26:50 2013----------*
 * @method  CwmsQmlEditor::Save                              // public                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 21:26:50 2013----------*/
bool CwmsQmlEditor::Save()
{
    bool success = false;
    if (Validate())
    {
        m_Form.SetName(m_pqleName->text());

        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            CdmClass* pClass = pManager->GetClassManager()->FindClassByKeyname(m_pqleClass->text());

            if (pClass)
            {
                m_Form.SetClassUri(pClass->GetUriInternal());
            }
        }

        m_Form.SetDesktopForm(m_pqchbDesktop->isChecked());
        m_Form.SetMobileForm(m_pqchbMobile->isChecked());
        m_Form.SetTabletForm(m_pqchbTablet->isChecked());

        m_Form.SetDefault(m_pqchbDefault->isChecked());
        m_Form.SetWebForm(m_pqchbWeb->isChecked());


        m_Form.SetUICode(m_pqteCode->toPlainText());

        if (m_pqrbObject->isChecked())
        {
            m_Form.SetContext(eWmsFormContextObject);
        }
        else if (m_pqrbObjectContainer->isChecked())
        {
            m_Form.SetContext(eWmsFormContextContainer);
        }
        else if (m_pqrbWmsContext->isChecked())
        {
            m_Form.SetContext(eWmsFormContextWms);
        }

        if (m_pqrbDialog->isChecked())
        {
            m_Form.SetFormType(eWmsFormTypeDialog);
        }
        else if (m_pqrbWidget->isChecked())
        {
            m_Form.SetFormType(eWmsFormTypeWidget);
        }
        else if (m_pqrbMainWindow->isChecked())
        {
            m_Form.SetFormType(eWmsFormTypeMainWindow);
        }

        if (m_Form.CommitObject() > 0)
        {
            success = true;
        }
        else
        {
            if (!m_Form.GetObject()->IsModified())
            {
                success = true;
            }
            else
            {
                ERR("Could not save Form!");
            }
        }

        if (success)
        {
            m_pqteCode->document()->setModified(false);

            if (m_rpItem)
            {
                m_rpItem->setText(0,m_Form.GetName());
                m_rpItem->setData(0, Qt::UserRole, m_Form.GetObjectId());
            }
        }
    }
    return success;
}

void CwmsQmlEditor::Revert()
{
    if (IsModified())
    {
        FillDialog(m_Form);
    }
}

void CwmsQmlEditor::SetItem(QTreeWidgetItem* p_pItem)
{
    m_rpItem = p_pItem;
}

bool CwmsQmlEditor::IsModified()
{
    bool bRet = false;

    bRet = (m_pqteCode->document()->isModified());

    if (!bRet)
    {
        bRet = (m_Form.GetName() != m_pqleName->text());
    }

    if (!bRet)
    {
        bRet = (m_Form.GetDesktopForm() != m_pqchbDesktop->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_Form.GetDesktopForm() != m_pqchbDesktop->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_Form.GetMobileForm() != m_pqchbMobile->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_pqrbObject->isChecked() && m_Form.GetContext() != eWmsFormContextObject);
    }

    if (!bRet)
    {
        bRet = (m_pqrbObjectContainer->isChecked() && m_Form.GetContext() != eWmsFormContextContainer);
    }

    if (!bRet)
    {
        bRet = (m_pqrbWmsContext->isChecked() && m_Form.GetContext() != eWmsFormContextWms);
    }

    if (!bRet)
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
           CdmClass* pClass = pManager->GetClassManager()->FindClassByKeyname(m_pqleClass->text());

           if (pClass)
           {
              bRet = (m_Form.GetClassUri() != pClass->GetUriInternal());
           }
           else
           {
               bRet = (!m_Form.GetClassUri().isEmpty());
           }
        }
    }

    return bRet;
}

void CwmsQmlEditor::Debug()
{
    CdmMessageManager::critical(tr("Nicht unterstützt"), tr("Debugging ist nicht für Benutzeroberflächen unterstützt"));
}

void CwmsQmlEditor::Execute()
{
    PreviewClickedSlot();
}

/** +-=---------------------------------------------------------Mo 23. Sep 21:27:28 2013----------*
 * @method  CwmsQmlEditor::SelectClassClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 21:27:28 2013----------*/
void CwmsQmlEditor::SelectClassClickedSlot()
{
   CdmClass* pClass = CwmsClassSelectionIf::GetClass(this);

   if (pClass)
   {
      m_pqleClass->setText(pClass->GetKeyname());
   }
}

void CwmsQmlEditor::FileChangedSlot(QString p_qstrFile)
{
   if (CdmMessageManager::Ask(tr("Datei wurde lokal geändert"), 
      tr("Der Code wurde im lokalen Dateisystem geändert. Soll er übernommen werden?")))
   {
      QFile qFile(p_qstrFile);

      if (qFile.open(QIODevice::ReadOnly))
      {
         QString qstrCode = qFile.readAll();
         m_pqteCode->setPlainText(qstrCode);
      }

      qFile.close();
   }
}

void CwmsQmlEditor::OpenInExternalEditorSlot()
{
    QString qstrName = m_pqleName->text();
    QString qstrCode = m_pqteCode->toPlainText();

    // ToDo define Working Directory on local disk
    QString qstrTempPath = QDir::tempPath();
    QString qstrFilename = qstrTempPath + "/" + qstrName + ".qml";

    QFile qFile(qstrFilename);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream qStream(&qFile);
		qStream.setCodec(QTextCodec::codecForName("UTF-8"));
        qStream << qstrCode;
    }

    qFile.close();
    m_FileWatcher.addPath(qstrFilename);
    QDesktopServices::openUrl(QUrl(qstrFilename));
}

/** +-=---------------------------------------------------------Mo 23. Sep 22:13:49 2013----------*
 * @method  CwmsQmlEditor::PreviewClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 22:13:49 2013----------*/
void CwmsQmlEditor::PreviewClickedSlot()
{
   CwqQmlObjectViewer* pViewer = new CwqQmlObjectViewer(this);
   QQuickWindow* pView = pViewer->CreateView(m_pqleName->text(), m_pqteCode->toPlainText());

   if (pView)
   {
        CwmsQmlPreviewDlg cPreviewDlg(this);
        cPreviewDlg.AddWindow(pView);
        cPreviewDlg.exec();
   } 
   else
   {
       ERR("Could not create View");
   }
}

