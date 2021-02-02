#ifndef IDBCOMMAND_H
#define IDBCOMMAND_H

// System and Qt Includes
#include <QSqlQuery>

// WMS Commons Includes
#include "CwmsUtilities.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CftlHelper.h"
#include "CftlDataAccess.h"

class IftlCommand
{
    public:
        virtual ~IftlCommand(){}


    protected:
        virtual bool CheckValid() = 0;
        virtual int Execute() = 0;

};

#endif // IDBCOMMAND_H
