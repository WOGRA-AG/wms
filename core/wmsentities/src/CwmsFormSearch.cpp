// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormSearch.h"

// Forwards

// Enumerations

CwmsFormSearch::CwmsFormSearch()
 : CwmsFormContainer()
{
}

CwmsFormSearch::CwmsFormSearch(CdmObject* p_pCdmObject)
 : CwmsFormContainer(p_pCdmObject)
{
}

CwmsFormSearch::~CwmsFormSearch()
{
}

QList<QString> CwmsFormSearch::GetDisplayMembers()
{
   return GetStringList("Display_Members");
}

CdmObjectContainer* CwmsFormSearch::GetSearchList()
{
   return GetContainerRefValue("SearchList");
}

void CwmsFormSearch::SetSearchList(CdmObjectContainer* p_pCdmOLValue)
{
   SetContainerRefValue("SearchList", p_pCdmOLValue);
}

QList<QString> CwmsFormSearch::GetSearchMembers()
{
   return GetStringList("Search_Members");
}


/** +-=---------------------------------------------------------Mo 17. Sep 18:47:45 2012----------*
 * @method  CwmsFormSearch::SetSearchMembers                 // public                            *
 * @return  void                                             //                                   *
 * @param   QList<QString> p_qstrlMembers              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:47:45 2012----------*/
void CwmsFormSearch::SetSearchMembers(QList<QString> p_qstrlMembers)
{
   SetStringList("Search_Members", p_qstrlMembers);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:47:41 2012----------*
 * @method  CwmsFormSearch::SetDisplayMembers                // public                            *
 * @return  void                                             //                                   *
 * @param   QList<QString> p_qstrlMembers              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:47:41 2012----------*/
void CwmsFormSearch::SetDisplayMembers(QList<QString> p_qstrlMembers)
{
   SetStringList("Display_Members", p_qstrlMembers);
}

CwmsFormSearch CwmsFormSearch::Create(CdmObjectContainer* p_pContainer)
{
   CwmsFormSearch cCwmsFormSearch;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsFormSearch.SetObject(pCdmObject);
   }

   return cCwmsFormSearch;
}
bool CwmsFormSearch::Delete(CwmsFormSearch cCwmsFormSearch)
{
   bool bSuccess = false;
   if (cCwmsFormSearch.IsValid())
   {
      cCwmsFormSearch.SetDeleted();
      cCwmsFormSearch.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
