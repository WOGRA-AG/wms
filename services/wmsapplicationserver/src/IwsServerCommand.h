#ifndef IWSSERVERCOMMAND_H
#define IWSSERVERCOMMAND_H

// own Includes
#include "CwsRequest.h"
#include "CwsResponse.h"



class IwsServerCommand
{
public:
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse) = 0;
};

#endif // IWSSERVERCOMMAND_H
