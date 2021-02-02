/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifdef WIN32
#include <CdmValueCounter.h>
#include <qt_windows.h>
#undef GetObject
#else
#include <unistd.h>
#endif //

// own Includes
#include "CdbCommandUpdateContainer.h"
#include "CdbCommandReadBinaryDocument.h"
#include "CdbCommandDeleteContainer.h"
#include "CdbCommandCheckObjectLocked.h"
#include "CdbCommandDeleteObject.h"
#include "CdbCommandExistContainer.h"
#include "CdbCommandGetNewObjectId.h"
#include "CdbCommandUpdateObject.h"
#include "CdbCommandGetNewContainerId.h"
#include "CdbCommandGetContainerList.h"
#include "CdbCommandLoadObjects.h"
#include "CdbCommandRefreshObject.h"
#include "CdbCommandLoadContainer.h"
#include "CdbCommandUpdateBinaryDocument.h"
#include "CdbCommandRefreshComtainer.h"
#include "CdbCommandCountObjectsOnDb.h"
#include "CdbCommandLockObject.h"
#include "CdbCommandGetOwner.h"
#include "CdbCommandUnlockObject.h"
#include "CdbCommandCheckObjectUsed.h"
#include "CdbCommandLoadSingleObject.h"
#include "CdbCommandGetCounterValue.h"
#include "CdbCommandGetObjectReferences.h"
#include "CdbQuery.h"
#include "CdbObjectAccess.h"

/** +-=---------------------------------------------------------Sa 20. Aug 12:02:06 2005----------*
 * @method  CdbObjectAccess::CdbObjectAccess             // public                            *
 * @return                                                   //                                   *
 * @param   CdbDataAccess* p_pCdbDataAccess              //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:06 2005----------*/
