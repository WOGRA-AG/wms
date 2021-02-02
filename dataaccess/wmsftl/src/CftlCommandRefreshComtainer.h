#ifndef CDBCOMMANDREFRESHCOMTAINER_H
#define CDBCOMMANDREFRESHCOMTAINER_H

#include "CftlAbstractCommand.h"

class CftlCommandRefreshComtainer : public CftlAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
public:
    CftlCommandRefreshComtainer(CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandRefreshComtainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDREFRESHCOMTAINER_H
