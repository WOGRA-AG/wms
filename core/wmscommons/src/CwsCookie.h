#ifndef CWSCOOKIE_H
#define CWSCOOKIE_H

// System and Qt Includes
#include <QString>
#include <QDate>

// Own inclcudes
#include "wmscommons.h"

class WMSCOMMONS_API CwsCookie
{
private:
    QString name;
    QString value;
    QDate expires;
    QString path;
    QString domain;
    int maxAge;
    bool secure;
    QString comment;
    QString commentUrl;
    QString port;
    QString version;

public:
    CwsCookie();
    virtual ~CwsCookie(){};
    QString getName() const;
    void setName(const QString &value);
    QString getValue() const;
    void setValue(const QString &p_value);
    QDate getExpires() const;
    void setExpires(const QDate &value);
    QString getPath() const;
    void setPath(const QString &value);
    QString getDomain() const;
    void setDomain(const QString &value);
    int getMaxAge() const;
    void setMaxAge(int value);
    bool getSecure() const;
    void setSecure(bool value);
    QString getComment() const;
    void setComment(const QString &value);
    QString getCommentUrl() const;
    void setCommentUrl(const QString &value);
    QString getPort() const;
    void setPort(const QString &value);
    QString getVersion() const;
    void setVersion(const QString &value);
    QString generateCookieString() const;
    void setPair(const QString &key, const QString &value);
};

#endif // CWSCOOKIE_H
