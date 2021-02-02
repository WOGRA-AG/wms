// System and Qt Includes

// WMS COMMONS Includes
#include "CwsHttpRequest.h"
#include "wmsdefines.h"
#include "CwmsUtilities.h"
#include "CwmsTimeMeassurement.h"

// WMS Core Includes
#include "CdmSessionManager.h"
#include "CdmSession.h"
#include "CdmLogging.h"
#include "CdmLocatedElement.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CsaFactory.h"
#include "CsaObject.h"
#include "CsaFunction.h"

#include "CwmsApplicationServices.h"

// WMS Com Includes
#include "CwmscomController.h"
#include "CwmscomData.h"

// Own Includes
#include "CsraHandlerBase.h"
#include "CsraHandlerClass.h"
#include "CsraHandlerClassManager.h"
#include "CsraHandlerContainer.h"
#include "CsraHandlerContainerManager.h"
#include "CsraHandlerFunction.h"
#include "CsraHandlerMember.h"
#include "CsraHandlerObject.h"
#include "CsraHandlerScheme.h"
#include "CsraHandlerUser.h"
#include "CsraHandlerUserGroup.h"
#include "CsraHandlerValue.h"
#include "CsraHandlerManager.h"
#include "CsraRestRequestHandler.h"


CsraRestRequestHandler::CsraRestRequestHandler(CwmscomController* p_pController)
    : CwmscomResourceBase(p_pController, "Api", true, true)
{

}


void CsraRestRequestHandler::execute(CwmscomData *p_pData)
{
    CwmsTimeMeassurement cTime(false, "CsraRestRequestHandler::execute");
    if (CHKPTR(p_pData))
    {
        CwsHttpRequest* pRequest = p_pData->GetRequest();

        if (CHKPTR(pRequest))
        {
            if (Authenticate(pRequest))
            {
                cTime.finishedTask("Authenticate");
                executeP(p_pData);
                cTime.finishedTask("Execute Request");
            }
            else
            {
                CwsHttpResponse* pResponse = p_pData->GetResponse();
                pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
                pResponse->AddHeader(WWW_AUTHENTICATE, BASIC_REALM);
                GetResultContainer(p_pData, eWmsHttpStatusCodeUnauthorized, "Login failed!", eWmscomMessageServerityError);
            }
        }
    }
}

void CsraRestRequestHandler::executeDescription(CwmscomData *p_pData)
{
    Q_UNUSED(p_pData);
    NOTIMPLEMENTED;
}


QVariantMap CsraRestRequestHandler::getConfiguration()
{
    NOTIMPLEMENTED;
    return QVariantMap();
}

QString CsraRestRequestHandler::ParseWmsUri(QString p_qstrContextPath)
{
    QString qstrWmsUri;
    QString qstrRequestHandlerPath = GetContextPathToRequestHandler();
    CwmsUtilities::OptimizeUrl(p_qstrContextPath);

    int iPos = p_qstrContextPath.indexOf(qstrRequestHandlerPath);
    if (iPos <= 0)
    {
        qstrWmsUri = p_qstrContextPath.mid(iPos + qstrRequestHandlerPath.length()).simplified();
    }

    return qstrWmsUri;
}

void CsraRestRequestHandler::execute(CwmscomData *p_pData, QString qstrWmsUri)
{
    CwmsTimeMeassurement cTime(false, "CsraRestRequestHandler::execute");
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        CdmLocatedElement* pElement = pDataProvider->GetUriObject(qstrWmsUri);
        cTime.finishedTask("Find LocatedElement");

        if (!pElement && WMS_METHODS == CdmDataProvider::GetUriType(qstrWmsUri))
        {
            CsaFactory factory;
            CsaFunction* pFunction = CsaFunction::getFunctionElement(qstrWmsUri, factory);
            cTime.finishedTask("Find Function");

            if (CHKPTR(pFunction))
            {
                QScopedPointer<CsraHandlerBase> pHandler(getHandler(pFunction));
                cTime.finishedTask("Find Request Handler");

                if (CHKPTR(pHandler))
                {
                    pHandler->handleRequest(p_pData, pFunction);
                    cTime.finishedTask("Execute Request");
                }
                else
                {
                    CwsHttpResponse* pResponse = p_pData->GetResponse();
                    pResponse->SetStatusCode(eWmsHttpStatusCodeNotFound);
                }
            }
        }
        else if (pElement)
        {
            QScopedPointer<CsraHandlerBase> pHandler(getHandler(pElement));
            cTime.finishedTask("Find Element Handler");

            if (CHKPTR(pHandler))
            {
                pHandler->handleRequest(p_pData, pElement);
                cTime.finishedTask("Execute Element Request");
            }
            else
            {
                CwsHttpResponse* pResponse = p_pData->GetResponse();
                pResponse->SetStatusCode(eWmsHttpStatusCodeNotFound);
            }
        }
        else
        {
            CwsHttpResponse* pResponse = p_pData->GetResponse();
            pResponse->SetStatusCode(eWmsHttpStatusCodeNotFound);
        }

        CdmScheme* pScheme = pDataProvider->GetCurrentScheme();

        if (CHKPTR(pScheme))
        {
            pScheme->ResetContainerManager();
            cTime.finishedTask("Reset ContainerManager");
        }
    }
    else
    {
        CwsHttpResponse* pResponse = p_pData->GetResponse();
        pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }
}

