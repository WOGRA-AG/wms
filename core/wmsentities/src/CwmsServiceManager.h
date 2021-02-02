#ifndef CWMSSERVICEMANAGER_H
#define CWMSSERVICEMANAGER_H

// System and Qt Includes
#include <QMap>
#include <QObject>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// own Includes
#include "IwmsRunningService.h"
#include "basetools.h"

// Forwards
class QTimer;
class CdmClass;
class CdmPackage;
class CdmObject;
class CdmObjectContainer;

class BASETOOLS_API CwmsServiceManager : public QObject, CwmsSynchronizable
{
    Q_OBJECT
private:
    QString m_qstrServiceManagerId;
    QMap<QString, IwmsRunningService*> m_qmServices;
    QMap<QTimer*, QString> m_qmServiceTimers;

    void CreateDataStructure();
    bool CheckDataStructure();
    void ServiceCheck(IwmsRunningService *p_pService);
    void AddRunningServiceClassMembers(CdmClass *p_pClass);
    void CreateServiceManagerContainer(CdmClass *p_pClass);
    CdmPackage *FindOrCreateTechnicalPackage();
    void AddServiceInstanceClassMembers(CdmClass *p_pClass);
    void CreateServiceInstanceContainer(CdmClass *p_pClass);
    void CreateContainer(CdmClass *p_pClass, QString p_qstrKeyname);
    void DeleteTimer(QString p_qstrServiceId);
    bool ServiceCanStartCheck(IwmsRunningService *p_pService);
    void UpdateRunningData(IwmsRunningService *p_pService);

    void SignOffServiceManager();
    void RegisterServiceManager();
    CdmObject *GetServiceInstanceObject();
    int GetTimerIntervall(IwmsRunningService *p_pService);
    CdmObjectContainer *GetContainer(QString p_qstrKeyname);
    CdmObjectContainer *GetServiceManagerContainer();
    CdmObjectContainer *GetServiceInstanceContainer();

    void DeleteServices();
    void DeleteTimers();
public:
    CwmsServiceManager();
    virtual ~CwmsServiceManager();
    void AddService(IwmsRunningService* p_pService);
    void DeleteService(QString p_qstrServiceId);
    void DeleteAllServices();
private slots:
    void ServiceCheckSlot();
};

#endif // CWMSSERVICEMANAGER_H
