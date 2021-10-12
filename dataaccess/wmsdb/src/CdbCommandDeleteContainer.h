#ifndef CDBCOMMANDDELETECONTAINER_H
#define CDBCOMMANDDELETECONTAINER_H

#include "CdbAbstractCommandTransactional.h"


class CdbCommandDeleteContainer : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lContainerId;
public:
    CdbCommandDeleteContainer(qint64 p_lContainerId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETECONTAINER_H
