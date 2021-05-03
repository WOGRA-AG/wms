#ifndef CDBCOMMANDRENAMEUSERGROUP_H
#define CDBCOMMANDRENAMEUSERGROUP_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandRenameUserGroup : public CdbAbstractCommandTransactional
{
private:
    long m_lGroupId;
    QString m_qstrNewName;

public:
    CdbCommandRenameUserGroup(long p_lGroupId, QString p_qstrName, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandRenameUserGroup();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDRENAMEUSERGROUP_H
