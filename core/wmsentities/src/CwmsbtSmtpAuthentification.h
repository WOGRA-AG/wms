/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtSmtpAuthentification.h
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** This class implements the authentification mechanismn
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CSLSMTPAUTHENTIFICATION_H
#define CSLSMTPAUTHENTIFICATION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QList>

// Own Includes
#include "IwmsbtSmtpConfiguration.h"


// Forwards


// Enumerations

/* 
 * This class implements the authentification mechanismn
 */
class CwmsbtSmtpAuthentification
{
   private:
      static QList<QByteArray> m_sqlResponses;

   public:
   public:
   /** +-=---------------------------------------------------------So 10. Jan 12:39:19 2010-------*
    * @method  CwmsbtSmtpAuthentification::GetResponse          // public, static                    *
    * @return  QByteArray                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:39:19 2010----------*/
    static QByteArray GetResponse();


   public:
   /** +-=---------------------------------------------------------So 10. Jan 12:37:36 2010-------*
    * @method  CwmsbtSmtpAuthentification::GetSmtpAuthentification // public, static                 *
    * @return  QByteArray                                    //                                   *
    * @param   IwmsbtSmtpConfiguration* p_cIslSmtpConfiguration//                                    *
    * @param   QStringList& p_rqstrlcapabilities             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:37:36 2010----------*/
    static QByteArray GetSmtpAuthentification(IwmsbtSmtpConfiguration* p_cIslSmtpConfiguration,
                                              QStringList& p_rqstrlcapabilities);
};

#endif //
