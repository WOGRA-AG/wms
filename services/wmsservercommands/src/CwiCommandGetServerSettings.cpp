
// System and Qt Includes
#include <QVariant>

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmSettings.h"

// BASETOOLS Includes
#include "CwmsContext.h"

#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "WmsInterfaceDefines.h"
#include "CwiCommandGetServerSettings.h"

CwiCommandGetServerSettings::CwiCommandGetServerSettings(CwmscomData* p_pData)
    : m_rpData(p_pData)
{
}

CwiCommandGetServerSettings::~CwiCommandGetServerSettings()
{
}


void CwiCommandGetServerSettings::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);

    CdmSettings cSettings(eDmSettingsModeServer);
    QVariantMap config = cSettings.getValueMap();

    pResult->AddValue(CONFIGURATION, config);
    pResult->AddValue(RESULT, true);
    pResult->SetMessageCode(eWmsHttpStatusCodeOk);
    pResult->SetSeverity(eWmscomMessageServerityInfo);
    pResult->SetMessage("Command executed. Configurations transmitted");
}
