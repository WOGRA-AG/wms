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
    int GetNewIdForClassMembers(qint64 p_lClassId, QString p_qstrName, QString p_qstrTable);
   qint64 DeleteBaseClassFromDb(qint64 p_lClassId,qint64 p_lBaseClassId);
   qint64 InsertBaseClass(qint64 p_lClassId,qint64 p_lBaseClassId);
    bool FindValueInList(int p_iValue, QList<int> &p_rqvlList);
    bool FindValueInMap(qint64 p_lValue, QMap<qint64,qint64> &p_rqmMap);
   qint64 InsertOrUpdateBaseClasses(CdmClass *p_pCdmClass);
   qint64 DeleteMember(qint64 p_lMemberId);
   qint64 UpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
   qint64 InsertMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
   qint64 InsertOrUpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
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
