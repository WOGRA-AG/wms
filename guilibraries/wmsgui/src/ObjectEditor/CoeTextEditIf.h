/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CoeTextEditIf.hpp
 ** Started Implementation: 13.12.2005
 ** Description:
 ** Implements the Text Edit Dialog
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoeTextEditIf.hpp,v 1.1 2005/12/16 22:04:18 remote Exp $
 *****************************************************************************/ 

#ifndef CSLTEXTEDITDLG_HPP
#define CSLTEXTEDITDLG_HPP

// System and QT Includes
#include <QDialog>

// own Includes
#include "wmsgui.h"
#include "ui_CoeTextEditDlg.h"



// forwards




class WMSGUI_API CoeTextEditIf : public QDialog, public Ui::CoeTextEditDlg
{



   public:
   /** +-=---------------------------------------------------------Di 28. Sep 08:15:33 2010-------*
    * @method  CoeTextEditIf::CoeTextEditIf                  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment The Textedit dlg constructor                                                       *
    *----------------last changed: -----------------------------Di 28. Sep 08:15:33 2010----------*/
    CoeTextEditIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 13. Dez 21:29:43 2005*
    * @method  CoeTextEditIf::~CoeTextEditIf                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoeTextEditIf                                              *
    *                                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Di 13. Dez 21:29:43 2005----------*/
virtual ~CoeTextEditIf(  );

   public:
   /** +-=---------------------------------------------------------Di 13. Dez 21:30:03 2005*
    * @method  CoeTextEditIf::SetText                        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment Thsi method sets the text to the textedit.                                         *
    *----------------last changed: Wolfgang Graßhof-------------Di 13. Dez 21:30:03 2005----------*/
void SetText(  QString p_qstrText );

   public:
   /** +-=---------------------------------------------------------Di 13. Dez 21:30:26 2005*
    * @method  CoeTextEditIf::GetText                        // public                            *
    * @return  QString                                       //                                   *
    * @comment This method returns the Text of the textedit.                                      *
    *----------------last changed: Wolfgang Graßhof-------------Di 13. Dez 21:30:26 2005----------*/
QString GetText(  );

   public:
   /** +-=---------------------------------------------------------Di 13. Dez 21:44:31 2005*
    * @method  CoeTextEditIf::EditText                       // public, static                    *
    * @return  bool                                          // Modified Text or not.             *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @param   QString& p_qstrText                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Di 13. Dez 21:44:31 2005----------*/
static bool EditText(  QWidget* p_pqwParent, QString& p_qstrText );

   public:
   /** +-=---------------------------------------------------------Sa 2. Aug 13:16:27 2008--------*
    * @method  CoeTextEditIf::GetTextEdit                    // public                            *
    * @return  QTextEdit*                                    //                                   *
    * @comment returns the Textedit object.                                                       *
    *----------------last changed: -----------------------------Sa 2. Aug 13:16:27 2008-----------*/
    QTextEdit* GetTextEdit();
};

#endif //
