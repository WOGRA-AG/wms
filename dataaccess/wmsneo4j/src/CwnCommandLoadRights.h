#ifndef CWNCOMMANDLOADRIGHTS_H
#define CWNCOMMANDLOADRIGHTS_H

#include "CwnCommandStdHeader.h"

#include "CwnCommandBase.h"
#include "CdmRights.h"

class CwnCommandLoadRights : public CwnCommandBase
{
public:
    CwnCommandLoadRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, CwnDataAccess* p_DataAccess);
    virtual ~CwnCommandLoadRights();

    QString createQuery();
    QString queryCausedError;

private:
    long m_lObjectId;
    CdmRights& m_prCcdmRights;
    QString m_pqstrTableName;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOADRIGHTS_H
