#ifndef CSRAHANDLEROBJECT_H
#define CSRAHANDLEROBJECT_H

#include "CsraHandlerBase.h"

class CsraHandlerObject : public CsraHandlerBase
{
public:
    CsraHandlerObject();

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
    void addValueDetailsLinks(QVariantList& qvlLinks, CdmObject* pCdmObject);
    void addMethodLinks(QVariantList& qvlLinks, CsaObject* p_pObject);
};

#endif // CSRAHANDLEROBJECT_H
