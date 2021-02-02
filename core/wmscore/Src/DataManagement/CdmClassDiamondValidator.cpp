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
#include <QMap>
#include <qcoreapplication.h>

// own Includes
#include "CdmClass.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmClassMethod.h"
#include "CdmClassValidator.h"
#include "CdmMessageManager.h"
#include "CdmClassDiamondValidator.h"

//************************************
// Method:    CdmClassDiamondValidator
// FullName:  CdmClassDiamondValidator::CdmClassDiamondValidator
// Access:    public 
// Qualifier: : m_rpClass(p_pClass)
// Parameter: CdmClass * p_pClass
//************************************
CdmClassDiamondValidator::CdmClassDiamondValidator(CdmClass* p_pClass)
: m_rpClass(p_pClass)
{
   // nothing to do here
}

//************************************
// Method:    ~CdmClassDiamondValidator
// FullName:  CdmClassDiamondValidator::~CdmClassDiamondValidator
// Access:    virtual public 
//************************************
CdmClassDiamondValidator::~CdmClassDiamondValidator()
{

}

//************************************
// Method:    Validate
// FullName:  CdmClassDiamondValidator::Validate
// Access:    public static 
// Returns:   bool
// Qualifier:
//************************************
bool CdmClassDiamondValidator::Validate()
{
   bool bRet = false;

   if (CHKPTR(m_rpClass))
   {
      if (m_rpClass->GetBaseClasses().count() == 0)
      {
         bRet = true;
      }
      else 
      {
         bRet = true; // changing default because it is easier
         bool success = ValidateMembers();

         if (!success)
         {
            bRet = false;
         }

         success = ValidateMethods();

         if (!success)
         {
            bRet = false;
         }
      }
   }

   if (!bRet)
   {
      ERR(QCoreApplication::tr("Fehlschlag der Diamantenprüfung zur Mehrfachvererbung\n ") + 
                                  m_qstrErrorMessage);
   }

   return bRet;
}




bool CdmClassDiamondValidator::ValidateMembers()
{
   bool bRet = false;

   if (CHKPTR(m_rpClass))
   {
      QMap<long,long> qmBaseClasses = m_rpClass->GetBaseClasses();
      QMap<long,CdmMember*> qmClassMembers =  m_rpClass->GetClassMemberMap();
      bRet = ValidateBaseClassesMembers(m_rpClass, qmClassMembers);
   }

   return bRet;
}

bool CdmClassDiamondValidator::ValidateBaseClassesMembers(CdmClass* p_pClass, QMap<long,CdmMember*>& p_qmExistingMembers)
{
   bool bRet = false;
   QMap<long,long> qmBaseClasses = p_pClass->GetBaseClasses();
   
   QMap<long,long>::iterator qmIt = qmBaseClasses.begin();
   QMap<long,long>::iterator qmItEnd = qmBaseClasses.end();
   bool bCheckResult = true;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClass* pClass = FindClassById(qmIt.key());

      if (CHKPTR(pClass))
      {
         bCheckResult = ValidateBaseClassMembers(pClass, p_qmExistingMembers);

         if (!bCheckResult)
         {
            bRet = false;
            // don't break the process because it would cause in salami tactics ;-)
         }

      }
   }

   return bRet;
}

bool CdmClassDiamondValidator::ValidateBaseClassMembers(CdmClass* p_pClass, QMap<long,CdmMember*>& p_qmExistingMembers)
{
   bool bRet = false;

   if (p_pClass->GetBaseClasses().count() > 0)
   {
      bRet = ValidateBaseClassesMembers(p_pClass, p_qmExistingMembers);
   }

   QMap<long,CdmMember*> qmBaseClassMembers =  p_pClass->GetClassMemberMap();      


   QMap<long,CdmMember*>::iterator qmIt = qmBaseClassMembers.begin();
   QMap<long,CdmMember*>::iterator qmItEnd = qmBaseClassMembers.end();
    bool bCheckResult = true;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pMember = qmIt.value();

      if (CHKPTR(pMember))
      {
         bCheckResult = CheckMember(pMember, p_qmExistingMembers);

         if (!bCheckResult)
         {
            bRet = false;
            // don't break the process because it would cause in salami tactics ;-)
         }
      }
   }

   return bRet;
}

bool CdmClassDiamondValidator::CheckMember(CdmMember* p_pMember, QMap<long,CdmMember*>& p_qmExistingMembers)
{
   bool bRet = true;
   bool bInsert = true;

   QMap<long,CdmMember*>::iterator qmIt = p_qmExistingMembers.begin();
   QMap<long,CdmMember*>::iterator qmItEnd = p_qmExistingMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pMember = qmIt.value();

      if (pMember->GetKeyname() == p_pMember->GetKeyname() &&
          pMember->GetValueType() != p_pMember->GetValueType())
      {
         m_qstrErrorMessage += 
            QCoreApplication::tr("Der Member %1 ist bereits it gleichen Namen und unterschiedlicher Signatur enthalten. Klasse: %2\n")
            .arg(p_pMember->GetKeyname())
            .arg(p_pMember->GetClass()->GetKeyname());
         bRet = false;
         break;
      }
      else if (pMember->GetKeyname() == p_pMember->GetKeyname())
      {
         bInsert = false;
      }  
   }

   if (bRet && bInsert)
   {
      p_qmExistingMembers.insert(p_pMember->GetId(), p_pMember);
   }

   return bRet;
}

