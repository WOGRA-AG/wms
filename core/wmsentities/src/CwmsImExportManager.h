/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsImExportManager.h
 ** Started Implementation: 2013/02/05
 ** Description:
 ** 
 ** implements the manager for import and export configurations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMEXPORTMANAGER_H
#define CWMSIMEXPORTMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsImExportConfiguration.h"
#include "basetools.h"

// Forwards
class CdmClassManager;
class CdmObject;
class CdmClass;
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the manager for import and export configurations
 */
class BASETOOLS_API CwmsImExportManager : public QObject
{

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 15:53:01 2013--------*
    * @method  CwmsImExportManager::CwmsImExportManager      // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 15:53:01 2013-----------*/
    CwmsImExportManager( );

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 15:53:07 2013--------*
    * @method  CwmsImExportManager::~CwmsImExportManager     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImExportManager                                        *
    *----------------last changed: -----------------------------Di 5. Feb 15:53:07 2013-----------*/
    virtual ~CwmsImExportManager( );

   private:
   /** +-=---------------------------------------------------------Di 5. Feb 15:53:31 2013--------*
    * @method  CwmsImExportManager::CheckDataStructure       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 15:53:31 2013-----------*/
    void CheckDataStructure();

   private:
   /** +-=---------------------------------------------------------Di 5. Feb 17:34:49 2013--------*
    * @method  CwmsImExportManager::CreateImExportClass      // private                           *
    * @return  CdmClass*                                     //                                   *
    * @param   CdmClassManager* p_pClassManager              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 17:34:49 2013-----------*/
    CdmClass* CreateImExportClass(CdmClassManager* p_pClassManager);

   private:
   /** +-=---------------------------------------------------------Di 5. Feb 16:22:06 2013--------*
    * @method  CwmsImExportManager::CreateImExportClass      // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 16:22:06 2013-----------*/
    void CreateImExportClass(CdmClass* p_pClass);


   public:
   /** +-=---------------------------------------------------------Di 5. Feb 16:53:52 2013--------*
    * @method  CwmsImExportManager::GetImportObjectList      // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 16:53:52 2013-----------*/
    CdmObjectContainer* GetImportObjectList();

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 16:54:03 2013--------*
    * @method  CwmsImExportManager::GetExportObjectList      // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 16:54:03 2013-----------*/
    CdmObjectContainer* GetExportObjectList();

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 16:57:31 2013--------*
    * @method  CwmsImExportManager::GetImportConfiguration   // public                            *
    * @return  QMap<QString, QString>                        //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 16:57:31 2013-----------*/
    QMap<QString, QString> GetImportConfiguration(CdmClass* p_pClass);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 11:13:35 2013--------*
    * @method  CwmsImExportManager::LoadConfigurations       // public                            *
    * @return  QMap<QString, QString>                        //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @param   CdmObjectContainer* p_pObjectList                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 11:13:35 2013-----------*/
    QMap<QString, QString> LoadConfigurations(qint64 p_lClassId, CdmObjectContainer* p_pObjectList);

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 17:00:26 2013--------*
    * @method  CwmsImExportManager::GetExportConfiguration   // public                            *
    * @return  QMap<QString, QString>                        //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 17:00:26 2013-----------*/
    QMap<QString, QString> GetExportConfiguration(CdmClass* p_pClass);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 11:35:41 2013--------*
    * @method  CwmsImExportManager::GetImportConfiguration   // public                            *
    * @return  QMap<QString, QString>                        //                                   *
    * @param  qint64 p_lClass                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 11:35:41 2013-----------*/
    QMap<QString, QString> GetImportConfiguration(qint64 p_lClass);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 11:36:17 2013--------*
    * @method  CwmsImExportManager::GetExportConfiguration   // public                            *
    * @return  QMap<QString, QString>                        //                                   *
    * @param  qint64 p_lClass                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 11:36:17 2013-----------*/
    QMap<QString, QString> GetExportConfiguration(qint64 p_lClass);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 12:11:49 2013--------*
    * @method  CwmsImExportManager::GetConfiguration         // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @param   CdmObjectContainer* p_pObjectList                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 12:11:49 2013-----------*/
    QString GetConfiguration(QString p_qstrName,qint64 p_lClassId, CdmObjectContainer* p_pObjectList);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 12:14:12 2013--------*
    * @method  CwmsImExportManager::GetExportConfiguration   // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClass                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 12:14:12 2013-----------*/
    QString GetExportConfiguration(QString p_qstrName,qint64 p_lClass);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 12:13:56 2013--------*
    * @method  CwmsImExportManager::GetImportConfiguration   // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClass                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 12:13:56 2013-----------*/
    QString GetImportConfiguration(QString p_qstrName,qint64 p_lClass);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 15:34:26 2013--------*
    * @method  CwmsImExportManager::CreateOrGetExportConfiguration // public                      *
    * @return  CwmsImExportConfiguration                     //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 15:34:26 2013-----------*/
    CwmsImExportConfiguration CreateOrGetExportConfiguration(QString p_qstrName,qint64 p_lClassId);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 15:34:05 2013--------*
    * @method  CwmsImExportManager::CreateOrGetImportConfiguration // public                      *
    * @return  CwmsImExportConfiguration                     //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 15:34:05 2013-----------*/
    CwmsImExportConfiguration CreateOrGetImportConfiguration(QString p_qstrName,qint64 p_lClassId);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 15:34:51 2013--------*
    * @method  CwmsImExportManager::CreateOrGetConfiguration // public                            *
    * @return  CwmsImExportConfiguration                     //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 15:34:51 2013-----------*/
    CwmsImExportConfiguration CreateOrGetConfiguration(QString p_qstrName,
                                                      qint64 p_lClassId,
                                                       CdmObjectContainer* p_pList);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 15:37:14 2013--------*
    * @method  CwmsImExportManager::GetConfigurationObject   // public                            *
    * @return  CwmsImExportConfiguration                     //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 15:37:14 2013-----------*/
    CwmsImExportConfiguration GetConfigurationObject(QString p_qstrName,
                                                    qint64 p_lClassId,
                                                     CdmObjectContainer* p_pList);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 15:18:26 2013-------*
    * @method  CwmsImExportManager::LoadConfigurationNames   // public                            *
    * @return  QStringList                                   //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @param   CdmObjectContainer* p_pObjectList                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 15:18:26 2013----------*/
    QStringList LoadConfigurationNames(qint64 p_lClassId, CdmObjectContainer* p_pObjectList);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 15:19:33 2013-------*
    * @method  CwmsImExportManager::GetExportConfigurationNames // public                         *
    * @return  QStringList                                   //                                   *
    * @param  qint64 p_lClass                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 15:19:33 2013----------*/
    QStringList GetExportConfigurationNames(qint64 p_lClass);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 15:20:10 2013-------*
    * @method  CwmsImExportManager::GetImportConfigurationNames // public                         *
    * @return  QStringList                                   //                                   *
    * @param  qint64 p_lClass                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 15:20:10 2013----------*/
    QStringList GetImportConfigurationNames(qint64 p_lClass);
};

#endif // CWMSIMEXPORTMANAGER_H
