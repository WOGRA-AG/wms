#ifndef CSRAHANDLERCONTAINER_H
#define CSRAHANDLERCONTAINER_H

#include "CsraHandlerBase.h"

class CsraHandlerContainer : public CsraHandlerBase
{
private:
    bool m_bAddLinks;
public:
    CsraHandlerContainer();

    // CsraHandlerBase interface
public:
    virtual QString getType();
    virtual QVariant handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual QVariant handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual QVariant handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual void addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm);
    // CsraHandlerBase interface
protected:

private:
    void listAll(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap &qvm);
    void listFromTo(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, int p_iFrom, int p_iTo, QVariantMap &qvm);
    void createObject(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap &qvm);
    void deleteAllObjects(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap &qvm);
    void listObjects(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap &qvm);
    void addLinksToVariant(CsaLocatedElement *p_pElement, int p_iFrom, int p_iTo, QVariantMap &qvm);
};

#endif // CSRAHANDLERCONTAINER_H
