/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsClassValidationEditor.h
 ** Started Implementation: 2012/11/26
 ** Description:
 ** 
 ** implements the editor for class validations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCLASSVALIDATIONEDITOR_H
#define CWMSCLASSVALIDATIONEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "ui_CwmsClassValidationEditor.h"

// Forwards
class CdmClassValidator;
class CdmClass;

// TypeDefs


/* 
 * This class implements the editor for class validations
 */
class CwmsClassValidationEditor : public QDialog, public Ui::CwmsClassValidationEditorClass
{
   Q_OBJECT

   private:
      CdmClassValidator* m_rpValidator;



   public:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:40:21 2012-------*
    * @method  CwmsClassValidationEditor::CwmsClassValidationEditor // public                     *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 11:40:21 2012----------*/
    CwmsClassValidationEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:40:45 2012-------*
    * @method  CwmsClassValidationEditor::~CwmsClassValidationEditor // public, virtual           *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsClassValidationEditor                                  *
    *----------------last changed: -----------------------------Mo 26. Nov 11:40:45 2012----------*/
    virtual ~CwmsClassValidationEditor( );

   private:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:41:05 2012-------*
    * @method  CwmsClassValidationEditor::FillDialog         // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassValidator* p_pValidator               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 11:41:05 2012----------*/
    void FillDialog(CdmClassValidator* p_pValidator);

    private slots:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:43:46 2012-------*
    * @method  CwmsClassValidationEditor::SyntaxCheckClickedSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 11:43:46 2012----------*/
void SyntaxCheckClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:43:54 2012-------*
    * @method  CwmsClassValidationEditor::OKClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 11:43:54 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 26. Nov 12:34:54 2012-------*
    * @method  CwmsClassValidationEditor::EditValidation     // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   CdmClassValidator* p_pValidator               //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 12:34:54 2012----------*/
    static bool EditValidation(CdmClass* p_pCdmClass,
                               CdmClassValidator* p_pValidator,
                               bool p_bNew,
                               QWidget* p_pqwParent);

   private:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:44:56 2012-------*
    * @method  CwmsClassValidationEditor::Validate           // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 11:44:56 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Mo 26. Nov 11:45:05 2012-------*
    * @method  CwmsClassValidationEditor::SaveData           // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 11:45:05 2012----------*/
    bool SaveData();
};

#endif // CWMSCLASSVALIDATIONEDITOR_H
