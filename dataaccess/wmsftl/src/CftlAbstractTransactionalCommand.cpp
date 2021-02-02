#include "CftlInterface.h"
#include "CftlAbstractTransactionalCommand.h"

CftlAbstractTransactionalCommand::CftlAbstractTransactionalCommand(CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand (p_pDataAccess)
{

}

CftlAbstractTransactionalCommand::~CftlAbstractTransactionalCommand()
{

}

int CftlAbstractTransactionalCommand::Run()
{
    int iRet = Validate();

    if (SUCCESSFULL(iRet))
    {
        if (NeedsSessionCheck())
        {
            iRet = SessionCheck();
        }

        if (SUCCESSFULL(iRet))
        {
            CftlInterface* pInterface = GetInterface();

            if (CHKPTR(pInterface))
            {
                iRet = pInterface->BeginTransaction();

                if (SUCCESSFULL(iRet))
                {
                    iRet = Execute();

                    if (SUCCESSFULL(iRet))
                    {
                        pInterface->Commit();
                    }
                    else
                    {
                        pInterface->Rollback();
                    }
                }
            }
        }
    }

    return iRet;
}
