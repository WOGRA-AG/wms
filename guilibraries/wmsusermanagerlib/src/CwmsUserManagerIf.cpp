/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsUserManagerIf.cpp
 ** Started Implementation: 22.01.2005
 ** Description:
 **
 ** implements the usermanager
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QLayout> 
#include <QInputDialog>
#include <QVBoxLayout>
#include <QCloseEvent>

// WMS Includes
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CumUser.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsUserIf.h"
#include "CwmsNewUserIf.h"
#include "CwmsGroupIf.h"
#include "CwmsUserManagerIf.h"

CwmsUserManagerIf::CwmsUserManagerIf(QWidget* parent)
    : QMainWindow(parent),
      m_rpCumUserManager(nullptr),
      m_pqwEditor(nullptr)
{
    setupUi(this);
    m_pqvbLayout = new QVBoxLayout(m_pqframeEditor);
    m_pqframeEditor->setLayout(m_pqvbLayout);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(pCdmManager)
    {
        m_rpCumUserManager = pCdmManager->GetUserManager();
    }
}

CwmsUserManagerIf::CwmsUserManagerIf(CumUserManager* p_pCumUserManager, QWidget* parent)
    : QMainWindow(parent),
      m_rpCumUserManager(nullptr),
      m_pqwEditor(nullptr)
{
    setupUi(this);
    m_pqvbLayout = new QVBoxLayout(m_pqframeEditor);
    m_pqframeEditor->setLayout(m_pqvbLayout);

    if(p_pCumUserManager)
    {
        m_rpCumUserManager = p_pCumUserManager;
    }
}

CwmsUserManagerIf::~CwmsUserManagerIf()
{
    ClearUsers();
}

void CwmsUserManagerIf::ClearGroupList()
{
    m_qvlUserGroups.clear();
    m_pqlvGroups->clear();
}

void CwmsUserManagerIf::UserGroupChangedSlot()
{
    QTreeWidgetItem* pItem = GetSelectedItem(m_pqlvGroups);

    if(CHKPTR(pItem))
    {
        CumUserGroup* pCumUserGroup = FindUserGroupById(pItem->data(0, Qt::UserRole).toInt());

        if(CHKPTR(pCumUserGroup))
        {
            DELPTR(m_pqwEditor);
            m_pqwEditor = new CwmsGroupIf(pCumUserGroup, m_pqframeEditor);
            m_pqvbLayout->addWidget(m_pqwEditor);
            m_pqwEditor->show();
        }
    }
}

CumUserGroup* CwmsUserManagerIf::FindUserGroupById(int p_iId)
{
    CumUserGroup* pCumGroup = nullptr;

    if(CHKPTR(m_rpCumUserManager))
    {
        pCumGroup = m_rpCumUserManager->FindUserGroupById(p_iId);
    }

    return pCumGroup;
}

CumUser* CwmsUserManagerIf::FindUserById(int p_iId)
{
    CumUser* pCumUser = nullptr;

    if(CHKPTR(m_rpCumUserManager))
    {
        pCumUser = m_rpCumUserManager->FindUserById(p_iId);
    }

    return pCumUser;
}

void CwmsUserManagerIf::ClearUserList()
{
    m_pqlvUsers->clear();
    m_qvlUsers.clear();
}

void CwmsUserManagerIf::UserChangedSlot()
{
    QTreeWidgetItem* pItem = GetSelectedItem(m_pqlvUsers);

    if(pItem)
    {
        CumUser* pCumUser = FindUserById(pItem->data(0, Qt::UserRole).toInt());

        if(CHKPTR(pCumUser))
        {
            DELPTR(m_pqwEditor);
            m_pqwEditor = new CwmsUserIf(pCumUser, m_pqframeEditor);
            m_pqwEditor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            m_pqvbLayout->addWidget(m_pqwEditor);
            m_pqwEditor->show();
        }
    }
}

void CwmsUserManagerIf::AboutSlot() const
{
    // todo
}

