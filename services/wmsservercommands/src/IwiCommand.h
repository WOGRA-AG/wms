#ifndef IWICOMMAND_H
#define IWICOMMAND_H

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"

// WMSCOM Inlcudes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes


// forwards


class IwiCommand
{

public:
    virtual void Execute() = 0;

};

#endif // IWICOMMAND_H
