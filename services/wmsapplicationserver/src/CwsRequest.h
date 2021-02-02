#ifndef CWSREQUEST_H
#define CWSREQUEST_H

// Sytem and Qt Includes

// Basetools Includes
#include "CwmsDataExchange.h"

// own Includes

class CwsRequest : public CwmsDataExchange
{
public:
    CwsRequest();
    CwsRequest(QString p_qstrSource, CwmsDataExchangeConfigurator *p_pConfigurator);
    QString GetCommand();
    virtual ~CwsRequest();
};

#endif // CWSREQUEST_H
