// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"


//WMS Core Includes
#include "CdmLogging.h"
#include "CdmQueryEnhanced.h"
#include "CdmClass.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CsaObject.h"
#include "CsaFactory.h"
#include "CsaObjectContainer.h"
#include "CdmObjectAdaptor.h"

// Own Includes
#include "CsaQuery.h"
#include "CsraUtilities.h"
#include "CsraHandlerContainer.h"

#include "CwmsJson.h"

#include "CdmJsonToObjectMapper.h"

#define PAGE_SIZE 50

CsraHandlerContainer::CsraHandlerContainer()
    : m_bAddLinks(true)
{

}


QString CsraHandlerContainer::getType()
{
    return WMS_CONTAINER;
}

QVariant CsraHandlerContainer::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    bool bAddLinks = m_bAddLinks;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());


    if (qstrCommand.isEmpty())
    {
        CsaObjectContainer* pContainer  = dynamic_cast<CsaObjectContainer*> (p_pElement);
        if (CHKPTR(pContainer) && pContainer->hasCurrentUserReadAccess())
        {
            qvm = p_pElement->getDetailedVariant().toMap();
        }
        else
        {
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
        }
    }
    else
    {
        if (WMS_URI_CREATE == qstrCommand)
        {
            createObject(p_pElement, p_pRequest, p_pResponse, qvm);
            bAddLinks = false;
        }
        else if (WMS_URI_DELETE_ALL_OBJECTS == qstrCommand)
        {
            deleteAllObjects(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else if (WMS_LIST == qstrCommand)
        {
            listObjects(p_pElement, p_pRequest, p_pResponse, qvm);
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

void CsraHandlerContainer::createObject(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserWriteAccess())
    {
        CdmObjectContainer* pContainer = dynamic_cast<CdmObjectContainer*> (p_pElement->getElement());

        if (CHKPTR(pContainer))
        {
            CdmObject* pObject = pContainer->CreateNewObject();

            if (CHKPTR(pObject))
            {              
                CdmJsonToObjectMapper mapper;
                QString qstrBody = p_pRequest->GetBody();
                mapper.ConvertJson(pObject, qstrBody);

                if (SUCCESSFULL(pObject->Commit()))
                {
                    CdmObjectAdaptor cCdmObjectAdaptor(pObject);
                    QVariantMap qVariant = cCdmObjectAdaptor.GetVariantGraph(false, false, QStringList(), 1, 1);
                    qVariant.remove(WMS_PROCESSED_OBJECTS);
                    qvm.insert(WMS_SIMPLE_REST_DATA, qVariant);
                    CsaLocatedElement* pElement = dynamic_cast<CsaFactory*> (p_pElement->getFactory())->createScriptObject(pObject);
                    QVariantList qvlLinks = generateLinkRestSection(pElement).toList();
                    qvm.insert(WMS_LINKS, qvlLinks);
                    qvm.insert(WMS_SUCCESS, WMS_TRUE);
                    p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk);
                }
                else
                {
                    pObject->SetDeleted();
                    pObject->Commit();
                    qvm.insert(WMS_SUCCESS, WMS_FALSE);
                    qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeBadRequest));
                    p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
                }
            }
            else
            {
                ERR("Could not create new Object");
                qvm.insert(WMS_SUCCESS, WMS_FALSE);
                qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeInternalServerError));
                p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
            }
        }
        else
        {
            ERR("Invalid Container");
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeInternalServerError));
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

void CsraHandlerContainer::listObjects(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserReadAccess())
    {
        QString qstrFrom = p_pRequest->GetPathVariable("from");
        QString qstrTo = p_pRequest->GetPathVariable("to");

        if (!qstrFrom.isEmpty() && !qstrTo.isEmpty())
        {
            if (CwmsUtilities::IsNumber(qstrFrom) && CwmsUtilities::IsNumber(qstrTo))
            {
                listFromTo(p_pElement, p_pRequest, p_pResponse, qstrFrom.toInt(), qstrTo.toInt(), qvm);
            }
            else
            {
                ERR("From or To are not valid numbers");
                qvm.insert(WMS_SUCCESS, WMS_FALSE);
                qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeBadRequest));
                p_pResponse->SetStatusCode(eWmsHttpStatusCodeBadRequest);
            }
        }
        else
        {
            listAll(p_pElement, p_pRequest, p_pResponse, qvm);
        }
    }
    else
    {
        qvm.insert(WMS_SUCCESS, WMS_FALSE);
        qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
    }
}

