// System and QT Includes
#include <QFileDialog>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmClass.h"
#include "CdmRights.h"
#include "CdmClassMethod.h"
#include "CdmMessageManager.h"

// WMS GUI Includes
#include "CwmsObjectSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"

// own Includes
#include "CwmsPlatformServices.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsUniversalRightsManager.h"
#include "CwmsClassDataFiller.h"
#include "CwmsFunctionEditor.h"
#include "CwmsJson.h"
#include "CsaFactory.h"

CwmsFunctionEditor::CwmsFunctionEditor(QWidget* p_pqwParent)
: QWidget(p_pqwParent),
  m_rpItem(nullptr),
  m_bModified(false)
{
   setupUi(this);
}

CwmsFunctionEditor::~CwmsFunctionEditor()
{

}

void CwmsFunctionEditor::FillDialog(CdmClassMethod* p_pMethod)
{
    FillDialog(p_pMethod, p_pMethod->GetClass(), false);
}

void CwmsFunctionEditor::FillDialog(CdmClassMethod* p_pMethod, CdmClass* p_pCdmClass, bool p_bNew)
{
   if (CHKPTR(p_pMethod) && CHKPTR(p_pCdmClass))
   {
      m_rpCdmClass = p_pCdmClass;
      m_rpCdmFunction = p_pMethod;

      if (!p_bNew)
      {
         m_pqleName->setText(m_rpCdmFunction->GetMethodName());
         m_pqleCaption->setText(m_rpCdmFunction->GetCaption());
         QPixmap qPixmap = m_rpCdmFunction->GetIcon();
         
         if (!qPixmap.isNull())
         {
            m_qbaIcon = m_rpCdmFunction->GetIconAsByteArray();
            QIcon qIcon(qPixmap);
            m_pqpbSelectIcon->setIcon(qIcon);
         }
         
         switch (m_rpCdmFunction->GetAccess())
         {
         case eDmMemberAccessPublic:
            m_pqrbPublic->setChecked(true);
            break;
         case eDmMemberAccessProtected:
            m_pqrbProtected->setChecked(true);
            break;
         case eDmMemberAccessPrivate:
            m_pqrbPrivate->setChecked(true);
            break;
         }

         if (!m_rpCdmFunction->IsStatic())
         {
            m_pqrbObject->setChecked(true);
         }
         else
         {
            m_pqrbStatic->setChecked(true);
         }
      }
   
      AddTypesToTypeBox();
      AddClassesToComboBox(); 
      FillParameters();
      int iIndex = m_pqcbReturnType->findData(m_rpCdmFunction->GetReturnType());
      m_pqcbReturnType->setCurrentIndex(iIndex);
      m_pjsEditor->setTextWrapEnabled(false);
      m_pjsEditor->setPlainText(m_rpCdmFunction->GetSourceCode());
      m_pjsEditor->SetClass(m_rpCdmClass);
      m_pjsEditor->setCodeFoldingEnabled(true);
      m_pjsEditor->document()->setModified(false);

      if (!p_bNew)
      {
          m_bModified = false;
      }
   }
}

void CwmsFunctionEditor::FillParameters()
{
   m_pqtwParameters->clear();
   QList<CdmClassMethodParameter> qmParams = m_rpCdmFunction->GetParameters();

   for (int iCounter = 0; iCounter < qmParams.count(); ++iCounter)
   {
      CdmClassMethodParameter cParam = qmParams[iCounter];
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwParameters);
      pItem->setText(0, QString::number(cParam.m_iPos));
      pItem->setText(1, CdmMember::GetValueTypeAsString(cParam.m_eType));
      pItem->setText(2, cParam.GetName());
      pItem->setData(0, Qt::UserRole, cParam.m_eType);
      pItem->setData(1, Qt::UserRole, cParam.m_lReference);
   }
}

void CwmsFunctionEditor::AddTypesToTypeBox()
{
    AddTypesToTypeBox(m_pqcbType);
    m_pqcbReturnType->addItem(tr("Keiner"), eDmValueNone);
    AddTypesToTypeBox(m_pqcbReturnType);
    m_pqcbReturnType->addItem(tr("Binärdokument"), eDmValueBinaryDocument);
}

