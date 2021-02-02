#ifndef CDBCOMMANDGETCLASS_H
#define CDBCOMMANDGETCLASS_H

// own Includes
#include "CftlAbstractCommand.h"

// forwards
class CdmClass;
class CdmClassGroup;
class CdmMember;

class CftlCommandGetClass : public CftlAbstractCommand
{
private:
    long m_lClassId;
    CdmClass* m_rpClass;
	CdmClassManager* m_rpClassManager;

    void LoadMethods(CdmClass *p_pCdmClass);
    void LoadValidators(CdmClass *p_pCdmClass);
    void LoadGroups(CdmClass *p_pCdmClass);
    long LoadMembers(CdmClass *p_pCdmClass);
    long LoadBaseClasses(CdmClass *p_pCdmClass);
    void LoadGroupTranslations(CdmClassGroup *p_pCdmGroup);
    void LoadTranslations(CdmMember *p_pCdmMember);
public:
	CftlCommandGetClass(CdmClassManager* p_ppClassManager, long p_lClassId, CftlDataAccess* p_pDataAccess);
	virtual ~CftlCommandGetClass();
    CdmClass* GetResult();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCLASS_H
