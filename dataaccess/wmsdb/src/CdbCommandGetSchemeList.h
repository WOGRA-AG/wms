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
    QLinkedList<QString> m_qllSchemes;
public:
    CdbCommandGetSchemeList(CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetSchemeList();

    QLinkedList<QString> GetSchemes() const;

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETSCHEMELIST_H
