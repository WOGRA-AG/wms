/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: CwmsAddNewClassIf.cpp
 ** Started Implementation: 2008/05/23
 ** Description:
 ** 
 ** implements the class creation dlg
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

// System and QT Includes

// WMS Includes
#include "CdmModelElement.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsAddNewClassIf.h"


/** +-=---------------------------------------------------------Mo 27. Aug 18:34:23 2012----------*
 * @method  CwmsAddNewClassIf::CwmsAddNewClassIf             // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 18:34:23 2012----------*/
CwmsAddNewClassIf::CwmsAddNewClassIf(QWidget* parent)
   : QDialog(parent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 23. Mai 20:29:44 2008----------*
 * @method  CwmsAddNewClassIf::~CwmsAddNewClassIf            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsAddNewClassIf                                             *
 *----------------last changed: --------------------------------Fr 23. Mai 20:29:44 2008----------*/
CwmsAddNewClassIf::~CwmsAddNewClassIf()
{
}

/** +-=---------------------------------------------------------Fr 23. Mai 20:30:46 2008----------*
 * @method  CwmsAddNewClassIf::CancelClickedSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 23. Mai 20:30:46 2008----------*/
void CwmsAddNewClassIf::CancelClickedSlot()
{
   reject();
}

/** +-=---------------------------------------------------------Do 27. Dez 12:32:55 2012----------*
 * @method  CwmsAddNewClassIf::Validate                      // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 27. Dez 12:32:55 2012----------*/
bool CwmsAddNewClassIf::Validate()
{
   bool bRet = true;

   if (m_pqleCaption->text().isEmpty())
   {
      bRet = false;
      MSG_CRIT("Pflichtfeld nicht gefüllt", "Das Feld Name ist nicht gefüllt.");
   }

   if (m_pqleKeyname->text().isEmpty())
   {
      bRet = false;
      MSG_CRIT("Pflichtfeld nicht gefüllt", "Das Feld Schlüssel ist nicht gefüllt.");
   }
   else
   {
       if (!CdmModelElement::CheckKeyname(m_pqleKeyname->text()))
       {
           bRet = false;
           MSG_CRIT("Schlüsselbezeichnung entspricht nicht den Regeln",
                    "Schlüsselbezeichnung nicht erlaubt (muss mit einem Buchstaben beginnen und darf keine Umlaute oder Sonderzeichen außer \"_\" enthalten.");
       }

   }

   if (m_pqteComment->toPlainText().isEmpty())
   {
      bRet = false;
      MSG_CRIT("Pflichtfeld nicht gefüllt", "Das Feld Beschreibung ist nicht gefüllt.");
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 23. Mai 20:30:33 2008----------*
 * @method  CwmsAddNewClassIf::OKClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 23. Mai 20:30:33 2008----------*/
void CwmsAddNewClassIf::OKClickedSlot()
{
   if (Validate())
   {
      accept();
   }
}
