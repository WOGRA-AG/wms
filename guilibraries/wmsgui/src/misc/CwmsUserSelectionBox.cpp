/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsUserSelectionBox.cpp
 ** Started Implementation: 2009/11/14
 ** Description:
 **
 ** This class implements the selection box for users
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QStringBuilder>

// WMS Manager Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"

// Own Includes
#include "CwmsUserSelectionBox.h"


/** +-=---------------------------------------------------------Mo 29. Okt 09:31:30 2012----------*
 * @method  CwmsUserSelectionBox::CwmsUserSelectionBox       // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 09:31:30 2012----------*/
CwmsUserSelectionBox::CwmsUserSelectionBox(QWidget* p_pqwParent)
    : QComboBox(p_pqwParent)
{
    FillComboBox();
}

/** +-=---------------------------------------------------------Sa 14. Nov 11:14:37 2009----------*
 * @method  CwmsUserSelectionBox::~CwmsUserSelectionBox      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsUserSelectionBox                                          *
 *----------------last changed: --------------------------------Sa 14. Nov 11:14:37 2009----------*/
CwmsUserSelectionBox::~CwmsUserSelectionBox()
{
}

/** +-=---------------------------------------------------------Sa 14. Nov 11:29:57 2009----------*
 * @method  CwmsUserSelectionBox::GetUserList                // private                           *
 * @return  void                                             //                                   *
 * @param   QList<CumUser*>& p_rqllUsers               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Nov 11:29:57 2009----------*/
void CwmsUserSelectionBox::GetUserList(QList<CumUser*>& p_rqllUsers)
{
    // TODO SB Document transfer of ownership
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

        if (CHKPTR(pCumUserManager))
        {
            pCumUserManager->GetUserListUnmanaged(p_rqllUsers);
        }
    }
}

/** +-=---------------------------------------------------------Sa 14. Nov 11:14:55 2009----------*
 * @method  CwmsUserSelectionBox::FillComboBox               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Nov 11:14:55 2009----------*/
void CwmsUserSelectionBox::FillComboBox()
{
    BODY_TRY
    QList<CumUser*> qllUsers;
    GetUserList(qllUsers);

    QMap<QString, int> qmUsers;

    for (CumUser* pCumUser: qllUsers)
    {
        if (CHKPTR(pCumUser))
        {
            if (pCumUser->IsActive())
            {
                    QString qstrDisplayString =
                        pCumUser->GetFirstName() %
                        QStringLiteral(" ")      %
                        pCumUser->GetLastName()  %
                        QStringLiteral(" (")     %
                        pCumUser->GetLogin()     %
                        QStringLiteral(")");

                qmUsers.insert(qstrDisplayString, static_cast<int>(pCumUser->GetId()));
            }

            delete pCumUser;
        }

    }

    for (auto qmIt = qmUsers.begin(); qmIt != qmUsers.end(); ++qmIt)
    {
        addItem(qmIt.key(), qmIt.value());
    }
    BODY_CATCH
}

void CwmsUserSelectionBox::FillComboBoxWithGivenUserGroup(CumUserGroup *pUserGroup)
{
    BODY_TRY
    if (CHKPTR(pUserGroup))
    {
        clear();

        QList<CumUser*> qllUsers;
        pUserGroup->GetUserListNewPointers(qllUsers);

        for (CumUser* pCumUser : qllUsers)
        {
            if (CHKPTR(pCumUser))
            {
                if (pCumUser->IsActive())
                {
                    QString qstrDisplayString =
                            pCumUser->GetFirstName() %
                            QStringLiteral(" ")      %
                            pCumUser->GetLastName()  %
                            QStringLiteral(" (")     %
                            pCumUser->GetLogin()     %
                            QStringLiteral(")");

                    addItem(qstrDisplayString, static_cast<int>(pCumUser->GetId()));
                }

                delete pCumUser;
            }
        }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Di 12. Mrz 12:59:50 2013----------*
 * @method  CwmsUserSelectionBox::SetCurrentUser             // public                            *
 * @return  void                                             //                                   *
 * @param   const CumUser* p_CumUser                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 12. Mrz 12:59:50 2013----------*/
void CwmsUserSelectionBox::SetCurrentUser(const CumUser* p_CumUser)
{
    if (p_CumUser)
    {
        SetCurrentUser(p_CumUser->GetId());
    }
}

/** +-=---------------------------------------------------------Sa 14. Nov 11:15:23 2009----------*
 * @method  CwmsUserSelectionBox::SetCurrentUser             // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iUserId                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Nov 11:15:23 2009----------*/
void CwmsUserSelectionBox::SetCurrentUser(int p_iUserId)
{
    int iIndex = findData(p_iUserId);
    setCurrentIndex(iIndex);
}

/** +-=---------------------------------------------------------Sa 14. Nov 11:16:38 2009----------*
 * @method  CwmsUserSelectionBox::GetSelectedUser            // public                            *
 * @return  CumUser*                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Nov 11:16:38 2009----------*/
CumUser* CwmsUserSelectionBox::GetSelectedUser()
{
    CumUser* pCumUser = nullptr;

    int iUserId = GetSelectedUserId();

    if (iUserId > 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager))
        {
            CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

            if (CHKPTR(pCumUserManager))
            {
                pCumUser = pCumUserManager->FindUserById(iUserId);
            }
        }
    }

    return pCumUser;
}

/** +-=---------------------------------------------------------Sa 14. Nov 11:16:49 2009----------*
 * @method  CwmsUserSelectionBox::GetSelectedUserId          // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Nov 11:16:49 2009----------*/
int CwmsUserSelectionBox::GetSelectedUserId()
{
    return itemData(currentIndex()).toInt();
}
