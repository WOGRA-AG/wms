#ifndef CWNDATAACCESS_H
#define CWNDATAACCESS_H

#include <QVariant>
#include <QList>

// WMS Include
#include "IdmDataAccess.h"

// own Includes
#include "CdmRights.h"

//forwards
class CumUser;
class CumUserGroup;
class CwnUserManager;
class CwnLoginManager;
class CwnClassAccess;
class CwnSchemeAccess;
class CwnJournal;
class CwnObjectAccess;
class CwnDataAccessConfigurator;

class CwnDataAccess : public QObject, public IdmDataAccess
{

private:
    CwnJournal* m_pCwnJournal;
    CwnUserManager* m_pCwnUserManager;
    CwnLoginManager* m_pCwnLoginManager;
    CwnClassAccess* m_pCwnClassAccess;
    CwnSchemeAccess* m_pCwnDbAccess;
    CwnObjectAccess* m_pCwnObjectAccess;

    int m_iQueryCountGlobal;
    int m_iQueryCountSuccess;
    QString m_qstrDbName;
    bool m_bServerMode;
    int m_iInterfaceCallCounter;
    int m_iTransactionCount;
    int m_iMsecsSum;
    CwnDataAccessConfigurator* m_rpConfig;

    int SessionCheck();
    CdmObject *GetObject(long p_lContainerId, long p_lObjectId);
public:
    CwnDataAccess();
    virtual ~CwnDataAccess();
    int Init(CwnDataAccessConfigurator* p_pConfig);
    CwnDataAccessConfigurator* GetConfig();
    virtual long GetNewObjectId(const CdmObjectContainer* p_pContainer);
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer);
    virtual int UpdateObject(CdmObject*& p_pCdmObject);
    virtual int LoadObjects(QLinkedList<long>& p_rqvlObjects,CdmObjectContainer*& p_pCdmObject);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, long p_lObjectId,CdmObject*& p_pCdmObject);
    virtual long RefreshObject(CdmObject* p_pCdmObject);
    virtual long GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);
    virtual QByteArray ReadBinaryDocument(long p_lDbId,CdmValueBinaryDocument* p_pCdmBinaryDocument );
    virtual int UpdateBinaryDocument(long p_lDbId,CdmValueBinaryDocument* p_pCdmBinaryDocument );
    virtual long CountObjectsOnDb(CdmObjectContainer* p_pCdmObject);
    virtual long IsObjectUsed(const CdmObject* p_pObject);
    virtual int LockObject(CdmObject* p_pObject, bool & p_bResult);
    virtual int UnLockObject(CdmObject* p_pObject, bool & p_bResult );
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject);
    virtual bool GetReferences(const CdmObject* p_pObject,QList<CdmObject*>& p_rqmReferences);
    virtual long GetNewContainerId(long p_lClassId);
    virtual int UpdateObjectContainer(CdmObjectContainer*& p_pContainer);
    virtual int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer, QDate p_qdFrom,QDate p_qdTo,QList<CdmJournalItem*>& p_qlItems);
    virtual int GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom,QDate p_qdTo,QList<CdmJournalItem*>& p_qlItems);
    virtual int ExistObjectContainer(long p_lDbId, QString p_qstrObjectListKeyname);
    virtual long RefreshObjectContainer(CdmObjectContainer* p_pCdmObject);
    virtual int LoadObjectContainer(long p_lObjectListId,CdmObjectContainer*& p_pContainer);
    virtual int LoadObjectContainer(long p_lDatabaseId,QString p_qstrKeyname,CdmObjectContainer*& p_pContainer);
    virtual int LoadEmptyObjectContainer(long p_lDataBaseId,QString p_qstrKeyname,CdmObjectContainer*& p_pContainer);
    virtual int LoadEmptyObjectContainer(long p_lDataBaseId,long p_lId,CdmObjectContainer*& p_pContainer);
    virtual int GetContainerList(long p_lDbId,long lClassId, QMap<long,QString>& p_rqmObjectListsLList);
    virtual int DeleteObjectContainer(long p_lObjectListId);
    virtual int ExecuteQuery(CdmQuery* p_pCdmQuery);
    CwnJournal* GetJournal();
    virtual int CreateScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager);
    virtual long GetSchemeList(QLinkedList<QString>& p_qvlDatabases);
    virtual int  GetSchemeModifications(long p_lDatabaseId,QDate p_qdFrom,QDate p_qdTo,QList<CdmJournalItem*>& p_qlItems);
    virtual long UpdateScheme(CdmScheme* p_pCdmDatabase);
    virtual int AddLanguage(long p_lDatabaseId, QString p_qstrLanguage);
    virtual int DeleteLanguage(long p_lDatabaseId, int p_iLanguageId);
    virtual int LoadSchemeBaseData(QString p_qstrKeyname,CdmScheme*& p_pCdmDatabaseManager);
    virtual int LoadSchemeBaseData(long p_lSchemeId,CdmScheme*& p_pCdmDatabaseManager);
    virtual int ExistScheme(QString p_qstrKeyname, bool& p_bResult);
    virtual int DeleteScheme(QString p_qstrKeyname);
    virtual int Login(QString p_qstrApplication,QString p_qstrLogin,QString p_qstrPassword,bool& p_bDemo,int& p_iModules,QString p_qstrVersion,long& p_lSessionId,CumUser*& p_rpCumUser);
    virtual int LoginLdap(QString p_qstrApplication, QString p_qstrLogin,QString p_qstrPassword,long& p_lSessionId,CumUser*& p_rUser);
    virtual int RegisterUser(CumUser* p_pUser);
    virtual CdmSession* FindSession(int p_iSessionId);
    virtual CdmSession* FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
    virtual bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword);
    virtual bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword);
    virtual int Logout();
    virtual int LoadClassManager(long p_lDatabaseId,CdmClassManager*& p_pCdmClassManager);
    virtual long GetNewClassId(long p_lDbId);
    virtual int ExistClass(long p_lDbId,QString p_qstrClassKeyname,bool & p_bResult);
    virtual int UpdatePackage(CdmPackage*& p_pCdmPackage);
    virtual int UpdateClass(CdmClass*& p_pCdmClass);
    virtual bool LockClassMethod(long p_lMethodId);
    virtual bool UnlockClassMethod(long p_lMethodId);
    virtual int DeleteClass(long p_lClassId);
    virtual int CreateUser(CumUser* p_pUser);
    virtual int GetUserList(QLinkedList<CumUser*>& p_rqvlUser);
    virtual long GetListOfUsersInList(long p_lUserGroupId,QLinkedList<CumUser*>& p_rqvlUserList );
    virtual CumUser* FindUserById(int p_iId);
    virtual CumUser* FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    virtual CumUser* FindUser(QString p_qstrUserId, QString p_qstrPassword, QString p_qstrSchemeUri);
    virtual QLinkedList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual int UpdateUser(CumUser* p_pUser);
    virtual int DeleteUser(QString p_qstrLogin);
    virtual int DeleteUser(long p_lUserToDeleteId);
    virtual long AddUserToUserGroup(long p_lChangeUserId,long p_lUserGroupId);
    virtual long RemoveUserFromGroup(long p_lChangeUserId,long p_lUserGroupId);
    virtual long CreateUserGroup(QString p_qstrGroupName);
    virtual long RenameUserGroup(long p_lGroupId,QString p_qstrNewName );
    virtual long GetUserGroupMemberList(long p_lChangeUserId,QLinkedList<CumUserGroup*>& p_qvlUserGroups);
    virtual long GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri);
    virtual CumUserGroup* FindUserGroupById(int p_iId);
    virtual CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
    virtual long DeleteUserGroup(long p_llGroupId);
    virtual int IsDemo(QString p_qstrApplication, QString p_qstrVersion);
    virtual bool LicenceCheck(QString p_qstrApplication,bool& p_bDemo,int& p_iModules,QString p_qstrVersion);
    virtual long AddLicense(QString p_qstrApplication,QString p_qstrLicensee,QString p_qstrLicensekey );
    virtual long FreeLicense();
    virtual QString GetConnectionDisplayString();
    virtual void SetServerMode(bool p_bServerMode);
    virtual bool IsInServerMode() const;
    virtual int GetInterfaceCallCounter() const;
    virtual void StartTransaction();
    virtual void CommitTransaction();
    virtual void RollbackTransaction();
    virtual QVariant ExecuteFunction(CdmObject* p_PObject, QString p_qstrFunctionName, QVariantList p_qvlParameters);
    virtual QVariant EvaluateFormula(const CdmObject* p_pObject, QString p_qstrFormula);
    virtual bool GetRfcExecution() const;
    virtual void PrintContainer(QString p_qstrTemplateName, CdmObjectContainer *p_pContainer);
    virtual void PrintObject(QString p_qstrTemplateName, CdmObject *p_pObject);
    int LoadRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int SaveRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int DeleteRights(long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    QString GetBoolAsString(bool p_bValue);
    QString GenerateInString(QLinkedList<long> &p_rqvlIds);
    virtual QLinkedList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
};

#endif // CWNDATAACCESS_H
