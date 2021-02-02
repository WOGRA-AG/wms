/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsGenerateCodeEditor.h
 ** Started Implementation: 2011/11/09
 ** Description:
 ** 
 ** Implements the Configuration ui for generating code
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSGENERATECODEEDITOR_H
#define CWMSGENERATECODEEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "ui_CwmsGenerateCodeEditor.h"

// Forwards
class CdmClass;

// TypeDefs


/* 
 * This class implements the the Configuration ui for generating code
 */
class CwmsGenerateCodeEditor : public QDialog, public Ui::CwmsGeneratorCodeEditorClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Mi 9. Nov 19:55:57 2011--------*
    * @method  CwmsGenerateCodeEditor::CwmsGenerateCodeEditor // public                           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 19:55:57 2011-----------*/
    CwmsGenerateCodeEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 9. Nov 19:56:05 2011--------*
    * @method  CwmsGenerateCodeEditor::~CwmsGenerateCodeEditor // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsGenerateCodeEditor                                     *
    *----------------last changed: -----------------------------Mi 9. Nov 19:56:05 2011-----------*/
    virtual ~CwmsGenerateCodeEditor( );

    private slots:
   /** +-=---------------------------------------------------------Mi 9. Nov 19:56:54 2011--------*
    * @method  CwmsGenerateCodeEditor::SearchClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 19:56:54 2011-----------*/
void SearchClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 9. Nov 19:57:55 2011--------*
    * @method  CwmsGenerateCodeEditor::ShowCodeGenerator     // public, static                    *
    * @return  void                                          //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 19:57:55 2011-----------*/
    static void ShowCodeGenerator(QWidget* p_pqwParent, CdmClass* p_pCdmClass);

    private slots:
   /** +-=---------------------------------------------------------Fr 8. Jun 10:25:52 2012--------*
    * @method  CwmsGenerateCodeEditor::OKClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 10:25:52 2012-----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 8. Jun 10:26:13 2012--------*
    * @method  CwmsGenerateCodeEditor::Validate              // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 10:26:13 2012-----------*/
    bool Validate();
};

#endif // CWMSGENERATECODEEDITOR_H
