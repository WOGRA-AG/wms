/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdbJournal.cpp
 ** Started Implementation: 2012/08/29
 ** Description:
 **
 ** implements the journal for wms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// Qt includes
#include <QSqlQuery>

// WMS Commons Includes
#include "CwmsUtilities.h"

// WMSCORE Includes
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmJournalItem.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmScheme.h"
#include "CdmSessionManager.h"
#include "CdmValue.h"

// own Includes
#include "CdbDataAccess.h"
#include "CdbJournal.h"

CdbJournal::CdbJournal(CdbDataAccess* p_pCdbDataAccess)
    : m_rpCdbDataAccess(p_pCdbDataAccess)
{
    // all the hard work was done above
}

long CdbJournal::ValueModified(CdmValue* p_pCdmValue)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   if (CHKPTR(p_pCdmValue) && (p_pCdmValue->GetValueType() != eDmValueBinaryDocument))
   {
      QSqlQuery cQSqlQuery(m_rpCdbDataAccess->GetDbInterface()->GetSqlDatabase());

      cQSqlQuery.prepare("insert into WMS_JOURNAL (UserId, SessionId, DatabaseId, DateTime, ChangeMode, ObjectListId, ObjectId, `Member`, DisplayValue, Json_Changes) values"
                         "(:userid, :sessionId, :databaseId, :dateTime, :changeMode, :objListId, :objId, :member, :displayvalue, :json)");
      cQSqlQuery.bindValue(":userid", (int) p_pCdmValue->GetUserId());
      cQSqlQuery.bindValue(":sessionId", (int)p_pCdmValue->GetSessionId());
      cQSqlQuery.bindValue(":databaseId", (int)p_pCdmValue->GetSchemeId());
      cQSqlQuery.bindValue(":dateTime", QDateTime::currentDateTime());
      cQSqlQuery.bindValue(":changeMode", eDmChangeModeModified);
      cQSqlQuery.bindValue(":objListId", (int)p_pCdmValue->GetDataObject()->GetObjectContainerId());
      cQSqlQuery.bindValue(":objId", (int)p_pCdmValue->GetDataObject()->GetId());
      cQSqlQuery.bindValue(":member", (int)p_pCdmValue->GetMemberId());
      cQSqlQuery.bindValue(":displayvalue", p_pCdmValue->GetDisplayString());
      cQSqlQuery.bindValue(":json", p_pCdmValue->GetValueVariant().toString());

      lRet = m_rpCdbDataAccess->ExecuteQuery(cQSqlQuery);
   }
   else if (CHKPTR(p_pCdmValue) && (p_pCdmValue->GetValueType() == eDmValueBinaryDocument))
   {
      lRet = CdmLogging::eDmOk;
   }
   BODY_CATCH

   return lRet;
}

long CdbJournal::ObjectDeleted(int p_iObjectId)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   if (p_iObjectId > 0)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, DatabaseId, DateTime, ChangeMode, ObjectId) values";

            qstrQuery += QString("(%1, %2, %3, %4, %5, %6)")
               .arg(pCdmManager->GetUserId())
               .arg(pCdmManager->GetSessionId())
               .arg(pCdmManager->GetCurrentScheme()->GetId())
               .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
               .arg(eDmChangeModeDeleted)
               .arg(p_iObjectId);

         lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
      }
   }
   BODY_CATCH
   return lRet;
}

long CdbJournal::ObjectModified(CdmObject* p_pCdmObject)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (CHKPTR(p_pCdmObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, DatabaseId, DateTime, ChangeMode, ObjectListId, ObjectId, DisplayValue) values";

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

      lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   }

   return lRet;
}

long CdbJournal::ObjectListModified(CdmObjectContainer* p_pContainer)
{
   long lRet = CdmLogging::eDmObjectAccessError;
   if (CHKPTR(p_pContainer))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, DatabaseId, DateTime, ChangeMode, ObjectListId, DisplayValue) values";

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
      
		  lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
	  }
	  else
	  {
		  lRet = EC(eDmOk);
	  }
   }

   return lRet;
}

long CdbJournal::ObjectListDeleted(int p_iObjectListId)
{
   long lRet = CdmLogging::eDmObjectAccessError;
   if (p_iObjectListId > 0)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery = "insert into WMS_JOURNAL (UserId, SessionId, DatabaseId, DateTime, ChangeMode, ObjectListId) values";

            qstrQuery += QString("(%1, %2, %3, %4, %5, %6)")
               .arg(pCdmManager->GetUserId())
               .arg(pCdmManager->GetSessionId())
               .arg(pCdmManager->GetCurrentScheme()->GetId())
               .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
               .arg(eDmChangeModeDeleted)
               .arg(p_iObjectListId);

         lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
      }
   }

   return lRet;
}

