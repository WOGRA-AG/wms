// System and QT Includes


// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmObject.h"
#include "CdmRights.h"
#include "CdmLogging.h"


// own Includes
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsSearchWindowDlg.h"


CwmsSearchWindowDlg::CwmsSearchWindowDlg(QWidget* p_pqwParent)
   : QDialog(p_pqwParent)
{
   setupUi(this);
}

CwmsSearchWindowDlg::~CwmsSearchWindowDlg()
{
}

void CwmsSearchWindowDlg::AddSearchMember(QString p_qstrSearchMember)
{
   m_pSearchWindow->AddSearchMember(p_qstrSearchMember);
}

void CwmsSearchWindowDlg::AddResultMembers(QString p_qstrMember)
{
    m_pSearchWindow->AddResultMember(p_qstrMember);
}

void CwmsSearchWindowDlg::SetPrintVisibility(bool p_bVisible)
{
    m_pSearchWindow->SetPrintVisibility(p_bVisible);
}

void CwmsSearchWindowDlg::SetExportVisibility(bool p_bVisible)
{
    m_pSearchWindow->SetExportVisibility(p_bVisible);
}

void CwmsSearchWindowDlg::SetImportVisibility(bool p_bVisible)
{
    m_pSearchWindow->SetImportVisibility(p_bVisible);
}

void CwmsSearchWindowDlg::SetDeleteVisibility(bool p_bVisible)
{
    m_pSearchWindow->SetDeleteVisibility(p_bVisible);
}

void CwmsSearchWindowDlg::SetEditVisibility(bool p_bVisible)
{
    m_pSearchWindow->SetEditVisibility(p_bVisible);
}

void CwmsSearchWindowDlg::FillDialog(CdmObjectContainer* p_pContainer)
{
   m_pSearchWindow->FillDialog(p_pContainer);
}

CdmObject* CwmsSearchWindowDlg::FindObject(CdmObjectContainer* p_pContainer, QWidget* parent)
{
    CwmsSearchWindowDlg cSearch(parent);
    cSearch.FillDialog(p_pContainer);

    if (cSearch.exec() == QDialog::Accepted)
    {
        return cSearch.m_pSearchWindow->GetSelectedObject();
    }

    return nullptr;
}

QList<CdmObject*> CwmsSearchWindowDlg::FindObjects(CdmObjectContainer* p_pContainer, QWidget* parent)
{
    QList<CdmObject*> qlResults;
    CwmsSearchWindowDlg cSearch(parent);
    cSearch.FillDialog(p_pContainer);

    if (cSearch.exec() == QDialog::Accepted)
    {
        qlResults = cSearch.m_pSearchWindow->GetSelectedObjects();
    }

    return qlResults;
}
