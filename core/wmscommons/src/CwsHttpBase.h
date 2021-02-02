#ifndef CWSHTTPBASE_H
#define CWSHTTPBASE_H

// System and Qt Includes
#include <QMap>
#include <QDate>
#include <QObject>

// Own includes
#include "CwsCookie.h"
#include "wmscommons.h"


#define COOKIE "Cookie"
#define SET_COOKIE "Set-Cookie"

enum EwsHttpMethod
{
    eWsGet,
    eWsPut,
    eWsDelete,
    eWsPost,
    eWsTrace,
    eWsConnect,
    eWsOptions
};

class WMSCOMMONS_API CwsHttpBase : public QObject
{
    Q_OBJECT
private:
    int m_iHeaderLength;
    QString m_qstrBody;
    QString m_qstrAuthType;
    QString m_qstrAuthValue;



public slots:
    QString GetAuthType() const;
    QList<QString> GetHeaderNames() const;
    QString GetHeader(QString p_qstrKey) const;
    int GetIntHeader(QString p_qstrKey) const;
    int GetHeaderCount() const;
    QString GetBody() const;
    void AddHeader(QString p_qstrKey, QString p_qstrValue);
    void AddCookie(CwsCookie p_Cookie);
    void SetBody(QString p_qstrBody);
    int GetContentLength() const;
    int GetDocumentLength() const;
    void CopyContent(QByteArray &p_rResponse);
    void ParseContent();
    bool IsBodyEmpty();
    QString GetServer() const;
    void SetServer(QString p_qstrServer);

    QString GetAuthValue() const;
    void SetAuthValue(QString p_qstrAuthtype);
    void SetAuthType(QString p_qstrAuthtype);
protected:
    QList<CwsCookie> m_qlCookies;
    QMap<QString,QString> m_qmHeaderInformation;
    QByteArray m_qbaContent;
    QString m_qstrServer;

    CwsHttpBase();
    virtual ~CwsHttpBase();
    void AddHeadersToString(QString &p_qstrRequest);
    void ParseHeaderContent(QString p_qstrHeader);
    virtual void ParseCookies(QString p_qstrCookies) = 0;
    virtual void ParseHeadline(QString p_qstrCookies) = 0;

};

#endif // CWSHTTPBASE_H
