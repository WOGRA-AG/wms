#ifndef CDBCOMMANDUPDATESESSION_H
#define CDBCOMMANDUPDATESESSION_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandUpdateSession : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lSessionId;
    QString m_qstrBaseAuth;


public:
    CdbCommandUpdateSession(qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    CdbCommandUpdateSession(QString p_qstrBaseAuth, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUpdateSession();

protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDUPDATESESSION_H
