// System and QT Includes
#include <QLayout>
#include <QObject>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmQueryEnhanced.h"
#include "CdmDataProvider.h"
#include "CdmValue.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmSession.h"
#include "CwmsJson.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"

// WMSBASETOOLS Includes
#include "CwmsbtSessionManager.h"

// own Includes
#include "CwmsJournalViewer.h"
#include "CwmsguiValidator.h"
#include "CwmsguiObjectEditorIf.h"

CwmsguiObjectEditorIf::CwmsguiObjectEditorIf(CdmObject* p_pCdmObject,
                                             QWidget* parent)
    : QDialog(parent),
      m_rpCwmsValidator(nullptr),
      m_qstrObjectEventMode("")
{
    setupUi(this);
    m_rpCdmObject = p_pCdmObject;
}

CwmsguiObjectEditorIf::~CwmsguiObjectEditorIf()
{
}

void CwmsguiObjectEditorIf::SetValidator(CwmsguiValidator* p_pCwmsguiValidator)
{
    m_rpCwmsValidator = p_pCwmsguiValidator;
}

void CwmsguiObjectEditorIf::FillDialog()
{
    CdmClass* pCdmClass = m_rpCdmObject->GetClass();

    if (CHKPTR(m_rpCdmObject))
    {
        m_pCoeObjectEditor->SetObject(m_rpCdmObject);
        m_pCoeObjectEditor->FillObjectEditor();

        if (CHKPTR(pCdmClass))
        {
            setWindowTitle(m_rpCdmObject->GetCaption() + QStringLiteral(" - ") + m_rpCdmObject->GetKeyname());
            m_pqlArticleType->setText(pCdmClass->GetCaption() + QStringLiteral(" ") + tr("bearbeiten"));
        }
    }
}

void CwmsguiObjectEditorIf::SetSortedList(QStringList p_qstrlSorting)
{
    m_pCoeObjectEditor->SetSortedList(p_qstrlSorting);
}

void CwmsguiObjectEditorIf::OKClickedSlot()
{
    bool bContinue = true;

    if(m_rpCwmsValidator)
    {
        bContinue = m_rpCwmsValidator->Validate();
    }

    if (bContinue)
    {
        CdmObjectContainer *container = m_rpCdmObject->GetObjectContainer();
        if (CdmExecutor::ExecuteValidation(container))
        {
            accept();
        }
    }
}

void CwmsguiObjectEditorIf::SetReadOnly()
{
    pushButton1->hide();
}

void CwmsguiObjectEditorIf::AddHiddenValue(QString p_qstrValue)
{
    m_pCoeObjectEditor->AddHiddenValue(p_qstrValue);
}

void CwmsguiObjectEditorIf::SetCaptionValue(QString p_qstrValue)
{
    m_pCoeObjectEditor->SetCaptionValue(p_qstrValue);
}

void CwmsguiObjectEditorIf::AddReadOnlyValue(QString p_qstrValue)
{
    m_pCoeObjectEditor->AddReadOnlyValue(p_qstrValue);
}

void CwmsguiObjectEditorIf::AddObjectRefData(QString p_qstrValue,
                                             QString p_qstrObjectList,
                                             QString p_qstrDisplayValue)
{
    m_pCoeObjectEditor->AddObjectRefData(p_qstrValue, p_qstrObjectList, p_qstrDisplayValue);
}

void CwmsguiObjectEditorIf::AddObjectRefData(QString p_qstrValue,
                                             QString p_qstrWql)
{
    m_pCoeObjectEditor->AddObjectRefData(p_qstrValue, p_qstrWql);
}

void CwmsguiObjectEditorIf::SetDisplayType(QString p_qstrValue,
                                           EdmStringDisplayType p_eOeDisplayType)
{
    m_pCoeObjectEditor->SetDisplayType(p_qstrValue, p_eOeDisplayType);
} 

void CwmsguiObjectEditorIf::SetFormConfiguration(CdmObject* p_pObject)
{
    m_pCoeObjectEditor->SetFormConfiguration(p_pObject);
}

void CwmsguiObjectEditorIf::SetObjectEventMode(QString qstr_EventMode)
{
    m_qstrObjectEventMode = qstr_EventMode;
}

QString CwmsguiObjectEditorIf::GetObjectEventMode() const
{
    return m_qstrObjectEventMode;
}

void CwmsguiObjectEditorIf::AddProxy(QString p_qstrKeyname, CdmQueryModel *p_pCwmsProxy)
{
    m_pCoeObjectEditor->AddProxy(p_qstrKeyname, p_pCwmsProxy);
}
