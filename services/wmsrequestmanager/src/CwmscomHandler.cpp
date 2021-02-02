/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomHandler.cpp
 ** Started Implementation: 2012/04/01
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QCoreApplication>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QPluginLoader>

// WMS Commons Includes
#include "CwmsJson.h"
#include "CwmsTimeMeassurement.h"

// WMS Core Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"

// own Includes
#include "IwmsServerPlugin.h"
#include "CwmscomData.h"
#include "CwmscomController.h"
#include "CwmscomHandler.h"

#define WMS_SERVER_PLUGIN_PATH "/servercommands"

CwmscomHandler* CwmscomHandler::ms_pCommandHandler = nullptr;

CwmscomHandler::CwmscomHandler()
    : CwmsDataExchangeConfigurator()
{

}

CwmscomHandler::~CwmscomHandler()
{
    QMap<QString, CwmscomController*>::iterator qmIt = m_qmController.begin();
    QMap<QString, CwmscomController*>::iterator qmItEnd = m_qmController.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CwmscomController* pController = qmIt.value();
        delete pController;
    }

    m_qmController.clear();
}

void CwmscomHandler::CleanupCachedData()
{
    CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

    if (pProvider)
    {
        CdmScheme* pScheme = pProvider->GetCurrentScheme();

        if (pScheme)
        {
            pScheme->ResetContainerManager();
        }
    }
}

bool CwmscomHandler::HandleRequest(CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    bool bRet = true;
    CwmsTimeMeassurement cTime(false, "HandleRequest");

    if (p_pRequest->GetMethod() == eWsOptions)
    {
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk); // The Default
        p_pRequest->AddHeader("Allow", "GET,PUT,DELETE,OPTIONS");
    }
    else
    {
        CwmscomData* pCwmscomData = new CwmscomData(p_pRequest, p_pResponse, this);
        cTime.finishedTask("Built comData Object");

        if (pCwmscomData->IsValid())
        {
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk); // The Default
            QString qstrControllerName = pCwmscomData->GetControllerName();
            CwmscomController* pController = GetController(qstrControllerName);
            cTime.finishedTask("Search for Controller");

            if (pController)
            {
                pController->Execute(pCwmscomData);
                cTime.finishedTask("Execute Request");
                CleanupCachedData();
                cTime.finishedTask("Cleanup Cache");
            }
            else
            {
                ERR("Controller " + qstrControllerName + " not found in Handler");
                bRet = false;
            }
        }
        else
        {
            ERR("Invalid ComData Object");
        }

        if (p_pResponse->IsBodyEmpty())
        {
            p_pResponse->SetBody(pCwmscomData->GetResult());
        }

        if (p_pResponse->IsBodyEmpty())
        {
            QVariantMap qvm;
            qvm.insert("Application", "WOGRA Application Server");
            qvm.insert("Error", "Unknow Request. No valid answer provided");
            CwmsJson json;
            p_pResponse->SetBody(json.serialize(qvm));
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeNotFound);
            bRet = false;
        }

        cTime.finishedTask("Check Response");

        delete pCwmscomData;
        cTime.finishedTask("Delete comData Object");
    }

    return bRet;
}

void CwmscomHandler::AddController(QString p_qstrName, CwmscomController* p_pController)
{
    m_qmController.insert(p_qstrName, p_pController);
    INFO("Added Controller " + p_qstrName);
}

CwmscomController* CwmscomHandler::GetController(QString m_qstrControllerName)
{
    CwmscomController* pController = nullptr;

    if (m_qmController.contains(m_qstrControllerName))
    {
        pController = m_qmController[m_qstrControllerName];
    }

    return pController;
}

QString CwmscomHandler::GetDescription(QString p_qstrController, QString p_qstrResource)
{
    QString qstrDescription;

    if (m_qmController.contains(p_qstrController))
    {
        CwmscomController* pController = m_qmController[p_qstrController];

        if (pController)
        {
            qstrDescription = pController->GetDescription(p_qstrResource);
        }
    }
    else
    {
        ERR("Controller " + p_qstrController + " not found");
        qstrDescription = "Controller not found!";
    }

    return qstrDescription;
}


QString CwmscomHandler::GetSystemUserPassword() const
{
    return m_qstrSystemUserPassword;
}

void CwmscomHandler::SetSystemUserPassword(const QString &qstrSystemUserPassword)
{
    m_qstrSystemUserPassword = qstrSystemUserPassword;
}

QString CwmscomHandler::GetSystemUserLogin() const
{
    return m_qstrSystemUserLogin;
}

void CwmscomHandler::SetSystemUserLogin(const QString &qstrSystemUserLogin)
{
    m_qstrSystemUserLogin = qstrSystemUserLogin;
}

CwmscomHandler* CwmscomHandler::CreateOrGetCommandHandler()
{
    if (!ms_pCommandHandler)
    {
        ms_pCommandHandler = new CwmscomHandler();
    }

    return ms_pCommandHandler;
}

void CwmscomHandler::Init()
{
    QString qstrPath = qApp->applicationDirPath() + WMS_SERVER_PLUGIN_PATH;
    QDir qPluginsDir(qstrPath);
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);

    for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
    {
        QFileInfo qfInfo = qlEntries[iCounter];
        QString qstrFile = qfInfo.absoluteFilePath();
        if (!qfInfo.isSymLink() && QLibrary::isLibrary(qstrFile))
        {
            QPluginLoader qLoader(qstrFile);

            if (qLoader.load())
            {
                QObject* pObject = qLoader.instance();
                IwmsServerPlugin* pPlugin = qobject_cast<IwmsServerPlugin*>(pObject);

                if (CHKPTR(pPlugin))
                {
                    // the init method registers the plugin to the server
                    // so a delete will destroy everything
                    pPlugin->init();
                    // don't delete the Plugin
                }
            }
        }
    }
}
