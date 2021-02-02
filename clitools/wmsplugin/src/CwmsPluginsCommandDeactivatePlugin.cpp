
// WMS Manager Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmObject.h"

// Own Inlcudes
#include "CwmsPluginsCommandDeactivatePlugin.h"

#define PLUGIN_NAME "name"
#define PLUGIN_VERSION "version"

CwmsPluginsCommandDeactivatePlugin::CwmsPluginsCommandDeactivatePlugin()
{
}

CwmsPluginsCommandDeactivatePlugin::~CwmsPluginsCommandDeactivatePlugin()
{
}

QString CwmsPluginsCommandDeactivatePlugin::GetCommand()
{
    return "deactivate";
}

bool CwmsPluginsCommandDeactivatePlugin::Run(QMap<QString, QString> p_qmArgs)
{
    CdmObjectContainer* pContainer = m_PluginManager.GetServerPluginContainer();

    if (CHKPTR(pContainer))
    {
        CdmObject* pObject = nullptr;

        QString qstrWql = QString("select from \"%1\" where and(Name = \"%2\", Version = \"%3\")")
                .arg(pContainer->GetKeyname())
                .arg(p_qmArgs[PLUGIN_NAME])
                .arg(p_qmArgs[PLUGIN_VERSION]);

        CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql, pContainer);

        if (CHKPTR(pQuery))
        {
            if (pQuery->GetResultCount() > 0)
            {
                pObject = pQuery->GetFirstResultObject();

                if (pQuery->GetResultCount() > 1)
                {
                    WARNING("More than one result found. Taking first");
                }

                pObject->SetValue("Active", false);
                pObject->Commit();
                INFO("Plugin deactivated.");
                return true;
            }
            else
            {
                ERR("Plugin not found with name " + p_qmArgs[PLUGIN_NAME] + " and version " + p_qmArgs[PLUGIN_VERSION] + ".");
            }
        }
        else
        {
            ERR("Invalid query for plugin search");
        }
    }
    else
    {
        ERR("Server container not found!");
    }

    return false;
}
