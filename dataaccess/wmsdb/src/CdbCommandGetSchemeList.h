#ifndef CDBCOMMANDGETSCHEMELIST_H
#define CDBCOMMANDGETSCHEMELIST_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandGetSchemeList : public CdbAbstractCommand
{
private:
    QList<QString> m_qllSchemes;
public:
    CdbCommandGetSchemeList(CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetSchemeList();

    QList<QString> GetSchemes() const;

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETSCHEMELIST_H
