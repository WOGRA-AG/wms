#ifndef CDBCOMMANDGETNEWSESSION_H
#define CDBCOMMANDGETNEWSESSION_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandGetNewSession : public CdbAbstractCommandTransactional
{
private:
    QString m_qstrApplication;
    QString m_qstrBaseAuth;
    long m_lUserId;
    long m_lSessionId;

public:
    CdbCommandGetNewSession(QString p_qstrApplication, long p_lUserId, QString p_qstrBaseAuth, CdbDataAccess* p_ppDataAccess);
    virtual ~CdbCommandGetNewSession();


    int GetResult();
protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDGETNEWSESSION_H
