#include "CwsHttpClient.h"
#include "CwsHttpRequest.h"
#include "CwsHttpResponse.h"

#include "CwnCommandBase.h"
#include "CwnConfiguration.h"
#include "CwnDataAccessConfigurator.h"

#include <CdmSessionManager.h>
#include <CdmLogging.h>

#include <QByteArray>
#include <QTime>

CwnCommandBase::CwnCommandBase(CwnDataAccess* m_rpDataAccess)
    : m_rpDataAccess(m_rpDataAccess)
{

}

CwnCommandBase::~CwnCommandBase()
{
    // nothing to do at the moment
}

bool CwnCommandBase::CheckSession()
{
    bool bRet = false;

    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        if (pSessionManager->GetCurrentSessionId() > 0)
        {
            bRet = true;
        }
    }

    return bRet;
}

qint64 CwnCommandBase::Run()
{
   qint64 lRet = 0;

    //CreateUser needs to pass
    //if (Validate())
    if(/* DISABLES CODE */ (true))
    {
        lRet = Execute();
    }
    else
    {
        lRet = CdmLogging::eDmPreconditionCheckFailed;
    }

    return lRet;
}

bool CwnCommandBase::Validate()
{
    return (CheckSession());
}

void CwnCommandBase::ConnectAndExecute(int role, QString payload, QString location, QString startNode)
{
    CwsHttpRequest cws_request;

    // Time for building your request
    QByteArray qb_payload = payload.toUtf8();
    int iContentLength = qb_payload.size();
    QTime t;

    switch (role)
    {
        case executeCommit:
            //ERR("------------------START TO TRANSFER PAYLOAD------------------");
            //t.start();
            //ERR(payload);
            cws_request.SetMethod(eWsPost);
            cws_request.SetHttpVersion("1.0");
            cws_request.SetUrl("/db/data/transaction/commit");
            break;
        case traverseDepthSearchFullPath:
            //ERR("------------------START TO TRANSFER PAYLOAD------------------");
            //t.start();
            //ERR(payload);
            cws_request.SetMethod(eWsPost);
            cws_request.SetHttpVersion("1.0");
            cws_request.SetUrl(QString("/db/data/node/%1/traverse/fullpath").arg(startNode));
           break;
        case openTransaction:
            //ERR("------------------START TO TRANSFER PAYLOAD------------------");
            //t.start();
            //ERR(payload);
            cws_request.SetMethod(eWsPost);
            cws_request.SetHttpVersion("1.0");
            cws_request.SetUrl("/db/data/transaction");
           break;
        case rollbackTransaction:
            cws_request.SetMethod(eWsDelete);
            cws_request.SetHttpVersion("1.0");
            cws_request.SetUrl(QString("%1").arg(location));
            break;
        case commitTransaction:
            cws_request.SetMethod(eWsPost);
            cws_request.SetHttpVersion("1.0");
            cws_request.SetUrl(QString("%1/commit").arg(location));
            break;
        default:
            break;
    }

    QByteArray ba;
    QString authorization;
    int port;
    QString server;

    ba.append(m_rpDataAccess->GetConfig()->getUser()+":"+m_rpDataAccess->GetConfig()->getPassword());
    authorization = ba.toBase64();

    port = m_rpDataAccess->GetConfig()->getPort();
    server = m_rpDataAccess->GetConfig()->getServer();


    cws_request.AddHeader("Accept","application/json; charset=UTF-8");
    cws_request.AddHeader("Authorization",QString("Basic %1").arg(authorization));
    cws_request.AddHeader("Content-Type","application/json");
    cws_request.AddHeader("Content-Length",QString("%1").arg(QString::number(iContentLength)));

    cws_request.SetServer(server);

    cws_request.SetBody(payload.toUtf8());

    CwsHttpClient client;
    client.SetPort(port);
    client.SetHostAddress(server);

    CwsHttpResponse cws_response;
    client.sendRequest(cws_request,cws_response);

    int begin=0;
    int end=0;
    QString header;

    switch (role)
    {
        case executeCommit:
        case traverseDepthSearchFullPath:
            this->answer.append(cws_response.GetBody());
            //ERR(QString("%1 ms").arg(t.elapsed()));
            //ERR("------------------QUERY EXECUTED------------------\n\n");
            break;
        case openTransaction:
            header = cws_response.GetHeader("Location");
            begin = header.indexOf("/db");
            end = header.indexOf("\n")-2;

            //qDebug() << header.mid(begin,(end-begin));
            this->location = header.mid(begin,(end-begin));
            this->answer.append(cws_response.GetBody());
            break;
        case rollbackTransaction:
            //ERR(QString("%1 ms").arg(t.elapsed()));
            //ERR("------------------QUERY EXECUTED------------------\n\n");
            break;
        case commitTransaction:
            //ERR(QString("%1 ms").arg(t.elapsed()));
            //ERR("------------------QUERY EXECUTED------------------\n\n");
            break;
    }

}

QString CwnCommandBase::createJson(QString p_qstrQuery)
{
    return QString("{\"statements\" : [ {\"statement\" : \"%1\" }]}\r\n").arg(p_qstrQuery);
}

QString CwnCommandBase::startJsonWCommand(QString p_qstrQuery)
{
    return QString("{\"statements\" : [{\"statement\" : \"%1\"}").arg(p_qstrQuery);
}

QString CwnCommandBase::addJsonCommand(QString p_qstrQuery)
{
    return QString(",{\"statement\" : \"%1\"}").arg(p_qstrQuery);
}

QString CwnCommandBase::endJsonCommand()
{
    return QString("]}\r\n");
}

const QVariantList* CwnCommandBase::getErrorsList()
{
    const QVariantList* errors = static_cast<const QVariantList*>(qResult->find("errors")->data());
    return errors;
}

bool CwnCommandBase::checkForErrors(const QVariantMap* qresult, QString& queryCausedError)
{
    if(CHKPTR(qresult))
    {
        if(hasErrors())
        {
            const QVariantList* qvlErrors = getErrorsList();
            const QVariantMap* errormap = static_cast<const QVariantMap*>(qvlErrors->at(0).data());

            ERR(errormap->find("code")->toString());
            ERR(errormap->find("message")->toString());
            ERR(queryCausedError);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        ERR(queryCausedError);
        ERR("Answer from Server was not legit.");
        return true;
    }
}

bool CwnCommandBase::hasErrors()
{
    return (getErrorsList()->count() > 0);
}

const QVariantList* CwnCommandBase::getDataListPtr()
{
    const QVariantList* results = static_cast<const QVariantList*>(qResult->find("results")->data());
    const QVariantMap* data = static_cast<const QVariantMap*>(results->at(0).data());
    return static_cast<const QVariantList*>(data->find("data")->data());
}


CwnDataAccess* CwnCommandBase::GetDataAccess()
{
    return m_rpDataAccess;
}


