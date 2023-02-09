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


CwmsbtMailMessage::CwmsbtMailMessage(IwmsbtSmtpConfiguration* p_cCslSmtpConfiguration)
: m_pCslSmtpClient(nullptr),
  m_pIslSmtpConfiguration(p_cCslSmtpConfiguration),
  m_bMessageSent(false),
  m_bSuccess(false)
{
}

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

void CwmsbtMailMessage::AddCopy(QString p_qstrCopy)
{

   m_qvlCopies.append(p_qstrCopy);
}

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

void CwmsbtMailMessage::SetSubject(QString p_qstrSubject)
{
   m_qstrSubject = p_qstrSubject;
}

QString CwmsbtMailMessage::GetSubject()
{

   return m_qstrSubject;
}

void CwmsbtMailMessage::SetBody(QString p_qstrBody)
{

   m_qstrBody = p_qstrBody;
}

QString CwmsbtMailMessage::GetBody()
{

   return m_qstrBody;
}

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

QString CwmsbtMailMessage::CreateHead(bool p_bAddBCC)
{
   QString qstrMessage;

   if (m_pIslSmtpConfiguration)
   {
      QString qstrDate = ExtractDayOfWeek() + ", " + QString::number(QDate::currentDate().day()) + " " +
                         ExtractMonthOfYear() + " " + QDateTime::currentDateTime().toUTC().toString("yyyy hh:mm:ss +0000");
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

QString CwmsbtMailMessage::GetRecipientsAsString()
{
   QString qstrMessage;
   qstrMessage += "To: ";
   qstrMessage += GetMailAddressesAsString(m_qvlRecipients) + "\r\n";
   return qstrMessage;
}

QList<QString>& CwmsbtMailMessage::GetRecipients()
{
   return m_qvlRecipients;
}

QString CwmsbtMailMessage::GetCopiesAsString()
{
   QString qstrMessage;
   qstrMessage += "CC: ";
   qstrMessage += GetMailAddressesAsString(m_qvlCopies) + "\r\n";
   return qstrMessage;
}

QString CwmsbtMailMessage::GetBlindCopiesAsString()
{
   QString qstrMessage;
   qstrMessage += "BCC: ";
   qstrMessage += GetMailAddressesAsString(m_qvlBlindCopies) + "\r\n";
   return qstrMessage;
}

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

QStringList CwmsbtMailMessage::GetRecipientsAsStringList()
{
   return GetMailAddressesAsStringList("RCPT TO:", m_qvlAllRecipients);
}

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

int CwmsbtMailMessage::GetMailSize()
{
   return CreateMessage().length();
}

void CwmsbtMailMessage::ToRfc2822(QDataStream& p_qdsOut)
{
   QString qstrMail = CreateMessage();
   QByteArray bytes = qstrMail.toUtf8();
   int iLength = bytes.length();
   p_qdsOut.writeRawData(bytes, iLength);
}

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


void CwmsbtMailMessage::BuildAllRecipients()
{
   m_qvlAllRecipients += m_qvlRecipients;
   m_qvlAllRecipients += m_qvlCopies;
   m_qvlAllRecipients += m_qvlBlindCopies;
}

QList<QString> CwmsbtMailMessage::GetAllRecipients()
{
   return m_qvlAllRecipients;
}

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

bool CwmsbtMailMessage::HasRecipients()
{
   bool bRet = false;

   if (m_qvlAllRecipients.count() > 0)
   {
      bRet = true;
   }

   return bRet;
}

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
