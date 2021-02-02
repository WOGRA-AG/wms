#ifndef CFTLCONTAINERTABLECREATE_H
#define CFTLCONTAINERTABLECREATE_H

#include "CftlContainerTableBase.h"

class CdmClass;


class CftlContainerTableCreate : public CftlContainerTableBase
{
private:
    CdmClass* m_rpClass;

    QString AddPrimaryKey();
    QString AddMembersToTable();
    QString AddMember(CdmMember *p_pMember);
    QString AddModificationInfo();
    QStringList CreateIndices(QString p_qstrTableName);
public:
    CftlContainerTableCreate(CdmClass* p_pClass, CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableCreate();

protected:
    virtual QStringList GenerateSqls();
    virtual bool IsValid();
};

#endif // CFTLCONTAINERTABLECREATE_H
