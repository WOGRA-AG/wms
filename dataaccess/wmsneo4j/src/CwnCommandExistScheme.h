#ifndef CWNCOMMANDEXISTSCHEME_H
#define CWNCOMMANDEXISTSCHEME_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnConfiguration;

class CwnCommandExistScheme : public CwnCommandBase
{
public:
    CwnCommandExistScheme(CwnDataAccess* m_rpDataAccess, QString qstrKeyname);
    virtual ~CwnCommandExistScheme();
    QString createQuery();
    QString queryCausedError;

private:
    QString m_qstrKeyname;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDEXISTSCHEME_H
