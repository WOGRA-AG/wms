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
    CwmsViewObjectListEditorWidget( QWidget* p_pqwParent);
    virtual ~CwmsViewObjectListEditorWidget( );

   private:
    void FillDialog();

   public:
    void AddView(QString p_qstrViewName);

   private:
    CwmsView LoadView(QString p_qstrName);

    private slots:
    void ViewSelectionChangedSlot( );

   public:
    QListWidgetItem* GetSelectedView();

   private:
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
