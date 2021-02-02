#include "CwiCommandGetLanguages.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"


CwiCommandGetLanguages::CwiCommandGetLanguages(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetLanguages::~CwiCommandGetLanguages()
{

}

void CwiCommandGetLanguages::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    if(pCdmManager)
    {
        int iDatabaseId = m_rpData->GetValue("DatabaseId").toInt();
        CdmScheme* pScheme = pCdmManager->FindSchemeById(iDatabaseId);
        if(pScheme)
        {
            QMap<int, QString> mLanguageMap = pScheme->GetLanguageMap();
            QVariantMap qVariantMap;

            QMap<int,QString>::iterator i;
            for(i = mLanguageMap.begin(); i != mLanguageMap.end(); ++i)
            {
                int iKey = i.key();
                QVariant qVar = QVariant(iKey);
                qVariantMap.insert(i.value(),qVar);
            }
            pResult = GetResultContainer(m_rpData,
                                         1,
                                         "SupportedLanguages",
                                         eWmscomMessageServerityInfo);
            pResult->AddValue("Results", qVariantMap);
        }
        else
        {
            GetResultContainer(m_rpData,
                               -5000,
                               "Scheme not found",
                               eWmscomMessageServerityError);
        }
    }
    else
    {
        GetResultContainer(m_rpData,
                           -5000,
                           "Invalid Session Manager bnot found",
                           eWmscomMessageServerityFatal);
    }
}

