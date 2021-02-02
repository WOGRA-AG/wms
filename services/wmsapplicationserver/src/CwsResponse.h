#ifndef CWSRESPONSE_H
#define CWSRESPONSE_H

// System and Qt Includes
#include "QStringList"

// Basetools Includes
#include "CwmsHttpService.h"
#include "CwmsDataExchange.h"

class CwsResponse : public CwmsDataExchange
{
private:
    QStringList m_qstrlErrors;
    EwmsHttpStatusCode m_eStatusCode;

public:
    CwsResponse(CwmsDataExchangeConfigurator *p_pConfigurator);
    CwsResponse();
    virtual ~CwsResponse();
    void AddError(QString p_qstrError);
    QString GetErrorString();
    void SetStatusCode(EwmsHttpStatusCode p_eStatusCode);
    void SetMessage(QString p_qstrMessage);
    EwmsHttpStatusCode GetStatusCode();
};

#endif // CWSRESPONSE_H
