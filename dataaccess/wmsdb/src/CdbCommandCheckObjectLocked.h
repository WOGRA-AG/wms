#ifndef CDBCOMMANDCHECKOBJECTLOCKED_H
#define CDBCOMMANDCHECKOBJECTLOCKED_H

// Own includes
#include "CdbAbstractCommand.h"

class CdbCommandCheckObjectLocked : public CdbAbstractCommand
{
private:
    long m_lObjectId;
    long m_lSessionId;

public:
    CdbCommandCheckObjectLocked(long p_lObjectId, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCheckObjectLocked();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKOBJECTLOCKED_H
