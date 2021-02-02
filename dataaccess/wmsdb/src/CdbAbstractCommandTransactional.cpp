#include "CdbAbstractCommandTransactional.h"

CdbAbstractCommandTransactional::CdbAbstractCommandTransactional(CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand (p_pDataAccess)
{

}

CdbAbstractCommandTransactional::~CdbAbstractCommandTransactional()
{

}

int CdbAbstractCommandTransactional::Run()
{
    int iRet = Validate();

    if (SUCCESSFULL(iRet))
    {
        if (NeedsActiveSession())
        {
            iRet = SessionCheck();
        }

        if (SUCCESSFULL(iRet))
        {
            CdbInterface* pInterface = GetInterface();

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
