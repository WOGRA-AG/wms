#ifndef CDBCOMMANDCHECKOBJECTUSED_H
#define CDBCOMMANDCHECKOBJECTUSED_H

#include "CftlAbstractCommand.h"

class CftlCommandCheckObjectUsed : public CftlAbstractCommand
{
private:
    const CdmObject* m_rpObject;
public:
    CftlCommandCheckObjectUsed(const CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCheckObjectUsed();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKOBJECTUSED_H
