/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueUser.cpp
 ** Started Implementation: 2009/04/07
 ** Description:
 ** 
 ** Implements the user value
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QVariantMap>

// Own Includes
#include "wmsdefines.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmValueUser.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CdmLogging.h"


/** +-=---------------------------------------------------------Di 7. Apr 22:07:25 2009-----------*
 * @method  CdmValueUser::CdmValueUser                       // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The Userconstructor                                                                   *
 *----------------last changed: --------------------------------Di 7. Apr 22:07:25 2009-----------*/
CdmValueUser::CdmValueUser(long p_lDatabaseId,
                           long p_lId,
                           QString p_qstrKeyname,
                           CdmObject* p_pCdmObject)
: CdmValueInt(eDmValueUser, p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObject)
{
   // nothing to do
}


/** +-=---------------------------------------------------------Fr 10. Apr 19:29:58 2009----------*
 * @method  CdmValueUser::CdmValueUser                       // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Source                        *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The integer constructor.                                                              *
 *----------------last changed: --------------------------------Fr 10. Apr 19:29:58 2009----------*/
CdmValueUser::CdmValueUser(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
: CdmValueInt(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 14:13:36 2012----------*
 * @method  CdmValueUser::CdmValueUser                       // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 14:13:36 2012----------*/
CdmValueUser::CdmValueUser(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueInt(p_rqvHash, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Di 7. Apr 22:15:36 2009-----------*
 * @method  CdmValueUser::~CdmValueUser                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueUser                                                  *
 *----------------last changed: --------------------------------Di 7. Apr 22:15:36 2009-----------*/
CdmValueUser::~CdmValueUser()
{
}


/** +-=---------------------------------------------------------Di 20. Nov 12:01:45 2012----------*
 * @method  CdmValueUser::GetUser                            // public, slots                     *
 * @return  CumUser*                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 12:01:45 2012----------*/
CumUser* CdmValueUser::GetUser()
{
   CumUser* pCumUser = nullptr;
   int iId = GetValue();

   if (iId > 0)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

         if (CHKPTR(pCumUserManager))
         {
            pCumUser = pCumUserManager->FindUserById(iId);
         }
      }
   }

   return pCumUser;
}

/** +-=---------------------------------------------------------Di 20. Nov 12:01:52 2012----------*
 * @method  CdmValueUser::SetUser                            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CumUser* p_pCumUser                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 12:01:52 2012----------*/
void CdmValueUser::SetUser(CumUser* p_pCumUser)
{

   int iUserId = 0;

   if (p_pCumUser)
   {
      iUserId = p_pCumUser->GetId();
   }
   
   SetValue(iUserId);
}

/** +-=---------------------------------------------------------So 10. Feb 11:41:46 2013----------*
 * @method  CdmValueUser::GetDisplayString                   // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:41:46 2013----------*/
QString CdmValueUser::GetDisplayString() const
{
   QString qstrRet;
   CumUser* pCumUser = (const_cast<CdmValueUser*>(this))->GetUser();

   if (pCumUser)
   {
      qstrRet = pCumUser->GetFirstName() + " " + pCumUser->GetLastName();
   }
   else
   {
      int iId = GetValue();

      if (iId == -1)
      {
         qstrRet = "Demo User";
      }
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------So 10. Feb 11:41:57 2013----------*
 * @method  CdmValueUser::GetLogin                           // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:41:57 2013----------*/
QString CdmValueUser::GetLogin() const
{

   QString qstrRet;
   CumUser* pCumUser = (const_cast<CdmValueUser*>(this))->GetUser();

   if (CHKPTR(pCumUser))
   {
      qstrRet = pCumUser->GetLogin();
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------So 10. Feb 11:42:07 2013----------*
 * @method  CdmValueUser::GetVariant                         // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 11:42:07 2013----------*/
QVariant CdmValueUser::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   qmVariant.insert("Name", GetDisplayString());
   return qmVariant;
}

/** +-=---------------------------------------------------------So 10. Feb 11:42:16 2013----------*
 * @method  CdmValueUser::GetValueVariant                    // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:42:16 2013----------*/
QVariant CdmValueUser::GetValueVariant() const
{
    QVariant qvUser("");
    int iUserId = GetValue();

    CumUserManager* pUserManager = GetDataProvider()->GetUserManager();

    if (CHKPTR(pUserManager))
    {
        auto pUser = pUserManager->FindUserById(iUserId);

        if (pUser)
        {
            qvUser = pUser->GetUri();
        }
    }

   return qvUser;
}

/** +-=---------------------------------------------------------Di 5. Jun 08:45:49 2012-----------*
 * @method  CdmValueUser::SetValueVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 08:45:49 2012-----------*/
void CdmValueUser::SetValueVariant(QVariant& p_rqVariant)
{
    QString qstrUri = p_rqVariant.toString();
    auto pScheme = GetDataProvider();

    if (CHKPTR(pScheme))
    {
        auto pElement = pScheme->GetUriObject(qstrUri);

        if (CHKPTR(pElement))
        {
            if (pElement->IsUser())
            {
                SetUser(dynamic_cast<CumUser*>(pElement));
            }
            else
            {
                ERR("Uri is not a user" + qstrUri);
            }
        }
        else
        {
            ERR("Uri Element not found " + qstrUri);
        }
    }
}
