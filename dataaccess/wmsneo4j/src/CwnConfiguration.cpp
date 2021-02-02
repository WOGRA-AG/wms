

#include "CwnConfiguration.h"

CwnConfiguration::CwnConfiguration()
{
    SetServer("127.0.0.1");
    SetPort(7474);
    SetUsername("neo4j");
    SetPassword("1qay2wsx");
}

CwnConfiguration::~CwnConfiguration()
{

}

QString CwnConfiguration::GetServer()
{
    return m_server;
}

int CwnConfiguration::GetPort()
{
    return m_port;
}

QString CwnConfiguration::GetUsername()
{
    return m_username;
}

QString CwnConfiguration::GetPassword()
{
    QByteArray ba;
    ba.append(m_username+":"+m_password);
    return ba.toBase64();
}

void CwnConfiguration::SetServer(QString server)
{
    this->m_server = server;
}

void CwnConfiguration::SetPort(int port)
{
    this->m_port = port;
}

void CwnConfiguration::SetUsername(QString username)
{
    this->m_username = username;
}

void CwnConfiguration::SetPassword(QString password)
{
    this->m_password = password;
}


