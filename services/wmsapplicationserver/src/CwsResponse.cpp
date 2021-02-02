#include "CwsResponse.h"

#define MESSAGE "Message"

CwsResponse::CwsResponse()
    : CwmsDataExchange(nullptr),
      m_eStatusCode(eWmsHttpStatusCodeOk)
{
}

CwsResponse::CwsResponse(CwmsDataExchangeConfigurator* p_pConfigurator)
: CwmsDataExchange(p_pConfigurator),
  m_eStatusCode(eWmsHttpStatusCodeOk)
{
}

CwsResponse::~CwsResponse()
{
}


void CwsResponse::AddError(QString p_qstrError)
{
    m_qstrlErrors.append(p_qstrError);
}

QString CwsResponse::GetErrorString()
{
    return m_qstrlErrors.join("\n");
}

void CwsResponse::SetStatusCode(EwmsHttpStatusCode p_eStatusCode)
{
    m_eStatusCode = p_eStatusCode;
}

void CwsResponse::SetMessage(QString p_qstrMessage)
{
    SetValue(MESSAGE, p_qstrMessage);
}

EwmsHttpStatusCode CwsResponse::GetStatusCode()
{
    return m_eStatusCode;
}

