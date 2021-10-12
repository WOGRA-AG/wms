/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <QString>
#include <QStringList>
#include <qfile.h>
#include <qdom.h>
#include <qtextstream.h>
#include <QList>

// WMS Commons
#include "CwmsUtilities.h"


// own Includes
#include "wmsdefines.h"
#include "CdmGlobalContext.h"
#include "CdmModelElement.h"
#include "CdmExecutor.h"
#include "CdmExecutorRemote.h"
#include "CdmContainerManager.h"
#include "IdmDataAccess.h"
#include "CdmSettings.h"
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "CdmClassManager.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"


CdmDataProvider::CdmDataProvider(IdmDataAccess* p_pIdmDataAccess)
    : m_rpIdmDataAccess(p_pIdmDataAccess),
      m_bDemo(false),
      m_iModules(0),
      m_pCdmSchemeCurrent(nullptr),
      m_pExecutor(nullptr)
{
    if (!p_pIdmDataAccess->GetRfcExecution())
    {
        m_pExecutor = new CdmExecutor();
    }
    else
    {
        m_pExecutor = new CdmExecutorRemote();
    }

    m_pCumUserManager = new CumUserManager(p_pIdmDataAccess);
}

CdmDataProvider::~CdmDataProvider(  )
{
    RemoveAllLocalSchemes();
    DELPTR(m_pCumUserManager);
    DELPTR(m_pExecutor);
    // m_pIdmDataAccess must not be deleted it is a plugin
    // and will be unloaded at application termination.
}

void CdmDataProvider::LicenceCheck(QString &p_qstrApplication, QString &p_qstrVersion)
{
    if (CHKPTR(m_rpIdmDataAccess))
    {
        m_rpIdmDataAccess->LicenceCheck(p_qstrApplication,
                                        m_bDemo,
                                        m_iModules,
                                        p_qstrVersion);
        SetApplicationVersion(p_qstrVersion);
    }
}


bool CdmDataProvider::IsLoggedInUserAdmin() const
{
    bool bRet = false;

    const CumUser* pCumUser = GetUser();

    if (CHKPTR(pCumUser))
    {
        bRet = pCumUser->IsAdministrator();
    }

    return bRet;
}

bool CdmDataProvider::IsDemo() const
{
    return m_bDemo;
}


int CdmDataProvider::GetModulesId() const
{
    return m_iModules;
}

QString CdmDataProvider::GetWmsVersion() const
{
    return WMS_LIB_VERSION;
}

void CdmDataProvider::SetSystemApplicationName(QString &p_qstrName)
{
    m_qstrSystemApplicationName = p_qstrName;
}

QString CdmDataProvider::GetSystemApplicationVersion() const
{
    return m_qstrSystemApplicationName;
}

void CdmDataProvider::SetApplicationVersion(QString p_qstrVersion)
{
    m_qstrApplicationVersion = p_qstrVersion;
}

QString CdmDataProvider::GetApplicationVersion() const
{
    return m_qstrApplicationVersion;
}

void CdmDataProvider::SetCurrentScheme(CdmScheme* p_pCdmDatabase)
{
    m_pCdmSchemeCurrent = p_pCdmDatabase;
}

CdmScheme* CdmDataProvider::GetCurrentScheme()
{
    return m_pCdmSchemeCurrent;
}

qint64 CdmDataProvider::CreateScheme(QString &p_qstrDbName)
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        CdmScheme* pScheme = nullptr;
        lRet = m_rpIdmDataAccess->CreateScheme(p_qstrDbName, pScheme);

        if (pScheme)
        {
            if (!m_qlSchemes.contains(pScheme))
            {
                m_qlSchemes.append(pScheme);
            }

            SetCurrentScheme(pScheme);
            lRet = pScheme->GetId();
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}


qint64 CdmDataProvider::LoadScheme(QString &p_qstrDatabaseName)
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        CdmScheme* pCdmDatabase = nullptr;

        if (!IsSchemeLoaded(p_qstrDatabaseName))
        {
            lRet = m_rpIdmDataAccess->LoadSchemeBaseData(p_qstrDatabaseName,
                                                         pCdmDatabase);

            if(pCdmDatabase)
            {
                m_qlSchemes.append(pCdmDatabase);
            }
        }

        if (IsSchemeLoaded(p_qstrDatabaseName))
        {
            SYNCHRONIZED;
            LoadClassManager(p_qstrDatabaseName);
            SetCurrentScheme(GetSchemeLocal(p_qstrDatabaseName));
            lRet = EC(eDmOk);
        }
    }

    return lRet;
}

