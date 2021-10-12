#ifndef CWNCOMMANDGETCLASS_H
#define CWNCOMMANDGETCLASS_H

// own Includes
#include "CwnCommandBase.h"

// forwards
class CdmClass;
class CdmClassGroup;
class CdmMember;

class CwnCommandGetClass : public CwnCommandBase
{
private:
    QString payload;
   qint64 m_lClassId;
    CdmClass* m_rpClass;
    CdmClassManager* m_rpClassManager;

   qint64 interpretAnswerForLoadMembers(QVariantList& dataList);
    bool interpretAnswerForLoadMethods(QVariantList& dataList);
    bool interpretAnswerForLoadValidators(QVariantList& dataList);
    bool interpretAnswerForLoadGroups(QVariantList& dataList);
    bool interpretAnswerForBaseClasses(QVariantList& dataList);
    bool interpretAnswerForPosAndMembers(QVariantList& dataList);
    bool interpretAnswerForClassLoad(QVariantList& dataList);
    bool interpretAnswerForPackageLoad(QVariantList& dataList);

    QString createQueryForLoadMembers();
    QString createQueryForLoadMethods();
    QString createQueryForLoadValidators();
    QString createQueryForLoadGroups();
    QString createQueryForBaseClasses();
    QString createQueryForPosAndMembers();
    QString createQueryForClassLoad();
    QString createQueryForLoadPackageString();

public:
    CwnCommandGetClass(CdmClassManager* p_ppClassManager,qint64 p_lClassId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetClass();
    CdmClass* GetResult();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETCLASS_H

