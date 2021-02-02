/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmExecutorFunction.h
 ** Started Implementation: 2013/11/15
 ** Description:
 ** 
 ** Implements the executor for formulas in Objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMEXECUTORFUNCTION_H
#define CDMEXECUTORFUNCTION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QScriptEngine>
#include <QVariant>

// Own Includes
#include "datamanager.h"
#include "CdmExecutorBase.h"
#include "CdmExecutorFunction.h"

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
class CdmExecutorRuntime;
class CdmClassManager;

// TypeDefs

// DEFINES


/* 
 * This class implements the executor for functions and validations in Objects
 */
class WMSMANAGER_API CdmExecutorFunction : public CdmExecutorBase
{

   private:
    bool m_bAllowAskForParameters;
    CdmExecutor* m_rpExecutor;
    bool m_bIsInitEvent;

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:17:10 2012-------*
    * @method  CdmExecutorFunction::CdmExecutorFunction                      // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:17:10 2012----------*/
    CdmExecutorFunction(CdmExecutor* p_pExecutor);

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012-------*
    * @method  CdmExecutorFunction::~CdmExecutorFunction                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmExecutorFunction                                                *
    *----------------last changed: -----------------------------Mi 19. Sep 14:18:59 2012----------*/
    virtual ~CdmExecutorFunction( );


    public slots:
   /** +-=---------------------------------------------------------So 25. Nov 12:22:10 2012-------*
    * @method  CdmExecutorFunction::ExecuteObject                    // public, slots                     *
    * @return  QVariant                                      //                                   *
    * @param   QString p_qstrFunction                        //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QVariantList p_qlParameters                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 25. Nov 12:22:10 2012----------*/
QVariant ExecuteObject( QString p_qstrFunction,
                        CdmObject* p_pCdmObject,
                        QVariantList p_qlParameters);




    public slots:
         /** +-=---------------------------------------------------------Di 13. Nov 15:39:16 2012-------*
    * @method  CdmExecutorFunction::Execute                          // public, slots                     *
    * @return  QVariant                                      //                                   *
    * @param   CdmClassMethod* p_pMethod                     //                                   *
    * @param   CdmModelElement* p_pCdmBase                           // Object / ObjectList               *
    * @param   QVariantList p_qlParams                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 15:39:16 2012----------*/
QVariant Execute( CdmClassMethod* p_pMethod, CdmModelElement* p_pCdmBase, QVariantList p_qlParams);
QVariant Execute(CdmClassMethod* p_pMethod, CdmModelElement* p_pCdmBase);


   
    public slots:
         /** +-=---------------------------------------------------------So 25. Nov 12:23:19 2012-------*
    * @method  CdmExecutorFunction::ExecuteStatic                    // public, slots                     *
    * @return  QVariant                                      //                                   *
    * @param   CdmClassMethod* p_pMethod                     //                                   *
    * @param   QVariantList p_qlParameters                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 25. Nov 12:23:19 2012----------*/
QVariant ExecuteStatic( CdmClassMethod* p_pMethod, QVariantList p_qlParameters);


   private:
   /** +-=---------------------------------------------------------Di 13. Nov 15:16:36 2012-------*
    * @method  CdmExecutorFunction::AddMethodDataToEngine            // private                           *
    * @return  void                                          //                                   *
    * @param   QScriptEngine& p_rqEngine                     //                                   *
    * @param   CdmClassMethod* p_pMethod                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 15:16:36 2012----------*/
    void AddMethodDataToEngine(QScriptEngine& p_rqEngine, CdmClassMethod* p_pMethod);

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 17:38:57 2012-------*
    * @method  CdmExecutorFunction::ExecStaticMethod                 // public                    *
    * @return  QVariant                                  //                                   *
    * @param   QString qstrObjectRefMember                   //                                   *
    * @param   QString qstrFunctionMemberName                //                                   *
    * @param   CdmClass* pCdmClass                           //                                   *
    * @param   QScriptContext* p_pContext                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 17:38:57 2012----------*/
    QVariant ExecStaticMethod(QString qstrObjectRefMember,
                                  QString qstrFunctionMemberName,
                                  CdmClass* pCdmClass,
                                  QScriptContext* p_pContext);

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 17:40:38 2012-------*
    * @method  CdmExecutorFunction::ExecStaticMethod                 // public                    *
    * @return  QVariant                                  //                                   *
    * @param   QString qstrObjectRefMember                   //                                   *
    * @param   QString qstrFunctionMemberName                //                                   *
    * @param   QScriptEngine* p_pEngine                      //                                   *
    * @param   QScriptContext* p_pContext                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 17:40:38 2012----------*/
    QVariant ExecStaticMethod(QString qstrObjectRefMember,
                                  QString qstrFunctionMemberName,
                                  QScriptEngine* p_pEngine,
                                  QScriptContext* p_pContext);

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 17:55:38 2012-------*
    * @method  CdmExecutorFunction::Exec                             // public                    *
    * @return  QVariant                                  //                                   *
    * @param   QScriptContext* p_pContext                    //                                   *
    * @param   QScriptEngine* p_pEngine                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 17:55:38 2012----------*/
    QVariant Exec(QScriptContext* p_pContext, QScriptEngine* p_pEngine);

