/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
  ******************************************************************************/

#ifndef CODBCOBJECTACCESS_H
#define CODBCOBJECTACCESS_H

// System and QT Includes
#include <QMap>
#include <QList>


// own Includes
#include "CdmLocatedElement.h"
#include "CftlDataAccess.h"


// forwards
class CftlDataAccess;
class CdmQuery;
class CdmObject;
class CdmObjectContainer;
class CdmValueBool;
class CdmValueInt;
class CdmValueFloat;
class CdmValueLong;
class CdmValueDouble;
class CdmValueString;
class CdmValueObjectRef;
class CdmValueContainerRef;
class CdmValueCharacterDocument;
class CdmValueBinaryDocument;
class CdmValueCounter;
class CdmValueDate;
class CdmValueTime;
class CdmValueDateTime;
class CdmValue;



/** 
  * This class manages the object access over
  * the database. All objects queries will be done here.
  */
class CftlObjectAccess
{
protected:
    /*
       * The dataaccess
       */
    CftlDataAccess* m_rpCftlDataAccess;

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
    CftlObjectAccess(CftlDataAccess* p_pCftlDataAccess);
    virtual ~CftlObjectAccess();
    virtual qint64 DeleteObjectList(qint64 p_lObjectListId);
   qint64 ExecuteQuery(CdmQuery* p_pCdmQuery);
   qint64 ExistObjectList(qint64 p_lClassId, QString p_qstrObjectListKeyname);
    virtual qint64 GetNewObjectId(const CdmObjectContainer* p_pContainer);
    virtual qint64 GetNewContainerId(qint64 p_lClassId);
   qint64 GetObjectListsList(qint64 p_lDbId,qint64 p_lClassId, QMap<qint64,QString>& p_rqmObjectListsList);
   qint64 LoadObject(const CdmObjectContainer* p_pContainer,qint64 p_lObjectId, CdmObject*& p_pCdmObject);
   qint64 LoadObjectList(qint64 p_lObjectListId, CdmObjectContainer*& p_pContainer);
   qint64 LockObject(CdmObject* p_pObject, bool & p_bResult);
   qint64 UnLockObject(CdmObject* p_pObject, bool & p_bResult );
   qint64 UpdateObject(CdmObject*& p_pCdmObject);
    virtual qint64 UpdateContainer(CdmObjectContainer*& p_pContainer);
    virtual void GetCounterValue(CdmValueCounter* p_pCdmCounter);
    virtual bool GetReferences(qint64 p_lObjectListId,
                              qint64 p_lObjectId,
                               QMap<qint64,
                              qint64>& p_rqmReferences);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject *&p_pOwnerObject);
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject *&p_pOwnerObject);
   qint64 LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
   qint64 LoadObjectList(qint64 p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
   qint64 LoadEmptyObjectList(qint64 p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    QByteArray ReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument);
    virtual int UpdateBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument);
    virtual qint64 GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);

   qint64 LoadEmptyObjectList(qint64 p_lDbId,qint64 p_lId, CdmObjectContainer*& p_pContainer);
   qint64 LoadObjects(CdmObjectContainer* p_pContainer, QList<qint64>& p_rqvlObjectIds);
    int IsObjectUsed(const CdmObject* p_pObject);
    virtual qint64 CountObjectsOnDb(CdmObjectContainer* p_pContainer);
    virtual qint64 RefreshObjectList(CdmObjectContainer* p_pContainer);
    virtual qint64 RefreshObject(CdmObject* p_pCdmObject);
    virtual qint64 DeleteObject(CdmObject* p_pObject);
   qint64 IsObjectLocked(CdmObject* p_pObject);

private:
    CdmObject *GetObject(qint64 p_lContainerId,qint64 p_lObjectId);
};

#endif //
