#ifndef CDBCOMMANDCHECKOBJECTUSED_H
#define CDBCOMMANDCHECKOBJECTUSED_H

#include "CdbAbstractCommand.h"

class CdbCommandCheckObjectUsed : public CdbAbstractCommand
{
private:
    long m_lObjectId;
    long m_lContainerId;
public:
    CdbCommandCheckObjectUsed(long p_lObjectId, long p_lContainerId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCheckObjectUsed();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKOBJECTUSED_H
