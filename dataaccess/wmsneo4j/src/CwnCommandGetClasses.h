#ifndef CWNCOMMANDGETCLASSES_H
#define CWNCOMMANDGETCLASSES_H

#include <QLinkedList>

// own Includes
#include "CwnCommandBase.h"

// forwards
class CdmClass;
class CdmClassGroup;
class CdmMember;

class CwnCommandGetClasses : public CwnCommandBase
{
private:
    CdmClass* m_rpClass;
    QString m_qstrClassIds;
    CdmClassManager* m_rpClassManager;


    long interpretAnswerForLoadMembers(const QVariantList *dataList, long &ldatabaseid, long &lclassid);
    bool interpretAnswerForLoadMethods(const QVariantList *dataList);
    bool interpretAnswerForLoadValidators(const QVariantList *dataList);
    bool interpretAnswerForLoadGroups(const QVariantList *dataList);
    bool interpretAnswerForBaseClasses(const QVariantList *dataList);
    bool interpretAnswerForPosAndMembers(const QVariantList &dataList);
    bool interpretAnswerForClassLoad(long &ldatabaseid, long &lclassid, const QVariantList *dataList);
    bool interpretAnswerForPackageLoad(const QVariantList *dataList);

public:
    CwnCommandGetClasses(CdmClassManager* p_ppClassManager, QLinkedList<long> &p_lClassIds, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetClasses();
    QString queryCausedError;

    QString createQuery();

protected:
    void interpretAnswer(QVariant& Ret);
    bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETCLASSES_H
