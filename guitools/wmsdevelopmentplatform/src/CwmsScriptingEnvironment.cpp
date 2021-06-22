// System and Qt Includes
#include <QSettings>
#include <QMdiSubWindow>

// WMS Manager Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmClassMethod.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsAddMemberIf.h"
#include "CwmsFormLibrary.h"
#include "CwmsFunctionEditor.h"
#include "CwmsQmlEditor.h"
#include "CwmsQmlLibraryEditor.h"
#include "CwmsFormManager.h"
#include "CwmsClassDataFiller.h"
#include "CwmsMiscDataFiller.h"
#include "CwmsScriptingEnvironment.h"
#include "ui_CwmsScriptingEnvironment.h"

CwmsScriptingEnvironment::CwmsScriptingEnvironment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CwmsScriptingEnvironmentClass),
    m_rpCutCopyElement(nullptr),
    m_rpCurrentItem(nullptr),
    m_eCutCopyMode(eWmsNone),
    m_pAdminMainWindow(nullptr),
    m_pFormItem(nullptr),
    m_pLibraryItem(nullptr)
{
    ui->setupUi(this);

    connect(ui->m_pqtwClasses, SIGNAL(expanded(const QModelIndex&)),
            this, SLOT(ClassesExpandedSlot()));

    connect(ui->m_pqtwUis, SIGNAL(expanded(const QModelIndex&)),
            this, SLOT(UisExpandedSlot()));

    QSettings settings("WOGRA", "SCRIPT_ENVIRONMENT");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    UpdateDockWidgetVisibility();
    AddContextMenus();
}

CwmsScriptingEnvironment::~CwmsScriptingEnvironment()
{
    delete ui;
}

void CwmsScriptingEnvironment::ClassesExpandedSlot()
{
    CwmsTreeWidgetHelper::ResizeColumnsToContent(ui->m_pqtwClasses);
}

void CwmsScriptingEnvironment::UisExpandedSlot()
{
    CwmsTreeWidgetHelper::ResizeColumnsToContent(ui->m_pqtwUis);
}

void CwmsScriptingEnvironment::AddContextMenus()
{
   connect(ui->m_pqtwClasses, SIGNAL(customContextMenuRequested(const QPoint &)),
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   ui->m_pqtwClasses->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(ui->m_pqtwUis, SIGNAL(customContextMenuRequested(const QPoint &)),
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   ui->m_pqtwUis->setContextMenuPolicy(Qt::CustomContextMenu);
}

void CwmsScriptingEnvironment::closeEvent(QCloseEvent* p_pqCloseEvent)
{
   QSettings settings("WOGRA", "SCRIPT_ENVIRONMENT");
   settings.setValue("geometry", saveGeometry());
   settings.setValue("windowState", saveState());

   CloseAllSlot();

   if (m_pAdminMainWindow)
   {
       m_pAdminMainWindow->setEnabled(true);
       m_pAdminMainWindow->RefreshClasses();
       m_pAdminMainWindow->CloseClassSubWindows();
   }

   QMainWindow::closeEvent(p_pqCloseEvent);
}

void CwmsScriptingEnvironment::SetAdminMainWindow(CwmsAdminMainWindowIf* p_pMainWindow)
{
    m_pAdminMainWindow = p_pMainWindow;
}


void CwmsScriptingEnvironment::FillContent()
{
    FillClasses();
    FillUi();
}

void CwmsScriptingEnvironment::FillClasses() // todo remove this function ShowTechnicalClassesChangedSlot() can be called directly
{
    ui->m_pqtwClasses->clear();
    ClearTreeWidgetAssignments();


    QTreeWidgetItem* pClassItem = new QTreeWidgetItem(ui->m_pqtwClasses);
    pClassItem->setText(0, tr("Klassen"));
    pClassItem->setData(1, Qt::UserRole, eWmsTreeItemTypeClassParent);
    CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();
    CwmsClassDataFiller::FillClasses(pClassManager, pClassItem, false, ui->m_pqchbShowTechnicalClasses->isChecked());
    CwmsTreeWidgetHelper::ResizeColumnsToContent(ui->m_pqtwClasses);
}

void CwmsScriptingEnvironment::FillUi()
{
    ui->m_pqtwUis->clear();
    m_pFormItem = new QTreeWidgetItem(ui->m_pqtwUis);
    m_pFormItem->setText(0, tr("Benutzeroberflächen"));
    m_pFormItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFormUserDefinedParent);
    CwmsMiscDataFiller::FillForms(m_pFormItem, "TechnicalFormUserDefined", eWmsTreeItemTypeFormUserDefined);

    m_pLibraryItem = new QTreeWidgetItem(ui->m_pqtwUis);
    m_pLibraryItem->setText(0, QObject::tr("Bibliotheken"));
    m_pLibraryItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFormLibraryParent);
    CwmsMiscDataFiller::FillLibraries(m_pLibraryItem);

    QTreeWidgetItem* pItem = new QTreeWidgetItem(ui->m_pqtwUis);
    pItem->setText(0, QObject::tr("Resourcen"));
    pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeResourceParent);
    CwmsMiscDataFiller::FillResources(pItem);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(ui->m_pqtwUis);
}

