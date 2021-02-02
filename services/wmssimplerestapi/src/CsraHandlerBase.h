#ifndef CSRAHANDLERBASE_H
#define CSRAHANDLERBASE_H

// System and Qt Incldues
#include <QVariant>
#include <QString>

// WMS Commons Includes
#include "CwsHttpRequest.h"
#include "CwsHttpResponse.h"

// WMS Core Includes
#include "CsaModelElement.h"

// Own Includes
#include "CwmscomDataResult.h"

class CsaLocatedElement;
class CdmLocatedElement;
class CwmscomData;



class CsraHandlerBase
{
public:
    CsraHandlerBase();
    virtual ~CsraHandlerBase();
    virtual QString getType() = 0;
    virtual QVariant handleGetRequest(CsaLocatedElement* p_pElement, CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse) = 0;
    virtual QVariant handlePutRequest(CsaLocatedElement* p_pElement, CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse) = 0;
    virtual QVariant handleDeleteRequest(CsaLocatedElement* p_pElement, CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse) = 0;
    void handleRequest(CwmscomData *p_pData, CdmLocatedElement* p_pElement);
    CwmscomDataResult *GetResultContainer(CwmscomData *p_pData, int p_iReturnCode, QString p_qstrMessage, EwmscomMessageServerity p_eSeverity);
    void handleRequest(CwmscomData *p_pData, CsaLocatedElement *p_pElement);
protected:
    QString parseCommandFromUri(CsaLocatedElement *p_pElement, QString p_qstrUri);
    QVariant generateLinkMap(QString qstrLinkName, QString qstrLink);
    QVariant generateLinkMap(QString qstrLinkName, const CdmLocatedElement *p_pElement, QString p_qstrLink);
    QVariant generateLinkRestSection(CsaLocatedElement *p_pElement);
    bool isSessionUserAdmin();
    QVariant generateLinkMap(QString qstrLinkName, const CdmLocatedElement *p_pElement);
    virtual void addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap& qvm) = 0;
    void addMainRestLinks(CsaModelElement *p_pElement, QVariantList &p_rqVariantList);

    QVariant generateLinkMap(QString qstrLinkName, const CsaLocatedElement *p_pElement, QString p_qstrLink);
    QVariant handleGetCommonCommandsRequest(CsaLocatedElement* p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, const QString &p_qstrCommand);
    QVariant generateLinkMap(QString qstrLinkName, const CsaLocatedElement *p_pElement);
    bool parseBooleanPathVariable(CwsHttpRequest *p_pRequest, QString p_qstrPathVariableName, bool p_bDefaultValue);
    QStringList parseStringListPathVariable(CwsHttpRequest *p_pRequest, QString p_qstrPathVariableName);
    int parseIntegerPathVariable(CwsHttpRequest *p_pRequest, QString p_qstrPathVariableName, int p_iDefaultValue);
    void temporaryRedirect(CwsHttpResponse *p_pResponse, QString uri);
private:
    QVariant handleRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    void setHostSettingsIfUndefined(CwsHttpRequest *p_pRequest);
};

#endif // CSRAHANDLERBASE_H
