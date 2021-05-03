/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsImExportManager.cpp
 ** Started Implementation: 2013/02/05
 ** Description:
 **
 ** implements the manager for import and export configurations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmScheme.h"
#include "CdmClassManager.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"

// own Includes
#include "CwmsImExportManager.h"

/** +-=---------------------------------------------------------Di 5. Feb 15:53:01 2013-----------*
 * @method  CwmsImExportManager::CwmsImExportManager         // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 15:53:01 2013-----------*/
CwmsImExportManager::CwmsImExportManager()
{
   CheckDataStructure();
}

/** +-=---------------------------------------------------------Di 5. Feb 15:53:07 2013-----------*
 * @method  CwmsImExportManager::~CwmsImExportManager        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImExportManager                                           *
 *----------------last changed: --------------------------------Di 5. Feb 15:53:07 2013-----------*/
CwmsImExportManager::~CwmsImExportManager()
{
}

/** +-=---------------------------------------------------------Di 5. Feb 15:53:31 2013-----------*
 * @method  CwmsImExportManager::CheckDataStructure          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 15:53:31 2013-----------*/
void CwmsImExportManager::CheckDataStructure()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

      if (CHKPTR(pCdmClassManager))
      {
         CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname("Technical_ImExport");

         if (!pCdmClass)
         {
            pCdmClass = CreateImExportClass(pCdmClassManager);

            CdmContainerManager* pOLManager = pCdmClassManager->GetContainerManager();

            if (CHKPTR(pOLManager))
            {
               QString qstrKeyname = "TechnicalImports";
               pOLManager->CreateContainer(pCdmClass, qstrKeyname);
               qstrKeyname = "TechnicalExports";
               pOLManager->CreateContainer(pCdmClass, qstrKeyname);
            }
         }
         else
         {
             if(pCdmClass->FindMember("Encoding") == nullptr)
             {
                 CdmMember* pMember = pCdmClass->CreateMember("Encoding", eDmValueString, false, 0);
                 pMember->SetCaption(tr("Encoding"));
                 pMember->SetComment(tr("Das Encoding der zu im- zw. exportierenden Datei"));
                 pCdmClass->Commit();
             }
         }
      }
   }
}

/** +-=---------------------------------------------------------Di 5. Feb 17:34:49 2013-----------*
 * @method  CwmsImExportManager::CreateImExportClass         // private                           *
 * @return  CdmClass*                                        //                                   *
 * @param   CdmClassManager* p_pClassManager                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 17:34:49 2013-----------*/
CdmClass* CwmsImExportManager::CreateImExportClass(CdmClassManager* p_pClassManager)
{
   CdmClass* pClass = nullptr;

   if (CHKPTR(p_pClassManager))
   {
      if (CHKPTR(p_pClassManager))
      {
         pClass = p_pClassManager->CreateClass("Technical_ImExport");
   
         if (CHKPTR(pClass))
         {
            CreateImExportClass(pClass);
         }
      }
   }

   return pClass;
}

/** +-=---------------------------------------------------------Di 5. Feb 16:22:06 2013-----------*
 * @method  CwmsImExportManager::CreateImExportClass         // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 16:22:06 2013-----------*/
void CwmsImExportManager::CreateImExportClass(CdmClass* p_pClass)
{
   if (CHKPTR(p_pClass))
   {
      p_pClass->SetCaption(tr("ImExportkonfigurationen"));
      p_pClass->SetComment(tr("Speichert Konfigurationen zum Datenimexport."));

      CdmMember* pCdmMember = nullptr;
      pCdmMember = p_pClass->CreateMember("Id", eDmValueCounter, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Id"));
         pCdmMember->SetComment(tr("Die eindeutige Id der Sicht"));
      }

      pCdmMember = p_pClass->CreateMember("Name", eDmValueString, true, 200);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Name"));
         pCdmMember->SetComment(tr("Name der Datensicht"));
      }

      pCdmMember = p_pClass->CreateMember("ClassId", eDmValueInt, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Klasse"));
         pCdmMember->SetComment(tr("Die ID der Klasse für die der IM/Export defniert wurde."));
      }

      pCdmMember = p_pClass->CreateMember("ClassUri", eDmValueString, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Klassen URI"));
         pCdmMember->SetComment(tr("Die URI der Klasse für die der IM/Export defniert wurde."));
      }

      pCdmMember = p_pClass->CreateMember("Configuration", eDmValueCharacterDocument, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Konfiguration"));
         pCdmMember->SetComment(tr("Die Konfiguration des Imports"));
         pCdmMember->SetClassReference(1);
      }

      p_pClass->Commit();
   }
}

