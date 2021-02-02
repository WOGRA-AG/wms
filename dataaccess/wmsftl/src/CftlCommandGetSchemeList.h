#ifndef CDBCOMMANDGETSCHEMELIST_H
#define CDBCOMMANDGETSCHEMELIST_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandGetSchemeList : public CftlAbstractCommand
{
private:
    QLinkedList<QString> m_qllSchemes;
public:
    CftlCommandGetSchemeList(CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetSchemeList();

    QLinkedList<QString> GetSchemes() const;

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETSCHEMELIST_H
