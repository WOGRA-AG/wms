#ifndef CWMSBTPLATTFORMINFORMATION_H
#define CWMSBTPLATTFORMINFORMATION_H

// System and QT Includes
#include <QObject>

// own INcludes
#include "basetools.h"

enum EwmsSimulationMode
{
    eWmsSimulationModeNone,
    eWmsSimulationModeIOsMobile,
    eWmsSimulationModeIOsTablet,
    eWmsSimulationModeAndroidMobile,
    eWmsSimulationModeAndroidTablet,
    eWmsSimulationModeOthersMobile,
    eWmsSimulationModeOthersTablet,
    eWmsSimulationModeNonGuiApp
};


class BASETOOLS_API CwmsbtPlattformInformation : public QObject
{
    private:
        static EwmsSimulationMode m_eSimulationMode;
public:
    CwmsbtPlattformInformation();
    static void SetSimulationMode(EwmsSimulationMode p_eMode);
    static void SetSimulationMode(QString p_qstrMode);
    static bool IsSimulating();
public slots:
    bool IsNonGuiApp();
    bool isWeb();
    bool isTablet();
    bool isMobile();
    bool isDesktop();
    bool isIOS();
    bool isAndroid();
    bool isWinRT();
    bool isBlackberry();
    bool isQNX();
};

#endif // // CWMSBTPLATTFORMINFORMATION_H
