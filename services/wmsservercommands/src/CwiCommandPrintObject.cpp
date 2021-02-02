#include "CwiCommandPrintObject.h"
#include "CdmDataProvider.h"
#include "CwmsPluginManager.h"
#include "CwmsContext.h"
#include "CwmsReportManager.h"

CwiCommandPrintObject::CwiCommandPrintObject(CwmscomData *m_rpData)
    :m_rpData(m_rpData)
{

}

CwiCommandPrintObject::~CwiCommandPrintObject()
{

}

void CwiCommandPrintObject::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    long lObjectListId = m_rpData->GetValue("ObjectListId").toInt();
    long lObjectId  = m_rpData->GetValue("ObjectId").toInt();
    QString qstrTemplateName = m_rpData->GetValue("Template").toString();
    QByteArray qbaPdfOutput;



    CwmsReportManager cReportManager;
    CwmsPluginManager* pPluginManager = CwmsContext::GetContext()->GetPluginManager();

    if (pPluginManager->HasPrintingPlugin())
    {
        if (lObjectId <= 0)
        {
           if (qstrTemplateName.isEmpty())
           {
              qbaPdfOutput = cReportManager.GetPdf(lObjectListId);
           }
           else
           {
              qbaPdfOutput = cReportManager.GetPdf(lObjectListId, qstrTemplateName);
           }
        }
        else
        {
           if (qstrTemplateName.isEmpty())
           {
              qbaPdfOutput = cReportManager.GetPdf(lObjectListId, lObjectId);
           }
           else
           {
              qbaPdfOutput = cReportManager.GetPdf(lObjectListId, lObjectId, qstrTemplateName);
           }
        }

        if (!qbaPdfOutput.isEmpty())
        {
           pResult = GetResultContainer(m_rpData,
                                        1,
                                        "Printing successfull!",
                                        eWmscomMessageServerityInfo);
           pResult->AddValue("Content", qbaPdfOutput.toBase64());
           pResult->AddValue("ContentType", "PDF");
        }
        else
        {
           pResult = GetResultContainer(m_rpData,
                                        -5000,
                                        "Printing failed!",
                                        eWmscomMessageServerityError);
        }
    }
    else
    {
       pResult = GetResultContainer(m_rpData,
                                    -5000,
                                    "Printing Plugin is missing on server!",
                                    eWmscomMessageServerityError);
    }
}

