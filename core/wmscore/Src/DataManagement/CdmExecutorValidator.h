/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmExecutorValidator.h
 ** Started Implementation: 2013/11/15
 ** Description:
 ** 
 ** Implements the executor for functions and validations in Objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMEXECUTORVALIDATOR_H
#define CDMEXECUTORVALIDATOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QScriptEngine>
#include <QScriptValue>

// Own Includes
#include "CdmExecutorBase.h"
#include "datamanager.h"

// Forwards
class QScriptEngineDebugger;
class CdmModelElement;
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class CdmClassValidator;
class CdmClassMethod;
class CdmValue;
class CdmMember;
class QScriptProgram;
class QScriptContext;
class IwmsPluginInterface;
class CdmExecutor;
// TypeDefs


/* 
 * This class implements the executor for functions and validations in Objects
 */
class WMSMANAGER_API CdmExecutorValidator : public CdmExecutorBase
{

   private:
      CdmExecutor* m_rpExecutor;
   
   public:

    CdmExecutorValidator(CdmExecutor* p_pExecutor);

   public:
    virtual ~CdmExecutorValidator();

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:22:40 2012-------*
    * @method  CdmExecutorValidator::ExecuteValidation                // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:22:40 2012----------*/
    static bool ExecuteValidation(CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Do 20. Sep 10:48:16 2012-------*
    * @method  CdmExecutorValidator::Validate                         // public, slots                     *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 10:48:16 2012----------*/
bool Validate( CdmObject* p_pCdmObject);


    public slots:
         /** +-=---------------------------------------------------------Do 20. Sep 10:48:43 2012-------*
    * @method  CdmExecutorValidator::Validate                         // public, slots                     *
    * @return  bool                                          //                                   *
    * @param   CdmObjectContainer* p_pCdmObejctList               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 10:48:43 2012----------*/
bool Validate( CdmObjectContainer* p_pCdmObejctList);

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:39:02 2012-------*
    * @method  CdmExecutorValidator::ExecuteValidation                // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:39:02 2012----------*/
    static bool ExecuteValidation(CdmObjectContainer* p_pContainer);

   private:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:56:03 2012-------*
    * @method  CdmExecutorValidator::MemberValidation                 // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:56:03 2012----------*/
    bool MemberValidation(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 10:21:32 2013-------*
    * @method  CdmExecutorValidator::Validate                         // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 10:21:32 2013----------*/
    bool Validate(CdmValue* p_pCdmValue, const CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Mi 19. Sep 15:04:50 2012-------*
    * @method  CdmExecutorValidator::CheckUnique                      // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 15:04:50 2012----------*/
    bool CheckUnique(CdmValue* p_pCdmValue);

   private:
   /** +-=---------------------------------------------------------Mi 19. Sep 15:09:31 2012-------*
    * @method  CdmExecutorValidator::CheckMemberValidation            // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 15:09:31 2012----------*/
    bool CheckMemberValidation(CdmValue* p_pCdmValue);

   private:
   /** +-=---------------------------------------------------------Mi 19. Sep 15:49:08 2012-------*
    * @method  CdmExecutorValidator::ClassValidation                  // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 15:49:08 2012----------*/
    bool ClassValidation(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Mi 19. Sep 15:55:41 2012-------*
    * @method  CdmExecutorValidator::Validate                         // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   CdmClassValidator* p_pCdmValidator            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 15:55:41 2012----------*/
    bool Validate(CdmObject* p_pCdmObject, CdmClassValidator* p_pCdmValidator);

    bool CheckSize(CdmValue* p_pCdmValue);
    bool CheckMust( const CdmMember* p_pCdmMember, CdmValue* p_pCdmValue);

private:
    bool ClassValidation(CdmObject *p_pCdmObject, CdmClass *p_pClass);
};

#endif //
