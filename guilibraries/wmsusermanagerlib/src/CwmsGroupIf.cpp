/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsGroupIf.cpp
 ** Started Implementation: 2005/01/26
 ** Description:
 **
 ** IMplements the form for group management
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// WMS Includes
#include "CumUserGroup.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"

// own Includes
#include "CwmsUserChoiceIf.h"
#include "CwmsUserManagerIf.h"
#include "CwmsGroupIf.h"

CwmsGroupIf::CwmsGroupIf(CumUserGroup* p_pCumUserGroup, QWidget* p_pqwParent)
   : QWidget(p_pqwParent),
     m_rpCumUserGroup(p_pCumUserGroup)
{
    BODY_TRY
    setupUi(this);
    FillDialog();
    BODY_CATCH
}

CwmsGroupIf::~CwmsGroupIf(  )
{
    BODY_TRY
    ClearUserList();
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 26. Jan 19:21:06 2005----------*
 * @method  CwmsGroupIf::ClearUserList                       // private                           *
 * @return  void                                             //                                   *
 * @comment This method clears the user list.                                                     *
 *----------------last changed: --------------------------------Mi 26. Jan 19:21:06 2005----------*/
void CwmsGroupIf::ClearUserList(  )
{
    BODY_TRY
    for (CumUser* pCumUser: m_qvlUsers)
    {
        if (pCumUser)
        {
            delete pCumUser;
        }
    }
    m_qvlUsers.clear();
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 26. Jan 19:13:04 2005----------*
 * @method  CwmsGroupIf::FillDialog                          // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog.                                                         *
 *----------------last changed: --------------------------------Mi 26. Jan 19:13:04 2005----------*/
void CwmsGroupIf::FillDialog(  )
{
    BODY_TRY
    if (CHKPTR(m_rpCumUserGroup))
    {
        m_pqleGroupId->setText(QString::number(m_rpCumUserGroup->GetId()));
        m_pqleGroupName->setText(m_rpCumUserGroup->GetGroupName());

        ClearUserList();
        m_rpCumUserGroup->GetUserListNewPointers(m_qvlUsers);
        FillUserList();
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 26. Jan 19:22:13 2005----------*
 * @method  CwmsGroupIf::FillUserList                        // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the User Listview                                                   *
 *----------------last changed: --------------------------------Mi 26. Jan 19:22:13 2005----------*/
void CwmsGroupIf::FillUserList(  )
{
    BODY_TRY
    m_pqlvGroupMembers->clear();

    for (CumUser* pCumUser: m_qvlUsers)
    {
        if (pCumUser)
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvGroupMembers);
            pItem->setText(0, QString::number(pCumUser->GetId()));
            pItem->setData(0, Qt::UserRole, static_cast<int>(pCumUser->GetId()));
            pItem->setText(1, pCumUser->GetFirstName());
            pItem->setText(2, pCumUser->GetLastName());
            pItem->setText(3, pCumUser->GetLogin());
        }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 26. Jan 19:26:08 2005----------*
 * @method  CwmsGroupIf::AddClickedSlot                      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the Add Button was clicked. It opens a dialog and the user can add a new user to this group.*
 *----------------last changed: --------------------------------Mi 26. Jan 19:26:08 2005----------*/
void CwmsGroupIf::AddClickedSlot(  )
{
    BODY_TRY
    long lUserId = CwmsUserChoiceIf::GetUserSelection(this);

    if (lUserId >= 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager))
        {
            CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

            if (CHKPTR(pCumUserManager))
            {
                if (!m_rpCumUserGroup->HasUser(lUserId))
                {
                    pCumUserManager->AddUserToUserGroup(lUserId, m_rpCumUserGroup->GetId());
                }
                else
                {
                    CdmMessageManager::critical(tr("Benutzer bereits in Gruppe"),
                                                tr("Der Benutzer ist bereits dieser Gruppe zugeordnet."));
                }
            }
        }

        FillDialog();
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 26. Jan 19:26:30 2005----------*
 * @method  CwmsGroupIf::RemoveClickedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot removes the selected user from group.                                       *
 *----------------last changed: --------------------------------Mi 26. Jan 19:26:30 2005----------*/
void CwmsGroupIf::RemoveClickedSlot(  )
{
    BODY_TRY
    if (CHKPTR(m_rpCumUserGroup))
    {
        QTreeWidgetItem* pItem = CwmsUserManagerIf::GetSelectedItem(m_pqlvGroupMembers);

        if (CHKPTR(pItem))
        {
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pCdmManager))
            {
                CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

                if (CHKPTR(pCumUserManager))
                {
                    int iUserId = pItem->data(0, Qt::UserRole).toInt();

                    if (iUserId >= 0)
                    {
                        pCumUserManager->RemoveUserFromGroup(iUserId, m_rpCumUserGroup->GetId());
                    }
                }
            }

            FillDialog();
        }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 26. Jan 19:26:53 2005----------*
 * @method  CwmsGroupIf::UpdateClickedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot updates all changes on this group.                                          *
 *----------------last changed: --------------------------------Mi 26. Jan 19:26:53 2005----------*/
void CwmsGroupIf::UpdateClickedSlot(  )
{
    BODY_TRY
    if (CHKPTR(m_rpCumUserGroup))
    {
        if (m_rpCumUserGroup->GetGroupName() != m_pqleGroupName->text())
        {
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pCdmManager))
            {
                CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

                if (CHKPTR(pCumUserManager))
                {
                    long lSuccess = pCumUserManager->RenameUserGroup(m_rpCumUserGroup->GetId(), m_pqleGroupName->text());

                    if (lSuccess > 0)
                    {
                        m_rpCumUserGroup->SetGroupName(m_pqleGroupName->text());
                    }
                }
            }
        }

        FillDialog();
    }
    BODY_CATCH
}
