#ifndef CDBCOMMANDCREATEUSERGROUP_H
#define CDBCOMMANDCREATEUSERGROUP_H

// System and Qt Includes
#include <QLinkedList>
// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandCreateUserGroup : public CftlAbstractTransactionalCommand
{
private:
    QString m_qstrNewName;
    int InsertInGroupTable(int p_iAccessorId);

public:
    CftlCommandCreateUserGroup(QString p_qstrGroupName, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCreateUserGroup();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDCREATEUSERGROUP_H
