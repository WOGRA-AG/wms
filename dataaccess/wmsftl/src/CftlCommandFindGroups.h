#ifndef CFTLCOMMANDFINDGROUPS_H
#define CFTLCOMMANDFINDGROUPS_H

// System and Qt Includes
#include <QLinkedList>

#include "CftlAbstractCommand.h"


//Forwards
class CdbDataAccess;
class CumUserGroup;

class CftlCommandFindGroups : public CftlAbstractCommand
{
private:
    QString m_qstrGroupName;
    QString m_qstrSchemeUri;
    QLinkedList<CumUserGroup*> m_qllGroups;
public:
    CftlCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandFindGroups();
    QLinkedList<CumUserGroup*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDFINDGROUPS_H
