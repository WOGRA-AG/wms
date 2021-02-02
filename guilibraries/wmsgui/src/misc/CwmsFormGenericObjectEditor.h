/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFormGenericObjectEditor.h
 ** Started Implementation: 2012/09/12
 ** Description:
 ** 
 ** implements the editor for generic forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSFORMGENERICOBJECTEDITOR_H
#define CWMSFORMGENERICOBJECTEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "CwmsFormObject.h"
#include "CwmsPrintingTemplate.h"
#include "ui_CwmsFormGenericObjectEditor.h"
#include "wmsgui.h"

// Forwards
class CdmClass;
class CdmObject;

// TypeDefs


/* 
 * This class implements the editor for generic forms
 */
class WMSGUI_API CwmsFormGenericObjectEditor : public QDialog, public Ui::CwmsFormGenericObjectEditorClass
{
   Q_OBJECT

   private:
      CwmsFormObject m_cForm;
      CwmsPrintingTemplate m_cTemplate;
      CdmClass* m_rpCdmClass;

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:10:10 2012-------*
    * @method  CwmsFormGenericObjectEditor::CwmsFormGenericObjectEditor // public                 *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:10:10 2012----------*/
    CwmsFormGenericObjectEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:11:22 2012-------*
    * @method  CwmsFormGenericObjectEditor::~CwmsFormGenericObjectEditor // public, virtual       *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFormGenericObjectEditor                                *
    *----------------last changed: -----------------------------Mi 12. Sep 14:11:22 2012----------*/
    virtual ~CwmsFormGenericObjectEditor( );

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:13:02 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillDialog       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsFormObject p_cForm                        //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:13:02 2012----------*/
    void FillDialog(CwmsFormObject p_cForm, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:26:29 2012-------*
    * @method  CwmsFormGenericObjectEditor::Validate         // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:26:29 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 13:56:12 2012-------*
    * @method  CwmsFormGenericObjectEditor::SaveData         // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 13:56:12 2012----------*/
    bool SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:26:05 2012-------*
    * @method  CwmsFormGenericObjectEditor::OKClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:26:05 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Fr 14. Dez 13:53:05 2012-------*
    * @method  CwmsFormGenericObjectEditor::SetClass         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrUri                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 13:53:05 2012----------*/
    void SetClass(QString p_qstrUri);

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:34:30 2012-------*
    * @method  CwmsFormGenericObjectEditor::SetClass         // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:34:30 2012----------*/
    void SetClass(CdmClass* p_pCdmClass);

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:34:51 2012-------*
    * @method  CwmsFormGenericObjectEditor::SelectPrintingTemplateClickedSlot // private, slots   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:34:51 2012----------*/
void SelectPrintingTemplateClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:35:28 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillReport       // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:35:28 2012----------*/
    void FillReport(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:36:51 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillVisibleMembers // private                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:36:51 2012----------*/
    void FillVisibleMembers();

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:37:46 2012-------*
    * @method  CwmsFormGenericObjectEditor::AddVisibleMemberClickedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:37:46 2012----------*/
void AddVisibleMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:38:13 2012-------*
    * @method  CwmsFormGenericObjectEditor::RemoveVisibleMemberClickedSlot // private, slots      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:38:13 2012----------*/
void RemoveVisibleMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:38:41 2012-------*
    * @method  CwmsFormGenericObjectEditor::VisibleMemberUpClickedSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:38:41 2012----------*/
void VisibleMemberUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:38:47 2012-------*
    * @method  CwmsFormGenericObjectEditor::VisibleMemberDownClickedSlot // private, slots        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:38:47 2012----------*/
void VisibleMemberDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:40:37 2012-------*
    * @method  CwmsFormGenericObjectEditor::SelectClassClickedSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:40:37 2012----------*/
void SelectClassClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:50:08 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillDefaultValues // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:50:08 2012----------*/
    void FillDefaultValues();

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:50:27 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillObjectReferences // private                       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:50:27 2012----------*/
    void FillObjectReferences();

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 14:50:48 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillDisplayTypes // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 14:50:48 2012----------*/
    void FillDisplayTypes();

   private:
   /** +-=---------------------------------------------------------Mi 12. Sep 15:29:46 2012-------*
    * @method  CwmsFormGenericObjectEditor::UpdateComboBoxes // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 15:29:46 2012----------*/
    void UpdateComboBoxes();

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:10:09 2012-------*
    * @method  CwmsFormGenericObjectEditor::AddDisplayTypeClickedSlot // private, slots           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:10:09 2012----------*/
void AddDisplayTypeClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:09:39 2012-------*
    * @method  CwmsFormGenericObjectEditor::RemoveDisplayTypeClickedSlot // private, slots        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:09:39 2012----------*/
void RemoveDisplayTypeClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:11:40 2012-------*
    * @method  CwmsFormGenericObjectEditor::AddObjectReferenceClickedSlot // private, slots       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:11:40 2012----------*/
void AddObjectReferenceClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:11:30 2012-------*
    * @method  CwmsFormGenericObjectEditor::RemoveObjectReferenceClickedSlot // private, slots    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:11:30 2012----------*/
void RemoveObjectReferenceClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:12:25 2012-------*
    * @method  CwmsFormGenericObjectEditor::AddDefaultValuesClickedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:12:25 2012----------*/
void AddDefaultValuesClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:12:38 2012-------*
    * @method  CwmsFormGenericObjectEditor::RemoveDefaultValuesClickedSlot // private, slots      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:12:38 2012----------*/
void RemoveDefaultValuesClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:36:09 2012-------*
    * @method  CwmsFormGenericObjectEditor::GetSelectedMember // public                           *
    * @return  QListWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:36:09 2012----------*/
    QListWidgetItem* GetSelectedMember();

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 16:45:53 2012-------*
    * @method  CwmsFormGenericObjectEditor::EditForm         // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsFormObject p_cForm                        //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 16:45:53 2012----------*/
    static void EditForm(CwmsFormObject p_cForm, bool p_bNew, QWidget* p_pqwParent);

    private slots:
   /** +-=---------------------------------------------------------Fr 14. Dez 09:50:39 2012-------*
    * @method  CwmsFormGenericObjectEditor::FunctionDownClickedSlot // private, slots             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 09:50:39 2012----------*/
void FunctionDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 14. Dez 09:50:42 2012-------*
    * @method  CwmsFormGenericObjectEditor::FunctionUpClickedSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 09:50:42 2012----------*/
void FunctionUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 14. Dez 09:50:47 2012-------*
    * @method  CwmsFormGenericObjectEditor::RemoveFunctionClickedSlot // private, slots           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 09:50:47 2012----------*/
void RemoveFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 14. Dez 09:50:53 2012-------*
    * @method  CwmsFormGenericObjectEditor::AddFunctionClickedSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 09:50:53 2012----------*/
void AddFunctionClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 09:51:33 2012-------*
    * @method  CwmsFormGenericObjectEditor::FillFunctions    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 09:51:33 2012----------*/
    void FillFunctions();
};

#endif // CWMSFORMGENERICOBJECTEDITOR_H
