#ifndef CSRARESTREQUESTHANDLER_H
#define CSRARESTREQUESTHANDLER_H

// WMSRequestManager Incldues
#include "CwmscomResource.h"

// Forwards
class CwmscomController;
class CdmLocatedElement;
class CsraHandlerBase;
class CsaLocatedElement;

class CsraRestRequestHandler : public CwmscomResourceBase
{
public:
    CsraRestRequestHandler(CwmscomController* p_pController);

    // IwmsWebService interface
public:
    virtual void execute(CwmscomData *p_pData);
    virtual void executeDescription(CwmscomData *p_pData);
    virtual QVariantMap getConfiguration();

    // CwmscomResourceBase interface
protected:
    virtual void executeP(CwmscomData *p_pData);

public:
    virtual QString GetResourceDescription();

    // IwmsWebService interface
public:
    virtual QString getVersion();
private:
    QString GetContextPathToRequestHandler();
    bool Authenticate(CwsHttpRequest *p_pRequest);
    QString ParseWmsUri(QString p_qstrContextPath);
    void execute(CwmscomData *p_pData, QString qstrWmsUri);
    CsraHandlerBase* getHandler(CdmLocatedElement* p_pElement);
    CsraHandlerBase *getHandler(CsaLocatedElement *p_pElement);
protected:
    virtual void ExecuteGet(CwmscomData *p_pData);
};

#endif // CSRARESTREQUESTHANDLER_H
