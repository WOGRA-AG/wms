/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsWorkflowDefinitionEditor.h
 ** Started Implementation: 2012/10/10
 ** Description:
 ** 
 ** implements the workflow editor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSWORKFLOWEDITOR_H
#define CWMSWORKFLOWEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSDATA Includes
#include "CwmsWorkflowDefinition.h"

// Own Includes
#include "wmsgui.h"
#include "IwmsObjectEditorDescriptor.h"
#include "ui_CwmsWorkflowDefinitionEditor.h"

// Forwards


// TypeDefs


/* 
 * This class implements the escalation editor
 */
class WMSGUI_API CwmsWorkflowDefinitionEditor : public QDialog, public Ui::CwmsWorkflowDefinitionEditorClass
{
   Q_OBJECT

   private:
      CwmsWorkflowDefinition m_cWorkflow;
      CdmClass* m_rpCdmClass;
      bool m_bNew;

   public:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:32:19 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::CwmsWorkflowDefinitionEditor // public                           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:32:19 2012----------*/
    CwmsWorkflowDefinitionEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:34:28 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::~CwmsWorkflowDefinitionEditor // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbgEscalationEditorDlg                                     *
    *----------------last changed: -----------------------------Mi 10. Okt 13:34:28 2012----------*/
    virtual ~CwmsWorkflowDefinitionEditor( );


   private:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:35:26 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::Validate              // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:35:26 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Di 18. Dez 13:24:32 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::SaveData        // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Dez 13:24:32 2012----------*/
    bool SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:36:15 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::OKClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:36:15 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 24. Okt 14:55:10 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::Edit            // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CwmsWorkflowDefinition p_cWorkflow             //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 14:55:10 2012----------*/
    static bool Edit(CwmsWorkflowDefinition p_cWorkflow, bool p_bNew, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 24. Okt 14:55:28 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::FillDialog      // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsWorkflowDefinition p_cWorkflow             //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 14:55:28 2012----------*/
    void FillDialog(CwmsWorkflowDefinition p_cWorkflow, bool p_bNew);

    private slots:
   /** +-=---------------------------------------------------------Di 18. Dez 13:39:31 2012-------*
    * @method  CwmsWorkflowDefinitionEditor::SelectClassClickedSlot // private, slots             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Dez 13:39:31 2012----------*/
void SelectClassClickedSlot( );
};

class WMSGUI_API CwmsWorkflowDefintionObjectEditorDescriptor : public IwmsObjectEditorDescriptor
{
   public:
   /** +-=---------------------------------------------------------So 30. Dez 13:50:17 2012-------*
    * @method  CwmsWorkflowDefintionObjectEditorDescriptor::GetClassKeyname // public             *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 13:50:17 2012----------*/
    QString GetClassKeyname();

   protected:
   /** +-=---------------------------------------------------------So 30. Dez 13:51:41 2012-------*
    * @method  CwmsWorkflowDefintionObjectEditorDescriptor::DisplayEditor // protected            *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 13:51:41 2012----------*/
    bool DisplayEditor(CdmObject* p_pCdmObject,
                       EwmsGuiDisplayMode p_eDisplayMode,
                       QWidget* p_pqwParent);
};

#endif // CwmsWorkflowEditor_H
