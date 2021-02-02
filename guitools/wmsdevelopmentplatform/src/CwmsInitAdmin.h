#ifndef CWMSINITADMIN_H
#define CWMSINITADMIN_H

// System and QT Includes

// WMS GUI Includes
#include "CwmsInitApplication.h"

// own Includes

// forwards

class CwmsInitAdmin : public CwmsInitApplication
{
   Q_OBJECT
public:
    CwmsInitAdmin(QString p_qstrName, QString p_qstrVersion);
    virtual ~CwmsInitAdmin();


protected:
    void Login();
    void Logging();
    void DbSelection();
    void ApplicationSelection();
    void ApplicationStart();
};

#endif // CWMSINITADMIN_H