void CwmsUserManagerIf::DeleteGroupSlot()
{
    if(CHKPTR(m_rpCumUserManager))
    {
        QTreeWidgetItem* pItem = GetSelectedItem(m_pqlvGroups);

        if(CHKPTR(pItem))
        {
            CumUserGroup* pCumUserGroup = FindUserGroupById(pItem->data(0, Qt::UserRole).toInt());

            if(CHKPTR(pCumUserGroup))
            {
                if(CdmMessageManager::Ask(tr("Gruppe wirklich löschen?"), tr("Die Gruppe und ihre Verwendung wird unwiderruflich gelöscht. Wollen Sie das wirklich?")))
                {
                    m_rpCumUserManager->DeleteUserGroup(pCumUserGroup->GetId());
                    DELPTR(pItem);
                }
            }
        }
    }
}

void CwmsUserManagerIf::DeleteUserSlot()
{
    if(CHKPTR(m_rpCumUserManager))
    {
        QTreeWidgetItem* pItem = GetSelectedItem(m_pqlvUsers);

        if(CHKPTR(pItem))
        {
            CumUser* pCumUser = FindUserById(pItem->data(0, Qt::UserRole).toInt());
            if(CHKPTR(pCumUser))
            {
                if (pCumUser->GetId() != m_rpCumUserManager->GetCurrentUserId())
                {
                    if(CdmMessageManager::Ask(tr("User wirklich löschen?"), tr("Der User und seine Verwendung sowie seine historischen Daten werden unwiderruflich gelöscht. Wollen Sie das wirklich?")))
                    {
                        m_rpCumUserManager->DeleteUser(pCumUser->GetLogin());
                        DELPTR(pItem);
                    }
                }
                else
                {
                    CdmMessageManager::critical(tr("Löschen nicht erlaubt"),tr("Man darf sich nicht selbst löschen!"));
                }
            }
        }
    }
}

void CwmsUserManagerIf::ExitSlot()
{
    close();
}

void CwmsUserManagerIf::closeEvent(QCloseEvent* p_pqCloseEvent)
{
    QWidget::closeEvent(p_pqCloseEvent);
}

void CwmsUserManagerIf::NewGroupSlot()
{
    QString qstrGroupName = QInputDialog::getText(this,
                                                  tr("Neue Gruppe"),
                                                  tr("Bitte geben Sie einen Namen für die neue Gruppe ein."),
                                                  QLineEdit::Normal);

    if(!qstrGroupName.isEmpty())
    {
        if(CHKPTR(m_rpCumUserManager))
        {
            m_rpCumUserManager->CreateUserGroup(qstrGroupName);
            m_pqTfSearchforUserGroup->setText(qstrGroupName);
            SearchForUserGroupSlot();
        }
    }
}

void CwmsUserManagerIf::NewUserSlot()
{
    QString qstrLogin = CwmsNewUserIf::CreateNewUser(this, m_rpCumUserManager);

    if (!qstrLogin.isEmpty())
    {
        m_pqTfSearchforUser->setText(qstrLogin);
        SearchForUserSlot();
    }
}

void CwmsUserManagerIf::RenameGroupSlot()
{
    if(CHKPTR(m_rpCumUserManager))
    {
        QTreeWidgetItem* pItem = GetSelectedItem(m_pqlvGroups);

        if(pItem)
        {
            CumUserGroup* pCumGroup = FindUserGroupById(pItem->data(0, Qt::UserRole).toInt());

            if(pCumGroup)
            {
                QString qstrGroupName = QInputDialog::getText(this,
                                                              tr("Gruppe umbenennen"),
                                                              tr("Bitte geben Sie den neuen Namen für die Gruppe ein."),
                                                              QLineEdit::Normal,
                                                              pCumGroup->GetGroupName());

                if(!qstrGroupName.isEmpty())
                {
                    if(CHKPTR(m_rpCumUserManager))
                    {
                        m_rpCumUserManager->RenameUserGroup(pCumGroup->GetId(), qstrGroupName);
                        pItem->setText(1, qstrGroupName);
                    }
                }
            }
        }
    }
}

void CwmsUserManagerIf::UpdateGroupListSlot()
{
    SearchForUserGroupSlot();
}

void CwmsUserManagerIf::UpdateUserListSlot()
{
    SearchForUserSlot();
}

