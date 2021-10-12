/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CftlJournal.cpp
 ** Started Implementation: 2012/08/29
 ** Description:
 **
 ** implements the journal for wms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QList>

// WMS Includes
#include "CdmJournalItem.h"
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmLogging.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsUtilities.h"
#include "CftlDataAccess.h"
#include "CftlJournal.h"

/** +-=---------------------------------------------------------Mi 29. Aug 10:20:51 2012----------*
 * @method  CftlJournal::CftlJournal                       // public                            *
 * @return                                                   //                                   *
 * @param   CftlDataAccess* p_pCftlDataAccess              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 10:20:51 2012----------*/
CftlJournal::CftlJournal(CftlDataAccess* p_pCftlDataAccess)
: m_rpCftlDataAccess(p_pCftlDataAccess)
{
}

/** +-=---------------------------------------------------------Mi 29. Aug 10:21:10 2012----------*
 * @method  CftlJournal::~CftlJournal                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CftlJournal                                                  *
 *----------------last changed: --------------------------------Mi 29. Aug 10:21:10 2012----------*/
CftlJournal::~CftlJournal()
{
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:39:55 2012----------*
 * @method  CftlJournal::ValueModified                      // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:39:55 2012----------*/
qint64 CftlJournal::ValueModified(CdmValue* p_pCdmValue)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   if (CHKPTR(p_pCdmValue) && p_pCdmValue->GetValueType() != eDmValueBinaryDocument)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, SchemeId, DateTime, ChangeMode, ContainerId, ObjectId, Member, DisplayValue, Json_Changes) values";
      qstrQuery += QString("(%1, %2, %3, %4, %5, %6, %7, %8, '%9', ")
                           .arg(p_pCdmValue->GetUserId())
                           .arg(p_pCdmValue->GetSessionId())
                           .arg(p_pCdmValue->GetSchemeId())
                           .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                           .arg(eDmChangeModeModified)
                           .arg(p_pCdmValue->GetObject()->GetObjectContainerId())
                           .arg(p_pCdmValue->GetObject()->GetId())
                           .arg(p_pCdmValue->GetMemberId())
                           .arg(CwmsUtilities::MaskStringForChanges(p_pCdmValue->GetDisplayString()));
      
      qstrQuery += QString("'%1')").arg(CwmsUtilities::MaskStringForChanges(p_pCdmValue->GetValueVariant().toString()));
      lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   }
   else if (CHKPTR(p_pCdmValue) && p_pCdmValue->GetValueType() == eDmValueBinaryDocument)
   {
      lRet = CdmLogging::eDmOk;
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mi 29. Aug 14:26:05 2012----------*
 * @method  CftlJournal::ObjectDeleted                      // public                            *
 * @return qint64                                             //                                   *
 * @param   int p_iObjectId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 14:26:05 2012----------*/
qint64 CftlJournal::ObjectDeleted(int p_iObjectId)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   if (p_iObjectId > 0)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, SchemeId, DateTime, ChangeMode, ObjectId) values";

         
            qstrQuery += QString("(%1, %2, %3, %4, %5, %6)")
               .arg(pCdmManager->GetUserId())
               .arg(pCdmManager->GetSessionId())
               .arg(pCdmManager->GetCurrentScheme()->GetId())
               .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
               .arg(eDmChangeModeDeleted)
               .arg(p_iObjectId);
        
         lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
      }
   }

   return lRet;
}


/** +-=---------------------------------------------------------Mi 29. Aug 11:40:06 2012----------*
 * @method  CftlJournal::ObjectModified                     // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:40:06 2012----------*/
