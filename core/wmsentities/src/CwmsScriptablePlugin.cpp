// WMS INcludes
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"

// Own Includes
#include "CwmsScriptablePlugin.h"

CwmsScriptablePlugin::CwmsScriptablePlugin()
{
}


CwmsScriptablePlugin::~CwmsScriptablePlugin()
{
}



QObject* CwmsScriptablePlugin::getPlugin(QString p_qstrName)
{
    return CdmExecutor::GetExecutor()->GetAddOnManager()->GetFunctionObject(p_qstrName);
}
