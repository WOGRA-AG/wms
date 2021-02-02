#ifndef CWNCOMMANDGETNEWSESSION_H
#define CWNCOMMANDGETNEWSESSION_H

#include "CwnCommandBase.h"
#include <QVariant>
#include <QString>


class CwnCommandGetNewSession : public CwnCommandBase
{

private:
    QString m_qstrApplication;
    long m_lUserId;
    long m_lSessionId;
    QDateTime m_qdtLoginDate;

public:
    CwnCommandGetNewSession(QString p_qstrApplication,
                            long p_lUserId,
                            CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandGetNewSession();

    QString createQueryForSessionInsert();
    QString createQueryForSessionRead();
    int GetResult();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETNEWSESSION_H
