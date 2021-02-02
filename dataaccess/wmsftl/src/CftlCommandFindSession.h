#ifndef CDBCOMMANDFINDSESSION_H
#define CDBCOMMANDFINDSESSION_H

#include "CftlAbstractCommand.h"

class CftlCommandFindSession : public CftlAbstractCommand
{
private:
    long m_lSessionId;
    long m_lUserId;

public:
    QString m_qstrBaseAuth;
    CdmSession* m_pSession;

    int FindSessionByBaseAuth();
    int FindSessionBySessionId();
    int FindSessionBySessionIdAndUserId();
public:
    CftlCommandFindSession(long p_lSessionId, long p_lUserId, CftlDataAccess* p_pDataAccess);
    CftlCommandFindSession(long p_lSessionId, CftlDataAccess* p_pDataAccess);
    CftlCommandFindSession(QString p_qstrBaseAuth, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandFindSession();

    CdmSession *GetResult();

protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsSessionCheck();
};

#endif // CDBCOMMANDFINDSESSION_H