void CwmsFunctionEditor::AddTypesToTypeBox(QComboBox* p_pComboBox)
{
    p_pComboBox->addItem(tr("Wahrheitsausdruck"), eDmValueBool);
    p_pComboBox->addItem(tr("Ganze Zahl"), eDmValueInt);
    p_pComboBox->addItem(tr("Fließkommazahl"), eDmValueDouble);
    p_pComboBox->addItem(tr("Textdokument"), eDmValueCharacterDocument);
    p_pComboBox->addItem(tr("Datum"), eDmValueDate);
    p_pComboBox->addItem(tr("Uhrzeit"), eDmValueTime);
    p_pComboBox->addItem(tr("Zeitstempel"), eDmValueDateTime);
    p_pComboBox->addItem(tr("Objektcontainer"), eDmValueContainerRef);
    p_pComboBox->addItem(tr("Objekt"), eDmValueObjectRef);
    p_pComboBox->addItem(tr("Zeichenkette"), eDmValueString);
    p_pComboBox->addItem(tr("Benutzer"), eDmValueUser);
    p_pComboBox->addItem(tr("Benutzergruppe"), eDmValueUserGroup);
    p_pComboBox->addItem(tr("Array"), eDmValueArray);
    p_pComboBox->addItem(tr("QObject"), eDmValueQObject);
}

void CwmsFunctionEditor::AddClassesToComboBox()
{
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmClassManager* pClassManager = pManager->GetClassManager();

      if (CHKPTR(pClassManager))
      {
         QList<CdmClass*> qlClasses;
         pClassManager->GetClassList(qlClasses);

         QList<CdmClass*>::iterator qlIt = qlClasses.begin();
         QList<CdmClass*>::iterator qlItEnd = qlClasses.end();

         for (; qlIt != qlItEnd; ++qlIt)
         {
            CdmClass* pClass = *qlIt;

            if (CHKPTR(pClass))
            {
               m_pqcbClass->addItem(pClass->GetCaption() + "(" + pClass->GetKeyname() + ")", 
                                    pClass->GetId());
            }
         }

      }
   }
}

void CwmsFunctionEditor::TypeIndexChangedSlot()
{
   m_pqlClass->hide();
   m_pqcbClass->hide();

   EdmValueType eValue = (EdmValueType)m_pqcbType->itemData(m_pqcbType->currentIndex()).toInt();

   if (eValue == eDmValueContainerRef ||
       eValue == eDmValueObjectRef)
   {
      m_pqlClass->show();
      m_pqcbClass->show();         
   }
}

void CwmsFunctionEditor::AddParameterClickedSlot()
{
   QString qstrName = m_pqleParameterName->text();
   EdmValueType eValue = (EdmValueType)m_pqcbType->itemData(m_pqcbType->currentIndex()).toInt();
   int iClassId = 0;

   if (eValue == eDmValueContainerRef || 
       eValue == eDmValueObjectRef)
   {
      iClassId = m_pqcbClass->itemData(m_pqcbClass->currentIndex()).toInt();
   }

   m_rpCdmFunction->AddParameter(qstrName, eValue, iClassId);
   m_pqcbType->setCurrentIndex(0);
   m_pqcbClass->setCurrentIndex(0);
   m_pqleParameterName->clear();
   FillParameters();
}

void CwmsFunctionEditor::DeleteParameterClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwParameters);

   if (pItem)
   {
      QString qstrName = pItem->text(2);
      m_rpCdmFunction->DeleteParameter(qstrName);
      FillParameters();
   }
}

void CwmsFunctionEditor::MoveParameterDownClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwParameters);

   if (pItem)
   {
      QString qstrName = pItem->text(2);
      m_rpCdmFunction->MoveParameterDown(qstrName);
      FillParameters();
      SetParameterSelected(qstrName);
   }
}

void CwmsFunctionEditor::SetParameterSelected(QString p_qstrName)
{
    CwmsTreeWidgetHelper::SelectItem(m_pqtwParameters, 2, p_qstrName);
}

