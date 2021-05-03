// Headder is missing impl started on 25.1.2005



// System and QT Includes
#include <qlineedit.h>
#include <qcheckbox.h>

// WMS Commons
#include "wmsdefines.h"


// own Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmSessionManager.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CwmsUserGroupChoiceIf.h"
#include "CwmsPasswordIf.h"
#include "CwmsUserSchemeSelection.h"
#include "CwmsUserIf.h"


CwmsUserIf::CwmsUserIf(CumUser* p_pCumUser, QWidget* p_pqwParent)
    : QWidget(p_pqwParent),
      m_rpCumUser(p_pCumUser)
{
    setupUi(this);
    FillDialog();
}

CwmsUserIf::~CwmsUserIf(  )
{
}

void CwmsUserIf::FillGroups()
{
    m_rpCumUser->GetUserGroups(m_qvlUserGroups);

    QList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
    QList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        CumUserGroup* pCumUserGroup = (*qvlIt);

        if(pCumUserGroup)
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvGroups);
            pItem->setText(0, QString::number(pCumUserGroup->GetId()));
            pItem->setData(0, Qt::UserRole, (int)pCumUserGroup->GetId());
            pItem->setText(1, pCumUserGroup->GetGroupName());
        }
    }
}

void CwmsUserIf::FillSchemes()
{
    QStringList qstrlSchemes = m_rpCumUser->GetSchemeList();

    for (int pos = 0; pos < qstrlSchemes.count(); ++pos)
    {
        QListWidgetItem* pItem = new QListWidgetItem(m_pqlwSchemes);
        pItem->setText(qstrlSchemes[pos]);
    }
}


void CwmsUserIf::FillDialog()
{
    if(CHKPTR(m_rpCumUser))
    {
        m_pqleUserId->setText(QString::number(m_rpCumUser->GetId()));
        m_pqleLogin->setText(m_rpCumUser->GetLogin());
        m_pqleName->setText(m_rpCumUser->GetLastName());
        m_pqleEmail->setText(m_rpCumUser->GetEmail());
        m_pqleSurname->setText(m_rpCumUser->GetFirstName());
        m_pqchbAdmin->setChecked(m_rpCumUser->IsAdministrator());
        m_pqchbActive->setChecked(m_rpCumUser->IsActive());
        m_pqchbSchemeIndependent->setChecked(m_rpCumUser->IsSchemeIndependent());

        FillGroups();

        CumUserManager* pUserManager = m_rpCumUser->GetUserManager();

        if (CHKPTR(pUserManager) && pUserManager->GetSchemeUri().isEmpty())
        {
            FillSchemes();
        }
        else
        {
            m_pqchbSchemeIndependent->hide();
            DELPTR(m_pqwSchemeAssignment);
        }
    }
}

/** +-=---------------------------------------------------------Di 25. Jan 20:23:17 2005----------*
 * @method  CwmsUserIf::ChangePasswordClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 25. Jan 20:23:17 2005----------*/
void CwmsUserIf::ChangePasswordClickedSlot(  )
{
    if(CwmsPasswordIf::ChangePassword(m_rpCumUser, this))
    {
        CdmMessageManager::information(tr("Passwort wurde geändert"),
                                       tr("Das Passwort wurde erfolgreich geändert."));
    }
    else
    {
        CdmMessageManager::critical(tr("Fehler bei der Passwortänderung"),
                                    tr("Das Passwort konnte nicht geändert werden."));
    }
}

void CwmsUserIf::AddScheme()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        QList<QString> qllSchemes;
        pManager->GetSchemeList(qllSchemes);
        QString qstrScheme = CwmsUserSchemeSelection::SelectScheme(qllSchemes, this);
        m_rpCumUser->AddSchemeUri("/" WMS_SCHEME  "/" + qstrScheme);
        m_rpCumUser->Update();
        QListWidgetItem* pItem = new QListWidgetItem(m_pqlwSchemes);
        pItem->setText(qstrScheme);
    }
}

