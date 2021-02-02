#ifndef CFTLCONTAINERTABLEDROP_H
#define CFTLCONTAINERTABLEDROP_H


//own Includes
#include "CftlContainerTableBase.h"


class CftlContainerTableDrop : public CftlContainerTableBase
{
private:
    CdmClass* m_rpClass;

public:
    CftlContainerTableDrop(CdmClass* p_pClass, CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableDrop();

protected:
    virtual QStringList GenerateSqls();
    virtual bool IsValid();
};

#endif // CFTLCONTAINERTABLEDROP_H
