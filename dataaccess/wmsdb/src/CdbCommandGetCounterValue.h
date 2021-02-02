#ifndef CDBCOMMANDGETCOUNTERVALUE_H
#define CDBCOMMANDGETCOUNTERVALUE_H

#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdmValueCounter;

class CdbCommandGetCounterValue : public CdbAbstractCommandTransactional
{
private:
    CdmValueCounter* m_rpCdmCounter;

    long GetCounterValue(long p_lObjectListId, long p_lMemberId);
public:
    CdbCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetCounterValue();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCOUNTERVALUE_H
