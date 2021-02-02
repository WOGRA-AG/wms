/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFormViewEditor.h
 ** Started Implementation: 2012/09/11
 ** Description:
 ** 
 ** implements the editor for view forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSFORMVIEWEDITOR_H
#define CWMSFORMVIEWEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "CwmsView.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsFormView.h"
#include "ui_CwmsFormViewEditor.h"

// Forwards


// TypeDefs


/* 
 * This class implements the editor for view forms
 */
class WMSGUI_API CwmsFormViewEditor : public QDialog, public Ui::CwmsFormViewEditorClass
{
   Q_OBJECT

   private:
      CwmsFormView m_cForm;
      CwmsPrintingTemplate m_cTemplate;

   public:
   /** +-=---------------------------------------------------------Di 11. Sep 13:33:54 2012-------*
    * @method  CwmsFormViewEditor::CwmsFormViewEditor        // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:33:54 2012----------*/
    CwmsFormViewEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 11. Sep 13:34:17 2012-------*
    * @method  CwmsFormViewEditor::~CwmsFormViewEditor       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFormViewEditor                                         *
    *----------------last changed: -----------------------------Di 11. Sep 13:34:17 2012----------*/
    virtual ~CwmsFormViewEditor( );

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 13:37:05 2012-------*
    * @method  CwmsFormViewEditor::FillViews                 // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:37:05 2012----------*/
    void FillViews();

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 13:37:26 2012-------*
    * @method  CwmsFormViewEditor::FillReport                // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:37:26 2012----------*/
    void FillReport(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 14:44:21 2012-------*
    * @method  CwmsFormViewEditor::FillDialog                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsFormView p_cForm                          //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:44:21 2012----------*/
    void FillDialog(CwmsFormView p_cForm, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 13:53:48 2012-------*
    * @method  CwmsFormViewEditor::Validate                  // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:53:48 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 13:53:57 2012-------*
    * @method  CwmsFormViewEditor::SaveData                  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:53:57 2012----------*/
    void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 13:54:07 2012-------*
    * @method  CwmsFormViewEditor::OKClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:54:07 2012----------*/
void OKClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 13:59:43 2012-------*
    * @method  CwmsFormViewEditor::AddViewClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 13:59:43 2012----------*/
void AddViewClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 14:00:10 2012-------*
    * @method  CwmsFormViewEditor::RemoveViewClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:00:10 2012----------*/
void RemoveViewClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 14:00:57 2012-------*
    * @method  CwmsFormViewEditor::ViewMemberDownClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:00:57 2012----------*/
void ViewDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 14:01:04 2012-------*
    * @method  CwmsFormViewEditor::ViewMemberUpClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:01:04 2012----------*/
void ViewUpClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Di 11. Sep 14:03:06 2012-------*
    * @method  CwmsFormViewEditor::EditForm                  // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsFormView p_cForm                          //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:03:06 2012----------*/
    static void EditForm(CwmsFormView p_cForm, bool p_bNew, QWidget* p_pqwParent);

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 14:36:21 2012-------*
    * @method  CwmsFormViewEditor::SelectPrintingTemplateClickedSlot // private, slots            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:36:21 2012----------*/
void SelectPrintingTemplateClickedSlot( );

};

#endif // CWMSFORMVIEWEDITOR_H
