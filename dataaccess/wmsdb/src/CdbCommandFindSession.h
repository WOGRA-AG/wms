#ifndef CDBCOMMANDFINDSESSION_H
#define CDBCOMMANDFINDSESSION_H

#include "CdbAbstractCommand.h"

class CdbCommandFindSession : public CdbAbstractCommand
{
private:
   qint64 m_lSessionId;
   qint64 m_lUserId;
    QString m_qstrBaseAuth;
    CdmSession* m_pSession;

    int FindSessionByBaseAuth();
    int FindSessionBySessionId();
    int FindSessionBySessionIdAndUserId();
public:
    CdbCommandFindSession(qint64 p_lSessionId,qint64 p_lUserId, CdbDataAccess* p_pDataAccess);
    CdbCommandFindSession(qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    CdbCommandFindSession(QString p_qstrBaseAuth, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandFindSession();

    CdmSession *GetResult();
protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDFINDSESSION_H
