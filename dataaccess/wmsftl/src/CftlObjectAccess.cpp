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
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QFileInfo>
#include <QSqlError>
#include <QList>
#include <QTime>


#ifdef WIN32
#include <qt_windows.h>
#undef GetObject
#else
#include <unistd.h>
#endif //

// WMS includes
#include "CdmSessionManager.h"
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
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"

// own Includes
#include "CftlCommandUpdateContainer.h"
#include "CftlCommandReadBinaryDocument.h"
#include "CftlCommandDeleteContainer.h"
#include "CftlCommandCheckObjectLocked.h"
#include "CftlCommandDeleteObject.h"
#include "CftlCommandExistContainer.h"
#include "CftlCommandGetNewObjectId.h"
#include "CftlCommandUpdateObject.h"
#include "CftlCommandGetNewContainerId.h"
#include "CftlCommandGetContainerList.h"
#include "CftlCommandLoadObjects.h"
#include "CftlCommandRefreshObject.h"
#include "CftlCommandLoadContainer.h"
#include "CftlCommandUpdateBinaryDocument.h"
#include "CftlCommandRefreshComtainer.h"
#include "CftlCommandCountObjectsOnDb.h"
#include "CftlCommandLockObject.h"
#include "CftlCommandGetOwner.h"
#include "CftlCommandUnlockObject.h"
#include "CftlCommandCheckObjectUsed.h"
#include "CftlCommandLoadSingleObject.h"
#include "CftlCommandGetCounterValue.h"
#include "CftlCommandGetObjectReferences.h"
#include "CwmsUtilities.h"
#include "CftlCommandQuery.h"
#include "CftlCommandQueryElement.h"
#include "CftlObjectAccess.h"
#include "CftlJournal.h"
#include "CftlDataAccess.h"

#define MAXLOCKTRIALS 20
#define BINARYBLOCK 10000

CftlObjectAccess::CftlObjectAccess(CftlDataAccess* p_pCftlDataAccess)
   : m_rpCftlDataAccess(p_pCftlDataAccess),
     m_iNewObjectCounter(0),
     m_iNewObjectListCounter(0)
{
   // nothing to do at the moment
}

CftlObjectAccess::~CftlObjectAccess(  )
{
   // nothing to do at the moment
}

