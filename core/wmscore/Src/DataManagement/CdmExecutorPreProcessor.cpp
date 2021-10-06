/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmExecutorPreProcessor.cpp
 ** Started Implementation: 2012/11/12
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QCoreApplication>
#include <QScriptContextInfo>

// own Includes
#include "CdmValue.h"
#include "CdmValueBool.h"
#include "CdmValueInt.h"
#include "CdmValueFloat.h"
#include "CdmValueDouble.h"
#include "CdmValueString.h"
#include "CdmValueObjectRef.h"
#include "CdmValueContainerRef.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueDateTime.h"
#include "CdmValueDate.h"
#include "CdmValueTime.h"
#include "CdmValueLong.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmClassValidator.h"
#include "CdmClassMethod.h"
#include "CdmMessageManager.h"
#include "CsaFactory.h"
#include "CdmExecutorBase.h"
#include "CdmExecutor.h"
#include "CdmExecutorRuntime.h"
#include "CdmExecutorRuntimeManager.h"
#include "CdmExecutorAddOnManager.h"
#include "IdmExecutorEngine.h"
#include "CdmExecutorPreProcessor.h"


CdmExecutorPreProcessor::CdmExecutorPreProcessor(CdmExecutorBase* p_rpExecutor)
:  m_rpExecutor(p_rpExecutor)
{
   // nothing to do here
}

CdmExecutorPreProcessor::~CdmExecutorPreProcessor()
{
}

QString CdmExecutorPreProcessor::GenerateScriptCode(CdmClassMethod* p_pMethod)
{
   QString qstrCode;

   if (CHKPTR(p_pMethod))
   {
      QString qstrArguments = p_pMethod->GetParametersAsStringForFunction();
      qstrCode = "function " + GenerateMethodName(p_pMethod) + "("+ qstrArguments + ")\n";
      qstrCode += "{\n";
      qstrCode += p_pMethod->GetSourceCode() + "\n";
      qstrCode += "}\n";
   }

   return qstrCode;
}

QString CdmExecutorPreProcessor::GenerateScriptCode(QString p_qstrMethodName, QString p_qstrCode)
{
   QString qstrCode;
   qstrCode = "function " + p_qstrMethodName + "()\n";
   qstrCode += "{\n";
   qstrCode += p_qstrCode + "\n";
   qstrCode += "}\n";
   return qstrCode;
}


void CdmExecutorPreProcessor::AddObjectValuesToEngine(CdmObject* p_pCdmObject, bool p_bFormula)
{
   if (p_pCdmObject)
   {
      if (!p_bFormula)
      {
         m_rpExecutor->GetFactory()->createThisScriptObject(p_pCdmObject);
      }
      else
      {
         m_rpExecutor->GetFactory()->createFormulaScriptObject(p_pCdmObject);
      }
   }
}

QString CdmExecutorPreProcessor::GenerateMethodName(CdmClassMethod* p_pMethod)
{
    CdmClass* pClass = p_pMethod->GetClass();
    QString qstrClass = pClass->GetKeyname();
    qstrClass = qstrClass.simplified();
    return qstrClass + "_" + p_pMethod->GetMethodName();
}

QVariantList CdmExecutorPreProcessor::AskForParameters(CdmClassMethod* p_pMethod)
{
   QVariantList qmRet;

   if (CHKPTR(p_pMethod))
   {
      QList<CdmClassMethodParameter> qmParams = p_pMethod->GetParameters();
      qmRet = CdmMessageManager::AskForParameters(qmParams);
   }

   return qmRet;
}

bool CdmExecutorPreProcessor::SyntaxCheck(IdmExecutorEngine* p_pEngine, CdmClassMethod* p_pCdmMethod)
{
   bool bRet = false;

   if (CHKPTR(p_pCdmMethod) && CHKPTR(p_pEngine))
   {
      QString qstrCode = GenerateScriptCode(p_pCdmMethod->GetMethodName(), 
                                            p_pCdmMethod->GetSourceCode());
      bRet = p_pEngine->SyntaxCheck(qstrCode);
   }

   return bRet;
}

