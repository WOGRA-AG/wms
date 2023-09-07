// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CsaClass.h"
#include <CsaFactory.h>
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CdmObjectContainer.h"
#include "CdmQuery.h"

// WMS Entities Includes
#include <CwmsExportSettings.h>
#include <CwmsExportSettingsIf.h>
#include <CwmsFormUserDefined.h>
#include <CwmsImport.h>
#include <CwmsScriptableModel.h>

// own Includes
#include "CwmsJournalViewer.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsScriptableUi.h"
#include "CwmsFormManager.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsFormUserDefinedExecutor.h"
#include <CwmsImportDlg.h>
#include <CwmsImportSettings.h>
#include <CwmsPrintingTemplateProperties.h>
#include <CwmsReportManager.h>
#include <CwmsSearchWindowDlg.h>

CwmsScriptableUi::CwmsScriptableUi()
{
}

CwmsScriptableUi::~CwmsScriptableUi()
{
}

void CwmsScriptableUi::openUi(CsaObject* p_pCdmObject, QWidget* parent)
{
    if (CHKPTR(p_pCdmObject))
    {
        CwmsguiObjectEditorSelector::Edit(p_pCdmObject->getInternals(), parent);
    }
}

void CwmsScriptableUi::openUi(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    if (CHKPTR(p_pContainer))
    {
        CwmsguiObjectEditorSelector::Edit(p_pContainer->getInternals(), parent);
    }
}

void CwmsScriptableUi::openUi(QString p_qstrName, CsaObject* p_pCdmObject, QWidget* parent)
{
    CwmsFormManager cFormManager;
    auto* pFormObj = cFormManager.GetUserDefinedUi(p_qstrName);
    CwmsFormUserDefined cForm(pFormObj);
    CwmsFormUserDefinedExecutor cExecutor;
    cExecutor.ExecuteUserDefinedFormObject(cForm, p_pCdmObject->getInternals(), parent);
}

void CwmsScriptableUi::openUi(QString p_qstrName, CsaObjectContainer* p_pContainer, QWidget* parent)
{
    CwmsFormManager cFormManager;
    auto* pFormObj = cFormManager.GetUserDefinedUi(p_qstrName);
    CwmsFormUserDefined cForm(pFormObj);
    CwmsFormUserDefinedExecutor cExecutor;
    cExecutor.ExecuteUserDefinedFormContainer(cForm, p_pContainer->getInternals(), parent);
}

void CwmsScriptableUi::openUi(QString p_qstrName, QWidget* parent)
{
    CwmsFormManager cFormManager;
    auto* pFormObj = cFormManager.GetUserDefinedUi(p_qstrName);
    CwmsFormUserDefined cForm(pFormObj);
    CwmsFormUserDefinedExecutor cExecutor;
    cExecutor.ExecuteUserDefinedFormMisc(cForm, parent);
}

void CwmsScriptableUi::openSearch(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    if (CHKPTR(p_pContainer))
    {
        CwmsSearchWindowDlg* pSearch = new CwmsSearchWindowDlg(parent);
        pSearch->FillDialog(p_pContainer->getInternals());
        pSearch->exec();
        DELPTR(pSearch);
    }
}

void CwmsScriptableUi::openImport(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    if (CHKPTR(p_pContainer))
    {
        CwmsImportSettings cCwmsImportSettings;
        cCwmsImportSettings.SetContainer(p_pContainer->getInternals());
        CwmsImport cImport;
        CwmsImportDlg cImportDlg(&cCwmsImportSettings, &cImport, parent);

        if (cImportDlg.exec() == QDialog::Accepted)
        {
            cImport.StartImport(p_pContainer->getInternals(), cCwmsImportSettings);
        }
    }
}

void CwmsScriptableUi::openExport(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    if (CHKPTR(p_pContainer))
    {
        CwmsExportSettings cCwmsExportSettings;
        cCwmsExportSettings.SetContainerId(p_pContainer->getId());
        cCwmsExportSettings.SetSchemeId(p_pContainer->getInternals()->GetSchemeId());
        cCwmsExportSettings.SetClassId(p_pContainer->getInternals()->GetClassId());

        CwmsExportSettingsIf* pCwmsExportSettingsIf = new CwmsExportSettingsIf(cCwmsExportSettings, parent);
        pCwmsExportSettingsIf->FillDialog();
        pCwmsExportSettingsIf->exec();
        delete pCwmsExportSettingsIf;
    }
}

