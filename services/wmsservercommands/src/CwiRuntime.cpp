/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiRuntime.cpp
 ** Started Implementation: 2013/02/25
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QBuffer>
#include <QByteArray>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQueryEnhanced.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmQueryBuilder.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmLogging.h"
#include "CdmValueContainerRef.h"

// WMS Basetools Includes
#include "CwmsContext.h"
#include "CwmsImExportManager.h"
#include "CwmsPluginManager.h"
#include "CwmsExportFileWriter.h"
#include "CwmsExportSettings.h"
#include "CwmsImportSettings.h"
#include "CwmsImportParser.h"
#include "CwmsImport.h"
#include "CwmsApplication.h"
#include "CwmsReportManager.h"

// own Includes
#include "CwmscomData.h"
#include "CwiCommandPrintContainer.h"
#include "CwiCommandPrintObject.h"
#include "CwiRuntime.h"


/** +-=---------------------------------------------------------Mo 25. Feb 13:36:14 2013----------*
 * @method  CwiRuntime::CwiRuntime                     // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:36:14 2013----------*/
CwiRuntime::CwiRuntime(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "Runtime", true, true)
{

}

/** +-=---------------------------------------------------------Mo 25. Feb 13:36:18 2013----------*
 * @method  CwiRuntime::~CwiRuntime                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiDatabase                                                *
 *----------------last changed: --------------------------------Mo 25. Feb 13:36:18 2013----------*/