void CwmsFunctionEditor::MoveParameterUpClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwParameters);

   if (pItem)
   {
      QString qstrName = pItem->text(2);
      m_rpCdmFunction->MoveParameterUp(qstrName);
      FillParameters();
      SetParameterSelected(qstrName);
   }
}


void CwmsFunctionEditor::EnlargeCodeViewClickedSlot()
{
   if (m_pqgbComment->isVisible())
   {
      m_pqgbComment->hide();
      m_pqgbAccess->hide();
      m_pqgbFunctionType->hide();
   }
   else
   {
      m_pqgbComment->show();
      m_pqgbAccess->show();
      m_pqgbFunctionType->show();
   }
}

void CwmsFunctionEditor::RightsClickedSlot()
{
   if (m_rpCdmFunction)
   {
      CdmRights* pCdmRights = &m_rpCdmFunction->GetRights();
      CwmsUniversalRightsManagerIf* pCwmsRighstManager =
         new CwmsUniversalRightsManagerIf(pCdmRights, this);
      pCwmsRighstManager->exec();
      DELPTR(pCwmsRighstManager);
      m_rpCdmClass->Commit();
   }
}

void CwmsFunctionEditor::SelectIconClickedSlot()
{
   QString qstrIconName = QFileDialog::getOpenFileName(this, tr("Bitte wählen Sie ein Icon aus dem Dateisystem aus"),
      "", "*.png *.jpg *.gif *.ico");

   if (!qstrIconName.isEmpty())
   {
      QFile qFile(qstrIconName);

      if (qFile.open(QIODevice::ReadOnly))
      {
         m_qbaIcon = qFile.readAll();
         QPixmap qPixmap;
         qPixmap.loadFromData(m_qbaIcon);

         if (!qPixmap.isNull())
         {
            QIcon qIcon(qPixmap);
            m_pqpbSelectIcon->setIcon(qIcon);
            m_bModified = true;
         }  
      }
   }
}

void CwmsFunctionEditor::SaveClickedSlot()
{
    Save();
}

bool CwmsFunctionEditor::Save()
{
    bool bSuccess = SaveData();

    if (bSuccess)
    {
        if (m_rpItem) // refesh treewidgetitem
        {
          m_rpItem->setText(0, m_rpCdmFunction->GetMethodName());
          m_rpItem->setData(0, Qt::UserRole, m_rpCdmFunction->GetUriInternal());
        }

        m_bModified = false;
    }

    return bSuccess;
}

void CwmsFunctionEditor::Revert()
{
    FillDialog(m_rpCdmFunction, m_rpCdmClass, false);
}

void CwmsFunctionEditor::SetItem(QTreeWidgetItem * p_pItem)
{
    m_rpItem = p_pItem;
}

bool CwmsFunctionEditor::IsModified()
{
    bool bRet = m_bModified;

    if (!bRet)
    {
        bRet = m_pjsEditor->document()->isModified();
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetMethodName() != m_pqleName->text());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetMethodName() != m_pqleName->text());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetCaption() != m_pqleCaption->text());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetComment() != m_pqteComment->toPlainText());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetAccess() != eDmMemberAccessPrivate && m_pqrbPrivate->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetAccess() != eDmMemberAccessProtected && m_pqrbProtected->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetAccess() != eDmMemberAccessPublic && m_pqrbPublic->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->IsStatic() != m_pqrbStatic->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetReturnType() != m_pqcbReturnType->currentIndex());
    }


    return bRet;
}

void CwmsFunctionEditor::DebugClickedSlot()
{
    Debug();
}

void CwmsFunctionEditor::Debug()
{
    ExecuteFunction(true);
}

void CwmsFunctionEditor::ExecuteClickedSlot()
{
    Execute();
}

void CwmsFunctionEditor::Execute()
{
    ExecuteFunction(false);
}

void CwmsFunctionEditor::closeEvent(QCloseEvent *event)
{
    if (IsModified())
    {
        if (CdmMessageManager::Ask(tr("Änderungen vorhanden"), tr("Sie haben Änderungen an der Funktion vorgenommen.\n Wollen Sie die Speichern?")))
        {
            Save();
        }
    }

    event->accept();
}

