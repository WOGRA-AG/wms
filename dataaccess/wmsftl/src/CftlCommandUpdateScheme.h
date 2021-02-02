#ifndef CDBCOMMANDUPDATESCHEME_H
#define CDBCOMMANDUPDATESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;
class CdmScheme;

class CftlCommandUpdateScheme : public CftlAbstractTransactionalCommand
{
private:
    CdmScheme* m_rpScheme;

public:
    CftlCommandUpdateScheme(CdmScheme* p_pScheme, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandUpdateScheme();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDSUPDATESCHEME_H
