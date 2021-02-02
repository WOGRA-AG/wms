#ifndef CSRAHANDLERUSERGROUP_H
#define CSRAHANDLERUSERGROUP_H

#include "CsraHandlerBase.h"

class CsraHandlerUserGroup : public CsraHandlerBase
{
public:
    CsraHandlerUserGroup();

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

#endif // CSRAHANDLERUSERGROUP_H
