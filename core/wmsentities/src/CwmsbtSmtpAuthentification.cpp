/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtSmtpAuthentification.cpp
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** This class implements the authentification mechanismn
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QByteArray>
#include <QString>

// Own Includes
#include "IwmsbtSmtpConfiguration.h"
#include "CwmsbtSmtpAuthentification.h"

QList<QByteArray> CwmsbtSmtpAuthentification::m_sqlResponses;

/** +-=---------------------------------------------------------So 10. Jan 12:37:36 2010----------*
 * @method  CwmsbtSmtpAuthentification::GetSmtpAuthentification // public, static                    *
 * @return  QByteArray                                       //                                   *
 * @param   IwmsbtSmtpConfiguration* p_cIslSmtpConfiguration    //                                   *
 * @param   QStringList& p_rqstrlcapabilities                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:37:36 2010----------*/
QByteArray CwmsbtSmtpAuthentification::GetSmtpAuthentification(IwmsbtSmtpConfiguration* p_cIslSmtpConfiguration,
                                                            QStringList& p_rqstrlcapabilities)
{
   QByteArray qbaResult;
   Q_UNUSED(p_rqstrlcapabilities);

   if (p_cIslSmtpConfiguration)
   {
      if (p_cIslSmtpConfiguration->GetSmtpAuthentication() != Auth_NONE) 
      {
         QByteArray qbaUsername(p_cIslSmtpConfiguration->GetSmtpUsername().toLocal8Bit());
         QByteArray qbaPassword(p_cIslSmtpConfiguration->GetSmtpPassword().toLocal8Bit());

         if (p_cIslSmtpConfiguration->GetSmtpAuthentication() == Auth_LOGIN) 
         {
            qbaResult = QByteArray("LOGIN");
            m_sqlResponses << qbaUsername << qbaPassword;
         } 
         else if (p_cIslSmtpConfiguration->GetSmtpAuthentication() == Auth_PLAIN) 
         {
            qbaResult = QByteArray("PLAIN");
            m_sqlResponses << QByteArray(qbaUsername + '\0' + qbaUsername + '\0' + qbaPassword);
         }
      }
   }


   if (!qbaResult.isEmpty()) 
   {
      qbaResult.prepend("AUTH ");
   }

   return qbaResult;
}

/** +-=---------------------------------------------------------So 10. Jan 12:39:19 2010----------*
 * @method  CwmsbtSmtpAuthentification::GetResponse             // public, static                    *
 * @return  QByteArray                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:39:19 2010----------*/
QByteArray CwmsbtSmtpAuthentification::GetResponse()
{
   return m_sqlResponses.takeFirst();
}
