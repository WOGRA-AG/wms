#ifndef CSRAHANDLERUSER_H
#define CSRAHANDLERUSER_H
#include "CsraHandlerBase.h"

class CsraHandlerUser : public CsraHandlerBase
{
public:
    CsraHandlerUser();

    // CsraHandlerBase interface
public:
    virtual QString getType();
    virtual QVariant handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual QVariant handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual QVariant handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);

    // CsraHandlerBase interface
protected:
    virtual void addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm);
};

#endif // CSRAHANDLERUSER_H