qint64 CftlObjectAccess::DeleteObjectList(qint64 p_lObjectListId)
{
    CftlCommandDeleteContainer command(p_lObjectListId, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::DeleteObject(CdmObject* p_pObject)
{
   CftlCommandDeleteObject command(p_pObject, m_rpCftlDataAccess);
   return command.Run();
}

qint64 CftlObjectAccess::ExecuteQuery(CdmQuery* p_pCdmQuery)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpCftlDataAccess) && CHKPTR(p_pCdmQuery))
   {
      lRet = CftlCommandQuery::Execute(m_rpCftlDataAccess, p_pCdmQuery);
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CftlObjectAccess::ExistObjectList(qint64 p_lClassId, QString p_qstrObjectListKeyname)
{
    Q_UNUSED(p_lClassId);
   CftlCommandExistContainer command(p_qstrObjectListKeyname, m_rpCftlDataAccess);
   return command.Run();
}

qint64 CftlObjectAccess::GetNewObjectId(const CdmObjectContainer* p_pContainer)
{
    CftlCommandGetNewObjectId command(p_pContainer, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::GetNewContainerId(qint64 p_lClassId)
{
   CftlCommandGetNewContainerId command(p_lClassId,  m_rpCftlDataAccess);
   return command.Run();
}

qint64 CftlObjectAccess::GetObjectListsList( qint64 p_lDbId,
                                           qint64 p_lClassId,
                                            QMap<qint64,
                                           QString>& p_rqmObjectListsList )
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   CftlCommandGetContainerList command(p_lDbId, p_lClassId, m_rpCftlDataAccess);
   lRet = command.Run();
   command.GetResult(p_rqmObjectListsList);
   return lRet;
}

qint64 CftlObjectAccess::LoadObjects(CdmObjectContainer* p_pContainer,
                                    QList<qint64>& p_rqvlObjectIds)
{
    CftlCommandLoadObjects command(p_pContainer, p_rqvlObjectIds, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::LoadObject(const CdmObjectContainer* p_pContainer,
                                 qint64 p_lObjectId,
                                  CdmObject*& p_pCdmObject)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   CftlCommandLoadSingleObject command(const_cast<CdmObjectContainer*>(p_pContainer), p_lObjectId, m_rpCftlDataAccess);
   lRet = command.Run();

   if (p_pCdmObject)
   {
       ERR("Object must be null!");
   }

   p_pCdmObject = command.GetResult();
   return lRet;
}

qint64 CftlObjectAccess::LoadObject(const CdmObjectContainer* p_pContainer,
                                  QString p_qstrKeyname,
                                  CdmObject*& p_pCdmObject)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   CftlCommandLoadSingleObject command(const_cast<CdmObjectContainer*>(p_pContainer), p_qstrKeyname, m_rpCftlDataAccess);
   lRet = command.Run();

   if (p_pCdmObject)
   {
       ERR("Object must be null!");
   }

   p_pCdmObject = command.GetResult();
   return lRet;
}

qint64 CftlObjectAccess::LoadObjectList(qint64 p_lObjectListId, CdmObjectContainer*& p_pContainer)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if (p_pContainer)
   {
       CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
   }

   CftlCommandLoadContainer command(p_lObjectListId, true, m_rpCftlDataAccess);
   lRet = command.Run();
   p_pContainer = command.GetResult();

   return lRet;
}

qint64 CftlObjectAccess::LoadEmptyObjectList(qint64 p_lDbId,
                                           QString p_qstrKeyname,
                                           CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CftlCommandLoadContainer command(p_lDbId, p_qstrKeyname, false, m_rpCftlDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;
}

qint64 CftlObjectAccess::LoadEmptyObjectList(qint64 p_lDbId,
                                         qint64 p_lId,
                                          CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    Q_UNUSED(p_lDbId);

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CftlCommandLoadContainer command(p_lId, false, m_rpCftlDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;
}

qint64 CftlObjectAccess::LoadObjectList(qint64 p_lDbId,
                                      QString p_qstrKeyname,
                                      CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (p_pContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(p_pContainer);
    }

    CftlCommandLoadContainer command(p_lDbId, p_qstrKeyname, true, m_rpCftlDataAccess);
    lRet = command.Run();
    p_pContainer = command.GetResult();

    return lRet;
}

qint64 CftlObjectAccess::LockObject(CdmObject* p_pObject, bool & p_bResult )
{
   p_bResult = false;
   CftlCommandLockObject command(p_pObject, m_rpCftlDataAccess);
  qint64 lRet  = command.Run();
   p_bResult = SUCCESSFULL(lRet);
   return lRet;
}

qint64 CftlObjectAccess::IsObjectLocked(CdmObject* p_pObject)
{
    CftlCommandCheckObjectLocked command(p_pObject, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::UnLockObject(CdmObject* p_pObject, bool & p_bResult )
{
    p_bResult = false;
    CftlCommandUnlockObject command(p_pObject, m_rpCftlDataAccess);
   qint64 lRet  = command.Run();
    p_bResult = SUCCESSFULL(lRet);
    return lRet;
}

qint64 CftlObjectAccess::UpdateObject(CdmObject*& p_pCdmObject)
{
    CftlCommandUpdateObject command(p_pCdmObject, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::UpdateContainer(CdmObjectContainer*& p_pContainer)
{
    CftlCommandUpdateContainer command(p_pContainer, m_rpCftlDataAccess);
   return command.Run();
}

QByteArray CftlObjectAccess::ReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument)
{
    CftlCommandReadBinaryDocument command(p_pCdmBinaryDocument, m_rpCftlDataAccess);
    if (SUCCESSFULL(command.Run()))
    {
        return command.GetByteArray();
    }

    return QByteArray();
}

int CftlObjectAccess::UpdateBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument)
{
    CftlCommandUpdateBinaryDocument command(p_pCdmBinaryDocument, m_rpCftlDataAccess);
   return command.Run();
}

void CftlObjectAccess::GetCounterValue(CdmValueCounter* p_pCdmCounter)
{
   CftlCommandGetCounterValue command(p_pCdmCounter, m_rpCftlDataAccess);
   command.Run();
}

qint64 CftlObjectAccess::GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue)
{
    CftlCommandGetCounterValue command(p_pContainer, p_pValue, m_rpCftlDataAccess);
    return command.Run();
}

int CftlObjectAccess::IsObjectUsed(const CdmObject* p_pObject)
{
    CftlCommandCheckObjectUsed command(p_pObject, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::RefreshObject(CdmObject* p_pCdmObject)
{
    CftlCommandRefreshObject command(p_pCdmObject, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::RefreshObjectList(CdmObjectContainer* p_pContainer)
{
    CftlCommandRefreshComtainer command(p_pContainer, m_rpCftlDataAccess);
    return command.Run();
}

qint64 CftlObjectAccess::CountObjectsOnDb(CdmObjectContainer* p_pContainer)
{
   CftlCommandCountObjectsOnDb command(p_pContainer, m_rpCftlDataAccess);
   return command.Run();
}

bool CftlObjectAccess::GetReferences(qint64 p_lObjectListId,
                                     qint64 p_lObjectId,
                                      QMap<qint64,
                                     qint64>& p_rqmReferences)
{
   CftlCommandGetObjectReferences command(p_lObjectListId, p_lObjectId, m_rpCftlDataAccess);
  qint64 lRet = command.Run();
   p_rqmReferences = command.GetResult();
   return SUCCESSFULL(lRet);
}

bool CftlObjectAccess::GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject)
{
   bool bRet = false;


   CftlCommandGetOwner command(p_pContainer, m_rpCftlDataAccess);
   command.Run();

  qint64 lOwnerObjectListId = command.GetOwnerContainerId();
  qint64 lOwnerObjectId = command.GetOwnerObjectId();
   p_pOwnerObject = nullptr;

   if (lOwnerObjectId > 0 && lOwnerObjectListId > 0)
   {
    p_pOwnerObject = GetObject(lOwnerObjectListId, lOwnerObjectId);
   }

   bRet = (p_pOwnerObject != nullptr);

   return bRet;
}

CdmObject* CftlObjectAccess::GetObject(qint64 p_lContainerId,qint64 p_lObjectId)
{
    CdmObject* pObject = nullptr;
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        CdmContainerManager* pContainerManager = pDataProvider->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pObject = pContainerManager->FindObject(p_lContainerId, p_lObjectId);
        }
    }

    return pObject;
}


bool CftlObjectAccess::GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject)
{
   bool bRet = false;

   CftlCommandGetOwner command(p_pObject, m_rpCftlDataAccess);
   command.Run();

  qint64 lOwnerObjectListId = command.GetOwnerContainerId();
  qint64 lOwnerObjectId = command.GetOwnerObjectId();

   p_pOwnerObject = GetObject(lOwnerObjectListId, lOwnerObjectId);
   bRet = (p_pOwnerObject != nullptr);

   return bRet;
}
