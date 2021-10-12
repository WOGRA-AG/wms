#ifndef CDBCOMMANDRENAMEUSERGROUP_H
#define CDBCOMMANDRENAMEUSERGROUP_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandRenameUserGroup : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lGroupId;
    QString m_qstrNewName;

public:
    CftlCommandRenameUserGroup(qint64 p_lGroupId, QString p_qstrName, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandRenameUserGroup();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDRENAMEUSERGROUP_H
