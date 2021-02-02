#ifndef CWMSSCRIPTABLEHTTPCLIENT_H
#define CWMSSCRIPTABLEHTTPCLIENT_H

#include <QScriptable>
#include <QObject>

#include "CwmsScriptableBase.h"
#include "basetools.h"

class CwsHttpClient;
class CwsHttpRequest;

class BASETOOLS_API CwmsScriptableHttpClient : public CwmsScriptableBase
{
    Q_OBJECT
public:
    CwmsScriptableHttpClient();
    virtual ~CwmsScriptableHttpClient();
public slots:
    QObject *createHttpClient();
    QObject *createHttpRequest();
    QObject *sendRequest(QObject* p_pClient, QObject* p_pRequest);
};

#endif // CWMSSCRIPTABLEHTTPCLIENT_H
