/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsWorkflowStepEditorDlg.h
 ** Started Implementation: 2012/10/10
 ** Description:
 ** 
 ** IMplements the workflow step editor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSWORKFLOWSTEPEDITORDLG_H
#define CWMSWORKFLOWSTEPEDITORDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSDATA Includes
#include "CwmsWorkflowStepDefinition.h"

// Own Includes
#include "IwmsObjectEditorDescriptor.h"
#include "ui_CwmsWorkflowStepEditorDlg.h"

// Forwards


// TypeDefs


/* 
 * This class implements the workflow step editor
 */
class CwmsWorkflowStepEditorDlg : public QDialog, public Ui::CwmsWorkflowStepEditorDlgClass
{
   Q_OBJECT

   private:
      CwmsWorkflowStepDefinition m_cStep;
      CdmObject* m_rpCdmObjectSubWorkflow;
      bool m_bNew;

   public:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:32:19 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::CwmsWorkflowStepEditorDlg // public                           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:32:19 2012----------*/
    CwmsWorkflowStepEditorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:34:28 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::~CwmsWorkflowStepEditorDlg // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbgEscalationEditorDlg                                     *
    *----------------last changed: -----------------------------Mi 10. Okt 13:34:28 2012----------*/
    virtual ~CwmsWorkflowStepEditorDlg( );

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:00:18 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::FillDialog         // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsWorkflowStepDefinition p_cStep      //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:00:18 2012----------*/
    void FillDialog(CwmsWorkflowStepDefinition p_cStep, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Do 20. Dez 11:47:27 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::Validate           // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 11:47:27 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 28. Dez 15:28:11 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::SaveData           // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 28. Dez 15:28:11 2012----------*/
    bool SaveData();

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 11:47:48 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::OKClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 11:47:48 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:00:39 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::Edit               // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CwmsWorkflowStepDefinition p_cStep      //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:00:39 2012----------*/
    static bool Edit(CwmsWorkflowStepDefinition p_cStep, bool p_bNew, QWidget* p_pqwParent);


   private:
   /** +-=---------------------------------------------------------Fr 26. Okt 11:45:59 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::FillHiddenValues   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 26. Okt 11:45:59 2012----------*/
    void FillHiddenValues();

   private:
   /** +-=---------------------------------------------------------Fr 26. Okt 11:46:55 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::FillReadOnlyValues // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 26. Okt 11:46:55 2012----------*/
    void FillReadOnlyValues();

   private:
   /** +-=---------------------------------------------------------Fr 26. Okt 11:47:18 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::FillChangingValues // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 26. Okt 11:47:18 2012----------*/
    void FillChangingValues();

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 11:45:02 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::AddValueChangeMemberClickedSlot // private, slots       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 11:45:02 2012----------*/
void AddValueChangeMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 11:45:14 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::RemoveValueChangeMemberClickedSlot // private, slots    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 11:45:14 2012----------*/
void RemoveValueChangeMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 11:45:26 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::AddSubProcessClickedSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 11:45:26 2012----------*/
void AddSubProcessClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 11:45:51 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::RemoveSubProcessClickedSlot // private, slots           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 11:45:51 2012----------*/
void RemoveSubProcessClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 16:07:38 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::AddHiddenMemberClickedSlot // private, slots            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:07:38 2012----------*/
void AddHiddenMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 16:07:48 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::RemoveHiddenMemberClickedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:07:48 2012----------*/
void RemoveHiddenMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 16:08:09 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::RemoveReadOnlyMemberClickedSlot // private, slots       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:08:09 2012----------*/
void RemoveReadOnlyMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 16:07:59 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::AddReadOnlyMemberClickedSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:07:59 2012----------*/
void AddReadOnlyMemberClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 20. Dez 15:17:39 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::GetClass           // private                           *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 15:17:39 2012----------*/
    CdmClass* GetClass();

   private:
   /** +-=---------------------------------------------------------Do 20. Dez 16:35:33 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::SaveChangeValues   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:35:33 2012----------*/
    void SaveChangeValues();

   private:
   /** +-=---------------------------------------------------------Do 20. Dez 16:39:59 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::SaveHiddenMembers  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:39:59 2012----------*/
    void SaveHiddenMembers();

   private:
   /** +-=---------------------------------------------------------Do 20. Dez 16:40:09 2012-------*
    * @method  CwmsWorkflowStepEditorDlg::SaveReadOnlyMembers // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 16:40:09 2012----------*/
    void SaveReadOnlyMembers();

};

class WMSGUI_API CwmsWorkflowStepObjectEditorDescriptor : public IwmsObjectEditorDescriptor
{

   public:
   /** +-=---------------------------------------------------------So 30. Dez 14:01:08 2012-------*
    * @method  CwmsWorkflowStepObjectEditorDescriptor::GetClassKeyname // public                  *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 14:01:08 2012----------*/
    QString GetClassKeyname();

   protected:
   /** +-=---------------------------------------------------------So 30. Dez 14:01:16 2012-------*
    * @method  CwmsWorkflowStepObjectEditorDescriptor::DisplayEditor // protected                 *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 14:01:16 2012----------*/
    bool DisplayEditor(CdmObject* p_pCdmObject,
                       EwmsGuiDisplayMode p_eDisplayMode,
                       QWidget* p_pqwParent);
};

#endif // CBGWORKFLOWSTEPEDITORDLG_H
