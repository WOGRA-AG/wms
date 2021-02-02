// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"


//WMS Core Includes
#include "CdmLogging.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CsaContainerManager.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"

// Own Includes
#include "CsraHandlerContainer.h"
#include "CsraHandlerContainerManager.h"

CsraHandlerContainerManager::CsraHandlerContainerManager()
{

}


QString CsraHandlerContainerManager::getType()
{
    return WMS_CONTAINERMANAGER;
}

QVariant CsraHandlerContainerManager::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    if (qstrCommand.isEmpty())
    {
        qvm = p_pElement->getDetailedVariant().toMap();
    }
    else
    {
        if (WMS_URI_CREATE == qstrCommand)
        {
            create(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else if (WMS_GET_LIST_BY_CLASS_ID == qstrCommand)
        {
            getListByClassId(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else if (WMS_GET_LIST_BY_CLASS_KEYNAME == qstrCommand)
        {
            getListByClassKeyname(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else
        {
            qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
            addLinksToVariant(p_pElement, qvm);
        }
    }

    return qvm;
}

void CsraHandlerContainerManager::create(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    CsaContainerManager* pContainerManager = dynamic_cast<CsaContainerManager*> (p_pElement);

    if (CHKPTR(pContainerManager))
    {
        if (p_pRequest->HasPathVariable(WMS_KEYNAME) && p_pRequest->HasPathVariable(WMS_CLASS_KEYNAME))
        {
            QString qstrKeyname = p_pRequest->GetPathVariable(WMS_KEYNAME);
            QString qstrClass = p_pRequest->GetPathVariable(WMS_CLASS_KEYNAME);
            CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*> (pContainerManager->createContainer(qstrKeyname, qstrClass));

            if (pContainer)
            {
                QVariantMap qvmResult = pContainer->getDetailedVariant().toMap();
                CsraHandlerContainer containerHandler;
                containerHandler.addLinksToVariant(pContainer, qvmResult);
                qvm.insert(WMS_RESULT, qvmResult);
            }
            else
            {
                ERR("could not create container");
                p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
            }
        }
        else
        {
            ERR("keyname or classkeyname or both ar missing");
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
        }
    }
    else
    {
        ERR("No valid Containermanager pointer");
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }
}

void CsraHandlerContainerManager::getListByClassId(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    CsaContainerManager* pContainerManager = dynamic_cast<CsaContainerManager*> (p_pElement);

    if (CHKPTR(pContainerManager))
    {
        if (p_pRequest->HasPathVariable(WMS_ID))
        {
            QString qstrClassKeyname = p_pRequest->GetPathVariable(WMS_ID);
            QLinkedList<QString> qllContainers = pContainerManager->getInternals()->GetContainerList(qstrClassKeyname.toLong());
            QLinkedList<QString>::iterator qllIt = qllContainers.begin();
            QLinkedList<QString>::iterator qllItEnd = qllContainers.end();
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
            ERR("keyname is missing");
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
        }
    }
    else
    {
        ERR("No valid Containermanager pointer");
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }
}

void CsraHandlerContainerManager::getListByClassKeyname(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    CsaContainerManager* pContainerManager = dynamic_cast<CsaContainerManager*> (p_pElement);

    if (CHKPTR(pContainerManager))
    {
        if (p_pRequest->HasPathVariable(WMS_CLASS_KEYNAME))
        {
            QString qstrClassKeyname = p_pRequest->GetPathVariable(WMS_CLASS_KEYNAME);
            QLinkedList<QString> qllContainers = pContainerManager->getInternals()->GetContainerList(qstrClassKeyname);
            QLinkedList<QString>::iterator qllIt = qllContainers.begin();
            QLinkedList<QString>::iterator qllItEnd = qllContainers.end();
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
            ERR("keyname is missing");
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
        }
    }
    else
    {
        ERR("No valid Containermanager pointer");
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }
}

QVariant CsraHandlerContainerManager::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerContainerManager::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerContainerManager::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    CdmLocatedElement* pElement = p_pElement->getElement();

    if (CHKPTR(pElement))
    {
        QString qstrUri = CdmLocatedElement::CreateUri(WMS_CONTAINER,"{id}");
        qvlLinks.append(generateLinkMap(WMS_FIND_BY_ID, qstrUri));
        qstrUri = CdmLocatedElement::CreateUri(WMS_CONTAINER,"{" WMS_KEYNAME "}");
        qvlLinks.append(generateLinkMap(WMS_FIND_BY_KEYNAME, qstrUri));
        qvlLinks.append(generateLinkMap(WMS_CREATE, p_pElement, WMS_URI_CREATE "/{?" WMS_KEYNAME "," WMS_CLASS_KEYNAME "}"));
        qvlLinks.append(generateLinkMap(WMS_GET_LIST_BY_CLASS_ID, p_pElement, WMS_GET_LIST_BY_CLASS_ID "/{?" WMS_ID "}"));
        qvlLinks.append(generateLinkMap(WMS_GET_LIST_BY_CLASS_KEYNAME, p_pElement, WMS_GET_LIST_BY_CLASS_KEYNAME "/{?" WMS_CLASS_KEYNAME "}"));
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
