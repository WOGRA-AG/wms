#ifndef CDBCOMMANDUPDATECLASS_H
#define CDBCOMMANDUPDATECLASS_H

#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdmClass;

class CdbCommandUpdateClass : public CdbAbstractCommandTransactional
{
private:
    CdmClass* m_rpClass;
    void DeleteTranslations(int p_iMemberId);
    void SaveGroupTranslations(CdmClassGroup *p_pCdmGroup);
    void SaveTranslations(CdmMember *p_pCdmMember);
    int GetNewIdForClassMembers(long p_lClassId, QString p_qstrName, QString p_qstrTable);
    long DeleteBaseClassFromDb(long p_lClassId, long p_lBaseClassId);
    long InsertBaseClass(long p_lClassId, long p_lBaseClassId);
    bool FindValueInList(int p_iValue, QList<int> &p_rqvlList);
    bool FindValueInMap(long p_lValue, QMap<long, long> &p_rqmMap);
    long InsertOrUpdateBaseClasses(CdmClass *p_pCdmClass);
    long DeleteMember(long p_lMemberId);
    long UpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
    long InsertMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
    long InsertOrUpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
    void SaveValidators(CdmClass *&p_rCdmClass);
    void SaveMethods(CdmClass *&p_rCdmClass);
    void SaveGroups(CdmClass *&p_rCdmClass);
public:
    CdbCommandUpdateClass(CdmClass* p_pClass, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUpdateClass();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};



#endif // CDBCOMMANDUPDATECLASS_H
