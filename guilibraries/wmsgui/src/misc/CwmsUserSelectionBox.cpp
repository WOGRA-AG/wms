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


CwmsUserSelectionBox::CwmsUserSelectionBox(QWidget* p_pqwParent)
    : QComboBox(p_pqwParent),
      m_bOnlyActiveUsers(true)
{
    FillComboBox();
}

CwmsUserSelectionBox::~CwmsUserSelectionBox()
{
}

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

void CwmsUserSelectionBox::FillUsersToComboBox(QList<CumUser*> qllUsers)
{
    clear();
    QMap<QString, int> qmUsers;

    for (CumUser* pCumUser: qAsConst(qllUsers))
    {
        if (CHKPTR(pCumUser))
        {
            if (pCumUser->IsActive() || !m_bOnlyActiveUsers)
            {
                QString qstrDisplayString = GetUserAsSelectionString(pCumUser);

                qmUsers.insert(qstrDisplayString, static_cast<int>(pCumUser->GetId()));
            }

            delete pCumUser;
        }

    }

    for (auto qmIt = qmUsers.begin(); qmIt != qmUsers.end(); ++qmIt)
    {
        addItem(qmIt.key(), qmIt.value());
    }
}

void CwmsUserSelectionBox::FillComboBox()
{
BODY_TRY
    QList<CumUser*> qllUsers;
    GetUserList(qllUsers);
    FillUsersToComboBox(qllUsers);
BODY_CATCH
}

void CwmsUserSelectionBox::FillComboBoxWithGivenUserGroup(CumUserGroup *pUserGroup)
{
BODY_TRY
    if (CHKPTR(pUserGroup))
    {
        QList<CumUser*> qllUsers;
        pUserGroup->GetUserListNewPointers(qllUsers);
        FillUsersToComboBox(qllUsers);
    }
BODY_CATCH
}

QString CwmsUserSelectionBox::GetUserAsSelectionString(CumUser* p_pUser)
{
    QString qstrDisplayString;

    if (CHKPTR(p_pUser))
    {
        qstrDisplayString =
                p_pUser->GetFirstName() %
                QStringLiteral(" ")      %
                p_pUser->GetLastName()  %
                QStringLiteral(" (")     %
                p_pUser->GetLogin()     %
                QStringLiteral(")");
    }

    return qstrDisplayString;
}


void CwmsUserSelectionBox::SetOnlyActiveUser(bool p_bOnlyActive)
{
    m_bOnlyActiveUsers = p_bOnlyActive;
}

bool CwmsUserSelectionBox::GetOnlyActiveUser()
{
    return m_bOnlyActiveUsers;
}

void CwmsUserSelectionBox::Refresh()
{
    FillComboBox();
}

void CwmsUserSelectionBox::SetCurrentUser(const CumUser* p_CumUser)
{
    if (p_CumUser)
    {
        SetCurrentUser(p_CumUser->GetId());
    }
}

void CwmsUserSelectionBox::SetCurrentUser(int p_iUserId)
{
    int iIndex = findData(p_iUserId);
    setCurrentIndex(iIndex);
}

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

int CwmsUserSelectionBox::GetSelectedUserId()
{
    return itemData(currentIndex()).toInt();
}
