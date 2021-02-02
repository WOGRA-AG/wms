#include "CwmscomDataResult.h"
#include "CwiAbstractCommand.h"

CwiAbstractCommand::CwiAbstractCommand()
{
}

CwiAbstractCommand::~CwiAbstractCommand()
{

}

CwmscomDataResult* CwiAbstractCommand::GetResultContainer(CwmscomData* p_pData,
                                                           int p_iReturnCode,
                                                           QString p_qstrMessage,
                                                           EwmscomMessageServerity p_eSeverity)
{

   CwmscomDataResult* pResult = nullptr;

   if (p_pData)
   {
      pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage(p_qstrMessage);
      pResult->SetMessageCode(p_iReturnCode);
      pResult->SetSeverity(p_eSeverity);
   }

   return pResult;
}
