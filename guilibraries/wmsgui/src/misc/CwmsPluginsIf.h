#ifndef CWMSPLUGINSIF_H
#define CWMSPLUGINSIF_H


// System and QT Includes
#include <QWidget>
#include <QFileInfo>

// Basetools includes
#include "CwmsApplication.h"
#include "CwmsPluginManager.h"

// own Includes
#include "wmsgui.h"
#include "ui_CwmsPluginManagerIf.h"

// forwards
class CdmObject;
class CdmObjectContainer;
class IwmsPrintingPlugin;
class IwmsWebService;

class WMSGUI_API CwmsPluginsIf : public QWidget, public Ui::CwmsPluginManagerIf
{
    Q_OBJECT

    private:
      QStringList m_qstrlFoundUris;

public:
    CwmsPluginsIf(QWidget* parent = NULL);
    virtual ~CwmsPluginsIf();
    void FillWidgetApplication(CwmsApplication p_App);
    void FillWidgetServer(CdmObjectContainer *p_pContainer);
    void FillWidgetAdmin(CdmObjectContainer* p_pContainer);

private slots:
    void ItemChangedSlot(QTreeWidgetItem *p_pItem, int p_iColumn);
private:
    void FillFunctionsPlugins(CdmObjectContainer *p_pContainer);
    void FillServerPlugins(CdmObjectContainer *p_pContainer);
    void FillPrintingPlugins(CdmObjectContainer *p_pContainer);
    void FillUserInterfacePlugins(CdmObjectContainer *p_pContainer);
    CdmObject *FindPluginConfiguration(CdmObjectContainer *p_pContainer, QString p_qstrPluginName, QString p_qstrVersion, EwmsPluginType p_Type, QString p_qstrFilename);
    void FillCommonPlugins(CdmObjectContainer* pContainer);
    void SetConfigurationData(CdmObject* pConfiguration, QTreeWidgetItem* pItem);
    void AddPlugintoView(CdmObject* pConfiguration, QStringList qstrlFunctions, QTreeWidgetItem* pFunctionRoot, bool p_bExists = true);
    void AddFunctionPlugin(CdmObjectContainer* p_pContainer, QFileInfo& qfInfo, QList<QString>& qlLoadedPlugins, QTreeWidgetItem* pFunctionRoot);
    void AddUiPlugin(CdmObjectContainer *p_pContainer, QFileInfo &qfInfo, QList<QString> &qlLoadedPlugins, QTreeWidgetItem *pFunctionRoot);
    void AddPrintingPlugin(CdmObjectContainer* p_pContainer, QTreeWidgetItem* pPrintingRoot, QFileInfo qfInfo);
    void AddPrintingPluginToView(QTreeWidgetItem* pPrintingRoot, QString qstrFile, IwmsPrintingPlugin* pPrintingPlugin, CdmObjectContainer* p_pContainer);
    void AddConnections();
    void AddServerPluginToView(QTreeWidgetItem *pServerRoot, QString qstrFile, IwmsWebService *pServerPlugin, CdmObjectContainer *p_pContainer);
    void AddServerPlugin(CdmObjectContainer *p_pContainer, QTreeWidgetItem *pServerRoot, QFileInfo qfInfo);
    void UpdatePluginState(CdmObject *p_pObject);
    void ActivatePlugin(CdmObject *p_pObject);
    void DeactivatePlugin(CdmObject *p_pObject);
    void FillNotExistingPlugins(CdmObjectContainer* p_pContainer, EwmsPluginType p_Type, QTreeWidgetItem* p_pParent);

};

#endif // CWMSPLUGINSIF_H