void CsraHandlerContainer::listAll(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    Q_UNUSED(p_pRequest);
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserReadAccess())
    {
        if (CHKPTR(p_pElement))
        {
            CsraUtilities::createAndExecuteQuery(dynamic_cast<CsaObjectContainer*>(p_pElement), p_pResponse, qvm);
        }
        else
        {
            ERR("Could not convert object to CsaObjectContainer");
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeInternalServerError));
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



void CsraHandlerContainer::listFromTo(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, int p_iFrom, int p_iTo, QVariantMap& qvm)
{
    Q_UNUSED(p_pRequest);
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserReadAccess())
    {
        if (CHKPTR(p_pElement))
        {
            CsraUtilities::createAndExecuteQuery(dynamic_cast<CsaObjectContainer*>(p_pElement),p_pResponse, qvm, p_iFrom, p_iTo);
            addLinksToVariant(p_pElement,p_iFrom, p_iTo, qvm);
            m_bAddLinks = false;
        }
        else
        {
            ERR("Could not convert object to CsaObjectContainer");
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeInternalServerError));
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

void CsraHandlerContainer::deleteAllObjects(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    Q_UNUSED(p_pRequest);
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserWriteAccess())
    {
        CdmObjectContainer* pContainer = dynamic_cast<CdmObjectContainer*> (p_pElement->getElement());

        if (CHKPTR(pContainer))
        {
            CdmContainerManager* pContainerManager = pContainer->GetContainerManager();
            if (CHKPTR(pContainerManager))
            {
                pContainerManager->ReloadContainerComplete(pContainer);
                pContainer->DeleteAllObjects();
                qvm.insert(WMS_RESULT, "Container Objects deleted.");
                qvm.insert(WMS_SUCCESS, WMS_TRUE);
                p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk);
            }
        }
        else
        {
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeInternalServerError));
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

QVariant CsraHandlerContainer::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    createObject(p_pElement, p_pRequest, p_pResponse, qvm);
    if (m_bAddLinks)
    {
        addLinksToVariant(p_pElement, qvm);
    }
    return qvm;
}

QVariant CsraHandlerContainer::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserWriteAccess())
    {
        CdmObjectContainer* pContainer = dynamic_cast<CdmObjectContainer*> (p_pElement->getElement());

        if (CHKPTR(pContainer))
        {
            CsaModelElement* pElement = dynamic_cast<CsaModelElement*>(p_pElement);
            QVariantList qvlLinks;
            addMainRestLinks(pElement, qvlLinks);
            qvm.insert(WMS_LINKS, qvlLinks);
            pContainer->GetContainerManager()->DeleteContainer(pContainer);
            qvm.insert(WMS_SUCCESS, WMS_TRUE);
            qvm.insert(WMS_INFO, "Container deleted");
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk);
        }
        else
        {
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeInternalServerError));
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
        }
    }
    else
    {
        qvm.insert(WMS_SUCCESS, WMS_FALSE);
        qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
        p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
    }

    return qvm;
}


