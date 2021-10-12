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
#include <QFile>
#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QTime>


#ifdef WIN32
#include <qt_windows.h>
#undef GetObject
#else
#include <unistd.h>
#endif //

// WMS includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmValue.h"
#include "CdmLogging.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListString.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueListObjects.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"
#include "CdmValueEnum.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CwnCommandUpdateContainer.h"
#include "CwnCommandReadBinaryDocument.h"
#include "CwnCommandDeleteContainer.h"
#include "CwnCommandCheckObjectLocked.h"
#include "CwnCommandDeleteObject.h"
#include "CwnCommandExistContainer.h"
#include "CwnCommandGetNewObjectId.h"
#include "CwnCommandUpdateObject.h"
#include "CwnCommandGetNewContainerId.h"
#include "CwnCommandGetContainerList.h"
#include "CwnCommandLoadObjects.h"
#include "CwnCommandRefreshObject.h"
#include "CwnCommandLoadContainer.h"
#include "CwnCommandUpdateBinaryDocument.h"
#include "CwnCommandRefreshContainer.h"
#include "CwnCommandCountObjectsOnDb.h"
#include "CwnCommandLockObject.h"
#include "CwnCommandGetOwner.h"
#include "CwnCommandUnlockObject.h"
#include "CwnCommandCheckObjectUsed.h"
#include "CwnCommandLoadSingleObject.h"
#include "CwnCommandGetCounterValue.h"
#include "CwnCommandGetObjectReferences.h"
#include "CwnHelper.h"
#include "CwnQuery.h"
#include "CwnQueryElement.h"
#include "CwnObjectAccess.h"
#include "CwnJournal.h"
#include "CwnDataAccess.h"

#define MAXLOCKTRIALS 20
#define BINARYBLOCK 10000


/** +-=---------------------------------------------------------Sa 20. Aug 12:02:06 2005----------*
 * @method  CwnObjectAccess::CwnObjectAccess             // public                            *
 * @return                                                   //                                   *
 * @param   CwnDataAccess* p_pCwnDataAccess              //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:06 2005----------*/
