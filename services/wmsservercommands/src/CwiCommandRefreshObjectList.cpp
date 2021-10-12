#include "CwiCommandRefreshObjectList.h"

/*
    //TODO funktioniert nicht, da getEmptyObjectList nicht aufgerufen werden kann
    //CwiCommandRefreshObjectList command(p_pData, p_lDbId, p_ObjectListId);
    //command.Execute();
*/


CwiCommandRefreshObjectList::CwiCommandRefreshObjectList(CwmscomData *p_pData,qint64 p_lDbId,qint64 p_ObjectListId)
    :m_rpData(p_pData),
     m_rlDbId(p_lDbId),
     m_rObjectListId(p_ObjectListId)
{

}

CwiCommandRefreshObjectList::~CwiCommandRefreshObjectList()
{

}

void CwiCommandRefreshObjectList::Execute()
{
/*    CwmscomDataResult* pResult = nullptr;
    CdmObjectContainer* pContainer = GetEmptyObjectList(p_lDbId, p_ObjectListId);

    if (pContainer)
    {
       CdmContainerManager* pManager = pContainer->GetContainerManager();

       if (CHKPTR(pManager))
       {
          pManager->ReloadContainerComplete(pContainer);
          pResult = GetResultContainer(p_pData,
                                       1,
                                       "Refresh executed!",
                                       eWmscomMessageServerityInfo);

          pResult->AddValue("ObjectList", pContainer->GetVariant());
       }
    }
    else
    {
       pResult = GetResultContainer(p_pData,
                                    -5000,
                                    "Objectlist not found!",
                                    eWmscomMessageServerityError);
    }*/

}

