#ifndef CDBCOMMANDGETNEWSESSION_H
#define CDBCOMMANDGETNEWSESSION_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandGetNewSession : public CdbAbstractCommandTransactional
{
private:
    QString m_qstrApplication;
    QString m_qstrBaseAuth;
   qint64 m_lUserId;
   qint64 m_lSessionId;

public:
    CdbCommandGetNewSession(QString p_qstrApplication,qint64 p_lUserId, QString p_qstrBaseAuth, CdbDataAccess* p_ppDataAccess);
    virtual ~CdbCommandGetNewSession();


    int GetResult();
protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDGETNEWSESSION_H
