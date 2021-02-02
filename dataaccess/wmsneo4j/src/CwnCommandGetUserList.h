#ifndef CWNCOMMANDGETUSERLIST_H
#define CWNCOMMANDGETUSERLIST_H

#include "CwnCommandBase.h"
#include "CumUser.h"

#include <QVariant>
#include <QString>
#include <QLinkedList>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandGetUserList : public CwnCommandBase
{
public:
    CwnCommandGetUserList(CwnDataAccess* m_rpDataAccess);
    CwnCommandGetUserList(QString p_qstrUserLoginNameEmail, CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandGetUserList();
    QLinkedList<CumUser*> getResult();


    QString createQuery();
    QString createSearchQuery();
    QString queryCausedError;

private:
    QLinkedList<CumUser*> p_qvlUsers;
    QString m_qstrUserLoginNameEmail;
    bool m_specialSearch;
    QVariantList m_dataList;


protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETUSERLIST_H
