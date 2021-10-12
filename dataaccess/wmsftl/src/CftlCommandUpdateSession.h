#ifndef CDBCOMMANDUPDATESESSION_H
#define CDBCOMMANDUPDATESESSION_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandUpdateSession : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lSessionId;
    QString m_qstrBaseAuth;


public:
    CftlCommandUpdateSession(qint64 p_lSessionId, CftlDataAccess* p_pDataAccess);
    CftlCommandUpdateSession(QString p_qstrBaseAuth, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandUpdateSession();

protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsSessionCheck();
};

#endif // CDBCOMMANDUPDATESESSION_H
