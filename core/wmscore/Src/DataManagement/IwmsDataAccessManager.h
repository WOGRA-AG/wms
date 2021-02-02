#ifndef IWMSDATAACCESSMANAGER_H
#define IWMSDATAACCESSMANAGER_H

#include "IdmDataAccess.h"

//forwards
class IdmDataAccess;

class IwmsDataAccessManager
{
public:
    IwmsDataAccessManager(){}
    virtual ~IwmsDataAccessManager(){}
    virtual void setEventStore(IdmDataAccess *pDataAccess) = 0;
    virtual int initEventStore(QString qstrEventName) = 0;
};

#endif // IWMSDATAACCESSMANAGER_H
