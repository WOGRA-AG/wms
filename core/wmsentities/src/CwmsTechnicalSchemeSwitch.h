#ifndef CWMSTECHNICALSCHEMESERVICES_H
#define CWMSTECHNICALSCHEMESERVICES_H


// OWn Includes
#include "CwmsServerSchemeManager.h"
#include "basetools.h"

#define WMS_TECHNICALSCHEME_SWITCH CwmsTechnicalSchemeSwitch technicalSwitch;


class BASETOOLS_API CwmsTechnicalSchemeSwitch
{
    QString m_qstrOrignalScheme;

public:
    CwmsTechnicalSchemeSwitch();
    virtual ~CwmsTechnicalSchemeSwitch();
    bool SwitchToTechnicalScheme();
    bool SwitchBackToOriginalScheme();
    bool RemoveTechnicalSchemeLocally();
};

#endif // CWMSTECHNICALSCHEMESERVICES_H