void CsraHandlerContainer::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    if (m_bAddLinks)
    {
        QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();

        CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

        if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserReadAccess())
        {
            qvlLinks.append(generateLinkMap(WMS_LIST "/all", p_pElement, WMS_LIST));

            CdmObjectContainer* pContainer = dynamic_cast<CdmObjectContainer*> (p_pElement->getElement());

            if (CHKPTR(pContainer))
            {
                int iCount = pContainer->CountObjectsOnDb();
                if (iCount > PAGE_SIZE)
                {
                    qvlLinks.append(generateLinkMap(WMS_LIST "/start", p_pElement, WMS_LIST "/?from=0&to=49"));
                }
                else
                {
                    qvlLinks.append(generateLinkMap(WMS_LIST "/start", p_pElement, WMS_LIST "/?from=0&to=" + QString::number(iCount)));
                }
            }

            qvlLinks.append(generateLinkMap(WMS_LIST, p_pElement, WMS_LIST "/{?from,to}"));

            if (pCsaContainer->hasCurrentUserWriteAccess())
            {
                qvlLinks.append(generateLinkMap(WMS_CREATE, p_pElement, WMS_URI_CREATE));
                qvlLinks.append(generateLinkMap(WMS_DELETE_ALL_OBJECTS, p_pElement, WMS_DELETE_ALL_OBJECTS));
            }

            CsaModelElement* pElement = dynamic_cast<CsaModelElement*> (p_pElement);

            if (CHKPTR(pElement))
            {
                QString qstrUri = CdmLocatedElement::CreateUri(WMS_URI_OBJECT, pElement->getKeyname(), "{id}");
                qvlLinks.append(generateLinkMap(WMS_FIND_BY_ID, qstrUri));

                qstrUri = CdmLocatedElement::CreateUri(WMS_URI_OBJECT, pElement->getKeyname(), "{keyname}");
                qvlLinks.append(generateLinkMap(WMS_FIND_BY_KEYNAME, qstrUri));
            }
        }

        qvm.insert(WMS_LINKS, qvlLinks);
    }
}


void CsraHandlerContainer::addLinksToVariant(CsaLocatedElement *p_pElement, int p_iFrom, int p_iTo, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    CsaObjectContainer* pCsaContainer = dynamic_cast<CsaObjectContainer*> (p_pElement);

    if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserReadAccess())
    {
        qvlLinks.append(generateLinkMap(WMS_LIST " all", p_pElement, WMS_LIST));

        CdmObjectContainer* pContainer = dynamic_cast<CdmObjectContainer*> (p_pElement->getElement());

        if (CHKPTR(pContainer))
        {
            int iCount = pContainer->CountObjectsOnDb();
            int iPageSizeEnd = 0;

            if (iCount > PAGE_SIZE)
            {
                iPageSizeEnd = PAGE_SIZE;
            }
            else
            {
                iPageSizeEnd = iCount -1;
            }

            // next
            if (p_iTo < iCount)
            {
                int iFrom = p_iTo + 1;
                int iTo = 0;

                iTo = iFrom + PAGE_SIZE;

                if (iTo > iCount)
                {
                    iTo = iCount;
                }

                qvlLinks.append(generateLinkMap(WMS_LIST " next", p_pElement, WMS_LIST "/?from=" +
                                                QString::number(iFrom) + "&to=" + QString::number(iTo)));
            }

            if (p_iFrom > 0)
            {
                // previous
                int iFrom = p_iFrom - PAGE_SIZE - 1;

                if (iFrom < 0)
                {
                    iFrom = 0;
                }

                int iTo = iFrom + PAGE_SIZE - 1;

                qvlLinks.append(generateLinkMap(WMS_LIST " previous", p_pElement, WMS_LIST "/?from=" +
                                                QString::number(iFrom) + "&to=" + QString::number(iTo)));
            }

            qvlLinks.append(generateLinkMap(WMS_LIST " start", p_pElement, WMS_LIST "/?from=0&to=" + QString::number(iPageSizeEnd)));


        }

        qvlLinks.append(generateLinkMap(WMS_LIST, p_pElement, WMS_LIST "/{?from,to}"));
        if (CHKPTR(pCsaContainer) && pCsaContainer->hasCurrentUserWriteAccess())
        {
            qvlLinks.append(generateLinkMap(WMS_CREATE, p_pElement, WMS_URI_CREATE));
            qvlLinks.append(generateLinkMap(WMS_DELETE_ALL_OBJECTS, p_pElement, WMS_URI_DELETE_ALL_OBJECTS));
        }

        CsaModelElement* pElement = dynamic_cast<CsaModelElement*> (p_pElement);

        if (CHKPTR(pElement))
        {
            QString qstrUri = CdmLocatedElement::CreateUri(WMS_URI_OBJECT, pElement->getKeyname(), "{id}");
            qvlLinks.append(generateLinkMap(WMS_FIND_BY_ID, qstrUri));

            qstrUri = CdmLocatedElement::CreateUri(WMS_URI_OBJECT, pElement->getKeyname(), "{keyname}");
            qvlLinks.append(generateLinkMap(WMS_FIND_BY_KEYNAME, qstrUri));
        }
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
