#include "CwsCookie.h"

#define EXPIRES "expires"
#define PATH "path"
#define WMS_DOMAIN "domain"
#define MAX_AGE "max-age"
#define COMMENT "comment"
#define SECURE "secure"
#define VERSION "version"
#define COMMENT_URL "comment-url"
#define PORT "port"


CwsCookie::CwsCookie()
    : expires(QDate()),
      maxAge(0),
      secure(false)

{

}

QString CwsCookie::getName() const
{
    return name;
}

void CwsCookie::setName(const QString &value)
{
    name = value;
}

QString CwsCookie::getValue() const
{
    return value;
}

void CwsCookie::setValue(const QString &p_value)
{
    value = p_value;
}

QDate CwsCookie::getExpires() const
{
    return expires;
}

void CwsCookie::setExpires(const QDate &value)
{
    expires = value;
}

QString CwsCookie::getPath() const
{
    return path;
}

void CwsCookie::setPath(const QString &value)
{
    path = value;
}

QString CwsCookie::getDomain() const
{
    return domain;
}

void CwsCookie::setDomain(const QString &value)
{
    domain = value;
}

int CwsCookie::getMaxAge() const
{
    return maxAge;
}

void CwsCookie::setMaxAge(int value)
{
    maxAge = value;
}

bool CwsCookie::getSecure() const
{
    return secure;
}

void CwsCookie::setSecure(bool value)
{
    secure = value;
}

QString CwsCookie::getComment() const
{
    return comment;
}

void CwsCookie::setComment(const QString &value)
{
    comment = value;
}

QString CwsCookie::getCommentUrl() const
{
    return commentUrl;
}

void CwsCookie::setCommentUrl(const QString &value)
{
    commentUrl = value;
}

QString CwsCookie::getPort() const
{
    return port;
}

void CwsCookie::setPort(const QString &value)
{
    port = value;
}

QString CwsCookie::getVersion() const
{
    return version;
}

void CwsCookie::setVersion(const QString &value)
{
    version = value;
}

void CwsCookie::setPair(const QString &key, const QString &value)
{

    if (key.toLower() == EXPIRES)
    {
        setExpires(QDate::fromString(value));
    }
    else if (key.toLower() == MAX_AGE)
    {
        setMaxAge(value.toInt());
    }
    else if (key.toLower() == PATH)
    {
        setPath(value);
    }
    else if (key.toLower() == WMS_DOMAIN)
    {
        setDomain(value);
    }
    else if (key.toLower() == VERSION)
    {
        setVersion(value);
    }
    else if (key.toLower() == PORT)
    {
        setPort(value);
    }
    else if (key.toLower() == COMMENT)
    {
        setComment(value);
    }
    else if (key.toLower() == COMMENT_URL)
    {
        setCommentUrl(value);
    }
    else if (key.toLower() == SECURE)
    {
        setSecure(true);
    }
    else
    {
        setName(key);
        setValue(value);
    }
}

QString CwsCookie::generateCookieString() const
{
    QString qstrCookie;
    qstrCookie ="Set-Cookie: ";
    qstrCookie += name + "=" + value + "; ";

    if (expires.isValid())
    {
        qstrCookie += EXPIRES "=" + expires.toString() + "; ";
    }

    if (maxAge > 0)
    {
        qstrCookie += MAX_AGE "=" + QString::number(maxAge) + "; ";
    }

    if (!path.isEmpty())
    {
        qstrCookie += PATH "=" + path + "; ";
    }

    if (!domain.isEmpty())
    {
        qstrCookie += WMS_DOMAIN "=" + domain + "; ";
    }

    if (!version.isEmpty())
    {
        qstrCookie += VERSION "=" + version + "; ";
    }

    if (!port.isEmpty())
    {
        qstrCookie += PORT "=" + port + "; ";
    }

    if (!commentUrl.isEmpty())
    {
        qstrCookie += COMMENT_URL "=" + commentUrl + "; ";
    }

    if (!comment.isEmpty())
    {
        qstrCookie += COMMENT "=" + comment + "; ";
    }

    if (secure)
    {
        qstrCookie += SECURE ";";
    }

    return qstrCookie;
}


