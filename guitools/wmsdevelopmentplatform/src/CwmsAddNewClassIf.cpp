// System and QT Includes

// WMS Includes
#include "CdmModelElement.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsAddNewClassIf.h"


CwmsAddNewClassIf::CwmsAddNewClassIf(QWidget* parent)
   : QDialog(parent)
{
   setupUi(this);
}

CwmsAddNewClassIf::~CwmsAddNewClassIf()
{
}

void CwmsAddNewClassIf::CancelClickedSlot()
{
   reject();
}


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

void CwmsAddNewClassIf::OKClickedSlot()
{
   if (Validate())
   {
      accept();
   }
}
