/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CoeTextEditMainWindow.h
 ** Started Implementation: 2008/07/26
 ** Description:
 ** 
 ** Implements the Texetdeit MainWindow for Editing Texts in WMSGUI and other libs
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef COETEXTEDITMAINWINDOW_H
#define COETEXTEDITMAINWINDOW_H

// System and QT Includes
#include <QMainWindow>
#include <QFontComboBox>
#include <QPrinter>

// own Includes
#include "wmsgui.h"
#include "ui_CoeTextEditMainWindow.h"

class WMSGUI_API CoeTextEditMainWindow : public QWidget
{
    Q_OBJECT

   public:
      Ui::CoeTextEditMainWindowClass ui;
   private:
       QFontComboBox* m_pqfcbFont;
       QComboBox* m_pqcbStyle;
       QComboBox* m_pqcbFontSize;
       static QString m_sqstrTextFamily;
       static QString m_sqstrTextSize;

   public:
   /** +-=---------------------------------------------------------Sa 26. Jul 16:17:54 2008-------*
    * @method  CoeTextEditMainWindow::CoeTextEditMainWindow  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwPrent                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 26. Jul 16:17:54 2008----------*/
    CoeTextEditMainWindow( QWidget* p_pqwPrent);

   public:
   /** +-=---------------------------------------------------------Sa 26. Jul 16:17:30 2008-------*
    * @method  CoeTextEditMainWindow::~CoeTextEditMainWindow // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoeTextEditMainWindow                                      *
    *----------------last changed: Wolfgang Graßhof-------------Sa 26. Jul 16:17:30 2008----------*/
    virtual ~CoeTextEditMainWindow( );

   public:
   /** +-=---------------------------------------------------------Sa 26. Jul 15:45:53 2008-------*
    * @method  CoeTextEditMainWindow::SetText                // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment sets the text to the Textedit.                                                     *
    *----------------last changed: -----------------------------Sa 26. Jul 15:45:53 2008----------*/
    void SetText(QString p_qstrText);

   public:
   /** +-=---------------------------------------------------------Sa 26. Jul 15:48:50 2008-------*
    * @method  CoeTextEditMainWindow::GetText                // public                            *
    * @return  QString                                       //                                   *
    * @comment returns the edited text in the editor                                              *
    *----------------last changed: -----------------------------Sa 26. Jul 15:48:50 2008----------*/
    QString GetText();

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:35:26 2008-------*
    * @method  CoeTextEditMainWindow::PrintPreviewSlot       // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This lsot will be called if the print button was clicked.                          *
    *----------------last changed: -----------------------------Do 31. Jul 18:35:26 2008----------*/
void PrintPreviewSlot( );


    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:35:36 2008-------*
    * @method  CoeTextEditMainWindow::PrintTextSlot          // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QPrinter* p_pqPrinter                         //                                   *
    * @comment prints the text.                                                                   *
    *----------------last changed: -----------------------------Do 31. Jul 18:35:36 2008----------*/
void PrintTextSlot( QPagedPaintDevice* p_pqPrinter);

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:35:46 2008-------*
    * @method  CoeTextEditMainWindow::ExportPDFSlot          // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This slot exports the document as PDF.                                             *
    *----------------last changed: -----------------------------Do 31. Jul 18:35:46 2008----------*/
void ExportPDFSlot( );

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:35:15 2008-------*
    * @method  CoeTextEditMainWindow::PrintSlot              // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This method prints the document.                                                   *
    *----------------last changed: -----------------------------Do 31. Jul 18:35:15 2008----------*/
void PrintSlot( );

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:54:12 2008-------*
    * @method  CoeTextEditMainWindow::SaveSlot               // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This slot save the file.                                                           *
    *----------------last changed: -----------------------------Do 31. Jul 18:54:12 2008----------*/
void SaveSlot( );


    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:54:01 2008-------*
    * @method  CoeTextEditMainWindow::BoldSlot               // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 18:54:01 2008----------*/
void BoldSlot( );