void CwmsScriptingEnvironment::OpenObject(CdmLocatedElement* p_pElement)
{
    if (CHKPTR(p_pElement))
    {
        if (p_pElement->IsMethod())
        {
            CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*>(p_pElement);
            if (CHKPTR(pMethod))
            {
                CdmClass* pClass = pMethod->GetClass();

                if (CHKPTR(pClass))
                {
                    if (CwmsClassDataFiller::IsTechnicalClass(pClass))
                    {
                        ui->m_pqchbShowTechnicalClasses->setChecked(true);
                        FillClasses();
                    }
                }


                QTreeWidgetItem* pItem = FindMethodItem(pMethod);
                if (CHKPTR(pItem))
                {
                    pItem->setSelected(true);
                    pItem->parent()->parent()->setExpanded(true); // class
                    pItem->parent()->setExpanded(true); // Functiongrouping
                    EditFunctionSlot(pMethod, pItem);
                }
            }
        }
        else if (p_pElement->IsObject())
        {
            CdmObject* pObject = dynamic_cast<CdmObject*>(p_pElement);

            if (CHKPTR(pObject))
            {
                QTreeWidgetItem* pItem = FindFormLibraryItem(pObject);
                CdmClass* pClass = pObject->GetClass();

                if (CHKPTR(pClass))
                {
                    if (pItem) // can be nullptr if it is a new UI Form
                    {
                        pItem->setSelected(true);
                        pItem->parent()->setExpanded(true);
                    }

                    if (pClass->GetKeyname() == "Technical_Form_UserDefined") //Form
                    {
                        EditFormSlot(pObject, pItem);
                    }
                    else if (pClass->GetKeyname() == "Technical_Form_Library") // Library
                    {
                        EditLibrarySlot(pObject, pItem);
                    }
                }
            }
        }
    }
}

QTreeWidgetItem* CwmsScriptingEnvironment::FindMethodItem(CdmClassMethod* p_pMethod)
{
    QTreeWidgetItem* pItem = nullptr;

    if (CHKPTR(p_pMethod))
    {
        QTreeWidgetItem* pRootItem = ui->m_pqtwClasses->invisibleRootItem();

        if (CHKPTR(pRootItem))
        {
            pItem = FindMethodItem(p_pMethod, pRootItem);
        }

    }

    return pItem;
}

QTreeWidgetItem* CwmsScriptingEnvironment::FindMethodItem(CdmClassMethod* p_pMethod, QTreeWidgetItem* p_pParent)
{
    QTreeWidgetItem* pItem = nullptr;

    if (CHKPTR(p_pMethod) && CHKPTR(p_pParent))
    {
        int iChildCount = p_pParent->childCount();

        for (int iCounter = 0; iCounter < iChildCount; ++iCounter)
        {
            QTreeWidgetItem* pCurrentItem = p_pParent->child(iCounter);

            if (CHKPTR(pCurrentItem))
            {
                if (p_pMethod->GetUriInternal() == pCurrentItem->data(0, Qt::UserRole).toString())
                {
                    pItem = pCurrentItem;

                }
                else
                {
                    pItem = FindMethodItem(p_pMethod, pCurrentItem);
                }

                if (pItem)
                {
                    break;
                }
            }
        }
    }

    return pItem;
}

QTreeWidgetItem* CwmsScriptingEnvironment::CreateItemToObject(CdmObject* p_pObject)
{
    QTreeWidgetItem* pItem = nullptr;
    if (p_pObject->IsExactTypeOf("Technical_Form_UserDefined"))
    {
        CwmsFormUserDefined cForm(p_pObject);
        pItem = new QTreeWidgetItem(m_pFormItem);
        pItem->setText(0, cForm.GetName());
        pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFormUserDefined);
        pItem->setData(0, Qt::UserRole, (int)p_pObject->GetId());
    }
    else if (p_pObject->IsExactTypeOf("Technical_Form_Library"))
    {
        CwmsFormLibrary cForm(p_pObject);
        pItem = new QTreeWidgetItem(m_pLibraryItem);
        pItem->setText(0, cForm.GetName());
        pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFormLibrary);
        pItem->setData(0, Qt::UserRole, (int)p_pObject->GetId());
    }

    return pItem;
}

QTreeWidgetItem* CwmsScriptingEnvironment::FindFormLibraryItem(CdmObject* p_pObject)
{
    QTreeWidgetItem* pItem = nullptr;

    if (CHKPTR(p_pObject))
    {
        QTreeWidgetItem* pRootItem = ui->m_pqtwUis->invisibleRootItem();

        if (CHKPTR(pRootItem))
        {
           pItem = FindFormLibraryItem(p_pObject, pRootItem);

           if (!pItem)
           {
               pItem = CreateItemToObject(p_pObject);
           }
        }
    }

    return pItem;
}