CwnObjectAccess::CwnObjectAccess(  CwnDataAccess* p_pCwnDataAccess )
   : m_rpCwnDataAccess(p_pCwnDataAccess),
     m_iNewObjectCounter(0),
     m_iNewObjectListCounter(0)
{
   // nothing to do at the moment
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:02:16 2005----------*
 * @method  CwnObjectAccess::~CwnObjectAccess            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwnObjectAccess                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:16 2005----------*/
CwnObjectAccess::~CwnObjectAccess(  )
{
   // nothing to do at the moment
}

/** +-=---------------------------------------------------------Di 23. Aug 15:50:10 2005----------*
 * @method  CwnObjectAccess::DeleteObjectList              // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @comment Deletes an objectlist from db.                                                        *
 *----------------last changed: --------------------------------Di 23. Aug 15:50:10 2005----------*/
qint64 CwnObjectAccess::DeleteContainer( qint64 p_lObjectListId )
{
    CwnCommandDeleteContainer command(p_lObjectListId, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Di 23. Aug 15:50:01 2005----------*
 * @method  CwnObjectAccess::DeleteObject                  // protected, virtual                *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment This method deletes objects from db.                                                  *
 *----------------last changed: --------------------------------Di 23. Aug 15:50:01 2005----------*/
qint64 CwnObjectAccess::DeleteObject(qint64 p_lObjectId,qint64 p_lSessionId)
{
    CwnCommandDeleteObject command(p_lObjectId,p_lSessionId,m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Mi 15. Sep 17:00:25 2010----------*
 * @method  CwnObjectAccess::ExecuteQuery                  // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64# p_lDbId                                    //                                   *
 * @param   CdmObjectContainer*# p_pContainer                 //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @comment This emthod executes an query on Server Side.                                         *
 *----------------last changed: --------------------------------Mi 15. Sep 17:00:25 2010----------*/
qint64 CwnObjectAccess::ExecuteQuery(CdmQuery* p_pCdmQuery)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(m_rpCwnDataAccess) && CHKPTR(p_pCdmQuery))
    {
       CwnQuery cCwnQuery(m_rpCwnDataAccess, p_pCdmQuery);
       lRet = cCwnQuery.Run();
    }
    else
    {
       lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:02:31 2005----------*
 * @method  CwnObjectAccess::ExistObjectList               // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @param   QString p_qstrObjectListKeyname                  //                                   *
 * @comment This method checks if exist th objectlist with the overgiven keyname.                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:31 2005----------*/
qint64 CwnObjectAccess::ExistObjectList( qint64 p_lClassId, QString p_qstrObjectListKeyname )
{
    CwnCommandExistContainer command(p_lClassId, p_qstrObjectListKeyname, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------So 11. Sep 12:22:14 2005----------*
 * @method  CwnObjectAccess::GetNewObjectId                // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment This method gets a new object id from datasource.                                     *
 *----------------last changed: --------------------------------So 11. Sep 12:22:14 2005----------*/
qint64 CwnObjectAccess::GetNewObjectId(qint64 p_lObjectListId,qint64 p_lSessionId)
{
    CwnCommandGetNewObjectId command(p_lObjectListId, p_lSessionId, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------So 11. Sep 12:22:20 2005----------*
 * @method  CwnObjectAccess::GetNewObjectListId            // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 11. Sep 12:22:20 2005----------*/
qint64 CwnObjectAccess::GetNewObjectListId( qint64 p_lClassId,qint64 p_lSessionId )
{
    CwnCommandGetNewContainerId command(p_lClassId, p_lSessionId, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------So 22. Jan 13:59:23 2006----------*
 * @method  CwnObjectAccess::GetObjectListsList            // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @param   QMap<qint64,QString>& p_rqmObjectListsList         //                                   *
 * @comment This method returns a list of all objectlists.                                        *
 *----------------last changed: Wolfgang Gra�of----------------So 22. Jan 13:59:23 2006----------*/
qint64 CwnObjectAccess::GetObjectListsList( qint64 p_lDbId,
                                           qint64 p_lClassId,
                                            QMap<qint64,
                                           QString>& p_rqmObjectListsList )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    CwnCommandGetContainerList command(p_lDbId, p_lClassId, m_rpCwnDataAccess);
    lRet = command.Run();
    command.GetResult(p_rqmObjectListsList);
    return lRet;
}

/** +-=---------------------------------------------------------Do 17. Mai 15:37:35 2007----------*
 * @method  CwnObjectAccess::LoadObjects                   // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QValueList<qint64>& p_rqvlObjectIds                //                                   *
 * @comment This method loads all objects overgiven in the objectid list.                         *
 *----------------last changed: Wolfgang Gra�of----------------Do 17. Mai 15:37:35 2007----------*/
qint64 CwnObjectAccess::LoadObjects(CdmObjectContainer* p_pContainer,
                                    QList<qint64>& p_rqvlObjectIds)
{
    CwnCommandLoadObjects command(p_pContainer, p_rqvlObjectIds, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:02:49 2005----------*
 * @method  CwnObjectAccess::LoadObject                    // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   CdmObject*& p_pCdmObject                         //                                   *
 * @comment This method loads a aobject from DataAccess.                                          *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:49 2005----------*/
qint64 CwnObjectAccess::LoadObject( qint64 p_lObjectListId,
                                   qint64 p_lObjectId,
                                    CdmObject*& p_pCdmObject )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    CwnCommandLoadSingleObject command(p_lObjectListId, p_lObjectId, m_rpCwnDataAccess);
    lRet = command.Run();

    if (p_pCdmObject)
    {
        ERR("Object must be null!");
    }

    p_pCdmObject = command.GetResult();
    return lRet;
}

qint64 CwnObjectAccess::LoadObject(qint64 p_lObjectListId,
                                 QString p_qstrKeyname,
                                 CdmObject*& p_pCdmObject )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    CwnCommandLoadSingleObject command(p_lObjectListId, p_qstrKeyname, m_rpCwnDataAccess);
    lRet = command.Run();

    if (p_pCdmObject)
    {
        ERR("Object msut be null");
    }

    p_pCdmObject = command.GetResult();
    return lRet;
}



/** +-=---------------------------------------------------------Sa 20. Aug 12:02:53 2005----------*
 * @method  CwnObjectAccess::LoadObjectList                // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:02:53 2005----------*/
qint64 CwnObjectAccess::LoadContainer(qint64 p_lObjectListId, CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CwnCommandLoadContainer command(p_lObjectListId, true, m_rpCwnDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:00 2005----------*
 * @method  CwnObjectAccess::LoadEmptyObjectList           // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:00 2005----------*/
qint64 CwnObjectAccess::LoadEmptyContainer( qint64 p_lDbId,
                                             QString p_qstrKeyname,
                                             CdmObjectContainer*& p_pContainer )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CwnCommandLoadContainer command(p_lDbId, p_qstrKeyname, false, m_rpCwnDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;
}

/** +-=---------------------------------------------------------Do 25. Mai 12:46:34 2006----------*
 * @method  CwnObjectAccess::LoadEmptyObjectList           // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: Wolfgang Gra�of----------------Do 25. Mai 12:46:34 2006----------*/
qint64 CwnObjectAccess::LoadEmptyContainer(qint64 p_lDbId,
                                         qint64 p_lId,
                                          CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    Q_UNUSED(p_lDbId);

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CwnCommandLoadContainer command(p_lId, false, m_rpCwnDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:05 2005----------*
 * @method  CwnObjectAccess::LoadObjectList                // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:05 2005----------*/
qint64 CwnObjectAccess::LoadContainer( qint64 p_lDbId,
                                        QString p_qstrKeyname,
                                        CdmObjectContainer*& p_pContainer )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CwnCommandLoadContainer command(p_lDbId, p_qstrKeyname, true, m_rpCwnDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:11 2005----------*
 * @method  CwnObjectAccess::LockObject                    // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   bool & p_bResult                                 //                                   *
 * @comment This method locks objects on server side.                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:11 2005----------*/
qint64 CwnObjectAccess::LockObject( qint64 p_lSessionId,qint64 p_lObjectId, bool & p_bResult )
{
    p_bResult = false;
    CwnCommandLockObject command(p_lSessionId, p_lObjectId, m_rpCwnDataAccess);
   qint64 lRet  = command.Run();
    p_bResult = SUCCESSFULL(lRet);
    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:16 2005----------*
 * @method  CwnObjectAccess::IsObjectLocked                // protected                         *
 * @return qint64                                             // SessionId of the locker or 0 if object is not locked*
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment returns if a object is locked or not.                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:16 2005----------*/
qint64 CwnObjectAccess::IsObjectLocked( qint64 p_lObjectId,qint64 p_lSessionId )
{
    CwnCommandCheckObjectLocked command(p_lObjectId, p_lSessionId, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:22 2005----------*
 * @method  CwnObjectAccess::UnLockObject                  // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   bool & p_bResult                                 //                                   *
 * @comment This method unlocks objects on server side.                                           *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:22 2005----------*/
qint64 CwnObjectAccess::UnLockObject( qint64 p_lSessionId,qint64 p_lObjectId, bool & p_bResult )
{
    p_bResult = false;
    CwnCommandUnlockObject command(p_lSessionId, p_lObjectId, m_rpCwnDataAccess);
   qint64 lRet  = command.Run();
    p_bResult = SUCCESSFULL(lRet);
    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:03:26 2005----------*
 * @method  CwnObjectAccess::UpdateObject                  // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmObject*& p_pCdmObject                         //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment This method updates an object. It sends the object changes to server. on which it     *
 *          will be merged and resend. This object can be invalid or delted and receiving the     *
 *          new object data because a other user has deleted it.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 12:03:26 2005----------*/
qint64 CwnObjectAccess::UpdateObject(CdmObject*& p_pCdmObject,qint64 p_lSessionId)
{
    CwnCommandUpdateObject command(p_lSessionId, p_pCdmObject, m_rpCwnDataAccess);
    return command.Run();
}


/** +-=---------------------------------------------------------Mo 5. Sep 19:07:39 2005-----------*
 * @method  CwnObjectAccess::UpdateObjectList              // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   CdmObjectContainer*& p_pContainer                 //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment This method updates an object. It sends the object changes to server. on which it     *
 *          will be merged and resend. This object can be invalid or delted and receiving the     *
 *          new object data because a other user has deleted it.                                  *
 *----------------last changed: --------------------------------Mo 5. Sep 19:07:39 2005-----------*/
qint64 CwnObjectAccess::UpdateContainer(  CdmObjectContainer*& p_pContainer,qint64 p_lSessionId )
{
    CwnCommandUpdateContainer command(p_pContainer, p_lSessionId, m_rpCwnDataAccess);
    return command.Run();
}



/** +-=---------------------------------------------------------Sa 20. Aug 12:07:25 2005----------*
 * @method  CwnObjectAccess::ReadBinaryDocument            // public                            *
 * @return  int                                              //                                   *
 * @param   CdmValueBinaryDocument* p_pCdmBinaryDocument          //                                   *
 * @comment This method reads the BinaryDocument from database and set it to the local filesystem.*
 *----------------last changed: --------------------------------Sa 20. Aug 12:07:25 2005----------*/
QByteArray CwnObjectAccess::ReadBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    CwnCommandReadBinaryDocument command(p_pCdmBinaryDocument, m_rpCwnDataAccess);
    if (SUCCESSFULL(command.Run()))
    {
        return command.GetByteArray();
    }

    return QByteArray();
}

/** +-=---------------------------------------------------------Mo 5. Sep 19:30:15 2005-----------*
 * @method  CwnObjectAccess::UpdateBinaryDocument          // public, virtual                   *
 * @return  int                                              //                                   *
 * @param   CdmValueBinaryDocument* p_pCdmBinaryDocument          //                                   *
 * @comment This method updates the BinaryDocument on the database and synchronizes it to the     *
 *          local file.                                                                           *
 *----------------last changed: --------------------------------Mo 5. Sep 19:30:15 2005-----------*/
int CwnObjectAccess::UpdateBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    CwnCommandUpdateBinaryDocument command(p_pCdmBinaryDocument, m_rpCwnDataAccess);
    return command.Run();
}


/** +-=---------------------------------------------------------Do 10. Sep 17:53:51 2009----------*
 * @method  CwnObjectAccess::GetCounterValue               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmValueCounter* p_pCdmCounter                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Sep 17:53:51 2009----------*/
void CwnObjectAccess::GetCounterValue(CdmValueCounter* p_pCdmCounter)
{
   CwnCommandGetCounterValue command(p_pCdmCounter, m_rpCwnDataAccess);
   command.Run();
}


/** +-=---------------------------------------------------------Mi 15. Sep 17:05:22 2010----------*
 * @method  CdbObjectAccess::GetCounterValue               // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64# p_lDbId                                    //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lValueId                                  //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 15. Sep 17:05:22 2010----------*/
qint64 CwnObjectAccess::GetCounterValue(qint64,
                                       qint64 p_lObjectListId,
                                       qint64 p_lValueId,
                                        QString p_qstrKeyname)
{
    CwnCommandGetCounterValue command(p_lObjectListId, p_lValueId, p_qstrKeyname, m_rpCwnDataAccess);
    return command.Run();
}



/** +-=---------------------------------------------------------Mo 17. Sep 17:55:28 2007----------*
 * @method  CwnObjectAccess::IsObjectUsed                  // public                            *
 * @return  int                                              //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @comment This method returns if a object is used in a objectref or not.                        *
 *----------------last changed: --------------------------------Mo 17. Sep 17:55:28 2007----------*/
int CwnObjectAccess::IsObjectUsed(qint64 p_lObjectId,qint64 p_lObjectListId)
{
    CwnCommandCheckObjectUsed command(p_lObjectId, p_lObjectListId, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 8. Nov 10:57:29 2008-----------*
 * @method  CwnObjectAccess::RefreshObject                 // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment refreshes the values from the overgiven object.                                       *
 *----------------last changed: --------------------------------Sa 8. Nov 10:57:29 2008-----------*/
qint64 CwnObjectAccess::RefreshObject(CdmObject* p_pCdmObject)
{
    CwnCommandRefreshObject command(p_pCdmObject, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 8. Nov 10:59:01 2008-----------*
 * @method  CwnObjectAccess::RefreshObjectList             // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment refreshes the objects from the overgiven objectlist.                                  *
 *----------------last changed: --------------------------------Sa 8. Nov 10:59:01 2008-----------*/
qint64 CwnObjectAccess::RefreshObjectList(CdmObjectContainer* p_pContainer)
{
    CwnCommandRefreshContainer command(p_pContainer, m_rpCwnDataAccess);
    return command.Run();
}


/** +-=---------------------------------------------------------Sa 8. Nov 10:59:19 2008-----------*
 * @method  CwnObjectAccess::CountObjectsOnDb              // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment refreshes the objects from the overgiven objectlist.                                  *
 *----------------last changed: --------------------------------Sa 8. Nov 10:59:19 2008-----------*/
qint64 CwnObjectAccess::CountObjectsOnDb(CdmObjectContainer* p_pContainer)
{
    CwnCommandCountObjectsOnDb command(p_pContainer, m_rpCwnDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Do 8. Nov 11:18:37 2012-----------*
 * @method  CwnObjectAccess::GetReferences                 // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   QMap<qint64,qint64>& p_rqmReferences                // objectId/ObjectListId             *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 8. Nov 11:18:37 2012-----------*/
bool CwnObjectAccess::GetReferences(qint64 p_lObjectListId,
                                     qint64 p_lObjectId,
                                      QMap<qint64,
                                     qint64>& p_rqmReferences)
{
    CwnCommandGetObjectReferences command(p_lObjectListId, p_lObjectId, m_rpCwnDataAccess);
   qint64 lRet = command.Run();
    p_rqmReferences = command.GetResult();
    return SUCCESSFULL(lRet);
}

/** +-=---------------------------------------------------------Do 8. Nov 11:18:59 2012-----------*
 * @method  CwnObjectAccess::GetOwner                      // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64& p_lOwnerObjectListId                       //                                   *
 * @param  qint64& p_lOwnerObjectId                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 8. Nov 11:18:59 2012-----------*/
bool CwnObjectAccess::GetOwner(qint64 p_lObjectListId,
                                qint64& p_lOwnerObjectListId,
                                qint64& p_lOwnerObjectId)
{
    bool bRet = false;


    CwnCommandGetOwner command(p_lObjectListId, 0, m_rpCwnDataAccess);
    command.Run();

    p_lOwnerObjectListId = command.GetOwnerContainerId();
    p_lOwnerObjectId = command.GetOwnerObjectId();

    bRet = (p_lOwnerObjectId > 0 && p_lOwnerObjectListId > 0);

    return bRet;
}

/** +-=---------------------------------------------------------Do 8. Nov 11:19:21 2012-----------*
 * @method  CwnObjectAccess::GetOwner                      // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param  qint64& p_lOwnerObjectListId                       //                                   *
 * @param  qint64& p_lOwnerObjectId                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 8. Nov 11:19:21 2012-----------*/
bool CwnObjectAccess::GetOwner(qint64 p_lObjectListId,
                                qint64 p_lObjectId,
                                qint64& p_lOwnerObjectListId,
                                qint64& p_lOwnerObjectId)
{
    bool bRet = false;

    CwnCommandGetOwner command(p_lObjectListId, p_lObjectId, m_rpCwnDataAccess);
    command.Run();

    p_lOwnerObjectListId = command.GetOwnerContainerId();
    p_lOwnerObjectId = command.GetOwnerObjectId();

    bRet = (p_lOwnerObjectId > 0 && p_lOwnerObjectListId > 0);

    return bRet;
}
