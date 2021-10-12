/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CoeTextEditMainWindow.cpp
 ** Started Implementation: 2008/07/26
 ** Description:
 **
 ** Implements the Texetdeit MainWindow for Editing Texts in WMSGUI and other libs
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/


// System and QT Includes
#include <QActionGroup>
#include <QTextCodec>
#include <QClipboard>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QTextStream>
#include <QPrintDialog>
#include <QTextList>
#include <QPrinter>
#include <QPrintPreviewDialog>

// Own Includes
#include "CdmLogging.h"
#include "CoeInsertTableDlg.h"
#include "CoeTextEditMainWindow.h"

QString CoeTextEditMainWindow::m_sqstrTextSize = "8";
QString CoeTextEditMainWindow::m_sqstrTextFamily = "arial";

/** +-=---------------------------------------------------------Sa 26. Jul 16:17:54 2008----------*
 * @method  CoeTextEditMainWindow::CoeTextEditMainWindow     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwPrent                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 26. Jul 16:17:54 2008----------*/
CoeTextEditMainWindow::CoeTextEditMainWindow(QWidget* p_pqwPrent)
   : QWidget(p_pqwPrent)
{
   ui.setupUi(this);

   m_pqcbStyle = new QComboBox(ui.m_pqtbText);
   ui.m_pqtbText->addWidget(m_pqcbStyle);
   m_pqcbStyle->addItem(tr("Standard"));
   m_pqcbStyle->addItem(tr("Unsortierte Liste (Disc)"));
   m_pqcbStyle->addItem(tr("Unsortierte Liste (Kreise)"));
   m_pqcbStyle->addItem(tr("Unsortierte Liste (Quadrate)"));
   m_pqcbStyle->addItem(tr("Sortierte Liste (Nummerisch)"));
   m_pqcbStyle->addItem(tr("Sortierte Liste (Alphabetisch Kleinbuchstaben)"));
   m_pqcbStyle->addItem(tr("Sortierte Liste (Alphabetisch Großbuchstaben)"));
   connect(m_pqcbStyle, SIGNAL(activated),
           this, SLOT(TextStyleSlot));

   m_pqfcbFont = new QFontComboBox(ui.m_pqtbText);
   m_pqfcbFont->setCurrentFont(QFont(m_sqstrTextFamily));
   ui.m_pqtbText->addWidget(m_pqfcbFont);
   connect(m_pqfcbFont, SIGNAL(activated(const QString &)),
      this, SLOT(TextFamilySlot(const QString &)));

   m_pqcbFontSize = new QComboBox(ui.m_pqtbText);
   m_pqcbFontSize->setObjectName("m_pqcbFontSize");
   ui.m_pqtbText->addWidget(m_pqcbFontSize);
   m_pqcbFontSize->setEditable(true);

   QFontDatabase db;
   foreach(int iSize, db.standardSizes())
   {
      m_pqcbFontSize->addItem(QString::number(iSize));
   }

   m_pqcbFontSize->setCurrentIndex(m_pqcbFontSize->findText(CoeTextEditMainWindow::m_sqstrTextSize));

   connect(m_pqcbFontSize, SIGNAL(activated(const QString &)),
           this, SLOT(TextSizeSlot(const QString &)));

   connect(ui.m_pqaPrint, SIGNAL(triggered()), SLOT(PrintSlot()));
   connect(ui.m_pqaprintPreview, SIGNAL(triggered()), SLOT(PrintPreviewSlot()));
   connect(ui.m_pqaPdfExport, SIGNAL(triggered()), SLOT(ExportPDFSlot()));
   connect(ui.m_pqaSave, SIGNAL(triggered()), SLOT(SaveSlot()));
   connect(ui.m_pqteTextEdit, SIGNAL(cursorPositionChanged()), SLOT(CursorPositionChangedSlot()));
    connect(ui.m_pqteTextEdit->document(), SIGNAL(undoAvailable(bool)),
           ui.m_pqaUndo, SLOT(setEnabled(bool)));
   connect(ui.m_pqteTextEdit->document(), SIGNAL(redoAvailable(bool)),
           ui.m_pqaRedo, SLOT(setEnabled(bool)));
   connect(ui.m_pqteTextEdit, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
           this, SLOT(CurrentCharFormatChangedSlot(const QTextCharFormat &)));

   connect(ui.m_pqteTextEdit, SIGNAL(copyAvailable(bool)), ui.m_pqaCut, SLOT(setEnabled(bool)));
   connect(ui.m_pqteTextEdit, SIGNAL(copyAvailable(bool)), ui.m_pqaCopy, SLOT(setEnabled(bool)));
   connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(ClipboardDataChangedSlot()));
   connect(ui.m_pqaBold, SIGNAL(triggered()), this, SLOT(BoldSlot()));
   connect(ui.m_pqaItalic, SIGNAL(triggered()), this, SLOT(ItalicSlot()));
   connect(ui.m_pqaUnderlined, SIGNAL(triggered()), this, SLOT(UnderlinedSlot()));

   QActionGroup* pqActionGroup = new QActionGroup(this);
   ui.m_pqaAlignCenter->setActionGroup(pqActionGroup);
   ui.m_pqaAlignLeft->setActionGroup(pqActionGroup);
   ui.m_pqaAlignRight->setActionGroup(pqActionGroup);
   ui.m_pqaAlignJustify->setActionGroup(pqActionGroup);

   connect(pqActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(TextAlignmentSlot(QAction *)));

   ui.m_pqaUndo->setEnabled(ui.m_pqteTextEdit->document()->isUndoAvailable());
   ui.m_pqaRedo->setEnabled(ui.m_pqteTextEdit->document()->isRedoAvailable());

   QFont qfFont(m_sqstrTextFamily, m_sqstrTextSize.toInt());
   ui.m_pqteTextEdit->setCurrentFont(qfFont);
}

