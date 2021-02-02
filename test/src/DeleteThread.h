#ifndef DELETETHREAD_H
#define DELETETHREAD_H

#include <QObject>
#include <QString>
#include <QThread>

class CdmContainerManager;
class CdmScheme;

class DeleteThread : public QThread
{
    Q_OBJECT
private:
    QString m_qstrSchemeName;
    long m_lContainerId;
    long m_lObjectId;

    void run();
    void Setup();
    void Cleanup();

public:
    DeleteThread(QString p_qstrSchemeName, long p_lContainerId, long p_lObjectId);

    void DeleteObjectInContainer();
protected:
    CdmContainerManager* GetContainerManager();
    CdmScheme* GetScheme(QString p_qstrSchemeName);
};

#endif // DELETETHREAD_H