qint64 CdmDataProvider::LoadScheme(int p_iSchemeId)
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        CdmScheme* pCdmDatabase = nullptr;

        if (!IsSchemeLoaded(p_iSchemeId))
        {
            lRet = m_rpIdmDataAccess->LoadSchemeBaseData(p_iSchemeId,
                                                         pCdmDatabase);

            if(pCdmDatabase)
            {
                m_qlSchemes.append(pCdmDatabase);
            }
        }

        if (IsSchemeLoaded(p_iSchemeId))
        {
            LoadClassManager(p_iSchemeId);
            SetCurrentScheme(GetSchemeLocal(p_iSchemeId));
            lRet = EC(eDmOk);
        }
    }

    return lRet;
}

bool CdmDataProvider::IsSchemeLoaded(QString &p_qstrSchemeName)
{
    return (GetSchemeLocal(p_qstrSchemeName) != nullptr);
}

bool CdmDataProvider::IsSchemeLoaded(qint64 p_lSchemeName)
{
    return (GetSchemeLocal(p_lSchemeName) != nullptr);
}

bool CdmDataProvider::IsDataProvider() const
{
    return true;
}

CdmScheme* CdmDataProvider::GetSchemeLocal(QString &p_qstrSchemeName)
{
    CdmScheme* pLocal = nullptr;
    QList<CdmScheme*>::iterator qIt = m_qlSchemes.begin();
    QList<CdmScheme*>::iterator qItEnd = m_qlSchemes.end();

    for (; qIt != qItEnd; ++qIt)
    {
        if ((*qIt)->GetSchemeName() == p_qstrSchemeName)
        {
            pLocal = (*qIt);
            break;
        }
    }

    return pLocal;
}

CdmScheme* CdmDataProvider::GetSchemeLocal(qint64 p_lSchemeId)
{
    CdmScheme* pLocal = nullptr;
    QList<CdmScheme*>::iterator qIt = m_qlSchemes.begin();
    QList<CdmScheme*>::iterator qItEnd = m_qlSchemes.end();

    for (; qIt != qItEnd; ++qIt)
    {
        if ((*qIt)->GetId() == p_lSchemeId)
        {
            pLocal = (*qIt);
            break;
        }
    }

    return pLocal;
}

qint64 CdmDataProvider::ExistScheme(QString p_qstrKeyname)
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        bool bRet = false;

        lRet = m_rpIdmDataAccess->ExistScheme(p_qstrKeyname, bRet);

        if(lRet < 0)
        {
            ERR("Not possible to check if database exists. Error Code: " + QString::number(lRet));
        }
        else
        {
            if(bRet)
            {
                lRet = EC(eDmTrue);
            }
            else
            {
                lRet = EC(eDmFalse);
            }
        }
    }

    return lRet;
}


CdmScheme* CdmDataProvider::FindSchemeById(qint64 p_lId)
{
    CdmScheme* pCdmScheme = nullptr;

    if (m_pCdmSchemeCurrent && m_pCdmSchemeCurrent->GetId() == p_lId)
    {
        pCdmScheme = m_pCdmSchemeCurrent;
    }
    else
    {
        QList<CdmScheme*>::iterator iIt = m_qlSchemes.begin();
        QList<CdmScheme*>::iterator iItEnd = m_qlSchemes.end();

        for(; iIt != iItEnd; ++iIt)
        {
            CdmScheme* pCdmSchemeTemp = (*iIt);

            if(CHKPTR(pCdmSchemeTemp))
            {
                if(pCdmSchemeTemp->GetId() == p_lId)
                {
                    if(pCdmSchemeTemp->GetId() == p_lId)
                    {
                        pCdmScheme = pCdmSchemeTemp;
                        SetCurrentScheme(pCdmScheme);
                        break;
                    }
                }
            }

            if (!pCdmScheme)
            {
                LoadScheme(p_lId);
                pCdmScheme = GetCurrentScheme();
            }
        }
    }

    return pCdmScheme;
}

