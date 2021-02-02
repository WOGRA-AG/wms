
// WMS Commons Includes
#include "wmsdefines.h"

// WMS Core Incldues
#include "CumUserGroup.h"
#include "CsaUserGroup.h"

// Own Includes
#include "CsraHandlerUserGroup.h"

CsraHandlerUserGroup::CsraHandlerUserGroup()
{

}


QString CsraHandlerUserGroup::getType()
{
    return WMS_USERGROUP;
}

QVariant CsraHandlerUserGroup::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
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

QVariant CsraHandlerUserGroup::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerUserGroup::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerUserGroup::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    qvm.insert(WMS_LINKS, qvlLinks);
}
