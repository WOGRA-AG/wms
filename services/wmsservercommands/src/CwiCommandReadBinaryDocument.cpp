#include "CwiCommandReadBinaryDocument.h"
#include "CdmValueBinaryDocument.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"


CwiCommandReadBinaryDocument::CwiCommandReadBinaryDocument(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandReadBinaryDocument::~CwiCommandReadBinaryDocument()
{

}

void CwiCommandReadBinaryDocument::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
        QVariantMap qvBinDoc = m_rpData->GetValue("BinDoc").toMap();

        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
        if (pCdmManager)
        {
            CdmValueBinaryDocument* pCdmBinDoc = nullptr;
            bool pCdmBinDocNew = false;
            QString pUri = qvBinDoc["Uri"].toString();

            if(!pUri.isEmpty())
            {
                CdmLocatedElement* pLocatedElement = pCdmManager->GetUriObject(pUri);
                try
                {
                    pCdmBinDoc = dynamic_cast<CdmValueBinaryDocument*>(pLocatedElement);
                } catch(...){
                    ERR("MemberValue is no binary document");
                }
            }

            if(!pCdmBinDoc){
                pCdmBinDoc = new CdmValueBinaryDocument(qvBinDoc, nullptr);
                pCdmBinDocNew = true;
            }


            pResult = GetResultContainer(m_rpData,
                                         1,
                                         "Binary Doc loaded",
                                         eWmscomMessageServerityInfo);

            pResult->AddValue("BinaryDocument", pCdmBinDoc->GetVariant());
            pResult->AddValue("Filename", pCdmBinDoc->GetFilename());
            pResult->AddValue("Filetype", pCdmBinDoc->GetFileType());


            if(pCdmBinDocNew){
                delete pCdmBinDoc;
            }
        }
        else
        {
            GetResultContainer(m_rpData,
                               -5000,
                               "No Session found!",
                               eWmscomMessageServerityFatal);
        }
    }
}

