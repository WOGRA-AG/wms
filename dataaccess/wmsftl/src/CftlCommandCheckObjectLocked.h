#ifndef CDBCOMMANDCHECKOBJECTLOCKED_H
#define CDBCOMMANDCHECKOBJECTLOCKED_H

// Own includes
#include "CftlAbstractCommand.h"

class CftlCommandCheckObjectLocked : public CftlAbstractCommand
{
private:
    CdmObject* m_rpObject;

public:
    CftlCommandCheckObjectLocked(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCheckObjectLocked();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKOBJECTLOCKED_H
