#ifndef CDBCOMMANDFINDGROUPS_H
#define CDBCOMMANDFINDGROUPS_H

// System and Qt Includes
#include <QList>

#include "CdbAbstractCommand.h"


//Forwards
class CdbDataAccess;
class CumUserGroup;

class CdbCommandFindGroups : public CdbAbstractCommand
{
private:
    QString m_qstrGroupName;
    QString m_qstrSchemeUri;
    QList<CumUserGroup*> m_qllGroups;
    int FindUserGroupByGroupName();
    void FillGroupList(QSqlQuery &cQSqlQuery);
    int GetAllUserGroups();
public:
    CdbCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandFindGroups();
    QList<CumUserGroup*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDFINDGROUPS_H
