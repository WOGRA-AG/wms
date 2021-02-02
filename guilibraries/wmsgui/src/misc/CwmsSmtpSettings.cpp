/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsSmtpSettings.cpp
 ** Started Implementation: 2010/01/11
 ** Description:
 ** 
 ** Implements the configurator for smtp
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CwmsSmtpSettings.h"


/** +-=---------------------------------------------------------Mo 11. Jan 21:37:10 2010----------*
 * @method  CwmsSmtpSettings::CwmsSmtpSettings                 // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Jan 21:37:10 2010----------*/
CwmsSmtpSettings::CwmsSmtpSettings(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
    setupUi(this);
}

/** +-=---------------------------------------------------------Mo 11. Jan 21:37:28 2010----------*
 * @method  CwmsSmtpSettings::~CwmsSmtpSettings                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsSmtpSettings                                               *
 *----------------last changed: --------------------------------Mo 11. Jan 21:37:28 2010----------*/
CwmsSmtpSettings::~CwmsSmtpSettings()
{
}

/** +-=---------------------------------------------------------Mi 21. Nov 10:41:39 2012----------*
 * @method  CwmsSmtpSettings::FillDialog                     // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsSmtpConfiguration p_cCbmsConfigurator        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 10:41:39 2012----------*/
void CwmsSmtpSettings::FillDialog(CwmsSmtpConfiguration p_cCbmsConfigurator)
{
   if (p_cCbmsConfigurator.IsValid())
   {
      m_cCwmsSmtpConfiguration = p_cCbmsConfigurator;
      m_pqlePassword->setText(m_cCwmsSmtpConfiguration.GetSmtpPassword());
      m_pqleSmtpServer->setText(m_cCwmsSmtpConfiguration.GetSmtpServer());
      m_pqleUsername->setText(m_cCwmsSmtpConfiguration.GetSmtpUsername());
      m_pqcbAuthentification->setCurrentIndex(m_cCwmsSmtpConfiguration.GetSmtpAuthentication());
      m_pqcbEncryption->setCurrentIndex(m_cCwmsSmtpConfiguration.GetSmtpEncryption());
      m_pqsbPort->setValue(m_cCwmsSmtpConfiguration.GetSmtpPort());
      m_pqleSender->setText(m_cCwmsSmtpConfiguration.GetSmtpSender());
   }
}

/** +-=---------------------------------------------------------Mo 11. Jan 21:38:35 2010----------*
 * @method  CwmsSmtpSettings::SaveSettings                    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Jan 21:38:35 2010----------*/
void CwmsSmtpSettings::SaveSettings()
{
   m_cCwmsSmtpConfiguration.SetSmtpAuthentication((EslSmtpAuthType)m_pqcbAuthentification->currentIndex());
   m_cCwmsSmtpConfiguration.SetSmtpEncryption(m_pqcbEncryption->currentIndex());
   m_cCwmsSmtpConfiguration.SetSmtpPassword(m_pqlePassword->text());
   m_cCwmsSmtpConfiguration.SetSmtpServer(m_pqleSmtpServer->text());
   m_cCwmsSmtpConfiguration.SetSmtpUsername(m_pqleUsername->text());
   m_cCwmsSmtpConfiguration.SetSmtpPort(m_pqsbPort->value());
   m_cCwmsSmtpConfiguration.SetSmtpSender(m_pqleSender->text());
   m_cCwmsSmtpConfiguration.CommitObject();
}

/** +-=---------------------------------------------------------Mi 21. Nov 10:42:40 2012----------*
 * @method  CwmsSmtpSettings::Edit                           // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsSmtpConfiguration p_cCbmsConfigurator        //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 10:42:40 2012----------*/
void CwmsSmtpSettings::Edit(CwmsSmtpConfiguration p_cCbmsConfigurator, QWidget* p_pqwParent)
{
   CwmsSmtpSettings* pCbgSmtpSettings = new CwmsSmtpSettings(p_pqwParent);
   pCbgSmtpSettings->FillDialog(p_cCbmsConfigurator);

   if (pCbgSmtpSettings->exec() == QDialog::Accepted)
   {
      pCbgSmtpSettings->SaveSettings();
   }

   DELPTR(pCbgSmtpSettings);
}
