#include "CdmScheme.h"
#include "CwiCommandUpdateDatabase.h"

CwiCommandUpdateDatabase::CwiCommandUpdateDatabase(CwmscomData* p_pData, CdmScheme* p_pDatabase)
    :m_rpData(p_pData),
     m_rpDatabase(p_pDatabase)
{

}

CwiCommandUpdateDatabase::~CwiCommandUpdateDatabase()
{

}

void CwiCommandUpdateDatabase::Execute()
{
    if (m_rpData->HasValue("Version"))
    {
       m_rpDatabase->SetVersion(m_rpData->GetValue("Version").toInt());
       GetResultContainer(m_rpData,
                          1,
                          "Database version updated!",
                          eWmscomMessageServerityInfo);
    }
    else
    {
       GetResultContainer(m_rpData,
                          0,
                          "Nothing done!",
                          eWmscomMessageServerityInfo);
    }
}



