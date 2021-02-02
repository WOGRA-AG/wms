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
 ** CVS Changes: $Id: CoeTextEditIf.cpp,v 1.2 2006/11/19 16:18:15 wogra Exp $
 *****************************************************************************/ 


// System and QT Includes


// own Includes
#include "CoeTextEditIf.h"



/** +-=---------------------------------------------------------Di 28. Sep 08:15:33 2010----------*
 * @method  CoeTextEditIf::CoeTextEditIf                     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment The Textedit dlg constructor                                                          *
 *----------------last changed: --------------------------------Di 28. Sep 08:15:33 2010----------*/
CoeTextEditIf::CoeTextEditIf(QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
   m_pCoeTextEdit->show();
}

/** +-=---------------------------------------------------------Di 13. Dez 21:29:43 2005----------*
 * @method  CoeTextEditIf::~CoeTextEditIf                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoeTextEditIf                                                 *
 *                                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Di 13. Dez 21:29:43 2005----------*/
CoeTextEditIf::~CoeTextEditIf(  )
{
}

/** +-=---------------------------------------------------------Di 13. Dez 21:30:03 2005----------*
 * @method  CoeTextEditIf::SetText                           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment Thsi method sets the text to the textedit.                                            *
 *----------------last changed: Wolfgang Graßhof----------------Di 13. Dez 21:30:03 2005----------*/
void CoeTextEditIf::SetText(  QString p_qstrText )
{
   m_pCoeTextEdit->SetText(p_qstrText);
}

/** +-=---------------------------------------------------------Di 13. Dez 21:30:26 2005----------*
 * @method  CoeTextEditIf::GetText                           // public                            *
 * @return  QString                                          //                                   *
 * @comment This method returns the Text of the textedit.                                         *
 *----------------last changed: Wolfgang Graßhof----------------Di 13. Dez 21:30:26 2005----------*/
QString CoeTextEditIf::GetText(  )
{
   return m_pCoeTextEdit->GetText();
}

/** +-=---------------------------------------------------------Sa 2. Aug 13:16:27 2008-----------*
 * @method  CoeTextEditIf::GetTextEdit                       // public                            *
 * @return  QTextEdit*                                       //                                   *
 * @comment returns the Textedit object.                                                          *
 *----------------last changed: --------------------------------Sa 2. Aug 13:16:27 2008-----------*/
QTextEdit* CoeTextEditIf::GetTextEdit()
{
   return m_pCoeTextEdit->GetTextEdit();
}

/** +-=---------------------------------------------------------Di 13. Dez 21:44:31 2005----------*
 * @method  CoeTextEditIf::EditText                          // public, static                    *
 * @return  bool                                             // Modified Text or not.             *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @param   QString& p_qstrText                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Di 13. Dez 21:44:31 2005----------*/
bool CoeTextEditIf::EditText(  QWidget* p_pqwParent, QString& p_qstrText )
{
   bool bModified = false;
   CoeTextEditIf* pCoeTextEditIf = new CoeTextEditIf(p_pqwParent);

   pCoeTextEditIf->SetText(p_qstrText);


   if(pCoeTextEditIf->exec() == QDialog::Accepted)
   {
      QString qstrText = pCoeTextEditIf->GetText();

      if(qstrText != p_qstrText)
      {
         bModified = true;
         p_qstrText = qstrText;
      }
   }

   return bModified;
}