CdmScheme* CdmDataProvider::FindSchemeByName(QString &p_qstrDatabaseName)
{
    CdmScheme* pCdmDatabase = nullptr;

    QList<CdmScheme*>::iterator iIt = m_qlSchemes.begin();
    QList<CdmScheme*>::iterator iItEnd = m_qlSchemes.end();

    for(; iIt != iItEnd; ++iIt)
    {
        CdmScheme* pCdmDatabaseTemp = (*iIt);
        if(pCdmDatabaseTemp)
        {
            if(pCdmDatabaseTemp->GetSchemeName() == p_qstrDatabaseName)
            {
                pCdmDatabase = pCdmDatabaseTemp;
                SetCurrentScheme(pCdmDatabase);
                break;
            }
        }
    }

    if(!pCdmDatabase)
    {
        LoadScheme(p_qstrDatabaseName);
        pCdmDatabase = GetCurrentScheme();
    }

    return pCdmDatabase;
}

CdmSettings* CdmDataProvider::GetSettings()
{
    return CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetSettings();
}

QString CdmDataProvider::GetVersion()
{
    QString qstrVersion = WMS_LIB_VERSION;
    qstrVersion += " Build " + GetBuild();
    return qstrVersion;
}

QString CdmDataProvider::GetBuild()
{
    QString qstrDate = __DATE__;
    QString qstrBuild = qstrDate;

    // a small hack for generating a nice date format
    const char mydate[] =
    {
        __DATE__[4] == ' ' ? '0' : __DATE__[4], __DATE__[5], '.',

        __DATE__[0] == 'O' ||
        __DATE__[0] == 'N' ||
        __DATE__[0] == 'D' ? '1' : '0',

        __DATE__[0] == 'J' && __DATE__[0] == 'a' ? '1' :
        __DATE__[0] == 'F' ? '2' :
        __DATE__[0] == 'M' && __DATE__[2] == 'r' ? '3' :
        __DATE__[0] == 'A' && __DATE__[1] == 'p' ? '4' :
        __DATE__[0] == 'M' ? '5' :
        __DATE__[0] == 'J' && __DATE__[2] == 'n' ? '6' :
        __DATE__[0] == 'J' ? '7' :
        __DATE__[0] == 'A' ? '8' :
        __DATE__[0] == 'S' ? '9' :
        __DATE__[0] == 'O' ? '0' :
        __DATE__[0] == 'N' ? '1' :
        __DATE__[0] == 'D' ? '2' : 'X',

        '.',
        __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10], '\0'

    };


    QDate qdDate = QDate::fromString(mydate, "dd.MM.yyyy");

    if (qdDate.isValid())
    {
        int iDays = qdDate.daysTo(QDate(2000,4,1)) * (-1);
        qstrBuild = QString::number(iDays);
    }

    return qstrBuild;
}

CdmClassManager* CdmDataProvider::GetClassManager(qint64 p_lDatabaseId)
{
    CdmClassManager* pCdmClassManager = nullptr;
    CdmScheme* pCdmDatabase = FindSchemeById(p_lDatabaseId);

    if(pCdmDatabase) // can be nullptr if not loaded
    {
        pCdmClassManager = pCdmDatabase->GetClassManager();
    }
    else
    {
        WARNING("Class Manager not found");
    }

    return pCdmClassManager;
}

CdmClassManager* CdmDataProvider::GetClassManager(QString &p_qstrDatabaseName)
{
    CdmClassManager* pCdmClassManager = nullptr;
    CdmScheme* pCdmDatabase = FindSchemeByName(p_qstrDatabaseName);

    if(CHKPTR(pCdmDatabase))
    {
        pCdmClassManager = pCdmDatabase->GetClassManager();
    }

    return pCdmClassManager;
}

CdmClassManager* CdmDataProvider::GetClassManager()
{
    CdmClassManager* pCdmClassManager = nullptr;
    CdmScheme* pCdmDatabase = GetCurrentScheme();

    if(CHKPTR(pCdmDatabase))
    {
        pCdmClassManager = pCdmDatabase->GetClassManager();
    }

    return pCdmClassManager;
}