/** +-=---------------------------------------------------------Di 5. Feb 16:53:52 2013-----------*
 * @method  CwmsImExportManager::GetImportObjectList         // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 16:53:52 2013-----------*/
CdmObjectContainer* CwmsImExportManager::GetImportObjectList()
{
   CdmObjectContainer* pList = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pOLManager = pCdmManager->GetContainerManager();

      if (CHKPTR(pOLManager))
      {
         pList = pOLManager->FindEmptyContainerByKeyname("TechnicalImports");
      }
   }

   return pList;
}

/** +-=---------------------------------------------------------Di 5. Feb 16:54:03 2013-----------*
 * @method  CwmsImExportManager::GetExportObjectList         // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 16:54:03 2013-----------*/
CdmObjectContainer* CwmsImExportManager::GetExportObjectList()
{
   CdmObjectContainer* pList = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pOLManager = pCdmManager->GetContainerManager();

      if (CHKPTR(pOLManager))
      {
         pList = pOLManager->FindEmptyContainerByKeyname("TechnicalExports");
      }
   }

   return pList;
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:35:41 2013-----------*
 * @method  CwmsImExportManager::GetImportConfiguration      // public                            *
 * @return  QMap<QString, QString>                           //                                   *
 * @param   long p_lClass                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 11:35:41 2013-----------*/
QMap<QString, QString> CwmsImExportManager::GetImportConfiguration(long p_lClass)
{

   QMap<QString, QString> qmConfigurations;

   if (p_lClass > 0)
   {
      CdmObjectContainer* pList = GetImportObjectList();

      if (CHKPTR(pList))
      {
         qmConfigurations = LoadConfigurations(p_lClass, pList);
      }
   }

   return qmConfigurations;
}

/** +-=---------------------------------------------------------Di 5. Feb 16:57:31 2013-----------*
 * @method  CwmsImExportManager::GetImportConfiguration      // public                            *
 * @return  QMap<QString, QString>                           //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 16:57:31 2013-----------*/
QMap<QString, QString> CwmsImExportManager::GetImportConfiguration(CdmClass* p_pClass)
{
   QMap<QString, QString> qmConfigurations;

   if (CHKPTR(p_pClass))
   {
      CdmObjectContainer* pList = GetImportObjectList();

      if (CHKPTR(pList))
      {
         qmConfigurations = LoadConfigurations(p_pClass->GetId(), pList);
      }
   }

   return qmConfigurations;
}

/** +-=---------------------------------------------------------Di 5. Feb 17:00:26 2013-----------*
 * @method  CwmsImExportManager::GetExportConfiguration      // public                            *
 * @return  QMap<QString, QString>                           //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 17:00:26 2013-----------*/
