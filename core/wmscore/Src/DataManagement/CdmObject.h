#ifndef CDMOBJECT_H
#define CDMOBJECT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <qmap.h>
#include <qpointer.h>
#include <QVariant>

// own Includes
#include "CdmModelElement.h"
#include "CdmLocatedElement.h"

// forwards
class QString;
class QTimer;
class CdmClass;
class CdmValue;
class CdmJournalItem;
class CdmMember;
class CdmObjectContainer;

class WMSMANAGER_API CdmObject : public CdmModelElement
{
    Q_OBJECT

    friend class CdmObjectContainer;
    friend class CdmQueryElement;
    friend class CdmDataAccessHelper;

private:
    int                        m_iValueIdCounter;
    QMap<QString,CdmValue*>    m_qmValues;
    long                       m_lClassId;
    CdmObjectContainer*        m_rpContainer;
    mutable long               m_lContainerId;
    bool                       m_bIsInitialized;
    long                       m_lParentId;
    bool                       m_bIsImmutable;
    bool                       m_bCommitRunning;
    mutable QPointer<CdmClass> m_rpClass = {};

private:
    CdmObject(QVariantMap& p_rqvHash);
    CdmObject(CdmObjectContainer* p_pContainer, CdmObject* p_pCdmObject, long p_lId);
    CdmObject(long p_lDatbaseId,
              long p_lId,
              QString p_qstrKeyname,
              long p_lClassId,
              CdmObjectContainer* p_pContainer);

