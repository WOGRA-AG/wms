#ifndef CDBCOMMANDLOADCLASSMANAGER_H
#define CDBCOMMANDLOADCLASSMANAGER_H

#include "CdbAbstractCommand.h"

class CdbCommandLoadClassManager : public CdbAbstractCommand
{
private:
    long m_lSchemeId;
    CdmClassManager* m_pClassManager;


public:
    CdbCommandLoadClassManager(long p_lSchemeId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadClassManager();
    CdmClassManager* GetResult();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDLOADCLASSMANAGER_H
