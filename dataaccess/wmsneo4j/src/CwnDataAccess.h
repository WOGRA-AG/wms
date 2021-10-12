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
    CdmObject *GetObject(qint64 p_lContainerId,qint64 p_lObjectId);
public:
    CwnDataAccess();
    virtual ~CwnDataAccess();
    int Init(CwnDataAccessConfigurator* p_pConfig);
    CwnDataAccessConfigurator* GetConfig();
    virtual qint64 GetNewObjectId(const CdmObjectContainer* p_pContainer);
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer);
    virtual int UpdateObject(CdmObject*& p_pCdmObject);
    virtual int LoadObjects(QList<qint64>& p_rqvlObjects,CdmObjectContainer*& p_pCdmObject);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer,qint64 p_lObjectId,CdmObject*& p_pCdmObject);
    virtual qint64 RefreshObject(CdmObject* p_pCdmObject);
    virtual qint64 GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);
    virtual QByteArray ReadBinaryDocument(qint64 p_lDbId,CdmValueBinaryDocument* p_pCdmBinaryDocument );
    virtual int UpdateBinaryDocument(qint64 p_lDbId,CdmValueBinaryDocument* p_pCdmBinaryDocument );
    virtual qint64 CountObjectsOnDb(CdmObjectContainer* p_pCdmObject);
    virtual qint64 IsObjectUsed(const CdmObject* p_pObject);
    virtual int LockObject(CdmObject* p_pObject, bool & p_bResult);
    virtual int UnLockObject(CdmObject* p_pObject, bool & p_bResult );
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject);
    virtual bool GetReferences(const CdmObject* p_pObject,QList<CdmObject*>& p_rqmReferences);
    virtual qint64 GetNewContainerId(qint64 p_lClassId);
    virtual int UpdateObjectContainer(CdmObjectContainer*& p_pContainer);
    virtual int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer, QDate p_qdFrom,QDate p_qdTo,QList<CdmJournalItem*>& p_qlItems);
    virtual int GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom,QDate p_qdTo,QList<CdmJournalItem*>& p_qlItems);
    virtual int ExistObjectContainer(qint64 p_lDbId, QString p_qstrObjectListKeyname);
    virtual qint64 RefreshObjectContainer(CdmObjectContainer* p_pCdmObject);
    virtual int LoadObjectContainer(qint64 p_lObjectListId,CdmObjectContainer*& p_pContainer);
    virtual int LoadObjectContainer(qint64 p_lDatabaseId,QString p_qstrKeyname,CdmObjectContainer*& p_pContainer);
    virtual int LoadEmptyObjectContainer(qint64 p_lDataBaseId,QString p_qstrKeyname,CdmObjectContainer*& p_pContainer);
    virtual int LoadEmptyObjectContainer(qint64 p_lDataBaseId,qint64 p_lId,CdmObjectContainer*& p_pContainer);
    virtual int GetContainerList(qint64 p_lDbId,qint64 lClassId, QMap<qint64,QString>& p_rqmObjectListsLList);
    virtual int DeleteObjectContainer(qint64 p_lObjectListId);
    virtual int ExecuteQuery(CdmQuery* p_pCdmQuery);
    CwnJournal* GetJournal();
    virtual int CreateScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager);
    virtual qint64 GetSchemeList(QList<QString>& p_qvlDatabases);
    virtual int  GetSchemeModifications(qint64 p_lDatabaseId,QDate p_qdFrom,QDate p_qdTo,QList<CdmJournalItem*>& p_qlItems);
    virtual qint64 UpdateScheme(CdmScheme* p_pCdmDatabase);
    virtual int AddLanguage(qint64 p_lDatabaseId, QString p_qstrLanguage);
    virtual int DeleteLanguage(qint64 p_lDatabaseId, int p_iLanguageId);
    virtual int LoadSchemeBaseData(QString p_qstrKeyname,CdmScheme*& p_pCdmDatabaseManager);
    virtual int LoadSchemeBaseData(qint64 p_lSchemeId,CdmScheme*& p_pCdmDatabaseManager);
    virtual int ExistScheme(QString p_qstrKeyname, bool& p_bResult);
    virtual int DeleteScheme(QString p_qstrKeyname);
    virtual int Login(QString p_qstrApplication,QString p_qstrLogin,QString p_qstrPassword,bool& p_bDemo,int& p_iModules,QString p_qstrVersion,qint64& p_lSessionId,CumUser*& p_rpCumUser);
    virtual int LoginLdap(QString p_qstrApplication, QString p_qstrLogin,QString p_qstrPassword,qint64& p_lSessionId,CumUser*& p_rUser);
    virtual int RegisterUser(CumUser* p_pUser);
    virtual CdmSession* FindSession(int p_iSessionId);
    virtual CdmSession* FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
    virtual bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword);
    virtual bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword);
    virtual int Logout();
    virtual int LoadClassManager(qint64 p_lDatabaseId,CdmClassManager*& p_pCdmClassManager);
    virtual qint64 GetNewClassId(qint64 p_lDbId);
    virtual int ExistClass(qint64 p_lDbId,QString p_qstrClassKeyname,bool & p_bResult);
    virtual int UpdatePackage(CdmPackage*& p_pCdmPackage);
    virtual int UpdateClass(CdmClass*& p_pCdmClass);
    virtual bool LockClassMethod(qint64 p_lMethodId);
    virtual bool UnlockClassMethod(qint64 p_lMethodId);
    virtual int DeleteClass(qint64 p_lClassId);
    virtual int CreateUser(CumUser* p_pUser);
    virtual int GetUserList(QList<CumUser*>& p_rqvlUser);
    virtual qint64 GetListOfUsersInList(qint64 p_lUserGroupId,QList<CumUser*>& p_rqvlUserList );
    virtual CumUser* FindUserById(int p_iId);
    virtual CumUser* FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    virtual CumUser* FindUser(QString p_qstrUserId, QString p_qstrPassword, QString p_qstrSchemeUri);
    virtual QList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual int UpdateUser(CumUser* p_pUser);
    virtual int DeleteUser(QString p_qstrLogin);
    virtual int DeleteUser(qint64 p_lUserToDeleteId);
    virtual qint64 AddUserToUserGroup(qint64 p_lChangeUserId,qint64 p_lUserGroupId);
    virtual qint64 RemoveUserFromGroup(qint64 p_lChangeUserId,qint64 p_lUserGroupId);
    virtual qint64 CreateUserGroup(QString p_qstrGroupName);
    virtual qint64 RenameUserGroup(qint64 p_lGroupId,QString p_qstrNewName );
    virtual qint64 GetUserGroupMemberList(qint64 p_lChangeUserId,QList<CumUserGroup*>& p_qvlUserGroups);
    virtual qint64 GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri);
    virtual CumUserGroup* FindUserGroupById(int p_iId);
    virtual CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
    virtual qint64 DeleteUserGroup(qint64 p_llGroupId);
    virtual int IsDemo(QString p_qstrApplication, QString p_qstrVersion);
    virtual bool LicenceCheck(QString p_qstrApplication,bool& p_bDemo,int& p_iModules,QString p_qstrVersion);
    virtual qint64 AddLicense(QString p_qstrApplication,QString p_qstrLicensee,QString p_qstrLicensekey );
    virtual qint64 FreeLicense();
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
    int LoadRights(CdmRights& p_rCcdmRights,qint64 p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int SaveRights(CdmRights& p_rCcdmRights,qint64 p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int DeleteRights(qint64 p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    QString GetBoolAsString(bool p_bValue);
    QString GenerateInString(QList<qint64> &p_rqvlIds);
    virtual QList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
};

#endif // CWNDATAACCESS_H
