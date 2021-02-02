
// WMS Commons Includes
#include "wmsdefines.h"

// WMS Core Incldues
#include "CdmValue.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CsaValue.h"
#include "CdmValueContainerRef.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringString.h"
#include "CdmValueListDouble.h"
#include "CdmValueListInt.h"
#include "CdmValueListObjects.h"
#include "CdmValueListString.h"
#include "CdmValueObjectRef.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"
#include "CumUser.h"
#include "CumUserGroup.h"

// Own Includes
#include "CsraHandlerValue.h"

CsraHandlerValue::CsraHandlerValue()
{

}


QString CsraHandlerValue::getType()
{
    return WMS_VALUE;
}

QVariant CsraHandlerValue::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    bool bAddLinks = true;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    if (qstrCommand.isEmpty())
    {
        CsaValue* pValue = dynamic_cast<CsaValue*> (p_pElement);

        if (CHKPTR(pValue) && pValue->hasCurrentUserReadAccess())
        {
            qvm = p_pElement->getDetailedVariant().toMap();
        }
        else
        {
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
        }
        qvm = p_pElement->getDetailedVariant().toMap();
    }
    else
    {
        if (qstrCommand == WMS_CONTENT)
        {
            content(p_pElement, p_pRequest, p_pResponse, qvm);
            bAddLinks = false;
        }
        else
        {
            qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
        }
    }

    if (bAddLinks)
    {
        addLinksToVariant(p_pElement, qvm);
    }

    return qvm;
}

void CsraHandlerValue::content(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    CsaValue* pValue = dynamic_cast<CsaValue*> (p_pElement);

    if (CHKPTR(pValue) && pValue->hasCurrentUserWriteAccess())
    {
        CdmValue* pCdmValue = pValue->getInternals();

        if (CHKPTR(pCdmValue))
        {
            if (pCdmValue->GetValueType() == eDmValueBinaryDocument)
            {
                CdmValueBinaryDocument* pBinDoc = dynamic_cast<CdmValueBinaryDocument*> (pCdmValue);

                if (CHKPTR(pBinDoc))
                {
                    p_pResponse->SetBody(pBinDoc->GetBase64());
                    p_pRequest->AddHeader("Content-Type", "application/" + pBinDoc->GetFileType());
                }
                else
                {
                    p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
                }
            }
            else
            {
                p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
            }
        }
        else
        {
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
        }
    }
    else
    {
        qvm.insert(WMS_SUCCESS, WMS_FALSE);
        qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
    }
}

QVariant CsraHandlerValue::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert(WMS_SUCCESS, WMS_FALSE);
    qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeMethodNotAllowed));
    addLinksToVariant(p_pElement, qvm);
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerValue::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert(WMS_SUCCESS, WMS_FALSE);
    qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeMethodNotAllowed));
    addLinksToVariant(p_pElement, qvm);
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

void CsraHandlerValue::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    CsaValue* pValue = dynamic_cast<CsaValue*> (p_pElement);

    if (CHKPTR(pValue) && pValue->hasCurrentUserReadAccess())
    {
        CdmValue* pCdmValue = pValue->getInternals();

        if (CHKPTR(pCdmValue)   )
        {
            qvlLinks.append(generateLinkMap(WMS_MEMBER, pCdmValue->GetMember()->GetUri()));
            qvlLinks.append(generateLinkMap(WMS_OBJECT, pCdmValue->GetObject()->GetUri()));

            if (pCdmValue->GetValueType() == eDmValueContainerRef)
            {
                CdmValueContainerRef* pContainerRef = dynamic_cast<CdmValueContainerRef*> (pCdmValue);

                if (CHKPTR(pContainerRef))
                {
                    CdmObjectContainer* pContainer = pContainerRef->GetContainer();

                    if (pContainer)
                    {
                        qvlLinks.append(generateLinkMap(WMS_CONTAINER, pContainer->GetUri()));
                    }
                }
            }
            else if (pCdmValue->GetValueType() == eDmValueObjectRef)
            {
                CdmValueObjectRef* pObjectRef = dynamic_cast<CdmValueObjectRef*> (pCdmValue);

                if (CHKPTR(pObjectRef))
                {
                    CdmObject* pObject = pObjectRef->GetObject();
                    if (pObject)
                    {
                        qvlLinks.append(generateLinkMap(WMS_OBJECT, pObject->GetUri()));
                    }
                }
            }
            else if (pCdmValue->GetValueType() == eDmValueUser)
            {
                CdmValueUser* pValueUser = dynamic_cast<CdmValueUser*> (pCdmValue);

                if (CHKPTR(pValueUser))
                {
                    CumUser* pUser = pValueUser->GetUser();

                    if (pUser)
                    {
                        qvlLinks.append(generateLinkMap(WMS_USER, pUser->GetUri()));
                    }
                }
            }
            else if (pCdmValue->GetValueType() == eDmValueUserGroup)
            {
                CdmValueUserGroup* pValueUserGroup = dynamic_cast<CdmValueUserGroup*> (pCdmValue);

                if (CHKPTR(pValueUserGroup))
                {
                    CumUserGroup* pUserGroup = pValueUserGroup->GetUserGroup();

                    if (pUserGroup)
                    {
                        qvlLinks.append(generateLinkMap(WMS_USERGROUP, pUserGroup->GetUri()));
                    }
                }
            }
        }
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}