QTreeWidgetItem* CwmsScriptingEnvironment::FindFormLibraryItem(CdmObject* p_pObject, QTreeWidgetItem* p_pParent)
{
    QTreeWidgetItem* pItem = nullptr;

    if (CHKPTR(p_pObject) && CHKPTR(p_pParent))
    {
        int iChildCount = p_pParent->childCount();

        for (int iCounter = 0; iCounter < iChildCount; ++iCounter)
        {
            QTreeWidgetItem* pCurrentItem = p_pParent->child(iCounter);

            if (CHKPTR(pCurrentItem))
            {
                if (p_pObject->GetId() == pCurrentItem->data(0, Qt::UserRole).toInt())
                {
                    pItem = pCurrentItem;

                }
                else
                {
                    pItem = FindFormLibraryItem(p_pObject, pCurrentItem);
                }

                if (pItem)
                {
                    break;
                }
            }
        }
    }

    return pItem;
}

void CwmsScriptingEnvironment::CustomContextMenuSlot(const QPoint & p_Pos)
{
   QTreeWidget* pCurrentWidget = nullptr;
   QObject* pObject = sender();
   QString qstrClassName = pObject->metaObject()->className();

   if (qstrClassName == "QTreeWidget")
   {
      pCurrentWidget = static_cast<QTreeWidget*> (sender());
   }

   if (pCurrentWidget)
   {
      m_rpCurrentItem = pCurrentWidget->itemAt(p_Pos);

      if(m_rpCurrentItem)
      {
         QMenu qMenu(this);
         EwmsTreeItemType eType = (EwmsTreeItemType)m_rpCurrentItem->data(1, Qt::UserRole).toInt();

         qMenu.addAction(ui->m_pqaRefresh);


         if (eType != eWmsTreeItemTypeNone &&
             eType != eWmsTreeItemTypeClass)
         {
            qMenu.addAction(ui->m_pqaNew);
            qMenu.addAction(ui->m_pqaEdit);
            qMenu.addAction(ui->m_pqaDelete);
            qMenu.addSeparator();
         }

         qMenu.exec(QCursor::pos());
      }
   }
}

void CwmsScriptingEnvironment::UpdateDockWidgetVisibility()
{
   ui->m_pqmView->addAction(ui->m_pqdwClasses->toggleViewAction());
   ui->m_pqmView->addAction(ui->m_pqdwUIs->toggleViewAction());
}

void CwmsScriptingEnvironment::CloseSlot()
{
    QMdiSubWindow* pSubWindow = ui->m_pqMdi->currentSubWindow();

    if (pSubWindow)
    {
        pSubWindow->close();
    }
}

void CwmsScriptingEnvironment::CloseAllSlot()
{
    QList<QMdiSubWindow*> qlSubWindows = ui->m_pqMdi->subWindowList();

    for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
    {
       QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];
       pTempWindow->close();
    }
}

void CwmsScriptingEnvironment::CopySlot()
{
    if(m_rpCurrentItem)
    {
        m_eCutCopyMode = eWmsCopy;
        m_rpCutCopyElement = GetCurrentElement();
    }
    else
    {
        CdmMessageManager::information(tr("Operation nicht möglich"), tr("Es ist keine Selektion vorhanden.\n Aus diesem Grund kann diese Aktion icht ausgeführt werden."));
    }
}

void CwmsScriptingEnvironment::CutSolt()
{
    if(m_rpCurrentItem)
    {
        m_eCutCopyMode = eWmsCut;
        m_rpCutCopyElement = GetCurrentElement();
    }
    else
    {
        CdmMessageManager::information(tr("Operation nicht möglich"), tr("Es ist keine Selektion vorhanden.\n Aus diesem Grund kann diese Aktion icht ausgeführt werden."));
    }
}

CdmLocatedElement* CwmsScriptingEnvironment::GetCurrentElement()
{
    CdmLocatedElement* pElement = nullptr;
    CwmsFormManager cManager;

    if(m_rpCurrentItem)
    {
        EwmsTreeItemType eType = (EwmsTreeItemType)m_rpCurrentItem->data(1, Qt::UserRole).toInt();

        if (eType == eWmsTreeItemTypeFormUserDefined)
        {
            CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();

            if (CHKPTR(pCdmList))
            {
               pElement = pCdmList->FindObjectById(m_rpCurrentItem->data(0, Qt::UserRole).toInt());
            }
        }
        else if (eType == eWmsTreeItemTypeFunction)
        {
            QString qstrUri = m_rpCurrentItem->data(0, Qt::UserRole).toString();
            pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);
        }
        else if (eType == eWmsTreeItemTypeFormLibrary)
        {
            CdmObjectContainer* pCdmList = cManager.GetFormLibrary();

            if (CHKPTR(pCdmList))
            {
               pElement = pCdmList->FindObjectById(m_rpCurrentItem->data(0, Qt::UserRole).toInt());
            }
        }
        else
        {
            CdmMessageManager::critical(tr("Kopieren oder Ausschneiden nicht möglich"),
                                        tr("Das markeirte Objekt kann nicht kopiert oder ausgeschnitten werden.\n"
                                           "Diese Funktion gibt es nur für Funktionen, Benutzeroberflächen oder Bibliotheken."));
        }
    }

    return pElement;
}

