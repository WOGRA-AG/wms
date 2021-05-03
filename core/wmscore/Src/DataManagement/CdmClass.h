#ifndef CDMCLASS_H
#define CDMCLASS_H

// System and QT Includes
#include <QMap>
#include <QList>
#include <QVariant>
#include <QVector>

// own Includes
#include "CdmMember.h"
#include "CdmConfigManager.h"
#include "CdmModelElement.h"


// forwards
class CdmClassMethod;
class CdmClassManager;
class CdmValue;
class CdmMember;
class CdmObject;
class CdmClassGroup;
class CdmClassValidator;
class CdmPackage;


/**
 *  Implements the Classes for WMS. One class can only own 1024 members.
 *  A class can only be created by the class manager.
 */
class WMSMANAGER_API CdmClass : public CdmModelElement, public CdmConfigManager
{
    Q_OBJECT

    friend class CdmClassManager;
    friend class CdmDataAccessHelper;

private:
    /*
    * The baseclass map <Position, classid>
    * Position means that number of the base class in this class this value will be
    * calculated with the help of the baseclasscounter
    */
    QMap<long,long> m_qmBaseClasses;

    QList<long> m_qlModifedBaseClasses;
    /*
    * The InUse Flag if this flag is set this class cannot be deleted
    */
    bool m_bIsInUse;

    /*
    * Counts the number of baseclasses
    */
    QAtomicInteger<long> m_lBaseClassCounter;

    /*
    * The class comment for creating documentation
    */
    QString m_qstrComment;

    /*
    * The sequence of the members for displaying in gui objects.
    * In this list you will also find baseclass members.
    */
    mutable QVector<QString> m_qlMemberSequence;

    /*
    * This flags displays if this class is abstract or not.
    */
    bool m_bAbstract;

    /*
    * This member identfies te membervalue which should be used as caption
    */
    QAtomicInteger<long> m_lCaptionMember;

    QAtomicInt m_iVersion;

    /*
    * The package to which this class belaongs to. can be null
    */
    CdmPackage* m_rPackage;


    QString m_qstrCreateEventClass;

    QString m_qstrDeleteEventClass;

    QString m_qstrUpdateEventClass;

    /*
    * EventLists for ComboBoxes / Line Edits
    */
    QList<CdmClass*> m_qlCreateEventClasses;
    QList<CdmClass*> m_qlDeleteEventClasses;
    QList<CdmClass*> m_qlUpdateEventClasses;

    /*
    * Stores selected CUD-Event
    */
    CdmClass *m_pEventClass;

    /*
    * The member map it contains all members of the class itselves.
    */
    QMap<long,CdmMember*>  m_qmMembers;

    /*
    * The grouping of the members in the class
    */
    QMap<int, CdmClassGroup*> m_qmGroups;

    /*
   * The methods of a class
   */
    QMap<QString, CdmClassMethod*> m_qmMethods;

