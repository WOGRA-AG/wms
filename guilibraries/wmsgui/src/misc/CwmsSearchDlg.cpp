/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsSearchDlg.cpp
 ** Started Implementation: 2009/08/20
 ** Description:
 ** 
 ** This class implements the searchdlg for viewing search widget 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes

// Data management includes
#include "CdmQueryModel.h"

// Own Includes
#include "CwmsSearchDlg.h"

#include "ui_CwmsSearchDlg.h"

/** +-=---------------------------------------------------------Do 20. Aug 17:57:27 2009----------*
 * @method  CwmsSearchDlg::CwmsSearchDlg                     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget *p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Aug 17:57:27 2009----------*/
CwmsSearchDlg::CwmsSearchDlg(QWidget *p_pqwParent)
    : CwmsSearchDlg(p_pqwParent, new CdmQueryModel)
{
}

CwmsSearchDlg::CwmsSearchDlg(QWidget *p_pqwParent, CdmQueryModel *queryModel)
   : QDialog(p_pqwParent, Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint),
     ui(new Ui::CwmsSearchDlgClass),
     m_pQueryModel(queryModel)
{
   ui->setupUi(this);

   connect(ui->m_pCwmsSearchWidget, &CwmsSearchWidgetIf::SearchSignal, this, &CwmsSearchDlg::SearchSlot);
}

CwmsSearchDlg::~CwmsSearchDlg()
{
   delete m_pQueryModel;
   delete ui;
}

int CwmsSearchDlg::exec()
{
   ui->m_pCwmsSearchWidget->FillWidget();

   return QDialog::exec();
}

void CwmsSearchDlg::DisableSearch()
{
   ui->m_pCwmsSearchWidget->SetSearchButtonVisibility(false);
   ui->m_pqtvResults->setHidden(true);
}

/** +-=---------------------------------------------------------Do 20. Aug 18:07:48 2009----------*
 * @method  CwmsSearchDlg::GetSearchWidget                   // public                            *
 * @return  CwmsSearchWidgetIf*                              //                                   *
 * @comment returns the search widget which is used in this dialog.                               *
 *----------------last changed: --------------------------------Do 20. Aug 18:07:48 2009----------*/
CwmsSearchWidgetIf* CwmsSearchDlg::GetSearchWidget()
{
   return ui->m_pCwmsSearchWidget;
}

CdmQueryModel *CwmsSearchDlg::GetQueryModel()
{
   return m_pQueryModel;
}

CdmObject *CwmsSearchDlg::GetSelectedObject()
{
   return m_pQueryModel->GetObject(ui->m_pqtvResults);
}

void CwmsSearchDlg::SearchSlot()
{
   QApplication::setOverrideCursor(Qt::WaitCursor);
   ui->m_pCwmsSearchWidget->CreateQuery(*m_pQueryModel->GetQuery());
   m_pQueryModel->Execute();
   ui->m_pqtvResults->setModel(m_pQueryModel);
   QApplication::restoreOverrideCursor();
}

void CwmsSearchDlg::SearchResultDoubleclicked(const QModelIndex &index)
{
   if(index.isValid())
   {
      emit accept();
   }
}