QString CdmExecutorPreProcessor::PreProcessValidation(CdmObject* p_pObject, CdmClassValidator* p_pValidator, IdmExecutorEngine& p_rEngine)
{
    AddObjectValuesToEngine(p_pObject);
    QString qstrClassKeyname = p_pObject->GetClass()->GetKeyname();
    QString qstrValidatorName = GenerateValidatorFunctionName(qstrClassKeyname, p_pValidator);
    QVariant qsValue = p_rEngine.GetProperty(qstrValidatorName);

    if (!qsValue.isValid())
    {
        QString qstrCode = GenerateScriptCode(p_pValidator, qstrClassKeyname);
        p_rEngine.Evaluate(qstrCode, qstrClassKeyname);
    }

    return qstrValidatorName;
}

QString CdmExecutorPreProcessor::PreProcessValidation(CdmValue* p_pValue, QString p_qstrCode, IdmExecutorEngine& p_rEngine)
{
    p_rEngine.SetProperty(p_pValue, "value");
    QString qstrValidatorName = GenerateMemberValidatorFunctionName(p_pValue);
    QVariant qsValue = p_rEngine.GetProperty(qstrValidatorName);

    if (!qsValue.isValid())
    {
        QString qstrCode = GenerateScriptCode(qstrValidatorName, p_qstrCode);
        p_rEngine.Evaluate(qstrCode, qstrValidatorName);
    }

    return qstrValidatorName;
}


QString CdmExecutorPreProcessor::GenerateScriptCode(CdmClassValidator* p_pValidator, QString p_qstrClassName)
{
    QString qstrResult;
    QString qstrCode = p_pValidator->GetCode();
    QString qstrName = GenerateValidatorFunctionName(p_qstrClassName, p_pValidator);
    qstrResult = GenerateScriptCode(qstrName, qstrCode);
    return qstrResult;
}

QString CdmExecutorPreProcessor::GenerateValidatorFunctionName(QString p_qstrClassName, CdmClassValidator* p_pValidator)
{
    return p_qstrClassName + "_" + p_pValidator->GetName();
}

QString CdmExecutorPreProcessor::GenerateMemberValidatorFunctionName(CdmValue* p_pValue)
{
    QString qstrValidatorName = p_pValue->GetMember()->GetClass()->GetKeyname();
    qstrValidatorName += "_" + p_pValue->GetMember()->GetKeyname();
    qstrValidatorName += "_Validator";
    return qstrValidatorName;
}


bool CdmExecutorPreProcessor::ExceptionCheck(IdmExecutorEngine& p_rEngine)
{
    bool bRet = true;

    if (p_rEngine.HasUncaughtExceptions())
    {
       bRet = false;
    }

    return bRet;
}

void CdmExecutorPreProcessor::PrepareObjects(IdmExecutorEngine& p_rEngine, CdmModelElement* p_pCdmBase)
{
    CdmExecutorRuntimeManager* pRuntimeManager = CdmExecutor::GetExecutor()->GetRuntimeManager();

    if (CHKPTR(pRuntimeManager))
    {
        CdmExecutorRuntime* pRuntime = pRuntimeManager->GetRuntime(&p_rEngine);

        if (CHKPTR(pRuntime))
        {
            CdmObject* pObject = static_cast<CdmObject*>(p_pCdmBase);

            if (pRuntime->NeedsCurrentThisObjectUpdate(pObject))
            {
                if (pRuntime->IsScriptRunning())
                {
                    pRuntime->AddCurrentObjectToCommit();
                }

                AddObjectValuesToEngine(pObject);
            }
        }
    }
}

QString CdmExecutorPreProcessor::PreProcessFunction(CdmClassMethod* p_pMethod,
                                                    CdmModelElement* p_pCdmBase,
                                                    IdmExecutorEngine& p_rEngine)
{
    QString qstrCode = GenerateScriptCode(p_pMethod);
    QString qstrMethodName = GenerateMethodName(p_pMethod);
    PrepareObjects(p_rEngine, p_pCdmBase);

    if (p_pCdmBase || p_pMethod->IsStatic())
    {
       p_rEngine.Evaluate(qstrCode, qstrMethodName);

       if (p_rEngine.HasUncaughtExceptions())
       {
         ERR("Error occurred while evaluating script");
       }
    }
    else
    {
      ERR(qApp->tr("Funktion kann nicht ausgeführt werden.\nDie Funktion muss entweder statisch sein oder auf einem Objekt bzw. Objektliste ausgeführt werden."));
    }

    return qstrMethodName;
}