void CwmsFunctionEditor::ExecuteFunction(bool p_bDebugger)
{
    QVariant qvResult;

    if (Save())
    {
        CwmsPlatformServices::ExecuteFunction(m_rpCdmFunction, p_bDebugger, this);
    }
}

bool CwmsFunctionEditor::Validate()
{
   bool bRet = true;

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
      MSG_CRIT("Funktionsname fehlt", "Funktion ohne Name kann nicht gespeichert werden!");
   }
   else
   {
       if (!CdmModelElement::CheckKeyname(m_pqleName->text()))
       {
           bRet = false;
           MSG_CRIT("Funktionsname ungültig", "Funktionsname muss mit einem Buchstaben beginnen und darf keine Umlaute und Sonderzeichen auße r\"_\" enthalten.");
       }
   }

   if (m_pjsEditor->toPlainText().isEmpty())
   {
      bRet = false;
      MSG_CRIT("Sourcecode fehlt", "Funktion ohne Sourcecode kann nicht gespeichert werden!");
   }

   if (m_pqtwParameters->topLevelItemCount() > 10)
   {
      bRet = false;
      MSG_CRIT("Zu viele Aufrufparameter",
                                  "Funktion mit mehr als 10 Aufrufparametern ist nicht erlaubt.\n"
                                     "Überprüfen Sie Ihren Programmierstil ;-)\n"
                                     "Lehrgänge zur effizienten Programmierung können Sie bei WOGRA Consulting buchen.");
   }

   if (m_rpCdmClass->HasMethod(m_pqleName->text()))
   {
      if (m_rpCdmClass->FindMethod(m_pqleName->text()) != m_rpCdmFunction)
      {
         bRet = false;
         MSG_CRIT("Funktion existiert bereits", "Eine Funktion mit dem gleichen Namen existiert bereits.");
      }
   }

   return bRet;
}

bool CwmsFunctionEditor::SaveData()
{
   bool bRet = false;

   if (m_rpCdmFunction)
   {
      m_rpCdmFunction->SetComment(m_pqteComment->toPlainText());
      m_rpCdmFunction->SetMethodName(m_pqleName->text());
      EdmValueType eReturnType = (EdmValueType)m_pqcbReturnType->itemData(m_pqcbReturnType->currentIndex()).toInt();
      m_rpCdmFunction->SetReturnType(eReturnType);

      if (m_pqrbPublic->isChecked())
      {
         m_rpCdmFunction->SetAccess(eDmMemberAccessPublic);
      }
      else if (m_pqrbProtected->isChecked())
      {
         m_rpCdmFunction->SetAccess(eDmMemberAccessProtected);
      }
      else if (m_pqrbPrivate->isChecked())
      {
         m_rpCdmFunction->SetAccess(eDmMemberAccessPrivate);
      }

      int iParameterCount = m_pqtwParameters->topLevelItemCount();
      QList<CdmClassMethodParameter> qlParams;

      for (int iCounter = 0; iCounter < iParameterCount; ++iCounter)
      {  
         QTreeWidgetItem* pItem = m_pqtwParameters->topLevelItem(iCounter);

         if (pItem)
         {
            CdmClassMethodParameter cParam;
            cParam.SetName(pItem->text(2));
            cParam.m_eType = (EdmValueType)pItem->data(0, Qt::UserRole).toInt();
            cParam.m_iPos = iCounter;
            cParam.m_lReference = pItem->data(1, Qt::UserRole).toInt();
            qlParams.append(cParam);
         }
      }
    
      m_rpCdmFunction->SetParameters(qlParams);
      m_rpCdmFunction->SetStatic(m_pqrbStatic->isChecked());
      m_rpCdmFunction->SetSourceCode(m_pjsEditor->toPlainText());
      m_rpCdmFunction->SetVersion(m_rpCdmFunction->GetVersion() + 1);

      CdmExecutor::GetExecutor()->GetFunction()->CreateEngine();

      if (CdmExecutor::GetExecutor()->GetFunction()->GetEngine()->SyntaxCheck(m_pjsEditor->toPlainText()))
      {
        bRet = true;
      }

      m_rpCdmFunction->SetCaption(m_pqleCaption->text());
      m_rpCdmFunction->SetIcon(m_qbaIcon);
      m_rpCdmClass->Commit();
      m_pjsEditor->document()->setModified(false);
   }

   return bRet;
}

