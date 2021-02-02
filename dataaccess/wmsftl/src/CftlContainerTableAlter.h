#ifndef CFTLCONTAINERTABLEALTER_H
#define CFTLCONTAINERTABLEALTER_H

// System and Qt Includes
#include <QStringList>

#include "CftlContainerTableBase.h"

// Forwards
class CdmClass;
class CdmMember;

class CftlContainerTableAlter : public CftlContainerTableBase
{
private:
    CdmClass* m_rpClass;

    QString AddNewMemberSql(QList<CdmMember*> &p_qlMembers, QString &qstrTableName);
    QStringList UpdateMembersSql(QList<CdmMember*> &p_qlMembers, QString& qstrTableName);
    QStringList DeleteMembersSql(QList<CdmMember*> &p_qlMembers, QString& qstrTableName);
    QString AddNewMemberSqlString(CdmMember* pMember);
    QStringList GenerateUpdateQueries(CdmMember *p_pMember);
    void GenerateMemberSqls(QStringList &qstrlQueries);
    void GenerateRenamingSqls(QStringList &qstrlQueries);
    void GenerateBaseClassChangesSqls(QStringList &qstrlQueries);
    QString AddNewMemberSqlString(CdmMember *pMember, QString &p_qstrKeyname);
public:
    CftlContainerTableAlter(CdmClass* p_pClass, CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableAlter();

protected:
    virtual QStringList GenerateSqls();
    virtual bool IsValid();
};

#endif // CFTLCONTAINERTABLEALTER_H
