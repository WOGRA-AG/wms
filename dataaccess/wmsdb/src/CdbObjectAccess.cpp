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

CdbObjectAccess::CdbObjectAccess(CdbDataAccess* p_pCdbDataAccess)
   : m_rpCdbDataAccess(p_pCdbDataAccess),
     m_iNewObjectCounter(0),
     m_iNewObjectListCounter(0)
{
   // nothing to do at the moment
}

CdbObjectAccess::~CdbObjectAccess(  )
{
   // nothing to do at the moment
}

qint64 CdbObjectAccess::DeleteObjectList(qint64 p_lObjectListId)
{
    CdbCommandDeleteContainer command(p_lObjectListId, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::DeleteObject(qint64 p_lObjectId,qint64 p_lSessionId)
{
   CdbCommandDeleteObject command(p_lObjectId, p_lSessionId, m_rpCdbDataAccess);
   return command.Run();
}

qint64 CdbObjectAccess::ExecuteQuery(CdmQuery* p_pCdmQuery)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

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

qint64 CdbObjectAccess::ExistContainer( qint64 p_lClassId, QString p_qstrObjectListKeyname )
{
   Q_UNUSED(p_lClassId)
   CdbCommandExistContainer command(p_qstrObjectListKeyname, m_rpCdbDataAccess);
   return command.Run();
}

qint64 CdbObjectAccess::GetNewObjectId(qint64 p_lObjectListId,qint64 p_lSessionId)
{
    CdbCommandGetNewObjectId command(p_lObjectListId, p_lSessionId, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::GetNewContainerId( qint64 p_lClassId,qint64 p_lSessionId )
{
   CdbCommandGetNewContainerId command(p_lClassId, p_lSessionId, m_rpCdbDataAccess);
   return command.Run();
}

qint64 CdbObjectAccess::GetContainerList( qint64 p_lDbId,
                                           qint64 p_lClassId,
                                            QMap<qint64,
                                           QString>& p_rqmObjectListsList )
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   CdbCommandGetContainerList command(p_lDbId, p_lClassId, m_rpCdbDataAccess);
   lRet = command.Run();
   command.GetResult(p_rqmObjectListsList);
   BODY_CATCH

   return lRet;
}

qint64 CdbObjectAccess::LoadObjects(CdmObjectContainer* p_pContainer,
                                    QList<qint64>& p_rqvlObjectIds)
{
    CdbCommandLoadObjects command(p_pContainer, p_rqvlObjectIds, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::LoadObject(qint64 p_lObjectListId,
                                qint64 p_lObjectId,
                                 CdmObject*& p_pCdmObject )
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

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

qint64 CdbObjectAccess::LoadObject(qint64 p_lObjectListId,
                                 QString p_qstrKeyname,
                                 CdmObject*& p_pCdmObject)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

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

qint64 CdbObjectAccess::LoadContainer(qint64 p_lObjectListId, CdmObjectContainer*& p_pContainer)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

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

qint64 CdbObjectAccess::LoadEmptyContainer( qint64 p_lDbId,
                                             QString p_qstrKeyname,
                                             CdmObjectContainer*& p_pContainer )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

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

qint64 CdbObjectAccess::LoadEmptyContainer(qint64 p_lDbId,
                                         qint64 p_lId,
                                          CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
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

qint64 CdbObjectAccess::LoadContainer( qint64 p_lDbId,
                                        QString p_qstrKeyname,
                                        CdmObjectContainer*& p_pContainer )
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

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

qint64 CdbObjectAccess::LockObject( qint64 p_lSessionId,qint64 p_lObjectId, bool & p_bResult )
{
   p_bResult = false;
   CdbCommandLockObject command(p_lSessionId, p_lObjectId, m_rpCdbDataAccess);
  qint64 lRet  = command.Run();
   p_bResult = SUCCESSFULL(lRet);
   return lRet;
}

qint64 CdbObjectAccess::IsObjectLocked( qint64 p_lObjectId,qint64 p_lSessionId )
{
    CdbCommandCheckObjectLocked command(p_lObjectId, p_lSessionId, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::UnLockObject( qint64 p_lSessionId,qint64 p_lObjectId, bool & p_bResult )
{
    p_bResult = false;
    CdbCommandUnlockObject command(p_lSessionId, p_lObjectId, m_rpCdbDataAccess);
    qint64 lRet  = command.Run();
    p_bResult = SUCCESSFULL(lRet);
    return lRet;
}

qint64 CdbObjectAccess::UpdateObject(CdmObject*& p_pCdmObject,qint64 p_lSessionId)
{
    CdbCommandUpdateObject command(p_lSessionId, p_pCdmObject, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::UpdateContainer(  CdmObjectContainer*& p_pContainer,qint64 p_lSessionId )
{
    CdbCommandUpdateContainer command(p_pContainer, p_lSessionId, m_rpCdbDataAccess);
    return command.Run();
}

QByteArray CdbObjectAccess::ReadBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    CdbCommandReadBinaryDocument command(p_pCdmBinaryDocument, m_rpCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        return command.GetByteArray();
    }

    return QByteArray();
}

int CdbObjectAccess::UpdateBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    CdbCommandUpdateBinaryDocument command(p_pCdmBinaryDocument, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::GetCounterValue(CdmValueCounter* p_pCdmCounter)
{
   CdbCommandGetCounterValue command(p_pCdmCounter, m_rpCdbDataAccess);
   command.Run();
   return p_pCdmCounter->GetValue();
}

int CdbObjectAccess::IsObjectUsed(qint64 p_lObjectId,qint64 p_lObjectListId)
{
    CdbCommandCheckObjectUsed command(p_lObjectId, p_lObjectListId, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::RefreshObject(CdmObject* p_pCdmObject)
{
    CdbCommandRefreshObject command(p_pCdmObject, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::RefreshContainer(CdmObjectContainer* p_pContainer)
{
    CdbCommandRefreshComtainer command(p_pContainer, m_rpCdbDataAccess);
    return command.Run();
}

qint64 CdbObjectAccess::CountObjectsOnDb(CdmObjectContainer* p_pContainer)
{
   CdbCommandCountObjectsOnDb command(p_pContainer, m_rpCdbDataAccess);
   return command.Run();
}

bool CdbObjectAccess::GetReferences(qint64 p_lObjectListId,
                                     qint64 p_lObjectId,
                                      QMap<qint64,
                                     qint64>& p_rqmReferences)
{
   CdbCommandGetObjectReferences command(p_lObjectListId, p_lObjectId, m_rpCdbDataAccess);
  qint64 lRet = command.Run();
   p_rqmReferences = command.GetResult();
   return SUCCESSFULL(lRet);
}

bool CdbObjectAccess::GetOwner(qint64 p_lObjectListId,
                                qint64& p_lOwnerObjectListId,
                                qint64& p_lOwnerObjectId)
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

bool CdbObjectAccess::GetOwner(qint64 p_lObjectListId,
                                qint64 p_lObjectId,
                                qint64& p_lOwnerObjectListId,
                                qint64& p_lOwnerObjectId)
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
