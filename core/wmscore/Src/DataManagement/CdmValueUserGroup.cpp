// System and QT Includes
#include <QVariantMap>

// Own Includes
#include "wmsdefines.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmValueUserGroup.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CdmLogging.h"


CdmValueUserGroup::CdmValueUserGroup(qint64 p_lDatabaseId,
                                    qint64 p_lId,
                                     QString p_qstrKeyname,
                                     CdmObject* p_pCdmObject)
   : CdmValueInt(eDmValueUserGroup, p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObject)
{

   // nothing to do
}



CdmValueUserGroup::CdmValueUserGroup(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueInt(p_rqvHash, p_pCdmObject)
{

}

CdmValueUserGroup::~CdmValueUserGroup()
{
}

CumUserGroup* CdmValueUserGroup::GetUserGroup()
{
   CumUserGroup* pCumUserGroup = nullptr;
   int iId = GetValue();

   if (iId > 0)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

         if (CHKPTR(pCumUserManager))
         {
            pCumUserGroup = pCumUserManager->FindUserGroupById(iId);
         }
      }
   }

   return pCumUserGroup;
}

void CdmValueUserGroup::SetUserGroup(CumUserGroup* p_pCumUserGroup)
{
   int iGroupId = 0;

   if (p_pCumUserGroup)
   {
      iGroupId = p_pCumUserGroup->GetId();
   }
   
   SetValue(iGroupId);
}

QString CdmValueUserGroup::GetDisplayString() const
{
   QString qstrRet;
   CumUserGroup* pCumUserGroup = (const_cast<CdmValueUserGroup*>(this))->GetUserGroup();

   if (pCumUserGroup)
   {
      qstrRet = pCumUserGroup->GetGroupName();
   }
   else
   {
      qstrRet = tr("-");
   }

   return qstrRet;
}

QVariant CdmValueUserGroup::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   qmVariant.insert("Name", GetDisplayString());
   return qmVariant;
}

QVariant CdmValueUserGroup::GetValueVariant() const
{
    QVariant qvUser("");
    int iUserId = GetValue();

    CumUserManager* pUserManager = GetDataProvider()->GetUserManager();

    if (CHKPTR(pUserManager))
    {
        auto pGroup = pUserManager->FindUserGroupById(iUserId);

        if (pGroup)
        {
            qvUser = pGroup->GetUri();
        }
    }

   return qvUser;
}

void CdmValueUserGroup::SetValueVariant(QVariant& p_rqVariant)
{
    QString qstrUri = p_rqVariant.toString();
    auto pScheme = GetDataProvider();

    if (CHKPTR(pScheme))
    {
        auto pElement = pScheme->GetUriObject(qstrUri);

        if (CHKPTR(pElement))
        {
            if (pElement->IsUserGroup())
            {
                SetUserGroup(dynamic_cast<CumUserGroup*>(pElement));
            }
            else
            {
                ERR("Uri is not a usergroup" + qstrUri);
            }
        }
        else
        {
            ERR("Uri Element not found " + qstrUri);
        }
    }
}

void CdmValueUserGroup::Restore(QString p_qstrValue)
{
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        auto pUriObject = pDataProvider->GetUriObject(p_qstrValue);

        if (pUriObject)
        {
            if (pUriObject->IsUserGroup())
            {
                auto pObject = dynamic_cast<CumUserGroup*>(pUriObject);

                if (CHKPTR(pObject))
                {
                    SetValue(pObject->GetId());
                }
            }
        }
        else
        {
            ERR("UserGroup to be restored in this value not found.");
        }
    }
}
