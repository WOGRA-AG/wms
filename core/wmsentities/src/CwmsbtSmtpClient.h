/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtSmtpClient.h
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** This class implements the smtp client for sending mails via smtp
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CSLSMTPCLIENT_H
#define CSLSMTPCLIENT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <qstring.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qlist.h>
#include <QList>

// Third Party Includes
#include "qmailtransport.h"

// Own Includes



// Forwards
class IwmsbtSmtpConfiguration;
class CwmsbtMailMessage;
class QMailTransport;

// Enumerations

enum EncryptType {
   Encrypt_NONE = 0,
#ifndef QT_NO_OPENSSL
   Encrypt_SSL = 1,
   Encrypt_TLS = 2
#endif //
};

enum EwmsTransferStatus
{
   Init, 
   Helo, 
   Extension, 
   StartTLS, 
   TLS, 
   Connected, 
   Authenticating, 
   Authenticated,
   MetaData, 
   From, 
   Recv, 
   MRcv, 
   PrepareData, 
   Data, 
   Body, 
   Chunk, 
   ChunkSent, 
   Sent, 
   Quit, 
   Done
};

enum EwmsTransferErrorCode
{
   eWmsTransferErrNoError = 0,
   eWmsTransferErrCodeMinimum = 1024,
   eWmsTransferErrNotImplemented = eWmsTransferErrCodeMinimum,
   eWmsTransferErrFrameworkFault,
   eWmsTransferErrSystemError,
   eWmsTransferErrUnknownResponse,
   eWmsTransferErrLoginFailed,
   eWmsTransferErrCancel,
   eWmsTransferErrFileSystemFull,
   eWmsTransferErrNonexistentMessage,
   eWmsTransferErrEnqueueFailed,
   eWmsTransferErrNoConnection,
   eWmsTransferErrConnectionInUse,
   eWmsTransferErrConnectionNotReady,
   eWmsTransferErrConfiguration,
   eWmsTransferErrInvalidAddress,
   eWmsTransferErrInvalidData,
   eWmsTransferErrTimeout,
   eWmsTransferErrorCodeMaximum = eWmsTransferErrTimeout
};



/*
 * This class implements the smtp client for sending mails via smtp
 */
class CwmsbtSmtpClient : public QObject
{
   Q_OBJECT

   private:
      IwmsbtSmtpConfiguration* m_rpIslSmtpConfiguration;
      CwmsbtMailMessage* m_rpCwmsbtMailMessage;
      EwmsTransferStatus m_eSlStatus;
      bool m_bSending;
      bool m_bSuccess;
      uint m_uiMessageLength;
      uint m_uiSentLength;
      uint m_iTotalSendSize;
      uint m_iProgressSendSize;
      int m_iOutstandingResponses;
      QMailTransport* m_pqMailTransport;
      QByteArray m_qbaDomainName;
      QStringList m_qstrlCapabilities;
      quint32 m_uiAddressComponent;
      QList<QString>::iterator m_qlIt;
   

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:02:34 2010--------*
    * @method  CwmsbtSmtpClient::CwmsbtSmtpClient                  // public                            *
    * @return                                                //                                   *
    * @param   IwmsbtSmtpConfiguration* p_pIslConfig            //                                   *
    * @param   CwmsbtMailMessage* p_pCwmsbtMailMessage             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:02:34 2010-----------*/
    CwmsbtSmtpClient( IwmsbtSmtpConfiguration* p_pIslConfig, CwmsbtMailMessage* p_pCwmsbtMailMessage);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:54:13 2010--------*
    * @method  CwmsbtSmtpClient::~CwmsbtSmtpClient                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsbtSmtpClient                                              *
    *----------------last changed: -----------------------------Sa 9. Jan 11:54:13 2010-----------*/
    virtual ~CwmsbtSmtpClient( );

   public:
   /** +-=---------------------------------------------------------So 10. Jan 13:26:21 2010-------*
    * @method  CwmsbtSmtpClient::SendMail                       // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:26:21 2010----------*/
    void SendMail();

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:45:25 2010--------*
    * @method  CwmsbtSmtpClient::ProgressChangedSignal          // private, signals                  *
    * @return  void                                          //                                   *
    * @param   int p_iSentSize                               //                                   *
    * @param   int p_iCompleteSize                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:45:25 2010-----------*/
    signals:
       void ProgressChangedSignal( int p_iSentSize, int p_iCompleteSize);

    private slots:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:23:37 2010--------*
    * @method  CwmsbtSmtpClient::ReadyReadSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:23:37 2010-----------*/
void ReadyReadSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 31. Okt 12:20:53 2012-------*
    * @method  CwmsbtSmtpClient::ConnectedSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @param   EncryptType p_eEncryptType                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 31. Okt 12:20:53 2012----------*/
void ConnectedSlot(QMailTransport::EncryptType p_eEncryptType);

    private slots:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:25:05 2010--------*
    * @method  CwmsbtSmtpClient::SentSlot                       // private, slots                    *
    * @return  void                                          //                                   *
    * @param   qint64 p_iSent                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:25:05 2010-----------*/
void SentSlot( qint64 p_iSent);


