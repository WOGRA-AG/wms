/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>

#include "CwmsUtilities.h"

// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"
#include "CdmMember.h"
#include "CdmValueContainerRef.h"
#include "CdmJsonToObjectMapper.h"


/** +-=---------------------------------------------------------Sa 20. Aug 10:43:24 2005----------*
 * @method  CdmValueContainerRef::CdmValueContainerRef               // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The cosntructor of the objectlist reference.                                          *
 *----------------last changed: --------------------------------Sa 20. Aug 10:43:24 2005----------*/
CdmValueContainerRef::CdmValueContainerRef(  long p_lDatabaseId,
                                    long p_lId,
                                    QString p_qstrKeyname,
                                    CdmObject* p_pCdmObject )
   : CdmValueLong(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueContainerRef, p_pCdmObject)
{
   // nothing to do
}


/** +-=---------------------------------------------------------Sa 20. Aug 10:43:47 2005----------*
 * @method  CdmValueContainerRef::CdmValueContainerRef               // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The xml constructor of the objectlist reference.                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 10:43:47 2005----------*/
CdmValueContainerRef::CdmValueContainerRef(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValueLong(p_rqDomElement, p_pCdmObject)
{
   XmlImportContainerRef(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 13:50:14 2012----------*
 * @method  CdmValueContainerRef::CdmValueContainerRef     // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 13:50:14 2012----------*/
CdmValueContainerRef::CdmValueContainerRef(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueLong(p_rqvHash, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:48:07 2005----------*
 * @method  CdmValueContainerRef::~CdmValueContainerRef              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueContainerRef                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 12:48:07 2005----------*/
CdmValueContainerRef::~CdmValueContainerRef(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:40:32 2012-----------*
 * @method  CdmValueContainerRef::Deploy                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:40:32 2012-----------*/
void CdmValueContainerRef::Deploy(QVariantMap& p_rqvHash)
{
   QString qstrObjectListUri = p_rqvHash[WMS_CONTAINERURI].toString();

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      if (!qstrObjectListUri.isEmpty())
      {
        CdmModelElement* pElement = dynamic_cast<CdmModelElement*> (pManager->GetUriObject(qstrObjectListUri));

         if (pElement)
         {
            if (pElement->IsContainer())
            {
               SetValue(dynamic_cast<CdmObjectContainer*>(pElement));
            }
            else
            {
               ERR("Wrong Type in Uri Object");
            }
         }
         else
         {
            m_qstrReferenceUri = qstrObjectListUri;
            CdmContainerManager* pOlManager = GetContainerManager();

            if (CHKPTR(pOlManager))
            {
               pOlManager->AddDeploymentResolveValue(this);
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:44:00 2005----------*
 * @method  CdmValueContainerRef::GetContainer                  // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment returns the Object list which belongs to this object ref.                             *
 *----------------last changed: --------------------------------Sa 20. Aug 10:44:00 2005----------*/
CdmObjectContainer* CdmValueContainerRef::GetContainer()
{
   CdmObjectContainer* pContainer = GetEmptyContainer();

   if (!pContainer)
   {
       const CdmMember* pCdmMember = GetMember();

       if (CHKPTR(pCdmMember))
       {
           const CdmObject* pObject = GetObject();

           if (CHKPTR(pObject))
           {
               if (pCdmMember->IsOwner() && !pObject->IsDeleted())
               {
                   CdmContainerManager* pContainerManager = GetContainerManager();

                   if(CHKPTR(pContainerManager))
                   {
                       QString qstrKeyname = GenerateKeyname();
                       pContainerManager->CreateContainer(pCdmMember->GetClassReference(), qstrKeyname);
                       pContainer = pContainerManager->FindContainerByKeyname(qstrKeyname);

                       if (CHKPTR(pContainer))
                       {
                           pContainer->SetTree(pCdmMember->IsTree());
                           SetValue(pContainer);
                           pContainer->Commit();
                       }
                   }
               }
           }
       }
   }

   return pContainer;
}

/** +-=---------------------------------------------------------So 10. Feb 09:57:00 2013----------*
 * @method  CdmValueContainerRef::IsTypeOf                  // public, const, slots              *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment This method checks if this is object is type of the overgiven classname.              *
 *----------------last changed: --------------------------------So 10. Feb 09:57:00 2013----------*/
bool CdmValueContainerRef::IsTypeOf(QString p_qstrClassName) const
{
   bool bRet = false;
   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      long lClassId = pCdmMember->GetClassReference();

      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(lClassId);

            if (CHKPTR(pCdmClass))
            {
               if (pCdmClass->IsInherited(p_qstrClassName) > 0)
               {
                  bRet = true;
               }
            }
         }
      }
   }

   return bRet;
}


/** +-=---------------------------------------------------------Di 20. Nov 10:43:15 2012----------*
 * @method  CdmValueContainerRef::GetEmptyContainer        // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment returns the Object list which belongs to this object ref.                             *
 *----------------last changed: --------------------------------Di 20. Nov 10:43:15 2012----------*/
CdmObjectContainer* CdmValueContainerRef::GetEmptyContainer()
{
   CdmObjectContainer* pContainer = nullptr;
   CdmContainerManager* pContainerManager = GetContainerManager();

   if(CHKPTR(pContainerManager))
   {
      pContainer = pContainerManager->FindEmptyContainerById(GetValue());
   }
   else
   {
      FATAL("There is no Object List Manager for finding ObjectList.");
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:43:27 2012----------*
 * @method  CdmValueContainerRef::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 10:43:27 2012----------*/
void CdmValueContainerRef::SetValue(CdmObjectContainer* p_pContainer)
{
   if(p_pContainer)
   {
      const CdmMember* pMember = GetMember();

      if (CHKPTR(pMember))
      {
         int iClassRefId = pMember->GetClassReference();

         CdmClass* pClass = GetClassManager()->FindClassById(iClassRefId);

         if (p_pContainer->IsTypeOf(pClass))
         {
            CdmValueLong::SetValue(p_pContainer->GetId());
            m_qstrContainerKeyname = p_pContainer->GetKeyname();
         }
         else
         {
            ERR("Wrong type to add to this value!");
         }
      }
   }
   else
   {
      CdmValueLong::SetValue(0);
      m_qstrContainerKeyname = "";
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 10:43:43 2012----------*
 * @method  CdmValueContainerRef::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 10:43:43 2012----------*/
void CdmValueContainerRef::SetValue(long p_lObjectListId)
{
   CdmValueLong::SetValue(p_lObjectListId);
   CdmObjectContainer* pContainer = GetEmptyContainer();
   SetValue(pContainer);
}

void CdmValueContainerRef::SetValue(long p_lObjectListId, QString p_qstrContainerKeyname)
{
   CdmValueLong::SetValue(p_lObjectListId);
   m_qstrContainerKeyname = p_qstrContainerKeyname;
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:34:52 2010----------*
 * @method  CdmValueContainerRef::SetDefaultValue           // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* #p_pCdmMember                   //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 14:34:52 2010----------*/
void CdmValueContainerRef::SetDefaultValue(const CdmMember*)
{
   // has no default value will be ignored
   INFO("This Value type can not have default values.");
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:35:01 2010----------*
 * @method  CdmValueContainerRef::IsSmaller                 // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Mi 15. Sep 14:35:01 2010----------*/
int CdmValueContainerRef::IsSmaller(QVariant*) const
{

   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:35:10 2010----------*
 * @method  CdmValueContainerRef::IsSmallerEqual            // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Mi 15. Sep 14:35:10 2010----------*/
int CdmValueContainerRef::IsSmallerEqual(QVariant*) const
{

   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:35:20 2010----------*
 * @method  CdmValueContainerRef::IsLarger                  // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 14:35:20 2010----------*/
int CdmValueContainerRef::IsLarger(QVariant* ) const
{

   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:35:29 2010----------*
 * @method  CdmValueContainerRef::IsLargerEqual             // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Mi 15. Sep 14:35:29 2010----------*/
int CdmValueContainerRef::IsLargerEqual(QVariant* ) const
{
   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:35:37 2010----------*
 * @method  CdmValueContainerRef::Add                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   long #p_lAdd                                     //                                   *
 * @comment Adds p_dAdd to Value.                                                                 *
 *----------------last changed: --------------------------------Mi 15. Sep 14:35:37 2010----------*/
void CdmValueContainerRef::Add(long )
{

   // does nothing
   ERR( "This method call makes no sense on ObjectListRefs." );
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:35:44 2010----------*
 * @method  CdmValueContainerRef::Subtract                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   long# p_lSubtract                                //                                   *
 * @comment subtracts p_dSubtract from value.                                                     *
 *----------------last changed: --------------------------------Mi 15. Sep 14:35:44 2010----------*/
void CdmValueContainerRef::Subtract(long)
{

   // does nothing
   ERR( "This method call makes no sense on ObjectListRefs." );
}

/** +-=---------------------------------------------------------So 10. Feb 09:57:31 2013----------*
 * @method  CdmValueContainerRef::GetClassId                // public, const                     *
 * @return  long                                             //                                   *
 * @comment This method returns the Class id for this ref Value.o                                 *
 *----------------last changed: --------------------------------So 10. Feb 09:57:31 2013----------*/
long CdmValueContainerRef::GetClassId() const
{
   long lRet = 0;
   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember))
   {
      lRet = pMember->GetClassReference();
   }
   return lRet;
}

/** +-=---------------------------------------------------------Fr 8. Feb 16:01:49 2013-----------*
 * @method  CdmValueContainerRef::HasValue                  // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment This method returns if this Values has an value.                                      *
 *----------------last changed: --------------------------------Fr 8. Feb 16:01:49 2013-----------*/
bool CdmValueContainerRef::HasValue() const
{
   bool bRet = false;

   if (GetValue() != 0)
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 7. Dez 15:38:42 2012-----------*
 * @method  CdmValueContainerRef::GetClass                  // public                            *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Dez 15:38:42 2012-----------*/
CdmClass* CdmValueContainerRef::GetClass()
{
   CdmClass* pClass = nullptr;
   CdmClassManager* pClassManager = GetClassManager();

   if (CHKPTR(pClassManager))
   {
      pClass = pClassManager->FindClassById(GetClassId());
   }

   return pClass;
}

/** +-=---------------------------------------------------------Sa 7. Jan 14:29:08 2006-----------*
 * @method  CdmValueContainerRef::CheckUnique                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:29:08 2006-----------*/
void CdmValueContainerRef::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 09:58:05 2013----------*
 * @method  CdmValueContainerRef::XmlExport                 // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:58:05 2013----------*/
void CdmValueContainerRef::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);

   p_rqdeValue.setAttribute(WMS_CLASSID,      QString::number(GetClassId()));
   p_rqdeValue.setAttribute(WMS_CONTAINERID, QString::number(GetValue()));
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:44:51 2005----------*
 * @method  CdmValueContainerRef::XmlImportContainerRef         // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 10:44:51 2005----------*/
void CdmValueContainerRef::XmlImportContainerRef(  QDomElement& p_rqDomElement )
{
   SetValue(p_rqDomElement.attribute(WMS_CONTAINERID, "-1").toInt());
}


/** +-=---------------------------------------------------------Sa 20. Aug 10:44:55 2005----------*
 * @method  CdmValueContainerRef::XmlImport                      // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Sa 20. Aug 10:44:55 2005----------*/
void CdmValueContainerRef::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportContainerRef(p_rqDomElement);
}


/** +-=---------------------------------------------------------So 10. Feb 09:58:18 2013----------*
 * @method  CdmValueContainerRef::GetDisplayString          // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:58:18 2013----------*/
QString CdmValueContainerRef::GetDisplayString() const
{
   QString qstrDisplayString;
   CdmObjectContainer* pContainer = (const_cast<CdmValueContainerRef*>(this))->GetContainer();

   if(pContainer)
   {
      qstrDisplayString = pContainer->GetCaption();
   }
   
   return qstrDisplayString;
}

/** +-=---------------------------------------------------------So 10. Feb 09:58:26 2013----------*
 * @method  CdmValueContainerRef::GetVariant                // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:58:26 2013----------*/
QVariant CdmValueContainerRef::GetVariant() const
{
   QVariantMap qmVariant = CdmValueLong::GetVariant().toMap();
   CdmObjectContainer* pObjectList = (const_cast<CdmValueContainerRef*>(this))->GetContainer();

   if (pObjectList)
   {
      qmVariant.insert(WMS_CONTAINERURI, pObjectList->GetUriInternal());
   }
   
   return qmVariant;
}

/** +-=---------------------------------------------------------So 10. Feb 09:58:35 2013----------*
 * @method  CdmValueContainerRef::GetValueVariant           // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:58:35 2013----------*/
QVariant CdmValueContainerRef::GetValueVariant() const
{
    QString qstrUri;

    if (GetValue() > 0)
    {
        if (m_qstrContainerKeyname.isEmpty())
        {
            qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), QString::number(static_cast<int> (GetValue())));
        }
        else
        {
            qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), m_qstrContainerKeyname);
        }
    }

    return qstrUri;
}

/** +-=---------------------------------------------------------Di 5. Jun 08:35:38 2012-----------*
 * @method  CdmValueContainerRef::SetValueVariant           // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 08:35:38 2012-----------*/
void CdmValueContainerRef::SetValueVariant(QVariant& p_rqVariant)
{
   QVariantMap qvHash = p_rqVariant.toMap();
   QString qstrUri;

   if (qvHash.contains(WMS_CONTAINERID))
   {
        SetValue(qvHash[WMS_CONTAINERID].toInt());
        return;
   }
   else if (qvHash.contains(WMS_URI))
   {
       qstrUri = qvHash[WMS_URI].toString();
   }
   else
   {
       qstrUri = CdmJsonToObjectMapper::GetSelfLink(qvHash);
   }

   if (!qstrUri.isEmpty())
   {
       CdmDataProvider* pProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

       if (CHKPTR(pProvider))
       {
           auto pElement = pProvider->GetUriObject(qstrUri);

           if(pElement)
           {
               SetValue(dynamic_cast<CdmObjectContainer*>(pElement));
           }
       }
   }
   else
   {
       SetValue(nullptr);
   }
}

void CdmValueContainerRef::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
    CdmObjectContainer* pContainer = nullptr;
    CdmContainerManager* pContainerManager = GetContainerManager();

    if(CHKPTR(pContainerManager))
    {
        if (CwmsUtilities::IsNumber(p_qstrValue))
        {
            pContainer = pContainerManager->FindEmptyContainerById(p_qstrValue.toInt());
        }
        else
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrValue);
        }

        SetValue(pContainer);
    }
}

/** +-=---------------------------------------------------------Do 13. Dez 08:19:11 2012----------*
 * @method  CdmValueContainerRef::ResolveValue              // public, virtual                   *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 08:19:11 2012----------*/
bool CdmValueContainerRef::ResolveValue()
{
    bool bRet = false;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (m_qstrReferenceUri.isEmpty())
    {
        return true;
    }

    if (CHKPTR(pManager))
    {
        CdmModelElement* pElement = dynamic_cast<CdmModelElement*> (pManager->GetUriObject(m_qstrReferenceUri));

        if (pElement)
        {
            if (pElement->IsContainer())
            {
                SetValue(dynamic_cast<CdmObjectContainer*>(pElement));
                bRet = true;
            }
            else
            {
                ERR("Wrong Type in Uri Object");
            }
        }
    }

    return bRet;
}
