
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmObject.h"

#include "CwmsPluginsCommandListPlugins.h"

CwmsPluginsCommandListPlugins::CwmsPluginsCommandListPlugins()
{
}

CwmsPluginsCommandListPlugins::~CwmsPluginsCommandListPlugins()
{
}

QString CwmsPluginsCommandListPlugins::GetCommand()
{
    return "list";
}

bool CwmsPluginsCommandListPlugins::Run(QMap<QString, QString> p_qmArgs)
{
    Q_UNUSED(p_qmArgs);
    m_PluginManager.LoadInstalledFunctionsPlugins();
    m_PluginManager.LoadInstalledPrintingPlugins();

    CdmObjectContainer* pContainer = m_PluginManager.GetServerPluginContainer();

    if (CHKPTR(pContainer))
    {
        QString qstrWql = QString("select from \"%1\"")
            .arg(pContainer->GetKeyname());

        CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql, pContainer);
        QString qstrOutput = "Name\tVersion\tActive\tFile";

        if (CHKPTR(pQuery))
        {
           QList<qint64> qllResults = pQuery->GetResultList();

           if (qllResults.count() > 0)
           {
               QList<qint64>::iterator qllIt = qllResults.begin();
               QList<qint64>::iterator qllItEnd = qllResults.end();
               QString qstrOutput = "Name;Version;Active;File\r\n";

               for (; qllIt != qllItEnd; ++qllIt)
               {
                 qint64 lObjectId = (*qllIt);
                  CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                  if (pObject)
                  {
                      QString qstrVersion;
                      QString qstrName;
                      bool bActive;
                      QString qstrFile;
                      pObject->GetValue("Version", qstrVersion);
                      pObject->GetValue("Name", qstrName);
                      pObject->GetValue("Active", bActive);
                      pObject->GetValue("Library", qstrFile);
                      qstrOutput += qstrName + ";" + qstrVersion + ";" + QString::number(bActive) + ";" + qstrFile + "\r\n";
                  }
               }

               INFO("Found Plugins:\n" + qstrOutput);
               return true;
           }
           else
           {
               INFO("No Plugins found on Server.");
           }
        }
        else
        {
            ERR("Invalid Query for resolving Plugins.");
        }
    }
    else
    {
        ERR("Pluginscontainer not found!");
    }

    return false;
}
