#ifndef CDBCOMMANDGETUSERLIST_H
#define CDBCOMMANDGETUSERLIST_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;
class CumUser;

class CftlCommandGetUserList : public CftlAbstractCommand
{
private:
    QList<CumUser*> m_qllUsers;
    QString m_qstrSearchString;

    int FindUsersByUnknownString();
    int FindAllUsers();
public:
    CftlCommandGetUserList(CftlDataAccess* p_pDataAccess);
    CftlCommandGetUserList(QString p_qstrSearchString, CftlDataAccess *p_pDataAccess);
    virtual ~CftlCommandGetUserList();
    QList<CumUser*> GetResult();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDGETUSERLIST_H
