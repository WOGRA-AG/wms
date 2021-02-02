#ifndef CDBCOMMANDLOADCLASSMANAGER_H
#define CDBCOMMANDLOADCLASSMANAGER_H

#include "CftlAbstractCommand.h"

class CftlCommandLoadClassManager : public CftlAbstractCommand
{
private:
    long m_lSchemeId;
    CdmClassManager* m_pClassManager;


public:
    CftlCommandLoadClassManager(long p_lSchemeId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadClassManager();
    CdmClassManager* GetResult();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDLOADCLASSMANAGER_H
