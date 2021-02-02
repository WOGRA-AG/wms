#ifndef CWMSGUIINITAPPLICATION_H
#define CWMSGUIINITAPPLICATION_H

// System and Qt Includes

// basetools includes
#include "CwmsInitApplication.h"

// own Includes

// forwards


class CwmsGuiInitApplication : public CwmsInitApplication
{
public:
    CwmsGuiInitApplication(QString p_qstrApplicationName, QString p_qstrVersion);
    ~CwmsGuiInitApplication();

protected:
    void ApplicationStart();
    void Login();
    void DbSelection();
    void ApplicationSelection();
    void Logging();
};

#endif // CWMSGUIINITAPPLICATION_H