qint64 CftlJournal::ObjectModified(CdmObject* p_pCdmObject)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   if (CHKPTR(p_pCdmObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, SchemeId, DateTime, ChangeMode, ContainerId, ObjectId, DisplayValue) values";

      if (p_pCdmObject->IsNew())
      {
         qstrQuery += QString("(%1, %2, %3, %4, %5, %6, %7, '%8')")
            .arg(p_pCdmObject->GetUserId())
            .arg(p_pCdmObject->GetSessionId())
            .arg(p_pCdmObject->GetSchemeId())
            .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
            .arg(eDmChangeModeNew)
            .arg(p_pCdmObject->GetObjectContainerId())
            .arg(p_pCdmObject->GetId())
            .arg(p_pCdmObject->GetKeyname());
      }
      else if (p_pCdmObject->IsDeleted())   
      {
         qstrQuery += QString("(%1, %2, %3, %4, %5, %6, %7, '%8')")
            .arg(p_pCdmObject->GetUserId())
            .arg(p_pCdmObject->GetSessionId())
            .arg(p_pCdmObject->GetSchemeId())
            .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
             .arg(eDmChangeModeDeleted)
            .arg(p_pCdmObject->GetObjectContainerId())
            .arg(p_pCdmObject->GetId())
            .arg(p_pCdmObject->GetKeyname());
      }

      lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:39:46 2012----------*
 * @method  CftlJournal::ObjectListModified                 // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:39:46 2012----------*/
qint64 CftlJournal::ObjectListModified(CdmObjectContainer* p_pContainer)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   if (CHKPTR(p_pContainer))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, SchemeId, DateTime, ChangeMode, ContainerId, DisplayValue) values";

	  if(CHKPTR(p_pContainer->GetClass()))
	  {
		  if (p_pContainer->IsNew())
		  {
			 qstrQuery += QString("(%1, %2, %3, %4, %5, %6, '%7')")
								  .arg(p_pContainer->GetUserId())
								  .arg(p_pContainer->GetSessionId())
								  .arg(p_pContainer->GetSchemeId())
								  .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
								  .arg(eDmChangeModeNew)
								  .arg(p_pContainer->GetId())
								  .arg(p_pContainer->GetClass()->GetKeyname());
		  }
		  else if (p_pContainer->IsDeleted())   
		  {
			 qstrQuery += QString("(%1, %2, %3, %4, %5, %6, '%7')")
				.arg(p_pContainer->GetUserId())
				.arg(p_pContainer->GetSessionId())
				.arg(p_pContainer->GetSchemeId())
								  .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
								  .arg(eDmChangeModeDeleted)
								  .arg(p_pContainer->GetId())
								  .arg(p_pContainer->GetClass()->GetKeyname());
		  }
      
		  lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
	  }
	  else
	  {
		  lRet = EC(eDmOk);
	  }
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mi 29. Aug 14:22:55 2012----------*
 * @method  CftlJournal::ObjectListDeleted                  // public                            *
 * @return qint64                                             //                                   *
 * @param   int p_iObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 14:22:55 2012----------*/
qint64 CftlJournal::ObjectListDeleted(int p_iObjectListId)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   if (p_iObjectListId > 0)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, SchemeId, DateTime, ChangeMode, ContainerId) values";

        
            qstrQuery += QString("(%1, %2, %3, %4, %5, %6)")
               .arg(pCdmManager->GetUserId())
               .arg(pCdmManager->GetSessionId())
               .arg(pCdmManager->GetCurrentScheme()->GetId())
               .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
               .arg(eDmChangeModeDeleted)
               .arg(p_iObjectListId);
      
         lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
      }
   }

   return lRet;
}

