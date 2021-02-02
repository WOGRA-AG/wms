/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CODBCDATAACCESS_H
#define CODBCDATAACCESS_H

// System and QT Includes
#include <QStack>
#include <QMutex>
#include <QSqlDatabase>
#include <QLinkedList>
#include <QMap>
#include <QTimer>
#include <QObject>
#ifdef WOGRA_DEBUG
#include <QTime>
#endif

// own Includes
#include "CdbInterface.h"
#include "CdbDataAccessConfigurator.h"
#include "CdmRights.h"
#include "CdmModelElement.h"
#include "IdmDataAccess.h"


// forwards
class QSqlQuery;
class QSqlDatabase;
class CdbLoginManager;
class CdbUserManager;
class CdbClassAccess;
class CdbObjectAccess;
class CdbSchemeAccess;
class CdbJournal;

#ifdef WIN32

#ifdef WMSDB_EXPORTS
#define WMSDB_API __declspec(dllexport)
#else
#define WMSDB_API __declspec(dllimport)
#endif //

#else

#define WMSDB_API

#endif //

// Enumerations

enum EdbSupportedDatabase
{
    eDbSupportedDatabaseMySQL,
    eDbSupportedDatabasePostgreSQL,
    eDbSupportedDatabaseOracle
};

/*
 * This class implements the dataaccess of odbc
 */
class WMSDB_API CdbDataAccess : public QObject, public IdmDataAccess
{
    Q_OBJECT

public:
    /*
       * The odbc basetypes
       */
    enum EodbcBaseType
    {
        eOdbcNone                 = 0, /* An Error Case if this exists in Db*/
        eOdbcClass                = 1,
        eOdbcValueDescritpion     = 2,
        eOdbcObject               = 3,
        eOdbcObjectList           = 4,
        eOdbcBinDoc               = 5,
        eOdbcBool                 = 6,
        eOdbcCharDoc              = 7,
        eOdbcCounter              = 8,
        eOdbcDate                 = 9,
        eOdbcDateTime             = 10,
        eOdbcDouble               = 11,
        eOdbcFloat                = 12,
        eOdbcInt                  = 13,
        eOdbcLong                 = 14,
        eOdbcObjRef               = 15,
        eOdbcObjListRef           = 16,
        eOdbcString               = 17,
        eOdbcTime                 = 18,
        eOdbcListInt              = 19,
        eOdbcListDouble           = 20,
        eOdbcListString           = 21,
        eOdbcDictStringInt        = 22,
        eOdbcDictStringString     = 23,
        eOdbcDictStringDouble     = 24,
        eOdbcDictIntInt           = 25,
        eOdbcDictIntString        = 26,
        eODbcDictIntDouble        = 27,
        eOdbcListObjects          = 28,
        eOdbcUser                 = 29,
        eOdbcFormula              = 30,
        eOdbcUserGroup            = 31,
        eOdbcEnum                 = 32
    };

private:
    CdbUserManager*  m_pCdbUserManager;
    CdbLoginManager* m_pCdbLoginManager;
    CdbSchemeAccess*     m_pCdbDbAccess;
    CdbObjectAccess* m_pCdbObjectAccess;
    CdbClassAccess*  m_pCdbClassAccess;
    CdbJournal* m_pCdbJournal;
    QMap<qint64,CdbInterface*> m_qmConnections;
    CdbDataAccessConfigurator* m_rpConfig;
    int m_iQueryCountGlobal;
    int m_iQueryCountSuccess;
    int m_iMsecsSum;
    QMutex m_qMutex;
    bool m_bServerMode;
    int m_iInterfaceCallCounter;

