#ifndef CWMSNONGUIINITAPPLICATION_H
#define CWMSNONGUIINITAPPLICATION_H

// System and Qt Includes

// basetools includes
#include "CwmsInitApplication.h"

// own Includes

// forwards


class CwmsNonGuiInitApplication : public CwmsInitApplication
{
private:
    QString m_qstrLogin;
    QString m_qstrPassword;
    QString m_qstrScheme;
    QString m_qstrApp;
public:
    CwmsNonGuiInitApplication(QString p_qstrApplicationName, QString p_qstrVersion, QString p_qstrLogin, QString p_qstrPassword, QString p_qstrScheme, QString p_qstrApplication);
    ~CwmsNonGuiInitApplication();
    void ApplicationStart();
    
    void Login();
    void DbSelection();
    void ApplicationSelection();
    

    void Logging();
};

#endif // CWMSNONGUIINITAPPLICATION_H
