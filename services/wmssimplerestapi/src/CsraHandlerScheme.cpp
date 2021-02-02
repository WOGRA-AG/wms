// WMS Commons Includes
#include "wmsdefines.h"

// WMS Core includes
#include "CdmScheme.h"

// Own Incldues
#include "CsraHandlerScheme.h"

CsraHandlerScheme::CsraHandlerScheme()
{

}


QString CsraHandlerScheme::getType()
{
    return WMS_SCHEME;
}

QVariant CsraHandlerScheme::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
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

QVariant CsraHandlerScheme::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerScheme::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerScheme::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    qvm.insert(WMS_LINKS, qvlLinks);
}
