/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectObjectListEditorWidget.h
 ** Started Implementation: 2012/09/17
 ** Description:
 ** 
 ** implements the editor for object objectlists
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSOBJECTOBJECTLISTEDITORWIDGET_H
#define CWMSOBJECTOBJECTLISTEDITORWIDGET_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmQueryModel.h"


// Own Includes
#include "wmsgui.h"
#include "CwmsApplicationModule.h"
#include "ui_CwmsObjectObjectListEditorWidget.h"

// Forwards
class CwmsRuntime;
class CdmQueryEnhanced;

// TypeDefs


/* 
 * This class implements the editor for object objectlists
 */
class WMSGUI_API CwmsObjectContainerEditorWidget : public QWidget, public Ui::CwmsObjectObjectListEditorWidgetClass
{
   Q_OBJECT

   private:
      QString m_qstrKeyname;
      QString m_qstrEditorWql;
      CdmQueryEnhanced* m_pCdmQuery;
      CdmQueryModel m_cModel;

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:31:18 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::CwmsObjectObjectListEditorWidget // public       *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 10:31:18 2012----------*/
    CwmsObjectContainerEditorWidget( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:31:51 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::~CwmsObjectObjectListEditorWidget // public, virtual*
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectObjectListEditorWidget                           *
    *----------------last changed: -----------------------------Mo 17. Sep 10:31:51 2012----------*/
    virtual ~CwmsObjectContainerEditorWidget( );

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:32:19 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::FillDialog  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 10:32:19 2012----------*/
    void FillDialog();


   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:37:50 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::SetModule   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 10:37:50 2012----------*/
    void SetModule(CwmsApplicationModule p_cModule);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 10:36:05 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::Initialize  // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 10:36:05 2012----------*/
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 11:04:16 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::SetView     // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsView p_cCwmsView                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 11:04:16 2012----------*/
    void SetView(CwmsView p_cCwmsView);

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 11:20:20 2012-------*
    * @method  CwmsObjectObjectListEditorWidget::TreeViewSelectionChangedSlot // private, slots   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 11:20:20 2012----------*/
void TreeViewSelectionChangedSlot( );
};

#endif // CWMSOBJECTOBJECTLISTEDITORWIDGET_H
