/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <QList>

#include "wmsdefines.h"


// own Includes
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmModelElement.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"


CumUserGroup::CumUserGroup(qint64 p_lId, CumUserManager* p_pUserManager)
   : CumAccessor(p_lId, p_pUserManager)
{
}

CumUserGroup::CumUserGroup(qint64 p_lId, QString p_qstrGroupName, CumUserManager* p_pUserManager)
   : CumAccessor(p_lId, p_pUserManager),
   m_qstrGroupName(p_qstrGroupName)
{
   // nothing to do :-)
}

CumUserGroup::CumUserGroup(QVariantMap& p_qValues, CumUserManager* p_pUserManager)
   : CumAccessor(p_qValues["Id"].toInt(), p_pUserManager)
{
   SetGroupName(p_qValues["GroupName"].toString());
}


CumUserGroup::~CumUserGroup(  )
{
   // nothing to do :-)
}

void CumUserGroup::SetGroupName(  QString p_qstrGroupName )
{
   m_qstrGroupName = p_qstrGroupName;
}

QString CumUserGroup::GetGroupName() const
{
   return m_qstrGroupName;
}

void CumUserGroup::GetUserListNewPointers(QList<CumUser*>& p_rllUsers) const
{
    p_rllUsers.clear();
    CumUserManager* pCumUserManager = GetUserManager();

    if (CHKPTR(pCumUserManager))
    {
        pCumUserManager->GetListOfUsersInList(GetId(), p_rllUsers);
    }
}

bool CumUserGroup::HasUser(qint64 p_lUserId) const
{
    bool bRet = false;

    QList<CumUser*> qllGroupUsers;
    GetUserListNewPointers(qllGroupUsers);

    QList<CumUser*>::iterator qllIt = qllGroupUsers.begin();
    QList<CumUser*>::iterator qllItEnd = qllGroupUsers.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUser* pUser = *qllIt;

        if (CHKPTR(pUser) && pUser->GetId() == p_lUserId)
        {
            bRet = true;
            DELPTR(pUser)
            break;
        }
        else
        {
            DELPTR(pUser)
        }
    }

    return bRet;
}

void CumUserGroup::Update(  )
{
   CumUserManager* pCumUserManager = GetUserManager();

   if(CHKPTR(pCumUserManager))
   {
      pCumUserManager->RenameUserGroup(GetId(), m_qstrGroupName);
   }
}

bool CumUserGroup::IsGroup() const
{

   return true;
}

bool CumUserGroup::IsUserGroup() const
{
   return true;
}

QString CumUserGroup::GetUri() const
{
   QString qstrUri;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      qstrUri = CreateUri(WMS_URI_USERGROUP, GetGroupName());
   }
   
   return qstrUri;
}

QString CumUserGroup::GetUriInternal() const
{
    QString qstrUri;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
       qstrUri = CreateUriPath(WMS_URI_USERGROUP, GetGroupName(), "", "");
    }

    return qstrUri;
}

QVariant CumUserGroup::GetVariant() const
{
   QVariantMap qMap;

   qMap.insert(WMS_ID, GetId());
   qMap.insert(WMS_NAME, GetGroupName());
   qMap.insert(WMS_URI, GetUri());
   qMap.insert(WMS_TYPE, "Usergroup");

   QList<CumUser*> qllUsers;
   GetUserListNewPointers(qllUsers);

   QVariantList qvlUsers;

   QList<CumUser*>::iterator qllIt = qllUsers.begin();
   QList<CumUser*>::iterator qllItEnd = qllUsers.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      qvlUsers.append((*qllIt)->GetId());
   }

   qMap.insert("Users", qvlUsers);

   return qMap;
}

QVariant CumUserGroup::GetVariantForDeplyoment() const
{
    QVariantMap qMap;

    qMap.insert("Id", GetId());
    qMap.insert("Name", GetGroupName());
    qMap.insert("Uri", GetUriInternal());
    return qMap;
}

void CumUserGroup::SetVariant(QVariantMap& p_rqvHash)
{
   SetId(p_rqvHash["Id"].toInt());
   SetGroupName(p_rqvHash["Name"].toString());
}
