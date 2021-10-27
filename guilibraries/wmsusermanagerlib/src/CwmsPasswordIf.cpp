/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsPasswordIf.cpp
 ** Started Implementation: 2011/09/06
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

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



/** +-=---------------------------------------------------------Mi 7. Sep 15:20:48 2011-----------*
 * @method  CwmsPasswordIf::CwmsPasswordIf                   // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrOriginalPasswort                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 7. Sep 15:20:48 2011-----------*/
CwmsPasswordIf::CwmsPasswordIf(CumUser* p_pUser,
                               QWidget* parent)
   : QDialog(parent),
  m_rpUser(p_pUser)
{

   setupUi(this);
}


/** +-=---------------------------------------------------------Di 25. Jan 22:20:38 2005----------*
 * @method  CwmsPasswordIf::~CwmsPasswordIf                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsPasswordIf                                                *
 *                                                                                                *
 *----------------last changed: --------------------------------Di 25. Jan 22:20:38 2005----------*/
CwmsPasswordIf::~CwmsPasswordIf(  )
{
}

/** +-=---------------------------------------------------------Di 25. Jan 22:24:12 2005----------*
 * @method  CwmsPasswordIf::CancelClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the cancle button was clicked. it rejects the dialog.     *
 *----------------last changed: --------------------------------Di 25. Jan 22:24:12 2005----------*/
void CwmsPasswordIf::CancelClickedSlot(  )
{
   reject();
}

/** +-=---------------------------------------------------------Di 25. Jan 22:24:38 2005----------*
 * @method  CwmsPasswordIf::OKClickedSlot                    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the ok button was clicked it accepts the changes.         *
 *----------------last changed: --------------------------------Di 25. Jan 22:24:38 2005----------*/
void CwmsPasswordIf::OKClickedSlot(  )
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

/** +-=---------------------------------------------------------Di 25. Jan 22:31:28 2005----------*
 * @method  CwmsPasswordIf::ChangePassword                   // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CumUser* p_pCumUser                              //                                   *
 * @param   QWidget* parent                                  //                                   *
 * @comment This is static memeber function which is able to change the user password.            *
 *----------------last changed: --------------------------------Di 25. Jan 22:31:28 2005----------*/
bool CwmsPasswordIf::ChangePassword(CumUser* p_pCumUser, QWidget* parent )
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
             MSG_INFO(("Passwort wurde geändert"), ("Das Passwort wurde erfolgreich geändert."));
         }

      }

      delete pCwmsPasswordIf;
   }

   return bRet;
}
