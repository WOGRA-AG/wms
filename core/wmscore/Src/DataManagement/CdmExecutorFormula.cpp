/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmExecutorFormula.cpp
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
#include <QScriptSyntaxCheckResult>
#include <QScriptProgram>
#include <QScriptEngine>

// own Includes
#include "CsaFactory.h"
#include "IwmsPluginInterface.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
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
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmExecutorFormula.h"


CdmExecutorFormula::CdmExecutorFormula(CdmExecutor* p_pExecutor)
: m_rpExecutor(p_pExecutor)
{
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012----------*
 * @method  CdmExecutorFormula::~CdmExecutorFormula                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmExecutorFormula                                                   *
 *----------------last changed: --------------------------------Mi 19. Sep 14:18:59 2012----------*/
CdmExecutorFormula::~CdmExecutorFormula()
{
}

QVariant CdmExecutorFormula::EvaluateFormula(const CdmObject* p_pCdmObject, QString p_qstrFormula)
{
   QVariant qvRet;

   if (CHKPTR(p_pCdmObject))
   {

     CreateEngine();
     IdmExecutorEngine* pEngine = GetEngine();

     if (CHKPTR(pEngine))
     {
         if (pEngine->SyntaxCheck(p_qstrFormula))
         {
            GetPreProcessor()->AddObjectValuesToEngine(const_cast<CdmObject*>(p_pCdmObject), true);
            qvRet = pEngine->Evaluate(p_qstrFormula, "Formula");
            pEngine->HasUncaughtExceptions(); // Error handling
         }
     }
   }

   return qvRet;
}
