#ifndef CWNCOMMANDGETSCHEMELIST_H
#define CWNCOMMANDGETSCHEMELIST_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"

// Forwards
class CwnDataAccess;

class CwnCommandGetSchemeList : public CwnCommandBase
{

private:
    QList<QString> m_qllSchemes;
public:
    CwnCommandGetSchemeList(CwnDataAccess *p_pDataAccess);
    virtual ~CwnCommandGetSchemeList();

    QList<QString> GetSchemes() const;

    QString createQuery();
    void interpretAnswer(QVariant &Ret);
    QString queryCausedError;

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETSCHEMELIST_H
