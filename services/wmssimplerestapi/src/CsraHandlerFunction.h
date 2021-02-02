#ifndef CSRAHANDLERFUNCTION_H
#define CSRAHANDLERFUNCTION_H

#include "CsraHandlerBase.h"

class CsraHandlerFunction : public CsraHandlerBase
{
public:
    CsraHandlerFunction();

    // CsraHandlerBase interface
public:
    virtual QString getType();
    virtual QVariant handleGetRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual QVariant handlePutRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);
    virtual QVariant handleDeleteRequest(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse);

    // CsraHandlerBase interface
protected:
    virtual void addLinksToVariant(CsaLocatedElement *p_pElement, QVariantMap &qvm);
private:
    void execute(CsaLocatedElement *p_pElement, CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse, QVariantMap &qvm);
};

#endif // CSRAHANDLERFUNCTION_H