long CdbJournal::GetObjectModifications(int p_iObjectId,
                                          QDate p_qdFrom,
                                          QDate p_qdTo,
                                          QList<CdmJournalItem*>& p_rqlItems)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_iObjectId > 0)
   {
      QDateTime qdFrom;
      qdFrom.setDate(p_qdFrom);

      QDateTime qdTo;
      qdTo.setDate(p_qdTo);
      qdTo = qdTo.addDays(1);
      qdTo.setTime(QTime(24,59,59,99));

      QSqlQuery cQSqlQuery;
      QString qstrQuery = "select UserId, SessionId, DateTime, ChangeMode, `Member`, Json_CHanges, DisplayValue ";
      qstrQuery += "from WMS_JOURNAL ";
      qstrQuery += QString("where objectId = %1 and DateTime >= %2 and DateTime <= %3")
         .arg(p_iObjectId)
         .arg(CwmsUtilities::ChangeDateToString(qdFrom))
         .arg(CwmsUtilities::ChangeDateToString(qdTo));
      lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

      if (lRet > 0)
      {
         cQSqlQuery.first();

         if (cQSqlQuery.isValid())
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
               pCdmItem->SetChanges(qstrChanges);
               pCdmItem->SetDisplayString(qstrDisplayValue);
               p_rqlItems.append(pCdmItem);
            }
            while (cQSqlQuery.next());
         }
      }
   }

   return lRet;
}

long CdbJournal::GetContainerModifications(int p_iObjectListId,
                                              QDate p_qdFrom,
                                              QDate p_qdTo,
                                              QList<CdmJournalItem*>& p_rqlItems)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_iObjectListId > 0)
   {
      QDateTime qdFrom;
      qdFrom.setDate(p_qdFrom);

      QDateTime qdTo;
      qdTo.setDate(p_qdTo);
      qdTo = qdTo.addDays(1);
      qdTo.setTime(QTime(24,59,59,99));

      QSqlQuery cQSqlQuery;
      QString qstrQuery = "select UserId, SessionId, DateTime, ChangeMode, ObjectId, `Member`, Json_CHanges, DisplayValue ";
      qstrQuery += "from WMS_JOURNAL ";
      qstrQuery += QString("where objectlistId = %1 and DateTime >= %2 and DateTime <= %3")
                           .arg(p_iObjectListId)
                           .arg(CwmsUtilities::ChangeDateToString(qdFrom))
                           .arg(CwmsUtilities::ChangeDateToString(qdTo));
      lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

      if (lRet > 0)
      {
         cQSqlQuery.first();

         if (cQSqlQuery.isValid())
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
               pCdmItem->SetDisplayString(qstrDisplayValue);
               p_rqlItems.append(pCdmItem);
            }
            while (cQSqlQuery.next());
         }
      }
   }

   return lRet;
}

long CdbJournal::GetDatabaseModifications(int p_iDatabaseId,
                                            QDate p_qdFrom,
                                            QDate p_qdTo,
                                            QList<CdmJournalItem*>& p_rqlItems)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_iDatabaseId > 0)
   {
      QDateTime qdFrom;
      qdFrom.setDate(p_qdFrom);

      QDateTime qdTo;
      qdTo.setDate(p_qdTo);
      qdTo = qdTo.addDays(1);
      qdTo.setTime(QTime(24,59,59,99));


      QSqlQuery cQSqlQuery;
      QString qstrQuery = "select UserId, SessionId, DateTime, ChangeMode, ObjectListId, ObjectId, `Member`, Json_CHanges, DisplayValue ";
      qstrQuery += "from WMS_JOURNAL ";
      qstrQuery += QString("where DatabaseId = %1 and DateTime between %2 and %3")
                           .arg(p_iDatabaseId)
                           .arg(CwmsUtilities::ChangeDateToString(qdFrom))
                           .arg(CwmsUtilities::ChangeDateToString(qdTo));
      lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

      if (lRet > 0)
      {
         cQSqlQuery.first();

         if (cQSqlQuery.isValid())
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
               pCdmItem->SetDisplayString(qstrDisplayValue);
               p_rqlItems.append(pCdmItem);
            }
            while (cQSqlQuery.next());
         }
      }
   }

   return lRet;
}
