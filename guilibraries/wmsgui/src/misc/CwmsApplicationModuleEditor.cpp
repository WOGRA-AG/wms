/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsApplicationModuleEditor.cpp
 ** Started Implementation: 2012/09/03
 ** Description:
 **
 ** Implements the module editor for an application
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMenu>
#include <QFileDialog>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmQueryBuilder.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsFormObject.h"
#include "CwmsFormUserDefined.h"
#include "CwmsFormManager.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsApplicationModuleEditor.h"


#define GENERIC_OBJECT_FORMS tr("Generische Objekt-Formulare")
#define USER_DEFINED_FORMS tr("Benutzerdefinierte Formulare")
#define DEFAULT_CONTAINER_FORMS tr("Standard-Objektcontainer Formulare")
#define VIEW_CONTAINER_FORMS tr("Sichten-Objektcontainer Formulare")
#define OBJECT_CONTAINER_FORMS tr("Objekt-Objektcontainer Formulare")
#define SEARCH_FORMS tr("Suchformulare")
#define INTERACTIVE_COMPONENT_FORMS tr("InteractiveComponent Formulare")

/** +-=---------------------------------------------------------Mo 3. Sep 17:18:02 2012-----------*
 * @method  CwmsApplicationModuleEditor::CwmsApplicationModuleEditor // public                    *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:18:02 2012-----------*/
CwmsApplicationModuleEditor::CwmsApplicationModuleEditor(QWidget* p_pqwParent)
    : QDialog(p_pqwParent),
      m_rpCdmForm(nullptr),
      m_rpCdmView(nullptr),
      m_rpCdmData(nullptr),
      m_rpCdmDataOL(nullptr)

