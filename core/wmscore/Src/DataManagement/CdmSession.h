#ifndef CDMSESSION_H
#define CDMSESSION_H

// System and Qt Includes
#include <QMap>
#include <QDateTime>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// own Includes
#include "datamanager.h"
#include "CdmExecutor.h"
#include "IdmEventStoreManager.h"

// forwards
class CdmContainerManager;
class CumUser;
class CdmDataProvider;
class CdmExecutor;
class IdmEventStoreManager;

class WMSMANAGER_API CdmSession : public CwmsSynchronizable
{
    friend class CdmDataAccessHelper;

    private:
   qint64 m_lSessionId;
    CumUser* m_pSessionUser;
    CdmDataProvider* m_pDataProvider;
    QDateTime m_qdtLastRequest;
    QDateTime m_qdtLastUpdate;
    QString m_qstrServerRequestPath;
	IdmEventStoreManager *m_pEventStoreManager;

    void InitNewManager(IdmDataAccess* p_pDataAccess);
public:
    CdmSession();
    virtual ~CdmSession();
    const CumUser *GetCurrentUser() const;
   qint64 GetCurrentUserId() const;
    bool IsExpired() const;
    void LdapLogin(QString p_qstrLogin, QString p_qstrPassword, IdmDataAccess *p_pDataAccess);
    void Login(QString p_qstrLogin, QString p_qstrPassword, IdmDataAccess *p_pDataAccess);
    CdmDataProvider *GetDataProvider() const;

    QDateTime GetLastRequest() const;
    void SetLastRequest(const QDateTime &qdtLastRequest);
   qint64 GetId();
    QString GetBaseAuth() const;
   qint64 Logout();
    void SetServerRequestPath(QString p_qstrPath);
    QString GetServerRequestPath() const;
    void setEventStoreManager(IdmEventStoreManager *pEventStore);
    IdmEventStoreManager *getEventStoreManager();
    void SessionUpdated();
    bool NeedsUpdate();
};

#endif // CDMSESSION_H
