// WMS Includes
#include "wmsdefines.h"

#include "CwmsLogout.h"

CwmsLogout::CwmsLogout()
    : m_qSettings(QSettings::UserScope, "WOGRA", "WMS")
{

}

CwmsLogout::~CwmsLogout()
{

}

bool CwmsLogout::Logout()
{
    bool bRet = false;
    m_qSettings.setValue(STORE_WMS_LOGIN, false);
    m_qSettings.setValue(WMS_LOGIN, "");
    m_qSettings.setValue(PASSWORD, "");

    QString qstrPasswordString = m_qSettings.value(WMS_LOGIN).toString();
    if(qstrPasswordString.isEmpty())
    {
        bRet = true;
    }

    return bRet;
}
