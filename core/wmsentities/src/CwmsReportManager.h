/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsReportManager.h
 ** Started Implementation: 2012/08/27
 ** Description:
 ** 
 ** Implements the manager for reports and printing templates
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSREPORTMANAGER_H
#define CWMSREPORTMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "basetools.h"
#include "IwmsPrinting.h"
#include "IwmsPrintingPlugin.h"
#include "CwmsPrintingTemplate.h"

// Forwards


// TypeDefs


/* 
 * This class implements the manager for reports and printing templates
 */
class BASETOOLS_API CwmsReportManager : public QObject
{

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:07:50 2012-------*
    * @method  CwmsReportManager::CwmsReportManager          // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:07:50 2012----------*/
    CwmsReportManager( );

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:07:57 2012-------*
    * @method  CwmsReportManager::~CwmsReportManager         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsReportManager                                          *
    *----------------last changed: -----------------------------Mo 27. Aug 14:07:57 2012----------*/
    virtual ~CwmsReportManager( );

   private:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:08:49 2012-------*
    * @method  CwmsReportManager::CheckReportDataStructure   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:08:49 2012----------*/
    void CheckReportDataStructure();

   private:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:18:47 2012-------*
    * @method  CwmsReportManager::CreateReportClass          // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:18:47 2012----------*/
    void CreateReportClass(CdmClassManager* p_pCdmClassManager);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:40:21 2012-------*
    * @method  CwmsReportManager::GetObjectList              // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:40:21 2012----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:40:50 2012-------*
    * @method  CwmsReportManager::GetReportList              // public                            *
    * @return  void                                          //                                   *
    * @param   QList<CdmObject*>& p_rqlViews           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:40:50 2012----------*/
    void GetReportList(QList<CdmObject*>& p_rqlViews);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:41:50 2012-------*
    * @method  CwmsReportManager::GetReport                  // public                            *
    * @return  CwmsPrintingTemplate                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:41:50 2012----------*/
    CwmsPrintingTemplate GetReport(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 14:43:22 2012-------*
    * @method  CwmsReportManager::GetReport                  // public                            *
    * @return  CwmsPrintingTemplate                          //                                   *
    * @param  qint64 p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 14:43:22 2012----------*/
    CwmsPrintingTemplate GetReport(qint64 p_lObjectId);

   public:
   /** +-=---------------------------------------------------------Mi 20. Feb 16:20:42 2013-------*
    * @method  CwmsReportManager::GetClassesWithReports      // public                            *
    * @return  void                                          //                                   *
    * @param   QStringList& p_rqlClasses                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 20. Feb 16:20:42 2013----------*/
    void GetClassesWithReports(QStringList& p_rqlClasses);

   public:
   /** +-=---------------------------------------------------------Mi 20. Feb 16:21:19 2013-------*
    * @method  CwmsReportManager::GetReportsByClassKeyname   // public                            *
    * @return  CdmQueryEnhanced*                             //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 20. Feb 16:21:19 2013----------*/
    CdmQueryEnhanced* GetReportsByClassKeyname(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Mi 20. Feb 16:22:09 2013-------*
    * @method  CwmsReportManager::GetReportsByClassKeyname   // public                            *
    * @return  CdmQueryEnhanced*                             //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EwmsTemplateType p_eType                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 20. Feb 16:22:09 2013----------*/
    CdmQueryEnhanced* GetReportsByClassKeyname(QString p_qstrKeyname, EwmsTemplateType p_eType);

   public:
   /** +-=---------------------------------------------------------Di 26. Feb 15:57:00 2013-------*
    * @method  CwmsReportManager::GetPdf                     // public                            *
    * @return  QByteArray                                    //                                   *
    * @param  qint64 p_ObjectListId                           //                                   *
    * @param   QString p_qstrTemplate                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 15:57:00 2013----------*/
    QByteArray GetPdf(qint64 p_ObjectListId, QString p_qstrTemplate);

   public:
   /** +-=---------------------------------------------------------Di 26. Feb 15:57:19 2013-------*
    * @method  CwmsReportManager::GetPdf                     // public                            *
    * @return  QByteArray                                    //                                   *
    * @param  qint64 p_ObjectListId                           //                                   *
    * @param  qint64 p_ObjectId                               //                                   *
    * @param   QString p_qstrTemplate                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 15:57:19 2013----------*/
    QByteArray GetPdf(qint64 p_ObjectListId,qint64 p_ObjectId, QString p_qstrTemplate);

   public:
   /** +-=---------------------------------------------------------Di 26. Feb 15:57:38 2013-------*
    * @method  CwmsReportManager::GetPdf                     // public                            *
    * @return  QByteArray                                    //                                   *
    * @param  qint64 p_ObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 15:57:38 2013----------*/
    QByteArray GetPdf(qint64 p_ObjectListId);

   public:
   /** +-=---------------------------------------------------------Di 26. Feb 15:57:52 2013-------*
    * @method  CwmsReportManager::GetPdf                     // public                            *
    * @return  QByteArray                                    //                                   *
    * @param  qint64 p_ObjectListId                           //                                   *
    * @param  qint64 p_ObjectId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 15:57:52 2013----------*/
    QByteArray GetPdf(qint64 p_ObjectListId,qint64 p_ObjectId);

   private:
   /** +-=---------------------------------------------------------Di 26. Feb 15:59:55 2013-------*
    * @method  CwmsReportManager::FindObjectListForPDFCreation // private                         *
    * @return  CdmObjectContainer*                                //                                   *
    * @param  qint64 p_lObjectListId                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 15:59:55 2013----------*/
    CdmObjectContainer* FindObjectListForPDFCreation(qint64 p_lObjectListId);

   public:
   /** +-=---------------------------------------------------------Mi 27. Feb 09:24:24 2013-------*
    * @method  CwmsReportManager::GetDefaultReportByClassKeyname // public                        *
    * @return  CwmsPrintingTemplate                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EwmsTemplateType p_eType                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 27. Feb 09:24:24 2013----------*/
    CwmsPrintingTemplate GetDefaultReportByClassKeyname(QString p_qstrKeyname,
                                                        EwmsTemplateType p_eType);

    static IwmsPrinting *GetPrintingObject();
    static bool HasPrintingPlugin();
    static void OpenReportEditor(qint64 p_lObjectId, QWidget* p_pParent);
	static void OpenReportEditor(CdmObject* p_pObject, QWidget* p_pParent);

private:
   /** +-=---------------------------------------------------------Mi 27. Feb 09:37:16 2013-------*
    * @method  CwmsReportManager::CreatePDFOutput            // private                           *
    * @return  QByteArray                                    //                                   *
    * @param   CwmsPrinting& p_rPrinting                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 27. Feb 09:37:16 2013----------*/
    QByteArray CreatePDFOutput(IwmsPrinting& p_rPrinting);

public:
    static void LoadReportEngine();
    static void LoadPlugin(QString p_qstrFileName);
    static void RemovePlugin(QString p_qstrName);
    CdmQueryEnhanced *GetReportsByClassKeynameAndLanguage(QString p_qstrKeyname, EwmsTemplateType p_eType, QString p_qstrLanguage);
    static void PrintDefaultForContainer(CdmObjectContainer *p_pContainer);
    static void PrintDefaultForObject(CdmObject *p_pObject);
    static void Print(CdmObject *p_pCdmTemplateObject, CdmObjectContainer *p_pContainer);
    static void Print(CdmObject *p_pCdmTemplateObject, CdmObject *p_pObject);
    static bool HasDefaultPrintingTemplate(CdmObject *p_pObject);
    static bool HasDefaultPrintingTemplate(CdmObjectContainer *p_pContainer);
};

#endif // CWMSREPORTMANAGER_H
