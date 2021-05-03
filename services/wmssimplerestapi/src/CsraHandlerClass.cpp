// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsTimeMeassurement.h"

// WMS Manager Includes
#include "CdmClass.h"
#include "CdmLogging.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CsaClass.h"
#include "CsaContainerManager.h"

// Simple Rest Api Includes
#include "CsraHandlerClass.h"

CsraHandlerClass::CsraHandlerClass()
{

}


QString CsraHandlerClass::getType()
{
    return WMS_CLASS;
}

QVariant CsraHandlerClass::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    CwmsTimeMeassurement cTime(false, "CsraHandlerClass::handleGetRequest");
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());
    cTime.finishedTask("Parsed Command from URI");

    if (qstrCommand.isEmpty())
    {
        qvm = p_pElement->getDetailedVariant().toMap();
        cTime.finishedTask("Get Detailed Variant");
    }
    else
    {
        if (qstrCommand == WMS_URI_CONTAINER)
        {
            getContainerList(p_pElement, p_pRequest, p_pResponse, qvm);
            cTime.finishedTask("Get Container List");
        }
        else
        {
            qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
            cTime.finishedTask("Handled Common Commands Request");
        }
    }

    addLinksToVariant(p_pElement, qvm);
    cTime.finishedTask("Add Links to Variant");
    return qvm;
}

QVariant CsraHandlerClass::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerClass::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

void CsraHandlerClass::getContainerList(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    Q_UNUSED(p_pRequest);
    CsaClass* pClass = dynamic_cast<CsaClass*> (p_pElement);
    CsaContainerManager* pContainerManager = dynamic_cast<CsaContainerManager*> (p_pElement->getContainerManager());

    if (CHKPTR(pContainerManager) && CHKPTR(pClass))
    {
        QList<QString> qllContainers = pContainerManager->getInternals()->GetContainerList(pClass->getId());
        QList<QString>::iterator qllIt = qllContainers.begin();
        QList<QString>::iterator qllItEnd = qllContainers.end();
        QVariantList qvlResults;

        for (; qllIt != qllItEnd; ++qllIt)
        {
            QVariantMap qvmResult;
            QString qstrKeyname = *qllIt;
            qvmResult.insert(WMS_KEYNAME, qstrKeyname);
            QString qstrLink = CdmLocatedElement::CreateUri(WMS_CONTAINER, qstrKeyname);
            qvmResult.insert(WMS_LINKS, qstrLink);
            qvlResults.append(qvmResult);
        }

        qvm.insert(WMS_RESULT, qvlResults);
        qvm.insert("success", WMS_TRUE);
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk);
    }
    else
    {
        ERR("No valid Containermanager pointer");
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }
}


void CsraHandlerClass::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    CdmLocatedElement* pElement = p_pElement->getElement();

    if (CHKPTR(pElement))
    {
        qvlLinks.append(generateLinkMap(WMS_CONTAINERS, p_pElement->getUri() + "/" WMS_URI_CONTAINER));
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
