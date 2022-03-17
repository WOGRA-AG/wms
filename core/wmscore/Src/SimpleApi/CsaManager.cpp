// System and QT Includes
#include <QList>

// own Includes
#include "CdmDataProvider.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CsaScheme.h"
#include "CsaFactory.h"
#include "CsaManager.h"

CsaManager::CsaManager(CdmDataProvider *p_pManager)
: m_rpManager(p_pManager)
{
    setElement(m_rpManager);
}


CsaManager::~CsaManager()
{
}


int CsaManager::getSessionId()
{
    return m_rpManager->GetSessionId();
}


QObject *CsaManager::getCurrentUser()
{
    CumUser* pUser = const_cast<CumUser*> (m_rpManager->GetUser());
    return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pUser);
}


QString CsaManager::getApplicationVersion()
{
    return m_rpManager->GetSystemApplicationVersion();
}


QString CsaManager::getWmsBuild()
{
    return m_rpManager->GetBuild();
}

QString CsaManager::getUri() const
{
   return m_rpManager->GetUri();
}

QString CsaManager::getWmsVersion()
{
    return m_rpManager->GetWmsVersion();
}

QObject* CsaManager::getUserByLogin(QString pLoginName)
{
    QObject* qUser = nullptr;
    CumUserManager* pManager = getInternals()->GetUserManager();
    if (CHKPTR(pManager))
    {
        CumUser* cumUser = pManager->FindUserByLogin(pLoginName);
        if (CHKPTR(cumUser))
        {
            qUser = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(cumUser);
        }
    }
    return qUser;
}

QObject* CsaManager::getUsergroupByName(QString pGroupName)
{
    QObject* qUserGroup = nullptr;
    CumUserManager* pManager = getInternals()->GetUserManager();
    if (CHKPTR(pManager))
    {
        CumUserGroup* cumUserGroup = pManager->FindUserGroupByName(pGroupName);
        if (CHKPTR(cumUserGroup))
        {
            qUserGroup = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(cumUserGroup);
        }
    }
    return qUserGroup;
}

CdmDataProvider *CsaManager::getInternals()
{
    return m_rpManager;
}

QVariant CsaManager::getDetailedVariant()
{
    QVariantMap qvm;
    return qvm;
}



