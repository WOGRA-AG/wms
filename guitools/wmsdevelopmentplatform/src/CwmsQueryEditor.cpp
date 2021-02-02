/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsQueryEditor.cpp
 ** Started Implementation: 2012/07/26
 ** Description:
 **
 ** Implements the ui of the queryeditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

// WMS Includes
#include "CdmError.h"
#include "CdmQueryBuilder.h"
#include "CdmQueryEnhanced.h"


// own Includes
#include "CwmsQueryEditor.h"

/** +-=---------------------------------------------------------Do 26. Jul 11:26:32 2012----------*
 * @method  CwmsQueryEditor::CwmsQueryEditor                 // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:26:32 2012----------*/
CwmsQueryEditor::CwmsQueryEditor(QWidget* p_pqwParent)
: QWidget(p_pqwParent),
  m_pCdmQuery(NULL)
{
   setupUi(this);

   m_pqtvResult->setSelectionBehavior(QAbstractItemView::SelectRows);
   m_pqtvResult->setSelectionMode(QAbstractItemView::ContiguousSelection);
}

/** +-=---------------------------------------------------------Do 26. Jul 11:27:00 2012----------*
 * @method  CwmsQueryEditor::~CwmsQueryEditor                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsQueryEditor                                               *
 *----------------last changed: --------------------------------Do 26. Jul 11:27:00 2012----------*/
CwmsQueryEditor::~CwmsQueryEditor()
{
}

/** +-=---------------------------------------------------------Do 26. Jul 11:39:27 2012----------*
 * @method  CwmsQueryEditor::ExecuteClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:39:27 2012----------*/
void CwmsQueryEditor::ExecuteClickedSlot()
{
   QString qstrQuery = m_pqteEditor->toPlainText();
   m_cCdmModel.Execute(qstrQuery);
   m_pqtvResult->setModel(&m_cCdmModel);
}

/** +-=---------------------------------------------------------Do 26. Jul 11:39:42 2012----------*
 * @method  CwmsQueryEditor::SaveClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:39:42 2012----------*/
void CwmsQueryEditor::SaveClickedSlot()
{
   QString qstrFilename = AskForFilename(".wql");

   if (!qstrFilename.isEmpty())
   {
     SaveContent(qstrFilename, m_pqteEditor->toPlainText());
   }
}

/** +-=---------------------------------------------------------Do 26. Jul 11:39:53 2012----------*
 * @method  CwmsQueryEditor::SaveResultClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:39:53 2012----------*/
void CwmsQueryEditor::SaveResultClickedSlot()
{
   QString qstrFilename = AskForFilename(".csv");

   if (!qstrFilename.isEmpty())
   {
      QString qstrContent;
      QItemSelectionModel* pqSelection = m_pqtvResult->selectionModel();

      if (pqSelection)
      {
         QModelIndexList qlIndexList = pqSelection->selectedRows();
         qstrContent = m_cCdmModel.ExportCsv(qlIndexList);
      }
      else
      {
         qstrContent = m_cCdmModel.ExportCsv();
      }
      
      SaveContent(qstrFilename, qstrContent);
   }
}

/** +-=---------------------------------------------------------Di 14. Aug 09:56:37 2012----------*
 * @method  CwmsQueryEditor::AskForFilename                  // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrFileType                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 09:56:37 2012----------*/
QString CwmsQueryEditor::AskForFilename(QString p_qstrFileType)
{
   QString qstrFilename = QFileDialog::getSaveFileName(this, 
                                                       tr("Bitte Dateinamen angeben"), 
                                                       "", 
                                                       p_qstrFileType);

   if (!qstrFilename.isEmpty())
   {
      if (!qstrFilename.contains("."))
      {
         qstrFilename += p_qstrFileType;
      }
   }

   return qstrFilename;
}

/** +-=---------------------------------------------------------Di 14. Aug 10:10:25 2012----------*
 * @method  CwmsQueryEditor::SaveContent                     // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrContent                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 10:10:25 2012----------*/
void CwmsQueryEditor::SaveContent(QString p_qstrFilename, QString p_qstrContent)
{
   if (!p_qstrFilename.isEmpty())
   {
      QFile qFile(p_qstrFilename);

      if (qFile.open(QIODevice::WriteOnly))
      {
         QTextStream qTextStream(&qFile);
         qTextStream << p_qstrContent;
      }

      qFile.close();
   }
}

/** +-=---------------------------------------------------------Do 26. Jul 11:40:05 2012----------*
 * @method  CwmsQueryEditor::ClearResultClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:40:05 2012----------*/
void CwmsQueryEditor::ClearResultClickedSlot()
{
   // ToDo
   //m_pqtvResult->clear();

   // Perhaps:
   // m_cCdmModel.Execute("");
}