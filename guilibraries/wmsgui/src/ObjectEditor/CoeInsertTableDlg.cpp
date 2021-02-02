/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CoeInsertTableDlg.cpp
 ** Started Implementation: 2008/12/03
 ** Description:
 ** 
 ** implements the dialog for isnerting tables to the editor.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QTextCursor>
#include <QTextDocument>
#include <QTextTable>


// Own Includes
#include "CoeInsertTableDlg.h"


/** +-=---------------------------------------------------------Mi 3. Dez 19:03:49 2008-----------*
 * @method  CoeInsertTableDlg::CoeInsertTableDlg             // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 3. Dez 19:03:49 2008-----------*/
CoeInsertTableDlg::CoeInsertTableDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
    setupUi(this);
}

/** +-=---------------------------------------------------------Mi 3. Dez 19:04:08 2008-----------*
 * @method  CoeInsertTableDlg::~CoeInsertTableDlg            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoeInsertTableDlg                                             *
 *----------------last changed: --------------------------------Mi 3. Dez 19:04:08 2008-----------*/
CoeInsertTableDlg::~CoeInsertTableDlg()
{
}

/** +-=---------------------------------------------------------Mi 3. Dez 19:04:59 2008-----------*
 * @method  CoeInsertTableDlg::InsertTableInTextDocument     // public                            *
 * @return  void                                             //                                   *
 * @param   QTextCursor* p_pCursor                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 3. Dez 19:04:59 2008-----------*/
void CoeInsertTableDlg::InsertTableInTextDocument(QTextCursor* p_pCursor)
{
   if (p_pCursor)
   {
      QTextTableFormat qtfTableFormat;
      qtfTableFormat.setCellPadding(0);
      qtfTableFormat.setCellSpacing(0);
      int iRows = m_pqleRows->text().toInt();
      int iColumns = m_pqleColumns->text().toInt();
      int iBorder = 0;


      QString qstrTable;

      qstrTable = "<table border = " + QString::number(iBorder) + " width = \"100%\">";

      for (int iRowCounter = 0; iRowCounter < iRows; ++iRowCounter)
      {
         qstrTable += "<tr>";

         for (int iColCounter = 0; iColCounter < iColumns; ++iColCounter)
         {
            qstrTable += "<td></td>";
         }

         qstrTable += "</tr>";
      }

      qstrTable += "</table>";
      p_pCursor->insertHtml(qstrTable);
   }
}