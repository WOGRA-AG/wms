// WMSCommons Includes
#include "wmsdefines.h"

// WMS Core Includes
#include "CsaClassManager.h"
#include "CdmClassManager.h"

// Simple Rest Api Includes
#include "CsraHandlerClassManager.h"

CsraHandlerClassManager::CsraHandlerClassManager()
{

}


QString CsraHandlerClassManager::getType()
{
    return WMS_CLASSMANAGER;
}

QVariant CsraHandlerClassManager::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    if (qstrCommand.isEmpty())
    {
        qvm = p_pElement->getDetailedVariant().toMap();
    }
    else
    {
        qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
        addLinksToVariant(p_pElement, qvm);
    }

    return qvm;
}

QVariant CsraHandlerClassManager::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerClassManager::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerClassManager::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    CdmLocatedElement* pElement = p_pElement->getElement();

    if (CHKPTR(pElement))
    {
        QString qstrUri = CdmLocatedElement::CreateUri(WMS_CLASS,"{keyname}");
        qvlLinks.append(generateLinkMap(WMS_FIND_BY_KEYNAME, qstrUri));
        qstrUri = CdmLocatedElement::CreateUri(WMS_CLASS,"{id}");
        qvlLinks.append(generateLinkMap(WMS_FIND_BY_ID, qstrUri));
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
