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
    virtual long DeleteObjectList(long p_lObjectListId);
    long ExecuteQuery(CdmQuery* p_pCdmQuery);
    long ExistObjectList(long p_lClassId, QString p_qstrObjectListKeyname);
    virtual long GetNewObjectId(const CdmObjectContainer* p_pContainer);
    virtual long GetNewContainerId(long p_lClassId);
    long GetObjectListsList(long p_lDbId, long p_lClassId, QMap<long,QString>& p_rqmObjectListsList);
    long LoadObject(const CdmObjectContainer* p_pContainer, long p_lObjectId, CdmObject*& p_pCdmObject);
    long LoadObjectList(long p_lObjectListId, CdmObjectContainer*& p_pContainer);
    long LockObject(CdmObject* p_pObject, bool & p_bResult);
    long UnLockObject(CdmObject* p_pObject, bool & p_bResult );
    long UpdateObject(CdmObject*& p_pCdmObject);
    virtual long UpdateContainer(CdmObjectContainer*& p_pContainer);
    virtual void GetCounterValue(CdmValueCounter* p_pCdmCounter);
    virtual bool GetReferences(long p_lObjectListId,
                               long p_lObjectId,
                               QMap<long,
                               long>& p_rqmReferences);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject *&p_pOwnerObject);
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject *&p_pOwnerObject);
    long LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
    long LoadObjectList(long p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    long LoadEmptyObjectList(long p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    QByteArray ReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument);
    virtual int UpdateBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument);
    virtual long GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);

    long LoadEmptyObjectList(long p_lDbId, long p_lId, CdmObjectContainer*& p_pContainer);
    long LoadObjects(CdmObjectContainer* p_pContainer, QList<long>& p_rqvlObjectIds);
    int IsObjectUsed(const CdmObject* p_pObject);
    virtual long CountObjectsOnDb(CdmObjectContainer* p_pContainer);
    virtual long RefreshObjectList(CdmObjectContainer* p_pContainer);
    virtual long RefreshObject(CdmObject* p_pCdmObject);
    virtual long DeleteObject(CdmObject* p_pObject);
    long IsObjectLocked(CdmObject* p_pObject);

private:
    CdmObject *GetObject(long p_lContainerId, long p_lObjectId);
};

#endif //
