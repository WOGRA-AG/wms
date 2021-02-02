#ifndef CDBCOMMANDUPDATESCHEME_H
#define CDBCOMMANDUPDATESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;
class CdmScheme;

class CdbCommandUpdateScheme : public CdbAbstractCommandTransactional
{
private:
    CdmScheme* m_rpScheme;

public:
    CdbCommandUpdateScheme(CdmScheme* p_pScheme, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUpdateScheme();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDSUPDATESCHEME_H
