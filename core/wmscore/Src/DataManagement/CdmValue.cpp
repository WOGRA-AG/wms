/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
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

// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmLogging.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListString.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueUser.h"
#include "CdmValueFormula.h"
#include "CdmValueListObjects.h"
#include "CdmValueEnum.h"
#include "CdmValueUserGroup.h"
#include "CdmValue.h"

CdmValue::CdmValue(long p_lDatabaseId,
                   long p_lId,
                   QString p_qstrKeyname,
                   EdmValueType p_eDmValue,
                   CdmObject* p_pCdmObject )
: CdmModelElement(p_lDatabaseId, p_lId, p_qstrKeyname),
  m_lMemberId(0),
  m_rpCdmObject(p_pCdmObject)
{
   CHKPTR(m_rpCdmObject);
   Q_UNUSED(p_eDmValue);
}

CdmValue::CdmValue(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
: CdmModelElement(p_rqDomElement),
  m_lMemberId(0),
  m_rpCdmObject(p_pCdmObject)
{
   CHKPTR(m_rpCdmObject);
   XmlImportValue(p_rqDomElement);
}

CdmValue::CdmValue(QVariantMap& p_rqvVaraint, CdmObject* p_pCdmObject)
   : CdmModelElement(p_rqvVaraint),
  m_lMemberId(0),
  m_rpCdmObject(p_pCdmObject)
{
   CHKPTR(m_rpCdmObject);
   SetVariant(p_rqvVaraint);
}

CdmValue::~CdmValue()
{
   // nothing to do :-)
}

void CdmValue::SetVariant(QVariantMap& p_rqvHash)
{
   CdmModelElement::SetVariant(p_rqvHash);
   m_lMemberId = p_rqvHash[WMS_MEMBERID].toInt();
}

void CdmValue::Deploy(QVariantMap& p_rqvHash)
{
   CdmModelElement::Deploy(p_rqvHash);
   m_lMemberId = p_rqvHash[WMS_MEMBERID].toInt();
   CdmDataProvider* pManager = GetDataProvider();

   if (CHKPTR(pManager))
   {
      QString qstrMember = p_rqvHash[WMS_MEMBERURI].toString();
      CdmLocatedElement* pElement = pManager->GetUriObject(qstrMember);

      if (CHKPTR(pElement) && pElement->IsMember())
      {
         CdmMember* pMember = static_cast<CdmMember*>(pElement);
         m_lMemberId = pMember->GetId();
      }
   }
}

CdmValue* CdmValue::CreateValue(CdmMember* p_pCdmMember, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = nullptr;

   if(p_pCdmMember)
   {
      EdmValueType eDmValue = p_pCdmMember->GetValueType();

      switch(eDmValue)
      {
         
      case eDmValueBool:
         pCdmValue = new CdmValueBool(p_pCdmMember->GetSchemeId(), 
                                 p_pCdmMember->GetId(), 
                                 p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueInt:
         pCdmValue = new CdmValueInt(p_pCdmMember->GetSchemeId(), 
                                p_pCdmMember->GetId(), 
                                p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueLong:        
         pCdmValue = new CdmValueLong(p_pCdmMember->GetSchemeId(), 
                                 p_pCdmMember->GetId(), 
                                 p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueFloat:             
         pCdmValue = new CdmValueFloat(p_pCdmMember->GetSchemeId(), 
                                  p_pCdmMember->GetId(), 
                                  p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueDouble:            
         pCdmValue = new CdmValueDouble(p_pCdmMember->GetSchemeId(), 
                                   p_pCdmMember->GetId(), 
                                   p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueString:            
         pCdmValue = new CdmValueString(p_pCdmMember->GetSchemeId(), 
                                   p_pCdmMember->GetId(), 
                                   p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueDate:              
         pCdmValue = new CdmValueDate(p_pCdmMember->GetSchemeId(), 
                                 p_pCdmMember->GetId(), 
                                 p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueTime:              
         pCdmValue = new CdmValueTime(p_pCdmMember->GetSchemeId(), 
                                 p_pCdmMember->GetId(), 
                                 p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueDateTime:          
         pCdmValue = new CdmValueDateTime(p_pCdmMember->GetSchemeId(), 
                                     p_pCdmMember->GetId(), 
                                     p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueObjectRef:         
         pCdmValue = new CdmValueObjectRef(p_pCdmMember->GetSchemeId(), 
                                      p_pCdmMember->GetId(), 
                                      p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueContainerRef:    
         pCdmValue = new CdmValueContainerRef(p_pCdmMember->GetSchemeId(), 
                                          p_pCdmMember->GetId(), 
                                          p_pCdmMember->GetKeyname(),
                                 p_pCdmObject);
         break;
      case eDmValueCounter:           
         pCdmValue = new CdmValueCounter(p_pCdmMember->GetSchemeId(), 
                                    p_pCdmMember->GetId(), 
                                    p_pCdmMember->GetKeyname(),
                                    p_pCdmObject);
         break;
      case eDmValueBinaryDocument:    
         pCdmValue = new CdmValueBinaryDocument(p_pCdmMember->GetSchemeId(), 
                                           p_pCdmMember->GetId(), 
                                           p_pCdmMember->GetKeyname(),
                                           "",
                                           "",
                                           p_pCdmObject);
         break;
      case eDmValueCharacterDocument:
         pCdmValue = new CdmValueCharacterDocument(p_pCdmMember->GetSchemeId(), 
                                              p_pCdmMember->GetId(), 
                                              p_pCdmMember->GetKeyname(),
                                              p_pCdmObject);
         break;

      case eDmValueListInt:
         pCdmValue = new CdmValueListInt(p_pCdmMember->GetSchemeId(), 
                                    p_pCdmMember->GetId(), 
                                    p_pCdmMember->GetKeyname(),
                                    p_pCdmObject);
         break;
      case eDmValueListDouble:
         pCdmValue = new CdmValueListDouble(p_pCdmMember->GetSchemeId(), 
                                        p_pCdmMember->GetId(), 
                                        p_pCdmMember->GetKeyname(),
                                        p_pCdmObject);
         break;
      case eDmValueListString:
         pCdmValue = new CdmValueListString(p_pCdmMember->GetSchemeId(), 
                                       p_pCdmMember->GetId(), 
                                       p_pCdmMember->GetKeyname(),
                                       p_pCdmObject);
         break;
      case eDmValueDictStringInt:
         pCdmValue = new CdmValueDictStringInt(p_pCdmMember->GetSchemeId(), 
                                          p_pCdmMember->GetId(), 
                                          p_pCdmMember->GetKeyname(),
                                          p_pCdmObject);
         break;
      case eDmValueDictStringString:
         pCdmValue = new CdmValueDictStringString(p_pCdmMember->GetSchemeId(), 
                                             p_pCdmMember->GetId(), 
                                             p_pCdmMember->GetKeyname(),
                                             p_pCdmObject);
         break;
      case eDmValueDictStringDouble:
         pCdmValue = new CdmValueDictStringDouble(p_pCdmMember->GetSchemeId(), 
                                             p_pCdmMember->GetId(), 
                                             p_pCdmMember->GetKeyname(),
                                             p_pCdmObject);
         break;
      case eDmValueDictIntInt:
         pCdmValue = new CdmValueDictIntInt(p_pCdmMember->GetSchemeId(), 
                                       p_pCdmMember->GetId(), 
                                       p_pCdmMember->GetKeyname(),
                                       p_pCdmObject);
         break;
      case eDmValueDictIntString:
         pCdmValue = new CdmValueDictIntString(p_pCdmMember->GetSchemeId(), 
                                          p_pCdmMember->GetId(), 
                                          p_pCdmMember->GetKeyname(),
                                          p_pCdmObject);
         break;
      case eDmValueDictIntDouble:
         pCdmValue = new CdmValueDictIntDouble(p_pCdmMember->GetSchemeId(), 
                                          p_pCdmMember->GetId(), 
                                          p_pCdmMember->GetKeyname(),
                                          p_pCdmObject);
         break;
      case eDmValueUser:
         pCdmValue = new CdmValueUser(p_pCdmMember->GetSchemeId(), 
                                      p_pCdmMember->GetId(), 
                                      p_pCdmMember->GetKeyname(),
                                      p_pCdmObject);
         break;
      case eDmValueFormula:
         pCdmValue = new CdmValueFormula(p_pCdmMember->GetSchemeId(), 
                                         p_pCdmMember->GetId(), 
                                         p_pCdmMember->GetKeyname(),
                                         p_pCdmObject);
         break;
      case eDmValueListObjects:
         pCdmValue = new CdmValueListObjects(p_pCdmMember->GetSchemeId(), 
                                             p_pCdmMember->GetId(), 
                                             p_pCdmMember->GetKeyname(),
                                             p_pCdmObject);
         break;
      case eDmValueEnum:
         pCdmValue = new CdmValueEnum(p_pCdmMember->GetSchemeId(), 
                                      p_pCdmMember->GetId(), 
                                      p_pCdmMember->GetKeyname(),
                                      p_pCdmObject);
         break;
      case eDmValueUserGroup:
         pCdmValue = new CdmValueUserGroup(p_pCdmMember->GetSchemeId(), 
                                           p_pCdmMember->GetId(), 
                                           p_pCdmMember->GetKeyname(),
                                           p_pCdmObject);
         break;
      default:
         FATAL("Value does not exist in this switch operation");
         break;
      }

      if(CHKPTR(pCdmValue))
      {
         pCdmValue->SetMemberId(p_pCdmMember->GetId());
         pCdmValue->SetDefaultValue(p_pCdmMember);
         pCdmValue->SetCaption(p_pCdmMember->GetCaption());
      }
   }

   return pCdmValue;
}

CdmValue* CdmValue::CreateValue(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = nullptr;
   EdmValueType eDmValue  = static_cast<EdmValueType>(p_rqDomElement.attribute(WMS_VALUETYPE, "-1").toInt());
   
   switch(eDmValue)
   {
   case eDmValueBool:
      pCdmValue = new CdmValueBool(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueInt:
      pCdmValue = new CdmValueInt(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueLong:        
      pCdmValue = new CdmValueLong(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueFloat:             
      pCdmValue = new CdmValueFloat(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDouble:            
      pCdmValue = new CdmValueDouble(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueString:            
      pCdmValue = new CdmValueString(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDate:              
      pCdmValue = new CdmValueDate(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueTime:              
      pCdmValue = new CdmValueTime(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDateTime:          
      pCdmValue = new CdmValueDateTime(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueObjectRef:         
      pCdmValue = new CdmValueObjectRef(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueContainerRef:    
      pCdmValue = new CdmValueContainerRef(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueCounter:           
      pCdmValue = new CdmValueCounter(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueBinaryDocument:    
      pCdmValue = new CdmValueBinaryDocument(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueCharacterDocument:
      pCdmValue = new CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueListInt:
      pCdmValue = new CdmValueListInt(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueListDouble:
      pCdmValue = new CdmValueListDouble(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueListString:
      pCdmValue = new CdmValueListString(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDictStringInt:
      pCdmValue = new CdmValueDictStringInt(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDictStringString:
      pCdmValue = new CdmValueDictStringString(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDictStringDouble:
      pCdmValue = new CdmValueDictStringDouble(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDictIntInt:
      pCdmValue = new CdmValueDictIntInt(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDictIntString:
      pCdmValue = new CdmValueDictIntString(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueDictIntDouble:
      pCdmValue = new CdmValueDictIntDouble(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueUser:
      pCdmValue = new CdmValueUser(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueListObjects:
      pCdmValue = new CdmValueListObjects(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueEnum:
      pCdmValue = new CdmValueEnum(p_rqDomElement, p_pCdmObject);
      break;
   case eDmValueUserGroup:
      pCdmValue = new CdmValueUserGroup(p_rqDomElement, p_pCdmObject);
      break;
   default:
      FATAL("Value does not exist in this switch operation");
      break;
   }

   if (CHKPTR(pCdmValue))
   {
//       pCdmValue->setParent(p_pCdmObject);
   }

   return pCdmValue;
}

CdmValue* CdmValue::CreateDeployValue(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = nullptr;

   EdmValueType eDmValue  = static_cast<EdmValueType>(p_rqvHash[WMS_VALUETYPE].toInt());
   long lDatabaseId = p_rqvHash[WMS_DATABASEID].toInt();
   long lMemberId = p_rqvHash[WMS_MEMBERID].toInt();
   QString qstrKeyname = p_rqvHash[WMS_KEYNAME].toString();

   switch(eDmValue)
   {
   case eDmValueBool:
      pCdmValue = new CdmValueBool(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueInt:
      pCdmValue = new CdmValueInt(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueLong:        
      pCdmValue = new CdmValueLong(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueFloat:             
      pCdmValue = new CdmValueFloat(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDouble:            
      pCdmValue = new CdmValueDouble(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueString:            
      pCdmValue = new CdmValueString(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDate:              
      pCdmValue = new CdmValueDate(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueTime:              
      pCdmValue = new CdmValueTime(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDateTime:          
      pCdmValue = new CdmValueDateTime(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueObjectRef:         
      pCdmValue = new CdmValueObjectRef(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueContainerRef:    
      pCdmValue = new CdmValueContainerRef(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueCounter:           
      pCdmValue = new CdmValueCounter(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueBinaryDocument:    
      {
         QString qstrFilename = p_rqvHash[WMS_FILENAME].toString();
         QString qstrType = p_rqvHash[WMS_FILETYPE].toString();
         pCdmValue = new CdmValueBinaryDocument(lDatabaseId, lMemberId, qstrKeyname, qstrFilename, qstrType, p_pCdmObject);
         QString qstrBase64 = p_rqvHash[WMS_VALUE].toString();
         static_cast<CdmValueBinaryDocument*>(pCdmValue)->SetBase64(qstrFilename, qstrType, qstrBase64);
         break;
      }
   case eDmValueCharacterDocument:
      pCdmValue = new CdmValueCharacterDocument(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueListInt:
      pCdmValue = new CdmValueListInt(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueListDouble:
      pCdmValue = new CdmValueListDouble(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueListString:
      pCdmValue = new CdmValueListString(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDictStringInt:
      pCdmValue = new CdmValueDictStringInt(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDictStringString:
      pCdmValue = new CdmValueDictStringString(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDictStringDouble:
      pCdmValue = new CdmValueDictStringDouble(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDictIntInt:
      pCdmValue = new CdmValueDictIntInt(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDictIntString:
      pCdmValue = new CdmValueDictIntString(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueDictIntDouble:
      pCdmValue = new CdmValueDictIntDouble(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueUser:
      pCdmValue = new CdmValueUser(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueListObjects:
      pCdmValue = new CdmValueListObjects(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueEnum:
      pCdmValue = new CdmValueEnum(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   case eDmValueUserGroup:
      pCdmValue = new CdmValueUserGroup(lDatabaseId, lMemberId, qstrKeyname, p_pCdmObject);
      break;
   default:
      FATAL("Value does not exist in this switch operation");
      break;
   }


   return pCdmValue;
}

CdmValue* CdmValue::CreateValue(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = nullptr;

   const CdmClass* pClass = p_pCdmObject->GetClass();
   EdmValueType eDmValue  = eDmValueNone;

   if (CHKPTR(pClass))
   {
      long lMemberId = p_rqvHash[WMS_MEMBERID].toInt();

      if (lMemberId > 0)
      {
         const CdmMember* pMember = pClass->FindMember(lMemberId);

         if (CHKPTR(pMember))
         {
            eDmValue = pMember->GetValueType();
         }
      }
   }

   switch(eDmValue)
   {
   case eDmValueBool:
      pCdmValue = new CdmValueBool(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueInt:
      pCdmValue = new CdmValueInt(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueLong:        
      pCdmValue = new CdmValueLong(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueFloat:             
      pCdmValue = new CdmValueFloat(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDouble:            
      pCdmValue = new CdmValueDouble(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueString:            
      pCdmValue = new CdmValueString(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDate:              
      pCdmValue = new CdmValueDate(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueTime:              
      pCdmValue = new CdmValueTime(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDateTime:          
      pCdmValue = new CdmValueDateTime(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueObjectRef:         
      pCdmValue = new CdmValueObjectRef(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueContainerRef:    
      pCdmValue = new CdmValueContainerRef(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueCounter:           
      pCdmValue = new CdmValueCounter(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueBinaryDocument:    
      pCdmValue = new CdmValueBinaryDocument(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueCharacterDocument:
      pCdmValue = new CdmValueCharacterDocument(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueListInt:
      pCdmValue = new CdmValueListInt(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueListDouble:
      pCdmValue = new CdmValueListDouble(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueListString:
      pCdmValue = new CdmValueListString(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDictStringInt:
      pCdmValue = new CdmValueDictStringInt(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDictStringString:
      pCdmValue = new CdmValueDictStringString(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDictStringDouble:
      pCdmValue = new CdmValueDictStringDouble(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDictIntInt:
      pCdmValue = new CdmValueDictIntInt(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDictIntString:
      pCdmValue = new CdmValueDictIntString(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueDictIntDouble:
      pCdmValue = new CdmValueDictIntDouble(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueUser:
      pCdmValue = new CdmValueUser(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueListObjects:
      pCdmValue = new CdmValueListObjects(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueEnum:
      pCdmValue = new CdmValueEnum(p_rqvHash, p_pCdmObject);
      break;
   case eDmValueUserGroup:
      pCdmValue = new CdmValueUserGroup(p_rqvHash, p_pCdmObject);
      break;
   default:
      FATAL("Value does not exist in this switch operation");
      break;
   }

   return pCdmValue;
}

CdmValue* CdmValue::CopyValue(const CdmValue* p_pCdmValue, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = nullptr;

   if (p_pCdmValue)
   {
      EdmValueType eDmValue = p_pCdmValue->GetValueType();

      switch (eDmValue)
      {
         
      case eDmValueBool:
         pCdmValue = new CdmValueBool( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueBool*)pCdmValue)->SetValue(((CdmValueBool*)p_pCdmValue)->GetValue());
         break;
      case eDmValueInt:
         pCdmValue = new CdmValueInt( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueInt*)pCdmValue)->SetValue(((CdmValueInt*)p_pCdmValue)->GetValue());
         break;
      case eDmValueLong:        
         pCdmValue = new CdmValueLong( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueLong*)pCdmValue)->SetValue(((CdmValueLong*)p_pCdmValue)->GetValue());
         break;
      case eDmValueFloat:             
         pCdmValue = new CdmValueFloat( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueFloat*)pCdmValue)->SetValue(((CdmValueFloat*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDouble:            
         pCdmValue = new CdmValueDouble( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDouble*)pCdmValue)->SetValue(((CdmValueDouble*)p_pCdmValue)->GetValue());
         break;
      case eDmValueString:            
         pCdmValue = new CdmValueString( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueString*)pCdmValue)->SetValue(((CdmValueString*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDate:              
         pCdmValue = new CdmValueDate( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDate*)pCdmValue)->SetValue(((CdmValueDate*)p_pCdmValue)->GetValue());
         break;
      case eDmValueTime:              
         pCdmValue = new CdmValueTime( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueTime*)pCdmValue)->SetValue(((CdmValueTime*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDateTime:          
         pCdmValue = new CdmValueDateTime( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDateTime*)pCdmValue)->SetValue(((CdmValueDateTime*)p_pCdmValue)->GetValue());
         break;
      case eDmValueObjectRef:   
         {
            CdmValueObjectRef* pCdmObjectRef = (CdmValueObjectRef*)p_pCdmValue;
            
            if(CHKPTR(pCdmObjectRef))
            {
               if (pCdmObjectRef->IsOwner())
               {
                  CdmContainerManager* pContainerManager = pCdmObjectRef->GetContainerManager();

                  if(CHKPTR(pContainerManager))
                  {
                    pCdmValue = new CdmValueObjectRef(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
                    pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
                    long lObjectListId = pCdmObjectRef->GetObjectListId();

                    if (lObjectListId > 0)
                    {
                       CdmObjectContainer* pContainer = pContainerManager->FindContainerById(lObjectListId);

                       if(CHKPTR(pContainer))
                       {
                           CdmObject* pCdmObject = pContainer->CopyObject(pCdmObjectRef->GetObject());

                           if(CHKPTR(pCdmObject) && pCdmObject->IsValid())
                           {
                              ((CdmValueObjectRef*)pCdmValue)->SetValue(pCdmObject);
                           }
                           else
                           {
                              ERR("Copying of Object failed!");
                           }
                        }
                     }
                     else // copying nullptr value in ObjectRef
                     {
                        pCdmValue = new CdmValueObjectRef(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
                        pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
                     }
                  }
               }
               else
               {
                  pCdmValue = new CdmValueObjectRef(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
                  pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
                  ((CdmValueObjectRef*)pCdmValue)->SetValue(pCdmObjectRef->GetObject());
               }
            }
            
         break;
         }
      case eDmValueContainerRef: 
         {
            CdmValueContainerRef* pContainerRef = (CdmValueContainerRef*)p_pCdmValue;
            
            if(CHKPTR(pContainerRef))
            {
               if (pContainerRef->IsOwner())
               {
                  CdmContainerManager* pContainerManager = pContainerRef->GetContainerManager();

                  if(CHKPTR(pContainerManager))
                  {
                    pCdmValue = new CdmValueContainerRef( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
                    pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
                    CdmObjectContainer* pContainer = pContainerManager->CopyContainer(pContainerRef->GetValue(), true);

                    if(CHKPTR(pContainer))
                    {
                        ((CdmValueContainerRef*)pCdmValue)->CdmValueLong::SetValue(pContainer->GetId());
                     }
                  }
               }
               else
               {
                  pCdmValue = new CdmValueContainerRef( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
                  pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
                  ((CdmValueContainerRef*)pCdmValue)->CdmValueLong::SetValue(((CdmValueContainerRef*)p_pCdmValue)->GetValue());
               }
            }
            
            break;
         }
      case eDmValueCounter:
          pCdmValue = new CdmValueCounter(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         // no copying auf counter values.
         INFO("Counter won't be copied.");
         break;
      case eDmValueBinaryDocument: 
         {
         QString qstrFilename;
         QString qstrType;
         ((CdmValueBinaryDocument*)p_pCdmValue)->GetValue(qstrFilename, qstrType);
         
         pCdmValue = new CdmValueBinaryDocument(p_pCdmValue->GetSchemeId(), 
                                           p_pCdmValue->GetMemberId(),
                                           p_pCdmValue->GetKeyname(), 
                                           qstrFilename,
                                           qstrType,
                                           p_pCdmObject);
            pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         
         break;
         }
      case eDmValueCharacterDocument:
         pCdmValue = new CdmValueCharacterDocument( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueCharacterDocument*)pCdmValue)->SetValue(((CdmValueCharacterDocument*)p_pCdmValue)->GetValue());
         break;
      case eDmValueListDouble:
         pCdmValue = new CdmValueListDouble( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueListDouble*)pCdmValue)->SetValue(((CdmValueListDouble*)p_pCdmValue)->GetValue());
         break;
      case eDmValueListInt:
         pCdmValue = new CdmValueListInt( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueListInt*)pCdmValue)->SetValue(((CdmValueListInt*)p_pCdmValue)->GetValue());
         break;
      case eDmValueListString:
         pCdmValue = new CdmValueListString( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueListString*)pCdmValue)->SetValue(((CdmValueListString*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDictStringInt:
         pCdmValue = new CdmValueDictStringInt( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         ((CdmValueDictStringInt*)pCdmValue)->SetValue(((CdmValueDictStringInt*)p_pCdmValue)->GetValue());
         break;
       case eDmValueDictStringDouble:
         pCdmValue = new CdmValueDictStringDouble( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDictStringDouble*)pCdmValue)->SetValue(((CdmValueDictStringDouble*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDictStringString:
         pCdmValue = new CdmValueDictStringString( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDictStringString*)pCdmValue)->SetValue(((CdmValueDictStringString*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDictIntInt:
         pCdmValue = new CdmValueDictIntInt( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDictIntInt*)pCdmValue)->SetValue(((CdmValueDictIntInt*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDictIntDouble:
         pCdmValue = new CdmValueDictIntDouble( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueDictIntDouble*)pCdmValue)->SetValue(((CdmValueDictIntDouble*)p_pCdmValue)->GetValue());
         break;
      case eDmValueDictIntString:
         pCdmValue = new CdmValueDictIntString( p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         ((CdmValueDictIntString*)pCdmValue)->SetValue(((CdmValueDictIntString*)p_pCdmValue)->GetValue());
         break;
      case eDmValueListObjects:
         pCdmValue = new CdmValueListObjects(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueListObjects*)pCdmValue)->SetValue(((CdmValueListObjects*)p_pCdmValue)->GetValue());
         break;
      case eDmValueUser:
         pCdmValue = new CdmValueUser(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueUser*)pCdmValue)->SetValue(((CdmValueUser*)p_pCdmValue)->GetValue());
         break;
      case eDmValueUserGroup:
         pCdmValue = new CdmValueUserGroup(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueUserGroup*)pCdmValue)->SetValue(((CdmValueUserGroup*)p_pCdmValue)->GetValue());
         break;
      case eDmValueEnum:
         pCdmValue = new CdmValueEnum(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
         ((CdmValueEnum*)pCdmValue)->SetValue(((CdmValueEnum*)p_pCdmValue)->GetValue());
          break;
      case eDmValueFormula:
         pCdmValue = new CdmValueFormula(p_pCdmValue->GetSchemeId(), p_pCdmValue->GetMemberId(), p_pCdmValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmValue->GetMemberId());
        break;
      default:
         FATAL( "Value does not exist in this switch operation" );
         break;
      }

      if (pCdmValue)
      {
          pCdmValue->SetNew();
      }
   }
   
   return pCdmValue;
}

CdmValue* CdmValue::CopyEventValue(const CdmValue* p_pCdmEventValue, CdmObject *pEventObject, CdmObject* p_pCdmObject, CdmValue* p_pCdmObjectValue)
{
   CdmValue* pCdmValue = nullptr;

   if ( p_pCdmEventValue )
   {
      const CdmMember *pEventMember = p_pCdmEventValue->GetEventMember(pEventObject);
      EdmValueType eDmValue = pEventMember->GetValueType();

      switch ( eDmValue )
      {

      case eDmValueBool:
         pCdmValue = new CdmValueBool( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueBool*)pCdmValue)->SetValue(((CdmValueBool*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueInt:
         pCdmValue = new CdmValueInt( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueInt*)pCdmValue)->SetValue(((CdmValueInt*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueLong:
         pCdmValue = new CdmValueLong( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueLong*)pCdmValue)->SetValue(((CdmValueLong*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueFloat:
         pCdmValue = new CdmValueFloat( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueFloat*)pCdmValue)->SetValue(((CdmValueFloat*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDouble:
         pCdmValue = new CdmValueDouble( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDouble*)pCdmValue)->SetValue(((CdmValueDouble*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueString:
         pCdmValue = new CdmValueString( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueString*)pCdmValue)->SetValue(((CdmValueString*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDate:
         pCdmValue = new CdmValueDate( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDate*)pCdmValue)->SetValue(((CdmValueDate*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueTime:
         pCdmValue = new CdmValueTime( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueTime*)pCdmValue)->SetValue(((CdmValueTime*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDateTime:
         pCdmValue = new CdmValueDateTime( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDateTime*)pCdmValue)->SetValue(((CdmValueDateTime*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueObjectRef:
         {
            CdmValueObjectRef* pCdmObjectRef = (CdmValueObjectRef*)p_pCdmEventValue;

            if(CHKPTR(pCdmObjectRef))
            {
               if (pCdmObjectRef->IsOwner())
               {
                  CdmContainerManager* pContainerManager = pCdmObjectRef->GetContainerManager();

                  if(CHKPTR(pContainerManager))
                  {
                     long lObjectListId = pCdmObjectRef->GetObjectListId();

                     if (lObjectListId > 0)
                     {
                        CdmObjectContainer* pContainer = pContainerManager->FindContainerById(lObjectListId);

                        if(CHKPTR(pContainer))
                        {
                           CdmObject* pCdmObject = pContainer->CopyObject(pCdmObjectRef->GetObject());

                           if(CHKPTR(pCdmObject) && pCdmObject->IsValid())
                           {
                              pCdmValue = new CdmValueObjectRef(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
                              pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
                              ((CdmValueObjectRef*)pCdmValue)->SetValue(pCdmObject);
                           }
                           else
                           {
                              ERR("Copying of Object failed!");
                           }
                        }
                     }
                     else // copying nullptr value in ObjectRef
                     {
                        pCdmValue = new CdmValueObjectRef(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
                        pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
                     }
                  }
               }
               else
               {
                  pCdmValue = new CdmValueObjectRef(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
                  pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
                  ((CdmValueObjectRef*)pCdmValue)->SetValue(pCdmObjectRef->GetObject());
               }
            }

         break;
         }
      case eDmValueContainerRef:
         {

            CdmValueContainerRef* pContainerRef = (CdmValueContainerRef*)p_pCdmEventValue;

            if(CHKPTR(pContainerRef))
            {
               if (pContainerRef->IsOwner())
               {
                  CdmContainerManager* pContainerManager = pContainerRef->GetContainerManager();

                  if(CHKPTR(pContainerManager))
                  {
                     CdmObjectContainer* pContainer = pContainerManager->CopyContainer(pContainerRef->GetValue(), true);

                     if(CHKPTR(pContainer))
                     {
                        pCdmValue = new CdmValueContainerRef( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
                        pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
                        ((CdmValueContainerRef*)pCdmValue)->CdmValueLong::SetValue(pContainer->GetId());
                     }
                  }
               }
               else
               {
                  pCdmValue = new CdmValueContainerRef( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
                  pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
                  ((CdmValueContainerRef*)pCdmValue)->CdmValueLong::SetValue(((CdmValueContainerRef*)p_pCdmEventValue)->GetValue());
               }
            }

            break;
         }
      case eDmValueCounter:
          pCdmValue = new CdmValueCounter(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         // no copying auf counter values.
         INFO("Counter won't be copied.");
         break;
      case eDmValueBinaryDocument:
         {
         QString qstrFilename;
         QString qstrType;
         ((CdmValueBinaryDocument*)p_pCdmEventValue)->GetValue(qstrFilename, qstrType);

         pCdmValue = new CdmValueBinaryDocument(p_pCdmObjectValue->GetSchemeId(),
                                           p_pCdmObjectValue->GetMemberId(),
                                           p_pCdmObjectValue->GetKeyname(),
                                           qstrFilename,
                                           qstrType,
                                           p_pCdmObject);
            pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());

         break;
         }
      case eDmValueCharacterDocument:
         pCdmValue = new CdmValueCharacterDocument( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueCharacterDocument*)pCdmValue)->SetValue(((CdmValueCharacterDocument*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueListDouble:
         pCdmValue = new CdmValueListDouble( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueListDouble*)pCdmValue)->SetValue(((CdmValueListDouble*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueListInt:
         pCdmValue = new CdmValueListInt( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueListInt*)pCdmValue)->SetValue(((CdmValueListInt*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueListString:
         pCdmValue = new CdmValueListString( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueListString*)pCdmValue)->SetValue(((CdmValueListString*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDictStringInt:
         pCdmValue = new CdmValueDictStringInt( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         ((CdmValueDictStringInt*)pCdmValue)->SetValue(((CdmValueDictStringInt*)p_pCdmEventValue)->GetValue());
         break;
       case eDmValueDictStringDouble:
         pCdmValue = new CdmValueDictStringDouble( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDictStringDouble*)pCdmValue)->SetValue(((CdmValueDictStringDouble*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDictStringString:
         pCdmValue = new CdmValueDictStringString( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDictStringString*)pCdmValue)->SetValue(((CdmValueDictStringString*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDictIntInt:
         pCdmValue = new CdmValueDictIntInt( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDictIntInt*)pCdmValue)->SetValue(((CdmValueDictIntInt*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDictIntDouble:
         pCdmValue = new CdmValueDictIntDouble( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueDictIntDouble*)pCdmValue)->SetValue(((CdmValueDictIntDouble*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueDictIntString:
         pCdmValue = new CdmValueDictIntString( p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         ((CdmValueDictIntString*)pCdmValue)->SetValue(((CdmValueDictIntString*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueListObjects:
         pCdmValue = new CdmValueListObjects(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueListObjects*)pCdmValue)->SetValue(((CdmValueListObjects*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueUser:
         pCdmValue = new CdmValueUser(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueUser*)pCdmValue)->SetValue(((CdmValueUser*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueUserGroup:
         pCdmValue = new CdmValueUserGroup(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueUserGroup*)pCdmValue)->SetValue(((CdmValueUserGroup*)p_pCdmEventValue)->GetValue());
         break;
      case eDmValueEnum:
         pCdmValue = new CdmValueEnum(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
         ((CdmValueEnum*)pCdmValue)->SetValue(((CdmValueEnum*)p_pCdmEventValue)->GetValue());
          break;
      case eDmValueFormula:
         pCdmValue = new CdmValueFormula(p_pCdmObjectValue->GetSchemeId(), p_pCdmObjectValue->GetMemberId(), p_pCdmObjectValue->GetKeyname(), p_pCdmObject);
         pCdmValue->SetMemberId(p_pCdmObjectValue->GetMemberId());
        break;
      default:
         FATAL( "Value does not exist in this switch operation" );
         break;
      }

      if (pCdmValue)
      {
          pCdmValue->SetNew();
      }
   }

   return pCdmValue;
}

CdmValue *CdmValue::CopyObjectValueToEventValue(const CdmValue* p_pCdmEventValue, const CdmObject *pEventObject, CdmObject* p_pCdmObject, CdmValue* p_pCdmObjectValue)
{
    CdmValue* pCdmValue = nullptr;

    if ( p_pCdmEventValue )
    {
       EdmValueType eDmValue = p_pCdmEventValue->GetValueType();

       switch ( eDmValue )
       {

       case eDmValueBool:
          pCdmValue = new CdmValueBool( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueBool*)pCdmValue)->SetValue(((CdmValueBool*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueInt:
          pCdmValue = new CdmValueInt( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueInt*)pCdmValue)->SetValue(((CdmValueInt*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueLong:
          pCdmValue = new CdmValueLong( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueLong*)pCdmValue)->SetValue(((CdmValueLong*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueFloat:
          pCdmValue = new CdmValueFloat( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueFloat*)pCdmValue)->SetValue(((CdmValueFloat*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDouble:
          pCdmValue = new CdmValueDouble( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDouble*)pCdmValue)->SetValue(((CdmValueDouble*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueString:
          pCdmValue = new CdmValueString( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueString*)pCdmValue)->SetValue(((CdmValueString*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDate:
          pCdmValue = new CdmValueDate( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDate*)pCdmValue)->SetValue(((CdmValueDate*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueTime:
          pCdmValue = new CdmValueTime( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueTime*)pCdmValue)->SetValue(((CdmValueTime*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDateTime:
          pCdmValue = new CdmValueDateTime( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDateTime*)pCdmValue)->SetValue(((CdmValueDateTime*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueObjectRef:
          {
             CdmValueObjectRef* pCdmObjectRef = (CdmValueObjectRef*)p_pCdmEventValue;

             if(CHKPTR(pCdmObjectRef))
             {
                if (pCdmObjectRef->IsOwner())
                {
                   CdmContainerManager* pContainerManager = pCdmObjectRef->GetContainerManager();

                   if(CHKPTR(pContainerManager))
                   {
                      long lObjectListId = pCdmObjectRef->GetObjectListId();

                      if (lObjectListId > 0)
                      {
                         CdmObjectContainer* pContainer = pContainerManager->FindContainerById(lObjectListId);

                         if(CHKPTR(pContainer))
                         {
                            CdmObject* pCdmObject = pContainer->CopyObject(pCdmObjectRef->GetObject());

                            if(CHKPTR(pCdmObject) && pCdmObject->IsValid())
                            {
                               pCdmValue = new CdmValueObjectRef(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
                               pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
                               ((CdmValueObjectRef*)pCdmValue)->SetValue(pCdmObject);
                            }
                            else
                            {
                               ERR("Copying of Object failed!");
                            }
                         }
                      }
                      else // copying nullptr value in ObjectRef
                      {
                         pCdmValue = new CdmValueObjectRef(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
                         pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
                         ((CdmValueObjectRef*)pCdmValue)->SetValue(p_pCdmObject);
                      }
                   }
                }
                else
                {
                   pCdmValue = new CdmValueObjectRef(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
                   pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
                   ((CdmValueObjectRef*)pCdmValue)->SetValue(pCdmObjectRef->GetObject());
                }
             }

          break;
          }
       case eDmValueContainerRef:
          {

             CdmValueContainerRef* pContainerRef = (CdmValueContainerRef*)p_pCdmEventValue;

             if(CHKPTR(pContainerRef))
             {
                if (pContainerRef->IsOwner())
                {
                   CdmContainerManager* pContainerManager = pContainerRef->GetContainerManager();

                   if(CHKPTR(pContainerManager))
                   {
                      CdmObjectContainer* pContainer = pContainerManager->CopyContainer(pContainerRef->GetValue(), true);

                      if(CHKPTR(pContainer))
                      {
                         pCdmValue = new CdmValueContainerRef( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
                         pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
                         ((CdmValueContainerRef*)pCdmValue)->CdmValueLong::SetValue(pContainer->GetId());
                      }
                   }
                }
                else
                {
                   pCdmValue = new CdmValueContainerRef( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
                   pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
                   ((CdmValueContainerRef*)pCdmValue)->CdmValueLong::SetValue(((CdmValueContainerRef*)p_pCdmObjectValue)->GetValue());
                }
             }

             break;
          }
       case eDmValueCounter:
           pCdmValue = new CdmValueCounter(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          // no copying auf counter values.
          INFO("Counter won't be copied.");
          break;
       case eDmValueBinaryDocument:
          {
          QString qstrFilename;
          QString qstrType;
          ((CdmValueBinaryDocument*)p_pCdmEventValue)->GetValue(qstrFilename, qstrType);

          pCdmValue = new CdmValueBinaryDocument(p_pCdmEventValue->GetSchemeId(),
                                            p_pCdmEventValue->GetMemberId(),
                                            p_pCdmEventValue->GetKeyname(),
                                            qstrFilename,
                                            qstrType,
                                            p_pCdmObject);
             pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());

          break;
          }
       case eDmValueCharacterDocument:
          pCdmValue = new CdmValueCharacterDocument( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueCharacterDocument*)pCdmValue)->SetValue(((CdmValueCharacterDocument*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueListDouble:
          pCdmValue = new CdmValueListDouble( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueListDouble*)pCdmValue)->SetValue(((CdmValueListDouble*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueListInt:
          pCdmValue = new CdmValueListInt( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueListInt*)pCdmValue)->SetValue(((CdmValueListInt*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueListString:
          pCdmValue = new CdmValueListString( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueListString*)pCdmValue)->SetValue(((CdmValueListString*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDictStringInt:
          pCdmValue = new CdmValueDictStringInt( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          ((CdmValueDictStringInt*)pCdmValue)->SetValue(((CdmValueDictStringInt*)p_pCdmObjectValue)->GetValue());
          break;
        case eDmValueDictStringDouble:
          pCdmValue = new CdmValueDictStringDouble( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDictStringDouble*)pCdmValue)->SetValue(((CdmValueDictStringDouble*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDictStringString:
          pCdmValue = new CdmValueDictStringString( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDictStringString*)pCdmValue)->SetValue(((CdmValueDictStringString*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDictIntInt:
          pCdmValue = new CdmValueDictIntInt( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDictIntInt*)pCdmValue)->SetValue(((CdmValueDictIntInt*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDictIntDouble:
          pCdmValue = new CdmValueDictIntDouble( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueDictIntDouble*)pCdmValue)->SetValue(((CdmValueDictIntDouble*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueDictIntString:
          pCdmValue = new CdmValueDictIntString( p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          ((CdmValueDictIntString*)pCdmValue)->SetValue(((CdmValueDictIntString*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueListObjects:
          pCdmValue = new CdmValueListObjects(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueListObjects*)pCdmValue)->SetValue(((CdmValueListObjects*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueUser:
          pCdmValue = new CdmValueUser(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueUser*)pCdmValue)->SetValue(((CdmValueUser*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueUserGroup:
          pCdmValue = new CdmValueUserGroup(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueUserGroup*)pCdmValue)->SetValue(((CdmValueUserGroup*)p_pCdmObjectValue)->GetValue());
          break;
       case eDmValueEnum:
          pCdmValue = new CdmValueEnum(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
          ((CdmValueEnum*)pCdmValue)->SetValue(((CdmValueEnum*)p_pCdmObjectValue)->GetValue());
           break;
       case eDmValueFormula:
          pCdmValue = new CdmValueFormula(p_pCdmEventValue->GetSchemeId(), p_pCdmEventValue->GetMemberId(), p_pCdmEventValue->GetKeyname(), p_pCdmObject);
          pCdmValue->SetMemberId(p_pCdmEventValue->GetMemberId());
         break;
       default:
          FATAL( "Value does not exist in this switch operation" );
          break;
       }

       if (pCdmValue)
       {
           pCdmValue->SetEventValueNew(pEventObject);
       }
    }

    return pCdmValue;
}

void CdmValue::SetMemberId(long p_lId)
{
   m_lMemberId = p_lId;
}

long CdmValue::GetMemberId() const
{
   return m_lMemberId;
}

bool CdmValue::IsMustValue() const
{
   bool bRet = false;

   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember))
   {
      bRet = pMember->IsMust();
   }

   return bRet;
}

bool CdmValue::HasValue() const
{
   return true;
}

void CdmValue::ValueChanged()
{
   SetModified();

   if (CHKPTR(m_rpCdmObject))
   {
       m_rpCdmObject->SetModified();
   }

   emit ValueChanged(this);
}

int CdmValue::DeleteValue()
{
   int iRet = CdmLogging::eDmUnknownValueError;
   if(!IsMustValue())
   {
      emit ValueChanged(this);
      iRet = EC(eDmTrue);
   }
   else
   {
      iRet = EC(eDmMustValueDeletion);
      ERR( "Value Could not be deleted because it is a must value." );
   }

   return iRet;
}

QString CdmValue::GetKeyname() const
{
   QString qstrKeyname;
   const CdmMember* pMember = GetMember();

   if (pMember) // member could be deleted meanwhile
   {
      qstrKeyname = pMember->GetKeyname();
   }

   return qstrKeyname;
}

QString CdmValue::GetEventValueKeyname(CdmValue *pCdmEventValue) const
{
    QString qstrKeyname;

    const CdmMember* pMember = pCdmEventValue->GetMember();

    if(pMember)
    {
        qstrKeyname = pMember->GetKeyname();
    }

    return qstrKeyname;
}

void CdmValue::SetKeyname(QString p_qstrKeyname)
{
   Q_UNUSED(p_qstrKeyname);
   ERR("Calling this method makes no sense because the value uses in every case the memberkeyname!!");
}

EdmValueType CdmValue::GetValueType() const
{
   EdmValueType eValue = eDmValueNone;
   const CdmMember* pMember = GetMember();

   if (pMember)
   {
      eValue = pMember->GetValueType();
   }

   return eValue;
}

EdmValueType CdmValue::GetEvenValueType(const CdmObject *pEventObject) const
{
    EdmValueType eValue = eDmValueNone;
    if(pEventObject)
    {
        const CdmMember* pMember = GetEventMember(pEventObject);
        if(pMember)
        {
            eValue = pMember->GetValueType();
        }
    }

    return eValue;
}

long CdmValue::GetSize() const
{
   long lRet = 0;
   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember))
   {
      lRet = pMember->GetSize();
   }

   return lRet;
}

const CdmObject* CdmValue::GetObject() const
{
    // never use such a silly method name
    //DEPRECATED
    return m_rpCdmObject;
}

const CdmObject* CdmValue::GetDataObject() const
{
    return m_rpCdmObject;
}

const CdmMember* CdmValue::GetMember() const
{
   const CdmMember* pCdmMember = nullptr;
   const CdmObject* pCdmObject = (const_cast<CdmValue*>(this))->GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmClass* pCdmClass = pCdmObject->GetClass();

      if(CHKPTR(pCdmClass))
      {
         pCdmMember = const_cast<CdmMember*>(pCdmClass->FindMember(m_lMemberId));
      }
   }

   return pCdmMember;
}

const CdmMember* CdmValue::GetEventMember(const CdmObject *pEventObject) const
{
    const CdmMember* pCdmMember = nullptr;

    if(CHKPTR(pEventObject))
    {
        CdmClass *pClass = pEventObject->GetClass();

        if(CHKPTR(pClass))
        {
            pCdmMember = const_cast<CdmMember*>(pClass->FindMember(m_lMemberId));
        }
    }

    return pCdmMember;
}

bool CdmValue::IsOwner() const
{
   bool bRet = false;
   const CdmMember* pCdmMember = GetMember();

   if(CHKPTR(pCdmMember) && pCdmMember->IsOwner())
   {
      bRet = true;
   }

   return bRet;
}

bool CdmValue::IsUnique() const
{
   bool bRet = false;
   const CdmMember* pCdmMember = GetMember();

   if(CHKPTR(pCdmMember) && pCdmMember->IsUnique())
   {
      bRet = true;
   }

   return bRet;
}

void CdmValue::XmlExportValue(QDomElement& p_rqdeValue) const
{
   XmlExportBase(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_MEMBERID,  QString::number(m_lMemberId));
}

void CdmValue::XmlImportValue(QDomElement& p_rqDomElement)
{
   m_lMemberId = p_rqDomElement.attribute(WMS_MEMBERID, "-1").toInt();
}

int CdmValue::FromStringToValue(QString p_qstrValue)
{
   Q_UNUSED(p_qstrValue);
   ERR("Wrong Type for this method!!!");
   return EC(eDmUnknownValueError);
}

QString CdmValue::GetInfo() const
{
   QString qstrRet;

   qstrRet = CdmModelElement::GetInfo();
   qstrRet += "\n\n";

   qstrRet += "Value Informations:\n";
   
   qstrRet += "Object:      ";

   if (m_rpCdmObject)
   {
      qstrRet += m_rpCdmObject->GetKeyname() + " / " + m_rpCdmObject->GetCaption() + "\n";
   }
   else
   {
      qstrRet += "nullptr\n";
   }

   qstrRet += "Value:       " + GetDisplayString();
   qstrRet += "Valuetype:   " + QString::number(GetValueType()) + "\n";
   qstrRet += "Size:        " + QString::number(GetSize()) + "\n";
   qstrRet += "Member:      " + QString::number(m_lMemberId) + "\n";
   qstrRet += "Has Value:   ";

   if (HasValue())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }

   qstrRet += "Must Value:  ";

   if (IsMustValue())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }
   

   return qstrRet;
}

QVariant CdmValue::GetVariant() const
{
   QVariantMap qmVariant;

   qmVariant = CdmModelElement::GetVariant().toMap();
   qmVariant.insert("MemberId", (int)m_lMemberId);

   if (IsInDeploymentMode())
   {
      const CdmObject* pObject = CdmValue::GetObject();

      if (CHKPTR(pObject))
      {
         const CdmClass* pClass = pObject->GetClass();

         if (CHKPTR(pClass))
         {
            const CdmMember* pMember = pClass->FindMember(m_lMemberId);

            if (CHKPTR(pMember))
            {
                qmVariant.insert(WMS_MEMBERURI, pMember->GetUriInternal());
                qmVariant.insert(WMS_CLASSURI, pClass->GetUriInternal());
            }
         }
      }
   }

   return qmVariant;
}

bool CdmValue::IsValue() const
{
   return true;
}

QString CdmValue::GetUri() const
{
   QString qstrUri;
   const CdmObject* pObject = GetObject();

   if (CHKPTR(pObject))
   {
      qstrUri = CreateUri(WMS_VALUE, pObject->GetObjectContainer()->GetKeyname(), pObject->GetKeyname(), GetKeyname());
   }

   return qstrUri;
}

QString CdmValue::GetUriInternal() const
{
    QString qstrUri;
    const CdmObject* pObject = GetObject();

    if (CHKPTR(pObject))
    {
       const CdmObjectContainer* pObjectContainer = pObject->GetObjectContainer();
       if (CHKPTR(pObjectContainer)){
            qstrUri = CreateUriPath(WMS_VALUE, pObjectContainer->GetKeyname(), pObject->GetKeyname(), GetKeyname());
       }
    }

    return qstrUri;
}

void CdmValue::SetNew()
{
   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember) && pMember->IsPersistent())
   {
      CdmModelElement::SetNew();
   }
}

void CdmValue::SetEventValueNew(const CdmObject *pEventObject)
{
    const CdmMember *pMember = GetEventMember(pEventObject);

    if (CHKPTR(pMember) && pMember->IsPersistent())
    {
       CdmModelElement::SetNew();
    }
}

void CdmValue::SetModified()
{
    if (CHKPTR(m_rpCdmObject))
    {
        CdmClass *pClass = m_rpCdmObject->GetClass();
        if(!pClass->IsEventSourcingActive() ||
                !pClass->IsEventClass())
        {
            const CdmMember* pMember = GetMember();

            if (pMember && pMember->IsPersistent())
            {
                CdmModelElement::SetModified();
            }
            else if(!pMember)
            {
                ERR("Value Member not found. Keyname: " + GetKeyname());
            }
        }
        else
        {
            CdmModelElement::SetModified();
        }
    }
    else
    {
        CdmModelElement::SetModified();
    }
}

bool CdmValue::ResolveValue()
{
   return true;
}
