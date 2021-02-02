#include "CdmScheme.h"
#include "CwiCommandAddLanguage.h"

CwiCommandAddLanguage::CwiCommandAddLanguage(CwmscomData *p_pData, CdmScheme* p_pDatabase)
    :m_rpData(p_pData),
     m_rpDatabase(p_pDatabase)
{

}

CwiCommandAddLanguage::~CwiCommandAddLanguage()
{

}

void CwiCommandAddLanguage::Execute()
{
    if (m_rpDatabase && m_rpData)
    {
        QString qstrLanguage = m_rpData->GetValue("LanguageName").toString();
       m_rpDatabase->AddLanguage(qstrLanguage);
       GetResultContainer(m_rpData,
                          1,
                          "Language added.",
                          eWmscomMessageServerityInfo);
    }
    else
    {
       GetResultContainer(m_rpData,
                          -5000,
                          "Database not found!",
                          eWmscomMessageServerityFatal);
    }
}

