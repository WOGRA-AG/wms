#ifndef CWMSQUERYEDITOR_H
#define CWMSQUERYEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmQueryModel.h"

// Own Includes
#include "ui_CwmsQueryEditor.h"
#include "wmsgui.h"

// Forwards
class CdmQueryElement;
class CdmQuery;

// TypeDefs


/* 
 * This class implements the ui of the queryeditor
 */
class WMSGUI_API CwmsQueryEditor : public QWidget, public Ui::CwmsQueryEditorWidget
{
    Q_OBJECT

private:
    CdmQuery* m_pCdmQuery;
    CdmQueryModel m_cCdmModel;

public:
    CwmsQueryEditor( QWidget* p_pqwParent);
    virtual ~CwmsQueryEditor( );
    static void FillQueryAnalyzer(QTreeWidget* p_pqTreeWidget, CdmQuery* p_pQuery);

public slots:
    void SystemVariablesChangedSlot(QString);
    void QueryChangedSlot();
    void DeleteClickedSlot();
    void EnableSorting(bool p_bSorting);

private:
    static void AddQueryElement(CdmQueryElement* p_pCdmElement, QTreeWidgetItem* p_pqParent);

private slots:
    void ExecuteClickedSlot( );
    void SaveClickedSlot( );
    void SaveResultClickedSlot( );
    void ClearResultClickedSlot( );
    void EditClickedSlot();


};

#endif // CWMSQUERYEDITOR_H
