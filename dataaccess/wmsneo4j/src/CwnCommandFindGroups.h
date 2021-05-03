#ifndef CSLCOMMANDFINDGROUPS_H
#define CSLCOMMANDFINDGROUPS_H

// System and Qt Includes
#include <QList>

#include "CwnCommandBase.h"


//Forwards
class CdwnDataAccess;
class CumUserGroup;

class CwnCommandFindGroups : public CwnCommandBase
{
private:
    QString m_qstrGroupName;
    QString m_qstrSchemeUri;
    QString queryCausedError;
    QList<CumUserGroup*> m_qllGroups;

    void interpretAnswer(QVariant &Ret);
    QString createQuery();
public:
    CwnCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandFindGroups();
    QList<CumUserGroup*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDFINDGROUPS_H
