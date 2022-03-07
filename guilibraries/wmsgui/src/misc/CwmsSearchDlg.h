#ifndef CWMSSEARCHDLG_H
#define CWMSSEARCHDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "wmsgui.h"


// Forwards
class CdmObject;
class CdmQueryModel;
class CwmsSearchWidgetIf;
namespace Ui {
   class CwmsSearchDlgClass;
}

/* 
 * This class implements the searchdlg for viewing search widget
 */
class WMSGUI_API CwmsSearchDlg : public QDialog
{
   Q_OBJECT

private:
   Ui::CwmsSearchDlgClass *ui;
   CdmQueryModel *m_pQueryModel;

   public:
    CwmsSearchDlg(QWidget *p_pqwParent);
    CwmsSearchDlg(QWidget *p_pqwParent, CdmQueryModel *queryModel);
    virtual ~CwmsSearchDlg( );

    virtual int exec();

    void DisableSearch();

    CwmsSearchWidgetIf* GetSearchWidget();
    CdmQueryModel *GetQueryModel();
    CdmObject *GetSelectedObject();

private slots:
    void SearchSlot();
    void SearchResultDoubleclicked(const QModelIndex &index);
};

#endif //