void CwmsScriptingEnvironment::DeleteSlot()
{
    if(m_rpCurrentItem)
    {
        DeleteItem(m_rpCurrentItem);
    }
    else
    {
        CdmMessageManager::information(tr("Operation nicht möglich"), tr("Es ist keine Selektion vorhanden.\n Aus diesem Grund kann diese Aktion icht ausgeführt werden."));
    }
}

void CwmsScriptingEnvironment::DeleteItem(QTreeWidgetItem* p_pItem)
{
    if (CdmMessageManager::Ask(tr("Wirklich löschen?"),
       tr("Das Objekt wird unwiderruflich gelöscht."
       "Wollen Sie das wirklich?")))
    {
       EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

       if (eType == eWmsTreeItemTypeFormUserDefined)
       {
          DeleteUserDefinedFormSlot(p_pItem);
       }
       else if (eType == eWmsTreeItemTypeMember)
       {
          DeleteMemberSlot(p_pItem);
       }
       else if (eType == eWmsTreeItemTypeFunction)
       {
          DeleteFunctionSlot(p_pItem);
       }
       else if (eType == eWmsTreeItemTypeFormLibrary)
       {
           DeleteLibrarySlot(p_pItem);
       }
       else if (eType == eWmsTreeItemTypeResource)
       {
           DeleteResourceSlot(p_pItem);
       }
       else
       {
           CdmMessageManager::critical(tr("Löschen nicht möglich"), tr("Dieses Objekt kann in der Skriptumgebung nicht gelöscht werden."));
       }
    }
}

void CwmsScriptingEnvironment::DebugSlot()
{
    QMdiSubWindow* pSubWindow = ui->m_pqMdi->currentSubWindow();

    if (CHKPTR(pSubWindow))
    {
        IwmsScriptEditor* pWidget = dynamic_cast<IwmsScriptEditor*>(pSubWindow->widget());

        if (pWidget)
        {
            CdmMessageManager::StartAsyncMessageCollection();
            pWidget->Debug();
            CdmMessageManager::EndAndShowAsyncMessageCollection();

        }
    }
}

void CwmsScriptingEnvironment::ExecuteSlot()
{
    QMdiSubWindow* pSubWindow = ui->m_pqMdi->currentSubWindow();

    if (CHKPTR(pSubWindow))
    {
        IwmsScriptEditor* pWidget = dynamic_cast<IwmsScriptEditor*>(pSubWindow->widget());

        if (pWidget)
        {
            CdmMessageManager::StartAsyncMessageCollection();
            pWidget->Execute();
            CdmMessageManager::EndAndShowAsyncMessageCollection();
        }
    }
}

void CwmsScriptingEnvironment::InsertSlot()
{
    if (m_rpCutCopyElement)
    {
        if(m_rpCurrentItem)
        {
            if (m_eCutCopyMode == eWmsCopy)
            {
                // ToDo
            }
            else if (m_eCutCopyMode == eWmsCut)
            {
                // ToDo
            }
            else
            {
                // don't know what to do
                ERR("Unknown operation wanted! Neither copy or cut selected for element");
            }
        }
        else
        {
            CdmMessageManager::critical(tr("Einfügen nicht möglich"), tr("Es wurde keine Element in der Baumstruktur gewählt auf dass diese Operation ausgeführt werden soll."));
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Einfügen nicht möglich"), tr("Es wurde keine Element gewählt, dass man an Einfügen kann"));
    }
}

void CwmsScriptingEnvironment::NewSlot()
{
    if(m_rpCurrentItem)
    {
        NewItem(m_rpCurrentItem);
    }
    else
    {
        CdmMessageManager::information(tr("Operation nicht möglich"), tr("Es ist keine Selektion vorhanden.\n Aus diesem Grund kann diese Aktion icht ausgeführt werden."));
    }
}

void CwmsScriptingEnvironment::NewItem(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

        if (eType == eWmsTreeItemTypeClass)
        {
            CdmMessageManager::critical(tr("Neuanlage nicht möglich"), tr("Funktion steht bei der Selektion einer Klasse nicht zur Verfügung."));
        }
        else if (eType == eWmsTreeItemTypeFormLibrary || eType == eWmsTreeItemTypeFormLibraryParent)
        {
            NewLibrary(p_pItem);
        }
        else if (eType == eWmsTreeItemTypeFormUserDefined || eType == eWmsTreeItemTypeFormUserDefinedParent)
        {
            NewForm(p_pItem);
        }
        else if (eType == eWmsTreeItemTypeResource || eType == eWmsTreeItemTypeResourceParent)
        {
            NewResource(p_pItem);
        }
        else if (eType == eWmsTreeItemTypeFunction || eType == eWmsTreeItemTypeFunctionParent)
        {
            NewFunction(p_pItem);
        }
        else if (eType == eWmsTreeItemTypeMember || eType == eWmsTreeItemTypeMemberParent)
        {
            NewMember(p_pItem);
        }
    }
}

