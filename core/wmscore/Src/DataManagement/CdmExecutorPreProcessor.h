/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmExecutorPreProcessor.h
 ** Started Implementation: 2012/11/12
 ** Description:
 ** 
 ** implements the preprocessor for methods and validators
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMEXECUTORPREPROCESSOR_H
#define CDMEXECUTORPREPROCESSOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QList>

// Own Includes
#include "IdmExecutorEngine.h"
#include "datamanager.h"

// Forwards
class CdmClass;
class CdmClassValidator;
class CdmClassMethod;
class CdmExecutorBase;
class CdmModelElementBase;
class CdmModelElement;
class CdmValue;
class CdmObject;

// TypeDefs


/* 
 * This class implements the preprocessor for methods and validators
 */
class WMSMANAGER_API CdmExecutorPreProcessor
{
   private:
      CdmExecutorBase* m_rpExecutor;

      QString GenerateScriptCode(CdmClassValidator *p_pValidator, QString p_qstrClassName);
      QString GenerateScriptCode(CdmClassMethod *p_pValidator);
      QString PreProcessFunction(CdmClassMethod *p_pMethod, 
                                 CdmModelElement *p_pCdmBase, 
                                 IdmExecutorEngine &p_rEngine,
                                 QVariantList p_qlParams);

      QString GenerateMethodName(CdmClassMethod *p_pMethod);

public:
    CdmExecutorPreProcessor(CdmExecutorBase* p_rpExecutor);
    virtual ~CdmExecutorPreProcessor( );
    QString GenerateValidatorFunctionName(QString p_qstrClassName, CdmClassValidator *p_pValidator);

    QString GenerateScriptCode(QString p_qstrName, QString p_qstrCode);
    void AddObjectValuesToEngine(CdmObject* p_pCdmObject, bool p_bFormula = false);
    QVariantList AskForParameters(CdmClassMethod* p_pMethod);
    bool SyntaxCheck(IdmExecutorEngine* p_pEngine, CdmClassMethod* p_pCdmMethod);
    QString PreProcessValidation(CdmObject *p_pObject, CdmClassValidator *p_pValidator, IdmExecutorEngine &p_rEngine);
    bool ExceptionCheck(IdmExecutorEngine &p_rEngine);
    QString GenerateMemberValidatorFunctionName(CdmValue *p_pValue);
    QString PreProcessValidation(CdmValue *p_pValue, QString p_qstrCode, IdmExecutorEngine &p_rEngine);
    QString PreProcessFunction(CdmClassMethod* p_pMethod, CdmModelElement* p_pCdmBase, IdmExecutorEngine& p_rEngine);
    void PrepareObjects(IdmExecutorEngine& p_rEngine, CdmModelElement* p_pCdmBase);


};

#endif //
