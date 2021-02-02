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
#include <QTimer>
#include <QObject>
#ifdef WOGRA_DEBUG
#include <QTime>
#endif

// own Includes
#include "CftlDataAccessConfigurator.h"
#include "CdmRights.h"
#include "IdmDataAccess.h"


// forwards
class QSqlQuery;
class QSqlDatabase;
class CftlLoginManager;
class CftlUserManager;
class CftlClassAccess;
class CftlObjectAccess;
class CftlSchemeAccess;
class CftlJournal;
class CftlInterface;

// Enumerations

enum EftlSupportedDatabase
{
    eSupportedDatabaseMySQL,
    eSupportedDatabasePostgreSQL,
    eSupportedDatabaseOracle,
    eSupportedDatabaseMSSQL
};

/*
 * This class implements the dataaccess of odbc
 */
class CftlDataAccess : public QObject, public IdmDataAccess
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
    /*
       * The dataaccess to users
       */
    CftlUserManager*  m_pCftlUserManager;

    /*
       * The Login Manager
       */
    CftlLoginManager* m_pCftlLoginManager;
    /*
       * Class for managing virtual databases on DB
       */
    CftlSchemeAccess* m_pCftlDbAccess;

    /*
       * Class for managing objects and objects list on DB
       */
    CftlObjectAccess* m_pCftlObjectAccess;

    /*
       * Class for managing class on DB
       */
    CftlClassAccess*  m_pCftlClassAccess;

    /*
      * Class for managing changes in db, objectlists and objects
      */
    CftlJournal* m_pCftlJournal;

    /*
       * stores the number of interface calls
       */
    int m_iInterfaceCallCounter;
    /*
       * This flag shows if this dataccess runs in the servermode or not
       * is needed to instatiate database connection pool
       */
    bool m_bServerMode;
    QMap<qint64,CftlInterface*> m_qmConnections;
    CftlDataAccessConfigurator* m_rpConfig;
    QMutex m_qMutex;

private slots:
    void KeepAlive();
private:


public:
    virtual ~CftlDataAccess();
    CftlDataAccess();
    void SetServerMode(bool p_bServerMode);
    bool IsInServerMode() const;
    int GetInterfaceCallCounter() const;
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
    int ExistClass(long p_lDbId, QString p_qstrClassKeyname, bool & p_bResult);
    int ExistObjectContainer(long p_lDbId, QString p_qstrObjectListKeyname);
    int LockObject(CdmObject* p_pObject, bool & p_bResult);
    int UnLockObject(CdmObject* p_pObject, bool & p_bResult);
    int LoadObjectContainer(long p_lDatabaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer );
    int LoadEmptyObjectContainer(long p_lDataBaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer);
    QByteArray ReadBinaryDocument(long p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument);
    int UpdateBinaryDocument(long p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument);
    long RenameUserGroup(long p_lGroupId, QString p_qstrNewName);
    long CreateUserGroup(QString p_qstrGroupName);
    long DeleteUserGroup(long p_llGroupId);
    long AddUserToUserGroup(long p_lChangeUserId,long p_lUserGroupId);
    long RemoveUserFromGroup(long p_lChangeUserId, long p_lUserGroupId);
    long GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri);
    long GetListOfUsersInList(long p_lUserGroupId, QLinkedList<CumUser*>& p_rqvlUserList);
    long GetUserGroupMemberList(long p_lChangeUserId, QLinkedList<CumUserGroup*>& p_qvlUserGroups);
    long AddLicense(QString p_qstrApplication, QString p_qstrLicensee, QString p_qstrLicensekey);
    long FreeLicense();
    long GetSchemeList(QLinkedList<QString>& p_qvlDatabases);
    long UpdateScheme(CdmScheme* p_pCdmDatabase);
    int Init(CftlDataAccessConfigurator* p_pConfig);
    virtual int Init(QString p_qstrApplicationName, QString p_qstrVersion);
    long GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);
    virtual QString GetConnectionDisplayString();
    int LoadEmptyObjectContainer(long p_lDataBaseId, long p_lId, CdmObjectContainer*& p_pContainer);
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
    CftlJournal* GetJournal();
    int GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer,QDate p_qdFrom,QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetSchemeModifications(long p_lDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject);
    virtual bool GetReferences(const CdmObject* p_pObject, QList<CdmObject*>& p_rqmReferences);
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer);
    void CreateDatabase(EftlSupportedDatabase p_eDatabase);
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
    int LoadSchemeBaseData(long p_lDb, CdmScheme *&p_pCdmDatabaseManager);
    CdmSession *FindSession(int p_iSessionId);
    CdmSession *FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
    virtual QLinkedList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    virtual CumUserGroup* FindUserGroupById(int p_iId);
    virtual CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
    long ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    CftlInterface *GetFtlInterface();
    QLinkedList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
};

#endif //