CwiRuntime::~CwiRuntime()
{
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:36:22 2013----------*
 * @method  CwiRuntime::ExecuteGet                        // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:36:22 2013----------*/
void CwiRuntime::ExecuteGet(CwmscomData* p_pData)
{
   if (p_pData)
   {
      QString qstrMode = p_pData->GetValue("Mode").toString();

      if (qstrMode == "Application")
      {
         QString qstrAppName = p_pData->GetValue("ApplicationName").toString(); 
         GetApplication(p_pData, qstrAppName);
      }
      else if (qstrMode == "ApplicationList")
      {
         GetApplicationList(p_pData);
      }
      else if (qstrMode == "Export")
      {
         Export(p_pData);
      }
      else if (qstrMode == "Print")
      {
         Print(p_pData);
      }
      else if (qstrMode == "PrintList")
      {
         GetPrintList(p_pData);
      }
      else if (qstrMode == "ImportList")
      {
         GetImportList(p_pData);
      }
      else if (qstrMode == "ExportList")
      {
         GetExportList(p_pData);
      }
      else if (qstrMode == "EvaluateFormula")
      {
         EvaluateFormula(p_pData);
      }
   }
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:36:47 2013----------*
 * @method  CwiRuntime::ExecutePut                        // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:36:47 2013----------*/
void CwiRuntime::ExecutePut(CwmscomData* p_pData)
{
   if (p_pData)
   {
      QString qstrMode = p_pData->GetValue("Mode").toString();

      if (qstrMode == "Import")
      {
         Import(p_pData);
      }
      else if (qstrMode == "ExecuteFunction")
      {
		  NOTIMPLEMENTED;
		  ERR("Not supported Function. Use ClassManager Interface instead");

        // ExecuteFunction(p_pData);
      }
   }
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:37:03 2013----------*
 * @method  CwiRuntime::ExecuteDelete                     // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:37:03 2013----------*/
void CwiRuntime::ExecuteDelete(CwmscomData* p_pData)
{
   if (p_pData)
   {
      // we have nothing to delete in the runtime ;-)
   }
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:37:53 2013----------*
 * @method  CwiRuntime::ExecuteDescription                // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:37:53 2013----------*/
void CwiRuntime::executeDescription(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      // ToDo Result Parameters
   }
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:37:57 2013----------*
 * @method  CwiRuntime::GetResourceDescription            // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:37:57 2013----------*/
QString CwiRuntime::GetResourceDescription()
{
   return "Implements the WMS Runtime Interface usually you don't need it (except wms clients).";
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:48:30 2013----------*
 * @method  CwiRuntime::GetApplication                    // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:48:30 2013----------*/
void CwiRuntime::GetApplication(CwmscomData* p_pData, QString p_qstrApplication)
{
   CdmObject* pCdmObject = CwmsApplication::GetApplication(p_qstrApplication);
   CwmscomDataResult* pResult = nullptr;
   
   if (CHKPTR(pCdmObject))
   {
      pResult = GetResultContainer(p_pData,
                                   1,
                                   "Application found!",
                                   eWmscomMessageServerityInfo);
      pResult->AddValue("ApplicationObject", pCdmObject->GetVariant());
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Application not found!",
                                   eWmscomMessageServerityFatal);
   }
}

/** +-=---------------------------------------------------------Mo 25. Feb 13:48:39 2013----------*
 * @method  CwiRuntime::GetApplicationList                // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 13:48:39 2013----------*/
void CwiRuntime::GetApplicationList(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
   bool bWeb = p_pData->GetValue("Web").toBool();
   bool bDesktop = p_pData->GetValue("Desktop").toBool();
   bool bMobile = p_pData->GetValue("Mobile").toBool();

   if (!bWeb && !bDesktop && !bMobile) // if everything is false show all
   {
       bWeb = true;
       bDesktop = true;
       bMobile = true;
   }

   QStringList qstrlApplications = CwmsApplication::GetApplicationList(bDesktop, bWeb, bMobile);

   if (qstrlApplications.count() > 0)
   {
      QVariantList qvlApps;



      for (int iCounter = 0; iCounter < qstrlApplications.count(); ++iCounter)
      {
         qvlApps.append(qstrlApplications[iCounter]);
      }

      pResult = GetResultContainer(p_pData,
                                   1,
                                   "Application list found!",
                                   eWmscomMessageServerityInfo);
      pResult->AddValue("ApplicationList", qvlApps);
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "No Applications found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Do 28. Feb 15:15:10 2013----------*
 * @method  CwiRuntime::GetExportList                     // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 15:15:10 2013----------*/
void CwiRuntime::GetExportList(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
  qint64 lObjectListId = p_pData->GetValue("ObjectListId").toInt();
   CdmObjectContainer* pList = GetContainer(lObjectListId);

   if (CHKPTR(pList))
   {
      CwmsImExportManager cManager;
      QStringList qstrlNames = cManager.GetExportConfigurationNames(pList->GetClassId());

      if (qstrlNames.count() > 0)
      {
         pResult = GetResultContainer(p_pData,
                                      1,
                                      "Exportconfigurations found!",
                                      eWmscomMessageServerityInfo);

         QVariantList qvlConfigs;

         for (int iCounter = 0; iCounter < qstrlNames.count(); ++iCounter)
         {
            qvlConfigs.append(qstrlNames[iCounter]);
         }

         pResult->AddValue("Configurations", qvlConfigs);
      }
      else
      {
         pResult = GetResultContainer(p_pData,
                                      0,
                                      "No Exportconfigurations found",
                                      eWmscomMessageServerityInfo);
      }
   }
   else
   {
      pResult = GetResultContainer(p_pData,
         -5000,
         "Objectlist not found!",
         eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Do 28. Feb 15:15:16 2013----------*
 * @method  CwiRuntime::GetImportList                     // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 15:15:16 2013----------*/
void CwiRuntime::GetImportList(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
  qint64 lObjectListId = p_pData->GetValue("ObjectListId").toInt();
   CdmObjectContainer* pList = GetContainer(lObjectListId);

   if (CHKPTR(pList))
   {
      CwmsImExportManager cManager;
      QStringList qstrlNames = cManager.GetImportConfigurationNames(pList->GetClassId());

      if (qstrlNames.count() > 0)
      {
         pResult = GetResultContainer(p_pData,
                                      1,
                                      "Importconfigurations found!",
                                      eWmscomMessageServerityInfo);

         QVariantList qvlConfigs;

         for (int iCounter = 0; iCounter < qstrlNames.count(); ++iCounter)
         {
            qvlConfigs.append(qstrlNames[iCounter]);
         }

         pResult->AddValue("Configurations", qvlConfigs);
      }
      else
      {
         pResult = GetResultContainer(p_pData,
            0,
            "No Importconfigurations found",
            eWmscomMessageServerityInfo);
      }
   }
   else
   {
      pResult = GetResultContainer(p_pData,
         -5000,
         "Objectlist not found!",
         eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Do 28. Feb 15:15:21 2013----------*
 * @method  CwiRuntime::GetPrintList                      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 15:15:21 2013----------*/
void CwiRuntime::GetPrintList(CwmscomData* p_pData)
{
   CwiCommandPrintContainer command(p_pData);
   command.Execute();
}

/** +-=---------------------------------------------------------Mo 25. Feb 14:52:29 2013----------*
 * @method  CwiRuntime::Export                            // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 14:52:29 2013----------*/
void CwiRuntime::Export(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
   QString qstrConfigName = p_pData->GetValue("ConfigurationName").toString();
  qint64 lObjectListId = p_pData->GetValue("ObjectListId").toInt();
   CdmObjectContainer* pList = GetContainer(lObjectListId);

   if (CHKPTR(pList))
   {
      CwmsImExportManager cManager;
      QString qstrConfig = cManager.GetExportConfiguration(qstrConfigName, pList->GetClassId());

      if (!qstrConfig.isEmpty())
      {
         CwmsExportSettings cCwmsExportSettings;
         cCwmsExportSettings.Load(qstrConfigName, qstrConfig);
         cCwmsExportSettings.SetContainerId(pList->GetId());
         CwmsExportWriter cWriter(cCwmsExportSettings);

         QByteArray qbaExport;
         QBuffer* pBuffer = new QBuffer(&qbaExport);
         cWriter.SetDevice(pBuffer);
         cWriter.Export();

         if (!qbaExport.isEmpty())
         {
            pResult = GetResultContainer(p_pData,
                                         1,
                                         "Export successfull!",
                                         eWmscomMessageServerityInfo);
            pResult->AddValue("Content", qbaExport);
         }
         else
         {
            pResult = GetResultContainer(p_pData,
                                         -5000,
                                         "Export failed (empty result)!",
                                         eWmscomMessageServerityError);
         }
      }
      else
      {
         pResult = GetResultContainer(p_pData,
                                      -5000,
                                      "Export Configuration not found!",
                                      eWmscomMessageServerityError);
      }
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Objectlist for export not found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Mo 25. Feb 14:52:47 2013----------*
 * @method  CwiRuntime::Import                            // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 14:52:47 2013----------*/
void CwiRuntime::Import(CwmscomData* p_pData)
{
   QString qstrConfigName = p_pData->GetValue("ConfigurationName").toString();
  qint64 lObjectListId = p_pData->GetValue("ObjectListId").toInt();
   QString qstrContent = p_pData->GetValue("Content").toString();
   CdmObjectContainer* pList = GetContainer(lObjectListId);

   if (CHKPTR(pList))
   {
      CwmsImExportManager cManager;
      QString qstrConfig = cManager.GetImportConfiguration(qstrConfigName, pList->GetClassId());

      if (!qstrConfig.isEmpty())
      {
         CwmsImportSettings cCwmsImportSettings;
         cCwmsImportSettings.LoadSettings(qstrConfigName, qstrConfig);
         CwmsImport cImport;
         CwmsImportParser* pParser = cImport.CreateParser(cCwmsImportSettings);

         if (CHKPTR(pParser))
         {
            QByteArray qbArray(qstrContent.toLatin1());
            QBuffer* pBuffer = new QBuffer(&qbArray);
            pParser->SetDevice(pBuffer);
            cImport.StartImport(pList, cCwmsImportSettings);
         }

      }
      else
      {
         GetResultContainer(p_pData,
                          -5000,
                          "Import Configuration not found!",
                          eWmscomMessageServerityError);
      }
   }
   else
   {
      GetResultContainer(p_pData,
                       -5000,
                       "Objectlist for import not found!",
                       eWmscomMessageServerityError);
   }


}

/** +-=---------------------------------------------------------Mo 25. Feb 14:55:24 2013----------*
 * @method  CwiRuntime::ExecuteFunction                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 14:55:24 2013----------*/
void CwiRuntime::ExecuteFunction(CwmscomData* p_pData)
{
  qint64 lObjectListId = p_pData->GetValue("ObjectListId").toInt();
  qint64 lObjectId  = p_pData->GetValue("ObjectId").toInt();
  qint64 lClassId = p_pData->GetValue("ClassId").toInt();
   QString qstrFunction = p_pData->GetValue("Function").toString();
   QVariantList qvlParameters = p_pData->GetValue("Parameters").toList();

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      if (lClassId > 0 && lObjectListId <= 0) // for static functions
      {
         ExecuteStaticMethod(p_pData, lClassId, qstrFunction, qvlParameters);
      }
      else if (lObjectListId > 0 && lObjectId > 0) // for object functions
      {
         ExecuteObjectMethod(p_pData, lObjectListId, lObjectId, qstrFunction, qvlParameters);
      }
      else // ERROR Handling
      {
         GetResultContainer(p_pData,
                            -5000,
                            "Invalid call of ExecuteFunction!",
                            eWmscomMessageServerityError);
      }
   }
}


void CwiRuntime::EvaluateFormula(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
  qint64 lObjectListId = p_pData->GetValue("ObjectListId").toInt();
  qint64 lObjectId  = p_pData->GetValue("ObjectId").toInt();
   QString qstrFormula = p_pData->GetValue("Formula").toString();

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      if (lObjectListId > 0 && lObjectId > 0) // for object functions
      {
         CdmContainerManager* pContainerManager = pManager->GetContainerManager();

         if (CHKPTR(pContainerManager))
         {
            CdmObjectContainer* pContainer = pContainerManager->FindContainerById(lObjectListId);

            if (CHKPTR(pContainer))
            {
               CdmObject* pObject = pContainer->FindObjectById(lObjectId);

               if (CHKPTR(pObject))
               {
                  QVariant qvValue = CdmExecutor::GetExecutor()->EvaluateFormula(pObject, qstrFormula);
                  pResult = GetResultContainer(p_pData,
                                               1,
                                               "Method executed!",
                                               eWmscomMessageServerityInfo);

                  pResult->AddValue("Result", qvValue);
               }
               else
               {
                  pResult = GetResultContainer(p_pData,
                                               -5000,
                                               "Object not found",
                                               eWmscomMessageServerityError);
               }
            }
         }
      }
      else // ERROR Handling
      {
         pResult = GetResultContainer(p_pData,
                                      -5000,
                                      "Invalid call of ExecuteFunction!",
                                      eWmscomMessageServerityError);
      }
   }
}

/** +-=---------------------------------------------------------Do 28. Feb 10:34:58 2013----------*
 * @method  CwiRuntime::ExecuteObjectMethod               // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   QString p_qstrFunction                           //                                   *
 * @param   QVariantList p_qvlParameters                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 10:34:58 2013----------*/
void CwiRuntime::ExecuteObjectMethod(CwmscomData* p_pData,
                                    qint64 p_lObjectListId,
                                    qint64 p_lObjectId,
                                     QString p_qstrFunction,
                                     QVariantList p_qvlParameters)
{
   CwmscomDataResult* pResult = nullptr;
   CdmObject* pObject = GetObject(p_lObjectListId, p_lObjectId);

   if (CHKPTR(pObject))
   {
      CdmClass* pClass = pObject->GetClass();
      if (CHKPTR(pClass))
      {
         CdmClassMethod* pMethod = pClass->FindMethod(p_qstrFunction);

         if (CHKPTR(pMethod))
         {
            QVariant qvValue = 
            CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, pObject, p_qvlParameters);
            pResult = GetResultContainer(p_pData,
                                         1,
                                         "Method executed!",
                                         eWmscomMessageServerityInfo);
            pResult->AddValue("Result", qvValue);
         }
         else
         {
            pResult = GetResultContainer(p_pData,
                                          -5000,
                                          "Object not found!",
                                          eWmscomMessageServerityError);
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 28. Feb 10:27:46 2013----------*
 * @method  CwiRuntime::ExecuteStaticMethod               // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lCassId                                   //                                   *
 * @param   QString p_qstrFunction                           //                                   *
 * @param   QVariantList p_qvlParameters                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 10:27:46 2013----------*/
void CwiRuntime::ExecuteStaticMethod(CwmscomData* p_pData,
                                       qint64 p_lCassId,
                                        QString p_qstrFunction,
                                        QVariantList p_qvlParameters)
{
   CwmscomDataResult* pResult = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (pManager)
   {
      CdmClassManager* pClassManager = pManager->GetClassManager();

      if (CHKPTR(pClassManager))
      {
         CdmClass* pClass = pClassManager->FindClassById(p_lCassId);

         if (CHKPTR(pClass))
         {
            CdmClassMethod* pMethod = pClass->FindMethod(p_qstrFunction);

            if (CHKPTR(pMethod) && pMethod->IsStatic())
            {
               QVariant qvValue = CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, nullptr, p_qvlParameters);
               pResult = GetResultContainer(p_pData,
                                            1,
                                            "Method executed!",
                                            eWmscomMessageServerityInfo);
               pResult->AddValue("Result", qvValue);
            }
            else if (!pMethod->IsStatic())
            {
               pResult = GetResultContainer(p_pData,
                                             -5000,
                                             "Tried to call a non static method on a class!",
                                             eWmscomMessageServerityError);
            }
            else
            {
               pResult = GetResultContainer(p_pData,
                                            -5000,
                                            "Method not found!",
                                            eWmscomMessageServerityError);
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 27. Feb 14:20:15 2013----------*
 * @method  CwiRuntime::GetObject                         // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Feb 14:20:15 2013----------*/
CdmObject* CwiRuntime::GetObject(qint64 p_lObjectListId,qint64 p_lObjectId)
{
   CdmObject* pObject = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmObjectContainer* pList = GetContainer(p_lObjectListId);

      if (CHKPTR(pList))
      {
         pObject = pList->FindObjectById(p_lObjectId);
      }
   }

   return pObject;
}

/** +-=---------------------------------------------------------Do 28. Feb 10:21:21 2013----------*
 * @method  CwiRuntime::GetContainer                     // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lObjectList                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 10:21:21 2013----------*/
CdmObjectContainer* CwiRuntime::GetContainer(qint64 p_lObjectList)
{
   CdmObjectContainer* pList = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmContainerManager* pOLManager = pManager->GetContainerManager();

      if (CHKPTR(pOLManager))
      {
         pList = pOLManager->FindEmptyContainerById(p_lObjectList);
      }
   }

   return pList;
}

/** +-=---------------------------------------------------------Mo 25. Feb 14:55:29 2013----------*
 * @method  CwiRuntime::Print                             // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Feb 14:55:29 2013----------*/
void CwiRuntime::Print(CwmscomData* p_pData)
{
    CwiCommandPrintObject command(p_pData);
    command.Execute();
 }

/** +-=---------------------------------------------------------Do 10. Okt 16:29:18 2013----------*
 * @method  CwiRuntime::GetVersion                        // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:29:18 2013----------*/
QString CwiRuntime::getVersion()
{
   return "0.1.0";
}
