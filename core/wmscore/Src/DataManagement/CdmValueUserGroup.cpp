/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueUserGroup.cpp
 ** Started Implementation: 2009/04/07
 ** Description:
 ** 
 ** Implements the usergroup value
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
#include "CdmValueUserGroup.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CdmLogging.h"


/** +-=---------------------------------------------------------Di 28. Aug 10:29:08 2012----------*
 * @method  CdmValueUserGroup::CdmValueUserGroup             // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The Userconstructor                                                                   *
 *----------------last changed: --------------------------------Di 28. Aug 10:29:08 2012----------*/
CdmValueUserGroup::CdmValueUserGroup(long p_lDatabaseId,
                                     long p_lId,
                                     QString p_qstrKeyname,
                                     CdmObject* p_pCdmObject)
   : CdmValueInt(eDmValueUserGroup, p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObject)
{

   // nothing to do
}


/** +-=---------------------------------------------------------Di 28. Aug 10:30:02 2012----------*
 * @method  CdmValueUserGroup::CdmValueUserGroup             // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Source                        *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The integer constructor.                                                              *
 *----------------last changed: --------------------------------Di 28. Aug 10:30:02 2012----------*/
CdmValueUserGroup::CdmValueUserGroup(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueInt(p_rqDomElement, p_pCdmObject)
{

}

/** +-=---------------------------------------------------------Di 28. Aug 10:30:07 2012----------*
 * @method  CdmValueUserGroup::CdmValueUserGroup             // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 10:30:07 2012----------*/
CdmValueUserGroup::CdmValueUserGroup(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueInt(p_rqvHash, p_pCdmObject)
{

}

/** +-=---------------------------------------------------------Di 28. Aug 10:30:13 2012----------*
 * @method  CdmValueUserGroup::~CdmValueUserGroup            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueUserGroup                                             *
 *----------------last changed: --------------------------------Di 28. Aug 10:30:13 2012----------*/
CdmValueUserGroup::~CdmValueUserGroup()
{
}

/** +-=---------------------------------------------------------Di 20. Nov 12:02:41 2012----------*
 * @method  CdmValueUserGroup::GetUserGroup                  // public, slots                     *
 * @return  CumUserGroup*                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 12:02:41 2012----------*/
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

/** +-=---------------------------------------------------------Di 20. Nov 12:02:50 2012----------*
 * @method  CdmValueUserGroup::SetUserGroup                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CumUserGroup* p_pCumUserGroup                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 12:02:50 2012----------*/
void CdmValueUserGroup::SetUserGroup(CumUserGroup* p_pCumUserGroup)
{
   int iGroupId = 0;

   if (p_pCumUserGroup)
   {
      iGroupId = p_pCumUserGroup->GetId();
   }
   
   SetValue(iGroupId);
}

/** +-=---------------------------------------------------------So 10. Feb 11:42:50 2013----------*
 * @method  CdmValueUserGroup::GetDisplayString              // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:42:50 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 11:42:58 2013----------*
 * @method  CdmValueUserGroup::GetVariant                    // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 11:42:58 2013----------*/
QVariant CdmValueUserGroup::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   qmVariant.insert("Name", GetDisplayString());
   return qmVariant;
}

/** +-=---------------------------------------------------------So 10. Feb 11:43:06 2013----------*
 * @method  CdmValueUserGroup::GetValueVariant               // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:43:06 2013----------*/
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

/** +-=---------------------------------------------------------Di 28. Aug 10:33:21 2012----------*
 * @method  CdmValueUserGroup::SetValueVariant               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 10:33:21 2012----------*/
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