void CwmsScriptingEnvironment::NewLibrary(QTreeWidgetItem* p_pItem)
{
    CwmsFormManager cFormManager;
    CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

    if (CHKPTR(pContainer))
    {
        CdmObject* pObject = pContainer->CreateNewObject();

        if (CHKPTR(pObject))
        {
            CwmsFormLibrary form(pObject);
            form.SetName(tr("Neue Bibliothek_") + QDateTime::currentDateTime().toString());
            CwmsQmlLibraryEditor* pEditor = new CwmsQmlLibraryEditor(ui->m_pqMdi);
            pEditor->FillDialog(form);

            QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

            if (CHKPTR(pSubWindow))
            {
               pSubWindow->setWindowTitle(tr("Bibliothek ") + form.GetName() + " Version " + form.GetVersion());
               pSubWindow->setObjectName(pObject->GetUriInternal());
               pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
            }

             EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();
             QTreeWidgetItem* pParent = p_pItem;

             if (eType != eWmsTreeItemTypeFormLibraryParent)
             {
                 pParent = p_pItem->parent();
             }

             QTreeWidgetItem* pNewForm = new QTreeWidgetItem(pParent);
             pNewForm->setText(0, form.GetName());
             pNewForm->setData(1, Qt::UserRole, eWmsTreeItemTypeFormLibrary);
             pNewForm->setData(0, Qt::UserRole, (int)pObject->GetId());
             pEditor->SetItem(pNewForm);
        }
    }
}

void CwmsScriptingEnvironment::NewForm(QTreeWidgetItem* p_pItem)
{
    CwmsFormManager cManager;
    CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();

    if (CHKPTR(pCdmList))
    {
       CdmObject* pObject = pCdmList->CreateNewObject();

       if (CHKPTR(pObject))
       {
          CwmsFormUserDefined cForm(pObject);
          cForm.SetName(tr("Neue Benutzeroberfläche_") + QDateTime::currentDateTime().toString());
          cForm.CommitObject();

          CwmsQmlEditor* pEditor = new CwmsQmlEditor(ui->m_pqMdi);
          pEditor->FillDialog(cForm);

          QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

          if (CHKPTR(pSubWindow))
          {
             pSubWindow->setWindowTitle(tr("Benutzeroberfläche ") + cForm.GetName());
             pSubWindow->setObjectName(cForm.GetUriInternal());
             pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
          }

          EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();
          QTreeWidgetItem* pParent = p_pItem;

          if (eType != eWmsTreeItemTypeFormUserDefinedParent)
          {
              pParent = p_pItem->parent();
          }

          QTreeWidgetItem* pNewForm = new QTreeWidgetItem(pParent);
          pNewForm->setText(0, cForm.GetName());
          pNewForm->setData(1, Qt::UserRole, eWmsTreeItemTypeFormUserDefined);
          pNewForm->setData(0, Qt::UserRole, (int)pObject->GetId());
          pEditor->SetItem(pNewForm);
       }
    }

}

void CwmsScriptingEnvironment::NewResource(QTreeWidgetItem* p_pItem)
{
    Q_UNUSED(p_pItem);
    CwmsFormManager cFormManager;
    CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

    if (CHKPTR(pContainer))
    {
        CdmObject* pObject = pContainer->CreateNewObject();
        if (CwmsguiObjectEditorSelector::Create(pObject, this))
        {
            FillUi();
        }
    }
}

void CwmsScriptingEnvironment::NewFunction(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        CdmClassMethod* pMethod = p_pClass->CreateMethod(tr("New_Function"));
        p_pClass->Commit();
        FillClasses();
        OpenObject(pMethod);
    }
}

void CwmsScriptingEnvironment::NewFunction(QTreeWidgetItem* p_pItem)
{
    CdmClassMethod* pMethod = nullptr;

    if (p_pItem)
    {
         CdmClass* pClass = GetClassFromItem(p_pItem);

         if (CHKPTR(pClass))
         {
             pMethod = pClass->CreateMethod(tr("New_Function"));
             pClass->Commit();
         }

         EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

         if (eType == eWmsTreeItemTypeFunction)
         {
             p_pItem = p_pItem->parent();
         }

         if (CHKPTR(pMethod))
         {
             QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pItem);
             pItem->setText(0, pMethod->GetMethodName());
             pItem->setData(0, Qt::UserRole, pMethod->GetUriInternal());
             pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFunction);

             CwmsFunctionEditor* pEditor = new CwmsFunctionEditor(ui->m_pqMdi);
             pEditor->FillDialog(pMethod, pClass, false);
             pEditor->SetItem(pItem);

             QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

             if (CHKPTR(pSubWindow))
             {
                pSubWindow->setWindowTitle(tr("Funktion ") + pClass->GetKeyname() + "." + pMethod->GetMethodName());
                pSubWindow->setObjectName(pMethod->GetUriInternal());
                pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
             }
         }
    }
}

