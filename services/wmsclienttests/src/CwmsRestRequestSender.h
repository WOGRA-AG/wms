#ifndef CWMSRESTREQUESTSENDER_H
#define CWMSRESTREQUESTSENDER_H

#include <QString>
#include <QRunnable>

class CwmsRestRequestSender : public QRunnable
{
    QString m_qstrUrl;
    QString m_qstrServer;
    int m_iPort;
public:
    CwmsRestRequestSender(QString p_qstrUrl, QString p_qstrServer, int p_iPort);
    void run();
};

#endif // CWMSRESTREQUESTSENDER_H
