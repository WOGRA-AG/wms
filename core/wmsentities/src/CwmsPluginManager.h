#ifndef CWMSPLUGINMANAGER_H
#define CWMSPLUGINMANAGER_H

// System and QT includes
#include <QObject>
#include <QFileInfo>

// own Includes
#include "basetools.h"

// forwards
class CdmObjectContainer;
class CdmClassManager;
class IwmsPrintingPlugin;
class CdmExecutorAddOnManager;
class CdmObject;
class QMainWindow;
class CdmPackage;

// enumerations

enum EwmsPluginType
{
    eWmsPluginTypeFunction,
    eWmsPluginTypeServer,
    eWmsPluginTypePrinting,
    eWmsPluginTypeUserInterface
};

#define PLUGIN_PACKAGE "plugins"

class BASETOOLS_API CwmsPluginManager// : public QObject
{
   public:
      CwmsPluginManager();
      virtual ~CwmsPluginManager();
      bool HasPrintingPlugin();
      void LoadPrintingPlugin(QString p_qstrFileName);
      void RemovePrintingPlugin();
      IwmsPrintingPlugin* GetPrintingPlugin();
      void InstallFunctionPlugins(QMainWindow* p_pMainWindow);
      CdmObjectContainer* GetPluginContainer();
      void RefreshPlugins(QMainWindow* p_pMainWindow = NULL);
      void RemoveFunctionPlugin(QString p_qstrPlugin);
      void LoadFunctionPlugin(QString qstrPluginFilename, QMainWindow* p_pMainWindow);

      void LoadServerPlugins();
      void InstallFunctionPlugins(CdmObjectContainer* pContainer, QMainWindow* p_pMainWindow);
      CdmObjectContainer *GetServerPluginContainer();

      void LoadInstalledPrintingPlugins();
      void LoadInstalledFunctionsPlugins();
      static CdmPackage *FindOrCreatePluginPackage();
private:
      bool CheckDataStructure();
      void CreateDataStructure();
      void CreatePluginsClass(CdmClassManager* p_pClassManager);
      void CreateContainer();
      void CreateServerScheme();
      void LoadPrintingPlugin();
      void InstallServerFunctionPlugins();
      void InstallFunctionPlugins(QStringList &p_qstrlFunctions, QMainWindow* p_pMainWindow);
      CdmExecutorAddOnManager *GetAddOnManager();
      void AddPrintingPlugin(CdmObjectContainer *p_pContainer, QFileInfo qfInfo);
      CdmObject* FindPluginConfiguration(CdmObjectContainer* p_pContainer, QString p_qstrPluginName, QString p_qstrVersion, EwmsPluginType p_Type, QString p_qstrFilename);
      void AddFunctionPlugin(CdmObjectContainer* p_pContainer, QFileInfo& qfInfo);
};

#endif
