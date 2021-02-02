#ifndef CWMSCONTEXT_H
#define CWMSCONTEXT_H


// System and QT Includes
#include <QObject>

// own Includes
#include "basetools.h"
#include "CwmsApplication.h"
#include "CwmsPluginManager.h"

//Enumerations

enum EwmsApplicationContext
{
    eWmsApplicationContextServer,
    eWmsApplicationContextAdmin,
    eWmsApplicationContextApplication,
    eWmsApplicationContextCommandLineInterface
};

// forwards
class CdmObject;
class CwmsServiceManager;

// Singleton
class BASETOOLS_API CwmsContext : public QObject
{
    Q_OBJECT
     
    private:
    static CwmsContext* m_spContext;
    EwmsApplicationContext m_eContext;
    CdmObject* m_pApplicationObject;
    CwmsPluginManager* m_pPluginManager;
    bool m_bTimedOut;
    CwmsServiceManager* m_pServiceManager;
    void Init();
    CwmsContext(EwmsApplicationContext p_eContext);
    virtual ~CwmsContext();
public:
    static bool CreateContext(EwmsApplicationContext p_eContext);
    static bool CreateContext(CdmObject* p_pApplicationObject);
    static void DestroyContext();
    static CwmsContext *GetContext();
    bool IsTimedOut();

    CwmsServiceManager *GetServiceManager();
    bool ServerLogout();
    bool ServerLogin();
public slots:
    CwmsApplication GetApplication();
    EwmsApplicationContext GetContextType();
    CwmsPluginManager *GetPluginManager();

private slots:
    void SessionTimedOutSlot();

signals:
    void ApplicationShutdownSignal();
};

#endif // CWMSCONTEXT_H
