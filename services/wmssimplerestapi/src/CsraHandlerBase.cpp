// System and Qt Includes
#include <QUrl>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"
#include "CwmsTimeMeassurement.h"

// WMS Core
#include "CsaFactory.h"
#include "CdmLogging.h"
#include "CsaLocatedElement.h"
#include "CdmLocatedElement.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CumUser.h"
#include "CdmContainerManager.h"
#include "CsaClassManager.h"
#include "CsaContainerManager.h"
#include "CsaScheme.h"
#include "CsaManager.h"

//WMS Server
#include "CwmscomController.h"
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// Own Includes
#include "CsraRestRequestHandler.h"
#include "CsraUtilities.h"
#include "CsraHandlerBase.h"

CsraHandlerBase::CsraHandlerBase()
{

}


CsraHandlerBase::~CsraHandlerBase()
{

}

void CsraHandlerBase::handleRequest(CwmscomData* p_pData, CsaLocatedElement* p_pElement)
{
    if (p_pElement)
    {
        CwmscomDataResult* pResult = nullptr;
        pResult = GetResultContainer(p_pData, eWmsHttpStatusCodeOk, "OK", eWmscomMessageServerityInfo);
        QVariantMap qvm = handleRequest(p_pElement, p_pData->GetRequest(), p_pData->GetResponse()).toMap();
        pResult->SetResultMap(qvm);
    }
    else
    {
        CwsHttpResponse* pResponse = p_pData->GetResponse();
        pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
        GetResultContainer(p_pData, eWmsHttpStatusCodeInternalServerError, "Unknown WMS Element. Element not found", eWmscomMessageServerityError);
    }

}

void CsraHandlerBase::setHostSettingsIfUndefined(CwsHttpRequest *p_pRequest)
{
    QString qstrHost =  p_pRequest->GetHeader("Host");
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if(qstrHost.isNull() || qstrHost.isEmpty() || !qstrHost.contains(":"))
    {
        return;
    }
    QStringList qstrlHostParts = qstrHost.split(":");

    QString qstrAddress= qstrlHostParts.at(0).simplified();
    bool bPortIsNumber;
    int qstrPort = qstrlHostParts.at(1).simplified().toInt(&bPortIsNumber, 10);
    if(!bPortIsNumber) {
        return;
    }

    {
        if (CHKPTR(pManager))
        {
            CdmSettings* pSettings = pManager->GetSettings();
            if (CHKPTR(pSettings))
            {
                if (pSettings->GetHost().isEmpty()){
                    pSettings->SetHost(qstrAddress);
                    pSettings->SetPort(qstrPort);
                }
            }
        }
    }

}

void CsraHandlerBase::temporaryRedirect(CwsHttpResponse *p_pResponse, QString uri) {
    p_pResponse->AddHeader("Location", uri);
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMultipleSeeOther);
}

void CsraHandlerBase::handleRequest(CwmscomData* p_pData, CdmLocatedElement* p_pElement)
{
    CwmsTimeMeassurement cTime(false, "CsraHandlerBase::temporaryRedirect");
    if (p_pElement)
    {
        CwmscomDataResult* pResult = nullptr;
        CsaFactory factory;
        CsaLocatedElement* pSimpleElement = factory.createScriptObject(p_pElement);
        cTime.finishedTask("Create Script Object");
        if (CHKPTR(pSimpleElement))
        {
            pResult = GetResultContainer(p_pData, eWmsHttpStatusCodeOk, "OK", eWmscomMessageServerityInfo);
            cTime.finishedTask("GetResultContainer");
            QVariantMap qvm = handleRequest(pSimpleElement, p_pData->GetRequest(), p_pData->GetResponse()).toMap();
            cTime.finishedTask("Execute Request");
            if (!qvm.isEmpty())
            {
                pResult->SetResultMap(qvm);
            }
            cTime.finishedTask("Set ResultMap");
        }
        else
        {
            CwsHttpResponse* pResponse = p_pData->GetResponse();
            pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
            GetResultContainer(p_pData, eWmsHttpStatusCodeInternalServerError, "Unknown WMS Element. Element not found", eWmscomMessageServerityError);
        }
    }
}

