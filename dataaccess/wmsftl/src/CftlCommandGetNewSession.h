#ifndef CDBCOMMANDGETNEWSESSION_H
#define CDBCOMMANDGETNEWSESSION_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandGetNewSession : public CftlAbstractTransactionalCommand
{
private:
    QString m_qstrApplication;
   qint64 m_lUserId;
   qint64 m_lSessionId;

public:
    CftlCommandGetNewSession(QString p_qstrApplication,qint64 p_lUserId, CftlDataAccess* p_ppDataAccess);
    virtual ~CftlCommandGetNewSession();


    int GetResult();
protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsSessionCheck();
};

#endif // CDBCOMMANDGETNEWSESSION_H