void CwmsFunctionEditor::SyntaxCheckClickedSlot()
{
   QString qstrCode = m_pjsEditor->toPlainText();
   CdmExecutor::GetExecutor()->GetFunction()->CreateEngine();

   if (CdmExecutor::GetExecutor()->GetFunction()->GetEngine()->SyntaxCheck(qstrCode))
   {
      MSG_INFO(("Syntax gültig"), ("Die Syntax des Codes ist gültig."));
   }
}

void CwmsFunctionEditor::FindNextClickedSlot()
{
    if (!Find(0))
    {
        if (CdmMessageManager::Ask(tr("Keine weiteren Treffer gefunden"), tr("Es wurden keine weiteren Treffer gefunden.\n Soll die Suche von Beginn an weitergeführt werden?")))
        {
            QTextCursor startPos;
            startPos.setPosition(0);
            m_pjsEditor->setTextCursor(startPos);

            if (!Find(0))
            {
                MSG_INFO(("Keine weiteren Treffer gefunden"), ("Es wurden keine weiteren Treffer gefunden."));
            }
        }
    }
}

void CwmsFunctionEditor::FindPreviousClickedSlot()
{
    if (!Find(QTextDocument::FindBackward))
    {
        if (CdmMessageManager::Ask(tr("Keine weiteren Treffer gefunden"), tr("Es wurden keine weiteren Treffer gefunden.\n Soll die Suche vom Ende weitergeführt werden?")))
        {
            QTextCursor startPos;
            startPos.setPosition(m_pjsEditor->document()->characterCount() - 1);
            m_pjsEditor->setTextCursor(startPos);

            if (!Find(QTextDocument::FindBackward))
            {
                MSG_INFO(("Keine weiteren Treffer gefunden"), ("Es wurden keine weiteren Treffer gefunden."));
            }
        }
    }
}

bool CwmsFunctionEditor::Find(QTextDocument::FindFlags flag)
{
    bool bRet = false;
    QTextDocument::FindFlags iConfig = flag;

    if (m_pqchbCaseSensitive->isChecked())
    {
        iConfig = iConfig & QTextDocument::FindCaseSensitively;
    }

    if (m_pqchbWholeWord->isChecked())
    {
        iConfig = iConfig & QTextDocument::FindWholeWords;
    }

    if (m_pqchbRegExp->isChecked())
    {
        bRet = m_pjsEditor->find(QRegExp(m_pqleSearch->text()), iConfig);
    }
    else
    {
        bRet = m_pjsEditor->find(m_pqleSearch->text(), iConfig);
    }

    return bRet;
}

void CwmsFunctionEditor::ReplaceClickedSlot()
{
    if (m_pjsEditor->textCursor().hasSelection() && m_pjsEditor->textCursor().selectedText() == m_pqleSearch->text())
    {
        m_pjsEditor->textCursor().insertText(m_pqleReplace->text());
    }
    else
    {
        if (Find(0))
        {
            m_pjsEditor->textCursor().insertText(m_pqleReplace->text());
        }
    }
}

void CwmsFunctionEditor::ReplaceAllClickedSlot()
{
    int iReplaceCount = 0;
    QTextCursor currentCursor = m_pjsEditor->textCursor();
    QTextCursor startPos;
    startPos.setPosition(0);
    m_pjsEditor->setTextCursor(startPos);

    while (Find(0))
    {
        m_pjsEditor->textCursor().insertText(m_pqleReplace->text());
        ++iReplaceCount;
    }

    QString qstrMssage = QString::fromUtf8("Es wurden ") + QString::number(iReplaceCount) + QString::fromUtf8(" Ersetzungen durchgeführt.");
    MSG_INFO(("Ersetzung durchgeführt"), qstrMssage.toUtf8());
    m_pjsEditor->setTextCursor(currentCursor);
}
