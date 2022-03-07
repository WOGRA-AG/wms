/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsWorkflowMemberValueEditor.h
 ** Started Implementation: 2012/12/19
 ** Description:
 ** 
 ** implements the editor for changing values thru steps.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSWORKFLOWMEMBERVALUEEDITOR_H
#define CWMSWORKFLOWMEMBERVALUEEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "ui_CwmsWorkflowMemberValueEditor.h"


// Forwards
class CdmClass;

// TypeDefs


/* 
 * This class implements the editor for changing values thru steps.
 */
class CwmsWorkflowMemberValueEditor : public QDialog, public Ui::CwmsWorkflowMemberValueEditorClass
{

   public:
   /** +-=---------------------------------------------------------Mi 19. Dez 16:44:46 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::CwmsWorkflowMemberValueEditor // public             *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Dez 16:44:46 2012----------*/
    CwmsWorkflowMemberValueEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 19. Dez 16:44:52 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::~CwmsWorkflowMemberValueEditor // public, virtual   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsWorkflowMemberValueEditor                              *
    *----------------last changed: -----------------------------Mi 19. Dez 16:44:52 2012----------*/
    virtual ~CwmsWorkflowMemberValueEditor( );

   public:
   /** +-=---------------------------------------------------------Do 20. Dez 15:37:24 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::FillDialog     // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 15:37:24 2012----------*/
    void FillDialog(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Do 20. Dez 10:07:10 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::Validate       // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 10:07:10 2012----------*/
    bool Validate();


   public:
   /** +-=---------------------------------------------------------Do 20. Dez 10:07:36 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::GetMemberKeyname // public                          *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 10:07:36 2012----------*/
    QString GetMemberKeyname();

   public:
   /** +-=---------------------------------------------------------Do 20. Dez 10:07:53 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::GetValue       // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 10:07:53 2012----------*/
    QString GetValue();

    private slots:
   /** +-=---------------------------------------------------------Do 20. Dez 10:08:51 2012-------*
    * @method  CwmsWorkflowMemberValueEditor::OKClickedSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Dez 10:08:51 2012----------*/
void OKClickedSlot( );
};

#endif // CWMSWORKFLOWMEMBERVALUEEDITOR_H
