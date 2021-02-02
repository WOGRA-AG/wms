// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormStandardObjectList.h"

// Forwards

// Enumerations

CwmsFormStandardContainer::CwmsFormStandardContainer()
 : CwmsFormContainer()
{
}

CwmsFormStandardContainer::CwmsFormStandardContainer(CdmObject* p_pCdmObject)
 : CwmsFormContainer(p_pCdmObject)
{
}

CwmsFormStandardContainer::~CwmsFormStandardContainer()
{
}

QLinkedList<QString> CwmsFormStandardContainer::GetDisplayMembers()
{
   return GetStringList("Display_Members");
}

QLinkedList<QString> CwmsFormStandardContainer::GetSearchMembers()
{
   return GetStringList("Search_Members");
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:18:57 2012----------*
 * @method  CwmsFormStandardObjectList::SetSearchMembers     // public                            *
 * @return  void                                             //                                   *
 * @param   QLinkedList<QString> p_qstrlMembers              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:18:57 2012----------*/
void CwmsFormStandardContainer::SetSearchMembers(QLinkedList<QString> p_qstrlMembers)
{

   SetStringList("Search_Members", p_qstrlMembers);
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:19:07 2012----------*
 * @method  CwmsFormStandardObjectList::SetDisplayMembers    // public                            *
 * @return  void                                             //                                   *
 * @param   QLinkedList<QString> p_qstrlMembers              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:19:07 2012----------*/
void CwmsFormStandardContainer::SetDisplayMembers(QLinkedList<QString> p_qstrlMembers)
{
   SetStringList("Display_Members", p_qstrlMembers);
}

CdmObject* CwmsFormStandardContainer::GetView()
{
   return GetObjectRefValue("View");
}

void CwmsFormStandardContainer::SetView(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("View", p_pCdmValue);
}

CwmsFormStandardContainer CwmsFormStandardContainer::Create(CdmObjectContainer* p_pContainer)
{
   CwmsFormStandardContainer cCwmsFormStandardObjectList;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsFormStandardObjectList.SetObject(pCdmObject);
   }

   return cCwmsFormStandardObjectList;
}
bool CwmsFormStandardContainer::Delete(CwmsFormStandardContainer cCwmsFormStandardObjectList)
{
   bool bSuccess = false;
   if (cCwmsFormStandardObjectList.IsValid())
   {
      cCwmsFormStandardObjectList.SetDeleted();
      cCwmsFormStandardObjectList.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
