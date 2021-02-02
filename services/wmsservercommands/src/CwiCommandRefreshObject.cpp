#include "CwiCommandRefreshObject.h"
#include "CdmObject.h"
#include "CwiObject.h"


CwiCommandRefreshObject::CwiCommandRefreshObject(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandRefreshObject::~CwiCommandRefreshObject()
{

}

void CwiCommandRefreshObject::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    long lObjectId     =  m_rpData->GetValue("ObjectId").toInt();
    long lObjectListId =  m_rpData->GetValue("ObjectListId").toInt();
    long lDbId         =  m_rpData->GetValue("DatabaseId").toInt();
    CdmObject* pCdmObject = CwiObject::GetObject(lDbId, lObjectListId, lObjectId);

    if (pCdmObject)
    {
       pCdmObject->Refresh();
       pResult = GetResultContainer(m_rpData,
                                    1,
                                    "Refresh executed!",
                                    eWmscomMessageServerityInfo);
       pResult->AddValue("Object", pCdmObject->GetVariant());
    }
    else
    {
       pResult = GetResultContainer(m_rpData,
                                     -5000,
                                     "Object not found!",
                                     eWmscomMessageServerityError);
    }
}

