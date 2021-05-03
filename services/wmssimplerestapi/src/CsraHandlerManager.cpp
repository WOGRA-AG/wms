#include "wmsdefines.h"

// WMS Core Includes
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"

// Own Includes
#include "CsraHandlerManager.h"

CsraHandlerManager::CsraHandlerManager()
{

}


QString CsraHandlerManager::getType()
{
return WMS_URI_DATAPROVIDER;
}

QVariant CsraHandlerManager::handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    QVariantMap qvm;
    QString qstrCommand = parseCommandFromUri(p_pElement, p_pRequest->GetContextPath());

    if (qstrCommand.isEmpty())
    {
        qvm = p_pElement->getDetailedVariant().toMap();
    }
    else
    {
        if (qstrCommand == WMS_URI_FIND_USER)
        {
            findUser(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else if (qstrCommand == WMS_URI_FIND_USERGROUP)
        {
            findUserGroup(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else if (qstrCommand == WMS_URI_GET_SCHEMELIST)
        {
            getSchemeList(p_pElement, p_pRequest, p_pResponse, qvm);
        }
        else
        {
            qvm = handleGetCommonCommandsRequest(p_pElement, p_pRequest, p_pResponse, qstrCommand).toMap();
        }
    }

    addLinksToVariant(p_pElement, qvm);
    return qvm;
}

void CsraHandlerManager::findUser(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    Q_UNUSED(p_pResponse);
    if (CHKPTR(p_pElement))
    {
        if (p_pRequest->HasPathVariable("name"))
        {
            QString qstrName = p_pRequest->GetPathVariable("name");
            CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pDataProvider))
            {
                CumUserManager* pUserManager = pDataProvider->GetUserManager();

                if (CHKPTR(pUserManager))
                {
                    QList<CumUser*> qllUsers = pUserManager->FindUsersUnmanaged(qstrName);
                    QVariantList qvlUsers;

                    QList<CumUser*>::iterator qllIt = qllUsers.begin();
                    QList<CumUser*>::iterator qllItEnd = qllUsers.end();

                    for (; qllIt != qllItEnd; ++qllIt)
                    {
                        CumUser* pUser = *qllIt;

                        if (CHKPTR(pUser))
                        {
                            qvlUsers.append(pUser->GetVariant());
                            DELPTR(pUser); // Must be deleted because the result won't be managed by UserManager
                        }
                    }

                    qvm.insert(WMS_RESULT, qvlUsers);
                }
            }
        }
    }
}

void CsraHandlerManager::findUserGroup(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    Q_UNUSED(p_pResponse);

    if (CHKPTR(p_pElement))
    {
        if (p_pRequest->HasPathVariable("name"))
        {
            QString qstrName = p_pRequest->GetPathVariable("name");
            CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pDataProvider))
            {
                CumUserManager* pUserManager = pDataProvider->GetUserManager();

                if (CHKPTR(pUserManager))
                {
                    QList<CumUserGroup*> qllUsers = pUserManager->FindUserGroupsByNameUnmanaged(qstrName);
                    QVariantList qvlUserGroupss;

                    QList<CumUserGroup*>::iterator qlIt = qllUsers.begin();
                    QList<CumUserGroup*>::iterator qlItEnd = qllUsers.end();

                    for(; qlIt != qlItEnd; ++qlIt)
                    {
                        CumUserGroup* pUserGroup = *qlIt;

                        if (CHKPTR(pUserGroup))
                        {
                            qvlUserGroupss.append(pUserGroup->GetVariant());
                            DELPTR(pUserGroup);
                        }
                    }

                    qvm.insert(WMS_RESULT, qvlUserGroupss);
                }
            }
        }
    }
}

void CsraHandlerManager::getSchemeList(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap& qvm)
{
    Q_UNUSED(p_pRequest);
    Q_UNUSED(p_pResponse);
    if (CHKPTR(p_pElement))
    {
        CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pDataProvider))
        {
            QVariantList qvlSchemes;
            QList<QString> qllSchemes;
            pDataProvider->GetSchemeList(qllSchemes);

            QList<QString>::iterator qllIt = qllSchemes.begin();
            QList<QString>::iterator qllItEnd = qllSchemes.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                QString qstrScheme = *qllIt;
                QString qstrUri = pDataProvider->CreateUriHost();
                qstrUri += "/" WMS_URI_SCHEME "/" + qstrScheme;
                qvlSchemes.append(generateLinkMap(qstrScheme, qstrUri));
            }

            qvm.insert(WMS_RESULT, qvlSchemes);
        }
    }
}

QVariant CsraHandlerManager::handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}

QVariant CsraHandlerManager::handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    Q_UNUSED(p_pElement);
    Q_UNUSED(p_pRequest);
    QVariantMap qvm;
    qvm.insert("success", "false");
    qvm.insert("error", "Not supported!");
    p_pResponse->SetStatusCode(eWmsHttpStatusCodeMethodNotAllowed);
    return qvm;
}


void CsraHandlerManager::addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm)
{
    QVariantList qvlLinks = generateLinkRestSection(p_pElement).toList();
    qvlLinks.append(generateLinkMap(WMS_FIND_USER, p_pElement, WMS_URI_FIND_USER "/{?name}"));
    qvlLinks.append(generateLinkMap(WMS_FIND_USERGROUP, p_pElement, WMS_URI_FIND_USERGROUP "/{?name}"));
    qvlLinks.append(generateLinkMap(WMS_GET_SCHEMELIST, p_pElement, WMS_URI_GET_SCHEMELIST));
    qvm.insert(WMS_LINKS, qvlLinks);
}
