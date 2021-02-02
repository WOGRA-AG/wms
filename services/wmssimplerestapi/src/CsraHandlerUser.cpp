
// WMS Commons Includes
#include "wmsdefines.h"

// WMS Core Incldues
#include "CumUser.h"
#include "CsaUser.h"

// Own Includes
#include "CsraHandlerUser.h"

CsraHandlerUser::CsraHandlerUser()
{

}


QString CsraHandlerUser::getType()
{
    return WMS_USER;
}

QVariant CsraHandlerUser::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    if (qstrCommand.isEmpty())
    {
       qvm = p_pElement->getDetailedVariant().toMap();
       addLinksToVariant(p_pElement, qvm);
    }
    else
    {
       qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
       addLinksToVariant(p_pElement, qvm);
    }

    return qvm;
}

QVariant CsraHandlerUser::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerUser::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerUser::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    qvm.insert(WMS_LINKS, qvlLinks);
}
