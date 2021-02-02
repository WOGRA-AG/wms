#ifndef CDBCOMMANDREFRESHCOMTAINER_H
#define CDBCOMMANDREFRESHCOMTAINER_H

#include "CdbAbstractCommand.h"

class CdbCommandRefreshComtainer : public CdbAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
public:
    CdbCommandRefreshComtainer(CdmObjectContainer* p_pContainer, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandRefreshComtainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDREFRESHCOMTAINER_H
