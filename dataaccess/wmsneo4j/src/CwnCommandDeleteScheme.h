#ifndef CWNCOMMANDDELETESCHEME_H
#define CWNCOMMANDDELETESCHEME_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnUserManager;
class CdmPackage;
class CwnConfiguration;

class CwnCommandDeleteScheme : public CwnCommandBase
{

public:
    CwnCommandDeleteScheme(CwnDataAccess* m_rpDataAccess, QString p_qstrKeyname);
    virtual ~CwnCommandDeleteScheme();
    QString createQuery();
    QString createQueryForNodesWithNoRelationsships();
    QString queryCausedError;

private:
    QString m_qstrKeyname;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETESCHEME_H
