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
    CwmsbtMailMessage(IwmsbtSmtpConfiguration* p_cCslSmtpConfiguration);
    void AddAttachment(QString p_qstrFilename);
    void AddAttachment(QString p_qstrFilename, QString p_qstrBase64Data);
    QString RetrieveSender();
    IwmsbtSmtpConfiguration* getSmtpConfigurations();
    void SetSender(QString qstrSender);
    void AddRecipients(QStringList &p_qstrRecipient);
    void AddRecipients(QList<QString> &p_qstrRecipient);
    virtual ~CwmsbtMailMessage( );
    QString CreateMessage();
    QList<QString>& GetRecipients();
    void ToRfc2822(QDataStream& p_qdsOut);
    QList<QString> GetAllRecipients();
    int GetMailSize();
    QStringList GetRecipientsAsStringList();

public slots:
    void AddRecipients( QString& p_qstrRecipient);
    void AddCopy( QString p_qstrCopy);
    void AddBlindCopy( QString p_qstrBlindCopy);
    void SetSubject( QString p_qstrSubject);
    void SetBody( QString p_qstrBody);
    bool SendMessage();
    QString GetSubject();
    QString GetBody();

private:
    QStringList GetMailAddressesAsStringList(QString p_qstrPreString,
                                             QList<QString>& p_rqllAddresses);
    QString ExtractDayOfWeek();
    QString ExtractMonthOfYear();
    bool WaitForMessageSent(qint64 p_iTimeout = 5000);
    QByteArray encodeQuotedPrintable(const QString &input);
    QString CreateHead(bool p_bAddBCC = false);
    QString GetRecipientsAsString();
    QString GetMailAddressesAsString(QList<QString>& p_rqllAddresses);
    QString GetCopiesAsString();
    QString GetBlindCopiesAsString();
    bool CheckMail();
    bool HasRecipients();
    void BuildAllRecipients();

private slots:
    void MessageTransmittedSlot(bool p_bSuccess);
};

#endif
