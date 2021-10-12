#include "CdmLogging.h"

#include "CftlInterface.h"
#include "CftlContainerTableBase.h"



CftlContainerTableBase::CftlContainerTableBase(CftlDialect* p_ppDialect)
: m_rpDialect(p_ppDialect)
{

}

CftlContainerTableBase::~CftlContainerTableBase()
{

}

bool CftlContainerTableBase::CheckValid()
{
    return (IsValid() && m_rpDialect != nullptr);
}

CftlDialect *CftlContainerTableBase::GetDialect()
{
    return m_rpDialect;
}

qint64 CftlContainerTableBase::Execute(CftlInterface *p_pInterface)
{
   qint64 lRet = CdmLogging::eDmOk;

    if (CHKPTR(p_pInterface))
    {
        QStringList qstrlSqls = GenerateSqls();

        for (int iPos = 0; iPos < qstrlSqls.count() && SUCCESSFULL(lRet); ++iPos)
        {
            QString qstrSql = qstrlSqls[iPos];

            if (!qstrSql.isEmpty())
            {
               lRet =  p_pInterface->ExecuteQuery(qstrSql, m_qsqlQuery);
            }
        }
    }

    return lRet;
}

QSqlQuery &CftlContainerTableBase::GetQuery()
{
    return m_qsqlQuery;
}