QMap<QString, QString> CwmsImExportManager::GetExportConfiguration(CdmClass* p_pClass)
{
   QMap<QString, QString> qmConfigurations;

   if (CHKPTR(p_pClass))
   {
      CdmObjectContainer* pList = GetExportObjectList();

      if (CHKPTR(pList))
      {
         qmConfigurations = LoadConfigurations(p_pClass->GetId(), pList);
      }
   }

   return qmConfigurations;
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:36:17 2013-----------*
 * @method  CwmsImExportManager::GetExportConfiguration      // public                            *
 * @return  QMap<QString, QString>                           //                                   *
 * @param   long p_lClass                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 11:36:17 2013-----------*/
QMap<QString, QString> CwmsImExportManager::GetExportConfiguration(long p_lClass)
{

   QMap<QString, QString> qmConfigurations;

   if (p_lClass > 0)
   {
      CdmObjectContainer* pList = GetExportObjectList();

      if (CHKPTR(pList))
      {
         qmConfigurations = LoadConfigurations(p_lClass, pList);
      }
   }

   return qmConfigurations;
}

/** +-=---------------------------------------------------------Do 28. Feb 15:19:33 2013----------*
 * @method  CwmsImExportManager::GetExportConfigurationNames // public                            *
 * @return  QStringList                                      //                                   *
 * @param   long p_lClass                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 15:19:33 2013----------*/
QStringList CwmsImExportManager::GetExportConfigurationNames(long p_lClass)
{
   QStringList qstrlConfigs;
   if (p_lClass > 0)
   {
      CdmObjectContainer* pList = GetExportObjectList();

      if (CHKPTR(pList))
      {
         qstrlConfigs = LoadConfigurationNames(p_lClass, pList);
      }
   }

   return qstrlConfigs;
}

/** +-=---------------------------------------------------------Do 28. Feb 15:20:10 2013----------*
 * @method  CwmsImExportManager::GetImportConfigurationNames // public                            *
 * @return  QStringList                                      //                                   *
 * @param   long p_lClass                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 15:20:10 2013----------*/
QStringList CwmsImExportManager::GetImportConfigurationNames(long p_lClass)
{
   QStringList qstrlConfigs;
   if (p_lClass > 0)
   {
      CdmObjectContainer* pList = GetImportObjectList();

      if (CHKPTR(pList))
      {
         qstrlConfigs = LoadConfigurationNames(p_lClass, pList);
      }
   }

   return qstrlConfigs;
}

/** +-=---------------------------------------------------------Mi 6. Feb 12:14:12 2013-----------*
 * @method  CwmsImExportManager::GetExportConfiguration      // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClass                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 12:14:12 2013-----------*/
QString CwmsImExportManager::GetExportConfiguration(QString p_qstrName, long p_lClass)
{
   QString qstrConfig;

   if (p_lClass > 0)
   {
      CdmObjectContainer* pList = GetExportObjectList();

      if (CHKPTR(pList))
      {
         qstrConfig = GetConfiguration(p_qstrName, p_lClass, pList);
      }
   }

   return qstrConfig;
}

/** +-=---------------------------------------------------------Mi 6. Feb 12:13:56 2013-----------*
 * @method  CwmsImExportManager::GetImportConfiguration      // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClass                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 12:13:56 2013-----------*/
QString CwmsImExportManager::GetImportConfiguration(QString p_qstrName, long p_lClass)
{
   QString qstrConfig;

   if (p_lClass > 0)
   {
      CdmObjectContainer* pList = GetImportObjectList();

      if (CHKPTR(pList))
      {
         qstrConfig = GetConfiguration(p_qstrName, p_lClass, pList);
      }
   }

   return qstrConfig;
}

/** +-=---------------------------------------------------------Do 28. Feb 15:18:26 2013----------*
 * @method  CwmsImExportManager::LoadConfigurationNames      // public                            *
 * @return  QStringList                                      //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   CdmObjectContainer* p_pObjectList                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 15:18:26 2013----------*/
QStringList CwmsImExportManager::LoadConfigurationNames(long p_lClassId,
                                                        CdmObjectContainer* p_pObjectList)
{
   QStringList qstrlConfigurations;

   if (p_lClassId > 0 && CHKPTR(p_pObjectList))
   {
      QString qstrWql;
      qstrWql = "select Name from \"" + p_pObjectList->GetKeyname() + "\" where ClassId = " + QString::number(p_lClassId);

      CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
         {
            qstrlConfigurations.append(pQuery->GetResultAt(0, iCounter).toString());
         }
      }
   }

   return qstrlConfigurations;
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:13:35 2013-----------*
 * @method  CwmsImExportManager::LoadConfigurations          // public                            *
 * @return  QMap<QString, QString>                           //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   CdmObjectContainer* p_pObjectList                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 11:13:35 2013-----------*/
QMap<QString, QString> CwmsImExportManager::LoadConfigurations(long p_lClassId,
                                                               CdmObjectContainer* p_pObjectList)
{
   QMap<QString, QString> qmConfigurations;

   if (p_lClassId > 0 && CHKPTR(p_pObjectList))
   {
      QString qstrWql;
      qstrWql = "select Name, Configuration from \"" + p_pObjectList->GetKeyname() + "\" where ClassId = " + QString::number(p_lClassId);

      CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
         {
            qmConfigurations.insert(pQuery->GetResultAt(0, iCounter).toString(),
                                    pQuery->GetResultAt(1, iCounter).toString());
         }
      }
   }

   return qmConfigurations;
}

