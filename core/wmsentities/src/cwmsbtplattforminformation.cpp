
#include <QApplication>
#include <qglobal.h>
#include <QDesktopWidget>
#include "cwmsbtplattforminformation.h"

#define SIM_MODE_IOS_MOBILE     "iOsMobile"
#define SIM_MODE_IOS_TABLET     "iOsTablet"
#define SIM_MODE_ANDROID_MOBILE "AndroidMobile"
#define SIM_MODE_ANDROID_TABLET "AndroidTablet"
#define SIM_MODE_OTHERS_MOBILE  "OthersMobile"
#define SIM_MODE_OTHERS_TABLET  "OthersTablet"
#define SIM_MODE_NON_GUI_APP    "NonGuiApp"



EwmsSimulationMode CwmsbtPlattformInformation::m_eSimulationMode = eWmsSimulationModeNone;

CwmsbtPlattformInformation::CwmsbtPlattformInformation()
{
}


bool CwmsbtPlattformInformation::isDesktop()
{
    bool bRet = false;

#if !defined(Q_OS_IOS) && !defined(Q_OS_QNX) && !defined (Q_OS_ANDROID) && !defined (Q_OS_BLACKBERRY)
    bRet = true;
#endif //

    if (m_eSimulationMode != eWmsSimulationModeNone)
    {
        return false;
    }

    return bRet;
}

bool CwmsbtPlattformInformation::isIOS()
{
#if defined(Q_OS_IOS)
    return true;
#else

     if (m_eSimulationMode == eWmsSimulationModeIOsMobile ||
         m_eSimulationMode == eWmsSimulationModeIOsTablet)
     {
         return true;
     }
     else
     {
        return false;
     }
#endif
}

bool CwmsbtPlattformInformation::isAndroid()
{
#if defined(Q_OS_ANDROID)
    return true;
#else
    if (m_eSimulationMode == eWmsSimulationModeAndroidMobile ||
        m_eSimulationMode == eWmsSimulationModeAndroidTablet)
    {
        return true;
    }
    else
    {
       return false;
    }
#endif
}

bool CwmsbtPlattformInformation::isWinRT()
{
#if defined(Q_OS_WINRT)
    return true;
#else
    return false;
#endif
}

bool CwmsbtPlattformInformation::isBlackberry()
{
#if defined(Q_OS_BLACKBERRY)
    return true;
#else
    return false;
#endif
}

bool CwmsbtPlattformInformation::isQNX()
{
#if defined(Q_OS_QNX)
    return true;
#else
    return false;
#endif
}

bool CwmsbtPlattformInformation::isMobile()
{
    bool bRet = false;

#if defined(Q_OS_IOS) || defined(Q_OS_QNX) || defined (Q_OS_ANDROID) || defined (Q_OS_BLACKBERRY)
    bRet = true;
#endif //

    if (bRet) // now check the resolution of the device
    {
        QDesktopWidget* pDesktopWidget = qApp->desktop();
        QPoint screenResolution;

        if (pDesktopWidget->width() > 960 || pDesktopWidget->height() > 960)
        {
            bRet = false;
        }
    }

    if (m_eSimulationMode == eWmsSimulationModeAndroidMobile ||
        m_eSimulationMode == eWmsSimulationModeIOsMobile ||
        m_eSimulationMode == eWmsSimulationModeOthersMobile)
    {
        bRet = true;
    }

    return bRet;
}

bool CwmsbtPlattformInformation::IsNonGuiApp()
{
    return (m_eSimulationMode == eWmsSimulationModeNonGuiApp);
}

bool CwmsbtPlattformInformation::isTablet()
{
    bool bRet = false;

#if defined(Q_OS_IOS) || defined(Q_OS_QNX) || defined (Q_OS_ANDROID) || defined (Q_OS_BLACKBERRY)
    bRet = true;
#endif //

    if (bRet) // now check the resolution of the device
    {
        QDesktopWidget* pDesktopWidget = qApp->desktop();

        if (pDesktopWidget->width() <= 960)
        {
            bRet = false;
        }
    }

    if (m_eSimulationMode == eWmsSimulationModeAndroidTablet ||
        m_eSimulationMode == eWmsSimulationModeIOsTablet ||
        m_eSimulationMode == eWmsSimulationModeOthersTablet)
    {
        bRet = true;
    }

    return bRet;
}

bool CwmsbtPlattformInformation::isWeb()
{
    return false;
}


void CwmsbtPlattformInformation::SetSimulationMode(EwmsSimulationMode p_eMode)
{
    m_eSimulationMode = p_eMode;
}

void CwmsbtPlattformInformation::SetSimulationMode(QString p_qstrSimulationMode)
{
    if (p_qstrSimulationMode == SIM_MODE_IOS_MOBILE)
    {
        m_eSimulationMode = eWmsSimulationModeIOsMobile;
    }
    else if (p_qstrSimulationMode == SIM_MODE_IOS_TABLET)
    {
        m_eSimulationMode = eWmsSimulationModeIOsTablet;
    }
    else if (p_qstrSimulationMode == SIM_MODE_ANDROID_MOBILE)
    {
        m_eSimulationMode = eWmsSimulationModeAndroidMobile;
    }
    else if (p_qstrSimulationMode == SIM_MODE_ANDROID_TABLET)
    {
        m_eSimulationMode = eWmsSimulationModeAndroidTablet;
    }
    else if (p_qstrSimulationMode == SIM_MODE_OTHERS_MOBILE)
    {
        m_eSimulationMode = eWmsSimulationModeOthersMobile;
    }
    else if (p_qstrSimulationMode == SIM_MODE_OTHERS_TABLET)
    {
        m_eSimulationMode = eWmsSimulationModeOthersTablet;
    }
    else if (p_qstrSimulationMode == SIM_MODE_NON_GUI_APP)
    {
        m_eSimulationMode = eWmsSimulationModeNonGuiApp;
    }
}

bool CwmsbtPlattformInformation::IsSimulating()
{
    return (m_eSimulationMode != eWmsSimulationModeNone);
}
