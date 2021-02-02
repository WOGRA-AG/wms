/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwsRequestSocket.h
 ** Started Implementation: 2012/04/02
 ** Description:
 **
 ** IMplements the threaded request socket for handling request.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWSHTTPREQUEST_H
#define CWSHTTPREQUEST_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// Own Includes
#include "CwsHttpBase.h"
#include "CwsHttpResponse.h"
#include "wmscommons.h"

// Forwards
class IwmsHttpRequestHandler;

// TypeDefs

// Defines
#define BASIC_AUTH "BASIC"
#define FORM_AUTH "FORM"
#define CLIENT_CERT_AUTH "CLIENT_CERT"
#define DIGEST_AUTH "DIGEST"
#define HTTP_GET "GET"
#define HTTP_PUT "PUT"
#define HTTP_DELETE "DELETE"
#define HTTP_POST "POST"
#define HTTP_TRACE "TRACE"
#define HTTP_CONNECT "CONNECT"
#define HTTP_OPTIONS "OPTIONS"

/* 
 * This class implements the threaded request socket for handling request.
 */
class WMSCOMMONS_API CwsHttpRequest : public CwsHttpBase
{
    Q_OBJECT

private:
    EwsHttpMethod m_wsMethod;

    QString m_qstrUrl;
    QString m_qstrVersion;
    QMap<QString,QString> m_qmPathVariables;

    void AddCookiesToString(QString &p_qstrRequest);
    void ParseParameter(QString p_qstrParams);
    EwsHttpMethod GetMethodFromString(QString p_qstrMethod) const;

    QString GenerateParameterListString();

    QString GetHost() const;
public:
    CwsHttpRequest();
    virtual ~CwsHttpRequest();
    QString GenerateRequestString();
    QString GetHttpVersion() const;
    QString GetProtocol() const;
    void SetMethod(EwsHttpMethod p_eMthod);
    bool IsSSLRequest() const;

    QMap<QString, QString> &GetPathVariableMap();
public slots:
    EwsHttpMethod GetMethod() const;
    QString GetMethodAsString() const;
    bool HasPathVariable(QString p_qstrKey) const;
    QString GetPathInfo() const;
    QString GetPathVariable(QString p_qstrKey) const;
    QString GetContextPath() const;
    void AddPathVariable(QString p_qstrKey, QString p_qstrValue);
    void SetUrl(QString p_qstrUrl);

    void SetHttpVersion(QString p_qstrVersion);

    void SetMethod(QString p_qstrMethod);
    int GetPathVariableCount() const;
    QStringList GetPathVariableNames() const;
protected:
    virtual void ParseCookies(QString p_qstrCookies);
    virtual void ParseHeadline(QString p_qstrRequest);


};

#endif // CWSHTTPREQUEST_H
