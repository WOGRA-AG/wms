// Header is missing impl started on 25.1.2005



// System and QT Includes
#include <qlineedit.h>
#include <qcheckbox.h>



// own Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUserManager.h"
#include "CumUser.h"


#include "CwmsNewUserIf.h"




/** +-=---------------------------------------------------------Di 25. Jan 21:57:16 2005----------*
 * @method  CwmsNewUserIf::CwmsNewUserIf                     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 25. Jan 21:57:16 2005----------*/
CwmsNewUserIf::CwmsNewUserIf(CumUserManager* p_pUserManager, QWidget* parent)
    : QDialog(parent),
    m_rpUserManager(p_pUserManager)
{
    setupUi(this);
}


/** +-=---------------------------------------------------------Di 25. Jan 21:57:26 2005----------*
 * @method  CwmsNewUserIf::~CwmsNewUserIf                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsNewUserIf                                                 *
 *                                                                                                *
 *----------------last changed: --------------------------------Di 25. Jan 21:57:26 2005----------*/
CwmsNewUserIf::~CwmsNewUserIf(  )
{
}

/** +-=---------------------------------------------------------Di 25. Jan 21:58:24 2005----------*
 * @method  CwmsNewUserIf::OKClickedSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the ok button was clicked. it creates the new user.       *
 *----------------last changed: --------------------------------Di 25. Jan 21:58:24 2005----------*/
void CwmsNewUserIf::OKClickedSlot(  )
{
    if (Validate() && Save())
    {
        accept();
    }
}

bool CwmsNewUserIf::Save()
{
    CumUser* pUser = new CumUser(m_rpUserManager);
    pUser->SetLogin(m_pqleLogin->text());
    pUser->SetPassword(m_pqlePassword->text());
    pUser->SetLastName(m_pqleName->text());
    pUser->SetFirstName(m_pqleSurName->text());
    pUser->SetEmail(m_pqleEmail->text());
    pUser->SetAdministrator(m_pqchbAdministrator->isChecked());
    pUser->SetSchemeIndependent(m_pqchbSchemeIndependent->isChecked());
   qint64 lAccessorId = m_rpUserManager->CreateUser(pUser);
    return (lAccessorId > 0);
}

bool CwmsNewUserIf::Validate()
{

    if (m_pqleLogin->text().isEmpty())
    {
        ERR("Login must be filled");
        return false;
    }

    if (m_pqlePassword->text().isEmpty())
    {
        ERR("Password must be filled");
        return false;
    }

    if (m_pqleEmail->text().isEmpty())
    {
        ERR("E-Mail must be filled");
        return false;
    }

    return true;
}

void CwmsNewUserIf::HideSchemeIndependentCheckbox()
{
    m_pqchbSchemeIndependent->setVisible(false);
}

/** +-=---------------------------------------------------------Di 25. Jan 21:58:55 2005----------*
 * @method  CwmsNewUserIf::CancelClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the cancle button was clicked it cancels the user creation.*
 *----------------last changed: --------------------------------Di 25. Jan 21:58:55 2005----------*/
void CwmsNewUserIf::CancelClickedSlot(  )
{
    reject();
}

/** +-=---------------------------------------------------------Di 25. Jan 22:02:40 2005----------*
 * @method  CwmsNewUserIf::CreateNewUser                     // public, static                    *
 * @return  bool                                             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment This static method creates a new user and returns the success flag                    *
 *----------------last changed: --------------------------------Di 25. Jan 22:02:40 2005----------*/
QString CwmsNewUserIf::CreateNewUser(QWidget* p_pqwParent, CumUserManager* p_pUserManager)
{
    QString qstrLogin;
    if(CHKPTR(p_pUserManager))
    {
        CwmsNewUserIf* pCwmsNewUserIf = new CwmsNewUserIf(p_pUserManager, p_pqwParent);

        if (p_pUserManager->GetSchemeUri().isEmpty())
        {
            pCwmsNewUserIf->HideSchemeIndependentCheckbox();
        }

        if(pCwmsNewUserIf->exec() == QDialog::Accepted)
        {
            qstrLogin  = pCwmsNewUserIf->m_pqleLogin->text();
        }

        delete pCwmsNewUserIf;
    }

    return qstrLogin;
}