CdmClass* CwmsScriptingEnvironment::GetClassFromItem(QTreeWidgetItem* p_pItem)
{
    CdmClass* pClass = nullptr;

    if (p_pItem)
    {
         EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

         if (eType == eWmsTreeItemTypeFunction)
         {
            QString qstrUri = p_pItem->data(0, Qt::UserRole).toString();
            CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);
            CdmClassMethod* pMethod = nullptr;

            if (CHKPTR(pElement) && pElement->IsMethod())
            {
                pMethod = static_cast<CdmClassMethod*>(pElement);
            }

            if (pMethod)
            {
                pClass = pMethod->GetClass();
            }
         }
         else if (eType == eWmsTreeItemTypeFunctionParent || eType == eWmsTreeItemTypeMemberParent)
         {
             QTreeWidgetItem* pClassItem = p_pItem->parent();
             long lClassId = pClassItem->data(0, Qt::UserRole).toInt();
             pClass = CdmSessionManager::GetDataProvider()->GetClassManager()->FindClassById(lClassId);
         }
         else if (eType == eWmsTreeItemTypeMember)
         {
            p_pItem = p_pItem->parent();

            eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

            if (eType == eWmsTreeItemTypeGroup)
            {
                p_pItem = p_pItem->parent();
            }

            eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

            if (eType == eWmsTreeItemTypeMemberParent)
            {
                pClass = GetClassFromItem(p_pItem);
            }
         }
    }

    return pClass;
}

void CwmsScriptingEnvironment::NewMember(QTreeWidgetItem* p_pItem)
{
    CdmClass* pClass = GetClassFromItem(p_pItem);
    if (CHKPTR(pClass))
    {
        CwmsAddMemberIf* pCwmsAddMemberIf = new CwmsAddMemberIf(pClass, this);
        pCwmsAddMemberIf->Init();
        pCwmsAddMemberIf->exec();
        DELPTR(pCwmsAddMemberIf);
        pClass->Commit();
        FillClasses();
    }
}

void CwmsScriptingEnvironment::SaveSlot()
{
    QMdiSubWindow* pSubWindow = ui->m_pqMdi->currentSubWindow();

    if (pSubWindow)
    {
        Save(pSubWindow);
    }
}

void CwmsScriptingEnvironment::Save(QMdiSubWindow* p_pSubWindow)
{
    if (CHKPTR(p_pSubWindow))
    {
        IwmsScriptEditor* pWidget = dynamic_cast<IwmsScriptEditor*>(p_pSubWindow->widget());

        if (CHKPTR(pWidget) && pWidget->IsModified())
        {
            pWidget->Save();
        }
    }
}

void CwmsScriptingEnvironment::SaveAllSlot()
{
    QList<QMdiSubWindow*> qlSubWindows = ui->m_pqMdi->subWindowList();

    for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
    {
       QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];
       Save(pTempWindow);
    }
}

void CwmsScriptingEnvironment::ClearTreeWidgetAssignments()
{
    QList<QMdiSubWindow*> qlSubWindows = ui->m_pqMdi->subWindowList();

    for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
    {
       QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];
       IwmsScriptEditor* pWidget = dynamic_cast<IwmsScriptEditor*>(pTempWindow->widget());

       if (CHKPTR(pWidget))
       {
           pWidget->SetItem(nullptr);
       }
    }
}

void CwmsScriptingEnvironment::EditClicked()
{
    QObject* pObject = sender();
    QString qstrClassName = pObject->metaObject()->className();

    if (qstrClassName == "QTreeWidget")
    {
       QTreeWidget* pqCurrentWidget = dynamic_cast<QTreeWidget*> (sender());
       m_rpCurrentItem = CwmsTreeWidgetHelper::GetSelectedItem(pqCurrentWidget);

    }

    if (m_rpCurrentItem)
    {
        EditSlot(m_rpCurrentItem);
    }
}

void CwmsScriptingEnvironment::RefreshSlot()
{
    SaveAllSlot();
    CloseAllSlot();
    FillContent();
}