   private:
   /** +-=---------------------------------------------------------Do 31. Jul 18:56:47 2008-------*
    * @method  CoeTextEditMainWindow::MergeFormatOnWordOrSelection // private                     *
    * @return  void                                          //                                   *
    * @param   const QTextCharFormat &format                 //                                   *
    * @comment merges the new textformat whith already set formats.                               *
    *----------------last changed: -----------------------------Do 31. Jul 18:56:47 2008----------*/
    void MergeFormatOnWordOrSelection(const QTextCharFormat &format);

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:58:26 2008-------*
    * @method  CoeTextEditMainWindow::FontChangedSlot        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const QFont& p_rqFont                         //                                   *
    * @comment updates the selected font in editor.                                               *
    *----------------last changed: -----------------------------Do 31. Jul 18:58:26 2008----------*/
void FontChangedSlot( const QFont& p_rqFont);

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 18:59:44 2008-------*
    * @method  CoeTextEditMainWindow::UnderlinedSlot         // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 18:59:44 2008----------*/
void UnderlinedSlot( );

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 19:01:30 2008-------*
    * @method  CoeTextEditMainWindow::ItalicSlot             // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:01:30 2008----------*/
void ItalicSlot( );

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 19:02:44 2008-------*
    * @method  CoeTextEditMainWindow::TextFamilySlot         // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const QString& p_qstrFont                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:02:44 2008----------*/
void TextFamilySlot( const QString& p_qstrFont);

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 19:04:09 2008-------*
    * @method  CoeTextEditMainWindow::TextSizeSlot           // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const QString& p_qstrSize                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:04:09 2008----------*/
void TextSizeSlot( const QString& p_qstrSize);

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 19:04:47 2008-------*
    * @method  CoeTextEditMainWindow::TextStyleSlot          // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iStyle                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:04:47 2008----------*/
void TextStyleSlot( int p_iStyle);

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 19:08:05 2008-------*
    * @method  CoeTextEditMainWindow::TextAlignmentSlot      // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QAction* p_pqaAction                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:08:05 2008----------*/
void TextAlignmentSlot( QAction* p_pqaAction);

    private slots:
   /** +-=---------------------------------------------------------Do 31. Jul 19:13:09 2008-------*
    * @method  CoeTextEditMainWindow::CursorPositionChangedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:13:09 2008----------*/
void CursorPositionChangedSlot( );

    public slots:
         /** +-=---------------------------------------------------------Do 31. Jul 19:20:31 2008-------*
    * @method  CoeTextEditMainWindow::ClipboardDataChangedSlot // public, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:20:31 2008----------*/
void ClipboardDataChangedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 31. Jul 19:35:21 2008-------*
    * @method  CoeTextEditMainWindow::AlignmentChangedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @param   Qt::Alignment p_iAlignment                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Jul 19:35:21 2008----------*/
void AlignmentChangedSlot( Qt::Alignment p_iAlignment);

    public slots:
         /** +-=---------------------------------------------------------Sa 2. Aug 09:23:31 2008--------*
    * @method  CoeTextEditMainWindow::CurrentCharFormatChangedSlot // public, slots               *
    * @return  void                                          //                                   *
    * @param   const QTextCharFormat & p_rqTextCharFormat    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 2. Aug 09:23:31 2008-----------*/
void CurrentCharFormatChangedSlot( const QTextCharFormat & p_rqTextCharFormat);

   public:
   /** +-=---------------------------------------------------------Sa 2. Aug 13:15:36 2008--------*
    * @method  CoeTextEditMainWindow::GetTextEdit            // public                            *
    * @return  QTextEdit*                                    //                                   *
    * @comment returns the textedit gui element.                                                  *
    *----------------last changed: -----------------------------Sa 2. Aug 13:15:36 2008-----------*/
    QTextEdit* GetTextEdit();

   public:
   /** +-=---------------------------------------------------------Sa 2. Aug 13:26:15 2008--------*
    * @method  CoeTextEditMainWindow::SetDefaultFontType     // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFontType                        //                                   *
    * @comment sets the default fonttype for the textedit widget.                                 *
    *----------------last changed: -----------------------------Sa 2. Aug 13:26:15 2008-----------*/
    void SetDefaultFontType(QString p_qstrFontType);

   public:
   /** +-=---------------------------------------------------------Sa 2. Aug 13:26:25 2008--------*
    * @method  CoeTextEditMainWindow::SetDefaultFontSize     // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iFontSize                               //                                   *
    * @comment This method sets the default fontsize of the textedit.                             *
    *----------------last changed: -----------------------------Sa 2. Aug 13:26:25 2008-----------*/
    void SetDefaultFontSize(int p_iFontSize);

    private slots:
   /** +-=---------------------------------------------------------Mi 3. Dez 19:17:01 2008--------*
    * @method  CoeTextEditMainWindow::InsertTableSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot calls the insert tableeditor.                                            *
    *----------------last changed: -----------------------------Mi 3. Dez 19:17:01 2008-----------*/
void InsertTableSlot( );

   public:
   /** +-=---------------------------------------------------------Do 12. Mrz 18:06:39 2009-------*
    * @method  CoeTextEditMainWindow::SetDefaultFontAndSize  // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFont                            //                                   *
    * @param   QString p_qstrSize                            //                                   *
    * @comment This method sets the default font and size which is set in the system.             *
    *----------------last changed: -----------------------------Do 12. Mrz 18:06:39 2009----------*/
    static void SetDefaultFontAndSize(QString p_qstrFont, QString p_qstrSize);

    void HideBars();
public slots:
         /** +-=---------------------------------------------------------Mo 30. Mrz 20:26:51 2009-------*
    * @method  CoeTextEditMainWindow::ImportSlot             // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This lsot will be called to import html documents.                                 *
    *----------------last changed: -----------------------------Mo 30. Mrz 20:26:51 2009----------*/
void ImportSlot( );
};

#endif // // COETEXTEDITMAINWINDOW_H
