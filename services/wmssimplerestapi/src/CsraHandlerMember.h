#ifndef CSRAHANDLERMEMBER_H
#define CSRAHANDLERMEMBER_H

#include "CsraHandlerBase.h"

class CsraHandlerMember : public CsraHandlerBase
{
public:
    CsraHandlerMember();

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

#endif // CSRAHANDLERMEMBER_H
