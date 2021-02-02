#ifndef IWMSRUNNINGSERVICE_H
#define IWMSRUNNINGSERVICE_H

#include "basetools.h"

class BASETOOLS_API IwmsRunningService
{
public:
    virtual ~IwmsRunningService() {}
    virtual QString GetServiceId() = 0;
    virtual int GetCheckIntervall() = 0;
    virtual bool StartService() = 0;
    virtual bool StopService() = 0;
    virtual bool IsRunning() = 0;
};

#endif // IWMSRUNNINGSERVICE_H
