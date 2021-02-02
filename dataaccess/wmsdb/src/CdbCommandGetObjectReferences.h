#ifndef CDBCOMMANDGETOBJECTREFERENCES_H
#define CDBCOMMANDGETOBJECTREFERENCES_H

#include "CdbAbstractCommand.h"

class CdbCommandGetObjectReferences : public CdbAbstractCommand
{
private:
    long m_lContainerId;
    long m_lObjectId;
    QMap<long, long> m_qmReferences;
public:
    CdbCommandGetObjectReferences(long p_lContainerId, long p_lObjectId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetObjectReferences();

    QMap<long, long> GetResult();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOBJECTREFERENCES_H
