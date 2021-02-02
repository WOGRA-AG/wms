/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef IDMDATAACCESS_H
#define IDMDATAACCESS_H

// System and QT Includes
#include <qstring.h>
#include <qmap.h>
#include <qdatetime.h>
#include <QLinkedList>
#include <QVariant>


// own Includes
#include "datamanager.h"

// forwards
class CdmManager;
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class CdmPackage;
class CdmValue;
class CdmError;
class CdmModelElement;
class CdmValueBinaryDocument;
class CdmMember;
class CdmSettings;
class CdmScheme;
class CumUser;
class CumUserGroup;
class CdmQuery;
class CdmClassManager;
class CdmJournalItem;
class QVariant;
class QSqlDatabase;
class CdmQueryEnhanced;
class CdmSession;

/*
 * This method is the interface class for the dataaccesses like
 * sqllite, odbc, client or server. 
 * This class contains methods to manipulate and create objects
 * These method are only for internal use. They are not part of
 * the public interface!!!!!
 */
class IdmDataAccess 
{
   public:
    virtual ~IdmDataAccess() {}
    virtual int LoadObject(const CdmObjectContainer* p_pContainer,
                           long p_lObjectId,
                           CdmObject*& p_pCdmObject)= 0;

    virtual int LoadObject(const CdmObjectContainer* p_pContainer,
                           QString p_qstrKeyname,
                           CdmObject*& p_pCdmObject)= 0;

    virtual int LoadObjectContainer(long p_lObjectListId,
                                    CdmObjectContainer*& p_pContainer)= 0;


    virtual long GetNewClassId(long p_lDbId)= 0;
    virtual long GetNewObjectId(const CdmObjectContainer* p_pContainer)= 0;
    virtual int UpdateObject(CdmObject*& p_pCdmObject)= 0;
    virtual int UpdateObjectContainer(CdmObjectContainer*& p_pContainer)= 0;
    virtual int CreateScheme(QString p_qstrKeyname,
                             CdmScheme*& p_pCdmDatabaseManager )= 0;

    virtual int LoadSchemeBaseData(QString p_qstrKeyname,
                                   CdmScheme*& p_pCdmDatabaseManager)= 0;

    virtual int LoadSchemeBaseData(long p_lId,
                                   CdmScheme*& p_pCdmDatabaseManager)= 0;
public:
    virtual int Login(QString p_qstrApplication,
                      QString p_qstrLogin,
                      QString p_qstrPassword,
                      bool& p_bDemo,
                      int& p_iModules,
                      QString p_qstrVersion,
                      long& p_lSessionId,
                      CumUser*& p_rpCumUser)= 0;

    virtual int LoginLdap(QString p_qstrApplication,
                          QString p_qstrLogin,
                          QString p_qstrPassword,
                          long& p_lSessionId,
                          CumUser*& p_rUser) = 0;
    virtual int Logout()= 0;

    virtual int CreateUser(CumUser* p_pUser)= 0;

    virtual int RegisterUser(CumUser* p_pUser)= 0;

    virtual int DeleteUser(QString p_qstrLogin)= 0;
    virtual int DeleteUser(long p_lUserToDeleteId)= 0;
    virtual int DeleteClass(long p_lClassId)= 0;
    virtual int LoadClassManager(long p_lDatabaseId,
                                 CdmClassManager*& p_pCdmClassManager)= 0;

    virtual int DeleteScheme(QString p_qstrKeyname )= 0;
    virtual int DeleteObjectContainer(long p_lObjectListId)= 0;
    virtual int GetUserList(QLinkedList<CumUser*>& p_rqvlUser)= 0;
    virtual int GetContainerList(long p_lDbId,
                                 long lClassId,
                                 QMap<long,
                                    QString>& p_rqmObjectListsList)= 0;

    virtual int ExecuteQuery(CdmQuery* p_pCdmQuery)= 0;

    virtual int ExistScheme(QString p_qstrKeyname, bool& p_bResult)= 0;

    virtual int ExistClass(long p_lDbId,
                           QString p_qstrClassKeyname,
                           bool & p_bResult)= 0;

    virtual int ExistObjectContainer(long p_lDbId,
                                     QString p_qstrObjectListKeyname)= 0;

    virtual int LockObject(CdmObject* p_pObject,
                           bool & p_bResult)= 0;

    virtual int UnLockObject(CdmObject* p_pObject,
                             bool & p_bResult)= 0;


    virtual int LoadObjectContainer(long p_lDatabaseId,
                                    QString p_qstrKeyname,
                                    CdmObjectContainer*& p_pContainer)= 0;

    virtual int LoadEmptyObjectContainer(long p_lDataBaseId,
                                         QString p_qstrKeyname,
                                         CdmObjectContainer*& p_pContainer)= 0;

    virtual QByteArray ReadBinaryDocument(long p_lDbId,
                                          CdmValueBinaryDocument* p_pCdmBinaryDocument)= 0;


    virtual int UpdateBinaryDocument(long p_lDbId,
                                     CdmValueBinaryDocument* p_pCdmBinaryDocument )= 0;

    virtual long RenameUserGroup(long p_lGroupId,
                                 QString p_qstrNewName)= 0;

    virtual long CreateUserGroup(QString p_qstrGroupName)= 0;
    virtual long DeleteUserGroup(long p_llGroupId)= 0;
    virtual long AddUserToUserGroup(long p_lChangeUserId,
                                    long p_lUserGroupId)= 0;

    virtual long RemoveUserFromGroup(long p_lChangeUserId,
                                     long p_lUserGroupId)= 0;

