/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CbgWorkflowStepEditorDlg.h
 ** Started Implementation: 2012/10/10
 ** Description:
 ** 
 ** IMplements the workflow step execution editor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSWORKFLOWSTEPEXECUTIONEDITORDLG_H
#define CWMSWORKFLOWSTEPEXECUTIONEDITORDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSDATA Includes
#include "CwmsWorkflowStepExecution.h"

// Own Includes
#include "IwmsObjectEditorDescriptor.h"
#include "ui_CwmsWorkflowStepExecutionEditorDlg.h"

// Forwards


// TypeDefs


/* 
 * This class implements thethe workflow step editor
 */
class CwmsWorkflowStepExecutionEditorDlg : public QDialog, public Ui::CwmsWorkflowStepExecutionEditorDlgClass
{
   Q_OBJECT

   private:
      CwmsWorkflowStepExecution m_cStep;
      bool m_bNew;

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 17:23:01 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::CwmsWorkflowStepExecutionEditorDlg // public     *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 17:23:01 2012----------*/
    CwmsWorkflowStepExecutionEditorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 17:23:10 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::~CwmsWorkflowStepExecutionEditorDlg // public, virtual*
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbgEscalationEditorDlg                                     *
    *----------------last changed: -----------------------------Mi 17. Okt 17:23:10 2012----------*/
    virtual ~CwmsWorkflowStepExecutionEditorDlg( );

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:14:34 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::FillDialog // public                           *
    * @return  void                                          //                                   *
    * @param   CwmsWorkflowStepExecution p_cStep       //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:14:34 2012----------*/
    void FillDialog(CwmsWorkflowStepExecution p_cStep, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Mi 17. Okt 17:23:33 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::Validate   // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 17:23:33 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Mi 17. Okt 17:23:44 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::SaveData   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 17:23:44 2012----------*/
    void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mi 17. Okt 17:23:54 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::OKClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 17:23:54 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:15:05 2012-------*
    * @method  CwmsWorkflowStepExecutionEditorDlg::Edit      // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CwmsWorkflowStepExecution p_cStep       //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:15:05 2012----------*/
    static bool Edit(CwmsWorkflowStepExecution p_cStep, bool p_bNew, QWidget* p_pqwParent);


};


class WMSGUI_API CwmsWorkflowStepExecutionObjectEditorDescriptor : public IwmsObjectEditorDescriptor
{

   public:
   /** +-=---------------------------------------------------------So 30. Dez 14:21:47 2012-------*
    * @method  CwmsWorkflowStepExecutionObjectEditorDescriptor::DisplayEditor // public           *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 14:21:47 2012----------*/
    bool DisplayEditor(CdmObject* p_pCdmObject,
                       EwmsGuiDisplayMode p_eDisplayMode,
                       QWidget* p_pqwParent);
   public:
   /** +-=---------------------------------------------------------So 30. Dez 14:21:53 2012-------*
    * @method  CwmsWorkflowStepExecutionObjectEditorDescriptor::GetClassKeyname // public         *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 14:21:53 2012----------*/
    QString GetClassKeyname();
};
#endif // CBGWORKFLOWSTEPEDITORDLG_H
