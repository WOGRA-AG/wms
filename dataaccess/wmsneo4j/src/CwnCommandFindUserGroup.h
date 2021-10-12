#ifndef CWNCOMMANDFindUserGroup_H
#define CWNCOMMANDFindUserGroup_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUserGroup;
class CwnConfiguration;

class CwnCommandFindUserGroup : public CwnCommandBase
{
public:
    CwnCommandFindUserGroup(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandFindUserGroup();

    void setGroupid(qint64 groupid);
   qint64 getGroupid();

    QString createQuery();
    CumUserGroup *getResult();
    QString queryCausedError;

private:
   qint64 groupid;
    CumUserGroup* result;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDFindUserGroup_H