/** +-=---------------------------------------------------------Mi 6. Feb 12:11:49 2013-----------*
 * @method  CwmsImExportManager::GetConfiguration            // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   CdmObjectContainer* p_pObjectList                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 12:11:49 2013-----------*/
QString CwmsImExportManager::GetConfiguration(QString p_qstrName,
                                              long p_lClassId,
                                              CdmObjectContainer* p_pObjectList)
{
   QString qstrConfiguration;

   if (p_lClassId > 0 && CHKPTR(p_pObjectList))
   {
      QString qstrWql;
      qstrWql = "select Configuration from \"" + p_pObjectList->GetKeyname() + "\" where and(ClassId = " + QString::number(p_lClassId)+ ", Name = \"" + p_qstrName + "\")";

      CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
         {
            qstrConfiguration = pQuery->GetResultAt(0, iCounter).toString();
         }
      }
   }

   return qstrConfiguration;
}

/** +-=---------------------------------------------------------Mi 6. Feb 15:34:26 2013-----------*
 * @method  CwmsImExportManager::CreateOrGetExportConfiguration // public                         *
 * @return  CwmsImExportConfiguration                        //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 15:34:26 2013-----------*/
CwmsImExportConfiguration CwmsImExportManager::CreateOrGetExportConfiguration(QString p_qstrName,
                                                                              long p_lClassId)
{
   return CreateOrGetConfiguration(p_qstrName, p_lClassId, GetExportObjectList());
}

/** +-=---------------------------------------------------------Mi 6. Feb 15:34:05 2013-----------*
 * @method  CwmsImExportManager::CreateOrGetImportConfiguration // public                         *
 * @return  CwmsImExportConfiguration                        //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 15:34:05 2013-----------*/
CwmsImExportConfiguration CwmsImExportManager::CreateOrGetImportConfiguration(QString p_qstrName,
                                                                              long p_lClassId)
{
   return CreateOrGetConfiguration(p_qstrName, p_lClassId, GetImportObjectList());
}

/** +-=---------------------------------------------------------Mi 6. Feb 15:34:51 2013-----------*
 * @method  CwmsImExportManager::CreateOrGetConfiguration    // public                            *
 * @return  CwmsImExportConfiguration                        //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 15:34:51 2013-----------*/
CwmsImExportConfiguration CwmsImExportManager::CreateOrGetConfiguration(QString p_qstrName,
                                                                        long p_lClassId,
                                                                        CdmObjectContainer* p_pList)
{
   CwmsImExportConfiguration cConfig = GetConfigurationObject(p_qstrName, p_lClassId, p_pList);

   if (!cConfig.IsValid())
   {
      if (CHKPTR(p_pList))
      {
         cConfig = CwmsImExportConfiguration::Create(p_pList);
      }
      
   }

   return cConfig;
}

/** +-=---------------------------------------------------------Mi 6. Feb 15:37:14 2013-----------*
 * @method  CwmsImExportManager::GetConfigurationObject      // public                            *
 * @return  CwmsImExportConfiguration                        //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 15:37:14 2013-----------*/
CwmsImExportConfiguration CwmsImExportManager::GetConfigurationObject(QString p_qstrName,
                                                                      long p_lClassId,
                                                                      CdmObjectContainer* p_pList)
{
   CwmsImExportConfiguration cConfig;

   if (p_lClassId > 0 && CHKPTR(p_pList))
   {
      QString qstrWql;
      qstrWql = "select from \"" + p_pList->GetKeyname() + "\" where and(ClassId = " + QString::number(p_lClassId)+ ", Name = \"" + p_qstrName + "\")";

      CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         QList<long> qllResults = pQuery->GetResultList();

         if (qllResults.count() > 0)
         {
            long lObjectId = *qllResults.begin();
            CdmObject* pObject = p_pList->FindObjectById(lObjectId);
            cConfig.SetObject(pObject);
         }
      }
   }

   return cConfig;
}