    private slots:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:26:23 2010--------*
    * @method  CwmsbtSmtpClient::TransportErrorSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @param   int p_iErrorCode                              //                                   *
    * @param   QString p_qstrErrorMessage                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:26:23 2010-----------*/
void TransportErrorSlot( int p_iErrorCode, QString p_qstrErrorMessage);

    signals:
       void UpdateStatusSignal(QString p_qstrStatus);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:46:34 2010--------*
    * @method  CwmsbtSmtpClient::IncomingData                   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:46:34 2010-----------*/
    void IncomingData();

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:06:35 2010--------*
    * @method  CwmsbtSmtpClient::InitAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:06:35 2010-----------*/
    void InitAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:59:06 2010--------*
    * @method  CwmsbtSmtpClient::SendCommand                    // private                           *
    * @return  void                                          //                                   *
    * @param   const char *data                              //                                   *
    * @param   int p_iLength                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:59:06 2010-----------*/
    void SendCommand(const char *data, int p_iLength);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:00:54 2010--------*
    * @method  CwmsbtSmtpClient::SendCommand                    // private                           *
    * @return  void                                          //                                   *
    * @param   const QString& p_qtrCommand                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:00:54 2010-----------*/
    void SendCommand(const QString& p_qtrCommand);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:01:38 2010--------*
    * @method  CwmsbtSmtpClient::SendCommand                    // private                           *
    * @return  void                                          //                                   *
    * @param   const QByteArray & p_rComand                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:01:38 2010-----------*/
    void SendCommand(const QByteArray & p_rComand);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 12:59:04 2010-------*
    * @method  CwmsbtSmtpClient::SendCommands                   // private                           *
    * @return  void                                          //                                   *
    * @param   const QStringList& p_rqstrlCommands           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:59:04 2010----------*/
    void SendCommands(const QStringList& p_rqstrlCommands);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:06:46 2010--------*
    * @method  CwmsbtSmtpClient::HeloAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:06:46 2010-----------*/
    void HeloAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:08:25 2010--------*
    * @method  CwmsbtSmtpClient::ExtractDomainName              // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:08:25 2010-----------*/
    void ExtractDomainName(QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:11:33 2010--------*
    * @method  CwmsbtSmtpClient::ExtensionAction                // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:11:33 2010-----------*/
    void ExtensionAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:24:20 2010--------*
    * @method  CwmsbtSmtpClient::StartTlsAction                 // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:24:20 2010-----------*/
    void StartTlsAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:26:53 2010--------*
    * @method  CwmsbtSmtpClient::TlsAction                      // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:26:53 2010-----------*/
    void TlsAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 13:29:22 2010--------*
    * @method  CwmsbtSmtpClient::ConnectedAction                // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 13:29:22 2010-----------*/
    void ConnectedAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:13:45 2010--------*
    * @method  CwmsbtSmtpClient::AuthenticatingAction           // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:13:45 2010-----------*/
    void AuthenticatingAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:33:18 2010--------*
    * @method  CwmsbtSmtpClient::AuthenticatedAction            // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:33:18 2010-----------*/
    void AuthenticatedAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:35:20 2010--------*
    * @method  CwmsbtSmtpClient::MetaDataAction                 // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:35:20 2010-----------*/
    void MetaDataAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:45:00 2010--------*
    * @method  CwmsbtSmtpClient::FromAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:45:00 2010-----------*/
    void FromAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 13:04:36 2010-------*
    * @method  CwmsbtSmtpClient::RcvAction                      // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:04:36 2010----------*/
    void RcvAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 13:04:51 2010-------*
    * @method  CwmsbtSmtpClient::MRcvAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:04:51 2010----------*/
    void MRcvAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 15:01:15 2010--------*
    * @method  CwmsbtSmtpClient::PrepareDataAction              // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 15:01:15 2010-----------*/
    void PrepareDataAction();

   private:
   /** +-=---------------------------------------------------------So 10. Jan 13:05:02 2010-------*
    * @method  CwmsbtSmtpClient::BodyAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:05:02 2010----------*/
    void BodyAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 12:08:15 2010-------*
    * @method  CwmsbtSmtpClient::ChunkAction                    // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:08:15 2010----------*/
    void ChunkAction(uint p_uiResponseCode);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 13:05:14 2010-------*
    * @method  CwmsbtSmtpClient::SentAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @param   QString p_qstrResponse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:05:14 2010----------*/
    void SentAction(uint p_uiResponseCode, QString p_qstrResponse);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 12:17:35 2010-------*
    * @method  CwmsbtSmtpClient::MessageTransmittedSignal       // private, signals                  *
    * @return  void                                          //                                   *
    * @param   bool p_bSuccess                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:17:35 2010----------*/
    signals:
       void MessageTransmittedSignal( bool p_bSuccess);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 12:21:42 2010-------*
    * @method  CwmsbtSmtpClient::QuitAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   uint p_uiResponseCode                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:21:42 2010----------*/
    void QuitAction(uint p_uiResponseCode);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 12:24:23 2010-------*
    * @method  CwmsbtSmtpClient::NextAction                     // private                           *
    * @return  void                                          //                                   *
    * @param   const QString p_qstrResponse                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 12:24:23 2010----------*/
    void NextAction(const QString p_qstrResponse);
};

#endif //
