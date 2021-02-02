/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmExecutorFormula.h
 ** Started Implementation: 2013/11/15
 ** Description:
 ** 
 ** Implements the executor for formulas in Objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMEXECUTORFORMULA_H
#define CDMEXECUTORFORMULA_H

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
#include "datamanager.h"
#include "CdmExecutorBase.h"
#include "CdmExecutor.h"

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
class CdmExecutor;
class IwmsPluginInterface;

// TypeDefs


/* 
 * This class implements the executor for functions and validations in Objects
 */
class WMSMANAGER_API CdmExecutorFormula : public CdmExecutorBase
{
    
    private:
      CdmExecutor* m_rpExecutor;


   public:
    CdmExecutorFormula(CdmExecutor* p_pExecutor);

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012-------*
    * @method  CdmExecutorFormula::~CdmExecutorFormula                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmExecutorFormula                                                *
    *----------------last changed: -----------------------------Mi 19. Sep 14:18:59 2012----------*/
    virtual ~CdmExecutorFormula( );

   public:
    QVariant EvaluateFormula(const CdmObject* p_pCdmObject, QString p_qstrFormula);

};

#endif // CdmExecutorFormula_H