void CwmsScriptingEnvironment::EditSlot(QTreeWidgetItem* p_pItem)
{
   if (p_pItem)
   {
      EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

      if (eType == eWmsTreeItemTypeFormUserDefined)
      {
         EditFormSlot(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeMember)
      {
         EditMemberSlot(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeFunction)
      {
         EditFunctionSlot(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeFormLibrary)
      {
          EditLibrarySlot(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeResource)
      {
          EditResourceSlot(p_pItem);
      }
   }
}

void CwmsScriptingEnvironment::EditFormSlot(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        CwmsFormManager cManager;
        CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();

        if (CHKPTR(pCdmList))
        {
           CdmObject* pCdmObject = pCdmList->FindObjectById(p_pItem->data(0, Qt::UserRole).toInt());
           EditFormSlot(pCdmObject, p_pItem);
        }
    }
}

void CwmsScriptingEnvironment::EditFormSlot(CdmObject* p_pObject, QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pObject))
    {
        if (!FindAndSetSubWindow(p_pObject->GetUriInternal()))
        {
           CwmsFormUserDefined cForm(p_pObject);
           CwmsQmlEditor* pEditor = new CwmsQmlEditor(ui->m_pqMdi);
           pEditor->FillDialog(cForm);
           pEditor->SetItem(p_pItem);

           QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

           if (CHKPTR(pSubWindow))
           {
              pSubWindow->setWindowTitle(tr("Benutzeroberfläche ") + cForm.GetName());
              pSubWindow->setObjectName(p_pObject->GetUriInternal());
              pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
           }
       }
    }
}

void CwmsScriptingEnvironment::EditMemberSlot(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        CdmMember* pMember = nullptr;
        QString qstrUri = p_pItem->data(0, Qt::UserRole).toString();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (CHKPTR(pElement) && pElement->IsMember())
        {
            pMember = static_cast<CdmMember*>(pElement);
        }

        if (pMember)
        {
            CwmsAddMemberIf* pCwmsAddMemberIf = new CwmsAddMemberIf(pMember->GetClass(), this);
            pCwmsAddMemberIf->SetMember(pMember);

            if (pCwmsAddMemberIf->exec())
            {
                pMember->GetClass()->Commit();
            }

            delete pCwmsAddMemberIf;
        }
    }
}

void CwmsScriptingEnvironment::EditFunctionSlot(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        CdmClassMethod* pMethod = nullptr;
        QString qstrUri = p_pItem->data(0, Qt::UserRole).toString();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (CHKPTR(pElement) && pElement->IsMethod())
        {
            pMethod = static_cast<CdmClassMethod*>(pElement);
        }

        if (pMethod)
        {
             EditFunctionSlot(pMethod, p_pItem);
        }
    }
}

void CwmsScriptingEnvironment::EditFunctionSlot(CdmClassMethod* p_pMethod, QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pMethod))
    {
         if (!FindAndSetSubWindow(p_pMethod->GetUriInternal()))
         {
             CwmsFunctionEditor* pEditor = new CwmsFunctionEditor(ui->m_pqMdi);
             CdmClass* pClass = p_pMethod->GetClass();
             pEditor->FillDialog(p_pMethod, pClass, false);
             pEditor->SetItem(p_pItem);

             QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

             if (CHKPTR(pSubWindow))
             {
                pSubWindow->setWindowTitle(tr("Funktion ") + pClass->GetKeyname() + "." + p_pMethod->GetMethodName());
                pSubWindow->setObjectName(p_pMethod->GetUriInternal());
                pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
             }
         }
    }
}

void CwmsScriptingEnvironment::EditLibrarySlot(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

        if (eType == eWmsTreeItemTypeFormLibrary)
        {
            long lObjectId = p_pItem->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    EditLibrarySlot(pObject, p_pItem);
                }
            }
        }
    }
}

void CwmsScriptingEnvironment::EditLibrarySlot(CdmObject* p_pObject, QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pObject))
    {
        if (!FindAndSetSubWindow(p_pObject->GetUriInternal()))
        {
            CwmsFormLibrary form(p_pObject);
            CwmsQmlLibraryEditor* pEditor = new CwmsQmlLibraryEditor(ui->m_pqMdi);
            pEditor->FillDialog(form);
            pEditor->SetItem(p_pItem);

            QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

            if (CHKPTR(pSubWindow))
            {
               pSubWindow->setWindowTitle(tr("Bibliothek ") + form.GetName() + " Version " + form.GetVersion());
               pSubWindow->setObjectName(p_pObject->GetUriInternal());
               pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
            }
        }
    }
}

void CwmsScriptingEnvironment::EditResourceSlot(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        EwmsTreeItemType eType = (EwmsTreeItemType)p_pItem->data(1, Qt::UserRole).toInt();

        if (eType == eWmsTreeItemTypeResource)
        {
            long lObjectId = p_pItem->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    CwmsguiObjectEditorSelector::Edit(pObject, this);
                }
            }
        }
    }
}

QMdiSubWindow* CwmsScriptingEnvironment::AddMdiWindow(QWidget* p_pWidget)
{
   QMdiSubWindow* pSubWindow = nullptr;

   if (CHKPTR(p_pWidget))
   {
      pSubWindow = ui->m_pqMdi->addSubWindow(p_pWidget);

      if (CHKPTR(pSubWindow))
      {
         p_pWidget->show();
      }
   }

   return pSubWindow;
}