CsraHandlerBase* CsraRestRequestHandler::getHandler(CsaLocatedElement* p_pElement)
{
    return getHandler(p_pElement->getElement());
}

CsraHandlerBase* CsraRestRequestHandler::getHandler(CdmLocatedElement* p_pElement)
{
    CsraHandlerBase*  pHandler = nullptr;

    if (p_pElement)
    {
        if (p_pElement->IsClass())
        {
            pHandler = new CsraHandlerClass();
        }
        else if (p_pElement->IsClassManager())
        {
            pHandler = new CsraHandlerClassManager();
        }
        else if (p_pElement->IsContainer())
        {
            pHandler = new CsraHandlerContainer();

        }
        else if (p_pElement->IsContainerManager())
        {
            pHandler = new CsraHandlerContainerManager();

        }
        else if (p_pElement->IsMember())
        {
            pHandler = new CsraHandlerMember();

        }
        else if (p_pElement->IsMethod())
        {
            pHandler = new CsraHandlerFunction();

        }
        else if (p_pElement->IsObject())
        {
            pHandler = new CsraHandlerObject();

        }
        else if (p_pElement->IsScheme())
        {
            pHandler = new CsraHandlerScheme();

        }
        else if (p_pElement->IsUser())
        {
            pHandler = new CsraHandlerUser();

        }
        else if (p_pElement->IsUserGroup())
        {
            pHandler = new CsraHandlerUserGroup();
        }
        else if (p_pElement->IsValue())
        {
            pHandler = new CsraHandlerValue();
        }
        else if (p_pElement->IsDataProvider())
        {
            pHandler = new CsraHandlerManager();
        }
        else
        {
            ERR("Unkonwn Type");
        }
    }

    return pHandler;
}

void CsraRestRequestHandler::executeP(CwmscomData *p_pData)
{
    CwmsTimeMeassurement cTime(false, "CsraRestRequestHandler::executeP");
    if (CHKPTR(p_pData))
    {
        CwsHttpRequest* pRequest = p_pData->GetRequest();

        if (CHKPTR(pRequest))
        {
            cTime.finishedTask("Get Request Data");
            QString qstrWmsUri = ParseWmsUri(pRequest->GetContextPath());
            cTime.finishedTask("Parse WMS Uri");


            if (qstrWmsUri.length() > 0)
            {
                execute(p_pData, qstrWmsUri);
                cTime.finishedTask("Execute Request");
            }
            else
            {
                CwsHttpResponse* pResponse = p_pData->GetResponse();

                if (CHKPTR(pResponse))
                {
                    pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
                }

                GetResultContainer(p_pData, eWmsHttpStatusCodeBadRequest, "Invalid URI atleast Scheme is needed in the URI.", eWmscomMessageServerityError);
            }
        }
    }
}

bool CsraRestRequestHandler::Authenticate(CwsHttpRequest* p_pRequest)
{
    if (CHKPTR(p_pRequest))
    {
        QString qstrAuthType = p_pRequest->GetAuthType();

        if (qstrAuthType.toLower() == "basic")
        {
            QString qstrCredentials = p_pRequest->GetAuthValue();

            if (!qstrCredentials.isEmpty())
            {
                CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

                if (CHKPTR(pSessionManager))
                {
                    CdmSession* pSession = pSessionManager->FindSessionByBaseAuth(qstrCredentials);

                    if (pSession)
                    {
                        CwmsApplicationServices::InstallFunctionsAndPlugins();

                        pSession->SetServerRequestPath("Rest/Api");
                        pSessionManager->AddSessionToThreadContext(pSession);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

QString CsraRestRequestHandler::GetResourceDescription()
{
    NOTIMPLEMENTED;
    return "";
}



QString CsraRestRequestHandler::GetContextPathToRequestHandler()
{
    if (CHKPTR(GetController()))
    {
        CdmSettings cSettings(eDmSettingsModeServer);
        QString qstrPath = cSettings.GetPath() + "/" + GetController()->GetName() + "/" + getName() + "/";

        if (!qstrPath.startsWith("/"))
        {
            qstrPath = "/" + qstrPath;
        }

        return qstrPath;
    }

    return "";
}


QString CsraRestRequestHandler::getVersion()
{
    return "0.0.1";
}



void CsraRestRequestHandler::ExecuteGet(CwmscomData *p_pData)
{
    Q_UNUSED(p_pData);
    NOTIMPLEMENTED;
}
