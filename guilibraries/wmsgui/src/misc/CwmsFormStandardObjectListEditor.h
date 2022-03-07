/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFormStandardContainerEditor.h
 ** Started Implementation: 2012/09/10
 ** Description:
 ** 
 ** implements the editor for standardobjectlistform configuration
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CwmsFormStandardContainerEditor_H
#define CwmsFormStandardContainerEditor_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "CwmsView.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsFormStandardObjectList.h"
#include "ui_CwmsFormStandardObjectListEditor.h"

// Forwards
class CdmClass;

// TypeDefs


/* 
 * This class implements the editor for standardobjectlistform configuration
 */
class WMSGUI_API CwmsFormStandardContainerEditor : public QDialog, public Ui::CwmsFormStandardObjectListEditorClass
{
   Q_OBJECT

   private:
      const CdmClass* m_rpCdmClass;
      CwmsFormStandardContainer m_cForm;
      CwmsView m_cView;
      CwmsPrintingTemplate m_cTemplate;

   protected:
      CwmsView m_cSelectionView;
      CdmObjectContainer* m_rpCdmSelectionList;

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:02:33 2012-------*
    * @method  CwmsFormStandardContainerEditor::CwmsFormStandardContainerEditor // public       *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:02:33 2012----------*/
    CwmsFormStandardContainerEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:02:58 2012-------*
    * @method  CwmsFormStandardContainerEditor::~CwmsFormStandardContainerEditor // public, virtual*
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFormStandardContainerEditor                           *
    *----------------last changed: -----------------------------Mo 10. Sep 14:02:58 2012----------*/
    virtual ~CwmsFormStandardContainerEditor( );

   protected:
   /** +-=---------------------------------------------------------Di 11. Sep 15:44:27 2012-------*
    * @method  CwmsFormStandardContainerEditor::FillDialog  // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CwmsFormStandardObjectList p_cForm            //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 15:44:27 2012----------*/
    virtual void FillDialog(CwmsFormStandardContainer p_cForm, bool p_bNew);

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:04:22 2012-------*
    * @method  CwmsFormStandardContainerEditor::AddFunctionClickedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:04:22 2012----------*/
void AddFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:08:54 2012-------*
    * @method  CwmsFormStandardContainerEditor::AddVisibleMemberClickedSlot // private, slots    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:08:54 2012----------*/
void AddVisibleMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:10:09 2012-------*
    * @method  CwmsFormStandardContainerEditor::AddSearchMemberClickedSlot // private, slots     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:10:09 2012----------*/
void AddSearchMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:11:02 2012-------*
    * @method  CwmsFormStandardContainerEditor::RemoveFunctionClickedSlot // private, slots      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:11:02 2012----------*/
void RemoveFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:11:15 2012-------*
    * @method  CwmsFormStandardContainerEditor::RemoveVisibleMemberClickedSlot // private, slots *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:11:15 2012----------*/
void RemoveVisibleMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:11:26 2012-------*
    * @method  CwmsFormStandardContainerEditor::RemoveSearchMemberClickedSlot // private, slots  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:11:26 2012----------*/
void RemoveSearchMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:11:42 2012-------*
    * @method  CwmsFormStandardContainerEditor::VisibleMemberUpClickedSlot // private, slots     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:11:42 2012----------*/
void VisibleMemberUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:12:04 2012-------*
    * @method  CwmsFormStandardContainerEditor::VisibleMemberDownClickedSlot // private, slots   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:12:04 2012----------*/
void VisibleMemberDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:12:16 2012-------*
    * @method  CwmsFormStandardContainerEditor::FunctionUpClickedSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:12:16 2012----------*/
void FunctionUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:12:30 2012-------*
    * @method  CwmsFormStandardContainerEditor::FunctionDownClickedSlot // private, slots        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:12:30 2012----------*/
void FunctionDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:12:42 2012-------*
    * @method  CwmsFormStandardContainerEditor::SearchMemberUpClickedSlot // private, slots      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:12:42 2012----------*/
void SearchMemberUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:13:04 2012-------*
    * @method  CwmsFormStandardContainerEditor::SearchMemberDownClickedSlot // private, slots    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:13:04 2012----------*/
void SearchMemberDownClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:14:48 2012-------*
    * @method  CwmsFormStandardContainerEditor::SetClass    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrUri                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:14:48 2012----------*/
    void SetClass(QString p_qstrUri);

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:18:33 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectClassClickedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:18:33 2012----------*/
void SelectClassClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:05:01 2013-------*
    * @method  CwmsFormStandardContainerEditor::SetClass    // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmClass* p_pCdmClass                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:05:01 2013----------*/
    void SetClass(const CdmClass* p_pCdmClass);

