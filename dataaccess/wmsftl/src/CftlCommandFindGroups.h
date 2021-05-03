#ifndef CFTLCOMMANDFINDGROUPS_H
#define CFTLCOMMANDFINDGROUPS_H

// System and Qt Includes
#include <QList>

#include "CftlAbstractCommand.h"


//Forwards
class CdbDataAccess;
class CumUserGroup;

class CftlCommandFindGroups : public CftlAbstractCommand
{
private:
    QString m_qstrGroupName;
    QString m_qstrSchemeUri;
    QList<CumUserGroup*> m_qllGroups;
public:
    CftlCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandFindGroups();
    QList<CumUserGroup*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDFINDGROUPS_H
