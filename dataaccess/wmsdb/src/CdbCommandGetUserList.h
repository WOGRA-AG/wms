#ifndef CDBCOMMANDGETUSERLIST_H
#define CDBCOMMANDGETUSERLIST_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;
class CumUser;

class CdbCommandGetUserList : public CdbAbstractCommand
{
private:
    QList<CumUser*> m_qllUsers;
    QString m_qstrSearchString;
    QString m_qstrSchemeUri;

    int FindAllUsers();
    int FindUsersByUnknownString();
    QString GenerateJoin();
    int SetResult(QSqlQuery &p_rQuery);
    QString GetSelectPartOfQuery();
public:
    CdbCommandGetUserList(CdbDataAccess* p_pDataAccess);
    CdbCommandGetUserList(QString p_qstrSearchString, QString p_qstrSchemeUri, CdbDataAccess *p_pDataAccess);
    virtual ~CdbCommandGetUserList();
    QList<CumUser*> GetResult();


protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDGETUSERLIST_H