/** +-=---------------------------------------------------------Sa 26. Jul 16:17:30 2008----------*
 * @method  CoeTextEditMainWindow::~CoeTextEditMainWindow    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoeTextEditMainWindow                                         *
 *----------------last changed: Wolfgang Gra?hof----------------Sa 26. Jul 16:17:30 2008----------*/
CoeTextEditMainWindow::~CoeTextEditMainWindow()
{

}

/** +-=---------------------------------------------------------Do 12. Mrz 18:06:39 2009----------*
 * @method  CoeTextEditMainWindow::SetDefaultFontAndSize     // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFont                               //                                   *
 * @param   QString p_qstrSize                               //                                   *
 * @comment This method sets the default font and size which is set in the system.                *
 *----------------last changed: --------------------------------Do 12. Mrz 18:06:39 2009----------*/
void CoeTextEditMainWindow::SetDefaultFontAndSize(QString p_qstrFont, QString p_qstrSize)
{
   m_sqstrTextFamily = p_qstrFont;
   m_sqstrTextSize = p_qstrSize;
}

void CoeTextEditMainWindow::HideBars()
{
    ui.menuBar->hide();
    ui.statusBar->hide();
}

/** +-=---------------------------------------------------------Sa 26. Jul 15:45:53 2008----------*
 * @method  CoeTextEditMainWindow::SetText                   // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment sets the text to the Textedit.                                                        *
 *----------------last changed: --------------------------------Sa 26. Jul 15:45:53 2008----------*/
void CoeTextEditMainWindow::SetText(QString p_qstrText)
{
   ui.m_pqteTextEdit->setHtml(p_qstrText);
}

/** +-=---------------------------------------------------------Sa 26. Jul 15:48:50 2008----------*
 * @method  CoeTextEditMainWindow::GetText                   // public                            *
 * @return  QString                                          //                                   *
 * @comment returns the edited text in the editor                                                 *
 *----------------last changed: --------------------------------Sa 26. Jul 15:48:50 2008----------*/
QString CoeTextEditMainWindow::GetText()
{
   return ui.m_pqteTextEdit->toHtml();
}

/** +-=---------------------------------------------------------Sa 2. Aug 13:15:36 2008-----------*
 * @method  CoeTextEditMainWindow::GetTextEdit               // public                            *
 * @return  QTextEdit*                                       //                                   *
 * @comment returns the textedit gui element.                                                     *
 *----------------last changed: --------------------------------Sa 2. Aug 13:15:36 2008-----------*/
