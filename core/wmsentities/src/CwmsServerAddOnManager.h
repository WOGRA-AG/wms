#ifndef CWMSSERVERADDONMANAGER_H
#define CWMSSERVERADDONMANAGER_H

// System and Qt Includes

// WMS Includes
#include "CdmExecutorAddOnManager.h"

// Own Includes
#include "basetools.h"

// Forwards
class CdmExecutor;

// Enumerations


class BASETOOLS_API CwmsServerAddOnManager : public CdmExecutorAddOnManager
{
public:
    CwmsServerAddOnManager();
    virtual ~CwmsServerAddOnManager();


};

#endif // CWMSSERVERADDONMANAGER_H
