/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtSmtpClient.cpp
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** This class implements the smtp client for sending mails via smtp
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QtNetwork/QHostAddress>

// Own Includes
#include "qmailtransport.h"
#include "CdmMessageManager.h"
#include "CwmsbtMailMessage.h"
#include "IwmsbtSmtpConfiguration.h"
#include "CwmsbtSmtpAuthentification.h"
#include "CwmsbtSmtpClient.h"

#define QT_NO_OPENSSL


/** +-=---------------------------------------------------------Sa 9. Jan 12:02:34 2010-----------*
 * @method  CwmsbtSmtpClient::CwmsbtSmtpClient                     // public                            *
 * @return                                                   //                                   *
 * @param   IwmsbtSmtpConfiguration* p_pIslConfig               //                                   *
 * @param   CwmsbtMailMessage* p_pCwmsbtMailMessage                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:02:34 2010-----------*/
CwmsbtSmtpClient::CwmsbtSmtpClient(IwmsbtSmtpConfiguration* p_pIslConfig, CwmsbtMailMessage* p_pCwmsbtMailMessage)
: m_rpIslSmtpConfiguration(p_pIslConfig),
  m_rpCwmsbtMailMessage(p_pCwmsbtMailMessage),
  m_eSlStatus(Init),
  m_bSending(false),
  m_bSuccess(false),
  m_uiMessageLength(0),
  m_uiSentLength(0),
  m_iTotalSendSize(0),
  m_iProgressSendSize(0),
  m_iOutstandingResponses(0),
  m_pqMailTransport(nullptr),
  m_uiAddressComponent(0)
{
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:54:13 2010-----------*
 * @method  CwmsbtSmtpClient::~CwmsbtSmtpClient                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsbtSmtpClient                                                 *
 *----------------last changed: --------------------------------Sa 9. Jan 11:54:13 2010-----------*/
CwmsbtSmtpClient::~CwmsbtSmtpClient()
{
   // nothing to do here ;-)
}

/** +-=---------------------------------------------------------So 10. Jan 13:26:21 2010----------*
 * @method  CwmsbtSmtpClient::SendMail                          // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:26:21 2010----------*/
void CwmsbtSmtpClient::SendMail()
{
   if (m_bSending) 
   {
      MSG_CRIT("Senden nicht möglich",
               "Es wird gerade eine Mail versendet. Daher ist derzeit das Senden nicht möglich");
      return;
   }

   if (m_rpIslSmtpConfiguration->GetSmtpServer().isEmpty()) 
   {
      m_eSlStatus = Done;
      MSG_CRIT("Senden nicht möglich",
               "Smtp Server in Einstellungen nicht definiert");

      return;
   }

   // Calculate the total indicative size of the messages we're sending
   m_iTotalSendSize = m_rpCwmsbtMailMessage->GetMailSize();
   m_iProgressSendSize = 0;
   emit ProgressChangedSignal(m_iProgressSendSize, m_iTotalSendSize);

   m_eSlStatus = Init;
   m_bSending = true;
   
   if (!m_pqMailTransport) 
   {
      // Set up the m_pqMailTransport
      m_pqMailTransport = new QMailTransport("SMTP");

      connect(m_pqMailTransport, SIGNAL(readyRead()),
              this, SLOT(ReadyReadSlot()));
      connect(m_pqMailTransport, SIGNAL(connected(QMailTransport::EncryptType)),
              this, SLOT(ConnectedSlot(QMailTransport::EncryptType)));
      connect(m_pqMailTransport, SIGNAL(bytesWritten(qint64)),
              this, SLOT(SentSlot(qint64)));
   }

   m_pqMailTransport->open(m_rpIslSmtpConfiguration->GetSmtpServer(), 
                           m_rpIslSmtpConfiguration->GetSmtpPort(), 
                           static_cast<QMailTransport::EncryptType>(m_rpIslSmtpConfiguration->GetSmtpEncryption()));
}




/** +-=---------------------------------------------------------Sa 9. Jan 12:23:37 2010-----------*
 * @method  CwmsbtSmtpClient::ReadyReadSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:23:37 2010-----------*/
void CwmsbtSmtpClient::ReadyReadSlot()
{
   IncomingData();
}

/** +-=---------------------------------------------------------Sa 9. Jan 12:46:34 2010-----------*
 * @method  CwmsbtSmtpClient::IncomingData                      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:46:34 2010-----------*/
void CwmsbtSmtpClient::IncomingData()
{
#ifndef ANDROID
   while (m_pqMailTransport->canReadLine()) 
   {
      QString qstrResponse = m_pqMailTransport->readLine();
   
      if (m_iOutstandingResponses > 0) 
      {
         --m_iOutstandingResponses;
      }

      if (m_iOutstandingResponses > 0) 
      {
         // For pipelined qstrLCommands, just ensure that they did not fail
         if (!qstrResponse.isEmpty() && (qstrResponse[0] != QChar('2'))) 
         {
            TransportErrorSlot(eWmsTransferErrUnknownResponse, qstrResponse);
         }
      } 
      else 
      {
         NextAction(qstrResponse);
      }
   }
#endif //
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:06:35 2010-----------*
 * @method  CwmsbtSmtpClient::InitAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:06:35 2010-----------*/
void CwmsbtSmtpClient::InitAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 220) 
   {
      //mailItr = mailList.begin();
      //capabilities.clear();

      // We need to know if extensions are supported
      SendCommand(QString("EHLO WOGRA-Mail-System"));
      m_eSlStatus = Helo;
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   } 
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:06:46 2010-----------*
 * @method  CwmsbtSmtpClient::HeloAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:06:46 2010-----------*/
void CwmsbtSmtpClient::HeloAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 500) 
   {
      // EHLO is not implemented by this server - fallback to HELO
      SendCommand(QString("HELO WOGRA-Mail-System"));
   } 
   else if (p_uiResponseCode == 250) 
   {
      ExtractDomainName(p_qstrResponse);

      if (p_qstrResponse[3] == '-') 
      {
         // This is to be followed by extension keywords
         m_eSlStatus = Extension;
      } 
      else 
      {
         // No extension data available - proceed to TLS negotiation
         m_eSlStatus = StartTLS;
         NextAction(QString());
      }
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:08:25 2010-----------*
 * @method  CwmsbtSmtpClient::ExtractDomainName                 // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:08:25 2010-----------*/
void CwmsbtSmtpClient::ExtractDomainName(QString p_qstrResponse)
{
   if (m_qbaDomainName.isEmpty()) 
   {
      // Extract the domain name from the greeting
      int index = p_qstrResponse.indexOf(' ', 4);
      if (index == -1) 
      {
         m_qbaDomainName = p_qstrResponse.mid(4).trimmed().toLocal8Bit();
      } 
      else 
      {
         m_qbaDomainName = p_qstrResponse.mid(4, index - 4).trimmed().toLocal8Bit();
      }
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:11:33 2010-----------*
 * @method  CwmsbtSmtpClient::ExtensionAction                   // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:11:33 2010-----------*/
void CwmsbtSmtpClient::ExtensionAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 250) 
   {
      m_qstrlCapabilities.append(p_qstrResponse.mid(4).trimmed());

      if (p_qstrResponse[3] == '-') 
      {
         // More to follow
      } 
      else 
      {
         // Proceed to TLS negotiation
         m_eSlStatus = StartTLS;
         NextAction(QString());
      }
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   } 
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:24:20 2010-----------*
 * @method  CwmsbtSmtpClient::StartTlsAction                    // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:24:20 2010-----------*/
void CwmsbtSmtpClient::StartTlsAction(uint p_uiResponseCode, QString p_qstrResponse)
{
    Q_UNUSED(p_uiResponseCode);
    Q_UNUSED(p_qstrResponse);
#ifndef QT_NO_OPENSSL
   const bool bUseTLS(m_rpIslSmtpConfiguration->GetSmtpEncryption() == QMailTransport::Encrypt_TLS);
#else
   const bool bUseTLS(false);
#endif //

   if (bUseTLS && 
       !m_pqMailTransport->isEncrypted()) 
   {
      SendCommand(QString("STARTTLS"));
      m_eSlStatus = TLS;
   } 
   else 
   {
      m_eSlStatus = Connected;
      NextAction(QString());
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:26:53 2010-----------*
 * @method  CwmsbtSmtpClient::TlsAction                         // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:26:53 2010-----------*/
void CwmsbtSmtpClient::TlsAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 220) 
   {
#ifndef QT_NO_OPENSSL
      // Switch into encrypted mode
      m_pqMailTransport->switchToEncrypted();
#endif //
   } 
   else  
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:29:22 2010-----------*
 * @method  CwmsbtSmtpClient::ConnectedAction                   // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:29:22 2010-----------*/
void CwmsbtSmtpClient::ConnectedAction(uint p_uiResponseCode, QString p_qstrResponse)
{
    Q_UNUSED(p_uiResponseCode);
    Q_UNUSED(p_qstrResponse);

   // We are now connected with appropriate encryption

   // Find the properties of our connection
   QHostAddress localAddress(m_pqMailTransport->socket().localAddress());
   
   if (localAddress.isNull()) 
   {
      // Better to use the remote address than nothing...
      localAddress = m_pqMailTransport->socket().peerAddress();

      if (localAddress.isNull()) 
      {
         localAddress = QHostAddress(QHostAddress::LocalHost);
      }
   }

   m_uiAddressComponent = localAddress.toIPv4Address();

   // Find the authentication mode to use
   QByteArray authCmd(CwmsbtSmtpAuthentification::GetSmtpAuthentification(m_rpIslSmtpConfiguration, 
                                                                       m_qstrlCapabilities));

   if (!authCmd.isEmpty()) 
   {
      SendCommand(authCmd);
      m_eSlStatus = Authenticating;
   } 
   else 
   {
      m_eSlStatus = Authenticated;
      NextAction(QString());
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 14:13:45 2010-----------*
 * @method  CwmsbtSmtpClient::AuthenticatingAction              // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 14:13:45 2010-----------*/
void CwmsbtSmtpClient::AuthenticatingAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 334) 
   {
      // This is a continuation containing a challenge string (in Base64)
      QByteArray challenge = QByteArray::fromBase64(p_qstrResponse.mid(4).toLocal8Bit());
      QByteArray qbaResponse(CwmsbtSmtpAuthentification::GetResponse());

      if (!qbaResponse.isEmpty()) 
      {
         // Send the p_qstrResponse as Base64 encoded
         SendCommand(qbaResponse.toBase64());
      }
   } 
   else if (p_uiResponseCode == 235) 
   {
      // We are now authenticated
      m_eSlStatus = Authenticated;
      NextAction(QString());
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrLoginFailed, p_qstrResponse);
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 14:33:18 2010-----------*
 * @method  CwmsbtSmtpClient::AuthenticatedAction               // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 14:33:18 2010-----------*/
void CwmsbtSmtpClient::AuthenticatedAction(uint p_uiResponseCode, QString p_qstrResponse)
{
    Q_UNUSED(p_uiResponseCode);
    Q_UNUSED(p_qstrResponse);

   if (!m_rpCwmsbtMailMessage) 
   {
      m_eSlStatus = Quit;
   } 
   else 
   {
      m_eSlStatus = MetaData;
   }

   NextAction(QString());
}

/** +-=---------------------------------------------------------Sa 9. Jan 14:35:20 2010-----------*
* @method  CwmsbtSmtpClient::MetaDataAction                    // private                           *
* @return  void                                             //                                   *
* @param   uint p_uiResponseCode                            //                                   *
* @param   QString p_qstrResponse                           //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Sa 9. Jan 14:35:20 2010-----------*/
void CwmsbtSmtpClient::MetaDataAction(uint p_uiResponseCode, QString p_qstrResponse)
{
    Q_UNUSED(p_uiResponseCode);
    Q_UNUSED(p_qstrResponse);
   if (m_qstrlCapabilities.contains("PIPELINING")) 
   {
      // We can send all our non-message qstrLCommands together
      QStringList qstrlCommands;
      qstrlCommands.append("MAIL FROM: " + m_rpCwmsbtMailMessage->RetrieveSender());
      qstrlCommands += m_rpCwmsbtMailMessage->GetRecipientsAsStringList();
      SendCommands(qstrlCommands);

      // Continue on with the message data proper
      m_eSlStatus = PrepareData;
      NextAction(QString());
   } 
   else 
   {
      // Send meta data elements individually
      m_eSlStatus = From;
      NextAction(QString());
   }
}


/** +-=---------------------------------------------------------Sa 9. Jan 14:45:00 2010-----------*
* @method  CwmsbtSmtpClient::FromAction                        // private                           *
* @return  void                                             //                                   *
* @param   uint p_uiResponseCode                            //                                   *
* @param   QString p_qstrResponse                           //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Sa 9. Jan 14:45:00 2010-----------*/
void CwmsbtSmtpClient::FromAction(uint p_uiResponseCode, QString p_qstrResponse)
{
    Q_UNUSED(p_uiResponseCode);
    Q_UNUSED(p_qstrResponse);

   SendCommand("MAIL FROM: " + m_rpCwmsbtMailMessage->RetrieveSender());
   m_eSlStatus = Recv;
   QString qstrStatusSignal = tr( "Sending: %1").arg(m_rpCwmsbtMailMessage->GetSubject());
   emit UpdateStatusSignal(qstrStatusSignal);
}

/** +-=---------------------------------------------------------So 10. Jan 13:04:36 2010----------*
 * @method  CwmsbtSmtpClient::RcvAction                         // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:04:36 2010----------*/
void CwmsbtSmtpClient::RcvAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 250) 
   {
      m_qlIt = m_rpCwmsbtMailMessage->GetAllRecipients().begin();
      if (m_qlIt == m_rpCwmsbtMailMessage->GetAllRecipients().end()) 
      {
         TransportErrorSlot(eWmsTransferErrInvalidAddress, tr("Keine Empfänger eingegeben"));
      } 
      else 
      {
         SendCommand("RCPT TO: <" + *m_qlIt + ">");
         m_eSlStatus = MRcv;
      }
   } 
   else  
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   } 
}

/** +-=---------------------------------------------------------So 10. Jan 13:04:51 2010----------*
 * @method  CwmsbtSmtpClient::MRcvAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:04:51 2010----------*/
void CwmsbtSmtpClient::MRcvAction(uint p_uiResponseCode, QString p_qstrResponse)
{

   if ((p_uiResponseCode == 250) || (p_uiResponseCode == 251)) 
   {
      m_qlIt++;

      if (m_qlIt != m_rpCwmsbtMailMessage->GetAllRecipients().end()) 
      {
         SendCommand("RCPT TO: <" + *m_qlIt + ">");
      } 
      else 
      {
         m_eSlStatus = PrepareData;
         NextAction(QString());
      }
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 15:01:15 2010-----------*
 * @method  CwmsbtSmtpClient::PrepareDataAction                 // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 15:01:15 2010-----------*/
void CwmsbtSmtpClient::PrepareDataAction()
{
   m_eSlStatus = Data;
   NextAction(QString());
}

/** +-=---------------------------------------------------------So 10. Jan 13:05:02 2010----------*
 * @method  CwmsbtSmtpClient::BodyAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:05:02 2010----------*/
void CwmsbtSmtpClient::BodyAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   if (p_uiResponseCode == 354) 
   {
      m_uiSentLength = 0;

      // Set the message's message ID
      m_pqMailTransport->mark();
      m_rpCwmsbtMailMessage->ToRfc2822(m_pqMailTransport->stream());
      m_uiMessageLength = m_pqMailTransport->bytesSinceMark();
      m_pqMailTransport->stream().writeRawData("\r\n.\r\n", 5);
      m_eSlStatus = Sent;
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   }
}

/** +-=---------------------------------------------------------So 10. Jan 12:08:15 2010----------*
 * @method  CwmsbtSmtpClient::ChunkAction                       // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:08:15 2010----------*/
void CwmsbtSmtpClient::ChunkAction(uint p_uiResponseCode)
{
    Q_UNUSED(p_uiResponseCode);

   TransportErrorSlot(-1, tr("Chunk Sendungen werden nicht unterstützt."));
   m_eSlStatus = Sent;
   NextAction("");
}

/** +-=---------------------------------------------------------So 10. Jan 13:05:14 2010----------*
 * @method  CwmsbtSmtpClient::SentAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @param   QString p_qstrResponse                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:05:14 2010----------*/
void CwmsbtSmtpClient::SentAction(uint p_uiResponseCode, QString p_qstrResponse)
{
   // The last send operation is complete
   if (p_uiResponseCode == 250) 
   {
      m_eSlStatus = Quit;
      NextAction(QString());
   } 
   else 
   {
      TransportErrorSlot(eWmsTransferErrUnknownResponse, p_qstrResponse);
   }
}

/** +-=---------------------------------------------------------So 10. Jan 12:21:42 2010----------*
 * @method  CwmsbtSmtpClient::QuitAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   uint p_uiResponseCode                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:21:42 2010----------*/
void CwmsbtSmtpClient::QuitAction(uint p_uiResponseCode)
{
    Q_UNUSED(p_uiResponseCode);

   // Completed successfully
   SendCommand(QString("QUIT"));

   m_bSending = false;
   m_eSlStatus = Done;
   m_pqMailTransport->close();

   QString qstrStatus = tr("Mail versendet.");
   emit UpdateStatusSignal(qstrStatus);
   emit MessageTransmittedSignal(true);

}

/** +-=---------------------------------------------------------So 10. Jan 12:24:23 2010----------*
 * @method  CwmsbtSmtpClient::NextAction                        // private                           *
 * @return  void                                             //                                   *
 * @param   const QString p_qstrResponse                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:24:23 2010----------*/
void CwmsbtSmtpClient::NextAction(const QString p_qstrResponse)
{
   uint uiResponseCode(0);

   if (!p_qstrResponse.isEmpty())
   {
      uiResponseCode = p_qstrResponse.left(3).toUInt();
   }

   switch (m_eSlStatus)
   {
    case Init:  
          InitAction(uiResponseCode, p_qstrResponse);
          break;
    case Helo:
       {
          HeloAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case Extension:
       {
          ExtensionAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case StartTLS:
       {
          StartTlsAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case TLS:
       {
          TlsAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case Connected:
       {
          ConnectedAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case Authenticating:
       {
          AuthenticatingAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case Authenticated:
       {
          AuthenticatedAction(uiResponseCode, p_qstrResponse);
          break;
       }

    case MetaData:
       {
          MetaDataAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case From:  
       {
          FromAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case Recv:  
       {
          RcvAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case MRcv:  
       {
          MRcvAction(uiResponseCode, p_qstrResponse);
          break;
       }
    case PrepareData:  
       {
          PrepareDataAction();
          break;
       }
    case Data:  
       {
          SendCommand(QString("DATA"));
          m_eSlStatus = Body;
          break;
       }
    case Body:  
       {
          BodyAction(uiResponseCode, p_qstrResponse);
          break;
       }

    case Chunk:
       {
          // not supported
          ChunkAction(uiResponseCode);
          break;
       }
    case ChunkSent:
       {
          // not supported
          ChunkAction(uiResponseCode);
          break;
       }

    case Sent:  
       {
          SentAction(uiResponseCode, p_qstrResponse);
          break;
       }

    case Quit:  
       {
          QuitAction(uiResponseCode);
          break;
       }

    case Done:  
       {
          // Supposed to be unused here
          qWarning() << "nextAction - Unexpected status value: " << m_eSlStatus;
          break;
       }

   }
}


/** +-=---------------------------------------------------------Mi 31. Okt 12:20:53 2012----------*
 * @method  CwmsbtSmtpClient::ConnectedSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @param   EncryptType p_eEncryptType                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 31. Okt 12:20:53 2012----------*/
void CwmsbtSmtpClient::ConnectedSlot(QMailTransport::EncryptType p_eEncryptType)
{
   if (m_rpIslSmtpConfiguration->GetSmtpEncryption() == p_eEncryptType) 
   {
       QString qstrSignal = tr("Verbunden");
      emit UpdateStatusSignal(qstrSignal);
   }

#ifndef QT_NO_OPENSSL

   if ((m_rpIslSmtpConfiguration->GetSmtpEncryption() == QMailTransport::Encrypt_TLS) && 
       (m_eSlStatus == TLS)) 
   {
      // We have entered TLS mode - restart the SMTP dialog
      SendCommand(QString("EHLO WOGRA-Mail-System"));
      m_eSlStatus = Helo;
   }

#endif //
}

/** +-=---------------------------------------------------------Sa 9. Jan 12:59:06 2010-----------*
 * @method  CwmsbtSmtpClient::SendCommand                       // private                           *
 * @return  void                                             //                                   *
 * @param   const char *data                                 //                                   *
 * @param   int p_iLength                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:59:06 2010-----------*/
void CwmsbtSmtpClient::SendCommand(const char *data, int p_iLength)
{
   if (p_iLength == -1)
   {
      p_iLength = ::strlen(data);
   }

   QDataStream &out(m_pqMailTransport->stream());
   out.writeRawData(data, p_iLength);
   out.writeRawData("\r\n", 2);

   ++m_iOutstandingResponses;
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:00:54 2010-----------*
 * @method  CwmsbtSmtpClient::SendCommand                       // private                           *
 * @return  void                                             //                                   *
 * @param   const QString& p_qtrCommand                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:00:54 2010-----------*/
void CwmsbtSmtpClient::SendCommand(const QString& p_qtrCommand)
{
   SendCommand(p_qtrCommand.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 9. Jan 13:01:38 2010-----------*
 * @method  CwmsbtSmtpClient::SendCommand                       // private                           *
 * @return  void                                             //                                   *
 * @param   const QByteArray & p_rComand                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 13:01:38 2010-----------*/
void CwmsbtSmtpClient::SendCommand(const QByteArray & p_rComand)
{
   SendCommand(p_rComand.data(), p_rComand.length());
}

/** +-=---------------------------------------------------------So 10. Jan 12:59:04 2010----------*
 * @method  CwmsbtSmtpClient::SendCommands                      // private                           *
 * @return  void                                             //                                   *
 * @param   const QStringList& p_rqstrlCommands              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:59:04 2010----------*/
void CwmsbtSmtpClient::SendCommands(const QStringList& p_rqstrlCommands)
{
   foreach (const QString &cmd, p_rqstrlCommands)
   {
      SendCommand(cmd.toLocal8Bit());
   }
}

/** +-=---------------------------------------------------------Sa 9. Jan 12:25:05 2010-----------*
 * @method  CwmsbtSmtpClient::SentSlot                          // private, slots                    *
 * @return  void                                             //                                   *
 * @param   qint64 p_iSent                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:25:05 2010-----------*/
void CwmsbtSmtpClient::SentSlot(qint64 p_iSent)
{
   m_uiSentLength += p_iSent;
   emit ProgressChangedSignal(m_uiSentLength, m_uiMessageLength);
}



/** +-=---------------------------------------------------------Sa 9. Jan 12:26:23 2010-----------*
 * @method  CwmsbtSmtpClient::TransportErrorSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @param   int p_iErrorCode                                 //                                   *
 * @param   QString p_qstrErrorMessage                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:26:23 2010-----------*/
void CwmsbtSmtpClient::TransportErrorSlot(int p_iErrorCode, QString p_qstrErrorMessage)
{
   QString qstrMessage = tr("Fehlercode: ") + QString::number(p_iErrorCode) 
                          + "\n" + tr("Nachricht:") + "\n" + p_qstrErrorMessage;

  MSG_CRIT("Senden nicht möglich", qstrMessage.toUtf8());
}

/** +-=---------------------------------------------------------Sa 9. Jan 12:45:25 2010-----------*
 * @method  CwmsbtSmtpClient::ProgressChangedSignal             // private, signals                  *
 * @return  void                                             //                                   *
 * @param   int p_iSentSize                                  //                                   *
 * @param   int p_iCompleteSize                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:45:25 2010-----------*/

/** +-=---------------------------------------------------------Sa 9. Jan 12:36:06 2010-----------*
 * @method  CwmsbtSmtpClient::UpdateStatusSignal                // private, signals                  *
 * @return  void                                             //                                   *
 * @param   QString& p_qstrStatus                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:36:06 2010-----------*/

/** +-=---------------------------------------------------------So 10. Jan 12:17:35 2010----------*
 * @method  CwmsbtSmtpClient::MessageTransmittedSignal          // private, signals                  *
 * @return  void                                             //                                   *
 * @param   bool p_bSuccess                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 12:17:35 2010----------*/