CdmContainerManager* CdmDataProvider::GetContainerManager(CdmScheme* p_pCdmDatabase)
{
    CdmContainerManager* pContainerManager = nullptr;

    if(CHKPTR(p_pCdmDatabase))
    {
        pContainerManager = p_pCdmDatabase->GetContainerManager();
    }

    return pContainerManager;
}

CdmContainerManager* CdmDataProvider::GetContainerManager(qint64 p_lDatabaseId)
{
    CdmContainerManager* pContainerManager = nullptr;

    if (p_lDatabaseId > 0)
    {
        CdmScheme* pCdmDatabase = FindSchemeById(p_lDatabaseId);

        if(CHKPTR(pCdmDatabase))
        {
            pContainerManager = pCdmDatabase->GetContainerManager();
        }
    }
    else
    {
        INFO("Invalid Database Id: " + QString::number(p_lDatabaseId));
    }

    return pContainerManager;
}

CdmContainerManager* CdmDataProvider::GetContainerManager()
{
    CdmContainerManager* pContainerManager = nullptr;
    CdmScheme* pCdmDatabase = GetCurrentScheme();

    if(CHKPTR(pCdmDatabase))
    {
        pContainerManager = pCdmDatabase->GetContainerManager();
    }

    return pContainerManager;
}

CdmContainerManager* CdmDataProvider::GetContainerManager(QString &p_qstrDatabaseName)
{
    CdmContainerManager* pContainerManager = nullptr;
    CdmScheme* pCdmDatabase = FindSchemeByName(p_qstrDatabaseName);

    if(CHKPTR(pCdmDatabase))
    {
        pContainerManager = pCdmDatabase->GetContainerManager();
    }

    return pContainerManager;
}

IdmDataAccess* CdmDataProvider::GetDataAccess()
{
    return m_rpIdmDataAccess;
}

qint64 CdmDataProvider::RemoveScheme(qint64 p_lDatabaseId)
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;

    CdmScheme* pScheme = nullptr;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        QList<CdmScheme*>::iterator iIt = m_qlSchemes.begin();
        QList<CdmScheme*>::iterator iItEnd = m_qlSchemes.end();

        for(; iIt != iItEnd; ++iIt)
        {
            pScheme = (*iIt);

            if(CHKPTR(pScheme))
            {
                if(pScheme->GetId() == p_lDatabaseId)
                {
                    lRet = m_rpIdmDataAccess->DeleteScheme(pScheme->GetSchemeName());

                    if(lRet > 0)
                    {
                        m_qlSchemes.erase(iIt);
                        DELPTR(pScheme);
                        INFO("DB Deleted!!!");
                        break;
                    }
                }
            }
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

qint64 CdmDataProvider::RemoveScheme(QString &p_qstrDatabaseName)
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;

    if (CHKPTR(m_rpIdmDataAccess))
    {
        lRet = m_rpIdmDataAccess->DeleteScheme(p_qstrDatabaseName);

        if(lRet > 0)
        {
            QList<CdmScheme*>::iterator qllIt = m_qlSchemes.begin();
            QList<CdmScheme*>::iterator qllItEnd = m_qlSchemes.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                CdmScheme* pScheme = *qllIt;

                if (pScheme && pScheme->GetSchemeName() == p_qstrDatabaseName)
                {
                    if (m_pCdmSchemeCurrent == pScheme)
                    {
                        m_pCdmSchemeCurrent = nullptr;
                    }

                    m_qlSchemes.removeAll(pScheme);
                    DELPTR(pScheme);
                    INFO("DB Deleted!!!");
                    break;
                }
            }
        }
    }

    return lRet;
}

void CdmDataProvider::RemoveAllLocalSchemes()
{
    QList<CdmScheme*>::iterator qllIt = m_qlSchemes.begin();
    QList<CdmScheme*>::iterator qllItEnd = m_qlSchemes.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CdmScheme* pDatabase = *qllIt;
        DELPTR(pDatabase);
    }

    m_qlSchemes.clear();
}

