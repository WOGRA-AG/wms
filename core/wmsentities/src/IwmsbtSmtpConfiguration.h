/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: IwmsbtSmtpConfiguration.h
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** Implements the interface for the smtp configuration
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef ISLSMTPCONFIGURATION_H
#define ISLSMTPCONFIGURATION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// Own Includes



// Forwards


// Enumerations
enum EslSmtpAuthType 
{
   Auth_NONE = 0,
   Auth_LOGIN = 1,
   Auth_PLAIN = 2,
   Auth_INCOMING = 3
};

/* 
 * This class implements the interface for the SMTP configuration
 */
class IwmsbtSmtpConfiguration
{

public:
   virtual ~IwmsbtSmtpConfiguration(){};
   virtual QString GetUserName() = 0;
   virtual QString GetEmailAddress() = 0;
   virtual QString GetSmtpServer() = 0;
   virtual QString GetSmtpSender() = 0;
   virtual int GetSmtpPort() = 0;
   virtual QString GetSmtpUsername() = 0;
   virtual QString GetSmtpPassword() = 0;
   virtual EslSmtpAuthType GetSmtpAuthentication() = 0;
   virtual int GetSmtpEncryption() = 0;
   virtual bool CheckConfiguration() = 0;
};

#endif //
