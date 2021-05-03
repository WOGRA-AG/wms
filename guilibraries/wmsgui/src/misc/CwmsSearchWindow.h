/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsSearchWindow.h
 ** Started Implementation: 2012/09/06
 ** Description:
 ** 
 ** implements the user for generic search
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSEARCHWINDOW_H
#define CWMSSEARCHWINDOW_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>
#include <QList>

// WMS Includes
#include "CdmQueryEnhanced.h"
#include "CdmQueryModel.h"

// Own Includes
#include "wmsgui.h"
#include "CwmsApplicationModule.h"
#include "ui_CwmsSearchWindow.h"

// Forwards
class CdmObjectContainer;
class CwmsRuntime;
class QMenu;
class QToolBar;

// TypeDefs


/* 
 * This class implements the user for generic search
 */
class WMSGUI_API CwmsSearchWindow : public QWidget, public Ui::CwmsSearchWindowClass
{
   Q_OBJECT

   private:
      CdmQueryEnhanced* m_pCdmQuery;
      CdmQueryModel m_CdmModel;
      CdmObject* m_rpCdmPrintingTemplate;
      QList<QString> m_qllResultMembers;
      QMenu* m_pMenu;
      QToolBar* m_pToolBar;

   public:
   /** +-=---------------------------------------------------------Do 6. Sep 19:01:24 2012--------*
    * @method  CwmsSearchWindow::CwmsSearchWindow            // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 19:01:24 2012-----------*/
    CwmsSearchWindow( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 6. Sep 19:01:51 2012--------*
    * @method  CwmsSearchWindow::~CwmsSearchWindow           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsSearchWindow                                           *
    *----------------last changed: -----------------------------Do 6. Sep 19:01:51 2012-----------*/
    virtual ~CwmsSearchWindow( );

   public:
   /** +-=---------------------------------------------------------Do 6. Sep 19:02:39 2012--------*
    * @method  CwmsSearchWindow::FillDialog                  // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 19:02:39 2012-----------*/
    void FillDialog(CdmObjectContainer* p_pContainer);

    private slots:
   /** +-=---------------------------------------------------------Do 6. Sep 19:08:06 2012--------*
    * @method  CwmsSearchWindow::EditClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 19:08:06 2012-----------*/
void EditClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 6. Sep 19:08:15 2012--------*
    * @method  CwmsSearchWindow::SearchSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 19:08:15 2012-----------*/
void SearchSlot( );

   private:
   /** +-=---------------------------------------------------------Do 6. Sep 19:15:15 2012--------*
    * @method  CwmsSearchWindow::AddResultMembers            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 19:15:15 2012-----------*/
    void AddResultMembers();

   public:
   /** +-=---------------------------------------------------------Fr 14. Sep 12:36:19 2012-------*
    * @method  CwmsSearchWindow::AddSearchMember             // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrSearchMember                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Sep 12:36:19 2012----------*/
    void AddSearchMember(QString p_qstrSearchMember);

   public:
   /** +-=---------------------------------------------------------Di 18. Sep 10:39:34 2012-------*
    * @method  CwmsSearchWindow::Initialize                  // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:39:34 2012----------*/
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);

    CdmObject *GetSelectedObject();
    void AddResultMember(QString p_qstrMember);
    void SetPrintVisibility(bool p_bVisible);
    void SetExportVisibility(bool p_bVisible);
    void SetImportVisibility(bool p_bVisible);
    void SetDeleteVisibility(bool p_bVisible);
    void SetEditVisibility(bool p_bVisible);
    void SaveAsCsvClickedSlot();
public slots:
    void DeleteClickedSlot();
    void NewClickedSlot();
    void CopyClickedSlot();
private:
   /** +-=---------------------------------------------------------Di 18. Sep 10:39:40 2012-------*
    * @method  CwmsSearchWindow::SetModule                   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:39:40 2012----------*/
    void SetModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Di 23. Jul 13:23:04 2013-------*
    * @method  CwmsSearchWindow::ConnectRuntime              // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 23. Jul 13:23:04 2013----------*/
    void ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule p_cModule);

    private slots:
   /** +-=---------------------------------------------------------Di 18. Sep 10:51:39 2012-------*
    * @method  CwmsSearchWindow::PrintClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:51:39 2012----------*/
void PrintClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 7. Feb 09:46:31 2013--------*
    * @method  CwmsSearchWindow::ExportClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 09:46:31 2013-----------*/
void ExportClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 7. Feb 09:46:42 2013--------*
    * @method  CwmsSearchWindow::ImportClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 09:46:42 2013-----------*/
void ImportClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Di 18. Sep 10:54:13 2012-------*
    * @method  CwmsSearchWindow::Print                       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:54:13 2012----------*/
    void Print();

   private:
   /** +-=---------------------------------------------------------Di 18. Sep 10:54:19 2012-------*
    * @method  CwmsSearchWindow::Print                       // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:54:19 2012----------*/
    void Print(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Do 7. Feb 09:46:25 2013--------*
    * @method  CwmsSearchWindow::OpenExportConfigurator      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 09:46:25 2013-----------*/
    void OpenExportConfigurator();

   private:
   /** +-=---------------------------------------------------------Do 7. Feb 09:46:37 2013--------*
    * @method  CwmsSearchWindow::OpenImportConfigurator      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 09:46:37 2013-----------*/
    void OpenImportConfigurator();
};

#endif // CWMSSEARCHWINDOW_H
