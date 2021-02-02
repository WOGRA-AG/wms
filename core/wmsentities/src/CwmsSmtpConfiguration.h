/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsSmtpConfiguration.h
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** Implements the Smtp Configuration class
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSMTPCONFIGURATION_H
#define CWMSSMTPCONFIGURATION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes



// WMS BASETOOLS Includes
#include "IwmsbtSmtpConfiguration.h"

// WMS Includes
#include "CdmObjectAdaptor.h"


// Own Includes
#include "basetools.h"

// Forwards


// Enumerations

/* 
 * This class implements the Smtp Configuration class
 */
class BASETOOLS_API CwmsSmtpConfiguration : public CdmObjectAdaptor, public IwmsbtSmtpConfiguration
{


   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:14:33 2010--------*
    * @method  CwmsSmtpConfiguration::CwmsSmtpConfiguration  // public                            *
    * @return                                                //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:14:33 2010-----------*/
    CwmsSmtpConfiguration( CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:14:40 2010--------*
    * @method  CwmsSmtpConfiguration::CwmsSmtpConfiguration  // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:14:40 2010-----------*/
    CwmsSmtpConfiguration( );

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:14:47 2010--------*
    * @method  CwmsSmtpConfiguration::~CwmsSmtpConfiguration // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsSmtpConfiguration                                      *
    *----------------last changed: -----------------------------Sa 9. Jan 10:14:47 2010-----------*/
    virtual ~CwmsSmtpConfiguration( );

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:46:52 2010--------*
    * @method  CwmsSmtpConfiguration::GetUserName            // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:46:52 2010-----------*/
    virtual QString GetUserName();


   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:46:59 2010--------*
    * @method  CwmsSmtpConfiguration::GetEmailAddress        // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:46:59 2010-----------*/
    virtual QString GetEmailAddress();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:47:06 2010--------*
    * @method  CwmsSmtpConfiguration::GetSmtpServer          // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:47:06 2010-----------*/
    virtual QString GetSmtpServer();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:17:10 2010--------*
    * @method  CwmsSmtpConfiguration::SetSmtpServer          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrServer                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:17:10 2010-----------*/
    void SetSmtpServer(QString p_qstrServer);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:47:11 2010--------*
    * @method  CwmsSmtpConfiguration::GetSmtpPort            // public, virtual                   *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:47:11 2010-----------*/
    virtual int GetSmtpPort();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:17:46 2010--------*
    * @method  CwmsSmtpConfiguration::SetSmtpPort            // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iPort                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:17:46 2010-----------*/
    void SetSmtpPort(int p_iPort);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:47:18 2010--------*
    * @method  CwmsSmtpConfiguration::GetSmtpUsername        // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:47:18 2010-----------*/
    virtual QString GetSmtpUsername();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:18:30 2010--------*
    * @method  CwmsSmtpConfiguration::SetSmtpUsername        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrSmtpUsername                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:18:30 2010-----------*/
    void SetSmtpUsername(QString p_qstrSmtpUsername);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:47:24 2010--------*
    * @method  CwmsSmtpConfiguration::GetSmtpPassword        // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:47:24 2010-----------*/
    virtual QString GetSmtpPassword();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:19:04 2010--------*
    * @method  CwmsSmtpConfiguration::SetSmtpPassword        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:19:04 2010-----------*/
    void SetSmtpPassword(QString p_qstrPassword);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:47:30 2010--------*
    * @method  CwmsSmtpConfiguration::GetSmtpAuthentication  // public, virtual                   *
    * @return  EslSmtpAuthType                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:47:30 2010-----------*/
    virtual EslSmtpAuthType GetSmtpAuthentication();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:48:23 2010--------*
    * @method  CwmsSmtpConfiguration::SetSmtpAuthentication  // public                            *
    * @return  void                                          //                                   *
    * @param   EslSmtpAuthType p_eSlSmtpAuthType             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:48:23 2010-----------*/
    void SetSmtpAuthentication(EslSmtpAuthType p_eSlSmtpAuthType);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:47:37 2010--------*
    * @method  CwmsSmtpConfiguration::GetSmtpEncryption      // public, virtual                   *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:47:37 2010-----------*/
    virtual int GetSmtpEncryption();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:21:07 2010--------*
    * @method  CwmsSmtpConfiguration::SetSmtpEncryption      // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iEncryption                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 10:21:07 2010-----------*/
    void SetSmtpEncryption(int p_iEncryption);

    void SetSmtpSender(QString p_qstrSmtpSender);
    QString GetSmtpSender();
private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:33:30 2010--------*
    * @method  CwmsSmtpConfiguration::CheckConfiguration     // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:33:30 2010-----------*/
    bool CheckConfiguration();
};

#endif //
