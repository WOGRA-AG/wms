#ifndef IDBCOMMAND_H
#define IDBCOMMAND_H

// System and Qt Includes
#include <QSqlQuery>

// WMSCOMMONS Includes
#include "CwmsUtilities.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CdbDataAccess.h"

class IdbCommand
{
    public:
        virtual ~IdbCommand(){}


    protected:
        virtual bool CheckValid() = 0;
        virtual int Execute() = 0;

};

#endif // IDBCOMMAND_H