QVariant CsraHandlerBase::handleGetCommonCommandsRequest(CsaLocatedElement* p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, const QString& p_qstrCommand)
{
    QVariantMap qvm;

    if (WMS_URI_WQL == p_qstrCommand)
    {
        QString qstrWql = p_pRequest->GetPathVariable(WMS_URI_WQL);

        if (!qstrWql.isEmpty())
        {
            CsraUtilities::executeQuery(dynamic_cast<CsaFactory*> (p_pElement->getFactory()), qstrWql, p_pResponse, qvm);
        }
        else
        {
            ERR("Path Variable wql is missing.");
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
        }
    }
    else
    {
        ERR("Unknown command");
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
    }

    return qvm;
}

QVariant CsraHandlerBase::handleRequest(CsaLocatedElement* p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    CwmsTimeMeassurement cTime(false, "CsraHandlerBase::handleRequest");
    QVariantMap qvmJson;
    QMap<QString, QString> p_qmPathVariables = p_pRequest->GetPathVariableMap();
    cTime.finishedTask("Get Path Variable Map");
    setHostSettingsIfUndefined(p_pRequest);
    cTime.finishedTask("Get Host Settings");
    switch (p_pRequest->GetMethod())
    {
    case eWsGet:
        qvmJson = handleGetRequest(p_pElement, p_pRequest, p_pResponse).toMap();
        cTime.finishedTask("Handled Get Request");
        break;
    case eWsPut:
    case eWsPost:
        qvmJson = handlePutRequest(p_pElement, p_pRequest, p_pResponse).toMap();
        cTime.finishedTask("Handled Put/Post Request");
        break;
    case eWsDelete:
        qvmJson = handleDeleteRequest(p_pElement, p_pRequest, p_pResponse).toMap();
        cTime.finishedTask("Handled Delete Request");
        break;
    default:
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
        break;
    }

    if (p_pRequest->GetMethod() != eWsDelete) // in this case p_pElement is destroyed
    {
        addLinksToVariant(p_pElement, qvmJson);
        cTime.finishedTask("added Links");
    }

    return qvmJson;
}

CwmscomDataResult* CsraHandlerBase::GetResultContainer(CwmscomData* p_pData,
                                                       int p_iReturnCode,
                                                       QString p_qstrMessage,
                                                       EwmscomMessageServerity p_eSeverity)
{
    CwmscomDataResult* pResult = nullptr;

    if (p_pData)
    {
        pResult = new CwmscomDataResult(p_pData);
        pResult->SetMessage(p_qstrMessage);
        pResult->SetMessageCode(p_iReturnCode);
        pResult->SetSeverity(p_eSeverity);
    }

    return pResult;
}
QString CsraHandlerBase::parseCommandFromUri(CsaLocatedElement* p_pElement, QString p_qstrUri)
{
    QString qstrElementUri = p_pElement->getUriInternal();
    QStringList qstrlUri = p_qstrUri.split("/", QString::SkipEmptyParts);
    QStringList qstrlElementUri = qstrElementUri.split("/", QString::SkipEmptyParts);
    QString qstrCommand;

    if (qstrlElementUri.isEmpty() || qstrlUri.last() != qstrlElementUri.last())
    {
        qstrCommand = qstrlUri.last();

        if (CwmsUtilities::IsNumber(qstrCommand))
        {
            qstrCommand = "";
        }
    }

    return qstrCommand;
}

bool CsraHandlerBase::parseBooleanPathVariable(CwsHttpRequest *p_pRequest, QString p_qstrPathVariableName, bool p_bDefaultValue)
{
    QString qstrPathVariableValue = p_pRequest->GetPathVariable(p_qstrPathVariableName);
    bool result = p_bDefaultValue;
    if (!qstrPathVariableValue.isEmpty())
    {
        result = CwmsUtilities::isValueTrue(qstrPathVariableValue);
    }
    return result;
}

QStringList CsraHandlerBase::parseStringListPathVariable(CwsHttpRequest *p_pRequest, QString p_qstrPathVariableName)
{
    QString qstrPathVariableValue = p_pRequest->GetPathVariable(p_qstrPathVariableName);
    QStringList result;
    if (!qstrPathVariableValue.isEmpty())
    {
        result = qstrPathVariableValue.split(",");
    }
    return result;
}

