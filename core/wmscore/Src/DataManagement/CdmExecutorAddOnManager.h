/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmExecutorAddOnManager.h
 ** Started Implementation: 2013/11/15
 ** Description:
 ** 
 ** manages plugins and additional functions for executing scripts
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMEXECUTORADDONMANAGER_H
#define CDMEXECUTORADDONMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QJSEngine>
#include <QScriptEngine>
#include <QScriptValue>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// Own Includes
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
class CdmExecutor;
class QScriptProgram;
class QScriptContext;
class IwmsPluginInterface;
class IwmsPrintingPlugin;

// TypeDefs


/* 
 * This class implements the executor for functions and validations in Objects
 */
class WMSMANAGER_API CdmExecutorAddOnManager : public CwmsSynchronizable
{
   private:
      QMap<QString, QObject*> m_qmAdditionalFunctions;
      QMap<QString, IwmsPluginInterface*> m_qmPlugins;
      IwmsPrintingPlugin* m_pPrintingPlugin;
      
   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:17:10 2012-------*
    * @method  CdmExecutorAddOnManager::CdmExecutorAddOnManager                      // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:17:10 2012----------*/
    CdmExecutorAddOnManager();

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012-------*
    * @method  CdmExecutorAddOnManager::~CdmExecutorAddOnManager                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmExecutorAddOnManager                                                *
    *----------------last changed: -----------------------------Mi 19. Sep 14:18:59 2012----------*/
    virtual ~CdmExecutorAddOnManager( );


   private:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:34:02 2012-------*
    * @method  CdmExecutorAddOnManager::AddFunctionality                 // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QObject* p_pqFunctionality                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:34:02 2012----------*/
    void AddFunctionality(QString p_qstrName, QObject* p_pqFunctionality);

   public:
   /** +-=---------------------------------------------------------Mi 19. Sep 14:35:28 2012-------*
    * @method  CdmExecutorAddOnManager::InstallAdditionalFunctionality   // public                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QObject* p_pqObject                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Sep 14:35:28 2012----------*/
    void InstallAdditionalFunctionality(QString p_qstrName, QObject* p_pqObject);

   public:
   /** +-=---------------------------------------------------------Do 20. Sep 10:22:29 2012-------*
    * @method  CdmExecutorAddOnManager::AddAditionalFunctionalityToEngine // public                          *
    * @return  void                                          //                                   *
    * @param   QScriptEngine& p_rqEngine                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 10:22:29 2012----------*/
    void AddAditionalFunctionalityToEngine(QScriptEngine& p_rqEngine);

   public:
   /** +-=---------------------------------------------------------Mo 7. Jan 14:22:01 2013--------*
    * @method  CdmExecutorAddOnManager::InstallPlugin                    // public                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   IwmsPluginInterface* p_pPlugin                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 7. Jan 14:22:01 2013-----------*/
    void InstallPlugin(QString p_qstrName, IwmsPluginInterface* p_pPlugin);

   private:
   /** +-=---------------------------------------------------------Mo 7. Jan 14:30:19 2013--------*
    * @method  CdmExecutorAddOnManager::AddPlugin                        // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   IwmsPluginInterface* p_pPlugin                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 7. Jan 14:30:19 2013-----------*/
    void AddPlugin(QString p_qstrName, IwmsPluginInterface* p_pPlugin);

public:
   /** +-=---------------------------------------------------------Mo 7. Jan 14:36:06 2013--------*
    * @method  CdmExecutorAddOnManager::GetFunctionObject                // public                            *
    * @return  QObject*                                      //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 7. Jan 14:36:06 2013-----------*/
    QObject* GetFunctionObject(QString p_qstrName);

    void RemovePlugin(QString p_qstrName);
    void ClearPlugins();
    void SetPrintingPlugin(IwmsPrintingPlugin *p_pPlugin);
    IwmsPrintingPlugin *GetPrintingPlugin();
    void ResetPrintingPlugin();
    void AddAditionalFunctionalityToEngine(QJSEngine &p_rqEngine);
    bool ContainsFunctionality(QString p_qstrName);
};

#endif //
