// System and QT includes


// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CumUserManager.h"
#include "CumUser.h"

// own Includes
#include "CwmsUserManagerIf.h"
#include "CwmsUserChoiceIf.h"



CwmsUserChoiceIf::CwmsUserChoiceIf(QWidget* parent)
    : QDialog(parent)
{
    setupUi(this);
}


CwmsUserChoiceIf::~CwmsUserChoiceIf()
{
}

int CwmsUserChoiceIf::GetSelectedUserId()
{
    int iUserId = -1;
    QTreeWidgetItem* pItem = CwmsUserManagerIf::GetSelectedItem(m_pqlvUsers);

    if(pItem)
    {
        iUserId = pItem->data(0, Qt::UserRole).toInt();
    }

    return iUserId;
}

void CwmsUserChoiceIf::OKClickedSlot()
{
    accept();
}

void CwmsUserChoiceIf::CancelClickedSlot()
{
    reject();
}


qint64 CwmsUserChoiceIf::GetUserSelection(QWidget* parent)
{
    qint64 lUserId = -1;
    CwmsUserChoiceIf* pCwmsUserChoiceIf = new CwmsUserChoiceIf(parent);

    if(pCwmsUserChoiceIf->exec() == QDialog::Accepted)
    {
        lUserId = pCwmsUserChoiceIf->GetSelectedUserId();
    }

    delete pCwmsUserChoiceIf;
    return lUserId;
}

void CwmsUserChoiceIf::SearchUserClickedSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
    QString qstrSearchString = m_pqleInputSearch->text();
    QList<CumUser*> qllUsers = pCumUserManager->FindUsersUnmanaged(qstrSearchString);

    m_pqlvUsers->clear();

    QList<CumUser*>::iterator qvlIt    = qllUsers.begin();
    QList<CumUser*>::iterator qvlItEnd = qllUsers.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        CumUser* pCumUser = (*qvlIt);

        if(pCumUser && (pCumUser->IsActive() == m_pqchbActiveUser->isChecked() || !m_pqchbActiveUser->isChecked()))
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvUsers);
            pItem->setText(0, QString::number(pCumUser->GetId()));
            pItem->setData(0, Qt::UserRole, pCumUser->GetId());
            pItem->setText(1, pCumUser->GetFirstName());
            pItem->setText(2, pCumUser->GetLastName());
            pItem->setText(3, pCumUser->GetLogin());
        }
    }

    qvlIt    = qllUsers.begin();
    qvlItEnd = qllUsers.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        DELPTR(*qvlIt);
    }

    qllUsers.clear();
}
