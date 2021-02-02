#ifndef CDBCOMMANDGETOBJECTREFERENCES_H
#define CDBCOMMANDGETOBJECTREFERENCES_H

#include "CftlAbstractCommand.h"

class CftlCommandGetObjectReferences : public CftlAbstractCommand
{
private:
    long m_lContainerId;
    long m_lObjectId;
    QMap<long, long> m_qmReferences;
public:
    CftlCommandGetObjectReferences(long p_lContainerId, long p_lObjectId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetObjectReferences();

    QMap<long, long> GetResult();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOBJECTREFERENCES_H
