#ifndef CWMSSERVERLOGIN_H
#define CWMSSERVERLOGIN_H

// WMS Commons Includes
#include "CwmsSynchronizable.h"

#include "basetools.h"

#define WMS_SERVER_LOGIN CwmsServerLogin login;

class CwmsServerLogin : CwmsSynchronizable
{
    bool m_bLogoutNeeded;

public:
    CwmsServerLogin();
    virtual ~CwmsServerLogin();
};

#endif // CWMSSERVERLOGIN_H