void CdmDataProvider::RemoveLocalScheme(QString &p_qstrName)
{
    CdmScheme* pScheme = FindSchemeByName(p_qstrName);

    if (pScheme)
    {
        m_qlSchemes.removeAll(pScheme);
        DELPTR(pScheme);
    }
}

void CdmDataProvider::AddCurrentScheme(CdmScheme *p_pScheme)
{
    if (CHKPTR(p_pScheme))
    {
        m_qlSchemes.append(p_pScheme);
        m_pCdmSchemeCurrent = p_pScheme;
    }
}

QVariant CdmDataProvider::GetVariant() const
{
    return QVariant();
}

qint64 CdmDataProvider::GetSessionId() const
{
    return CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
}

CdmObjectContainer* CdmDataProvider::GetObjectContainer(QString p_qstrObjectList)
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

        if(CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindContainerByKeyname(p_qstrObjectList);
        }
    }

    return pContainer;
}

CdmObjectContainer* CdmDataProvider::GetObjectContainer(qint64 ObjectListId)
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

        if(CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindContainerById(ObjectListId);
        }
    }

    return pContainer;
}

CdmObjectContainer* CdmDataProvider::GetObjectContainerEmpty(QString &p_qstrObjectList)
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

        if(CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrObjectList);
        }
    }

    return pContainer;
}

CdmObjectContainer* CdmDataProvider::GetObjectContainer(QString& p_qstrDataBase, QString& p_qstrObjectList)
{
    CdmObjectContainer* pContainer = nullptr;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(p_qstrDataBase);

        if(CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindContainerByKeyname(p_qstrObjectList);
        }
    }

    return pContainer;
}


CdmObjectContainer* CdmDataProvider::GetObjectContainer(int p_iDatabaseId, int p_iObjectListId)
{
    CdmObjectContainer* pContainer = nullptr;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(p_iDatabaseId);

        if(CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindContainerById(p_iObjectListId);
        }
    }

    return pContainer;
}

CdmClass* CdmDataProvider::GetClass(QString& p_qstrDatabase, QString& p_qstrClassName)
{
    CdmClass* pCdmClass = nullptr;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(p_qstrDatabase);

        if(pCdmClassManager)
        {
            pCdmClass = pCdmClassManager->FindClassByKeyname(p_qstrClassName);
        }
    }

    return pCdmClass;
}

