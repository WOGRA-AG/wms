/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtMailMessage.cpp
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** Implements the Class for defining a message
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QDateTime>
#include <QThread>
#include <QStringList>
#include <QCoreApplication>
#include <QFileInfo>

// WMS Includes
#include "CdmLogging.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsbtSmtpClient.h"
#include "CwmsbtMailMessage.h"


/** +-=---------------------------------------------------------Sa 9. Jan 11:39:25 2010-----------*
 * @method  CwmsbtMailMessage::CwmsbtMailMessage                   // public                            *
 * @return                                                   //                                   *
 * @param   IwmsbtSmtpConfiguration* p_cCslSmtpConfiguration    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:39:25 2010-----------*/
CwmsbtMailMessage::CwmsbtMailMessage(IwmsbtSmtpConfiguration* p_cCslSmtpConfiguration)
: m_pCslSmtpClient(nullptr),
  m_pIslSmtpConfiguration(p_cCslSmtpConfiguration),
  m_bMessageSent(false),
  m_bSuccess(false)
{
}

/** +-=---------------------------------------------------------Sa 9. Jan 10:55:33 2010-----------*
 * @method  CwmsbtMailMessage::~CwmsbtMailMessage                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsbtMailMessage                                                *
 *----------------last changed: --------------------------------Sa 9. Jan 10:55:33 2010-----------*/
