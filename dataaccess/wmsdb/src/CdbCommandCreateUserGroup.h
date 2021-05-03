#ifndef CDBCOMMANDCREATEUSERGROUP_H
#define CDBCOMMANDCREATEUSERGROUP_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandCreateUserGroup : public CdbAbstractCommandTransactional
{
private:
    QString m_qstrNewName;

    int InsertInAccessorTable();
    int InsertInGroupTable(int p_iAccessorId);
public:
    CdbCommandCreateUserGroup(QString p_qstrGroupName, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCreateUserGroup();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDCREATEUSERGROUP_H
