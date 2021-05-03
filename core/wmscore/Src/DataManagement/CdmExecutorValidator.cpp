/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmExecutorValidator.cpp
 ** Started Implementation: 2012/09/19
 ** Description:
 **
 ** Implements the executor for functions and validations in Objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QCoreApplication>
#include <QScriptProgram>

// own Includes
#include "CsaFactory.h"
#include "IwmsPluginInterface.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"
#include "CdmValue.h"
#include "CdmValueBool.h"
#include "CdmValueInt.h"
#include "CdmValueFloat.h"
#include "CdmValueDouble.h"
#include "CdmValueString.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueDateTime.h"
#include "CdmValueDate.h"
#include "CdmValueTime.h"
#include "CdmObjectContainer.h"
#include "CdmMember.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmValueObjectRef.h"
#include "CdmClassValidator.h"
#include "CdmValue.h"
#include "CdmExecutor.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmExecutorPreProcessor.h"
#include "IdmExecutorEngine.h"
#include "CdmExecutorValidator.h"


CdmExecutorValidator::CdmExecutorValidator(CdmExecutor* p_pExecutor)
: m_rpExecutor(p_pExecutor)
{
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012----------*
 * @method  CdmExecutorValidator::~CdmExecutorValidator                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmExecutorValidator                                                   *
 *----------------last changed: --------------------------------Mi 19. Sep 14:18:59 2012----------*/
CdmExecutorValidator::~CdmExecutorValidator()
{
}

/** +-=---------------------------------------------------------Do 20. Sep 10:48:16 2012----------*
 * @method  CdmExecutorValidator::Validate                            // public, slots                     *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 10:48:16 2012----------*/
bool CdmExecutorValidator::Validate(CdmObject* p_pCdmObject)
{
   bool bRet = false;

   if (CHKPTR(p_pCdmObject))
   {
      if (MemberValidation(p_pCdmObject))  
      {
         if (ClassValidation(p_pCdmObject))
         {
            bRet = true;
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 19. Sep 15:49:08 2012----------*
 * @method  CdmExecutorValidator::ClassValidation                     // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 15:49:08 2012----------*/
bool CdmExecutorValidator::ClassValidation(CdmObject* p_pCdmObject)
{
   bool bRet = true;

   if (CHKPTR(p_pCdmObject))
   {
      CdmClass* pCdmClass = p_pCdmObject->GetClass();
      bRet = ClassValidation(p_pCdmObject, pCdmClass);
   }

   return bRet;
}

///
/// \brief CdmExecutorValidator::ClassValidation
/// \param p_pCdmObject
/// \param p_pClass
/// \return success flag
///
/// checks all validations also baseclass validations
bool CdmExecutorValidator::ClassValidation(CdmObject* p_pCdmObject, CdmClass* p_pClass)
{
    bool bRet = true;

    if (CHKPTR(p_pCdmObject) && CHKPTR(p_pClass))
    {
        CdmClassManager* pClassManager = p_pClass->GetClassManager();
        const QMap<long,long> qmBaseClasses = p_pClass->GetBaseClasses();

        QMap<long,long>::const_iterator qmIt = qmBaseClasses.begin();
        QMap<long,long>::const_iterator qmItEnd = qmBaseClasses.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmClass* pBaseClass = pClassManager->FindClassById(qmIt.value());

            if (CHKPTR(pBaseClass))
            {
                bool bSuccess = ClassValidation(p_pCdmObject, pBaseClass);

                if (!bSuccess)
                {
                    bRet = false;
                }
            }
            else
            {
               ERR("Baseclass with ID " + QString::number(qmIt.key())+ " not found!");
            }
        }

        if (CHKPTR(p_pClass) && p_pClass->HasValidators())
        {
           QMap<QString, CdmClassValidator*> qmValidators = p_pClass->GetValidators();

           QMap<QString, CdmClassValidator*>::iterator qmIt = qmValidators.begin();
           QMap<QString, CdmClassValidator*>::iterator qmItEnd = qmValidators.end();

           for (; qmIt != qmItEnd; ++qmIt)
           {
              CdmClassValidator* pValidator = qmIt.value();

              if (CHKPTR(pValidator))
              {
                 bool bSuccess = Validate(p_pCdmObject, pValidator);

                 if (!bSuccess)
                 {
                     bRet = false;
                 }
              }
           }
        }
     }

     return bRet;
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:56:03 2012----------*
 * @method  CdmExecutor::MemberValidation                    // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 14:56:03 2012----------*/
bool CdmExecutorValidator::MemberValidation(CdmObject* p_pCdmObject)
{
   bool bRet = true;

   if (CHKPTR(p_pCdmObject))
   {
      CdmClass* pCdmClass = p_pCdmObject->GetClass();

      if (CHKPTR(pCdmClass))
      {
         QMap<QString, CdmValue*> qmMembers;
         p_pCdmObject->GetValueMap(qmMembers);

         QMap<QString, CdmValue*>::iterator qmIt = qmMembers.begin();
         QMap<QString, CdmValue*>::iterator qmItEnd = qmMembers.end();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            const CdmMember* pCdmMember = pCdmClass->FindMember(qmIt.key());
            CdmValue* pCdmValue = qmIt.value();

            if (pCdmValue->IsModified())
            {
                bRet = Validate(pCdmValue, pCdmMember);
            }

            if (!bRet)
            {
                break;
            }
         }
      }
   }

   return bRet;
}


/** +-=---------------------------------------------------------Mi 19. Sep 15:55:41 2012----------*
 * @method  CdmExecutorValidator::Validate                            // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   CdmClassValidator* p_pCdmValidator               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 15:55:41 2012----------*/
bool CdmExecutorValidator::Validate(CdmObject* p_pCdmObject, CdmClassValidator* p_pCdmValidator)
{
   bool bRet = true;

   if (CHKPTR(p_pCdmObject) && CHKPTR(p_pCdmValidator))
   {
      CdmExecutorPreProcessor* pPreProcessor = GetPreProcessor();
      QString qstrValidatorName;
      CreateEngine();
      IdmExecutorEngine* pEngine = GetEngine();

      if (pEngine)
      {
          if (pEngine->SyntaxCheck(p_pCdmValidator->GetCode()))
          {
            qstrValidatorName = pPreProcessor->PreProcessValidation(p_pCdmObject,
                                                                    p_pCdmValidator,
                                                                    *pEngine);

            QScriptValue qValue;
            bRet = pEngine->Call(qstrValidatorName).toBool();

           if (!bRet)
           {
               QString qstrMessage = qApp->tr(p_pCdmValidator->GetErrorMessage().toUtf8());
               ERR("Validation failed\n" + qstrMessage);
           }
          }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 11. Feb 10:21:32 2013----------*
 * @method  CdmExecutorValidator::Validate                            // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 10:21:32 2013----------*/
bool CdmExecutorValidator::Validate(CdmValue* p_pCdmValue, const CdmMember* p_pCdmMember)
{
   bool bRet = true;

   if ((p_pCdmValue) && (p_pCdmMember))
   {
      if (!CheckMust(p_pCdmMember, p_pCdmValue))
      {
         bRet = false;
      }

      if (!CheckUnique(p_pCdmValue))
      {
         bRet = false;
      }
         
      if (!CheckSize(p_pCdmValue))
      {
         bRet = false;
      }

      if (!CheckMemberValidation(p_pCdmValue))
      {
         bRet = false;
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 19. Sep 15:09:31 2012----------*
 * @method  CdmExecutorValidator::CheckMemberValidation               // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 15:09:31 2012----------*/
bool CdmExecutorValidator::CheckMemberValidation(CdmValue* p_pCdmValue)
{
   bool bRet = true;

   if (CHKPTR(p_pCdmValue))
   {
      const CdmMember* pMember = p_pCdmValue->GetMember();

      if (pMember)
      {
          QString qstrValidationCode = pMember->GetValidationCode();

          if (!qstrValidationCode.isEmpty() && pMember->IsValidationType())
          {
             CdmExecutorPreProcessor* pPreProcessor =  GetPreProcessor();

             if (!GetEngine())
             {
                 CreateEngine();
             }

             IdmExecutorEngine& qEngine = *GetEngine();
             if (qEngine.SyntaxCheck(qstrValidationCode))
             {
                QString qstrValidationName = pPreProcessor->PreProcessValidation(p_pCdmValue, qstrValidationCode, qEngine);
                QVariant qValue = qEngine.Evaluate(qstrValidationCode, qstrValidationName);

                if (!qEngine.HasUncaughtExceptions())
                {
                   bRet = qValue.toBool();

                   if (!bRet)
                   {
                      ERR(qApp->tr("Validierung fehlgeschlagen für Wert %1. Die Eingabeprüfung schlug fehl.\n Prüfung:\n%2").arg(p_pCdmValue->GetCaption()).arg(qstrValidationCode));
                   }
                }
             }
          }
      }
      else
      {
          QString qstrClassName = "<Class not found>";
          const CdmObject* pObject = p_pCdmValue->GetObject();

          if (CHKPTR(pObject))
          {
              const CdmClass* pClass = pObject->GetClass();

              if (CHKPTR(pClass))
              {
                  qstrClassName = pClass->GetKeyname();
              }
          }

          ERR("Member for Value "+ p_pCdmValue->GetKeyname() + " not found in class "  + qstrClassName + ".");
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 19. Sep 15:04:50 2012----------*
 * @method  CdmExecutorValidator::CheckUnique                         // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 15:04:50 2012----------*/
bool CdmExecutorValidator::CheckUnique(CdmValue* p_pCdmValue)
{
   bool bRet = true;

   if (p_pCdmValue->GetMember())
   {
       if (p_pCdmValue->GetMember()->IsUnique() && p_pCdmValue->GetValueType() != eDmValueFormula)
       {
          if (CHKPTR(p_pCdmValue))
          {
             const CdmObject* pCdmObject = p_pCdmValue->GetObject();

             if (CHKPTR(pCdmObject))
             {
                CdmObjectContainer* pCdmList = (const_cast<CdmObject*>(pCdmObject))->GetObjectContainer();

                if (CHKPTR(pCdmList))
                {
                   // now we can check if it is unique
                   QString qstrWql = QString("select from \"%1\" where %2 = \"%3\"")
                      .arg(pCdmList->GetKeyname())
                      .arg(p_pCdmValue->GetKeyname())
                      .arg(p_pCdmValue->GetValueAsString());

                   CdmQuery* pCdmQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

                   if(CHKPTR(pCdmQuery))
                   {
                       QList<long> qllResult = pCdmQuery->GetResultList();

                       if (qllResult.count() > 1)
                       {
                          bRet = false;
                       }
                       else if (qllResult.count() == 1 && (*(qllResult.begin())) != pCdmObject->GetId())
                       {
                          bRet = false;
                       }
                   } else {
                       bRet = false;
                   }

                   if (!bRet)
                   {
                       CdmMessageManager::critical(qApp->tr("Speichern nicht möglich."),
                                                   qApp->tr("Speichern nicht möglich. Feld %1 muss eindeutig sein.").arg(p_pCdmValue->GetCaption()));
                   }
                }
             }
          }
       }
    }
   return bRet;
}

/** +-=---------------------------------------------------------Do 20. Sep 10:48:43 2012----------*
 * @method  CdmExecutorValidator::Validate                            // public, slots                     *
 * @return  bool                                             //                                   *
 * @param   CdmObjectContainer* p_pCdmObjectList                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 10:48:43 2012----------*/
bool CdmExecutorValidator::Validate(CdmObjectContainer* p_pCdmObjectList)
{
   bool bRet = true;

   if (CHKPTR(p_pCdmObjectList))
   {
      const CdmClass* pCdmClass = p_pCdmObjectList->GetClass();

      if (CHKPTR(pCdmClass))
      {
         QList<CdmObject*> qllList = p_pCdmObjectList->GetNewModifiedList();
         QList<CdmObject*>::iterator qllIt = qllList.begin();
         QList<CdmObject*>::iterator qllItEnd = qllList.end();

         for (; qllIt != qllItEnd; ++qllIt)
         {
            CdmObject* pCdmObject = *qllIt;

            if (pCdmObject && (pCdmObject->IsNew() || pCdmObject->IsModified()))
            {
               bRet = Validate(pCdmObject);

               if (!bRet)
               {
                  break;
               }
            }
         }
      }
   }

   return bRet;
}

bool CdmExecutorValidator::CheckMust( const CdmMember* p_pCdmMember, CdmValue* p_pCdmValue)
{
   bool bRet = true;

   if (p_pCdmValue->GetValueType() != eDmValueFormula)
   {
      if (p_pCdmMember->IsMust() && !p_pCdmValue->HasValue())
      {
         const CdmClass* pClass = p_pCdmMember->GetClass();
         if (CHKPTR(pClass))
         {
            bRet = false;
            CdmMessageManager::critical(qApp->tr("Speichern nicht möglich."),
                                        qApp->tr("Speichern nicht möglich. Pflichtfeld wurde nicht ausgefüllt: ")+ p_pCdmValue->GetCaption() + qApp->tr(" Datenklasse: ") + pClass->GetKeyname());
         }
      }
   }
   return bRet;
}

bool CdmExecutorValidator::CheckSize(CdmValue* p_pCdmValue)
{
   bool bRet = true;
   if (p_pCdmValue->GetValueType() == eDmValueString ||
	   p_pCdmValue->GetValueType() == eDmValueCharacterDocument)
   {
	   int iSize = p_pCdmValue->GetSize();
      if(iSize > 0 && iSize < p_pCdmValue->GetDisplayString().length())
      {
         bRet = false;
         CdmMessageManager::critical(qApp->tr("Speichern nicht möglich."),
                                     qApp->tr("Speichern nicht möglich. Feldlänge überschritten Feld: ")+ p_pCdmValue->GetCaption());
      }
   }
   return bRet;
}


