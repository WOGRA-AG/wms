#include "CwsRequest.h"

CwsRequest::CwsRequest()
: CwmsDataExchange(nullptr)
{
}

CwsRequest::CwsRequest(QString p_qstrSource, CwmsDataExchangeConfigurator* p_pConfigurator)
: CwmsDataExchange(p_qstrSource, p_pConfigurator)
{
}

CwsRequest::~CwsRequest()
{
}

QString CwsRequest::GetCommand()
{
   return m_qmMembers.value("Command").toString();
}
