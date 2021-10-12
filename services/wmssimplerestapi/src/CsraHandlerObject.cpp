// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsJson.h"
#include "CwmsUtilities.h"

// WMS Core includes
#include "CdmClassMethod.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmObjectAdaptor.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CsaFunction.h"
#include "CsaObjectContainer.h"
#include "CsaObject.h"

// Own Includes
#include "CsraHandlerObject.h"
#include "CdmJsonToObjectMapper.h"

CsraHandlerObject::CsraHandlerObject()
{

}

QString CsraHandlerObject::getType()
{
    return WMS_OBJECT;
}

QVariant CsraHandlerObject::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    if (qstrCommand.isEmpty())
    {
        CsaObject* pObject = dynamic_cast<CsaObject*> (p_pElement);

        if (CHKPTR(pObject) && pObject->hasCurrentUserReadAccess())
        {
            QVariantMap qvmObj = pObject->getObjectGraphVariant(false, false, QStringList(), 1, 1);
            //addLinksToVariant(p_pElement, qvmObj);
            qvmObj.remove(WMS_PROCESSED_OBJECTS);
            qvm.insert(WMS_SIMPLE_REST_DATA, qvmObj);
        }
        else
        {
            qvm.insert(WMS_SUCCESS, WMS_FALSE);
            qvm.insert(WMS_ERROR, CwmsHttpService::TranslateStatusCodeToString(eWmsHttpStatusCodeUnauthorized));
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeUnauthorized);
        }
    }
    else if(qstrCommand == WMS_GRAPH)
    {
        CsaObject* pObject = dynamic_cast<CsaObject*> (p_pElement);

        if (CHKPTR(pObject) && pObject->hasCurrentUserReadAccess())
        {
            bool followOwnerObjectlist = parseBooleanPathVariable(p_pRequest, WMS_FOLLOW_NON_OWNER_OBJECTLIST, true);
            bool followOwnerObject = parseBooleanPathVariable(p_pRequest, WMS_FOLLOW_NON_OWNER_OBJECT, true);
            QStringList qstrExcludedKeynames = parseStringListPathVariable(p_pRequest,WMS_EXCLUDED_KEYNAMES);
            int iMaxDepth = parseIntegerPathVariable(p_pRequest, WMS_MAX_DEPTH, 10);
            int iMaxObjects = parseIntegerPathVariable(p_pRequest, WMS_MAX_OBJECTS, 1000);
            QVariantMap qvmGraph;
            qvmGraph = pObject->getObjectGraphVariant(followOwnerObjectlist, followOwnerObject, qstrExcludedKeynames, iMaxDepth, iMaxObjects);
            qvm.insert(WMS_GRAPH, qvmGraph);
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
        CsaObject* pObject = dynamic_cast<CsaObject*> (p_pElement);
        CdmValue *value = pObject->getInternals()->GetValue(qstrCommand);
        if(value) {
            qvm[qstrCommand] = value->GetVariant();
        } else {
            qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
        }
    }

    addLinksToVariant(p_pElement, qvm);
    return qvm;
}

QVariant CsraHandlerObject::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    CsaObject* pObject = dynamic_cast<CsaObject*> (p_pElement);

    if (CHKPTR(pObject) && pObject->hasCurrentUserWriteAccess())
    {
        CdmObject* pCdmObject = dynamic_cast<CdmObject*> (p_pElement->getElement());

        if (CHKPTR(pCdmObject))
        {
            CdmJsonToObjectMapper mapper;
            QString qstrBody = p_pRequest->GetBody();
            mapper.ConvertJson(pCdmObject, qstrBody);
            qvm["ObjectID"] = pCdmObject->GetId();

            if (SUCCESSFULL(pObject->commit()))
            {
                QVariantMap qVariant = pObject->getObjectGraphVariant(false, false, QStringList(), 1, 1);
                qVariant.remove(WMS_PROCESSED_OBJECTS);
                qvm.insert(WMS_SIMPLE_REST_DATA, qVariant);
                qvm.insert(WMS_SUCCESS, WMS_TRUE);
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

QVariant CsraHandlerObject::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    CsaObject* pObject = dynamic_cast<CsaObject*> (p_pElement);

    if (CHKPTR(pObject) && pObject->hasCurrentUserWriteAccess())
    {
        CdmObject* pObject = dynamic_cast<CdmObject*> (p_pElement->getElement());

        if (CHKPTR(pObject))
        {
            pObject->SetDeleted();
            if (SUCCESSFULL(pObject->Commit()))
            {
                qvm.insert(WMS_SUCCESS, WMS_TRUE);
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

void CsraHandlerObject::addValueDetailsLinks(QVariantList& qvlLinks, CdmObject* pCdmObject)
{
    if (CHKPTR(pCdmObject))
    {
        QMap<QString, CdmValue*> qmValues;
        pCdmObject->GetValueMap(qmValues);

        QMap<QString, CdmValue*>::iterator qmIt = qmValues.begin();
        QMap<QString, CdmValue*>::iterator qmItEnd = qmValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmValue* pValue = qmIt.value();

            if (CHKPTR(pValue))
            {
                qvlLinks.append(generateLinkMap(qmIt.key(), pValue->GetUri()));
            }
        }
    }
}

void CsraHandlerObject::addMethodLinks(QVariantList& qvlLinks, CsaObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        QList<CsaFunction*> qlFunctions = p_pObject->getFunctions();
        for (int iPos = 0; iPos < qlFunctions.count(); ++iPos)
        {
            CsaFunction* pFunction = qlFunctions[iPos];

            if (CHKPTR(pFunction))
            {
                CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (pFunction->getElement());

                if (CHKPTR(pMethod) &&
                        pMethod->GetAccess() ==  eDmMemberAccessPublic &&
                        pMethod->GetRights().HasCurrentUserWriteAccess())
                {
                    if (CHKPTR(pFunction))
                    {
                        qvlLinks.append(generateLinkMap(pMethod->GetMethodName(), pFunction->getUri()));
                    }
                }
            }
        }
    }
}

void CsraHandlerObject::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    CsaObject* pObject = dynamic_cast<CsaObject*> (p_pElement);
    if (CHKPTR(pObject) && pObject->hasCurrentUserReadAccess())
    {
        CdmObject* pCdmObject = pObject->getInternals();

        if (CHKPTR(pCdmObject))
        {
            QVariantMap qvmDetails;
            QVariantList qvlValueDetails;
            QVariantList qvlMethods;
            addValueDetailsLinks(qvlValueDetails, pCdmObject);

            if (qvlValueDetails.count() > 0)
            {
                qvmDetails.insert(WMS_VALUES, qvlValueDetails);
            }

            addMethodLinks(qvlMethods, pObject);

            if (qvlMethods.count() > 0)
            {
                qvmDetails.insert(WMS_METHODS, qvlMethods);
            }

            if (qvmDetails.count() > 0)
            {
                qvlLinks.append(qvmDetails);
            }
        }

        qvlLinks.append(generateLinkMap(WMS_GRAPH, dynamic_cast<CsaObject*> (pObject), WMS_GRAPH "/{?excludedKeynames,maxDepth,maxObjects,followNonOwnerObjectlist,followNonOwnerObject}"));
        qvlLinks.append(generateLinkMap(WMS_CONTAINER, dynamic_cast<CsaObjectContainer*> (pObject->getContainer())));
        qvlLinks.append(generateLinkMap(WMS_CLASS, pCdmObject->GetClass()));
    }

    qvm.insert(WMS_LINKS, qvlLinks);
}
