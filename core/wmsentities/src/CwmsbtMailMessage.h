/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtMailMessage.h
 ** Started Implementation: 2010/01/09
 ** Description:
 ** 
 ** Implements the Class for defining a message
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CwmsbtMailMessage_H
#define CwmsbtMailMessage_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QList>
#include <QString>
#include <QObject>
#include <QDataStream>

// Own Includes
#include "IwmsbtSmtpConfiguration.h"
#include "basetools.h"


// Forwards
class CwmsbtSmtpClient;

// Enumerations

/* 
 * This class implements the Class for defining a message
 */
class BASETOOLS_API CwmsbtMailMessage : public QObject
{
   Q_OBJECT
 
   private:
      QList<QPair<QString,QString>> m_qlAttachments;
      QList<QString> m_qvlRecipients;
      QList<QString> m_qvlCopies;
      QList<QString> m_qvlBlindCopies;
      QList<QString> m_qvlAllRecipients;
      CwmsbtSmtpClient*       m_pCslSmtpClient;
      IwmsbtSmtpConfiguration* m_pIslSmtpConfiguration;
      QString              m_qstrBody;
      QString              m_qstrSubject;
      QString              m_qstrSender;
      bool m_bMessageSent;
      bool m_bSuccess;

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:39:25 2010--------*
    * @method  CwmsbtMailMessage::CwmsbtMailMessage                // public                            *
    * @return                                                //                                   *
    * @param   IwmsbtSmtpConfiguration* p_cCslSmtpConfiguration//                                    *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:39:25 2010-----------*/
    CwmsbtMailMessage( IwmsbtSmtpConfiguration* p_cCslSmtpConfiguration);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 10:55:33 2010--------*
    * @method  CwmsbtMailMessage::~CwmsbtMailMessage               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsbtMailMessage                                             *
    *----------------last changed: -----------------------------Sa 9. Jan 10:55:33 2010-----------*/
    virtual ~CwmsbtMailMessage( );

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:08 2012-------*
    * @method  CwmsbtMailMessage::AddRecipients              // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString& p_qstrRecipient                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:08 2012----------*/
void AddRecipients( QString& p_qstrRecipient);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:14 2012-------*
    * @method  CwmsbtMailMessage::AddCopy                    // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCopy                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:14 2012----------*/
void AddCopy( QString p_qstrCopy);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:21 2012-------*
    * @method  CwmsbtMailMessage::AddBlindCopy               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrBlindCopy                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:21 2012----------*/
void AddBlindCopy( QString p_qstrBlindCopy);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:36:20 2010--------*
    * @method  CwmsbtMailMessage::CreateMessage                 // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:36:20 2010-----------*/
    QString CreateMessage();

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:28 2012-------*
    * @method  CwmsbtMailMessage::SetSubject                 // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrSubject                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:28 2012----------*/
void SetSubject( QString p_qstrSubject);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:42 2012-------*
    * @method  CwmsbtMailMessage::SetBody                    // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrBody                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:42 2012----------*/
void SetBody( QString p_qstrBody);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:09:54 2012-------*
    * @method  CwmsbtMailMessage::SendMessage                // public, slots                     *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:09:54 2012----------*/
bool SendMessage( );

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 16:00:27 2010--------*
    * @method  CwmsbtMailMessage::CreateHead                    // private                           *
    * @return  QString                                       //                                   *
    * @param   bool p_bAddBCC = false                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 16:00:27 2010-----------*/
    QString CreateHead(bool p_bAddBCC = false);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:01:31 2010--------*
    * @method  CwmsbtMailMessage::GetRecipientsAsString         // private                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:01:31 2010-----------*/
    QString GetRecipientsAsString();

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:06:00 2010--------*
    * @method  CwmsbtMailMessage::GetMailAddressesAsString      // private                           *
    * @return  QString                                       //                                   *
    * @param   QList<QString>& p_rqllAddresses         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:06:00 2010-----------*/
    QString GetMailAddressesAsString(QList<QString>& p_rqllAddresses);

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:07:35 2010--------*
    * @method  CwmsbtMailMessage::GetCopiesAsString             // private                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:07:35 2010-----------*/
    QString GetCopiesAsString();

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:08:59 2010--------*
    * @method  CwmsbtMailMessage::GetBlindCopiesAsString        // private                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:08:59 2010-----------*/
    QString GetBlindCopiesAsString();


   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:15:47 2010--------*
    * @method  CwmsbtMailMessage::CheckMail                     // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:15:47 2010-----------*/
    bool CheckMail();

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 11:30:18 2010--------*
    * @method  CwmsbtMailMessage::HasRecipients                 // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 11:30:18 2010-----------*/
    bool HasRecipients();

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 12:14:56 2010--------*
    * @method  CwmsbtMailMessage::GetMailSize                   // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 12:14:56 2010-----------*/
    int GetMailSize();