int CsraHandlerBase::parseIntegerPathVariable(CwsHttpRequest *p_pRequest, QString p_qstrPathVariableName, int p_iDefaultValue)
{
    QString qstrPathVariableValue = p_pRequest->GetPathVariable(p_qstrPathVariableName);
    int result = p_iDefaultValue;
    if (!qstrPathVariableValue.isEmpty() && CwmsUtilities::IsNumber(qstrPathVariableValue))
    {
        result = qstrPathVariableValue.toInt();
    }
    return result;
}


QVariant CsraHandlerBase::generateLinkMap(QString qstrLinkName, const CdmLocatedElement* p_pElement)
{
    if (CHKPTR(p_pElement))
    {
        return generateLinkMap(qstrLinkName, p_pElement->GetUri());
    }

    return QVariant();
}

QVariant CsraHandlerBase::generateLinkMap(QString qstrLinkName, const CsaLocatedElement* p_pElement)
{
    if (CHKPTR(p_pElement))
    {
        return generateLinkMap(qstrLinkName, p_pElement->getUri());
    }

    return QVariant();
}

QVariant CsraHandlerBase::generateLinkMap(QString qstrLinkName, const CsaLocatedElement* p_pElement, QString p_qstrLink)
{
    if (CHKPTR(p_pElement))
    {
        return generateLinkMap(qstrLinkName, p_pElement->getUri() + p_qstrLink);
    }

    return QVariant();
}

QVariant CsraHandlerBase::generateLinkMap(QString qstrLinkName, const CdmLocatedElement* p_pElement, QString p_qstrLink)
{
    if (CHKPTR(p_pElement))
    {
        return generateLinkMap(qstrLinkName, p_pElement->GetUri() + p_qstrLink);
    }

    return QVariant();
}

QVariant CsraHandlerBase::generateLinkMap(QString qstrLinkName, QString qstrLink)
{
    QVariantMap qvm;
    qvm.insert(WMS_REL, qstrLinkName);
    CwmsUtilities::OptimizeUrl(qstrLink);
    qvm.insert(WMS_HREF, qstrLink);
    return qvm;
}

void CsraHandlerBase::addMainRestLinks(CsaModelElement* p_pElement, QVariantList& p_rqVariantList)
{
    CdmModelElement* pElement = dynamic_cast<CdmModelElement*>(p_pElement->getElement());

    if (CHKPTR(pElement))
    {
        p_rqVariantList.append(generateLinkMap(WMS_CLASSMANAGER, pElement->GetClassManager()));
        p_rqVariantList.append(generateLinkMap(WMS_SCHEME, pElement->GetScheme()));
        p_rqVariantList.append(generateLinkMap(WMS_CONTAINERMANAGER, pElement->GetContainerManager()));
        p_rqVariantList.append(generateLinkMap(WMS_DATAPROVIDER, pElement->GetDataProvider()));
        p_rqVariantList.append(generateLinkMap(WMS_WQL, pElement, WMS_URI_WQL "/{?wql}"));
    }
}

QVariant CsraHandlerBase::generateLinkRestSection(CsaLocatedElement* p_pElement)
{
    QVariantList qvList;

    if (CHKPTR(p_pElement))
    {
        qvList.append(generateLinkMap(WMS_SELF, p_pElement));
    }

    if (p_pElement->isModelElement())
    {
        addMainRestLinks(dynamic_cast<CsaModelElement*>(p_pElement), qvList);
    }
    else
    {
        qvList.append(generateLinkMap(WMS_CLASSMANAGER, dynamic_cast<CsaClassManager*>(p_pElement->getClassManager())));
        qvList.append(generateLinkMap(WMS_SCHEME, dynamic_cast<CsaScheme*>(p_pElement->getScheme())));
        qvList.append(generateLinkMap(WMS_CONTAINERMANAGER, dynamic_cast<CsaContainerManager*>(p_pElement->getContainerManager())));
        CsaManager* pManager = dynamic_cast<CsaManager*>(p_pElement->getManager());

        if (pManager)
        {
            qvList.append(generateLinkMap(WMS_DATAPROVIDER, pManager));
        }

        qvList.append(generateLinkMap(WMS_WQL, p_pElement, WMS_URI_WQL "/{?wql}"));
    }

    return qvList;
}

bool CsraHandlerBase::isSessionUserAdmin()
{
    bool bRet = false;
    const CumUser* pUser = CdmSessionManager::GetSessionManager()->GetCurrentUser();

    if (CHKPTR(pUser) && pUser->IsAdministrator())
    {
        bRet = true;
    }

    return bRet;
}