QTreeWidgetItem* CwmsUserManagerIf::GetSelectedItem(QTreeWidget* p_pWidget)
{
    QTreeWidgetItem* pItem = nullptr;

    if (p_pWidget)
    {
        QList<QTreeWidgetItem*> qlItems = p_pWidget->selectedItems();

        if (qlItems.count() > 0)
        {
            pItem = qlItems[0];
        }
    }

    return pItem;
}

void CwmsUserManagerIf::SearchForUserSlot()
{
    QString qstrUserSearchTf = m_pqTfSearchforUser->text();
    ClearUsers();
    m_qlUsers = FindUserByWildCard(qstrUserSearchTf);
    getSearchedUsersToList();
    ClearGroupList();
}

void CwmsUserManagerIf::ClearUsers()
{
    QLinkedList<CumUser*>::iterator qlIt = m_qlUsers.begin();
    QLinkedList<CumUser*>::iterator qlItEnd = m_qlUsers.end();

    for(; qlIt != qlItEnd; ++qlIt)
    {
        DELPTR(*qlIt);
    }
}

QLinkedList<CumUser*> CwmsUserManagerIf::FindUserByWildCard(QString qstrSearchstring)
{
    QLinkedList<CumUser*> qlUsers;

    if(CHKPTR(m_rpCumUserManager))
    {
        qlUsers = m_rpCumUserManager->FindUsersUnmanaged(qstrSearchstring);
    }
    return qlUsers;
}

void CwmsUserManagerIf::getSearchedUsersToList()
{
    ClearUserList();

    QLinkedList<CumUser*>::iterator qlIt = m_qlUsers.begin();
    QLinkedList<CumUser*>::iterator qlItEnd = m_qlUsers.end();

    for(; qlIt != qlItEnd; ++qlIt)
    {
        CumUser* pCumUser = (*qlIt);

        if(pCumUser)
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvUsers);
            pItem->setText(0, QString::number(pCumUser->GetId()));
            pItem->setData(0, Qt::UserRole, (int)pCumUser->GetId());
            pItem->setText(1, pCumUser->GetFirstName());
            pItem->setText(2, pCumUser->GetLastName());
            pItem->setText(3, pCumUser->GetLogin());
        }
    }

    QTreeWidgetItem* pqfirst = m_pqlvUsers->topLevelItem(0);

    if(pqfirst)
    {
        pqfirst->setSelected(true);
        UserChangedSlot();
    }
}

void CwmsUserManagerIf::SearchForUserGroupSlot()
{
    QString qstrUsergroupSearchTf = m_pqTfSearchforUserGroup->text();
    m_qlUsergroups = FindUserGroupByWildCard(qstrUsergroupSearchTf);
    getSearchedUserGroupToList();
    ClearUserList();
}

QLinkedList<CumUserGroup*> CwmsUserManagerIf::FindUserGroupByWildCard(QString qstrSearch)
{
    QLinkedList<CumUserGroup*> qlUsergroups;

    if(CHKPTR(m_rpCumUserManager))
    {
        qlUsergroups = m_rpCumUserManager->FindUserGroupsByNameUnmanaged(qstrSearch);
    }
    return qlUsergroups;
}

void CwmsUserManagerIf::getSearchedUserGroupToList()
{
    ClearGroupList();

    QLinkedList<CumUserGroup*>::iterator qlIt = m_qlUsergroups.begin();
    QLinkedList<CumUserGroup*>::iterator qlItEnd = m_qlUsergroups.end();

    QTreeWidgetItem* pUserGroupItem = nullptr;
    bool bFirst = true;

    for(; qlIt != qlItEnd; ++qlIt)
    {
        CumUserGroup* pCumUserGroup = (*qlIt);

        if(pCumUserGroup)
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvGroups);
            pItem->setText(0, QString::number(pCumUserGroup->GetId()));
            pItem->setData(0, Qt::UserRole, (int)pCumUserGroup->GetId());
            pItem->setText(1, pCumUserGroup->GetGroupName());

            if (bFirst)
            {
                pUserGroupItem = pItem;
                bFirst = false;
            }

            DELPTR(pCumUserGroup);
        }
    }

    if (pUserGroupItem)
    {
        pUserGroupItem->setSelected(true);
        UserGroupChangedSlot();
    }

    m_qlUsergroups.clear();
}