void CwmsUserIf::RemoveScheme()
{
    QList<QListWidgetItem*> pqlItems = m_pqlwSchemes->selectedItems();

    for (int pos = 0; pos < pqlItems.count(); ++pos)
    {
        QListWidgetItem* pItem = pqlItems[pos];

        if (CHKPTR(pItem))
        {
            QString qstrScheme = pItem->text();
            m_rpCumUser->RemoveSchemeUri(qstrScheme);
            m_rpCumUser->Update();
            DELPTR(pItem);
        }
    }
}

void CwmsUserIf::AddGroup()
{
    long lGroupId = CwmsUserGroupChoiceIf::GetGroupSelection(this);

    if (lGroupId >= 0)
    {
        CumUserManager* pUserManager = m_rpCumUser->GetUserManager();

        if (CHKPTR(pUserManager))
        {
            pUserManager->AddUserToUserGroup(m_rpCumUser->GetId(), lGroupId);
            CumUserGroup* pGroup = pUserManager->FindUserGroupById(lGroupId);

            if (CHKPTR(pGroup))
            {
                QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvGroups);
                pItem->setText(0, QString::number(pGroup->GetId()));
                pItem->setData(0, Qt::UserRole, (int)pGroup->GetId());
                pItem->setText(1, pGroup->GetGroupName());
            }
        }
    }
}

void CwmsUserIf::RemoveGroup()
{
    QList<QTreeWidgetItem*> pqlItems = m_pqlvGroups->selectedItems();

    for (int pos = 0; pos < pqlItems.count(); ++pos)
    {
        QTreeWidgetItem* pItem = pqlItems[pos];

        if (CHKPTR(pItem))
        {
            QString qstrGroup = pItem->text(1);
            CumUserManager* pUserManager = m_rpCumUser->GetUserManager();

            if (CHKPTR(pUserManager))
            {
                pUserManager->RemoveUserFromGroup(m_rpCumUser->GetLogin(), qstrGroup);
                DELPTR(pItem);
            }
        }
    }
}

void CwmsUserIf::UpdateCLickedSlot(  )
{
    if(m_rpCumUser)
    {
        CumUserManager* pUserManager = m_rpCumUser->GetUserManager();

        if (CHKPTR(pUserManager))
        {
            bool bOldIsAdmin = m_rpCumUser->IsAdministrator();
            QString qstrOldLogin = m_rpCumUser->GetLogin();
            QString qstrOldLastName = m_rpCumUser->GetLastName();
            QString qstrOldFirstName = m_rpCumUser->GetFirstName();
            bool bOldIsActive = m_rpCumUser->IsActive();
            QString qstrOldMail = m_rpCumUser->GetEmail();

            m_rpCumUser->SetAdministrator(m_pqchbAdmin->isChecked());
            m_rpCumUser->SetLogin(m_pqleLogin->text());
            m_rpCumUser->SetLastName(m_pqleName->text());
            m_rpCumUser->SetFirstName(m_pqleSurname->text());
            m_rpCumUser->SetActive(m_pqchbActive->isChecked());
            m_rpCumUser->SetEmail(m_pqleEmail->text());

            if (SUCCESSFULL(pUserManager->UpdateUser(m_rpCumUser)))
            {
                CdmMessageManager::information(tr("Benutzer wurde erfolgreich gespeichert"),
                                               tr("Der Benutzer wurde erfolgreich gespeichert."));
            }
            else
            {//reset User and GUI fields
                CdmMessageManager::critical(tr("Benutzer kann nicht gespeichert werden"), tr("Login und E-Mail müssen eindeutig sein."));
                m_pqchbAdmin->setChecked(bOldIsAdmin);
                m_pqleLogin->setText(qstrOldLogin);
                m_pqleName->setText(qstrOldLastName);
                m_pqleSurname->setText(qstrOldFirstName);
                m_pqchbActive->setChecked(bOldIsActive);
                m_pqleEmail->setText(qstrOldMail);

                bOldIsAdmin = false;
                bOldIsActive = false;
                qstrOldFirstName = "";
                qstrOldLastName = "";
                qstrOldLogin = "";
                qstrOldMail = "";
            }
        }
    }
}