CwmsbtMailMessage::~CwmsbtMailMessage()
{
   if (m_pCslSmtpClient)
   {
      DELPTR(m_pCslSmtpClient);
   }
   
   if (m_pIslSmtpConfiguration)
   {
      DELPTR(m_pIslSmtpConfiguration);
   }
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:08:08 2012----------*
 * @method  CwmsbtMailMessage::AddRecipients                 // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString& p_qstrRecipient                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:08 2012----------*/
void CwmsbtMailMessage::AddRecipients(QString& p_qstrRecipient)
{

   m_qvlRecipients.append(p_qstrRecipient);
}

void CwmsbtMailMessage::AddRecipients(QList<QString>& p_qstrRecipient)
{

   m_qvlRecipients = p_qstrRecipient;
}


void CwmsbtMailMessage::AddRecipients(QStringList& p_qstrRecipient)
{
    for(auto qstrRecipient : p_qstrRecipient)
    {
        AddRecipients(qstrRecipient);
    }
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:08:14 2012----------*
 * @method  CwmsbtMailMessage::AddCopy                       // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCopy                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:14 2012----------*/
void CwmsbtMailMessage::AddCopy(QString p_qstrCopy)
{

   m_qvlCopies.append(p_qstrCopy);
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:08:21 2012----------*
 * @method  CwmsbtMailMessage::AddBlindCopy                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrBlindCopy                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:21 2012----------*/
void CwmsbtMailMessage::AddBlindCopy(QString p_qstrBlindCopy)
{

   m_qvlBlindCopies.append(p_qstrBlindCopy);
}

void CwmsbtMailMessage::AddAttachment(QString p_qstrFilename)
{
    QFile qFile(p_qstrFilename);
    QFileInfo  qFileInfo(p_qstrFilename);

    if (qFile.open(QIODevice::ReadOnly))
    {
       QByteArray qContent = qFile.readAll();
       QString qstrContent(qContent.toBase64());

       AddAttachment(qFileInfo.fileName(), qstrContent);
    }
}

void CwmsbtMailMessage::AddAttachment(QString p_qstrFilename, QString p_qstrBase64Data)
{
    m_qlAttachments << QPair<QString,QString>(p_qstrFilename, p_qstrBase64Data);
}


/** +-=---------------------------------------------------------Mi 21. Nov 15:08:28 2012----------*
 * @method  CwmsbtMailMessage::SetSubject                    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSubject                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:28 2012----------*/
void CwmsbtMailMessage::SetSubject(QString p_qstrSubject)
{
   m_qstrSubject = p_qstrSubject;
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:08:35 2012----------*
 * @method  CwmsbtMailMessage::GetSubject                    // public, slots                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:35 2012----------*/
QString CwmsbtMailMessage::GetSubject()
{

   return m_qstrSubject;
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:08:42 2012----------*
 * @method  CwmsbtMailMessage::SetBody                       // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrBody                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:42 2012----------*/
void CwmsbtMailMessage::SetBody(QString p_qstrBody)
{

   m_qstrBody = p_qstrBody;
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:08:48 2012----------*
 * @method  CwmsbtMailMessage::GetBody                       // public, slots                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:08:48 2012----------*/
QString CwmsbtMailMessage::GetBody()
{

   return m_qstrBody;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:36:20 2010-----------*
 * @method  CwmsbtMailMessage::CreateMessage                    // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:36:20 2010-----------*/
QString CwmsbtMailMessage::CreateMessage()
{
   QString qstrMessage;
   qstrMessage += CreateHead();
   m_qstrBody = m_qstrBody.replace("</p>", "</p>\r\n");

   if (m_qlAttachments.isEmpty())
   {
      qstrMessage += "Content-Type: text/html; charset=utf-8\r\nContent-Transfer-Encoding: 8bit\r\n\r\n";
      qstrMessage += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\r\n";
      qstrMessage += m_qstrBody;
   }
   else
   {
      qstrMessage += "Content-Type: multipart/mixed;\r\n boundary=wogramail\r\n\r\n";
      qstrMessage += "--wogramail\r\n";
      qstrMessage += "Content-Type: text/html; charset=utf-8\r\nContent-Transfer-Encoding: 8bit\r\n\r\n";
      qstrMessage += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\r\n";
      qstrMessage += m_qstrBody;
      qstrMessage += "\r\n\r\n";

      for (int iCounter = 0; iCounter < m_qlAttachments.count(); ++ iCounter)
      {
         QString qstrFilename = m_qlAttachments[iCounter].first;
         QString qstrContent(m_qlAttachments[iCounter].second);

         int iPos = 998;
         int iLength = qstrContent.length();

         while (iPos < iLength)
         {
             qstrContent = qstrContent.insert(iPos, "\r\n");
             iPos = iPos + 1000;
             iLength = qstrContent.length();
         }

         qstrMessage += "--wogramail\r\n";
         qstrMessage += "Content-Type: application/octet-stream\r\n";
         qstrMessage += "Content-Disposition: attachment;";
         qstrMessage += " filename=" + qstrFilename + ";\r\n";
         qstrMessage += "Content-Transfer-Encoding: base64\r\n\r\n";
         qstrMessage += qstrContent;
         qstrMessage += "\r\n\r\n";
      }

      qstrMessage += "--wogramail--\r\n";
   }

   return qstrMessage;
}

/** +-=---------------------------------------------------------Do 4. Okt 14:33:27 2012-----------*
 * @method  CwmsbtMailMessage::ExtractDayOfWeek                 // private                           *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 4. Okt 14:33:27 2012-----------*/
QString CwmsbtMailMessage::ExtractDayOfWeek()
{
   QString qstrRet;

   switch (QDate::currentDate().dayOfWeek())
   {
   case 1:
      qstrRet = "Mon";
      break;
   case 2:
      qstrRet = "Tue";
      break;
   case 3:
      qstrRet = "Wed";
      break;
   case 4:
      qstrRet = "Thu";
      break;
   case 5:
      qstrRet = "Fri";
      break;
   case 6:
      qstrRet = "Sat";
      break;
   case 7:
      qstrRet = "Sun";
      break;
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Do 4. Okt 14:36:26 2012-----------*
 * @method  CwmsbtMailMessage::ExtractMonthOfYear               // private                           *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 4. Okt 14:36:26 2012-----------*/
QString CwmsbtMailMessage::ExtractMonthOfYear()
{
   QString qstrRet;

   switch (QDate::currentDate().month())
   {
   case 1:
      qstrRet = "Jan";
      break;
   case 2:
      qstrRet = "Feb";
      break;
   case 3:
      qstrRet = "Mar";
      break;
   case 4:
      qstrRet = "Apr";
      break;
   case 5:
      qstrRet = "May";
      break;
   case 6:
      qstrRet = "Jun";
      break;
   case 7:
      qstrRet = "Jul";
      break;
   case 8:
      qstrRet = "Aug";
      break;
   case 9:
      qstrRet = "Sep";
      break;
   case 10:
      qstrRet = "Oct";
      break;
   case 11:
      qstrRet = "Nov";
      break;
   case 12:
      qstrRet = "Dec";
      break;
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 9. Jan 16:00:27 2010-----------*
 * @method  CwmsbtMailMessage::CreateHead                       // private                           *
 * @return  QString                                          //                                   *
 * @param   bool p_bAddBCC = false                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 16:00:27 2010-----------*/
QString CwmsbtMailMessage::CreateHead(bool p_bAddBCC)
{
   QString qstrMessage;

   if (m_pIslSmtpConfiguration)
   {
      QString qstrDate = ExtractDayOfWeek() + ", " + QString::number(QDate::currentDate().day()) + " " +  ExtractMonthOfYear() + " " + QDateTime::currentDateTime().toUTC().toString("yyyy hh:mm:ss +0000");
      qstrMessage += "Date: " + qstrDate + "\r\n";
      qstrMessage += "From: " + RetrieveSender() + "\r\n";
      qstrMessage += GetRecipientsAsString();
      qstrMessage += GetCopiesAsString();
      if (p_bAddBCC)
      {
         qstrMessage += GetBlindCopiesAsString();
      }
      qstrMessage += "Subject: " + m_qstrSubject + "\r\n";
   }

   return qstrMessage;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:01:31 2010-----------*
 * @method  CwmsbtMailMessage::GetRecipientsAsString            // private                           *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:01:31 2010-----------*/
QString CwmsbtMailMessage::GetRecipientsAsString()
{
   QString qstrMessage;
   qstrMessage += "To: ";
   qstrMessage += GetMailAddressesAsString(m_qvlRecipients) + "\r\n";
   return qstrMessage;
}

/** +-=---------------------------------------------------------Sa 9. Jan 14:54:10 2010-----------*
 * @method  CwmsbtMailMessage::GetRecipients                    // public                            *
 * @return  QList<QString>&                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 14:54:10 2010-----------*/
QList<QString>& CwmsbtMailMessage::GetRecipients()
{
   return m_qvlRecipients;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:07:35 2010-----------*
 * @method  CwmsbtMailMessage::GetCopiesAsString                // private                           *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:07:35 2010-----------*/
QString CwmsbtMailMessage::GetCopiesAsString()
{
   QString qstrMessage;
   qstrMessage += "CC: ";
   qstrMessage += GetMailAddressesAsString(m_qvlCopies) + "\r\n";
   return qstrMessage;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:08:59 2010-----------*
 * @method  CwmsbtMailMessage::GetBlindCopiesAsString           // private                           *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:08:59 2010-----------*/
QString CwmsbtMailMessage::GetBlindCopiesAsString()
{
   QString qstrMessage;
   qstrMessage += "BCC: ";
   qstrMessage += GetMailAddressesAsString(m_qvlBlindCopies) + "\r\n";
   return qstrMessage;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:06:00 2010-----------*
 * @method  CwmsbtMailMessage::GetMailAddressesAsString         // private                           *
 * @return  QString                                          //                                   *
 * @param   QList<QString>& p_rqllAddresses            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:06:00 2010-----------*/
QString CwmsbtMailMessage::GetMailAddressesAsString(QList<QString>& p_rqllAddresses)
{
   QString qstrMailAddresses;
   QList<QString>::iterator qvlIt    = p_rqllAddresses.begin();
   QList<QString>::iterator qvlItEnd = p_rqllAddresses.end();

   for(; qvlIt != qvlItEnd; ++qvlIt)
   {
      QString qstrMailAddress = (*qvlIt);

      if(!qstrMailAddress.isEmpty())
      {
         qstrMailAddresses += "<" + qstrMailAddress + "> ";
      }
   }

   return qstrMailAddresses;
}

/** +-=---------------------------------------------------------Sa 9. Jan 14:41:58 2010-----------*
 * @method  CwmsbtMailMessage::GetRecipientsAsStringList        // public                            *
 * @return  QStringList                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 14:41:58 2010-----------*/
QStringList CwmsbtMailMessage::GetRecipientsAsStringList()
{
   return GetMailAddressesAsStringList("RCPT TO:", m_qvlAllRecipients);
}

/** +-=---------------------------------------------------------Sa 9. Jan 14:40:36 2010-----------*
 * @method  CwmsbtMailMessage::GetMailAddressesAsStringList     // private                           *
 * @return  QStringList                                      //                                   *
 * @param   QString p_qstrPreString                          //                                   *
 * @param   QList<QString>& p_rqllAddresses            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 14:40:36 2010-----------*/
QStringList CwmsbtMailMessage::GetMailAddressesAsStringList(QString p_qstrPreString,
                                                         QList<QString>& p_rqllAddresses)
{

   QStringList qstrMailAddresses;
   QList<QString>::iterator qvlIt    = p_rqllAddresses.begin();
   QList<QString>::iterator qvlItEnd = p_rqllAddresses.end();

   for(; qvlIt != qvlItEnd; ++qvlIt)
   {
      QString qstrMailAddress = (*qvlIt);

      if(!qstrMailAddress.isEmpty())
      {
         qstrMailAddresses.append(p_qstrPreString + " <" + qstrMailAddress + "> ");
      }
   }

   return qstrMailAddresses;
}

/** +-=---------------------------------------------------------Sa 9. Jan 12:14:56 2010-----------*
 * @method  CwmsbtMailMessage::GetMailSize                      // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 12:14:56 2010-----------*/
int CwmsbtMailMessage::GetMailSize()
{
   return CreateMessage().length();
}

/** +-=---------------------------------------------------------So 10. Jan 13:06:31 2010----------*
 * @method  CwmsbtMailMessage::ToRfc2822                        // public                            *
 * @return  void                                             //                                   *
 * @param   QDataStream& p_qdsOut                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:06:31 2010----------*/
void CwmsbtMailMessage::ToRfc2822(QDataStream& p_qdsOut)
{
   QString qstrMail = CreateMessage();
   QByteArray bytes = qstrMail.toUtf8();
   int iLength = bytes.length();
   p_qdsOut.writeRawData(bytes, iLength);
}

/** +-=---------------------------------------------------------Mi 21. Nov 15:09:54 2012----------*
 * @method  CwmsbtMailMessage::SendMessage                   // public, slots                     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 15:09:54 2012----------*/
bool CwmsbtMailMessage::SendMessage()
{
   if (m_pIslSmtpConfiguration)
   {
      BuildAllRecipients();

      if (m_pIslSmtpConfiguration->CheckConfiguration() && CheckMail())
      {

         CwmsbtSmtpClient* m_pCslSmtpClient = new CwmsbtSmtpClient(m_pIslSmtpConfiguration, this);
         connect(m_pCslSmtpClient, SIGNAL(MessageTransmittedSignal(bool)),
                 this, SLOT(MessageTransmittedSlot(bool)));
         m_pCslSmtpClient->SendMail();
      }
   }

   return WaitForMessageSent();
}

IwmsbtSmtpConfiguration* CwmsbtMailMessage::getSmtpConfigurations()
{
    return m_pIslSmtpConfiguration;
}


/** +-=---------------------------------------------------------So 10. Jan 11:47:36 2010----------*
 * @method  CwmsbtMailMessage::BuildAllRecipients               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 11:47:36 2010----------*/
void CwmsbtMailMessage::BuildAllRecipients()
{
   m_qvlAllRecipients += m_qvlRecipients;
   m_qvlAllRecipients += m_qvlCopies;
   m_qvlAllRecipients += m_qvlBlindCopies;
}

/** +-=---------------------------------------------------------So 10. Jan 11:48:08 2010----------*
 * @method  CwmsbtMailMessage::GetAllRecipients                 // public                            *
 * @return  QList<QString>                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 11:48:08 2010----------*/
QList<QString> CwmsbtMailMessage::GetAllRecipients()
{
   return m_qvlAllRecipients;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:15:47 2010-----------*
 * @method  CwmsbtMailMessage::CheckMail                        // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:15:47 2010-----------*/
bool CwmsbtMailMessage::CheckMail()
{
   bool bRet = false;

   if (HasRecipients())
   {
      bRet = true;
   }
   else
   {
      MSG_CRIT("Fehlende Angabe zur Mail", "Bei der Mail ist kein Empfänger angegeben.");
   }

   if (m_qstrSubject.isEmpty())
   {
      bRet = CdmMessageManager::Ask("Hinweis bei der Mailversendung",
                                    "Es wurde kein Betreff angegeben. Wollen Sie die Mail tortzdem senden?");
   }

   if (m_qstrBody.isEmpty())
   {
      bRet = CdmMessageManager::Ask("Hinweis bei der Mailversendung",
                                    "Die Mail hat keinen Inhalt. Wollen Sie sie trotzdem senden?");
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 9. Jan 11:30:18 2010-----------*
 * @method  CwmsbtMailMessage::HasRecipients                    // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Jan 11:30:18 2010-----------*/
bool CwmsbtMailMessage::HasRecipients()
{
   bool bRet = false;

   if (m_qvlAllRecipients.count() > 0)
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 10. Jan 13:26:55 2010----------*
 * @method  CwmsbtMailMessage::MessageTransmittedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @param   bool p_bSuccess                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Jan 13:26:55 2010----------*/
void CwmsbtMailMessage::MessageTransmittedSlot(bool p_bSuccess)
{
    m_bMessageSent = true;
    m_bSuccess = p_bSuccess;

    if(!m_bSuccess)
    {
        MSG_INFO("E-Mail wurde nicht versendet",
                 "E-Mail konnte nicht versendet werden (technisches Problem).");
    }
}

bool CwmsbtMailMessage::WaitForMessageSent(qint64 p_iTimeout)
{
    bool bSent = false;
   qint64 lTimeNeeded = 0;
     qint64 sleep = 100;
    while (!m_bMessageSent)
    {
        QThread* pCurrentThread = QThread::currentThread();

        if (CHKPTR(pCurrentThread))
        {
            pCurrentThread->msleep(sleep);
        }

        lTimeNeeded += sleep;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        if (lTimeNeeded >= p_iTimeout)
        {
            break;
        }
    }

    deleteLater();
    bSent = m_bSuccess;
    return bSent;
}

void CwmsbtMailMessage::SetSender(QString qstrSender)
{
    m_qstrSender = qstrSender;
}

QString CwmsbtMailMessage::RetrieveSender()
{
    QString qstrSender = m_qstrSender;

    if (qstrSender.isEmpty())
    {
        qstrSender = m_pIslSmtpConfiguration->GetEmailAddress();
    }

    return qstrSender;
}

QByteArray CwmsbtMailMessage::encodeQuotedPrintable(const QString &input)
{
    QByteArray output;

    char byte;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    QByteArray latin1 = input.toUtf8();
    for (int i = 0; i < latin1.length() ; ++i)
    {
        byte = latin1[i];

        if ((byte == ' ') || ((byte >= 33) && (byte <= 126)  && (byte != '=')))
        {
            output.append(byte);
        }
        else
        {
            output.append('=');
            output.append(hex[((byte >> 4) & 0x0F)]);
            output.append(hex[(byte & 0x0F)]);
        }
    }

    return output;
}
