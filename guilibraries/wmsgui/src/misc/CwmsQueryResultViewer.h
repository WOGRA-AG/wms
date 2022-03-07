#ifndef CWMSQUERYRESULTVIEWER_H
#define CWMSQUERYRESULTVIEWER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

//WMS INcludes
#include "CdmQueryModel.h"

#include "CwmsView.h"

// Own Includes
#include "ui_CwmsQueryResultViewer.h"
#include "wmsgui.h"

// Forwards


// TypeDefs


/* 
 * This class implements the viewer for query results
 */
class WMSGUI_API CwmsQueryResultViewer : public QWidget, public Ui::CwmsQueryResultViewerClass
{
   Q_OBJECT

   private:
      QAbstractItemModel* m_pModel;
      CwmsView m_View;

   public:
    CwmsQueryResultViewer( QWidget* p_pqwParent);
    virtual ~CwmsQueryResultViewer( );
    void SetQuery(QString p_qstrQuery);
    void SetQuery(CdmQueryEnhanced* p_pQuery);
    void SetModel(QAbstractItemModel *p_pModel);
    void SetView(CwmsView p_pView);
public slots:
    void SaveAsCsvClickedSlot();
    void RefreshClickedSlot();
};

#endif // CWMSQUERYRESULTVIEWER_H
