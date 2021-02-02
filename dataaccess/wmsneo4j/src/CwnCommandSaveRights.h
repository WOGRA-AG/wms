#ifndef CWNCOMMANDSAVERIGHTS_H
#define CWNCOMMANDSAVERIGHTS_H

#include "CwnCommandStdHeader.h"

#include "CwnCommandBase.h"
#include "CdmRights.h"

class CwnCommandSaveRights : public CwnCommandBase
{
public:
    CwnCommandSaveRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName);
    virtual ~CwnCommandSaveRights();

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

#endif // CWNCOMMANDSAVERIGHTS_H
