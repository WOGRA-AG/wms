#include "CwiCommandCreateObject.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"



CwiCommandCreateObject::CwiCommandCreateObject(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandCreateObject::~CwiCommandCreateObject()
{

}

void CwiCommandCreateObject::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
       CdmObject* pObject = nullptr;
       QString qstrKeyname = m_rpData->GetValue("Keyname").toString();
       CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pManager))
       {
          CdmObjectContainer* pObjectList = pManager->GetObjectContainerEmpty(qstrKeyname);

          if (CHKPTR(pObjectList))
          {
             pObject = pObjectList->CreateNewObject();

             if (pObject && pObject->Commit() > 0)
             {
                pResult = GetResultContainer(m_rpData,
                                             1,
                                             "Object created!",
                                             eWmscomMessageServerityInfo);

                pResult->AddValue("Object", pObject->GetVariant());
             }
             else
             {
                pResult = GetResultContainer(m_rpData,
                                              -5000,
                                              "Object creation failed! (DB Error)",
                                              eWmscomMessageServerityError);
             }
          }
          else
          {
             pResult = GetResultContainer(m_rpData,
                                           -5000,
                                           "objectlist for Object creation not found!",
                                           eWmscomMessageServerityFatal);
          }
       }
       else
       {
          pResult = GetResultContainer(m_rpData,
             -5000,
             "Invalid session object creation not possible!",
             eWmscomMessageServerityFatal);
       }
    }
}

