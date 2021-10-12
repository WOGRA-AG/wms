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
    int ExistClass(qint64 p_lDbId, QString p_qstrClassKeyname, bool & p_bResult);
    int ExistObjectContainer(qint64 p_lDbId, QString p_qstrObjectListKeyname);
    int LockObject(CdmObject* p_pObject, bool & p_bResult);
    int UnLockObject(CdmObject* p_pObject, bool & p_bResult);
    int LoadObjectContainer(qint64 p_lDatabaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer );
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
    int Init(CftlDataAccessConfigurator* p_pConfig);
    virtual int Init(QString p_qstrApplicationName, QString p_qstrVersion);
   qint64 GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue);
    virtual QString GetConnectionDisplayString();
    int LoadEmptyObjectContainer(qint64 p_lDataBaseId,qint64 p_lId, CdmObjectContainer*& p_pContainer);
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
    CftlJournal* GetJournal();
    int GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer,QDate p_qdFrom,QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    int GetSchemeModifications(qint64 p_lDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems);
    virtual bool GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject);
    virtual bool GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject);
    virtual bool GetReferences(const CdmObject* p_pObject, QList<CdmObject*>& p_rqmReferences);
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer);
    void CreateDatabase(EftlSupportedDatabase p_eDatabase);
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
    int LoadSchemeBaseData(qint64 p_lDb, CdmScheme *&p_pCdmDatabaseManager);
    CdmSession *FindSession(int p_iSessionId);
    CdmSession *FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
    virtual QList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    virtual CumUserGroup* FindUserGroupById(int p_iId);
    virtual CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
   qint64 ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    CftlInterface *GetFtlInterface();
    QList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
    virtual int LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
};

#endif //
