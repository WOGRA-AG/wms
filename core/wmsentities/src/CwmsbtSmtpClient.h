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
    CwmsbtSmtpClient( IwmsbtSmtpConfiguration* p_pIslConfig, CwmsbtMailMessage* p_pCwmsbtMailMessage);
    virtual ~CwmsbtSmtpClient( );
    void SendMail();

private slots:
    void ReadyReadSlot();
    void ConnectedSlot(QMailTransport::EncryptType p_eEncryptType);
    void SentSlot(qint64 p_iSent);
    void TransportErrorSlot( int p_iErrorCode, QString p_qstrErrorMessage);

private:
    void IncomingData();
    void InitAction(uint p_uiResponseCode, QString p_qstrResponse);
    void SendCommand(const char *data, int p_iLength);
    void SendCommand(const QString& p_qtrCommand);
    void SendCommand(const QByteArray & p_rComand);
    void SendCommands(const QStringList& p_rqstrlCommands);
    void HeloAction(uint p_uiResponseCode, QString p_qstrResponse);
    void ExtractDomainName(QString p_qstrResponse);
    void ExtensionAction(uint p_uiResponseCode, QString p_qstrResponse);
    void StartTlsAction(uint p_uiResponseCode, QString p_qstrResponse);
    void TlsAction(uint p_uiResponseCode, QString p_qstrResponse);
    void ConnectedAction(uint p_uiResponseCode, QString p_qstrResponse);
    void AuthenticatingAction(uint p_uiResponseCode, QString p_qstrResponse);
    void AuthenticatedAction(uint p_uiResponseCode, QString p_qstrResponse);
    void MetaDataAction(uint p_uiResponseCode, QString p_qstrResponse);
    void FromAction(uint p_uiResponseCode, QString p_qstrResponse);
    void RcvAction(uint p_uiResponseCode, QString p_qstrResponse);
    void MRcvAction(uint p_uiResponseCode, QString p_qstrResponse);
    void PrepareDataAction();
    void BodyAction(uint p_uiResponseCode, QString p_qstrResponse);
    void ChunkAction(uint p_uiResponseCode);
    void SentAction(uint p_uiResponseCode, QString p_qstrResponse);
    void QuitAction(uint p_uiResponseCode);
    void NextAction(const QString p_qstrResponse);


signals:
    void MessageTransmittedSignal( bool p_bSuccess);
    void UpdateStatusSignal(QString p_qstrStatus);
    void ProgressChangedSignal( int p_iSentSize, int p_iCompleteSize);
};

#endif //
