#ifndef CDMOBJECTLIST_H
#define CDMOBJECTLIST_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QList>
#include <QVariant>

// own Includes
#include "CumAccessorRight.h"
#include "CdmRights.h"
#include "CdmModelElement.h"


// forwards
class QString;
class CdmClass;
class CdmContainerAdaptor;
class CdmJournalItem;
class CdmObject;

/* 
 * This class implements the managing object class
 * in the database. This class is a container for
 * objects of a specific class. Over this container
 * it is possible to access all objects
 */
class WMSMANAGER_API CdmObjectContainer : public CdmModelElement
{
    Q_OBJECT

    friend class CdmContainerManager;
    friend class CdmDataAccessHelper;
    friend class CdmContainerAdaptor;
    friend class CdmObject;

private:
    QMap<long,CdmObject*> m_qmObjects;
    CdmRights m_cCdmRights;

    /*
       * List of object factories which must be informed
       * by changes
       */
    QList<CdmContainerAdaptor*> m_qvlObjectFactories;
    long                          m_lClassId;
    QString                       m_qstrComment;
    bool                          m_bIsAccessorListModified;
    QList<CdmObject*>       m_qlNewModifiedObjects;
    QList<CdmObject*>       m_qlDeletedObjects;
    bool m_bIsTree;
    bool m_bImportMode;
    bool m_bIsImmutable;

private:
    CdmObjectContainer();
    CdmObjectContainer(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmClass* p_pCdmClass);
    CdmObjectContainer(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, long p_lClassId);
    CdmObjectContainer(long p_lId, CdmObjectContainer* p_pContainer);
    CdmObjectContainer(QVariantMap& p_rqvHash);
    virtual ~CdmObjectContainer();

public:
    void RemoveObjectLocalWithoutDelete(long p_lObjectId);
    int AddObject(CdmObject* p_pCdmObject);
    bool CheckReadAccess() const;
    bool CheckWriteAccess() const;
    CdmObject* CreateNewObject();
    long GetNewObjectId();
    long GetClassId() const;
    CdmObject* CopyObject(const CdmObject* p_pCdmObject);
    int DeleteObject(CdmObject* p_pCdmObject);
    int DeleteObject(long p_lObjectId);
    void GetObjectList(QList<CdmObject*>& p_rqvlObjects);
    const CdmRights& GetRights() const;
    virtual void ResetNewModified();
    QList<CdmObject*> GetDeletedList();
    QList<CdmObject*> GetNewModifiedList();
    void GetObjects(QList<long>&  p_rqllObjectIds, QList<CdmObject*>& p_rqllObjects);
    QVariant GetVariant() const;
    bool HasDeploymentRelevantOwner() const;
    void SetObjects(QVariantList& p_rqvObjects);
    void SetVariant(QVariantMap& p_rqvHash);
    bool IsDeploymentRelevant();
    QVariant GetContainerDataVariant() const;
    void SetVariantBaseData(QVariantMap& p_rqvHash);
    void Deploy(QVariantMap& p_rqvHash);
    CdmObject* FindObjectByKeyname(QString p_qstrKeyname);
    void SetImportMode(bool p_bMode);
    QVariant GetVariantComplete() const;
    bool IsExactTypeOf(QString p_qstrClassName) const;
    bool IsExactTypeOf(CdmClass *p_pClass) const;
    QString GetConfig() const;
    void SetConfig(QString p_qstrConfig);
    bool IsImmutable() const;
    void SetImmutable(bool p_bImmutable);
    bool IsTechnicalDeploymentRelevant() const;
    bool IsTree() const;
    void SetTree(bool p_bTree);
    void GetChanges(QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqllChanges);
    void GetChanges(QList<CdmJournalItem*>& p_rqllChanges);
    CdmObject* GetOwner() const;
    virtual bool IsContainer() const;
    bool HasOwner();
    bool IsTypeOf(CdmClass* p_pClass) const;
    CdmObject* CreateNewObject(QString p_qstrKeyname);
    void SetAllLocalObjectsDeleted();
    void SetDeleted();
    CdmObject* FindObjectByIndex(int p_iIndex);
    void DeleteAllObjects();
    long LoadObjects(const QList<long>& p_rqvlObjectIds, bool p_bWithChildren = true);
    void ClearContainerLocal();
    void RemoveObjectLocal(long p_lObjectId);
    void CopyObjects(CdmObjectContainer* p_pContainerSource);
    int MoveObjectsTo(CdmObjectContainer *p_pDestContainer);
    void GetObjectList(QList<long>& p_rqvlObjects);
    virtual QString GetInfo() const;
    bool IsTypeOf(QString p_qstrClassName) const;
    long CountModifiedObjects() const;
    long CountObjectsOnDb();
    CdmObject* FindObjectById(long p_lObjectId);
    int Commit();
    const CdmClass* GetClass() const;
    CdmObject* FindObjectByIdLocal(long p_lObjectId);
    void SetComment(QString p_qstrComment);
    QString GetComment() const;
    void AddAccessorRight(long p_lUserId, EdmRight p_eUmAccessRight);
    void RemoveAccessorRight(long p_lUserId);
    void UpdateAccessorRight(long p_lUserId, EdmRight p_eUmAccessRight);
    bool IsAccessorListModified() const;
    void RemoveObjectFactory(CdmContainerAdaptor* p_pCdmObjectFactory );
    void AddObjectFactory(CdmContainerAdaptor* p_pCdmObjectFactory );
    long CountObjects() const;
    long Refresh();
    QMap<int, EdmRight> GetAccessorMap() const;
    CdmObject *CreateObject(long p_lObjectId);
    QList<CdmContainerAdaptor *> GetObjectFactoryList();
protected:
    virtual void SetModified();


public slots:
    void ObjectModifiedSlot(CdmObject* p_pCdmObject);
    void ObjectCommitedSlot(int p_iId);
    void ObjectDeletedSlot(CdmObject* p_pCdmObject);
    void ObjectRefModifiedSlot(CdmObject* p_pCdmObject);

public:
    // Call may be necessary after reloading the container from the databasr
    // Use method only if you know what you do
    void TriggerObjectCommittedEventAfterDbReload();

private:
    void CopyRights(CdmObjectContainer* p_pCdmSourceObjectList);
    void LoadChildrenObjects(const QList<long>& p_rqvlObjectIds);
    void LoadObjectRefs(QMap<long,long>& p_rqmObjectRefs);
    void UpdateFactoriesObjectModified();
    bool IsDeploymentObjectKeynameValid(QString &p_rqstrKeyname);
    void RefreshObjectKeyname(CdmObject *pObject);
    void CommitDeleteObjects();
    void CommitUpdateObjects();
    int CommitDeleteContainer();
    int CommitUpdateContainer();
};

#endif
