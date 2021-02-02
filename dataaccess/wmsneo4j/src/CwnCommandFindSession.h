#ifndef CWNCOMMANDFINDSESSION_H
#define CWNCOMMANDFINDSESSION_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;
class CdmSession;

class CwnCommandFindSession : public CwnCommandBase
{

private:
    long m_lSessionId;
    long m_lUserId;
    QString m_qstrBaseAuth;
    CdmSession* m_pSession;

public:
    CwnCommandFindSession(long p_lSessionId, long p_lUserId, CwnDataAccess* p_pDataAccess);
    CwnCommandFindSession(long p_lSessionId, CwnDataAccess* p_pDataAccess);
    CwnCommandFindSession(QString p_qstrBaseAuth, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandFindSession();

    QString createQueryIdAndUser();
    QString createQueryById();
    QString createQueryBaseAuth();
    CdmSession *GetResult();
    QString queryCausedError;
protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDFINDSESSION_H