    CdmObject(long p_lDatbaseId, long p_lId, long p_lClassId, long p_lObjectListId);
    CdmObject(const CdmObject& p_rCdmObject, long p_lId);
    CdmObject(long p_lDatbaseId,
              long p_lId,
              QString p_qstrKeyname,
              const CdmClass* p_pCdmClass,
              CdmObjectContainer* p_pContainer);
    CdmObject();
    virtual ~CdmObject();

public:
    void Deploy(QVariantMap& p_rqvHash);
    void DeployValues(QVariantMap& p_rqvHash);
    void SetObjectContainer(CdmObjectContainer* p_pContainer);
    void SetObjectContainer(long lObjectContainerId);
    QString GetUri() const;
    int SetValue(const wchar_t* p_pKeyname, const double p_dValue);
    void ClearValuesFromObject();
    CdmValue* GetEventValue(const QString& p_qstrKeyname, CdmObject *pEventObject);
    QString GetDisplayString(QString p_qstrKeyname) const;
    virtual QVariant GetVariant(QString p_qstrKeyname) const;
    void CheckAllValuesCreated();
    void SetValue(QString p_qstrKeyname, QVariant p_qvValue);
    virtual QVariant GetVariant() const;
    void SetValues(QVariantMap& p_rqvHash);
    void SetVariant(QVariantMap& p_rqvHash);
    void SetParentObject(CdmObject* p_pCdmObject);
    void SetParent(long p_lObjectId);
    void ClearPersistentValuesFromObject();
    bool IsExactTypeOf(QString p_qstrClassName) const;
    bool IsExactTypeOf(CdmClass *p_pClass) const;
    QString GetConfig() const;
    void SetConfig(QString p_qstrConfig);
    void SetImmutable(bool p_bImmutable);
    bool IsImmutable() const;
    bool IsReadOnly() const;
    QString GetUriInternal() const;
    void CopyValuesFromObjectToEventObject(CdmObject *pEventObject);
    void CopyObjectValueToEventValueWithEventObjectStarting(CdmObject *pEventObject);
    void CopyObjectValueToEventValueWithObjectStarting(CdmObject *pEventObject);
    void CopyObjectValuesToEventObjectValues(CdmObject *pEventObject);
    CdmObjectContainer* getValueObjectContainer();
    CdmClass* GetClass() const;
    CdmValue* GetValue(const QString& p_qstrKeyname);
    int GetValue(const QString& p_qstrKeyname, QString& p_qstrValue);
    int SetValue(const QString& p_qstrKeyname, const QString p_qstrValue);
    int GetValue(const QString& p_qstrKeyname, bool& p_bValue);
    int SetValue(const QString& p_qstrKeyname, bool p_bValue);
    int SetValue(const QString& p_qstrKeyname, const QDate& p_rqdValue);
    int GetValue(const QString& p_qstrKeyname, QDate& p_rqdValue);
    int GetValue(const QString& p_rqstrKeyname, QDateTime& p_rqdtValue);
    int SetValue(const QString& p_qstrKeyname, const QDateTime& p_rqdtValue);
    int GetValue(const QString& p_rqstrKeyname, double& p_rdValue);
    int SetValue(const QString& p_qstrKeyname, const double p_rdValue);
    int GetValue(const QString& p_rqstrKeyname, float& p_rfValue);
    int SetValue(const QString& p_qstrKeyname, const float p_rfValue);
    int SetValue(const QString& p_qstrKeyname, const int p_riValue);
    int GetValue(const QString& p_qstrKeyname, int& p_iValue);
    int GetValue(const QString& p_qstrKeyname, long& p_lValue);
    int SetValue(const QString& p_qstrKeyname, const long p_lValue);
    int SetValue(const QString& p_qstrKeyname, const QTime& p_qtValue);
    int DeleteValue(const QString& p_qstrKeyname);
    void SetDeleted();
    void SetNew();
    CdmObjectContainer* GetObjectContainer() const;
    long GetObjectContainerId() const;
    void ResetNewModified();
    long GetClassId() const;
    bool IsObjectInitialized() const;
    int GetValueCounter() const;
    void SetValueIdCounter(int p_lValueIdCounter);
    int GetValue(const QString& p_qstrKeyname, QTime& p_qtValue);
    void GetValueMap(QMap<QString, CdmValue*>& p_qmValues) const;
    int Commit();
    int LockObjectOnDb();
    int UnlockObjectOnDb();
    void GetCounterValues();
    int SetValue(QString p_pKeyname, const char* p_pValue);
    QMap<QString, CdmValue*>& GetValueMap( );
    void CopyValuesFromObject(const CdmObject& p_rCdmObject);
    //void CopyValuesFromObject(CdmObjectContainer *p_rCdmObjectContainer);
    int GetValue(const QString& p_qstrKeyname, CumUser*& p_pCumUser);
    int MoveToObjectList(CdmObjectContainer* p_pContainer);
    virtual QString GetInfo() const;
    virtual bool IsValid() const;
    bool IsTypeOf(QString p_qstrClassName) const;
    void Refresh();
    CdmObject* GetParent();
    long GetParentId() const;
    void GetChanges(QList<CdmJournalItem*>& p_rqllChanges);
    void GetChanges(QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqllChanges);
    bool HasParent() const;
    CdmObject* GetOwner();
    QList<CdmObject*> GetReferences();
    bool HasOwner() const;
    virtual bool IsObject() const;
    bool IsTypeOf(CdmClass* p_pClass) const;
    virtual QString GetCaption() const;

    QString GetObjectContainerKeyname() const;
    void RestoreValue(int p_iMemberId, QString p_qstrValueAsString);
    CdmValue *GetValue(int p_iMemberId);

protected slots:
    void ObjectModifiedSlot();

private slots:
    void ValueChangedSlot(CdmValue* p_pCdmValue);
    void ObjectRefModifiedSlot(CdmObject* p_pCdmObject, CdmValue* p_pCdmValue);

private:
    bool IsCachingEnabled() const;
    CdmValue* FindValueOverMember(QString p_qstrKeyname);
    CdmValue* FindValueOverReference(QString p_qstrKeyname);
    CdmObjectContainer * findValueObjectContainer();
    CdmValue* CreateObjectValue(CdmMember* p_pCdmMember);
    int InitObject(const CdmClass* p_pCdmClass);
    int AddObjectValue(CdmValue* p_pCdmValue);
    int RemoveValue(QString p_qstrKeyname);
    int InitObject();
    void DeleteOwnerRefs();
    void CommitOwnRefs();
    void CopyFromSourceObject(const CdmObject& p_rCdmObject);
    QString BuildComplexDisplayString(QString p_qstrComplexDisplayString) const;

signals:
    void ObjectDeletedSignal(CdmObject*);
    void ObjectModifiedSignal(CdmObject*);
    void ObjectRefModifiedSignal(CdmObject*);
    void ObjectCommitedSignal(int);


};
#endif