qint64 CftlJournal::GetObjectModifications(const CdmObject* p_pObject,
                                          QDate p_qdFrom,
                                          QDate p_qdTo,
                                          QList<CdmJournalItem*>& p_rqlItems)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if (p_pObject)
   {
      QDateTime qdFrom;
      qdFrom.setDate(p_qdFrom);

      QDateTime qdTo;
      qdTo.setDate(p_qdTo);
      qdTo = qdTo.addDays(1);
      qdTo.setTime(QTime(24,59,59,99));

      QSqlQuery cQSqlQuery;
      QString qstrQuery = "select UserId, SessionId, DateTime, ChangeMode, Member, Json_CHanges, DisplayValue ";
      qstrQuery += "from WMS_JOURNAL ";
      qstrQuery += QString("where objectId = %1 and DateTime >= %2 and DateTime <= %3")
         .arg(p_pObject->GetId())
         .arg(CwmsUtilities::ChangeDateToString(qdFrom))
         .arg(CwmsUtilities::ChangeDateToString(qdTo));
      lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

      if(lRet > 0)
      {
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do // reading each bool
            {
               int       iUserId           = cQSqlQuery.value(0).toInt();
               int       iSessionId        = cQSqlQuery.value(1).toInt();
               QDateTime qdtModified       = cQSqlQuery.value(2).toDateTime();
               int       iChangeMode       = cQSqlQuery.value(3).toInt();
               int       iMemberId         = cQSqlQuery.value(4).toInt();
               QString   qstrChanges       = cQSqlQuery.value(5).toString();
               QString   qstrDisplayValue  = cQSqlQuery.value(6).toString();

               CdmJournalItem* pCdmItem = new CdmJournalItem();
               pCdmItem->SetUserId(iUserId);
               pCdmItem->SetSessionId(iSessionId);
               pCdmItem->SetModified(qdtModified);
               pCdmItem->SetChangeMode((EdmChangeMode) iChangeMode);
               pCdmItem->SetMemberId(iMemberId);
               pCdmItem->SetObjectId(p_pObject->GetId());
               pCdmItem->SetObjectListId(p_pObject->GetObjectContainerId());
               pCdmItem->SetChanges(qstrChanges);
               pCdmItem->SetDisplayString(qstrDisplayValue);
               p_rqlItems.append(pCdmItem);
            }  
            while(cQSqlQuery.next());
         }
      }
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mi 29. Aug 13:55:15 2012----------*
 * @method  CftlJournal::GetObjectListModifications         // public                            *
 * @return qint64                                             //                                   *
 * @param   int p_iObjectListId                              //                                   *
 * @param   QDate p_qdFrom                                   //                                   *
 * @param   QDate p_qdTo                                     //                                   *
 * @param   QList<CdmJournalItem*>& p_rqlItems               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 13:55:15 2012----------*/
qint64 CftlJournal::GetObjectListModifications(int p_iObjectListId,
                                              QDate p_qdFrom,
                                              QDate p_qdTo,
                                              QList<CdmJournalItem*>& p_rqlItems)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if (p_iObjectListId > 0)
   {
      QDateTime qdFrom;
      qdFrom.setDate(p_qdFrom);

      QDateTime qdTo;
      qdTo.setDate(p_qdTo);
      qdTo = qdTo.addDays(1);
      qdTo.setTime(QTime(24,59,59,99));

      QSqlQuery cQSqlQuery;
      QString qstrQuery = "select UserId, SessionId, DateTime, ChangeMode, ObjectId, Member, Json_CHanges, DisplayValue ";
      qstrQuery += "from WMS_JOURNAL ";
      qstrQuery += QString("where ContainerId = %1 and DateTime >= %2 and DateTime <= %3")
                           .arg(p_iObjectListId)
                           .arg(CwmsUtilities::ChangeDateToString(qdFrom))
                           .arg(CwmsUtilities::ChangeDateToString(qdTo));
      lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

      if(lRet > 0)
      {
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do // reading each bool
            {
               int       iUserId           = cQSqlQuery.value(0).toInt();
               int       iSessionId        = cQSqlQuery.value(1).toInt();
               QDateTime qdtModified       = cQSqlQuery.value(2).toDateTime();
               int       iChangeMode       = cQSqlQuery.value(3).toInt();
               int       iObjectId         = cQSqlQuery.value(4).toInt();
               int       iMemberId         = cQSqlQuery.value(5).toInt();
               QString   qstrChanges       = cQSqlQuery.value(6).toString();
               QString   qstrDisplayValue  = cQSqlQuery.value(7).toString();

               CdmJournalItem* pCdmItem = new CdmJournalItem();
               pCdmItem->SetUserId(iUserId);
               pCdmItem->SetSessionId(iSessionId);
               pCdmItem->SetModified(qdtModified);
               pCdmItem->SetChangeMode((EdmChangeMode) iChangeMode);
               pCdmItem->SetMemberId(iMemberId);
               pCdmItem->SetObjectId(iObjectId);
               pCdmItem->SetChanges(qstrChanges);
               pCdmItem->SetObjectListId(p_iObjectListId);
               pCdmItem->SetDisplayString(qstrDisplayValue);
               p_rqlItems.append(pCdmItem);
            }  
            while(cQSqlQuery.next());
         }
      }
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mi 29. Aug 13:54:17 2012----------*
 * @method  CftlJournal::GetDatabaseModifications           // public                            *
 * @return qint64                                             //                                   *
 * @param   int p_iSchemeId                                //                                   *
 * @param   QDate p_qdFrom                                   //                                   *
 * @param   QDate p_qdTo                                     //                                   *
 * @param   QList<CdmJournalItem*>& p_rqlItems               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 13:54:17 2012----------*/
