/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsViewObjectListEditorWidget.h
 ** Started Implementation: 2012/09/09
 ** Description:
 ** 
 ** implements an objectlisteditor with different views for user selection
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSVIEWOBJECTLISTEDITORWIDGET_H
#define CWMSVIEWOBJECTLISTEDITORWIDGET_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>


// Own Includes
#include "CwmsView.h"
#include "ui_CwmsViewObjectListEditorWidget.h"
#include "wmsgui.h"

// Forwards


// TypeDefs


/* 
 * This class implements an objectlisteditor with different views for user selection
 */
class WMSGUI_API CwmsViewObjectListEditorWidget : public QWidget, public Ui::CwmsViewObjectListEditorWidgetClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------So 9. Sep 12:30:27 2012--------*
    * @method  CwmsViewObjectListEditorWidget::CwmsViewObjectListEditorWidget // public           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 12:30:27 2012-----------*/
    CwmsViewObjectListEditorWidget( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------So 9. Sep 12:31:03 2012--------*
    * @method  CwmsViewObjectListEditorWidget::~CwmsViewObjectListEditorWidget // public, virtual *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsViewObjectListEditorWidget                             *
    *----------------last changed: -----------------------------So 9. Sep 12:31:03 2012-----------*/
    virtual ~CwmsViewObjectListEditorWidget( );

   private:
   /** +-=---------------------------------------------------------So 9. Sep 12:31:11 2012--------*
    * @method  CwmsViewObjectListEditorWidget::FillDialog    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 12:31:11 2012-----------*/
    void FillDialog();

   public:
   /** +-=---------------------------------------------------------Fr 14. Sep 10:39:14 2012-------*
    * @method  CwmsViewObjectListEditorWidget::AddView       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrViewName                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Sep 10:39:14 2012----------*/
    void AddView(QString p_qstrViewName);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 12:32:19 2012--------*
    * @method  CwmsViewObjectListEditorWidget::LoadView      // private                           *
    * @return  CwmsView                                      //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 12:32:19 2012-----------*/
    CwmsView LoadView(QString p_qstrName);

    private slots:
   /** +-=---------------------------------------------------------So 9. Sep 12:36:30 2012--------*
    * @method  CwmsViewObjectListEditorWidget::ViewSelectionChangedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 12:36:30 2012-----------*/
void ViewSelectionChangedSlot( );

   public:
   /** +-=---------------------------------------------------------So 9. Sep 12:40:34 2012--------*
    * @method  CwmsViewObjectListEditorWidget::GetSelectedView // public                          *
    * @return  QListWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 12:40:34 2012-----------*/
    QListWidgetItem* GetSelectedView();

   private:
   /** +-=---------------------------------------------------------Di 23. Jul 13:21:01 2013-------*
    * @method  CwmsViewObjectListEditorWidget::ConnectRuntime // private                          *
    * @return  void                                          //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 23. Jul 13:21:01 2013----------*/
    void ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:36:56 2012-------*
    * @method  CwmsViewObjectListEditorWidget::SetModule     // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 10:36:56 2012----------*/
    void SetModule(CwmsApplicationModule p_cModule);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:36:40 2012-------*
    * @method  CwmsViewObjectListEditorWidget::Initialize    // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 10:36:40 2012----------*/
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);
};

#endif // CWMSVIEWOBJECTLISTEDITORWIDGET_H
