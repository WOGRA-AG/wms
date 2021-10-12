/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsSmtpConfiguration.cpp
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** Implements the Smtp Configuration class
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "CumUser.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CwmsSmtpConfiguration.h"


/** +-=---------------------------------------------------------Sa 9. Jan 10:14:33 2010-----------*
 * @method  CwmsSmtpConfiguration::CwmsSmtpConfiguration     // public                            *
 * @return                                                   //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:14:33 2010-----------*/
CwmsSmtpConfiguration::CwmsSmtpConfiguration(CdmObject* p_pCdmObject)
: CdmObjectAdaptor(p_pCdmObject)
{

}

/** +-=---------------------------------------------------------Sa 9. Jan 10:14:40 2010-----------*
 * @method  CwmsSmtpConfiguration::CwmsSmtpConfiguration     // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:14:40 2010-----------*/
CwmsSmtpConfiguration::CwmsSmtpConfiguration()
: CdmObjectAdaptor()
{

}

/** +-=---------------------------------------------------------Sa 9. Jan 10:14:47 2010-----------*
 * @method  CwmsSmtpConfiguration::~CwmsSmtpConfiguration    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsSmtpConfiguration                                         *
 *----------------last changed: --------------------------------Sa 9. Jan 10:14:47 2010-----------*/
CwmsSmtpConfiguration::~CwmsSmtpConfiguration()
{
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:46:52 2010-----------*
 * @method  CwmsSmtpConfiguration::GetUserName               // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:46:52 2010-----------*/
QString CwmsSmtpConfiguration::GetUserName()
{
   QString qstrName;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      const CumUser* pCumUser = pCdmManager->GetUser();

      if (CHKPTR(pCumUser))
      {
         qstrName = pCumUser->GetFirstName() + " " + pCumUser->GetLastName();
      }
   }

   return qstrName;
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:46:59 2010-----------*
 * @method  CwmsSmtpConfiguration::GetEmailAddress           // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:46:59 2010-----------*/
QString CwmsSmtpConfiguration::GetEmailAddress()
{
   QString qstrMail;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      const CumUser* pCumUser = pCdmManager->GetUser();

      if (CHKPTR(pCumUser))
      {
         qstrMail = pCumUser->GetEmail();
      }
   }

   return qstrMail;
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:47:06 2010-----------*
 * @method  CwmsSmtpConfiguration::GetSmtpServer             // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:47:06 2010-----------*/
QString CwmsSmtpConfiguration::GetSmtpServer()
{
   return GetString("Smtp_Server");
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:17:10 2010-----------*
 * @method  CwmsSmtpConfiguration::SetSmtpServer             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrServer                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:17:10 2010-----------*/
void CwmsSmtpConfiguration::SetSmtpServer(QString p_qstrServer)
{
   SetValue("Smtp_Server", p_qstrServer);
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:47:11 2010-----------*
 * @method  CwmsSmtpConfiguration::GetSmtpPort               // public, virtual                   *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:47:11 2010-----------*/
int CwmsSmtpConfiguration::GetSmtpPort()
{
   return GetInt("Smtp_Port");
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:17:46 2010-----------*
 * @method  CwmsSmtpConfiguration::SetSmtpPort               // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iPort                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:17:46 2010-----------*/
void CwmsSmtpConfiguration::SetSmtpPort(int p_iPort)
{
   SetValue("Smtp_Port", p_iPort);
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:47:18 2010-----------*
 * @method  CwmsSmtpConfiguration::GetSmtpUsername           // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:47:18 2010-----------*/
QString CwmsSmtpConfiguration::GetSmtpUsername()
{
   return GetString("Smtp_Username");
}

QString CwmsSmtpConfiguration::GetSmtpSender()
{
   return GetString("Smtp_Sender");
}

void CwmsSmtpConfiguration::SetSmtpSender(QString p_qstrSmtpSender)
{
   SetValue("Smtp_Sender", p_qstrSmtpSender);
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:18:30 2010-----------*
 * @method  CwmsSmtpConfiguration::SetSmtpUsername           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSmtpUsername                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:18:30 2010-----------*/
void CwmsSmtpConfiguration::SetSmtpUsername(QString p_qstrSmtpUsername)
{
   SetValue("Smtp_Username", p_qstrSmtpUsername);
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:47:24 2010-----------*
 * @method  CwmsSmtpConfiguration::GetSmtpPassword           // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:47:24 2010-----------*/
QString CwmsSmtpConfiguration::GetSmtpPassword()
{
   return GetString("Smtp_Password");
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:19:04 2010-----------*
 * @method  CwmsSmtpConfiguration::SetSmtpPassword           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:19:04 2010-----------*/
void CwmsSmtpConfiguration::SetSmtpPassword(QString p_qstrPassword)
{
   SetValue("Smtp_Password", p_qstrPassword);
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:47:30 2010-----------*
 * @method  CwmsSmtpConfiguration::GetSmtpAuthentication     // public, virtual                   *
 * @return  EslSmtpAuthType                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:47:30 2010-----------*/
EslSmtpAuthType CwmsSmtpConfiguration::GetSmtpAuthentication()
{
   return (EslSmtpAuthType)GetInt("Smtp_Authentification");
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:48:23 2010-----------*
 * @method  CwmsSmtpConfiguration::SetSmtpAuthentication     // public                            *
 * @return  void                                             //                                   *
 * @param   EslSmtpAuthType p_eSlSmtpAuthType                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:48:23 2010-----------*/
void CwmsSmtpConfiguration::SetSmtpAuthentication(EslSmtpAuthType p_eSlSmtpAuthType)
{
   SetValue("Smtp_Authentification", p_eSlSmtpAuthType);
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:47:37 2010-----------*
 * @method  CwmsSmtpConfiguration::GetSmtpEncryption         // public, virtual                   *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:47:37 2010-----------*/
int CwmsSmtpConfiguration::GetSmtpEncryption()
{
   return GetInt("Smtp_Encryption");
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:21:07 2010-----------*
 * @method  CwmsSmtpConfiguration::SetSmtpEncryption         // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iEncryption                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 10:21:07 2010-----------*/
void CwmsSmtpConfiguration::SetSmtpEncryption(int p_iEncryption)
{
   SetValue("Smtp_Encryption", p_iEncryption);
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:33:30 2010-----------*
 * @method  CwmsSmtpConfiguration::CheckConfiguration        // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:33:30 2010-----------*/
bool CwmsSmtpConfiguration::CheckConfiguration()
{
   bool bRet = true;

   if (GetEmailAddress().isEmpty())
   {
       CdmMessageManager::critical(tr("Smtp Konfiguration nicht vollstänidg"), tr("Absender E-Mail fehlt."));
      bRet = false;
   }

   if (GetSmtpServer().isEmpty())
   {
      bRet = false;
      CdmMessageManager::critical(tr("Smtp Konfiguration nicht vollstänidg"), tr("Smtp Server fehlt."));
   }

   if (GetSmtpPort() <= 0)
   {
       CdmMessageManager::critical(tr("Smtp Konfiguration nicht vollstänidg"), tr("Smtp Port fehlt."));
      bRet = false;
   }


   return bRet;
}