void CwmsScriptableUi::openHistory(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    if (CHKPTR(p_pContainer))
    {
        CwmsJournalViewer* pViewer = new CwmsJournalViewer(parent);
        pViewer->FillDialog(p_pContainer->getInternals());
        pViewer->exec();
        DELPTR(pViewer);
    }
}

void CwmsScriptableUi::openHistory(CsaObject* pObject, QWidget* parent)
{
    if (pObject)
    {
        CwmsJournalViewer* pViewer = new CwmsJournalViewer(parent);
        pViewer->FillDialog(pObject->getInternals());
        pViewer->exec();
        DELPTR(pViewer);
    }
}

QObject* CwmsScriptableUi::selectObject(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    auto pContainer = CwmsObjectSelectionIf::GetObject(p_pContainer->getInternals(), parent);

    if (pContainer)
    {
        return CsaFactory::getCurrentFunctionFactory()->createScriptObject(pContainer);
    }

    return nullptr;
}

QObject* CwmsScriptableUi::selectContainer(CsaClass* p_pCdmClass, QWidget* parent)
{
    auto pContainer = CwmsContainerSelectionIf::GetObjectContainer(p_pCdmClass->getInternals(), parent);

    if (pContainer)
    {
        return CsaFactory::getCurrentFunctionFactory()->createScriptObject(pContainer);
    }

    return nullptr;
}

void CwmsScriptableUi::editPrintingTemplate(CsaObjectContainer* p_pContainer, QWidget* parent)
{
    CwmsReportManager cManager;

    if (cManager.HasPrintingPlugin())
    {
        CwmsPrintingTemplate cTemplate = cManager.GetDefaultReportByClassKeyname(p_pContainer->getInternals()->GetClass()->GetKeyname(), eWmsTemplateTypeList);

        if (cTemplate.IsValid())
        {
            cManager.OpenReportEditor(cTemplate.GetObject(), parent);
        }
        else
        {
            ERR("There is no printing template to edit.");
        }
    }
    else
    {
        ERR("No printing plugin installed. Printingtemplate cann't be edited");
    }
}

void CwmsScriptableUi::editPrintingTemplate(CsaObject* p_pCdmObject, QWidget* parent)
{
    CwmsReportManager cManager;

    if (cManager.HasPrintingPlugin())
    {
        CwmsPrintingTemplate cTemplate = cManager.GetDefaultReportByClassKeyname(p_pCdmObject->getInternals()->GetClass()->GetKeyname(), eWmsTemplateTypeObject);

        if (cTemplate.IsValid())
        {
            cManager.OpenReportEditor(cTemplate.GetObject(), parent);
        }
        else
        {
            ERR("There is no printing template to edit.");
        }
    }
    else
    {
        ERR("No printing plugin installed. Printingtemplate cann't be edited");
    }
}

void CwmsScriptableUi::createPrintingTemplate(QWidget* parent)
{
    CwmsReportManager cManager;

    CdmObjectContainer* pContainer = cManager.GetObjectList();

    if (CHKPTR(pContainer))
    {
        CdmObject* pCdmObject = pContainer->CreateNewObject();

        if (CHKPTR(pCdmObject))
        {
            CwmsPrintingTemplateProperties::EditProperties(parent, pCdmObject, true);
        }
    }
}

QObject* CwmsScriptableUi::selectClass(QWidget* parent)
{
    auto pClass = CwmsClassSelectionIf::GetClass(parent);

    if (pClass)
    {
        return CsaFactory::getCurrentFunctionFactory()->createScriptObject(pClass);
    }

    return nullptr;
}

void CwmsScriptableUi::addModelToItemView(CwmsScriptableModel* p_pModel, QAbstractItemView* p_pItemView)
{
    if (CHKPTR(p_pModel), p_pItemView)
    {
        p_pItemView->setModel(p_pModel->generateItemModel());
    }
}
