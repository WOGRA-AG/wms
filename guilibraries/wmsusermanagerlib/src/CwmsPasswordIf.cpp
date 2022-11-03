// System and QT Inlcudes
#include <QLineEdit>
#include <QCryptographicHash>

// WMS COmmons Includes
#include "CwmsUtilities.h"

// own Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CumUser.h"
#include "CwmsPasswordIf.h"


CwmsPasswordIf::CwmsPasswordIf(CumUser* p_pUser,
                               QWidget* parent)
: QDialog(parent),
  m_rpUser(p_pUser)
{

   setupUi(this);
}

CwmsPasswordIf::~CwmsPasswordIf()
{
}

void CwmsPasswordIf::CancelClickedSlot()
{
   reject();
}

void CwmsPasswordIf::OKClickedSlot()
{
   QString qstrOldPassword = m_pqleOldPassword->text();

   if (m_rpUser->IsEncrypted())
   {
       qstrOldPassword = CwmsUtilities::EncryptPassword(qstrOldPassword);
   }

   if(qstrOldPassword == m_rpUser->GetPassword())
   {
      if(m_pqlenNwPassword->text() == m_pqleRepeatNewPassword->text())
      {
         accept();
      }
      else
      {
         MSG_CRIT("Ungültige Eingabe", "Das neue Passwort und die Wiederholung des Passworts stimmen nicht überein!");
      }
   }
   else
   {
      MSG_CRIT("Ungültige Eingabe", "Die Passwortverifikation schlug fehl das Originalpasswort ist falsch!");
   }

}

bool CwmsPasswordIf::ChangePassword(CumUser* p_pCumUser, QWidget* parent)
{
   bool bRet = false;

   if(CHKPTR(p_pCumUser))
   {
      CwmsPasswordIf* pCwmsPasswordIf = new CwmsPasswordIf(p_pCumUser, parent);
      
      if(pCwmsPasswordIf->exec() == QDialog::Accepted)
      {
         p_pCumUser->SetPassword(pCwmsPasswordIf->m_pqleRepeatNewPassword->text());
         p_pCumUser->SetEncrypted(false);
         bRet = p_pCumUser->Update();

         if (bRet)
         {
             MSG_INFO("Passwort wurde geändert", "Das Passwort wurde erfolgreich geändert.");
         }
      }

      delete pCwmsPasswordIf;
   }

   return bRet;
}
