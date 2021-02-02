// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"


//WMS Core Includes
#include "CdmRights.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CsaClassManager.h"
#include "CsaContainerManager.h"
#include "CsaScheme.h"
#include "CsaManager.h"
#include "CsaObject.h"
#include "CsaFunction.h"

// Own Includes
#include "CsraHandlerFunction.h"

CsraHandlerFunction::CsraHandlerFunction()
{

}


QString CsraHandlerFunction::getType()
{
    return WMS_METHODS;
}

QVariant CsraHandlerFunction::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (p_pElement->getElement());

    if (CHKPTR(pMethod))
    {
        if (pMethod->GetRights().HasCurrentUserWriteAccess())
        {
            if (qstrCommand.isEmpty())
            {
                qvm = p_pElement->getDetailedVariant().toMap();
            }
            else
            {
                if (WMS_EXECUTE == qstrCommand)
                {
                    execute(p_pElement, p_pRequest, p_pResponse, qvm);
                }
                else
                {
                    qvm = handleGetCommonCommandsRequest(p_pElement,p_pRequest, p_pResponse, qstrCommand).toMap();
                }
            }
        }
        else
        {
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
        }
    }

    addLinksToVariant(p_pElement, qvm);
    return qvm;
}

void CsraHandlerFunction::execute(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    if (CHKPTR(p_pElement))
    {
        CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (p_pElement->getElement());

        if (CHKPTR(pMethod))
        {
            int iParameterCount = pMethod->GetParameterCount();
            QVariantList qvlParams;

            for (int iPos = 0; iPos < iParameterCount; ++iPos)
            {
                CdmClassMethodParameter cParameter = pMethod->GetParameterByPos(iPos);
                QString qstrName = cParameter.GetName();
                if (p_pRequest->HasPathVariable(qstrName))
                {
                    qvlParams.append(p_pRequest->GetPathVariable(qstrName));
                }
                else
                {
                    ERR("Paraemter for function call is missing");
                    qvm.insert(WMS_SUCCESS, WMS_FALSE);
                    qvm.insert(WMS_MESSAGE, "Parameter " + qstrName + " is missing");
                    qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeBadRequest));
                    p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
                    return;
                }

            }

            CsaFunction* pFunction = dynamic_cast<CsaFunction*> (p_pElement);

            if (CHKPTR(pFunction))
            {
                QVariant qvResult = pFunction->execute(qvlParams);
                qvm.insert(WMS_RESULT, qvResult);
                p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk);
            }
        }
    }
}

QVariant CsraHandlerFunction::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert(WMS_SUCCESS, WMS_FALSE);
    qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeMethodNotAllowed));
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerFunction::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert(WMS_SUCCESS, WMS_FALSE);
    qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeMethodNotAllowed));
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerFunction::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();

    CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (p_pElement->getElement());

    if (CHKPTR(pMethod))
    {
        int iParameterCount = pMethod->GetParameterCount();
        QString qstrParams;

        if (iParameterCount > 0)
        {
            qstrParams = "{?";
            for (int iPos = 0; iPos < iParameterCount; ++iPos)
            {
                if (iPos > 0)
                {
                    qstrParams += ", ";
                }
                CdmClassMethodParameter cParameter = pMethod->GetParameterByPos(iPos);
                qstrParams += cParameter.GetName();
            }

            qstrParams += "}";
        }

        qvlLinks.append(generateLinkMap(WMS_EXECUTE, p_pElement, WMS_EXECUTE "/" + qstrParams));

        CdmClass* pClass = pMethod->GetClass();

        if (pClass)
        {
             qvlLinks.append(generateLinkMap(WMS_CLASS, pClass));
        }

        CsaFunction* pFunction = dynamic_cast<CsaFunction*> (p_pElement);

        if (CHKPTR(pFunction))
        {
            qvlLinks.append(generateLinkMap(WMS_CLASSMANAGER, dynamic_cast<CsaClassManager*>(pFunction->getClassManager())));
            qvlLinks.append(generateLinkMap(WMS_CONTAINERMANAGER, dynamic_cast<CsaContainerManager*>(pFunction->getContainerManager())));
            qvlLinks.append(generateLinkMap(WMS_SCHEME, dynamic_cast<CsaScheme*>(pFunction->getScheme())));
            qvlLinks.append(generateLinkMap(WMS_URI_DATAPROVIDER, dynamic_cast<CsaManager*>(pFunction->getManager())));
            qvlLinks.append(generateLinkMap(WMS_WQL, pFunction, WMS_URI_WQL "/{?wql}"));

            CsaObject* pObject = pFunction->getObject();

            if (pObject)
            {
                qvlLinks.append(generateLinkMap(WMS_OBJECT, pObject));
            }
        }
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
