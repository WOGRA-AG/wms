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
   qint64 lObjectId     =  m_rpData->GetValue("ObjectId").toInt();
   qint64 lObjectListId =  m_rpData->GetValue("ObjectListId").toInt();
   qint64 lDbId         =  m_rpData->GetValue("DatabaseId").toInt();
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

