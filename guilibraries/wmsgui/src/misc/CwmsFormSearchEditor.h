/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFormStandardObjectListEditor.h
 ** Started Implementation: 2012/09/10
 ** Description:
 ** 
 ** implements the editor for searchform configuration
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSFORMSEARCHEDITOR_H
#define CWMSFORMSEARCHEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "CwmsView.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsFormSearch.h"
#include "ui_CwmsFormSearchEditor.h"

// Forwards
class CdmClass;

// TypeDefs


/* 
 * This class implements the editor for standardobjectlistform configuration
 */
class WMSGUI_API CwmsFormSearchEditor : public QDialog, public Ui::CwmsFormSearchEditorClass
{
   Q_OBJECT

   private:
      CdmObjectContainer* m_rpContainer;
      CwmsFormSearch m_cForm;
      CwmsPrintingTemplate m_cTemplate;




   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:39:00 2012-------*
    * @method  CwmsFormSearchEditor::CwmsFormSearchEditor    // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:39:00 2012----------*/
    CwmsFormSearchEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:39:13 2012-------*
    * @method  CwmsFormSearchEditor::~CwmsFormSearchEditor   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFormStandardObjectListEditor                           *
    *----------------last changed: -----------------------------Mo 17. Sep 18:39:13 2012----------*/
    virtual ~CwmsFormSearchEditor( );

   protected:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:39:59 2012-------*
    * @method  CwmsFormSearchEditor::FillDialog              // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CwmsFormSearch p_cForm                        //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:39:59 2012----------*/
    virtual void FillDialog(CwmsFormSearch p_cForm, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:49:08 2012-------*
    * @method  CwmsFormSearchEditor::FillReport              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:49:08 2012----------*/
    void FillReport(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:49:21 2012-------*
    * @method  CwmsFormSearchEditor::FillFunctions           // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:49:21 2012----------*/
    void FillFunctions();

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:49:30 2012-------*
    * @method  CwmsFormSearchEditor::FillSearchMembers       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:49:30 2012----------*/
    void FillSearchMembers();

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:49:41 2012-------*
    * @method  CwmsFormSearchEditor::FillVisibleMembers      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:49:41 2012----------*/
    void FillVisibleMembers();

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:50:39 2012-------*
    * @method  CwmsFormSearchEditor::SetObjectList           // public                            *
    * @return  void                                          //                                   *
    * @param   int p_lObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:50:39 2012----------*/
    void SetObjectList(int p_lObjectListId);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:51:52 2012-------*
    * @method  CwmsFormSearchEditor::SetObjectList           // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:51:52 2012----------*/
    void SetObjectList(CdmObjectContainer* p_pContainer);

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:52:33 2012-------*
    * @method  CwmsFormSearchEditor::SelectPrintingTemplateClickedSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:52:33 2012----------*/
void SelectPrintingTemplateClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:52:49 2012-------*
    * @method  CwmsFormSearchEditor::SelectObjectListClickedSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:52:49 2012----------*/
void SelectObjectListClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:54:14 2012-------*
    * @method  CwmsFormSearchEditor::AddFunctionClickedSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:54:14 2012----------*/
void AddFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:54:19 2012-------*
    * @method  CwmsFormSearchEditor::AddVisibleMemberClickedSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:54:19 2012----------*/
void AddVisibleMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:54:24 2012-------*
    * @method  CwmsFormSearchEditor::AddSearchMemberClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:54:24 2012----------*/
void AddSearchMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:54:29 2012-------*
    * @method  CwmsFormSearchEditor::RemoveFunctionClickedSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:54:29 2012----------*/
void RemoveFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:54:36 2012-------*
    * @method  CwmsFormSearchEditor::RemoveVisibleMemberClickedSlot // private, slots             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:54:36 2012----------*/
void RemoveVisibleMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:07 2012-------*
    * @method  CwmsFormSearchEditor::RemoveSearchMemberClickedSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:07 2012----------*/
void RemoveSearchMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:17 2012-------*
    * @method  CwmsFormSearchEditor::VisibleMemberUpClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:17 2012----------*/
void VisibleMemberUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:22 2012-------*
    * @method  CwmsFormSearchEditor::VisibleMemberDownClickedSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:22 2012----------*/
void VisibleMemberDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:31 2012-------*
    * @method  CwmsFormSearchEditor::FunctionUpClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:31 2012----------*/
void FunctionUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:41 2012-------*
    * @method  CwmsFormSearchEditor::FunctionDownClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:41 2012----------*/
void FunctionDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:49 2012-------*
    * @method  CwmsFormSearchEditor::SearchMemberUpClickedSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:49 2012----------*/
void SearchMemberUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:56:57 2012-------*
    * @method  CwmsFormSearchEditor::SearchMemberDownClickedSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:56:57 2012----------*/
void SearchMemberDownClickedSlot( );

   protected:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:57:32 2012-------*
    * @method  CwmsFormSearchEditor::Validate                // protected, virtual                *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:57:32 2012----------*/
    virtual bool Validate();

   protected:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:58:03 2012-------*
    * @method  CwmsFormSearchEditor::SaveData                // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:58:03 2012----------*/
    virtual void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:58:14 2012-------*
    * @method  CwmsFormSearchEditor::OKClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:58:14 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:58:32 2012-------*
    * @method  CwmsFormSearchEditor::EditForm                // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsFormSearch p_cForm                        //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:58:32 2012----------*/
    static void EditForm(CwmsFormSearch p_cForm, bool p_bNew, QWidget* p_pqwParent);
};

#endif // CWMSFORMSTANDARDOBJECTLISTEDITOR_H
