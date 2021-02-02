#ifndef IWNCOMMAND_H
#define IWNCOMMAND_H

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CwnDataAccess.h"

class IwnCommand
{
    public:
        virtual ~IwnCommand(){}


    protected:
        virtual int Execute() = 0;
        virtual bool CheckValid() = 0;
};

#endif // IWNCOMMAND_H
