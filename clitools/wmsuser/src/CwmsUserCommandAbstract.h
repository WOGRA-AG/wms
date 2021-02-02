#ifndef CWMSUSERCOMMANDABSTRACT_H
#define CWMSUSERCOMMANDABSTRACT_H

// System and Qt Includes
#include <QString>
#include <QMap>

// WMS Includes
#include "CumUserManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdmLogging.h"

#define FIRSTNAME "firstname"
#define LASTNAME "lastname"
#define LOGIN "userlogin"
#define PASSWORD "userpassword"
#define MAIL "mail"
#define ADMIN "admin"
#define NEW_GROUP_NAME "name"
#define GROUP_NAME "group"
#define SCHEME "scheme"

class CwmsUserCommandAbstract
{
public:
    CwmsUserCommandAbstract();
    virtual ~CwmsUserCommandAbstract();
    virtual QString GetCommand() = 0;
    virtual bool Run(QMap<QString,QString> p_qmArgs) = 0;
    CumUserManager* GetUserManager();
};

#endif // CWMSUSERCOMMANDABSTRACT_H
