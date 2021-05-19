#ifndef CWMSOBJECTLISTEDITORWIDGETIF_H
#define CWMSOBJECTLISTEDITORWIDGETIF_H


// System and QT Includes
#include <QDialog>
#include <qmap.h>
#include <qpair.h>

// WMS Includes
#include "CdmQueryModel.h"

// own Includes
#include "CwmsApplicationModule.h"
#include "CwmsFormStandardObjectList.h"
#include "CwmsView.h"
#include "wmsgui.h"
#include "CwmsObjectListEditorBase.h"
#include "ui_CwmsObjectListEditorWidget.h"
#include "IdmEventStoreManager.h"
#include "CwmsEventClassEditor.h"

// forwards
class CwmsRuntime;
class CwmsguiValidator;
class CdmObjectContainer;
class QTreeWidgetItem;
class QMenu;
class QToolBar;
class CwmsEventClassEditor;
typedef QPair<QString,QString> StringPair;

class WMSGUI_API CwmsObjectListEditorWidgetIf : public QWidget, public Ui::CwmsObjectListEditorWidget, public CwmsContainerEditorBase
{
    Q_OBJECT

private:
    CdmObject* m_rpCdmPrintingTemplate;
    EwmsLvObjectInUseHandling m_eWmsLvObjectInUseHandling;
    CdmObject* m_rpCdmObjectSelected;
    QAbstractItemModel* m_pModel;
    QString m_qstrWQL;

    QMap<QPushButton*, QString> m_qmFunctionMapping;
    QMenu* m_pMenu;
    QToolBar* m_pToolBar;
    QMap<QString, StringPair> m_qmDefaultValuesNewObject;
    QStringList m_qstrlContextMenuItems;
    QList<QString> m_qllSearchMembers;
    QStringList m_qstrlFunctions;
    QString m_qstrObjectEventMode;
    class::CwmsEventClassEditor *m_pEventClassEditor;


public:
    CwmsObjectListEditorWidgetIf( QWidget* parent = NULL);
    CwmsObjectListEditorWidgetIf( CdmObjectContainer* p_pContainer, QWidget* parent = NULL);
    virtual ~CwmsObjectListEditorWidgetIf(  );
    void SetContainer(  CdmObjectContainer* p_pContainer );
    void AddColumn(  QString p_qstrColumn );
    void FillDialog(  );
    void ClearColumns(  );
    void SetModel(CdmQueryModel* p_pModel);
    void SetNewAndDeleteButtonVisibily(bool p_bVisible);
    void UnsetProxy();
    virtual void clear();
    void SetDefaultValueForNewObject(QString p_qstrValueName,
                                     QString p_qstrValue,
                                     QString p_qstrValue2);
    void Refresh();
    QTreeView* GetListView();
    void ClearMenu();
    void AddPopupItem(QString p_qstrItem);
    void setSelected(CdmObject* pCdmObject);
    CdmObjectContainer* GetContainer();
    void SetView(CwmsView p_cCwmsView);
    void SetQuery(QString p_qstrWQL);
    void SetObjectInUseHandling(EwmsLvObjectInUseHandling p_eWmsLvObjectInUseHandling);
    void ConnectRuntime(CwmsRuntime* p_pCwmsRuntime, CwmsApplicationModule p_cModule);
    void SetFormBase(CwmsFormContainer p_cForm);
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);
    void SetFormStandard(CwmsFormStandardContainer p_cForm);
    void SetReadOnly(bool p_bReadOnly);
    void SetFormConfiguration(CdmObject* p_pCdmObejct);
    void ExecuteQuery(QString p_qstrQuery);
    void HideSearchButton();
    void HidePrintButton();
    void HideJournalButton();
    void HideExportButton();
    void HideImportButton();
    void AddDisplayHeader(QString p_qstrColumn, QString p_qstrHeader);
    void HideRefreshButton();
    void HideCopyButton();
    void HideSaveAsCsvButton();

public slots:
    virtual void NewClickedSlot( );
    virtual void DeleteClicekdSlot( );
    void EditClickedSlot( );
    void RefreshClickedSlot();
    void CopyObjectClickedSlot();
    void SaveAsCsvClickedSlot();
    void MetaDataClickedSlot();


    void HideNewButton();
    void HideDeleteButton();
private slots:
    void PrintClickedSlot( );
    void JournalClickedSlot( );
    void CustomContextMenuSlot( const QPoint& p_Pos);
    void SearchClickedSlot( );
    void ImportClickedSlot( );
    void ExportClickedSlot( );
    void UpdateTreeViewSlot( );
    void FunctionClickedSlot( );
    void QMLGeneratorClickedSlot();


private:
    void ContextMenuAction(QString p_qstrAction);
    void InitContextMenu();
    void SetModule(CwmsApplicationModule p_cModule);
    void AddFunctions();
    void OpenExportConfigurator();
    void OpenImportConfigurator();
    int IdentificateAndSaveDeleteEvent(CdmObject *pCdmObject, CdmContainerManager *p_pCdmContainerManager, IdmEventStoreManager *p_EventStoreManager);
    int prepareStoringDeleteEvent(CdmObject *pCdmObject, CdmObjectContainer *pCdmEventObjectContainer, IdmEventStoreManager *p_EventStoreManager);
    QVariantList StoreDeleteEvent(IdmEventStoreManager *p_pEventStoreManager, CdmObject *pCdmEventObject);
    void IterateOverSubscribersAndExecuteFunction(QList<CdmClassMethod *> ql_Subscribers, QVariantList qvlParameters);

signals:
    void ContextMenuActionSignal( QString p_qstrAction);
};

#endif //
