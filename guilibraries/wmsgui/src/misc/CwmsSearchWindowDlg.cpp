/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsSearchWindow.cpp
 ** Started Implementation: 2012/09/06
 ** Description:
 **
 ** implements the Dlg for generic search
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

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


/** +-=---------------------------------------------------------Di 18. Sep 10:21:33 2012----------*
 * @method  CwmsSearchWindowDlg::CwmsSearchWindowDlg         // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 10:21:33 2012----------*/
CwmsSearchWindowDlg::CwmsSearchWindowDlg(QWidget* p_pqwParent)
   : QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Di 18. Sep 10:21:43 2012----------*
 * @method  CwmsSearchWindowDlg::~CwmsSearchWindowDlg        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsSearchWindow                                              *
 *----------------last changed: --------------------------------Di 18. Sep 10:21:43 2012----------*/
CwmsSearchWindowDlg::~CwmsSearchWindowDlg()
{
}

/** +-=---------------------------------------------------------Di 18. Sep 10:21:53 2012----------*
 * @method  CwmsSearchWindowDlg::AddSearchMember             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSearchMember                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 10:21:53 2012----------*/
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


/** +-=---------------------------------------------------------Di 18. Sep 10:22:52 2012----------*
 * @method  CwmsSearchWindowDlg::FillDialog                  // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 10:22:52 2012----------*/
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