{
    setupUi(this);
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:18:20 2012-----------*
 * @method  CwmsApplicationModuleEditor::~CwmsApplicationModuleEditor // public, virtual          *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsApplicationModuleEditor                                   *
 *----------------last changed: --------------------------------Mo 3. Sep 17:18:20 2012-----------*/
CwmsApplicationModuleEditor::~CwmsApplicationModuleEditor()
{
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:18:49 2012-----------*
 * @method  CwmsApplicationModuleEditor::FillDialog          // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:18:49 2012-----------*/
void CwmsApplicationModuleEditor::FillDialog(CwmsApplicationModule p_cModule)
{
    m_cModule = p_cModule;

    if (m_cModule.IsValid())
    {
        m_pqchbDefault->setChecked(m_cModule.GetDefault());
        m_pqchbActive->setChecked(m_cModule.GetActive());
        m_pqleName->setText(m_cModule.GetName());

        if (m_cModule.GetContainerModule())
        {
            m_rpCdmDataOL = m_cModule.GetContainerModule();
            m_rpCdmData = nullptr;
            m_pqrbObjectList->setChecked(true);
            m_pqleData->setText(m_rpCdmDataOL->GetCaption());
        }
        else
        {
            m_rpCdmData = m_cModule.GetObjectModule();
            m_rpCdmDataOL = nullptr;
            m_pqrbObject->setChecked(true);

            if (m_rpCdmData)
            {
                m_pqleData->setText(m_rpCdmData->GetCaption());
            }
        }

        m_rpCdmView = m_cModule.GetView();

        if (m_rpCdmView)
        {
            m_pqleView->setText(m_rpCdmView->GetDisplayString("Name"));
        }

        m_rpCdmForm = m_cModule.GetUserInterface();

        if (m_rpCdmForm)
        {
            m_pqleForm->setText(m_rpCdmForm->GetDisplayString("Name"));
        }

        QPixmap qPixmap = m_cModule.GetIcon();

        if (!qPixmap.isNull())
        {
            QIcon qIcon(qPixmap);
            m_pqpbSelectIcon->setIcon(qIcon);
        }
    }
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:24:17 2012-----------*
 * @method  CwmsApplicationModuleEditor::SelectDataClickedSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:24:17 2012-----------*/
void CwmsApplicationModuleEditor::SelectDataClickedSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
        if (m_pqrbObject->isChecked())
        {
            CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);

            if (pCdmClass)
            {
                if (pCdmClass->IsSingleton())
                {
                    m_rpCdmData = pCdmClass->GetSingletonObject();
                    m_rpCdmDataOL = nullptr;

                    if (m_rpCdmData)
                    {
                        m_pqleData->setText(m_rpCdmData->GetCaption());
                    }
                }
                else
                {
                    CdmObjectContainer* pCdmList = CwmsContainerSelectionIf::GetObjectContainer(pCdmClass->GetSchemeId(), pCdmClass->GetId(), this);

                    if (pCdmList)
                    {
                        m_rpCdmData = CwmsObjectSelectionIf::GetObject(pCdmList, nullptr, this);
                        m_rpCdmDataOL = nullptr;

                        if (m_rpCdmData)
                        {
                            m_pqleData->setText(m_rpCdmData->GetCaption());
                        }
                    }
                }
            }
        }
        else if (m_pqrbObjectList->isChecked())
        {
            CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);

            if (pCdmClass)
            {
                m_rpCdmDataOL = CwmsContainerSelectionIf::GetObjectContainer(pCdmClass->GetSchemeId(), pCdmClass->GetId(), this);
                m_rpCdmData = nullptr;

                if (m_rpCdmDataOL)
                {
                    m_pqleData->setText(m_rpCdmDataOL->GetCaption());
                }
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:24:31 2012-----------*
 * @method  CwmsApplicationModuleEditor::SelectFormClickedSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:24:31 2012-----------*/
void CwmsApplicationModuleEditor::SelectFormClickedSlot()
{
    CwmsFormManager cManager;
    QMenu* pqMenu = new QMenu(this);
    pqMenu->addAction(GENERIC_OBJECT_FORMS);
    pqMenu->addAction(USER_DEFINED_FORMS);
    pqMenu->addAction(DEFAULT_CONTAINER_FORMS);
    pqMenu->addAction(VIEW_CONTAINER_FORMS);
    pqMenu->addAction(OBJECT_CONTAINER_FORMS);
    pqMenu->addAction(SEARCH_FORMS);
    pqMenu->addAction(INTERACTIVE_COMPONENT_FORMS);
    QAction* pqaAction = pqMenu->exec(QCursor::pos());
    CdmObjectContainer* pCdmList = nullptr;

    if (pqaAction)
    {
        QString qstrAction = pqaAction->text();

        if (qstrAction == GENERIC_OBJECT_FORMS)
        {
            pCdmList = cManager.GetGenericFormContainer();
        }
        else if (qstrAction == USER_DEFINED_FORMS)
        {
            pCdmList = cManager.GetFormUserDefinedContainer();
        }
        else if (qstrAction == DEFAULT_CONTAINER_FORMS)
        {
            pCdmList = cManager.GetStandardFormContainer();
        }
        else if (qstrAction == VIEW_CONTAINER_FORMS)
        {
            pCdmList = cManager.GetFormViewContainer();
        }
        else if (qstrAction == OBJECT_CONTAINER_FORMS)
        {
            pCdmList = cManager.GetFormObjectObjectContainer();
        }
        else if (qstrAction == SEARCH_FORMS)
        {
            pCdmList = cManager.GetFormSearchContainer();
        }
        else if (qstrAction == INTERACTIVE_COMPONENT_FORMS)
        {
            pCdmList = cManager.GetInteractiveComponentContainer();
        }
    }

    if (CHKPTR(pCdmList))
    {
        m_rpCdmForm = CwmsObjectSelectionIf::GetObject(pCdmList, nullptr, this, "Name");

        if (m_rpCdmForm)
        {
            m_pqleForm->setText(m_rpCdmForm->GetDisplayString("Name"));
        }
    }
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:24:45 2012-----------*
 * @method  CwmsApplicationModuleEditor::SelectViewClickedSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:24:45 2012-----------*/
void CwmsApplicationModuleEditor::SelectViewClickedSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
        CdmObjectContainer* pCdmList = CdmDataProvider::GetObjectContainer("TechnicalViews");

        if (CHKPTR(pCdmList))
        {
            m_rpCdmView = CwmsObjectSelectionIf::GetObject(pCdmList, nullptr, this);

            if (m_rpCdmView)
            {
                m_pqleView->setText(m_rpCdmView->GetCaption());
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:27:23 2012-----------*
 * @method  CwmsApplicationModuleEditor::Validate            // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:27:23 2012-----------*/
bool CwmsApplicationModuleEditor::Validate()
{
    bool bRet = true;

    if (!m_rpCdmData && !m_rpCdmDataOL && !m_rpCdmView &&! m_rpCdmForm)
    {
        bRet = false;
        CdmMessageManager::critical(tr("Fehlende Informationen"),
                                    tr("Die Auswahl ist nicht vollständig mindestens ein Auswahlfeld muss gefüllt sein."));
    }

    if (!m_rpCdmData && m_rpCdmForm &&
            (m_rpCdmForm->IsTypeOf("Technical_Form_UserDefined") ||
             m_rpCdmForm->IsTypeOf("Technical_Form_Object")))
    {
        bool bError = false;

        if (m_rpCdmForm->IsTypeOf("Technical_Form_Object"))
        {
            CwmsFormObject form(m_rpCdmForm);

            if (form.GetWql().isEmpty())
            {
                bError = true;
            }
        }
        else
        {
            CwmsFormUserDefined form(m_rpCdmForm);

            if (form.GetContext() != eWmsFormContextWms)
            {
                bError = true;
            }
        }

        if (bError)
        {
            bRet = false;
            CdmMessageManager::critical(tr("Fehlende Informationen"),
                                        tr("Zum ausgewählten Formular muss ein Objekt ausgewählt sein."));
        }
    }

    if (!m_rpCdmDataOL &&  m_rpCdmForm &&
            (m_rpCdmForm->IsTypeOf("Technical_Form_Standard_ObjectList") ||
             m_rpCdmForm->IsTypeOf("Technical_Form_Object_ObjectList")))
    {
        bRet = false;
        CdmMessageManager::critical(tr("Fehlende Informationen"),
                                    tr("Zum ausgewählten Formular muss eine Objektliste ausgewählt sein."));
    }

    if (m_pqleName->text().isEmpty())
    {
        bRet = true;
        CdmMessageManager::critical(tr("Fehlende Informationen"),
                                    tr("Das Modul benötigt einen Namen."));

    }

    return bRet;
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:27:32 2012-----------*
 * @method  CwmsApplicationModuleEditor::SaveData            // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:27:32 2012-----------*/
void CwmsApplicationModuleEditor::SaveData(bool p_bNew)
{
    if (m_cModule.IsValid())
    {
        m_cModule.SetDefault(m_pqchbDefault->isChecked());
        m_cModule.SetName(m_pqleName->text());
        m_cModule.SetUserInterface(m_rpCdmForm);
        m_cModule.SetView(m_rpCdmView);
        m_cModule.SetActive(m_pqchbActive->isChecked());


        if (p_bNew)
        {
            QString qstrWql ("select max(Position) from \""+ m_cModule.GetObject()->GetObjectContainer()->GetKeyname() + "\"");
            CdmQueryEnhanced* pQuery = static_cast<CdmQueryEnhanced*>(CdmQueryBuilder::ExecuteQuery(qstrWql));

            if (CHKPTR(pQuery))
            {
                m_cModule.SetPosition(pQuery->GetResultAt(0,0).toInt() + 1);
            }
        }

        if (!m_qstrIconName.isEmpty())
        {
            m_cModule.SetIcon(m_qstrIconName);
        }

        if (m_pqrbObject->isChecked())
        {
            m_cModule.SetObjectModule(m_rpCdmData);
            m_cModule.SetContainerModule(nullptr);
        }
        else
        {
            m_cModule.SetObjectModule(nullptr);
            m_cModule.SetContainerModule(m_rpCdmDataOL);
        }
    }
}

/** +-=---------------------------------------------------------Mo 3. Sep 17:24:57 2012-----------*
 * @method  CwmsApplicationModuleEditor::OKClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 17:24:57 2012-----------*/
void CwmsApplicationModuleEditor::OKClickedSlot()
{
    if (Validate())
    {
        accept();
    }
}

/** +-=---------------------------------------------------------Mo 4. Feb 16:47:07 2013-----------*
 * @method  CwmsFunctionEditor::SelectIconClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Feb 16:47:07 2013-----------*/
void CwmsApplicationModuleEditor::SelectIconClickedSlot()
{
    m_qstrIconName = QFileDialog::getOpenFileName(this, tr("Bitte wählen Sie ein Icon aus dem Dateisystem aus"),
                                                  "", "*.png *.jpg *.gif *.ico");

    if (!m_qstrIconName.isEmpty())
    {
        QFile qFile(m_qstrIconName);

        if (qFile.open(QIODevice::ReadOnly))
        {
            m_qbaIcon = qFile.readAll();
            QPixmap qPixmap;
            qPixmap.loadFromData(m_qbaIcon);

            if (!qPixmap.isNull())
            {
                QIcon qIcon(qPixmap);
                m_pqpbSelectIcon->setIcon(qIcon);
            }
        }
    }
}

void CwmsApplicationModuleEditor::DeleteDataClickedSlot()
{
    m_rpCdmData = nullptr;
    m_rpCdmDataOL = nullptr;
    m_pqleData->setText("");
}

void CwmsApplicationModuleEditor::DeleteFormClickedSlot()
{
    m_rpCdmForm = nullptr;
    m_pqleForm->setText("");
}

void CwmsApplicationModuleEditor::DeleteViewClickedSlot()
{
    m_rpCdmView = nullptr;
    m_pqleView->setText("");
}

/** +-=---------------------------------------------------------Mo 3. Sep 18:39:11 2012-----------*
 * @method  CwmsApplicationModuleEditor::EditModule          // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 18:39:11 2012-----------*/
void CwmsApplicationModuleEditor::EditModule(CwmsApplicationModule p_cModule,
                                             bool p_bNew,
                                             QWidget* p_pqwParent)
{
    if (p_cModule.IsValid())
    {
        CwmsApplicationModuleEditor* pEditor = new CwmsApplicationModuleEditor(p_pqwParent);
        pEditor->FillDialog(p_cModule);

        if (pEditor->exec() == QDialog::Accepted)
        {
            pEditor->SaveData(p_bNew);
        }
        else if (p_bNew)
        {
            p_cModule.SetDeleted();
        }

        p_cModule.CommitObject();
        DELPTR(pEditor);
    }
}
