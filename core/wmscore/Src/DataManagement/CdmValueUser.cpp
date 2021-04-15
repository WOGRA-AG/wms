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

CdmValueUser::CdmValueUser(long p_lDatabaseId,
                           long p_lId,
                           QString p_qstrKeyname,
                           CdmObject* p_pCdmObject)
: CdmValueInt(eDmValueUser, p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObject)
{
   // nothing to do
}

CdmValueUser::CdmValueUser(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueInt(p_rqvHash, p_pCdmObject)
{
}

CdmValueUser::~CdmValueUser()
{
}

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

void CdmValueUser::SetUser(CumUser* p_pCumUser)
{

   int iUserId = 0;

   if (p_pCumUser)
   {
      iUserId = p_pCumUser->GetId();
   }
   
   SetValue(iUserId);
}

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

QVariant CdmValueUser::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   qmVariant.insert("Name", GetDisplayString());
   return qmVariant;
}

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

void CdmValueUser::Restore(QString p_qstrValue)
{
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        auto pUriObject = pDataProvider->GetUriObject(p_qstrValue);

        if (pUriObject)
        {
            if (pUriObject->IsUser())
            {
                auto pObject = dynamic_cast<CumUser*>(pUriObject);

                if (CHKPTR(pObject))
                {
                    SetValue(pObject->GetId());
                }
            }
        }
        else
        {
            ERR("User to be restored in this value not found.");
        }
    }
}
