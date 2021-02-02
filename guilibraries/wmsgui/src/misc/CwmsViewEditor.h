/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsViewEditor.h
 ** Started Implementation: 2012/08/24
 ** Description:
 ** 
 ** implements the editor for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSVIEWEDITOR_H
#define CWMSVIEWEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CwmsView.h"
#include "ui_CwmsViewEditor.h"
#include "wmsgui.h"

// Forwards


// TypeDefs


/* 
 * This class implements the editor for views
 */
class WMSGUI_API CwmsViewEditor : public QDialog, public Ui::CwmsViewEditorClass
{
   Q_OBJECT

   private:
      CwmsView m_cView;
   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:56:17 2012-------*
    * @method  CwmsViewEditor::CwmsViewEditor                // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:56:17 2012----------*/
    CwmsViewEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:56:41 2012-------*
    * @method  CwmsViewEditor::~CwmsViewEditor               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsViewEditor                                             *
    *----------------last changed: -----------------------------Fr 24. Aug 11:56:41 2012----------*/
    virtual ~CwmsViewEditor( );

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:57:01 2012-------*
    * @method  CwmsViewEditor::FillDialog                    // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsView p_cCwmsView                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:57:01 2012----------*/
    void FillDialog(CwmsView p_cCwmsView);

    private slots:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:57:19 2012-------*
    * @method  CwmsViewEditor::OKClickedSlot                 // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:57:19 2012----------*/
void OKClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:57:32 2012-------*
    * @method  CwmsViewEditor::ShowResultClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:57:32 2012----------*/
void ShowResultClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:58:23 2012-------*
    * @method  CwmsViewEditor::CurrentTabChangedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:58:23 2012----------*/
void CurrentTabChangedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:58:44 2012-------*
    * @method  CwmsViewEditor::Validate                      // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:58:44 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 24. Aug 13:19:34 2012-------*
    * @method  CwmsViewEditor::SaveData                      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 13:19:34 2012----------*/
    void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Fr 24. Aug 12:01:21 2012-------*
    * @method  CwmsViewEditor::CheckClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 12:01:21 2012----------*/
void CheckClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 13:56:50 2012-------*
    * @method  CwmsViewEditor::Edit                          // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsView p_cView                              //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 13:56:50 2012----------*/
    static void Edit(CwmsView p_cView, bool p_bNew, QWidget* p_pqwParent);
};

#endif // CWMSVIEWEDITOR_H