CdbObjectAccess::CdbObjectAccess(  CdbDataAccess* p_pCdbDataAccess )
   : m_rpCdbDataAccess(p_pCdbDataAccess),
     m_iNewObjectCounter(0),
     m_iNewObjectListCounter(0)
{
   // nothing to do at the moment
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:02:16 2005----------*
 * @method  CdbObjectAccess::~CdbObjectAccess            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdbObjectAccess                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:16 2005----------*/
CdbObjectAccess::~CdbObjectAccess(  )
{
   // nothing to do at the moment
}

/** +-=---------------------------------------------------------Di 23. Aug 15:50:10 2005----------*
 * @method  CdbObjectAccess::DeleteObjectList              // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment Deletes an objectlist from db.                                                        *
 *----------------last changed: --------------------------------Di 23. Aug 15:50:10 2005----------*/
long CdbObjectAccess::DeleteObjectList(  long p_lObjectListId )
{
    CdbCommandDeleteContainer command(p_lObjectListId, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Di 23. Aug 15:50:01 2005----------*
 * @method  CdbObjectAccess::DeleteObject                  // protected, virtual                *
 * @return  long                                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment This method deletes objects from db.                                                  *
 *----------------last changed: --------------------------------Di 23. Aug 15:50:01 2005----------*/
long CdbObjectAccess::DeleteObject(long p_lObjectId, long p_lSessionId)
{
   CdbCommandDeleteObject command(p_lObjectId, p_lSessionId, m_rpCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Mi 15. Sep 17:00:25 2010----------*
 * @method  CdbObjectAccess::ExecuteQuery                  // public                            *
 * @return  long                                             //                                   *
 * @param   long# p_lDbId                                    //                                   *
 * @param   CdmObjectContainer*# p_pContainer                 //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @comment This emthod executes an query on Server Side.                                         *
 *----------------last changed: --------------------------------Mi 15. Sep 17:00:25 2010----------*/
long CdbObjectAccess::ExecuteQuery(CdmQuery* p_pCdmQuery)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   if (CHKPTR(m_rpCdbDataAccess) &&
       CHKPTR(p_pCdmQuery))
   {
      CdbQuery cCdbQuery(m_rpCdbDataAccess, p_pCdmQuery);
      lRet = cCdbQuery.Execute();
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }
   BODY_CATCH

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:02:31 2005----------*
 * @method  CdbObjectAccess::ExistObjectList               // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   QString p_qstrObjectListKeyname                  //                                   *
 * @comment This method checks if exist th objectlist with the overgiven keyname.                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:31 2005----------*/
long CdbObjectAccess::ExistObjectList(  long p_lClassId, QString p_qstrObjectListKeyname )
{
   Q_UNUSED(p_lClassId)
   CdbCommandExistContainer command(p_qstrObjectListKeyname, m_rpCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------So 11. Sep 12:22:14 2005----------*
 * @method  CdbObjectAccess::GetNewObjectId                // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment This method gets a new object id from datasource.                                     *
 *----------------last changed: --------------------------------So 11. Sep 12:22:14 2005----------*/
long CdbObjectAccess::GetNewObjectId(long p_lObjectListId, long p_lSessionId)
{
    CdbCommandGetNewObjectId command(p_lObjectListId, p_lSessionId, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------So 11. Sep 12:22:20 2005----------*
 * @method  CdbObjectAccess::GetNewObjectListId            // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 11. Sep 12:22:20 2005----------*/
long CdbObjectAccess::GetNewObjectListId(  long p_lClassId, long p_lSessionId )
{
   CdbCommandGetNewContainerId command(p_lClassId, p_lSessionId, m_rpCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------So 22. Jan 13:59:23 2006----------*
 * @method  CdbObjectAccess::GetObjectListsList            // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDbId                                     //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   QMap<long,QString>& p_rqmObjectListsList         //                                   *
 * @comment This method returns a list of all objectlists.                                        *
 *----------------last changed: Wolfgang Gra�of----------------So 22. Jan 13:59:23 2006----------*/
long CdbObjectAccess::GetObjectListsList(  long p_lDbId,
                                            long p_lClassId,
                                            QMap<long,
                                           QString>& p_rqmObjectListsList )
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   CdbCommandGetContainerList command(p_lDbId, p_lClassId, m_rpCdbDataAccess);
   lRet = command.Run();
   command.GetResult(p_rqmObjectListsList);
   BODY_CATCH

   return lRet;
}

/** +-=---------------------------------------------------------Do 17. Mai 15:37:35 2007----------*
 * @method  CdbObjectAccess::LoadObjects                   // public                            *
 * @return  long                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QValueList<long>& p_rqvlObjectIds                //                                   *
 * @comment This method loads all objects overgiven in the objectid list.                         *
 *----------------last changed: Wolfgang Gra�of----------------Do 17. Mai 15:37:35 2007----------*/
long CdbObjectAccess::LoadObjects(CdmObjectContainer* p_pContainer,
                                    QLinkedList<long>& p_rqvlObjectIds)
{
    CdbCommandLoadObjects command(p_pContainer, p_rqvlObjectIds, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:02:49 2005----------*
 * @method  CdbObjectAccess::LoadObject                    // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   CdmObject*& p_pCdmObject                         //                                   *
 * @comment This method loads a aobject from DataAccess.                                          *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:49 2005----------*/
long CdbObjectAccess::LoadObject(long p_lObjectListId,
                                 long p_lObjectId,
                                 CdmObject*& p_pCdmObject )
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   CdbCommandLoadSingleObject command(p_lObjectListId, p_lObjectId, m_rpCdbDataAccess);
   lRet = command.Run();

   if (p_pCdmObject)
   {
       ERR("Object must be null!")
   }

   p_pCdmObject = command.GetResult();
   BODY_CATCH

   return lRet;
}

long CdbObjectAccess::LoadObject(long p_lObjectListId,
                                 QString p_qstrKeyname,
                                 CdmObject*& p_pCdmObject)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   CdbCommandLoadSingleObject command(p_lObjectListId, p_qstrKeyname, m_rpCdbDataAccess);
   lRet = command.Run();

   if (p_pCdmObject)
   {
       ERR("Object must be null!")
   }

   p_pCdmObject = command.GetResult();
   BODY_CATCH

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:02:53 2005----------*
 * @method  CdbObjectAccess::LoadObjectList                // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:53 2005----------*/
long CdbObjectAccess::LoadContainer(long p_lObjectListId, CdmObjectContainer*& p_pContainer)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   if (p_pContainer)
   {
       CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
   }

   CdbCommandLoadContainer command(p_lObjectListId, true, m_rpCdbDataAccess);
   lRet = command.Run();
   p_pContainer = command.GetResult();
   BODY_CATCH

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:00 2005----------*
 * @method  CdbObjectAccess::LoadEmptyObjectList           // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDbId                                     //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:00 2005----------*/
long CdbObjectAccess::LoadEmptyObjectList(  long p_lDbId,
                                             QString p_qstrKeyname,
                                             CdmObjectContainer*& p_pContainer )
{
    long lRet = CdmLogging::eDmObjectAccessError;

    BODY_TRY
    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CdbCommandLoadContainer command(p_lDbId, p_qstrKeyname, false, m_rpCdbDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();
    BODY_CATCH

    return lRet;
}

/** +-=---------------------------------------------------------Do 25. Mai 12:46:34 2006----------*
 * @method  CdbObjectAccess::LoadEmptyObjectList           // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDbId                                     //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: Wolfgang Gra�of----------------Do 25. Mai 12:46:34 2006----------*/
long CdbObjectAccess::LoadEmptyObjectList(long p_lDbId,
                                          long p_lId,
                                          CdmObjectContainer*& p_pContainer)
{
    long lRet = CdmLogging::eDmObjectAccessError;
    Q_UNUSED(p_lDbId)

    BODY_TRY
    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CdbCommandLoadContainer command(p_lId, false, m_rpCdbDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();
    BODY_CATCH

    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:05 2005----------*
 * @method  CdbObjectAccess::LoadObjectList                // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDbId                                     //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:05 2005----------*/
long CdbObjectAccess::LoadContainer(  long p_lDbId,
                                        QString p_qstrKeyname,
                                        CdmObjectContainer*& p_pContainer )
{
    long lRet = CdmLogging::eDmObjectAccessError;

    BODY_TRY
    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CdbCommandLoadContainer command(p_lDbId, p_qstrKeyname, true, m_rpCdbDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();
    BODY_CATCH

    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:11 2005----------*
 * @method  CdbObjectAccess::LockObject                    // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   bool & p_bResult                                 //                                   *
 * @comment This method locks objects on server side.                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:11 2005----------*/
long CdbObjectAccess::LockObject(  long p_lSessionId, long p_lObjectId, bool & p_bResult )
{
   p_bResult = false;
   CdbCommandLockObject command(p_lSessionId, p_lObjectId, m_rpCdbDataAccess);
   long lRet  = command.Run();
   p_bResult = SUCCESSFULL(lRet);
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:16 2005----------*
 * @method  CdbObjectAccess::IsObjectLocked                // protected                         *
 * @return  long                                             // SessionId of the locker or 0 if object is not locked*
 * @param   long p_lObjectId                                 //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment returns if a object is locked or not.                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:16 2005----------*/
long CdbObjectAccess::IsObjectLocked(  long p_lObjectId, long p_lSessionId )
{
    CdbCommandCheckObjectLocked command(p_lObjectId, p_lSessionId, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:22 2005----------*
 * @method  CdbObjectAccess::UnLockObject                  // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   bool & p_bResult                                 //                                   *
 * @comment This method unlocks objects on server side.                                           *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:22 2005----------*/
long CdbObjectAccess::UnLockObject(  long p_lSessionId, long p_lObjectId, bool & p_bResult )
{
    p_bResult = false;
    CdbCommandUnlockObject command(p_lSessionId, p_lObjectId, m_rpCdbDataAccess);
    long lRet  = command.Run();
    p_bResult = SUCCESSFULL(lRet);
    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:26 2005----------*
 * @method  CdbObjectAccess::UpdateObject                  // public                            *
 * @return  long                                             //                                   *
 * @param   CdmObject*& p_pCdmObject                         //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment This method updates an object. It sends the object changes to server. on which it     *
 *          will be merged and resend. This object can be invalid or delted and receiving the     *
 *          new object data because a other user has deleted it.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:26 2005----------*/
long CdbObjectAccess::UpdateObject(CdmObject*& p_pCdmObject, long p_lSessionId)
{
    CdbCommandUpdateObject command(p_lSessionId, p_pCdmObject, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Mo 5. Sep 19:07:39 2005-----------*
 * @method  CdbObjectAccess::UpdateObjectList              // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment This method updates an object. It sends the object changes to server. on which it     *
 *          will be merged and resend. This object can be invalid or delted and receiving the     *
 *          new object data because a other user has deleted it.                                  *
 *----------------last changed: --------------------------------Mo 5. Sep 19:07:39 2005-----------*/
long CdbObjectAccess::UpdateObjectList(  CdmObjectContainer*& p_pContainer, long p_lSessionId )
{
    CdbCommandUpdateContainer command(p_pContainer, p_lSessionId, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:07:25 2005----------*
 * @method  CdbObjectAccess::ReadBinaryDocument            // public                            *
 * @return  int                                              //                                   *
 * @param   CdmValueBinaryDocument* p_pCdmBinaryDocument          //                                   *
 * @comment This method reads the BinaryDocument from database and set it to the local filesystem.*
 *----------------last changed: --------------------------------Sa 20. Aug 12:07:25 2005----------*/
QByteArray CdbObjectAccess::ReadBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    CdbCommandReadBinaryDocument command(p_pCdmBinaryDocument, m_rpCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        return command.GetByteArray();
    }

    return QByteArray();
}

/** +-=---------------------------------------------------------Mo 5. Sep 19:30:15 2005-----------*
 * @method  CdbObjectAccess::UpdateBinaryDocument          // public, virtual                   *
 * @return  int                                              //                                   *
 * @param   CdmValueBinaryDocument* p_pCdmBinaryDocument          //                                   *
 * @comment This method updates the BinaryDocument on the database and synchronizes it to the     *
 *          local file.                                                                           *
 *----------------last changed: --------------------------------Mo 5. Sep 19:30:15 2005-----------*/
int CdbObjectAccess::UpdateBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    CdbCommandUpdateBinaryDocument command(p_pCdmBinaryDocument, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Do 10. Sep 17:53:51 2009----------*
 * @method  CdbObjectAccess::GetCounterValue               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmValueCounter* p_pCdmCounter                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Sep 17:53:51 2009----------*/
long CdbObjectAccess::GetCounterValue(CdmValueCounter* p_pCdmCounter)
{
   CdbCommandGetCounterValue command(p_pCdmCounter, m_rpCdbDataAccess);
   command.Run();
   return p_pCdmCounter->GetValue();
}

/** +-=---------------------------------------------------------Mo 17. Sep 17:55:28 2007----------*
 * @method  CdbObjectAccess::IsObjectUsed                  // public                            *
 * @return  int                                              //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment This method returns if a object is used in a objectref or not.                        *
 *----------------last changed: --------------------------------Mo 17. Sep 17:55:28 2007----------*/
int CdbObjectAccess::IsObjectUsed(long p_lObjectId, long p_lObjectListId)
{
    CdbCommandCheckObjectUsed command(p_lObjectId, p_lObjectListId, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 8. Nov 10:57:29 2008-----------*
 * @method  CdbObjectAccess::RefreshObject                 // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment refreshes the values from the overgiven object.                                       *
 *----------------last changed: --------------------------------Sa 8. Nov 10:57:29 2008-----------*/
long CdbObjectAccess::RefreshObject(CdmObject* p_pCdmObject)
{
    CdbCommandRefreshObject command(p_pCdmObject, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 8. Nov 10:59:01 2008-----------*
 * @method  CdbObjectAccess::RefreshObjectList             // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment refreshes the objects from the overgiven objectlist.                                  *
 *----------------last changed: --------------------------------Sa 8. Nov 10:59:01 2008-----------*/
long CdbObjectAccess::RefreshObjectList(CdmObjectContainer* p_pContainer)
{
    CdbCommandRefreshComtainer command(p_pContainer, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 8. Nov 10:59:19 2008-----------*
 * @method  CdbObjectAccess::CountObjectsOnDb              // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment refreshes the objects from the overgiven objectlist.                                  *
 *----------------last changed: --------------------------------Sa 8. Nov 10:59:19 2008-----------*/
long CdbObjectAccess::CountObjectsOnDb(CdmObjectContainer* p_pContainer)
{
   CdbCommandCountObjectsOnDb command(p_pContainer, m_rpCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Do 8. Nov 11:18:37 2012-----------*
 * @method  CdbObjectAccess::GetReferences                 // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   QMap<long, long>& p_rqmReferences                // objectId/ObjectListId             *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 8. Nov 11:18:37 2012-----------*/
bool CdbObjectAccess::GetReferences(long p_lObjectListId,
                                      long p_lObjectId,
                                      QMap<long,
                                      long>& p_rqmReferences)
{
   CdbCommandGetObjectReferences command(p_lObjectListId, p_lObjectId, m_rpCdbDataAccess);
   long lRet = command.Run();
   p_rqmReferences = command.GetResult();
   return SUCCESSFULL(lRet);
}

/** +-=---------------------------------------------------------Do 8. Nov 11:18:59 2012-----------*
 * @method  CdbObjectAccess::GetOwner                      // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   long& p_lOwnerObjectListId                       //                                   *
 * @param   long& p_lOwnerObjectId                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 8. Nov 11:18:59 2012-----------*/
bool CdbObjectAccess::GetOwner(long p_lObjectListId,
                                 long& p_lOwnerObjectListId,
                                 long& p_lOwnerObjectId)
{
   bool bRet = false;

   BODY_TRY
   CdbCommandGetOwner command(p_lObjectListId, 0, m_rpCdbDataAccess);
   command.Run();

   p_lOwnerObjectListId = command.GetOwnerContainerId();
   p_lOwnerObjectId = command.GetOwnerObjectId();

   bRet = (p_lOwnerObjectId > 0 && p_lOwnerObjectListId > 0);
   BODY_CATCH

   return bRet;
}

/** +-=---------------------------------------------------------Do 8. Nov 11:19:21 2012-----------*
 * @method  CdbObjectAccess::GetOwner                      // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   long& p_lOwnerObjectListId                       //                                   *
 * @param   long& p_lOwnerObjectId                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 8. Nov 11:19:21 2012-----------*/
bool CdbObjectAccess::GetOwner(long p_lObjectListId,
                                 long p_lObjectId,
                                 long& p_lOwnerObjectListId,
                                 long& p_lOwnerObjectId)
{
   bool bRet = false;

   BODY_TRY
   CdbCommandGetOwner command(p_lObjectListId, p_lObjectId, m_rpCdbDataAccess);
   command.Run();

   p_lOwnerObjectListId = command.GetOwnerContainerId();
   p_lOwnerObjectId = command.GetOwnerObjectId();

   bRet = (p_lOwnerObjectId > 0 && p_lOwnerObjectListId > 0);
   BODY_CATCH

   return bRet;
}