QTextEdit* CoeTextEditMainWindow::GetTextEdit()
{
   return ui.m_pqteTextEdit;
}

/** +-=---------------------------------------------------------Do 31. Jul 19:20:31 2008----------*
 * @method  CoeTextEditMainWindow::ClipboardDataChangedSlot  // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:20:31 2008----------*/
void CoeTextEditMainWindow::ClipboardDataChangedSlot()
{
   ui.m_pqaPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

/** +-=---------------------------------------------------------Do 31. Jul 19:13:09 2008----------*
 * @method  CoeTextEditMainWindow::CursorPositionChangedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:13:09 2008----------*/
void CoeTextEditMainWindow::CursorPositionChangedSlot()
{
   AlignmentChangedSlot(ui.m_pqteTextEdit->alignment());
}

/** +-=---------------------------------------------------------Do 31. Jul 19:35:21 2008----------*
 * @method  CoeTextEditMainWindow::AlignmentChangedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @param   Qt::Alignment p_iAlignment                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:35:21 2008----------*/
void CoeTextEditMainWindow::AlignmentChangedSlot(Qt::Alignment p_iAlignment)
{
   if (p_iAlignment & Qt::AlignLeft)
   {
      ui.m_pqaAlignLeft->setChecked(true);
   }
   else if (p_iAlignment & Qt::AlignHCenter)
   {
      ui.m_pqaAlignCenter->setChecked(true);
   }
   else if (p_iAlignment & Qt::AlignRight)
   {
      ui.m_pqaAlignRight->setChecked(true);
   } else if (p_iAlignment & Qt::AlignJustify)
   {
      ui.m_pqaAlignJustify->setChecked(true);
   }
}

/** +-=---------------------------------------------------------Do 31. Jul 18:35:15 2008----------*
 * @method  CoeTextEditMainWindow::PrintSlot                 // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This method prints the document.                                                      *
 *----------------last changed: --------------------------------Do 31. Jul 18:35:15 2008----------*/
void CoeTextEditMainWindow::PrintSlot()
{
#ifndef Q_OS_IOS
   QPrinter qPrinter(QPrinter::HighResolution);
   QPrintDialog *pqPrinterDialog = new QPrintDialog(&qPrinter, this);

   if (ui.m_pqteTextEdit->textCursor().hasSelection())
   {
      pqPrinterDialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
   }

   pqPrinterDialog->setWindowTitle(tr("Dokument drucken"));
   if (pqPrinterDialog->exec() == QDialog::Accepted)
   {
      ui.m_pqteTextEdit->print(&qPrinter);
   }

   delete pqPrinterDialog;
#endif
}

/** +-=---------------------------------------------------------Do 31. Jul 18:35:26 2008----------*
 * @method  CoeTextEditMainWindow::PrintPreviewSlot          // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This lsot will be called if the print button was clicked.                             *
 *----------------last changed: --------------------------------Do 31. Jul 18:35:26 2008----------*/
void CoeTextEditMainWindow::PrintPreviewSlot()
{
#ifndef Q_OS_IOS
   QTextDocument* pqtdDocument = ui.m_pqteTextEdit->document();

   if (CHKPTR(pqtdDocument))
   {
      QPrinter printer(QPrinter::HighResolution);
      QPrintPreviewDialog qPrintPreview(&printer, this);
      connect(&qPrintPreview,
              SIGNAL(paintRequested(QPrinter *)),
              SLOT(PrintTextSlot(QPagedPaintDevice *)));

      qPrintPreview.exec();
   }
#endif
}


/** +-=---------------------------------------------------------Do 31. Jul 18:35:36 2008----------*
 * @method  CoeTextEditMainWindow::PrintTextSlot             // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QPrinter* p_pqPrinter                            //                                   *
 * @comment prints the text.                                                                      *
 *----------------last changed: --------------------------------Do 31. Jul 18:35:36 2008----------*/
void CoeTextEditMainWindow::PrintTextSlot(QPagedPaintDevice* p_pqPrinter)
{
    #ifndef Q_OS_IOS
   if (CHKPTR(p_pqPrinter))
   {
      QTextDocument* pqtdDocument = ui.m_pqteTextEdit->document();

      if (CHKPTR(pqtdDocument))
      {
         pqtdDocument->print(p_pqPrinter);
      }
   }
#endif
}


/** +-=---------------------------------------------------------Do 31. Jul 18:35:46 2008----------*
 * @method  CoeTextEditMainWindow::ExportPDFSlot             // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This slot exports the document as PDF.                                                *
 *----------------last changed: --------------------------------Do 31. Jul 18:35:46 2008----------*/
void CoeTextEditMainWindow::ExportPDFSlot()
{
#ifndef Q_OS_IOS
   QString qstrFileName = QFileDialog::getSaveFileName(this,
                                                       "Export PDF",
                                                       QString(),
                                                       "*.pdf");
   if (!qstrFileName.isEmpty())
   {
      if (QFileInfo(qstrFileName).suffix().isEmpty())
      {
         qstrFileName.append(".pdf");
      }

      QPrinter qPrinter(QPrinter::HighResolution);
      qPrinter.setOutputFormat(QPrinter::PdfFormat);
      qPrinter.setOutputFileName(qstrFileName);
      PrintTextSlot(&qPrinter);
   }
#endif
}

/** +-=---------------------------------------------------------Do 31. Jul 18:54:12 2008----------*
 * @method  CoeTextEditMainWindow::SaveSlot                  // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This slot save the file.                                                              *
 *----------------last changed: --------------------------------Do 31. Jul 18:54:12 2008----------*/
void CoeTextEditMainWindow::SaveSlot()
{
   QString qstrFilename = QFileDialog::getSaveFileName(this, tr("Speichern untern..."),
      QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
   if (!qstrFilename.isEmpty())
   {
      QFile qFile(qstrFilename);

      if (qFile.open(QFile::WriteOnly))
      {
         QTextStream ts(&qFile);
         ts.setCodec(QTextCodec::codecForName("UTF-8"));
         QString qstrContent = ui.m_pqteTextEdit->document()->toHtml("UTF-8");;
         ts << qstrContent;
      }

      qFile.close();
   }
}

/** +-=---------------------------------------------------------Do 31. Jul 18:54:01 2008----------*
 * @method  CoeTextEditMainWindow::BoldSlot                  // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 18:54:01 2008----------*/
void CoeTextEditMainWindow::BoldSlot()
{
   QTextCharFormat qFormat;

   if (ui.m_pqaBold->isChecked())
   {
      qFormat.setFontWeight(QFont::Bold);
   }
   else
   {
      qFormat.setFontWeight(QFont::Normal);
   }

   MergeFormatOnWordOrSelection(qFormat);
}

/** +-=---------------------------------------------------------Do 31. Jul 18:59:44 2008----------*
 * @method  CoeTextEditMainWindow::UnderlinedSlot            // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 18:59:44 2008----------*/
void CoeTextEditMainWindow::UnderlinedSlot()
{
   QTextCharFormat qFormat;
   qFormat.setFontUnderline(ui.m_pqaUnderlined->isChecked());
   MergeFormatOnWordOrSelection(qFormat);
}

/** +-=---------------------------------------------------------Do 31. Jul 19:01:30 2008----------*
 * @method  CoeTextEditMainWindow::ItalicSlot                // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:01:30 2008----------*/
void CoeTextEditMainWindow::ItalicSlot()
{
   QTextCharFormat qFormat;
   qFormat.setFontItalic(ui.m_pqaItalic->isChecked());
   MergeFormatOnWordOrSelection(qFormat);
}

/** +-=---------------------------------------------------------Do 31. Jul 19:02:44 2008----------*
 * @method  CoeTextEditMainWindow::TextFamilySlot            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const QString& p_qstrFont                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:02:44 2008----------*/
void CoeTextEditMainWindow::TextFamilySlot(const QString& p_qstrFont)
{
   QTextCharFormat qFormat;
   qFormat.setFontFamily(p_qstrFont);
   MergeFormatOnWordOrSelection(qFormat);
}

/** +-=---------------------------------------------------------Do 31. Jul 19:04:09 2008----------*
 * @method  CoeTextEditMainWindow::TextSizeSlot              // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const QString& p_qstrSize                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:04:09 2008----------*/
void CoeTextEditMainWindow::TextSizeSlot(const QString& p_qstrSize)
{
   QTextCharFormat qFormat;
   qFormat.setFontPointSize(p_qstrSize.toFloat());
   MergeFormatOnWordOrSelection(qFormat);
}

/** +-=---------------------------------------------------------Do 31. Jul 19:04:47 2008----------*
 * @method  CoeTextEditMainWindow::TextStyleSlot             // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iStyle                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:04:47 2008----------*/
void CoeTextEditMainWindow::TextStyleSlot(int p_iStyle)
{
   QTextCursor cursor = ui.m_pqteTextEdit->textCursor();

   if (p_iStyle != 0)
   {
      QTextListFormat::Style style = QTextListFormat::ListDisc;

      switch (p_iStyle)
      {
            default:
            case 1:
               style = QTextListFormat::ListDisc;
               break;
            case 2:
               style = QTextListFormat::ListCircle;
               break;
            case 3:
               style = QTextListFormat::ListSquare;
               break;
            case 4:
               style = QTextListFormat::ListDecimal;
               break;
            case 5:
               style = QTextListFormat::ListLowerAlpha;
               break;
            case 6:
               style = QTextListFormat::ListUpperAlpha;
               break;
      }

      cursor.beginEditBlock();

      QTextBlockFormat blockFmt = cursor.blockFormat();

      QTextListFormat listFmt;

      if (cursor.currentList())
      {
         listFmt = cursor.currentList()->format();
      }
      else
      {
         listFmt.setIndent(blockFmt.indent() + 1);
         blockFmt.setIndent(0);
         cursor.setBlockFormat(blockFmt);
      }

      listFmt.setStyle(style);
      cursor.createList(listFmt);
      cursor.endEditBlock();
   }
   else
   {
      QTextBlockFormat bfmt;
      bfmt.setObjectIndex(-1);
      cursor.mergeBlockFormat(bfmt);
   }
}

/** +-=---------------------------------------------------------Do 31. Jul 19:08:05 2008----------*
 * @method  CoeTextEditMainWindow::TextAlignmentSlot         // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QAction* p_pqaAction                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Jul 19:08:05 2008----------*/
void CoeTextEditMainWindow::TextAlignmentSlot(QAction* p_pqaAction)
{
   if (p_pqaAction == ui.m_pqaAlignLeft)
   {
      ui.m_pqteTextEdit->setAlignment(Qt::AlignLeft);
   }
   else if (p_pqaAction == ui.m_pqaAlignCenter)
   {
      ui.m_pqteTextEdit->setAlignment(Qt::AlignHCenter);
   }
   else if (p_pqaAction == ui.m_pqaAlignRight)
   {
      ui.m_pqteTextEdit->setAlignment(Qt::AlignRight);
   }
   else if (p_pqaAction == ui.m_pqaAlignJustify)
   {
      ui.m_pqteTextEdit->setAlignment(Qt::AlignJustify);
   }
}


/** +-=---------------------------------------------------------Do 31. Jul 18:56:47 2008----------*
 * @method  CoeTextEditMainWindow::MergeFormatOnWordOrSelection // private                        *
 * @return  void                                             //                                   *
 * @param   const QTextCharFormat &format                    //                                   *
 * @comment merges the new textformat whith already set formats.                                  *
 *----------------last changed: --------------------------------Do 31. Jul 18:56:47 2008----------*/
void CoeTextEditMainWindow::MergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
   QTextCursor cursor = ui.m_pqteTextEdit->textCursor();

   if (!cursor.hasSelection())
   {
      cursor.select(QTextCursor::WordUnderCursor);
   }

   cursor.mergeCharFormat(format);
   ui.m_pqteTextEdit->mergeCurrentCharFormat(format);
}

/** +-=---------------------------------------------------------Do 31. Jul 18:58:26 2008----------*
 * @method  CoeTextEditMainWindow::FontChangedSlot           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const QFont& p_rqFont                            //                                   *
 * @comment updates the selected font in editor.                                                  *
 *----------------last changed: --------------------------------Do 31. Jul 18:58:26 2008----------*/
void CoeTextEditMainWindow::FontChangedSlot(const QFont& p_rqFont)
{
   m_pqfcbFont->setCurrentIndex(m_pqfcbFont->findText(QFontInfo(p_rqFont).family()));
   m_pqcbFontSize->setCurrentIndex(m_pqcbFontSize->findText(QString::number(p_rqFont.pointSize())));
   ui.m_pqaBold->setChecked(p_rqFont.bold());
   ui.m_pqaItalic->setChecked(p_rqFont.italic());
   ui.m_pqaUnderlined->setChecked(p_rqFont.underline());
}

/** +-=---------------------------------------------------------Sa 2. Aug 09:23:31 2008-----------*
 * @method  CoeTextEditMainWindow::CurrentCharFormatChangedSlot // public, slots                  *
 * @return  void                                             //                                   *
 * @param   const QTextCharFormat & p_rqTextCharFormat       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 2. Aug 09:23:31 2008-----------*/
void CoeTextEditMainWindow::CurrentCharFormatChangedSlot(const QTextCharFormat & p_rqTextCharFormat)
{
   FontChangedSlot(p_rqTextCharFormat.font());
}

/** +-=---------------------------------------------------------Sa 2. Aug 13:26:15 2008-----------*
 * @method  CoeTextEditMainWindow::SetDefaultFontType        // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFontType                           //                                   *
 * @comment sets the default fonttype for the textedit widget.                                    *
 *----------------last changed: --------------------------------Sa 2. Aug 13:26:15 2008-----------*/
void CoeTextEditMainWindow::SetDefaultFontType(QString p_qstrFontType)
{
   QFont qFont(p_qstrFontType);
   m_pqfcbFont->setCurrentFont(qFont);
   TextFamilySlot(p_qstrFontType);
}

/** +-=---------------------------------------------------------Sa 2. Aug 13:26:25 2008-----------*
 * @method  CoeTextEditMainWindow::SetDefaultFontSize        // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iFontSize                                  //                                   *
 * @comment This method sets the default fontsize of the textedit.                                *
 *----------------last changed: --------------------------------Sa 2. Aug 13:26:25 2008-----------*/
void CoeTextEditMainWindow::SetDefaultFontSize(int p_iFontSize)
{
   m_pqcbFontSize->setCurrentIndex(m_pqcbFontSize->findText(QString::number(p_iFontSize)));
   TextSizeSlot(QString::number(p_iFontSize));
}

/** +-=---------------------------------------------------------Mi 3. Dez 19:17:01 2008-----------*
 * @method  CoeTextEditMainWindow::InsertTableSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot calls the insert tableeditor.                                               *
 *----------------last changed: --------------------------------Mi 3. Dez 19:17:01 2008-----------*/
void CoeTextEditMainWindow::InsertTableSlot()
{
   QTextCursor qCursor = ui.m_pqteTextEdit->textCursor();

   CoeInsertTableDlg* pInsertTableDlg = new CoeInsertTableDlg(this);

   if (pInsertTableDlg->exec() == QDialog::Accepted)
   {
      pInsertTableDlg->InsertTableInTextDocument(&qCursor);
   }

   delete pInsertTableDlg;
}

/** +-=---------------------------------------------------------Mo 30. Mrz 20:26:51 2009----------*
 * @method  CoeTextEditMainWindow::ImportSlot                // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This lsot will be called to import html documents.                                    *
 *----------------last changed: --------------------------------Mo 30. Mrz 20:26:51 2009----------*/
void CoeTextEditMainWindow::ImportSlot()
{
   QString qstrFilename = QFileDialog::getOpenFileName(this, tr("Dateinamen auswählen"), "", "*.html");

   if (!qstrFilename.isEmpty())
   {
      QFile qfFile(qstrFilename);

      if (qfFile.open(QIODevice::ReadOnly))
      {
         QTextStream qtsStream(&qfFile);
         QString qstrText = qtsStream.readAll();
         SetText(qstrText);
         qfFile.close();
      }
   }
}