qint64 CdmDataProvider::LoadClassManager(qint64 p_lDbId)
{
   qint64 lRet = CdmLogging::eDmUnknownDbError;
    CdmScheme* pCdmDatabase = FindSchemeById(p_lDbId);

    if(!CHKPTR(pCdmDatabase))
    {
        ERR("Database not found could not load classmanager!!!");
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

qint64 CdmDataProvider::LoadClassManager(QString &p_qstrDbKeyname)
{
    CdmScheme* pCdmDatabase = FindSchemeByName(p_qstrDbKeyname);
   qint64 lRet = CdmLogging::eDmUnknownDbError;

    if(!CHKPTR(pCdmDatabase))
    {
        ERR("Database not found could not load classmanager!!!");
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

CumUserManager* CdmDataProvider::GetUserManager()
{
    return m_pCumUserManager;
}

qint64 CdmDataProvider::GetUserId() const
{
    return CdmSessionManager::GetSessionManager()->GetCurrentUserId();
}

const CumUser* CdmDataProvider::GetUser() const
{
    return CdmSessionManager::GetSessionManager()->GetCurrentUser();
}

void CdmDataProvider::GetSchemeList(QList<QString>& p_rqvlDatabases)
{
    IdmDataAccess* pIdmDataAccess = nullptr;
    pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        QList<QString> qllDatabases;
        pIdmDataAccess->GetSchemeList(qllDatabases);

        QList<QString>::iterator qvlIt = qllDatabases.begin();
        QList<QString>::iterator qvlItEnd = qllDatabases.end();

        for (; qvlIt != qvlItEnd; ++ qvlIt)
        {
            QString qstrDatabase = (*qvlIt);
            CdmScheme* pCdmDatabase = nullptr;
            pIdmDataAccess->LoadSchemeBaseData(qstrDatabase,
                                               pCdmDatabase);

            if (pCdmDatabase)
            {
                CdmRights& cRights = pCdmDatabase->GetRights();

                if (cRights.HasCurrentUserReadAccess())
                {
                    CdmRights& cRights = pCdmDatabase->GetRights();

                    if (cRights.HasCurrentUserReadAccess())
                    {
                        p_rqvlDatabases.append(qstrDatabase);
                    }

                    DELPTR(pCdmDatabase);
                }
            }

        }
    }
}

bool CdmDataProvider::IsClientServerMode() const
{
    return m_rpIdmDataAccess->IsInServerMode();
}

QString CdmDataProvider::GetCurrentLanguage() const
{
    QString qstrName;

    if (m_pCdmSchemeCurrent)
    {
        qstrName = m_pCdmSchemeCurrent->GetCurrentLanguageName();
    }

    return qstrName;
}

void CdmDataProvider::SetCurrentLanguage(QString &p_iId)
{
    if (m_pCdmSchemeCurrent)
    {
        m_pCdmSchemeCurrent->SetCurrentLanguage(p_iId);
    }
}

void CdmDataProvider::ExtractDataFromUri(QString& p_qstrUri, QString& p_qstrType, QString& p_qstrMajorId, QString& p_qstrMinorId, QString& p_qstrValue)
{
    ReplaceUnnecessaryUriParts(p_qstrUri);
    QStringList qstrlUri = p_qstrUri.split("/", QString::SkipEmptyParts);
    int posStart = 0;

    if (qstrlUri.count() > posStart)
    {
        if (qstrlUri[posStart].length() > 0)
        {
            p_qstrType = qstrlUri[posStart];
        }
    }

    if (qstrlUri.count() > ++posStart)
    {
        if (qstrlUri[posStart].length() > 0)
        {
            p_qstrMajorId = qstrlUri[posStart];
        }
    }

    if (qstrlUri.count() > ++posStart)
    {
        if (qstrlUri[posStart].length() > 0)
        {
            p_qstrMinorId = qstrlUri[posStart];
        }
    }

    if (qstrlUri.count() > ++posStart)
    {
        if (qstrlUri[posStart].length() > 0)
        {
            p_qstrValue = qstrlUri[posStart];
        }
    }
}

CdmLocatedElement* CdmDataProvider::GetUriObjectInCurrentScheme(QString &p_qstrUri)
{
    CdmLocatedElement* pCdmBase = nullptr;
    QString qstrType;
    QString qstrMajorId;
    QString qstrMinorId;
    QString qstrValue;
    ExtractDataFromUri(p_qstrUri, qstrType, qstrMajorId, qstrMinorId, qstrValue);

    if (CHKPTR(m_pCdmSchemeCurrent))
    {
        pCdmBase = m_pCdmSchemeCurrent->GetBaseObject(qstrType, qstrMajorId, qstrMinorId, qstrValue);
    }
    else
    {
        ERR(tr("No current Scheme set.\n It is not possible to get the right object."));
    }


    return pCdmBase;
}


CdmLocatedElement* CdmDataProvider::GetUriObject(QString& p_qstrUri)
{
    if (!m_pCdmSchemeCurrent)
    {
        ReplaceUnnecessaryUriParts(p_qstrUri);
        QStringList qstrlUri = p_qstrUri.split("/");

        if (qstrlUri.count() > 1)
        {
            QString qstrType = qstrlUri[0];

            if (qstrType != WMS_USER && qstrType != WMS_USERGROUP)
            {
                QString qstrScheme = qstrlUri[1];
                if (CwmsUtilities::IsNumber(qstrScheme))
                {
                    FindSchemeById(qstrScheme.toInt());
                }
                else
                {
                    FindSchemeByName(qstrScheme);
                }
            }
        }
    }
    else
    {
        QString qstrType;
        QString qstrMajorId;
        QString qstrMinorId;
        QString qstrValue;
        ReplaceUnnecessaryUriParts(p_qstrUri); // added new for test
        ExtractDataFromUri(p_qstrUri, qstrType, qstrMajorId, qstrMinorId, qstrValue);

        if (qstrMajorId != m_pCdmSchemeCurrent->GetSchemeName())
        {
            if (CwmsUtilities::IsNumber(qstrMajorId))
            {
                FindSchemeById(qstrMajorId.toInt());
            }
            else
            {
                FindSchemeByName(qstrMajorId);
            }
        }
    }

    ReplaceUnnecessaryUriPartsAndScheme(p_qstrUri);
    return GetUriObjectInCurrentScheme(p_qstrUri);
}

void CdmDataProvider::ReplaceUnnecessaryUriParts(QString& p_qstrUri)
{
    QString qstrUri = p_qstrUri;
    QString qstrUriHost = CdmLocatedElement::CreateUriHost();

    if (p_qstrUri.startsWith(WMS_URI_START))
    {
        p_qstrUri = p_qstrUri.remove(WMS_URI_START "/");
    }
    else if(p_qstrUri.startsWith(WMS_URI_START_HTTPS))
    {
        p_qstrUri = p_qstrUri.remove(WMS_URI_START_HTTPS "/");
    }
    else if (p_qstrUri.startsWith(WMS_URI_START_SCHEME_INDEPENDENT))
    {
        p_qstrUri = p_qstrUri.remove(WMS_HTTP);
    }
    else if (p_qstrUri.startsWith(WMS_URI_START_SCHEME_INDEPENDENT_HTTPS))
    {
        p_qstrUri = p_qstrUri.remove(WMS_HTTPS);
    }
    else if (p_qstrUri.startsWith(qstrUriHost))
    {
        p_qstrUri = p_qstrUri.remove(qstrUriHost + "/");
    }
    else if (p_qstrUri.startsWith(WMS_HTTP))
    {
        p_qstrUri = p_qstrUri.remove(WMS_HTTP);
    }
    else if (p_qstrUri.startsWith(WMS_HTTPS))
    {
        p_qstrUri = p_qstrUri.remove(WMS_HTTPS);
    }

    CwmsUtilities::OptimizeUrl(p_qstrUri);
}

void CdmDataProvider::ReplaceUnnecessaryUriPartsAndScheme(QString& p_qstrUri)
{
    ReplaceUnnecessaryUriParts(p_qstrUri);
    int pos = p_qstrUri.indexOf("/", 1);
    int iEndPos = p_qstrUri.indexOf("/", pos + 1);

    if (pos > 0 && iEndPos > 0)
    {
        //QString qstrRemovablePart = p_qstrUri.mid(pos, iEndPos - pos);
        p_qstrUri = p_qstrUri.remove(pos, iEndPos - pos);
    }
}


QString CdmDataProvider::GetUriMajorId(QString &p_qstrUri)
{
    QString qstrMajorId;
    ReplaceUnnecessaryUriParts(p_qstrUri);
    QStringList qstrlUri = p_qstrUri.split("/");

    if (qstrlUri.count() > 2)
    {
        qstrMajorId = qstrlUri[2];
    }

    return qstrMajorId;
}

QString CdmDataProvider::GetUriType(QString &p_qstrUri)
{
    QString qstrType;
    ReplaceUnnecessaryUriParts(p_qstrUri);
    QStringList qstrlUri = p_qstrUri.split("/");

    if (qstrlUri.count() > 0)
    {
        qstrType = qstrlUri[0];
    }

    return qstrType;
}


QString CdmDataProvider::GetClassKeynameFromUri(QString &p_qstrUri)
{
    QString qstrMajorId;
    ReplaceUnnecessaryUriParts(p_qstrUri);
    QStringList qstrlUri = p_qstrUri.split("/", QString::SkipEmptyParts);
    QString qstrType = qstrlUri[0];
    int iCount = qstrlUri.count();

    if (qstrType == WMS_URI_CLASS && iCount >= 2)
    {
        qstrMajorId= qstrlUri[1];
    }

    return qstrMajorId;
}

CdmExecutor *CdmDataProvider::GetExecutor() const
{
    return m_pExecutor;
}

QString CdmDataProvider::GetUri() const
{
    return CreateUri(WMS_URI_DATAPROVIDER, "");
}

QString CdmDataProvider::GetUriInternal() const
{
    return CreateUriPath(WMS_URI_DATAPROVIDER, "", "", "");
}