   public:
   /** +-=---------------------------------------------------------So 25. Nov 11:56:30 2012-------*
    * @method  CdmExecutorFunction::ExecLocalObjectMethod            // public                    *
    * @return  QVariant                                  //                                   *
    * @param   QString qstrFunctionMemberName                //                                   *
    * @param   QScriptEngine* p_pEngine                      //                                   *
    * @param   QScriptContext* p_pContext                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 25. Nov 11:56:30 2012----------*/
    QVariant ExecLocalObjectMethod(QString qstrFunctionMemberName,
                                       QScriptEngine* p_pEngine,
                                       QScriptContext* p_pContext,
                                       CdmExecutorRuntime* p_pRuntime);

   public:
   /** +-=---------------------------------------------------------Di 27. Nov 16:30:00 2012-------*
    * @method  CdmExecutorFunction::Delete                           // public                    *
    * @return  QVariant                                  //                                   *
    * @param   QScriptContext* p_pContext                    //                                   *
    * @param   QScriptEngine* p_pEngine                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:30:00 2012----------*/
    QVariant Delete(QScriptContext* p_pContext, QScriptEngine* p_pEngine);


   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 11:13:16 2012--------*
    * @method  CdmExecutorFunction::ExecObjectMethod                 // public                    *
    * @return  QVariant                                  //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QString qstrFunctionMemberName                //                                   *
    * @param   QScriptEngine* p_pEngine                      //                                   *
    * @param   QScriptContext* p_pContext                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 11:13:16 2012-----------*/
    QVariant ExecObjectMethod(CdmObject* p_pCdmObject,
                                         QString qstrFunctionMemberName,
                                         QScriptEngine* p_pEngine,
                                         QScriptContext* p_pContext);

private:
    void CallConstructor(CdmObject *p_pObject, CdmClass *p_pClass);
    void CallDestructor(CdmObject *p_pObject, CdmClass *p_pClass);
    void CallClassConstructor(CdmObject *p_pObject, CdmClass* p_pClass);
    void CallClassDestructor(CdmObject *p_pObject, CdmClass* p_pClass);
    QString GenerateArguments(QVariantList p_qlParams, CdmClassMethod* p_pMethod);
    QVariant ExecuteReferencedFunction(QString qstrMethodName, QScriptEngine* p_pEngine, QScriptContext* p_pContext, CdmValue* pValue, CdmObject* pCallingObject, QString qstrRefName);
    QVariant ExecRefOrStaticFunction(QScriptEngine* p_pEngine, QString qstrMethodName, QScriptContext* p_pContext, CdmObject* pCallingObject, QString qstrRefName);
    QVariant ExecFunction(QVariant qsPrototype, QScriptEngine* p_pEngine, CdmExecutorRuntime* pRuntime, QScriptContext* p_pContext);
    QVariant ConvertToResultVariant(const QVariant &p_rQVariant);
    QString ConvertToJsDateConstructor(int pYear, int pMonth, int pDay, int pHour, int pMinute, int pSecond);
public:
    void CallConstructor(CdmObject *p_pObject);
    void CallDestructor(CdmObject *p_pObject);
    QVariant ExecuteFunction(QString p_qstrFunction, CdmObject* p_pCdmObject, QVariantList p_qlParameters);
    QVariant ExecuteFunctionStatic(CdmClassMethod* p_pMethod, QVariantList p_qlParameters);
    QVariant ExecStaticFunction(QString qstrMethodName, CdmClassManager* pClassManager, QScriptEngine* p_pEngine, QScriptContext* p_pContext, QString qstrRefName);
    void setAskForParametersAllowed(bool bAllowAskForParameters);
    bool IsAskForParametersAllowed() const;

};
#endif
