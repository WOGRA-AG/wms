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
#include <QList>
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
    CdmObject *GetObject(qint64 p_lContainerId,qint64 p_lObjectId);

public:
    virtual ~CdbDataAccess();
    CdbDataAccess();
    void SetServerMode(bool p_bServerMode);
    bool IsInServerMode() const;
    int GetInterfaceCallCounter() const;
    void PrintLastErrorFromDb(  );
   qint64 ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery);
    int LoadObject(const CdmObjectContainer* p_pContainer,qint64 p_lObjectId, CdmObject*& p_pCdmObject);
    int LoadObjectContainer(qint64 p_lObjectListId, CdmObjectContainer*& p_pContainer);
   qint64 GetNewContainerId(qint64 p_lClassId);
   qint64 GetNewClassId(qint64 p_lDbId);
    int UpdateObject(CdmObject*& p_pCdmObject);
   qint64 GetNewObjectId(const CdmObjectContainer* p_pContainer);
    int UpdateObjectContainer(CdmObjectContainer*& p_pContainer);
    int CreateScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager);
    int LoadSchemeBaseData(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager);
    int LoadSchemeBaseData(qint64 p_lDb, CdmScheme*& p_pCdmDatabaseManager);
    int Login(QString p_qstrApplication,
              QString p_qstrLogin,
              QString p_qstrPassword,
              bool& p_bDemo,
              int& p_iModules,
              QString p_qstrVersion,
             qint64& p_lSessionId,
              CumUser*& p_rpCumUser);
    int Logout();
    int CreateUser(CumUser* p_pUser);
    int DeleteUser(QString p_qstrLogin);
    int LoadClassManager(qint64 p_lDatabaseId, CdmClassManager*& p_pCdmClassManager);
    int UpdateClass(CdmClass*& p_pCdmClass);
    int DeleteClass(qint64 p_lClassId);
    int DeleteScheme(QString p_qstrKeyname);
    int DeleteObjectContainer(qint64 p_lObjectListId);
    int GetUserList(QList<CumUser*>& p_rqvlUser);
    int UpdateUser(CumUser* p_pUser);
    int GetContainerList(qint64 p_lDbId,qint64 p_lClassId, QMap<qint64, QString>& p_rqmObjectListsLList);
    int ExecuteQuery(CdmQuery* p_pCdmQuery);
    int ExistScheme(QString p_qstrKeyname, bool& p_bResult);
    int ExistClass(qint64 p_lDbId, QString p_qstrClassKeyname, bool& p_bResult);
    int ExistObjectContainer(qint64 p_lDbId, QString p_qstrObjectListKeyname);
    int LockObject(CdmObject* p_pObject, bool & p_bResult);
    int UnLockObject(CdmObject* p_pObject, bool & p_bResult);
    int LoadObjectContainer(qint64 p_lDatabaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    int LoadEmptyObjectContainer(qint64 p_lDataBaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    QByteArray ReadBinaryDocument(qint64 p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument);
    int UpdateBinaryDocument(qint64 p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument);
   qint64 RenameUserGroup(qint64 p_lGroupId, QString p_qstrNewName);
   qint64 CreateUserGroup(QString p_qstrGroupName);
   qint64 DeleteUserGroup(qint64 p_llGroupId);
   qint64 AddUserToUserGroup(qint64 p_lChangeUserId,qint64 p_lUserGroupId);
   qint64 RemoveUserFromGroup(qint64 p_lChangeUserId,qint64 p_lUserGroupId);
   qint64 GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri);
   qint64 GetListOfUsersInList(qint64 p_lUserGroupId, QList<CumUser*>& p_rqvlUserList);
   qint64 GetUserGroupMemberList(qint64 p_lChangeUserId, QList<CumUserGroup*>& p_qvlUserGroups);
   qint64 AddLicense(QString p_qstrApplication, QString p_qstrLicensee, QString p_qstrLicensekey);
   qint64 FreeLicense();
   qint64 GetSchemeList(QList<QString>& p_qvlDatabases);
   qint64 UpdateScheme(CdmScheme* p_pCdmDatabase);
    int Init(CdbDataAccessConfigurator* p_pConfig);
    virtual int Init(QString p_qstrApplicationName, QString p_qstrVersion);
   qint64 GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);
    virtual QString GetConnectionDisplayString();
    int LoadEmptyObjectContainer(qint64 p_lDataBaseId,qint64 p_lId, CdmObjectContainer*& p_pContainer);
    int GetQueryCount();
    int GetSuccessfullQueryCount();
    virtual int LoadObjects(QList<qint64>& p_rqvlObjects, CdmObjectContainer*& p_pCdmObject);
    virtual int IsDemo(QString p_qstrApplication, QString p_qstrVersion);
    virtual qint64 IsObjectUsed(const CdmObject* p_pObject);
    bool LicenceCheck(QString p_qstrApplication, bool& p_bDemo, int& p_iModules, QString p_qstrVersion);
    bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword);
    bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword);
    virtual CumUser* FindUserById(int p_iId);
    virtual qint64 RefreshObject(CdmObject* p_pCdmObject);
    virtual qint64 RefreshObjectContainer(CdmObjectContainer* p_pCdmObject);
    virtual qint64 CountObjectsOnDb(CdmObjectContainer* p_pCdmObject);
    int SaveRights(CdmRights& p_rCcdmRights,qint64 p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int LoadRights(CdmRights& p_rCcdmRights,qint64 p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    int DeleteRights(qint64 p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName);
    virtual int AddLanguage(qint64 p_lDatabaseId, QString p_qstrLanguage);
    virtual int DeleteLanguage(qint64 p_lDatabaseId, int p_iLanguageId);
    CdbJournal* GetJournal();
    int GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetSchemeModifications(qint64 p_lDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject);
    virtual bool GetReferences(const CdmObject* p_pObject, QList<CdmObject*>& p_rqmReferences);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject);
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer);
    void CreateDatabase(EdbSupportedDatabase p_eDatabase);
    void CreateDatabase(QString p_qstrFilename);
    bool UnlockClassMethod(qint64 p_lMethodId);
    bool LockClassMethod(qint64 p_lMethodId);
    virtual QVariant ExecuteFunction(CdmObject* p_PObject, QString p_qstrFunctionName, QVariantList p_qvlParameters);
    virtual QVariant EvaluateFormula(const CdmObject* p_pObject, QString p_qstrFormula);
    virtual bool GetRfcExecution()const {return false;}
    virtual void PrintContainer(QString p_qstrTemplateName, CdmObjectContainer *p_pContainer);
    virtual void PrintObject(QString p_qstrTemplateName, CdmObject *p_pObject);
    virtual int RegisterUser(CumUser* p_pUser);
    virtual CumUser *FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri);
    virtual CumUser *FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri);
    virtual CumUser *FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri);
    virtual int LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword,qint64& p_lSessionId, CumUser*& p_rUser);
    virtual int UpdatePackage(CdmPackage*& p_pCdmPackage);
    virtual int DeleteUser(qint64 p_lUserToDeleteId);
    virtual CdmSession* FindSession(int p_iSessionId);
    virtual CdmSession* FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
    virtual QList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    CumUserGroup* FindUserGroupById(int p_iId);
    CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
    CdbInterface *GetDbInterface();
   qint64 ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    virtual QList<CumUserGroup*> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject*& p_pCdmObject);
    static EodbcBaseType ConvertValueType(EdmValueType p_eValue);
};

#endif //