   private:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:40:36 2010--------*
    * @method  CwmsbtMailMessage::GetMailAddressesAsStringList  // private                           *
    * @return  QStringList                                   //                                   *
    * @param   QString p_qstrPreString                       //                                   *
    * @param   QList<QString>& p_rqllAddresses         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:40:36 2010-----------*/
    QStringList GetMailAddressesAsStringList(QString p_qstrPreString,
                                             QList<QString>& p_rqllAddresses);

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:41:58 2010--------*
    * @method  CwmsbtMailMessage::GetRecipientsAsStringList     // public                            *
    * @return  QStringList                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:41:58 2010-----------*/
    QStringList GetRecipientsAsStringList();

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:35 2012-------*
    * @method  CwmsbtMailMessage::GetSubject                 // public, slots                     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:35 2012----------*/
QString GetSubject( );

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 15:08:48 2012-------*
    * @method  CwmsbtMailMessage::GetBody                    // public, slots                     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 15:08:48 2012----------*/
QString GetBody( );

   public:
   /** +-=---------------------------------------------------------Sa 9. Jan 14:54:10 2010--------*
    * @method  CwmsbtMailMessage::GetRecipients                 // public                            *
    * @return  QList<QString>&                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Jan 14:54:10 2010-----------*/
    QList<QString>& GetRecipients();

   public:
   /** +-=---------------------------------------------------------So 10. Jan 13:06:31 2010-------*
    * @method  CwmsbtMailMessage::ToRfc2822                     // public                            *
    * @return  void                                          //                                   *
    * @param   QDataStream& p_qdsOut                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:06:31 2010----------*/
    void ToRfc2822(QDataStream& p_qdsOut);

   private:
   /** +-=---------------------------------------------------------So 10. Jan 11:47:36 2010-------*
    * @method  CwmsbtMailMessage::BuildAllRecipients            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 11:47:36 2010----------*/
    void BuildAllRecipients();

   public:
   /** +-=---------------------------------------------------------So 10. Jan 11:48:08 2010-------*
    * @method  CwmsbtMailMessage::GetAllRecipients              // public                            *
    * @return  QList<QString>                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 11:48:08 2010----------*/
    QList<QString> GetAllRecipients();

    private slots:
   /** +-=---------------------------------------------------------So 10. Jan 13:26:55 2010-------*
    * @method  CwmsbtMailMessage::MessageTransmittedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @param   bool p_bSuccess                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Jan 13:26:55 2010----------*/
void MessageTransmittedSlot( bool p_bSuccess);

   private:
   /** +-=---------------------------------------------------------Do 4. Okt 14:33:27 2012--------*
    * @method  CwmsbtMailMessage::ExtractDayOfWeek              // private                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 4. Okt 14:33:27 2012-----------*/
    QString ExtractDayOfWeek();

   private:
   /** +-=---------------------------------------------------------Do 4. Okt 14:36:26 2012--------*
    * @method  CwmsbtMailMessage::ExtractMonthOfYear            // private                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 4. Okt 14:36:26 2012-----------*/
    QString ExtractMonthOfYear();
    
    bool WaitForMessageSent(qint64 p_iTimeout = 5000);

    QByteArray encodeQuotedPrintable(const QString &input);
public:
    void AddAttachment(QString p_qstrFilename);
    void AddAttachment(QString p_qstrFilename, QString p_qstrBase64Data);

    QString RetrieveSender();

public:
    IwmsbtSmtpConfiguration* getSmtpConfigurations();
    void SetSender(QString qstrSender);
    void AddRecipients(QStringList &p_qstrRecipient);
    void AddRecipients(QList<QString> &p_qstrRecipient);
};

#endif //