CdmClass* CdmClassDiamondValidator::FindClassById(long p_lId)
{
   CdmClass* pClass = nullptr;
   CdmClassManager* pClassManager = m_rpClass->GetClassManager();

   if (CHKPTR(pClassManager))
   {
      pClass = pClassManager->FindClassById(p_lId);
   }

   return pClass;
}

bool CdmClassDiamondValidator::ValidateMethods()
{
   bool bRet = false;

   if (CHKPTR(m_rpClass))
   {
      QMap<long,long> qmBaseClasses = m_rpClass->GetBaseClasses();
      QMap<QString, CdmClassMethod*> qmClassMethods =  m_rpClass->GetMethods();
      bRet = ValidateBaseClassesMethods(m_rpClass, qmClassMethods);
   }

   return bRet;
}

bool CdmClassDiamondValidator::ValidateBaseClassesMethods(CdmClass* p_pClass, QMap<QString,CdmClassMethod*>& p_qmExistingMethods)
{
   bool bRet = false;
   QMap<long,long> qmBaseClasses = p_pClass->GetBaseClasses();

   QMap<long,long>::iterator qmIt = qmBaseClasses.begin();
   QMap<long,long>::iterator qmItEnd = qmBaseClasses.end();
   bool bCheckResult = true;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClass* pClass = FindClassById(qmIt.key());

      if (CHKPTR(pClass))
      {
         bCheckResult = ValidateBaseClassMethods(pClass, p_qmExistingMethods);

         if (!bCheckResult)
         {
            bRet = false;
            // don't break the process because it would cause in salami tactics ;-)
         }

      }
   }

   return bRet;
}

bool CdmClassDiamondValidator::ValidateBaseClassMethods(CdmClass* p_pClass, QMap<QString,CdmClassMethod*>& p_qmExistingMethods)
{
   bool bRet = false;

   if (p_pClass->GetBaseClasses().count() > 0)
   {
      bRet = ValidateBaseClassesMethods(p_pClass, p_qmExistingMethods);
   }

   QMap<QString,CdmClassMethod*> qmBaseClassMethods =  p_pClass->GetMethods();


   QMap<QString,CdmClassMethod*>::iterator qmIt = qmBaseClassMethods.begin();
   QMap<QString,CdmClassMethod*>::iterator qmItEnd = qmBaseClassMethods.end();
   bool bCheckResult = true;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClassMethod* pMethod = qmIt.value();

      if (CHKPTR(pMethod))
      {
         bCheckResult = CheckMethod(pMethod, p_qmExistingMethods);

         if (!bCheckResult)
         {
            bRet = false;
            // don't break the process because it would cause in salami tactics ;-)
         }
      }
   }

   return bRet;
}

bool CdmClassDiamondValidator::CheckMethod(CdmClassMethod* p_pMethod, QMap<QString,CdmClassMethod*>& p_qmExistingMethods)
{
   bool bRet = true;
   bool bInsert = true;

   QMap<QString,CdmClassMethod*>::iterator qmIt = p_qmExistingMethods.begin();
   QMap<QString,CdmClassMethod*>::iterator qmItEnd = p_qmExistingMethods.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClassMethod* pMethod = qmIt.value();

      if (pMethod->GetMethodName() == p_pMethod->GetMethodName() &&
         pMethod->GetParametersAsStringForFunction() != pMethod->GetParametersAsStringForFunction())
      {
          CdmClass* pClass = pMethod->GetClass();
          CdmClass* pPossiblyDerivedClass = p_pMethod->GetClass();

          if (CHKPTR(pClass) && CHKPTR(pPossiblyDerivedClass))
          {
              if (!pPossiblyDerivedClass->IsInherited(pClass->GetId()))
              {
                  m_qstrErrorMessage +=
                     QCoreApplication::tr("Der Methode %1 ist bereits mit gleichen Namen und unterschiedlicher Signatur enthalten. Klasse: %2\n")
                     .arg(pMethod->GetMethodName())
                     .arg(pMethod->GetClass()->GetKeyname());
                  bRet = false;
              }
          }
          else
          {
              m_qstrErrorMessage +=
                 QCoreApplication::tr("Methoden zu Klassenzuordnung nicht gefunden. Diamantenprüfung kann nicht durchgeführt werden.\n Methode: %1")
                 .arg(pMethod->GetMethodName());
              bRet = false;
          }

         break;
      }
   }

   if (bRet && bInsert)
   {
      p_qmExistingMethods.insert(p_pMethod->GetMethodName(), p_pMethod);
   }

   return bRet;
}


//************************************
// Method:    Validate
// FullName:  CdmClassDiamondValidator::Validate
// Access:    public static 
// Returns:   bool
// Qualifier:
// Parameter: CdmClass * p_pClass
//************************************
bool CdmClassDiamondValidator::Validate( CdmClass* p_pClass )
{
   CdmClassDiamondValidator validator(p_pClass);
   return validator.Validate();
}
