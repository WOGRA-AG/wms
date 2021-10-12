#ifndef CWNCOMMANDEXITSCLASS_H
#define CWNCOMMANDEXITSCLASS_H

// Own Includes
#include "CwnCommandBase.h"

class CwnCommandExistClass : public CwnCommandBase
{
private:
   qint64 m_lSchemeId;
    QString m_qstrKeyname;
    bool m_bResult;

public:
    CwnCommandExistClass(qint64 p_lSchemeId, QString p_qstrKeyname, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandExistClass();
    bool GetResult();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    bool CheckValid();
    virtual int Execute();
};

#endif // CWNCOMMANDEXISTCLASS_H