    QSqlDatabase RefreshConnection();
    CdmObject *GetObject(long p_lContainerId, long p_lObjectId);

public:
    virtual ~CdbDataAccess();
    CdbDataAccess();
    void SetServerMode(bool p_bServerMode);
    bool IsInServerMode() const;
    int GetInterfaceCallCounter() const;
    void PrintLastErrorFromDb(  );
    long ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery);
    int LoadObject(const CdmObjectContainer* p_pContainer, long p_lObjectId, CdmObject*& p_pCdmObject);
    int LoadObjectContainer(long p_lObjectListId, CdmObjectContainer*& p_pContainer);
    long GetNewContainerId(long p_lClassId);
    long GetNewClassId(long p_lDbId);
    int UpdateObject(CdmObject*& p_pCdmObject);
    long GetNewObjectId(const CdmObjectContainer* p_pContainer);
    int UpdateObjectContainer(CdmObjectContainer*& p_pContainer);
    int CreateScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager);
    int LoadSchemeBaseData(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager);
    int LoadSchemeBaseData(long p_lDb, CdmScheme*& p_pCdmDatabaseManager);
    int Login(QString p_qstrApplication,
              QString p_qstrLogin,
              QString p_qstrPassword,
              bool& p_bDemo,
              int& p_iModules,
              QString p_qstrVersion,
              long& p_lSessionId,
              CumUser*& p_rpCumUser);
    int Logout();
    int CreateUser(CumUser* p_pUser);
    int DeleteUser(QString p_qstrLogin);
    int LoadClassManager(long p_lDatabaseId, CdmClassManager*& p_pCdmClassManager);
    int UpdateClass(CdmClass*& p_pCdmClass);
    int DeleteClass(long p_lClassId);
    int DeleteScheme(QString p_qstrKeyname);
    int DeleteObjectContainer(long p_lObjectListId);
    int GetUserList(QLinkedList<CumUser*>& p_rqvlUser);
    int UpdateUser(CumUser* p_pUser);
    int GetContainerList(long p_lDbId, long p_lClassId, QMap<long, QString>& p_rqmObjectListsLList);
    int ExecuteQuery(CdmQuery* p_pCdmQuery);
    int ExistScheme(QString p_qstrKeyname, bool& p_bResult);
    int ExistClass(long p_lDbId, QString p_qstrClassKeyname, bool& p_bResult);
    int ExistObjectContainer(long p_lDbId, QString p_qstrObjectListKeyname);
    int LockObject(CdmObject* p_pObject, bool & p_bResult);
    int UnLockObject(CdmObject* p_pObject, bool & p_bResult);
    int LoadObjectContainer(long p_lDatabaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    int LoadEmptyObjectContainer(long p_lDataBaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    QByteArray ReadBinaryDocument(long p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument);
    int UpdateBinaryDocument(long p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument);
    long RenameUserGroup(long p_lGroupId, QString p_qstrNewName);
    long CreateUserGroup(QString p_qstrGroupName);
    long DeleteUserGroup(long p_llGroupId);
    long AddUserToUserGroup(long p_lChangeUserId, long p_lUserGroupId);
    long RemoveUserFromGroup(long p_lChangeUserId, long p_lUserGroupId);
    long GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri);
    long GetListOfUsersInList(long p_lUserGroupId, QLinkedList<CumUser*>& p_rqvlUserList);
    long GetUserGroupMemberList(long p_lChangeUserId, QLinkedList<CumUserGroup*>& p_qvlUserGroups);
    long AddLicense(QString p_qstrApplication, QString p_qstrLicensee, QString p_qstrLicensekey);
    long FreeLicense();
    long GetSchemeList(QLinkedList<QString>& p_qvlDatabases);
    long UpdateScheme(CdmScheme* p_pCdmDatabase);
    int Init(CdbDataAccessConfigurator* p_pConfig);
    virtual int Init(QString p_qstrApplicationName, QString p_qstrVersion);
    long GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);
    virtual QString GetConnectionDisplayString();
    int LoadEmptyObjectContainer(long p_lDataBaseId, long p_lId, CdmObjectContainer*& p_pContainer);
    int GetQueryCount();
    int GetSuccessfullQueryCount();
    virtual int LoadObjects(QLinkedList<long>& p_rqvlObjects, CdmObjectContainer*& p_pCdmObject);
    virtual int IsDemo(QString p_qstrApplication, QString p_qstrVersion);
    virtual long IsObjectUsed(const CdmObject* p_pObject);
    bool LicenceCheck(QString p_qstrApplication, bool& p_bDemo, int& p_iModules, QString p_qstrVersion);
    bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword);
    bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword);
    virtual CumUser* FindUserById(int p_iId);
    virtual long RefreshObject(CdmObject* p_pCdmObject);
    virtual long RefreshObjectContainer(CdmObjectContainer* p_pCdmObject);
    virtual long CountObjectsOnDb(CdmObjectContainer* p_pCdmObject);
    int SaveRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int LoadRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int DeleteRights(long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    virtual int AddLanguage(long p_lDatabaseId, QString p_qstrLanguage);
    virtual int DeleteLanguage(long p_lDatabaseId, int p_iLanguageId);
    CdbJournal* GetJournal();
    int GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetSchemeModifications(long p_lDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject);
    virtual bool GetReferences(const CdmObject* p_pObject, QList<CdmObject*>& p_rqmReferences);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject);
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer);
    void CreateDatabase(EdbSupportedDatabase p_eDatabase);
    void CreateDatabase(QString p_qstrFilename);
    bool UnlockClassMethod(long p_lMethodId);
    bool LockClassMethod(long p_lMethodId);
    virtual QVariant ExecuteFunction(CdmObject* p_PObject, QString p_qstrFunctionName, QVariantList p_qvlParameters);
    virtual QVariant EvaluateFormula(const CdmObject* p_pObject, QString p_qstrFormula);
    virtual bool GetRfcExecution()const {return false;}
    virtual void PrintContainer(QString p_qstrTemplateName, CdmObjectContainer *p_pContainer);
    virtual void PrintObject(QString p_qstrTemplateName, CdmObject *p_pObject);
    virtual int RegisterUser(CumUser* p_pUser);
    virtual CumUser *FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri);
    virtual CumUser *FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri);
    virtual CumUser *FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri);
    virtual int LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, long& p_lSessionId, CumUser*& p_rUser);
    virtual int UpdatePackage(CdmPackage*& p_pCdmPackage);
    virtual int DeleteUser(long p_lUserToDeleteId);
    virtual CdmSession* FindSession(int p_iSessionId);
    virtual CdmSession* FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
    virtual QLinkedList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    CumUserGroup* FindUserGroupById(int p_iId);
    CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
    CdbInterface *GetDbInterface();
    long ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    virtual QLinkedList<CumUserGroup*> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject*& p_pCdmObject);
    static EodbcBaseType ConvertValueType(EdmValueType p_eValue);
};

#endif //
