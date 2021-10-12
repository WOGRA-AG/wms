#ifndef CDBCOMMANDGETCOUNTERVALUE_H
#define CDBCOMMANDGETCOUNTERVALUE_H

#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdmValueCounter;

class CdbCommandGetCounterValue : public CdbAbstractCommandTransactional
{
private:
    CdmValueCounter* m_rpCdmCounter;

   qint64 GetCounterValue(qint64 p_lObjectListId,qint64 p_lMemberId);
public:
    CdbCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetCounterValue();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCOUNTERVALUE_H
