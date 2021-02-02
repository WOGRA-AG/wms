#ifndef CWSHTTPRESPONSE_H
#define CWSHTTPRESPONSE_H

#include "CwsHttpBase.h"
#include "wmscommons.h"
#include "CwmsHttpService.h"

class WMSCOMMONS_API CwsHttpResponse : public CwsHttpBase
{
    Q_OBJECT
private:

    EwmsHttpStatusCode m_eStatusCode;
    QString m_qstrContentType;
    QString m_qstrAllowOrigin;
    QString m_qstrConnectionMode;


    void GenerateHeadLine(QString &p_qstrRequest);
    void AddCookiesToString(QString &p_qstrRequest);
    void BuildResponse();
    void ParseHeadline(QString p_qstrRequest);
public:
    CwsHttpResponse();
    QByteArray GenerateResponse();

public slots:
    void SetStatusCode(EwmsHttpStatusCode p_eStatusCode);
    EwmsHttpStatusCode GetStatusCode();
    void SetContentType(QString p_qstrType);
    QString GetContentType();
    QString GetAllowOrigin();
    void SetAllowOrigin(QString p_qstrOrigin);

    QString GetConnectionMode();
    void SetConnectionMode(QString p_qstrConnectionMode);
    int GetStatusCodeValue();

protected:
    virtual void ParseCookies(QString p_qstrCookies);
};

#endif // CWSHTTPRESPONSE_H