qint64 CftlJournal::GetDatabaseModifications(int p_iSchemeId,
                                            QDate p_qdFrom,
                                            QDate p_qdTo,
                                            QList<CdmJournalItem*>& p_rqlItems)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if (p_iSchemeId > 0)
   {
      QDateTime qdFrom;
      qdFrom.setDate(p_qdFrom);

      QDateTime qdTo;
      qdTo.setDate(p_qdTo);
      qdTo = qdTo.addDays(1);
      qdTo.setTime(QTime(24,59,59,99));


      QSqlQuery cQSqlQuery;
      QString qstrQuery = "select UserId, SessionId, DateTime, ChangeMode, ContainerId, ObjectId, Member, Json_CHanges, DisplayValue ";
      qstrQuery += "from WMS_JOURNAL ";
      qstrQuery += QString("where SchemeId = %1 and DateTime between %2 and %3")
                           .arg(p_iSchemeId)
                           .arg(CwmsUtilities::ChangeDateToString(qdFrom))
                           .arg(CwmsUtilities::ChangeDateToString(qdTo));
      lRet = m_rpCftlDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

      if(lRet > 0)
      {
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do 
            {
               int       iUserId           = cQSqlQuery.value(0).toInt();
               int       iSessionId        = cQSqlQuery.value(1).toInt();
               QDateTime qdtModified       = cQSqlQuery.value(2).toDateTime();
               int       iChangeMode       = cQSqlQuery.value(3).toInt();
               int       iObjectLIstId     = cQSqlQuery.value(4).toInt();
               int       iObjectId         = cQSqlQuery.value(5).toInt();
               int       iMemberId         = cQSqlQuery.value(6).toInt();
               QString   qstrChanges       = cQSqlQuery.value(7).toString();
               QString   qstrDisplayValue  = cQSqlQuery.value(8).toString();

               CdmJournalItem* pCdmItem = new CdmJournalItem();
               pCdmItem->SetUserId(iUserId);
               pCdmItem->SetSessionId(iSessionId);
               pCdmItem->SetModified(qdtModified);
               pCdmItem->SetChangeMode((EdmChangeMode) iChangeMode);
               pCdmItem->SetMemberId(iMemberId);
               pCdmItem->SetObjectId(iObjectId);
               pCdmItem->SetObjectListId(iObjectLIstId);
               pCdmItem->SetChanges(qstrChanges);

               p_rqlItems.append(pCdmItem);
            }  
            while(cQSqlQuery.next());
         }
      }
   }

   return lRet;
}
