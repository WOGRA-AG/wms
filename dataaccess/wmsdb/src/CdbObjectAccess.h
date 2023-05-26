#ifndef CODBCOBJECTACCESS_H
#define CODBCOBJECTACCESS_H

// own Includes
#include "CdbDataAccess.h"

// forwards
class CdmObject;
class CdmObjectContainer;
class CdmQuery;
class CdmValue;
class CdmValueBinaryDocument;
class CdmValueBool;
class CdmValueCharacterDocument;
class CdmValueContainerRef;
class CdmValueCounter;
class CdmValueDate;
class CdmValueDateTime;
class CdmValueDouble;
class CdmValueFloat;
class CdmValueInt;
class CdmValueLong;
class CdmValueObjectRef;
class CdmValueString;
class CdmValueTime;

/** 
  * This class manages the object access over
  * the database. All objects queries will be done here.
  */
class WMSDB_API CdbObjectAccess
{
protected:
    /*
       * The dataaccess
       */
    CdbDataAccess* m_rpCdbDataAccess;

    /*
       * The new obejct counter
       */
    int m_iNewObjectCounter;

    /*
       * The newobjectlistcounter
       */
    int m_iNewObjectListCounter;

    /*
       * map of locked objects <ObjectId, SessionId>
       */
    QMap<int,int> m_qmLockedObjects;

public:
    CdbObjectAccess(CdbDataAccess* p_pCdbDataAccess);
    virtual ~CdbObjectAccess();
    virtual qint64 DeleteObjectList(qint64 p_lObjectListId);
    qint64 ExecuteQuery(CdmQuery* p_pCdmQuery);
    qint64 ExistContainer(qint64 p_lClassId, QString p_qstrObjectListKeyname);
    virtual qint64 GetNewObjectId( qint64 p_lObjectListId,qint64 p_lSessionId);
    virtual qint64 GetNewContainerId(qint64 p_lClassId,qint64 p_lSessionId);
    qint64 GetContainerList(qint64 p_lDbId,qint64 p_lClassId, QMap<qint64,QString>& p_rqmObjectListsList);
    qint64 LoadObject(qint64 p_lObjectListId,qint64 p_lObjectId, CdmObject*& p_pCdmObject);
    qint64 LoadContainer(qint64 p_lObjectListId, CdmObjectContainer*& p_pContainer);
    qint64 LockObject(qint64 p_lSessionId,qint64 p_lObjectId, bool & p_bResult);
    qint64 UnLockObject(qint64 p_lSessionId,qint64 p_lObjectId, bool & p_bResult);
    qint64 UpdateObject(CdmObject*& p_pCdmObject,qint64 p_lSessionId);
    virtual qint64 UpdateContainer(CdmObjectContainer*& p_pContainer,qint64 p_lSessionId);
    qint64 LoadEmptyContainer(qint64 p_lDbId,qint64 p_lId, CdmObjectContainer*& p_pContainer);
    qint64 LoadObjects(CdmObjectContainer* p_pContainer, QList<qint64>& p_rqvlObjectIds);
    int IsObjectUsed(qint64 p_lObjectId,qint64 p_lObjectListId);
    virtual qint64 CountObjectsOnDb(CdmObjectContainer* p_pContainer);
    virtual qint64 RefreshContainer(CdmObjectContainer* p_pContainer);
    virtual qint64 RefreshObject(CdmObject* p_pCdmObject);
    qint64 LoadContainer( qint64 p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer );
    qint64 LoadEmptyContainer( qint64 p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer );
    QByteArray ReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument);
    virtual int UpdateBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument );
    virtual qint64 GetCounterValue(CdmValueCounter* p_pCdmCounter);
    virtual bool GetReferences(qint64 p_lObjectListId,
                               qint64 p_lObjectId,
                               QMap<qint64,
                               qint64>& p_rqmReferences);
    virtual bool GetOwner(qint64 p_lObjectListId,qint64& p_lOwnerObjectListId,qint64& p_lOwnerObjectId);
    virtual bool GetOwner(qint64 p_lObjectListId,
                          qint64 p_lObjectId,
                          qint64& p_lOwnerObjectListId,
                          qint64& p_lOwnerObjectId);
    qint64 LoadObject(qint64 p_lObjectListId, QString p_qstrKeyname, CdmObject *&p_pCdmObject);

protected:
    virtual qint64 DeleteObject(qint64 p_lObjectId,qint64 p_lSessionId);
    qint64 IsObjectLocked(qint64 p_lObjectId,qint64 p_lSessionId);
    qint64 UpdateRights(CdmObjectContainer*& p_pContainer);

private:
    qint64 LoadObjectListRights(CdmObjectContainer*& p_pContainer);
    qint64 FindObjectIdToObjectList(qint64 p_lDbId,
                                    QString p_qstrKeynameObjectList,
                                    QList<qint64>& p_rqvlIds);
    qint64 UpdateObjects(CdmObjectContainer* p_pContainer,
                         QList<CdmObject*>& p_rqlObjects,
                         qint64 p_lSessionId);
    qint64 DeleteObjects(CdmObjectContainer* p_pContainer,
                         QList<CdmObject*>& p_rqlObjects,
                         qint64 p_lSessionId);
};

#endif //
