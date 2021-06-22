#ifndef CWMSSEARCHWINDOW_H
#define CWMSSEARCHWINDOW_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>
#include <QList>

// WMS Includes
#include "CdmQueryEnhanced.h"
#include "CdmQueryModel.h"

// Own Includes
#include "wmsgui.h"
#include "CwmsApplicationModule.h"
#include "ui_CwmsSearchWindow.h"

// Forwards
class CdmObjectContainer;
class CwmsRuntime;
class QMenu;
class QToolBar;

// TypeDefs


/* 
 * This class implements the user for generic search
 */
class WMSGUI_API CwmsSearchWindow : public QWidget, public Ui::CwmsSearchWindowClass
{
    Q_OBJECT

private:
    CdmQueryEnhanced* m_pCdmQuery;
    CdmQueryModel m_CdmModel;
    CdmObject* m_rpCdmPrintingTemplate;
    QList<QString> m_qllResultMembers;
    QMenu* m_pMenu;
    QToolBar* m_pToolBar;

public:
    CwmsSearchWindow( QWidget* p_pqwParent);
    virtual ~CwmsSearchWindow( );
    void FillDialog(CdmObjectContainer* p_pContainer);
    void AddSearchMember(QString p_qstrSearchMember);
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);
    CdmObject *GetSelectedObject();
    void AddResultMember(QString p_qstrMember);
    void SetPrintVisibility(bool p_bVisible);
    void SetExportVisibility(bool p_bVisible);
    void SetImportVisibility(bool p_bVisible);
    void SetDeleteVisibility(bool p_bVisible);
    void SetEditVisibility(bool p_bVisible);
    void SaveAsCsvClickedSlot();

    QList<CdmObject *> GetSelectedObjects();
public slots:
    void DeleteClickedSlot();
    void NewClickedSlot();
    void CopyClickedSlot();

private:
    void SetModule(CwmsApplicationModule p_cModule);
    void ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule p_cModule);
    void Print();
    void Print(CdmObject* p_pCdmObject);
    void OpenExportConfigurator();
    void OpenImportConfigurator();
    void AddResultMembers();

private slots:
    void EditClickedSlot( );
    void SearchSlot( );
    void PrintClickedSlot( );
    void ExportClickedSlot( );
    void ImportClickedSlot( );

};

#endif // CWMSSEARCHWINDOW_H