bool CwmsScriptingEnvironment::FindAndSetSubWindow(QString p_qstrUri)
{
   bool bRet = false;
   QMdiSubWindow* pWindow = FindSubWindowByUri(p_qstrUri);

   if (pWindow)
   {
      bRet = true;
      ui->m_pqMdi->setActiveSubWindow(pWindow);
   }

   return bRet;
}

QMdiSubWindow* CwmsScriptingEnvironment::FindSubWindowByUri(QString p_qstrUri)
{
   QMdiSubWindow* pSubWindow = nullptr;

   if (!p_qstrUri.isEmpty())
   {
      QList<QMdiSubWindow*> qlSubWindows = ui->m_pqMdi->subWindowList();

      for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
      {
         QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];

         if (pTempWindow->objectName() == p_qstrUri)
         {
            pSubWindow = pTempWindow;
            break;
         }
      }
   }

   return pSubWindow;
}

void CwmsScriptingEnvironment::TreeViewSelectionChangedSlot()
{
    m_rpCurrentItem = nullptr;

    QObject* pObject = sender();
    QString qstrClassName = pObject->metaObject()->className();

    if (qstrClassName == "QTreeWidget")
    {
       QTreeWidget* pqCurrentWidget = dynamic_cast<QTreeWidget*> (sender());
       m_rpCurrentItem = CwmsTreeWidgetHelper::GetSelectedItem(pqCurrentWidget);
    }
}

void CwmsScriptingEnvironment::DeleteFunctionSlot(QTreeWidgetItem* pqtwMethod)
{
    CdmClassMethod* pMethod = nullptr;

    if (pqtwMethod)
    {
        QString qstrUri = pqtwMethod->data(0, Qt::UserRole).toString();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (CHKPTR(pElement) && pElement->IsMethod())
        {
            pMethod = static_cast<CdmClassMethod*>(pElement);
        }

        if (pMethod)
        {
            CdmClass* pClass = pMethod->GetClass();

            if (pClass)
            {
                QMdiSubWindow* pSubWindow = FindSubWindowByUri(qstrUri);

                if (pSubWindow)
                {
                    pSubWindow->close();
                }

                pClass->DeleteMethod(pMethod->GetMethodName());
                pClass->Commit();
                DELPTR(pqtwMethod);

            }
        }
    }
}

void CwmsScriptingEnvironment::DeleteMemberSlot(QTreeWidgetItem* pqtwMember)
{
    CdmMember* pMember = nullptr;
    if (pqtwMember)
    {
        QString qstrUri = pqtwMember->data(0, Qt::UserRole).toString();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (CHKPTR(pElement) && pElement->IsMember())
        {
            pMember = static_cast<CdmMember*>(pElement);
        }

        if (pMember)
        {
            CdmClass* pClass = pMember->GetClass();

            if (pClass)
            {
                pClass->DeleteMember(pMember->GetKeyname());
                pClass->Commit();
                DELPTR(pqtwMember);
            }
        }
    }
}

void CwmsScriptingEnvironment::DeleteLibrarySlot(QTreeWidgetItem* pCurrent)
{
    if (pCurrent)
    {
        EwmsTreeItemType eType = (EwmsTreeItemType)pCurrent->data(1, Qt::UserRole).toInt();

        if (eType == eWmsTreeItemTypeFormLibrary)
        {
            long lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    QString qstrUri = pObject->GetUriInternal();
                    pObject->SetDeleted();
                    QMdiSubWindow* pSubWindow = FindSubWindowByUri(qstrUri);

                    if (pSubWindow)
                    {
                        pSubWindow->close();
                    }

                    pObject->Commit();
                    DELPTR(pCurrent);
                }
            }
        }
    }
}

void CwmsScriptingEnvironment::DeleteResourceSlot(QTreeWidgetItem* pCurrent)
{
    if (pCurrent)
    {
        EwmsTreeItemType eType = (EwmsTreeItemType)pCurrent->data(1, Qt::UserRole).toInt();

        if (eType == eWmsTreeItemTypeResource)
        {
            long lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    QString qstrUri = pObject->GetUriInternal();
                    pObject->SetDeleted();
                    pObject->Commit();
                    DELPTR(pCurrent);
                    QMdiSubWindow* pSubWindow = FindSubWindowByUri(qstrUri);

                    if (pSubWindow)
                    {
                        pSubWindow->close();
                    }
                }
            }
        }
    }
}

void CwmsScriptingEnvironment::DeleteUserDefinedFormSlot(QTreeWidgetItem* pItem)
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
          QString qstrUri = pCdmObject->GetUriInternal();
          pCdmObject->SetDeleted();
          QMdiSubWindow* pSubWindow = FindSubWindowByUri(qstrUri);

          if (pSubWindow)
          {
              pSubWindow->close();
          }

          pCdmObject->Commit();
          DELPTR(pItem);
      }
   }
}

void CwmsScriptingEnvironment::ShowTechnicalClassesChangedSlot()
{
    FillClasses();
}