    virtual long GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups,
                                  QString p_qstrSchemeUri)= 0;

    virtual long GetListOfUsersInList(long p_lUserGroupId,
                                      QLinkedList<CumUser*>& p_rqvlUserList)= 0;

    virtual long GetUserGroupMemberList(long p_lChangeUserId,
                                        QLinkedList<CumUserGroup*>& p_qvlUserGroups)= 0;

    virtual long AddLicense(QString p_qstrApplication,
                            QString p_qstrLicensee,
                            QString p_qstrLicensekey)= 0;

    virtual long FreeLicense()= 0;

    virtual long GetSchemeList(QLinkedList<QString>& p_qvlDatabases)= 0;

    virtual long UpdateScheme(CdmScheme* p_pCdmDatabase)= 0;

    virtual long GetCounterValue(const CdmObjectContainer* p_pContainer,
                                 CdmValue* p_pValue)= 0;

    virtual long GetNewContainerId(long p_lClassId)= 0;
    virtual QString GetConnectionDisplayString()= 0;
    virtual int UpdateUser(CumUser* p_pUser)= 0;

    virtual int LoadEmptyObjectContainer(long p_lDataBaseId,
                                         long p_lId,
                                         CdmObjectContainer*& p_pContainer)= 0;

    virtual int LoadObjects(QLinkedList<long>& p_rqvlObjects,
                            CdmObjectContainer*& p_pCdmObject)= 0;

    virtual int IsDemo(QString p_qstrApplication, QString p_qstrVersion)= 0;

    virtual long IsObjectUsed(const CdmObject* p_pObject)= 0;

    virtual bool LicenceCheck(QString p_qstrApplication,
                              bool& p_bDemo,
                              int& p_iModules,
                              QString p_qstrVersion)= 0;

    virtual bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)= 0;

    virtual bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)= 0;
    virtual CumUser* FindUserById(int p_iId)= 0;
    virtual CumUser* FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri)= 0;
    virtual CumUser* FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri)= 0;
    virtual CumUser* FindUser(QString p_qstrUserId, QString p_qstrPassword, QString p_qstrSchemeUri) = 0;
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri) = 0;
    virtual CumUserGroup* FindUserGroupById(int p_iId) = 0;
    virtual CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri) = 0;
    virtual QLinkedList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri) = 0;
    virtual QLinkedList<CumUserGroup*> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri) = 0;
    virtual long RefreshObject(CdmObject* p_pCdmObject)= 0;
    virtual long RefreshObjectContainer(CdmObjectContainer* p_pCdmObject)= 0;
    virtual long CountObjectsOnDb(CdmObjectContainer* p_pCdmObject)= 0;
    virtual int AddLanguage(long p_lDatabaseId,
                            QString p_qstrLanguage)= 0;

    virtual int DeleteLanguage(long p_lDatabaseId,
                               int p_iLanguageId)= 0;

    virtual int GetSchemeModifications(long p_lDatabaseId,
                                         QDate p_qdFrom,
                                         QDate p_qdTo,
                                         QList<CdmJournalItem*>& p_qlItems)= 0;

    virtual int GetObjectContainerModifications(const CdmObjectContainer* p_pContainer,
                                                QDate p_qdFrom,
                                                QDate p_qdTo,
                                                QList<CdmJournalItem*>& p_qlItems)= 0;

    virtual int GetObjectModifications(const CdmObject* p_pObject,
                                       QDate p_qdFrom,
                                       QDate p_qdTo,
                                       QList<CdmJournalItem*>& p_qlItems)= 0;

    virtual bool GetOwner(const CdmObject* p_pObject,
                          CdmObject*& p_pOwnerObject)= 0;

    virtual bool GetOwner(const CdmObjectContainer* p_pContainer,
                          CdmObject*& p_pOwnerObject)= 0;

    virtual bool GetReferences(const CdmObject* p_pObject,
                               QList<CdmObject*>& p_rqmReferences)= 0;

    virtual int UpdateClass(CdmClass*& p_pCdmClass)= 0;
    virtual int UpdatePackage(CdmPackage*& p_pCdmPackage)= 0;
    virtual void SetServerMode(bool p_bServerMode) = 0;
    virtual bool IsInServerMode() const = 0;
    virtual int GetInterfaceCallCounter() const = 0;
    virtual CdmObject* CreateObject(CdmObjectContainer* p_pContainer) = 0;
    virtual bool LockClassMethod(long p_lMethodId) = 0;
    virtual bool UnlockClassMethod(long p_lMethodId) = 0;
    virtual QVariant ExecuteFunction(CdmObject* p_PObject, QString p_qstrFunctionName, QVariantList p_qvlParameters) = 0;
    virtual QVariant EvaluateFormula(const CdmObject* p_pObject, QString p_qstrFormula) = 0;
    virtual bool GetRfcExecution() const = 0;
    virtual void PrintContainer(QString p_qstrTemplateName, CdmObjectContainer *p_pContainer) = 0;
    virtual void PrintObject(QString p_qstrTemplateName, CdmObject *p_pObject) = 0;
    virtual CdmSession* FindSession(int p_iSessionId) = 0;
    virtual CdmSession* FindSession(QString p_qstrBaseAuth) = 0;
    virtual void UpdateSession(int p_iSessionId) = 0;
    virtual void UpdateSession(QString p_qstrBaseAuth) = 0;
    virtual void SessionTimeoutCheck(int p_iTimeoutMin) = 0;

};
#endif // //IdmDataAccess_H
