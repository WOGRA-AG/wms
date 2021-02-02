#ifndef CDBCOMMANDFINDSESSION_H
#define CDBCOMMANDFINDSESSION_H

#include "CdbAbstractCommand.h"

class CdbCommandFindSession : public CdbAbstractCommand
{
private:
    long m_lSessionId;
    long m_lUserId;
    QString m_qstrBaseAuth;
    CdmSession* m_pSession;

    int FindSessionByBaseAuth();
    int FindSessionBySessionId();
    int FindSessionBySessionIdAndUserId();
public:
    CdbCommandFindSession(long p_lSessionId, long p_lUserId, CdbDataAccess* p_pDataAccess);
    CdbCommandFindSession(long p_lSessionId, CdbDataAccess* p_pDataAccess);
    CdbCommandFindSession(QString p_qstrBaseAuth, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandFindSession();

    CdmSession *GetResult();
protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDFINDSESSION_H
