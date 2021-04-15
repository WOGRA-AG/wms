/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMMANAGER_H
#define CDMMANAGER_H



// System and QT Includes
#include <QLinkedList>


// own Includes
#include "CdmSessionManager.h"
#include "CdmLocatedElement.h"
#include "CdmSettings.h"
#include "datamanager.h"


// forwards
class QString;
class CdmModelElement;
class QDomDocument;
class CdmSettings;
class CdmLogging;
class CdmClassManager;
class CdmClass;
class CdmObjectContainer;
class CdmScheme;
class IdmDataAccess;
class CdmContainerManager;
class CumUserManager;
class CumUser;
class CdmExecutor;

/*
 * This class manages the complete framework.
 * With the help of this class you can reach each
 * loaded Scheme.
 */
class WMSMANAGER_API CdmDataProvider : public CdmLocatedElement
{
    Q_OBJECT

private:
    QLinkedList<CdmScheme*> m_qlSchemes;
    IdmDataAccess* m_rpIdmDataAccess;
    CumUserManager* m_pCumUserManager;
    QString m_qstrBinaryDirectory;
    bool m_bDemo;
    int m_iModules;
    QString m_qstrSystemApplicationName;
    QString m_qstrApplicationVersion;
    CdmScheme* m_pCdmSchemeCurrent;
    CdmExecutor* m_pExecutor;

    friend class CdmSession;
    friend class CdmDataAccessHelper;

private:
    CdmDataProvider(IdmDataAccess* p_pIdmDataAccess);
    // only added for neo4J testcases, so it is not neccessary to regulary login and load scheme
    void AddCurrentScheme(CdmScheme* p_pScheme);
    CdmLocatedElement* GetUriObjectInCurrentScheme(QString& p_qstrUri);

public:
    virtual ~CdmDataProvider();
    CdmSettings* GetSettings();
    static QString GetVersion();
    void LicenceCheck(QString& p_qstrApplication, QString& p_qstrVersion);
    QString GetWmsVersion() const;
    bool IsLoggedInUserAdmin() const;
    bool IsDemo() const;
    int GetModulesId() const;
    void SetSystemApplicationName(QString& p_qstrName);
    void SetApplicationVersion(QString p_qstrVersion);
    void CreateSettings(EdmSettingsMode p_eDmSettingsMode);
    long LoadClassManager(QString& p_qstrSchemeKeyname);
    long LoadScheme(QString& p_qstrDatabaseName);
    long LoadScheme(int p_iSchemeId);
    IdmDataAccess* GetDataAccess();
    long RemoveScheme(long p_lDatabaseId);
    long RemoveScheme(QString& p_qstrDatabaseName);
    long CreateScheme(QString& p_qstrDbName);
    QVariant GetVariant() const;
    static void ReplaceUnnecessaryUriParts(QString &p_qstrUri);
    static void ReplaceUnnecessaryUriPartsAndScheme(QString &p_qstrUri);
    static QString GetUriType(QString& p_qstrUri);
    bool IsClientServerMode() const;
    QString GetClassKeynameFromUri(QString& p_qstrUri);
    CdmExecutor *GetExecutor() const;
    bool IsSchemeLoaded(QString& p_qstrSchemeName);
    CdmScheme *GetSchemeLocal(QString& p_qstrSchemeName);
    CdmScheme *GetSchemeLocal(long p_lSchemeId);
    bool IsSchemeLoaded(long p_lSchemeName);
    virtual bool IsDataProvider() const;
    QString GetUri() const;
    QString GetUriInternal() const;
    void ExtractDataFromUri(QString &p_qstrUri, QString &p_qstrType, QString &p_qstrMajorId, QString &p_qstrMinorId, QString &p_qstrValue);

public slots:
    CdmClassManager* GetClassManager(long p_lSchemeId);
    CdmClassManager* GetClassManager(QString& p_qstrSchemeName);
    CdmScheme* FindSchemeById(long p_lId);
    CdmScheme* FindSchemeByName(QString& p_qstrDatabaseName);
    CdmContainerManager* GetContainerManager(long p_lSchemeId);
    CdmContainerManager* GetContainerManager(QString& p_qstrSchemeName);
    long GetSessionId() const;
    static CdmObjectContainer* GetObjectContainer(QString& p_qstrScheme, QString& p_qstrObjectList);
    static CdmClass* GetClass(QString& p_qstrScheme, QString& p_qstrClassName);
    long ExistScheme(QString p_qstrKeyname);
    CumUserManager* GetUserManager();
    long GetUserId() const;
    void GetSchemeList(QLinkedList<QString>& p_rqvlDatabases);
    QString GetSystemApplicationVersion() const;
    QString GetApplicationVersion() const;
    CdmObjectContainer* GetObjectContainer(int p_iDatabaseId, int p_iObjectListId);
    const CumUser* GetUser() const;
    void SetCurrentScheme(CdmScheme* p_pCdmDatabase);
    CdmScheme* GetCurrentScheme();
    static CdmObjectContainer* GetObjectContainer(QString p_qstrObjectList);
    static CdmObjectContainer* GetObjectContainer(long ObjectListId);
    CdmContainerManager* GetContainerManager(CdmScheme* p_pCdmDatabase);
    long LoadClassManager(long p_lSchemeId);
    QString GetCurrentLanguage() const;
    void SetCurrentLanguage(QString& p_iId);
    CdmClassManager* GetClassManager();
    CdmContainerManager* GetContainerManager();
    static QString GetBuild();
    CdmLocatedElement* GetUriObject(QString &p_qstrUri);
    QString GetUriMajorId(QString& p_qstrUri);
    static CdmObjectContainer* GetObjectContainerEmpty(QString& p_qstrObjectList);
    void RemoveAllLocalSchemes();
    void RemoveLocalScheme(QString& p_qstrName);
};

#endif //
