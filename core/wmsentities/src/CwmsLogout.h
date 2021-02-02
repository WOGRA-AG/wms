#ifndef CWMSLOGOUT_H
#define CWMSLOGOUT_H

// System and QT Includes
#include <QObject>
#include <QSettings>

// Own Includes
#include "basetools.h"

class BASETOOLS_API CwmsLogout : public QObject
{
    Q_OBJECT

    QSettings m_qSettings;

public:
    CwmsLogout();
    virtual ~CwmsLogout();
    bool Logout();
};

#endif // CWMSLOGOUT_H
