#include "CwiCommandUpdateClass.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"


CwiCommandUpdateClass::CwiCommandUpdateClass(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandUpdateClass::~CwiCommandUpdateClass()
{

}

void CwiCommandUpdateClass::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    QVariantMap qvHash =  m_rpData->GetValue("Class").toMap();
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       long iDbId = qvHash["DatabaseId"].toInt();
       CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(iDbId);

       if (pCdmClassManager)
       {
          long iId = qvHash["Id"].toInt();
          CdmClass* pCdmClass = pCdmClassManager->FindClassById(iId);

          if (pCdmClass)
          {
             pCdmClass->SetVariant(qvHash);
          }
          else
          {
             QString qstrKeyname = qvHash["Keyname"].toString();
             pCdmClass = pCdmClassManager->CreateClass(qstrKeyname);
             pCdmClass->SetVariant(qvHash);
          }

          int iSuccess = pCdmClass->Commit();

          if (iSuccess > 0)
          {
             pResult = GetResultContainer(m_rpData,
                                          1,
                                          "Class updated",
                                          eWmscomMessageServerityInfo);
             pResult->AddValue("Class", pCdmClass->GetVariant());
          }
          else
          {
             pResult = GetResultContainer(m_rpData,
                                          -5000,
                                          "Error occured while updateing class",
                                          eWmscomMessageServerityError);
          }
       }
       else
       {
          pResult = GetResultContainer(m_rpData,
                                       -5000,
                                       "No Data Access configured",
                                       eWmscomMessageServerityFatal);
       }
    }
    else
    {
       pResult = GetResultContainer(m_rpData,
                                    -5000,
                                    "No session found",
                                    eWmscomMessageServerityFatal);
    }
}