   protected:
   /** +-=---------------------------------------------------------Di 11. Sep 15:44:43 2012-------*
    * @method  CwmsFormStandardContainerEditor::Validate    // protected, virtual                *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 15:44:43 2012----------*/
    virtual bool Validate();

   protected:
   /** +-=---------------------------------------------------------Di 11. Sep 15:44:52 2012-------*
    * @method  CwmsFormStandardContainerEditor::SaveData    // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 15:44:52 2012----------*/
    virtual void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:22:42 2012-------*
    * @method  CwmsFormStandardContainerEditor::OKClickedSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:22:42 2012----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:38:13 2012-------*
    * @method  CwmsFormStandardContainerEditor::FillFunctions // private                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:38:13 2012----------*/
    void FillFunctions();

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:38:25 2012-------*
    * @method  CwmsFormStandardContainerEditor::FillSearchMembers // private                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:38:25 2012----------*/
    void FillSearchMembers();

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 14:38:36 2012-------*
    * @method  CwmsFormStandardContainerEditor::FillVisibleMembers // private                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 14:38:36 2012----------*/
    void FillVisibleMembers();

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 15:33:13 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectViewClickedSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 15:33:13 2012----------*/
void SelectViewClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Sep 15:33:28 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectPrintingTemplateClickedSlot // private, slots*
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 15:33:28 2012----------*/
void SelectPrintingTemplateClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 15:35:45 2012-------*
    * @method  CwmsFormStandardContainerEditor::FillView    // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 15:35:45 2012----------*/
    void FillView(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 15:48:03 2012-------*
    * @method  CwmsFormStandardContainerEditor::FillReport  // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 15:48:03 2012----------*/
    void FillReport(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:22:06 2012-------*
    * @method  CwmsFormStandardContainerEditor::EditForm    // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsFormStandardObjectList p_cForm            //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:22:06 2012----------*/
    static void EditForm(CwmsFormStandardContainer p_cForm, bool p_bNew, QWidget* p_pqwParent);

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 14:46:54 2012-------*
    * @method  CwmsFormStandardContainerEditor::HideSelectionWidgets // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:46:54 2012----------*/
    void HideSelectionWidgets();

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 17:39:39 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectionMemberDownClickedSlot // private, slots *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 17:39:39 2012----------*/
void SelectionMemberDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 17:39:45 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectionMemberUpClickedSlot // private, slots   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 17:39:45 2012----------*/
void SelectionMemberUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 17:39:51 2012-------*
    * @method  CwmsFormStandardContainerEditor::RemoveSelectionMemberClickedSlot // private, slots*
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 17:39:51 2012----------*/
void RemoveSelectionMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 17:39:59 2012-------*
    * @method  CwmsFormStandardContainerEditor::AddSelectionMemberClickedSlot // private, slots  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 17:39:59 2012----------*/
void AddSelectionMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 17:40:05 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectSelectionObjectListClickedSlot // private, slots*
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 17:40:05 2012----------*/
void SelectSelectionObjectListClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 11. Sep 17:40:13 2012-------*
    * @method  CwmsFormStandardContainerEditor::SelectSelectionViewClickedSlot // private, slots *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 17:40:13 2012----------*/
void SelectSelectionViewClickedSlot( );




};

#endif // CwmsFormStandardContainerEditor_H
