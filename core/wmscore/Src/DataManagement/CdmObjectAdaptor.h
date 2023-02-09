#ifndef CWMSDATAACCESS_H
#define CWMSDATAACCESS_H

// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <QString>

// own Includes
#include "CdmLocatedElement.h"
#include "CdmModelElement.h"

// forwards
class CdmObject;
class CdmObjectContainer;


/**
 * The CdmObjectAdaptor class implements the adaptor for objects
 * it can be used for accessing object data and
 * reduce sourcecode size in client applications.
 */
class WMSMANAGER_API CdmObjectAdaptor : public CdmLocatedElement
{
private:
    // Datbase ID
    qint64 m_lDbId;

    // Object ID
    qint64 m_lObjectId;

    // ObjectList ID
    qint64 m_lObjectListId;

public:
    CdmObjectAdaptor( qint64 p_lDbId,qint64 p_lObjectId,qint64 p_lObjectListId );
    CdmObjectAdaptor(  CdmObject* p_pCdmObject );
    virtual ~CdmObjectAdaptor(  );
    CdmObject* GetObject(); // deprecated since everyone defines a "GetObject" -> GetObjectA GetObjectW stuff
    CdmObject* GetDataObject();
    CdmObject* GetDataObjectConst() const;
    const CdmObject* GetConstDataObjectConst() const;
    qint64 GetObjectId() const;
    QString GetString(QString p_qstrKeyname) const;
    QTime GetTime(QString p_qstrKeyname) const;
    QDate GetDate(QString p_qstrKeyname) const;
    float GetFloat(QString p_qstrKeyname) const;
    bool GetBool(QString p_qstrKeyname) const;
    void SetValue(QString p_qstrKeyname, QString p_qstrValue);
    void SetValue(QString p_qstrKeyname, QDate p_qdDate);
    void SetValue(QString p_qstrKeyname, QDateTime p_qdtDateTime);
    void SetValue(QString p_qqstrkeyname, QTime p_qtTime);
    void SetValue(QString p_qstrKeyname, float p_fValue);
    void SetValue(QString p_qstrKeyname, int p_iValue);
    void SetValue(QString p_qstrKeyname,qint64 p_lValue);
    void SetValue(QString p_qstrKeyname, bool p_bValue);
    CdmObject* GetObjectRefValue(QString p_qstrKeyname);
    qint64 GetObjectRef(QString p_qstrKeyname);
    qint64 GetContainerRef(QString p_qstrKeyname);
    void SetContainerRefValue(QString p_qstrKeyname,qint64 p_lObjectListId);
    CdmObjectContainer* GetEmptyContainerRefValue(QString p_qstrKeyname);
    int CommitObject();
    QDateTime GetDateTime(QString p_qstrKeyname) const;
    int GetInt(QString p_qstrKeyname) const;
    double GetDouble(QString p_qstrKeyname) const;
    void SetValue(QString p_qstrKeyname, double p_dValue);
    QString GetCaption() const;
    QString GetKeyname() const;
    QString GetDisplayString(QString p_qstrKeyname) const;
    bool IsValid() const;
    void SetObjectRefValue(QString p_qstrKeyname, CdmObject* p_pCdmObject);
    void SetContainerRefValue(QString p_qstrKeyname, CdmObjectContainer* p_pContainer);
    void ReloadContainerComplete(CdmObjectContainer*& p_pContainer);
    virtual void SetObject(CdmObject* p_pCdmObject);
    CdmObjectAdaptor( );
    CdmObjectContainer* GetContainerRefValue(QString p_qstrKeyname);
    qint64 GetLong(QString p_qstrKeyname) const;
    CdmObjectAdaptor( const CdmObjectAdaptor& p_rCdmObjectAdaptor);
    void operator=(const CdmObjectAdaptor& p_rCdmObjectAdaptor);
    CdmValue* GetValue(QString p_qstrKeyname);
    void SetBinDocNewFilename(QString p_qstrKeyname, QString p_qstrFilename);
    QString GetBinDocCurrentFilename(QString p_qstrKeyname);
    void OpenBinDoc(QString p_qstrKeyname);
    void SaveBinDocTo(QString p_qstrKeyname, QString p_qstrPath);
    bool DeleteObject();
    bool IsTypeOf(QString p_qstrType) const;
    QList<QString> GetStringList(QString p_qstrMember) const;
    void AddStringListValue(QString p_qstrMember, QString p_qstrValue);
    void RemoveStringListValue(QString p_qstrMember, QString p_qstrValue);
    CumUser* GetUser(QString p_qstrKeyname) const;
    void SetValue(QString p_qstrKeyname, CumUser* p_pCumUser);
    QList<double> GetDoubleList(QString p_qstrMember) const;
    QList<int> GetIntList(QString p_qstrMember) const;
    QList<CdmObject*> GetListObjects(QString p_qstrMember);
    void AddDoubleListValue(QString p_qstrMember, double p_dValue);
    void AddIntListValue(QString p_qstrMember, int p_iValue);
    void AddListObjectsValue(QString p_qstrMember, CdmObject* p_pCdmObject);
    void RemoveDoubleListValue(QString p_qstrMember, double p_dValue);
    void RemoveIntListValue(QString p_qstrMember, int p_iValue);
    void RemoveListObjectsValue(QString p_qstrMember, CdmObject* p_pCdmObject);
    void RemoveListObjectsComplete(QString p_qstrMember);
    void SetDeleted();
    QMap<QString, QString> GetStringStringDict(QString p_qstrValue) const;
    QMap<QString, int> GetStringIntDict(QString p_qstrValue) const;
    QMap<QString, double> GetStringDoubleDict(QString p_qstrValue) const;
    QMap<int, double> GetIntDoubleDict(QString p_qstrValue) const;
    QMap<int, int> GetIntIntDict(QString p_qstrValue) const;
    QMap<int, QString> GetIntStringDict(QString p_qstrValue) const;
    void AddIntStringEntry(QString p_qstrMember, int p_iKey, QString p_qstrValue);
    void AddStringIntEntry(QString p_qstrMember, QString p_qstrKey, int p_iValue);
    void AddStringDoubleEntry(QString p_qstrMember, QString p_qstrKey, double p_dValue);
    void AddIntDoubleEntry(QString p_qstrMember, int p_iKey, double p_dValue);
    void AddIntIntEntry(QString p_qstrMember, int p_iKey, int p_iValue);
    void RemoveIntDoubleEntry(QString p_qstrMember, int p_iKey);
    void RemoveIntIntEntry(QString p_qstrMember, int p_iKey);
    void RemoveIntStringEntry(QString p_qstrMember, int p_iKey);
    void RemoveStringDoubleEntry(QString p_qstrMember, QString p_qstrKey);
    void RemoveStringIntEntry(QString p_qstrMember, QString p_qstrKey);
    void RemoveStringStringEntry(QString p_qstrMember, QString p_qstrKey);
    void AddStringStringEntry(QString p_qstrMember, QString p_qstrKey, QString p_qstrValue);
    QVariant GetVariant() const;
    void SetVariant(QVariant& p_rqVariant, QString p_qstrOLKeyname);
    static CdmObjectContainer* GetObjectContainer(QString p_qstrKeyname);
    void SetStringList(QString p_qstrMember, QList<QString> p_rqstrlList);
    void SetStringStringDict(QString p_qstrValue, QMap<QString, QString> p_qmValue);
    void SetStringIntDict(QString p_qstrValue, QMap<QString, int> p_qmValue);
    CdmObjectContainer* GetObjectContainer();
    CdmObject* GetParentObject();
    qint64 GetParentObjectId();
    void SetListObjects(QString p_qstrMember, QList<CdmObject*> p_qlObjects);
    QVariant Execute(QString p_qstrFunction);
    void SetIntList(QString p_qstrMember, QList<int> p_rqstrlList);
    void SetDoubleList(QString p_qstrMember, QList<double> p_rqstrlList);
    void SetStringDoubleDict(QString p_qstrValue, QMap<QString, double> p_qmValue);
    void SetIntDoubleDict(QString p_qstrValue, QMap<int, double> p_qmValue);
    void SetIntIntDict(QString p_qstrValue, QMap<int, int> p_qmValue);
    void SetIntStringDict(QString p_qstrValue, QMap<int, QString> p_qmValue);
    virtual QString GetUri();
    QByteArray LoadBinDoc(QString p_qstrKeyname);
    QString GetUriInternal() const;
    CdmContainerManager *GetContainerManager();
    CdmClassManager *GetClassManager();
    QVariantMap GetVariantGraph(bool p_bFollowNonOwnerObjectlist, bool p_bFollowNonOwnerObject, QStringList p_qstrExcludedKeynames, int p_iMaxDepth, int p_iMaxObjects) const;
    QVariant GetVariant(QString &p_qstrValue) const;
    void Refresh();
    void SetObjectRefValue(QString p_qstrKeyname, QString qstrSelfLink);
    void SetListObjectsValues(QString p_qstrMember, QVariantList selfLinks);
    CdmObject *FindObjectBySelfLink(QString qstrSelfLink);
    QString GetBinDocCurrentCompletePath(QString p_qstrKeyname);

protected:
    virtual bool ValidateObjectData();
    virtual void AfterCommit();
    virtual void BeforeCommit();

private:
    void UpdateObject(QVariantMap& p_rqVariant);
    void AppendLinksToChildVariant(CdmObject *pObject, QVariantMap &childVariant) const;

};

#endif //
