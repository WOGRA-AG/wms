/******************************************************************************
 ** WOGRA Middleware Server GUI Tools Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes



// own Includes
#include "CdmEnhancedQueryProxy.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CwmsSearchWindowDlg.h"
#include "CwmsObjectSelectionIf.h"



/** +-=---------------------------------------------------------So 23. Mai 10:55:30 2010----------*
 * @method  CwmsObjectSelectionIf::CwmsObjectSelectionIf     // private                           *
 * @return  void                                             //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 10:55:30 2010----------*/
CwmsObjectSelectionIf::CwmsObjectSelectionIf(QWidget* parent)
   : QDialog(parent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mo 23. Jan 22:31:53 2006----------*
 * @method  CwmsObjectSelectionIf::~CwmsObjectSelectionIf    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectSelectionIf                                         *
 *                                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 22:31:53 2006----------*/
CwmsObjectSelectionIf::~CwmsObjectSelectionIf(  )
{
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:28:42 2012-----------*
 * @method  CwmsObjectSelectionIf::SetProxy                  // public                            *
 * @return  void                                             //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCwmsProxy              //                                   *
 * @comment This method sets the proxy for the dialog.                                            *
 *----------------last changed: --------------------------------Mi 3. Okt 11:28:42 2012-----------*/
void CwmsObjectSelectionIf::SetProxy(CdmEnhancedQueryProxy* p_pCwmsProxy)
{
   m_cModel.SetProxy(p_pCwmsProxy);
}

/** +-=---------------------------------------------------------Fr 21. Dez 11:30:40 2012----------*
 * @method  CwmsObjectSelectionIf::SetWql                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrWql                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Dez 11:30:40 2012----------*/
bool CwmsObjectSelectionIf::SetWql(QString p_qstrWql)
{
   m_cModel.Execute(p_qstrWql);

   if (m_cModel.GetQuery()->GetResultCount() == 0)
   {
       return false;
   }

   m_pqlvObjects->setModel(&m_cModel);
   return true;
}

/** +-=---------------------------------------------------------Mo 23. Jan 22:33:13 2006----------*
 * @method  CwmsObjectSelectionIf::SetObjectList             // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 22:33:13 2006----------*/
void CwmsObjectSelectionIf::SetObjectList(CdmObjectContainer* p_pContainer)
{
   if(CHKPTR(p_pContainer))
   {
      m_cModel.SetContainer(p_pContainer);

      if (m_qstrDisplayMember.isEmpty())
      {
         const CdmClass* pCdmClass = p_pContainer->GetClass();

         if(pCdmClass)
         {
            QMap<long, CdmMember*> qmMembers;
            pCdmClass->GetMemberMap(qmMembers);

            QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
            QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

            if(pCdmClass->IsEventSourcingActive() || pCdmClass->IsEventClass())
            {
                for(; qmIt != qmItEnd; ++qmIt)
                {
                    CdmMember *pMember = (*qmIt);
                    if(pMember)
                    {
                        QString qstrKeyname = pMember->GetKeyname();
                        if(qstrKeyname == "Id")
                        {
                            CdmClassManager *pClassManager = pCdmClass->GetClassManager();
                            CdmMember *pReferencedClassMember = getReferencedClassMemberForEvent(pMember->GetClassReference(), pClassManager);
                            if(CHKPTR(pReferencedClassMember) &&
                                    pReferencedClassMember->GetValueType() != eDmValueBinaryDocument &&
                                    pReferencedClassMember->GetValueType() != eDmValueCharacterDocument &&
                                    pReferencedClassMember->GetValueType() != eDmValueObjectRef &&
                                    pReferencedClassMember->GetValueType() != eDmValueListDouble &&
                                    pReferencedClassMember->GetValueType() != eDmValueListInt &&
                                    pReferencedClassMember->GetValueType() != eDmValueListString &&
                                    pReferencedClassMember->GetValueType() != eDmValueDictIntDouble &&
                                    pReferencedClassMember->GetValueType() != eDmValueDictIntInt &&
                                    pReferencedClassMember->GetValueType() != eDmValueDictIntString &&
                                    pReferencedClassMember->GetValueType() != eDmValueDictStringDouble &&
                                    pReferencedClassMember->GetValueType() != eDmValueDictStringInt &&
                                    pReferencedClassMember->GetValueType() != eDmValueDictStringString &&
                                    pReferencedClassMember->GetValueType() != eDmValueListObjects &&
                                    pReferencedClassMember->GetValueType() != eDmValueObjectRef &&
                                    pReferencedClassMember->GetValueType() != eDmValueContainerRef &&
                                    pReferencedClassMember->GetValueType() != eDmValueFormula)
                            {
                                m_cModel.GetQuery()->AddResultElement(pReferencedClassMember->GetKeyname());
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                for(; qmIt != qmItEnd; ++qmIt)
                {
                   CdmMember* pCdmMember = qmIt.value();

                   if(CHKPTR(pCdmMember) &&
                      pCdmMember->GetValueType() != eDmValueBinaryDocument &&
                      pCdmMember->GetValueType() != eDmValueCharacterDocument &&
                      pCdmMember->GetValueType() != eDmValueObjectRef &&
                      pCdmMember->GetValueType() != eDmValueListDouble &&
                      pCdmMember->GetValueType() != eDmValueListInt &&
                      pCdmMember->GetValueType() != eDmValueListString &&
                      pCdmMember->GetValueType() != eDmValueDictIntDouble &&
                      pCdmMember->GetValueType() != eDmValueDictIntInt &&
                      pCdmMember->GetValueType() != eDmValueDictIntString &&
                      pCdmMember->GetValueType() != eDmValueDictStringDouble &&
                      pCdmMember->GetValueType() != eDmValueDictStringInt &&
                      pCdmMember->GetValueType() != eDmValueDictStringString &&
                      pCdmMember->GetValueType() != eDmValueListObjects &&
                      pCdmMember->GetValueType() != eDmValueObjectRef &&
                      pCdmMember->GetValueType() != eDmValueContainerRef &&
                       pCdmMember->GetValueType() != eDmValueFormula)
                   {
                      m_cModel.GetQuery()->AddResultElement(pCdmMember->GetKeyname());
                   }
                }
            }
         }
      }

      m_cModel.Execute();
      m_pqlvObjects->setModel(&m_cModel);
   }
}

CdmMember *CwmsObjectSelectionIf::getReferencedClassMemberForEvent(long lReferencedClassId, CdmClassManager *pClassManager)
{
    CdmMember *pMember = nullptr;

    CdmClass *pReferencedClass = pClassManager->FindClassById(lReferencedClassId);
    QMap<long, CdmMember*> qmMembers;
    pReferencedClass->GetMemberMap(qmMembers);

    QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
    QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();
    for(; qmIt != qmItEnd; ++qmIt)
    {
        pMember = (*qmIt);
        QString qstrKeyname = pMember->GetKeyname();
        if(qstrKeyname == "Id")
        {
            break;
        }
    }
    return pMember;
}


/** +-=---------------------------------------------------------Mo 23. Jan 22:32:28 2006----------*
 * @method  CwmsObjectSelectionIf::GetSelectedObject         // public                            *
 * @return  CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 22:32:28 2006----------*/
CdmObject* CwmsObjectSelectionIf::GetSelectedObject(  )
{
   return m_cModel.GetObject(m_pqlvObjects);
}

/** +-=---------------------------------------------------------Fr 1. Jun 10:53:38 2012-----------*
 * @method  CwmsObjectSelectionIf::GetSelectedObjectId       // public                            *
 * @return  long                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 1. Jun 10:53:38 2012-----------*/
long CwmsObjectSelectionIf::GetSelectedObjectId()
{
   long lRet = 0;

   CdmObject* pCdmObject = GetSelectedObject();

   if (pCdmObject)
   {
      lRet = pCdmObject->GetId();
   }

   return lRet;
}

/** +-=---------------------------------------------------------Di 4. Sep 15:32:40 2012-----------*
 * @method  CwmsObjectSelectionIf::SetDisplayMember          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 15:32:40 2012-----------*/
void CwmsObjectSelectionIf::SetDisplayMember(QString p_qstrMember)
{
   if (!p_qstrMember.isEmpty())
   {
      m_cModel.GetQuery()->AddResultElement(p_qstrMember);
      m_qstrDisplayMember = p_qstrMember;
   }
}

/** +-=---------------------------------------------------------Fr 21. Dez 11:33:30 2012----------*
 * @method  CwmsObjectSelectionIf::GetObject                 // public, static                    *
 * @return  CdmObject*                                       //                                   *
 * @param   QString p_qstrWql                                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment the static implementation for returning an object.                                    *
 *----------------last changed: --------------------------------Fr 21. Dez 11:33:30 2012----------*/
CdmObject* CwmsObjectSelectionIf::GetObject(QString p_qstrWql, QWidget* p_pqwParent)
{
   CdmObject* pCdmObject = nullptr;
   CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
   if (pCwmsSelection->SetWql(p_qstrWql)) // more than 0 object found for selection
   {
       if(pCwmsSelection->exec() == QDialog::Accepted)
       {
          pCdmObject = pCwmsSelection->GetSelectedObject();
       }
   }

   return pCdmObject;
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:34:31 2012-----------*
 * @method  CwmsObjectSelectionIf::GetObject                 // public, static                    *
 * @return  CdmObject*                                       //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCwmsProxy              //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @param   QString p_qstrDisplayMember = ""                 //                                   *
 * @comment the static implementation for returning an object.                                    *
 *----------------last changed: --------------------------------Mi 3. Okt 11:34:31 2012-----------*/
CdmObject* CwmsObjectSelectionIf::GetObject(CdmObjectContainer* p_pContainer,
                                            CdmEnhancedQueryProxy* p_pCwmsProxy,
                                            QWidget* p_pqwParent,
                                            QString p_qstrDisplayMember)
{
   CdmObject* pCdmObject = nullptr;

   if(CHKPTR(p_pContainer))
   {
      int iObjectsOnDb = p_pContainer->CountObjectsOnDb();
      if (iObjectsOnDb < 100)
      {
          CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
          pCwmsSelection->SetObjectList(p_pContainer);
          pCwmsSelection->SetProxy(p_pCwmsProxy);
          pCwmsSelection->SetDisplayMember(p_qstrDisplayMember);

          if(pCwmsSelection->exec() == QDialog::Accepted)
          {
             pCdmObject = pCwmsSelection->GetSelectedObject();
          }
      }
      else
      {
          pCdmObject = CwmsSearchWindowDlg::FindObject(p_pContainer, p_pqwParent);
      }
   }

   return pCdmObject;
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:34:49 2012-----------*
 * @method  CwmsObjectSelectionIf::GetObjectId               // public, static                    *
 * @return  long                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCwmsProxy              //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment the static implementation for returning an object.                                    *
 *----------------last changed: --------------------------------Mi 3. Okt 11:34:49 2012-----------*/
long CwmsObjectSelectionIf::GetObjectId(CdmObjectContainer* p_pContainer,
                                        CdmEnhancedQueryProxy* p_pCwmsProxy,
                                        QWidget* p_pqwParent)
{
   long lObjectId = 0;

   if(CHKPTR(p_pContainer))
   {
      CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
      pCwmsSelection->SetProxy(p_pCwmsProxy);
      pCwmsSelection->SetObjectList(p_pContainer);

      if(pCwmsSelection->exec() == QDialog::Accepted)
      {
         lObjectId = pCwmsSelection->GetSelectedObjectId();
      }
   }

   return lObjectId;
}
