#ifndef CWMSSERVERSCHEMEMANAGER_H
#define CWMSSERVERSCHEMEMANAGER_H

// System and Qt Includes

// own Includes
#include "basetools.h"


#define APP_STORE_CLASS_NAME "App_Store"
#define APP_STORE_CONTAINER_NAME "Apps"
#define APP_STORE_VERSION 2


// forwards
class CdmClassManager;

class BASETOOLS_API CwmsServerSchemeManager
{
public:
    CwmsServerSchemeManager();
    void CheckServerScheme();
    virtual ~CwmsServerSchemeManager();
private:
    void CreatePluginsClass(CdmClassManager *p_pClassManager);
    void CheckPlugins();
    void CheckScheme();
    bool ExistServerScheme();
    void CheckAppStore();
    void CreateAppStore(CdmScheme *p_pScheme);
    CdmClass *CreateAppStoreClass(CdmClassManager *p_pClassManager);
    void CreateAppStoreContainer(CdmContainerManager *p_pContainerManager, CdmClass *p_pClass);
};

#endif // CWMSSERVERSCHEMEMANAGER_H
