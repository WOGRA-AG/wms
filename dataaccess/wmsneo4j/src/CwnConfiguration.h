

#ifndef CWNCONFIGURATION_H
#define CWNCONFIGURATION_H

#include <QString>

class CwnConfiguration
{

public:
    CwnConfiguration();
    virtual ~CwnConfiguration();

    QString GetServer();
    void SetServer(QString server);

    int GetPort();
    void SetPort(int port);

    QString GetUsername();
    void SetUsername(QString username);

    QString GetPassword();
    void SetPassword(QString password);

private:
    QString m_server;
    int m_port;
    QString m_username;
    QString m_password;

};

#endif // CWNCONFIGURATION_H

