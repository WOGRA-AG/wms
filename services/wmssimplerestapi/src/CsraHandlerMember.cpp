// WMS Commons Includes
#include "wmsdefines.h"

//WMS Core Includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CsaMember.h"

#include "CsraHandlerMember.h"

CsraHandlerMember::CsraHandlerMember()
{

}


QString CsraHandlerMember::getType()
{
    return WMS_MEMBER;
}

QVariant CsraHandlerMember::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
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

QVariant CsraHandlerMember::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;

    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerMember::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerMember::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();

    CdmClass* pClass = dynamic_cast<CsaMember*> (p_pElement)->getInternals()->GetClass();

    if (CHKPTR(pClass))
    {
        qvlLinks.append(generateLinkMap(WMS_CLASS, pClass));
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
