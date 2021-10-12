#ifndef CDBCOMMANDCHECKOBJECTLOCKED_H
#define CDBCOMMANDCHECKOBJECTLOCKED_H

// Own includes
#include "CdbAbstractCommand.h"

class CdbCommandCheckObjectLocked : public CdbAbstractCommand
{
private:
   qint64 m_lObjectId;
   qint64 m_lSessionId;

public:
    CdbCommandCheckObjectLocked(qint64 p_lObjectId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCheckObjectLocked();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKOBJECTLOCKED_H
