/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmSessionManager.h
 ** Started Implementation: 2012/04/03
 ** Description:
 **
 ** Implements the factory for the manager objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CDMSESSIONMANAGER_H
#define CDMSESSIONMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QThreadStorage>
#include <QDateTime>
#include <QTimer>
#include <QCache>
#include <QMutex>

// Own Includes
#include "datamanager.h"
#include "CdmSettings.h"
#include "CdmLocatedElement.h"
#include "IdmEventStoreManager.h"

// Forwards
class CumUser;
class CdmDataProvider;
class IdmDataAccess;
class CdmSession;
class CdmExecutorAddOnManager;
class CdmGlobalContext;

// TypeDefs


/* 
 * This class implements the factory for the manager objects
 */
class WMSMANAGER_API CdmSessionManager : public CdmLocatedElement
{
    Q_OBJECT

private:
    QThreadStorage<QCache<QString, QVariant> > m_qSessionData;
    QMap<int, CdmSession*> m_qmSessionManager;
    QMap<QString, CdmSession*> m_qmSessionManagerAuth;
    bool m_bServerMode;
    int m_iSessionTimeoutMinutes;
    int m_iSessionTimeoutIntervallmsecs;
    CdmExecutorAddOnManager* m_pAddOnManager;
    bool m_bPerSessionManager;
    CdmGlobalContext* m_pGlobalContext;
    QDateTime m_qdtLastSessionCheck;
    QString m_qstrApplicationName;
    bool m_bCollectSessionGarbage;
    IdmEventStoreManager *m_pEventStoreManager;
    IdmDataAccess* m_pDataAccess;

    static CdmSessionManager* m_spSessionManager;

    friend class CdmDataAccessHelper;
    friend class CdmSession;

signals:
    void SessionTimedOut(long p_lSessionId);
    void SessionTimedOut(QString p_qstrBaseAuth);


private:
    CdmSessionManager(EdmSettingsMode p_eMode);
    virtual ~CdmSessionManager();

public:
    void SetSessionThread(int p_iSession);
    int GetCurrentSessionId();
    int CreateNewSession(QString p_qstrLogin,
                         QString p_qstrPassword);
    CdmDataProvider* FindDataProvider();
    void DeleteSession();
    int GetSessionCount();
    int GetThreadCount();
    void SetAddOnManager(CdmExecutorAddOnManager *rpAddOnManager);
    bool GetServerMode() const;
    void SetServerMode(bool bServerMode);
    int GetSessionTimeoutMinutes() const;
    void SetSessionTimeoutMinutes(int iSessionTimeoutMinutes);
    long GetCurrentUserId() const;
    const CumUser *GetCurrentUser() const;
    int CreateNewSessionLdap(QString p_qstrLogin, QString p_qstrPassword);
    CdmGlobalContext *GetGlobalContext();
    CdmSession *FindSessionById(int p_iSessionId);
    CdmSession *FindSession();
    CdmSession *FindSessionByBaseAuth(QString p_qstrAuth);
    void SetSessionThread(QString p_qstrBasicAuth);
    QString GetCurrentSessionBaseAuth();
    CdmSession *FindSessionByIdLocal(int p_iSessionId);
    QVariant GetVariant() const;
    CdmSession *FindSessionLocal();
    void AddSessionToThreadContext(CdmSession *p_pSession);
    CdmExecutorAddOnManager *getAddonManager();
    void setEventStoreManager(IdmEventStoreManager *pEventStore);

    static void Logout();
    static int GetOpenSessions();
    static int GetOpenThreads();
    static CdmSessionManager* CreateSessionManager(EdmSettingsMode p_eMode);
    static CdmSessionManager* GetSessionManager();
    static int Login(QString p_qstrLogin,
                     QString p_qstrPassword);
    static CdmDataProvider* GetDataProvider();

public slots:
    void SessionGarbageCollection();

private:
    void InsertSession(CdmSession* p_pSession);
    void DeleteSession(CdmSession* p_pSession);
    void DeleteSessionObject(CdmSession *p_pSession);
    IdmEventStoreManager *getEventStoreManager() const;
    CdmSession *FindSessionByBaseAuthLocal(QString p_qstrAuth);
    void SetThreadBaseAuth(QString p_qstrBaseAuth);
    void SetThreadSessionId(int p_iSessionId);
    QString GetThreadBaseAuth();
    int GetThreadSessionId();
    IdmDataAccess *GetDataAccess();
};
#endif

