#ifndef CWNCOMMANDLOGOUT_H
#define CWNCOMMANDLOGOUT_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnConfiguration;

class CwnCommandLogout : public CwnCommandBase
{
public:
    CwnCommandLogout(qint64 m_lSessionId, CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandLogout();

    QString createQuery();
    QString queryCausedError;

private:
   qint64 m_lSessionId;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOGOUT_H
