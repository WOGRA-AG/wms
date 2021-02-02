#ifndef CWNCOMMANDUPDATESESSION_H
#define CWNCOMMANDUPDATESESSION_H

#include "CwnCommandBase.h"

class CwnCommandUpdateSession : public CwnCommandBase
{
private:
    long m_lSessionId;
    QString m_qstrBaseAuth;


public:
    CwnCommandUpdateSession(long p_lSessionId, CwnDataAccess* p_pDataAccess);
    CwnCommandUpdateSession(QString p_qstrBaseAuth, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdateSession();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
    virtual bool NeedsActiveSession();
};

#endif // CWNCOMMANDUPDATESESSION_H
