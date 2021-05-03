/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 .******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <QList>

#include "wmsdefines.h"

// own Includes
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmModelElement.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CumUser.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:24:20 2005----------*
 * @method  CumUser::CumUser                                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lId                                       //                                   *
 * @comment The construcotr of the user.                                                          *
 *----------------last changed: --------------------------------Sa 20. Aug 11:24:20 2005----------*/
CumUser::CumUser(long p_lId, CumUserManager* p_pUserManager)
   : CumAccessor(p_lId,p_pUserManager),
     m_bAdministrator(false),
     m_bActive(true),
     m_bEncrypted(false),
     m_bSchemeIndependent(false)
{
   // nothing to do
}

CumUser::CumUser(CumUserManager* p_pUserManager)
   : CumAccessor(-1, p_pUserManager),
     m_bAdministrator(false),
     m_bActive(true),
     m_bEncrypted(false),
     m_bSchemeIndependent(false)
{
   // nothing to do
}

/** +-=---------------------------------------------------------Sa 14. Apr 13:50:11 2012----------*
 * @method  CumUser::CumUser                                 // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap p_qValues                            //                                   *
 * @comment The construcotr of the user.                                                          *
 *----------------last changed: --------------------------------Sa 14. Apr 13:50:11 2012----------*/
CumUser::CumUser(QVariantMap p_qValues, CumUserManager* p_pUserManager)
: CumAccessor(p_qValues[WMS_USER_ID].toInt(),p_pUserManager),
  m_bAdministrator(p_qValues[WMS_USER_ADMIN].toBool()),
  m_bActive(p_qValues[WMS_USER_ACTIVE].toBool()),
  m_bEncrypted(false)
{
   SetFirstName(p_qValues[WMS_USER_FIRST_NAME].toString());
   SetLastName(p_qValues[WMS_USER_LAST_NAME].toString());
   SetLogin(p_qValues[WMS_USER_LOGIN].toString());
   SetPassword(p_qValues[WMS_USER_PASSWORD].toString());
   SetEmail(p_qValues[WMS_USER_EMAIL].toString());
   SetEncrypted(p_qValues[WMS_USER_ENCRYPTED].toBool());
   SetSchemeIndependent(p_qValues[WMS_USER_SCHEME_INDEPENDENT].toBool());
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:49:42 2005----------*
 * @method  CumUser::~CumUser                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CumUser                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:49:42 2005----------*/
CumUser::~CumUser(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------So 10. Feb 11:45:10 2013----------*
 * @method  CumUser::GetPassword                             // public, const                     *
 * @return  QString                                          //                                   *
 * @comment returns the Password of this user.                                                    *
 *----------------last changed: --------------------------------So 10. Feb 11:45:10 2013----------*/
QString CumUser::GetPassword() const
{
   return m_qstrPassword;
}


/** +-=---------------------------------------------------------Sa 20. Aug 11:25:16 2005----------*
 * @method  CumUser::SetPassword                             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment This method sets the password of the user.                                            *
 *----------------last changed: --------------------------------Sa 20. Aug 11:25:16 2005----------*/
void CumUser::SetPassword(  QString p_qstrPassword )
{
   m_qstrPassword = p_qstrPassword;
}

/** +-=---------------------------------------------------------So 10. Feb 11:45:18 2013----------*
 * @method  CumUser::GetLogin                                // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment returns the login of this user.                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:45:18 2013----------*/
QString CumUser::GetLogin() const
{
   return m_qstrLogin;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:25:51 2005----------*
 * @method  CumUser::SetLogin                                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment This method sets the login of the user.                                               *
 *----------------last changed: --------------------------------Sa 20. Aug 11:25:51 2005----------*/
void CumUser::SetLogin(  QString p_qstrLogin )
{
   m_qstrLogin = p_qstrLogin;
}

QString CumUser::GetCompleteName()
{
    return GetLastName() + " " + GetFirstName();
}

QString CumUser::GetFirstName() const
{
   return m_qstrFirstName;
}

void CumUser::SetFirstName(  QString p_qstrFirstName )
{
   m_qstrFirstName = p_qstrFirstName;
}


QString CumUser::GetLastName() const
{
    return m_qstrLastName;
}

QString CumUser::GetIdentitiyKey() const
{
    return m_qstrIdentityKey;
}

void CumUser::SetLastName(  QString p_qstrName )
{
   m_qstrLastName = p_qstrName;
}

bool CumUser::IsAdministrator() const
{
   return m_bAdministrator;
}

void CumUser::SetAdministrator(  bool p_bAdministrator )
{
    m_bAdministrator = p_bAdministrator;
}

void CumUser::SetIdentityKey(QString p_qstrIdentityKey)
{
    m_qstrIdentityKey = p_qstrIdentityKey;
}

bool CumUser::IsActive() const
{
   return m_bActive;
}

void CumUser::SetActive(bool p_bActive)
{
   m_bActive = p_bActive;
}

void CumUser::GetUserGroups(QList<CumUserGroup*>& p_qvlUserGroups)
{
   LoadUserGroups();
   p_qvlUserGroups = m_qvlUserGroups;
}

void CumUser::DeleteLocalGroups()
{
    if(!m_qvlUserGroups.isEmpty())
    {
        SYNCHRONIZED
        QList<CumUserGroup*>::iterator qllIt = m_qvlUserGroups.begin();
        QList<CumUserGroup*>::iterator qllItEnd = m_qvlUserGroups.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            DELPTR(*qllIt);
        }

        m_qvlUserGroups.clear();
    }
}

void CumUser::LoadUserGroups(  )
{
   CumUserManager* pCumUserManager = GetUserManager();
   
   if(CHKPTR(pCumUserManager))
   {
       DeleteLocalGroups();
       pCumUserManager->GetUserGroupMemberList(GetId(), m_qvlUserGroups);
   }
}

QString CumUser::GetEmail() const
{
   return m_qstrEmail;
}

void CumUser::SetEmail(QString p_qstrEmail)
{
   m_qstrEmail = p_qstrEmail;
}

QString CumUser::GetDisplayString() const
{
   return GetFirstName() + " " + GetLastName();
}

bool CumUser::Update(  )
{
   bool bRet = false;

   CumUserManager* pCumUserManager = GetUserManager();
   
   if(CHKPTR(pCumUserManager))
   {
      long lSuccess = pCumUserManager->UpdateUser(this);

      if(lSuccess > 0)
      {
         bRet = true;
      }
   }

   return bRet;
}

bool CumUser::IsUser() const
{
   return true;
}

QVariant CumUser::GetVariant() const
{
   QVariantMap qMap;

   qMap.insert(WMS_USER_ID, (int)GetId());
   qMap.insert(WMS_USER_LOGIN, GetLogin());
   qMap.insert(WMS_USER_FIRST_NAME, GetFirstName());
   qMap.insert(WMS_USER_LAST_NAME, GetLastName());
   qMap.insert(WMS_USER_EMAIL, GetEmail());
   qMap.insert(WMS_USER_ADMIN, IsAdministrator());
   qMap.insert(WMS_USER_ACTIVE, IsActive());
   qMap.insert(WMS_URI, GetUri());
   qMap.insert(WMS_USER_ENCRYPTED, IsEncrypted());
   qMap.insert(WMS_TYPE, "User");
   qMap.insert(WMS_USER_SCHEME_INDEPENDENT, IsSchemeIndependent());

   (const_cast<CumUser*>(this))->LoadUserGroups();
   QVariantMap qvmGroups;
   QList<CumUserGroup*>::const_iterator qllIt = m_qvlUserGroups.begin();
   QList<CumUserGroup*>::const_iterator qllItEnd = m_qvlUserGroups.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
       qvmGroups.insert(QString::number((*qllIt)->GetId()), (*qllIt)->GetUri());
   }

   qMap.insert(WMS_GROUPS, qvmGroups);
   return qMap;
}

/** +-=---------------------------------------------------------So 10. Feb 11:47:35 2013----------*
 * @method  CumUser::GetUri                                  // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:47:35 2013----------*/
QString CumUser::GetUri() const
{
   QString qstrUri;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      qstrUri = CreateUri("user", GetLogin());
   }

   return qstrUri;
}

QString CumUser::GetUriInternal() const
{
    QString qstrUri;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
       qstrUri = CdmLocatedElement::CreateUriPath(WMS_URI_USER, GetLogin(), "", "");
    }

    return qstrUri;
}


bool CumUser::IsEncrypted() const
{
    return m_bEncrypted;
}

void CumUser::SetEncrypted(bool p_bEncrypted)
{
    m_bEncrypted = p_bEncrypted;
}

QString CumUser::GetBaseAuth() const
{
    return GetLogin() + ":" + GetPassword();
}

bool CumUser::IsSchemeIndependent() const
{
    return m_bSchemeIndependent;
}

void CumUser::SetSchemeIndependent(bool p_bSchemeIndependent)
{
    m_bSchemeIndependent = p_bSchemeIndependent;
}