    /*
   * The methods of a class
   */
    QMap<QString, CdmClassValidator*> m_qmValidators;

private:
    CdmClass(long p_lDatabaseId, long p_lId, QString p_qstrKeyname);
    CdmClass(QDomElement& p_rqDomElement);
    CdmClass(QVariantMap& p_qvClass);
    virtual ~CdmClass();

public:
    int AddBaseClass(CdmClass* p_pCdmClass);
    void SetClassInUse(bool p_bInUse);
    int GetMemberMap(QMap<long, CdmMember*>& p_rqlMembers) const;
    int RemoveBaseClass(long p_lClassId);
    int DeleteMember(QString p_qstrKeyname);
    const QMap<long,long>& GetBaseClasses() const;
    bool IsInUse() const;
    int CheckObject(CdmObject* p_pCdmObject) const;
    CdmMember* CreateMember(QString p_qstrKeyname, EdmValueType p_eDmValue, bool p_bMust, long p_lSize);
    long GetNewMemberId();
    int GetClassMemberMap(QMap<long,CdmMember*>& p_rqlValues) const;
    int Commit();
    void SetComment(QString p_qstrComment);
    int XmlExport(QDomElement& p_rqdeClassManager) const;
    void XmlImport(QDomElement& p_rqDomElement);
    const QMap<long, CdmMember*> GetClassMemberMap() const;
    int RemoveBaseClass(QString p_qstrBaseClass);
    int AddBaseClass(QString p_qstrBaseClass);
    void SetAbstract(bool p_bAbstract);
    QString GetCaptionMemberKeyname() const;
    void SetCaptionMember(QString p_qstrCaptionMember);
    void SetMemberSequenceString(QMap<long, QString> &p_Sequence);
    void SetMemberSequenceString(QString p_qstrSequence);
    void SetMemberSequence(QVector<QString>& p_qvlSequence);
    virtual void ResetNewModified();
    bool HasNonSystemMembers() const;
    QList<QString> GetVisibleUserDefinedMembers() const;
    virtual QVariant GetVariant() const;
    void SetVariant(QVariantMap& p_rqvVariant);
    CdmClassGroup* CreateGroup(QString p_qstrName,
                               int p_iVersion,
                               CdmClassGroup* p_pCdmParent = nullptr);
    CdmClassGroup* CreateGroup(QString p_qstrName, int p_iVersion, int p_iPosition, CdmClassGroup* p_pCdmParent);
    const QMap<int, CdmClassGroup*>& GetClassGroups() const;
    bool AddMethod(CdmClassMethod* p_pCdmMethod);
    void AddValidator(CdmClassValidator* p_pValidator);
    void DeleteValidator(QString p_qstrName);
    void UpdateVersion();
    QMap<QString, CdmClassMethod*>& GetMethods();
    QMap<QString, CdmClassValidator*>& GetValidators();
    void DeleteGroup(int p_iId);
    void MoveGroupUp(int p_iGroupId);
    void MoveGroupDown(int p_iGroupId);
    bool HasValidators();
    void DeleteMethod(QString p_qstrName);
    CdmClassValidator* FindValidation(QString p_qstrName);
    void Deploy(QVariantMap& p_rqvHash);
    void SetVersion(int p_iVersion);
    void SetCaptionMember(CdmMember* p_pMember);
    void SetCaptionMember(long p_lMemberId);
    long GetCaptionMemberId() const;
    const CdmMember* GetCaptionMember() const;
    void ClearValidators();
    void ClearMethods();
    void ClearGroups();
    void SetPackage(CdmPackage* p_pPackage);
    void SetPackage(QString p_qstrUri);
    CdmPackage* GetPackage();
    QString GetFullQualifiedName() const;
    void SetKeyname(QString p_qstrKeyname);
    virtual QString GetUri() const;
    bool IsTypeOf(long p_lClassId);
    QList<long> GetDerivedClasses() const;
    QList<CdmClass*> getDerivedClasses();
    bool IsSingleton() const;
    bool IsImmutable() const;
    void SetSingleton(bool p_bSingleton);
    void SetImmutable(bool p_bImmutable);
    void SetIsEventClass(bool p_bIsEvent);
    bool IsEventClass() const;
    void SetEventSourcingActive(bool p_bEventSourcingActive);
    void SetCreateEventClass(QString p_qstrCreateEvent);
    void SetDeleteEventClass(QString p_qstrDeleteEvent);
    void SetUpdateEventClass(QString p_qstrUpdateEvent);
    bool IsEventSourcingActive() const;
    QString getCreateEventClass() const;
    QString getDeleteEventClass() const;
    QString getUpdateEventClass() const;
    CdmObject *GetSingletonObject();
    bool HasDirectClassImplementation(QString p_qstrName) const;
    QString GetUriInternal() const;
    void SetCreateEventClassList(QList<CdmClass *> qlCreateEventClasses);
    QList<CdmClass *> getCreateEventClassList() const;
    void SetDeleteEventClassList(QList<CdmClass *> qlDeleteEventClasses);
    QList<CdmClass *> getDeleteEventClassList() const;
    void SetUpdateEventClassList(QList<CdmClass *> qlUpdateEventClasses);
    QList<CdmClass *> getUpdateEventClassList() const;
    void setSelectedEventClass(CdmClass *pEventClass);
    CdmClass *getSelectedEventClass();
    QStringList getCreateEventClassStringList() const;
    void SetCreateEventClassStringList(QStringList p_qstrlList);
    QStringList getDeleteEventClassStringList() const;
    void SetDeleteEventClassStringList(QStringList p_qstrlList);
    QStringList getUpdateEventClassStringList() const;
    void SetUpdateEventClassStringList(QStringList p_qstrlList);
    CdmMember *FindEventClassMember(QString p_qstrKeyname);
    QList<long> GetBaseClassChanges();
    bool HasBaseClassChanges();
    const CdmMember* FindMember(QString p_qstrKeyname) const;
    int IsInherited(const CdmClass* p_pCdmClass) const;
    QString GetComment() const;
    const CdmMember* FindMember(QString p_qstrKeyname, int p_iRecursionLevel) const;
    bool HasValidator(QString p_qstrName) const;
    bool HasMethod(QString p_qstrName) const;
    CdmClassGroup* FindGroupById( long p_lGroupId);
    int FindGroupPosById( long p_lGroupId);
    void GetGroups(QMap<int, CdmClassGroup*>& p_qmGroups, int iIteration = 1) const;
    const CdmMember* FindMember(int p_iId) const;
    CdmClassMethod* GetMethod(QString p_qstrName);
    CdmClassMethod* FindMethod(QString p_qstrName);
    bool HasGroups() const;
    virtual bool IsClass() const;
    CdmClassGroup* FindGroupByName(QString p_qstrName);
    QMap<QString, CdmClassMethod *> GetAllMethods();
    void RemoveMethod(QString p_qstrName);
    int GetVersion() const;
    QString GetMemberSequenceString() const;
    QVector<QString> GetMemberSequence() const;
    bool IsAbstract() const;
    int IsInherited(QString p_qstrClassName) const;
    int IsInherited(int p_iClassId) const;
    CdmClassMethod *CreateMethod(int p_iId, QString p_qstrMethodName, EdmValueType p_eReturnType, EdmMemberAccess p_eAccessMode, QString p_qstrCode, int p_iVersion);
    CdmClassMethod *CreateMethod(QString p_qstrMethodName);
    CdmClassValidator *CreateValidator(QString p_qstrName);
    void DeleteValidator(CdmClassValidator *p_pValidator);
private:
    void XmlImportClass(QDomElement& p_rqdeElement);
    void XmlImportBaseClasses(QDomElement& p_rqDomElement);
    void XmlImportMembers(QDomElement& p_rqDomElement);
    void ClearMembers();
    int AddMember(CdmMember* p_pCdmMember);
    bool CheckMemberKeyname(QString p_qstrKeyname) const;
    bool HasMustMembers() const;
    void ResetGroupIds();
    void DeployBaseClasses(QVariantMap& p_rqHash);
    void DeployValidations(QVariantMap& p_rqvHash);
    void DeployGroups(QVariantMap& p_rqvHash);
    void DeployMethods(QVariantMap& p_rqvHash);
    void DeployMembers(QVariantList& p_rqHash);
    void UpdateSequenceOfDerivedClasses(QString p_qstrKeyname);
    void IncreaseVersion();
    void setCreateEventClassListStringList(QList<CdmClass*> qlCreateEventClassList);
    void setDeleteEventClassListStringList(QList<CdmClass*> qlDeleteEventClassList);
    void setUpdateEventClassListStringList(QList<CdmClass *> qlUpdateEventClassList);
    void ParseMethods(QVariantMap& p_rqvHash);
    void ParseGroups(QVariantMap& p_rqvHash);
    void ParseValidations(QVariantMap& p_rqvHash);
    bool ExistClassGroup(QString p_qstrName) const;
    void ParseBaseClasses(QVariantMap& p_rqHash);
    void ParseMembers(QVariantList& p_rqHash);
    void ParseMemberSequences(QVariantList& p_rqHash);
    CdmMember* FindClassMember(QString p_qstrKeyname);
    CdmMember* FindReferencedMember(QString p_qstrKeyname, int p_iRecusrionLevel = 0);
    void AddBaseClassData(CdmClass *p_pCdmClass);

private slots:
    QString GenerateDocumentation() const;
};
#endif
