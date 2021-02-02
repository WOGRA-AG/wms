// Header is missing impl started on 19.3.02
#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QTextCharFormat>
#include <QMainWindow>
#include <qmap.h>

// own Includes


class QAction;
class QComboBox;
class QTabWidget;
class QTextEdit;

class CoeTextEdit : public QMainWindow
{
    Q_OBJECT

   private:
    QAction *actionTextBold,
            *actionTextUnderline,
            *actionTextItalic,
            *actionTextColor,
            *actionAlignLeft,
            *actionAlignCenter,
            *actionAlignRight,
            *actionSave,
            *actionQuit,
            *actionAlignJustify;
      QComboBox *comboStyle,
                *comboFont,
                *comboSize;
      QString m_qstrFilename;
      QTextEdit* m_pqteEdit;
   public:
   /** +-=---------------------------------------------------------Mo 29. Okt 11:41:54 2012-------*
    * @method  CoeTextEdit::CoeTextEdit                      // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment This is the textedit constructor. This class is a mainwindow class to provide      *
    *          text                                                                               *
    *          editing.                                                                           *
    *----------------last changed: -----------------------------Mo 29. Okt 11:41:54 2012----------*/
    CoeTextEdit( QWidget* parent = NULL);
   public:
   /** +-=---------------------------------------------------------Mo 29. Okt 11:42:09 2012-------*
    * @method  CoeTextEdit::CoeTextEdit                      // public                            *
    * @return                                                //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment This is the textedit constructor. This class is a mainwindow class to provide      *
    *          text                                                                               *
    *          editing.                                                                           *
    *----------------last changed: -----------------------------Mo 29. Okt 11:42:09 2012----------*/
    CoeTextEdit( QString p_qstrFilename, QWidget* parent = NULL);

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::~CoeTextEdit                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoeTextEdit                                                *
    *                                                                                             *
    *---------------------------------------------------------------------------------------------*/
   public:
      virtual ~CoeTextEdit(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::SetupFileActions                 // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment This method creates the actions for the file menu.                                 *
    *---------------------------------------------------------------------------------------------*/
   protected:
       virtual void SetupFileActions(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::SetupEditActions                 // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment his mehtod creates the edit menu.                                                  *
    *---------------------------------------------------------------------------------------------*/
   protected:
       virtual void SetupEditActions(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::SetupTextActions                 // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment This method creates the text menu.                                                 *
    *---------------------------------------------------------------------------------------------*/
   protected:
       virtual void SetupTextActions(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::Load                             // public                            *
    * @return  void                                          //                                   *
    * @param   QString & p_qstrFilename                      //                                   *
    * @comment This method loads the file which should be edited.                                 *
    *---------------------------------------------------------------------------------------------*/
   public:
      void Load(  QString & p_qstrFilename );
   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 11:59:52 2012-------*
    * @method  CoeTextEdit::DoConnections                    // private                           *
    * @return  void                                          //                                   *
    * @param   QTextEdit* pqteEdit                           //                                   *
    * @comment This method connects the textedit with the several slots.                          *
    *----------------last changed: -----------------------------Mo 29. Okt 11:59:52 2012----------*/
    void DoConnections(QTextEdit* pqteEdit);

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::FileSave                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This message saves the file.                                                       *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void FileSave(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::FilePrint                        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This message prints the file.                                                      *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void FilePrint(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::FileExit                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method exits the Editor.                                                      *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void FileExit(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::EditUndo                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method undo`s the last edit step.                                             *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void EditUndo(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::EditRedo                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method redo`s the last edit step.                                             *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void EditRedo(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::EditCut                          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method cuts the selection from editor.                                        *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void EditCut(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::EditCopy                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method copies the selected text.                                              *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void EditCopy(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::EditPaste                        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method inserts copied text.                                                   *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void EditPaste(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextBold                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot changed the marked text to bold font.                                    *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextBold(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextUnderline                    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method underlines the marked text.                                            *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextUnderline(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextItalic                       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method sets the marked text to italic font.                                   *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextItalic(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextFamily                       // private, slots                    *
    * @return  void                                          //                                   *
    * @param   const QString & p_qstrFamily                  //                                   *
    * @comment This method sets the marked text to the font family p_qstrFamily.                  *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextFamily(  const QString & p_qstrFamily );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextSize                         // private, slots                    *
    * @return  void                                          //                                   *
    * @param   const QString & p_qstrSize                    //                                   *
    * @comment This method sets the textsize of the marked text.                                  *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextSize(  const QString & p_qstrSize );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextStyle                        // private, slots                    *
    * @return  void                                          //                                   *
    * @param   int p_iStyle                                  //                                   *
    * @comment This method sets the textstyle p_iStyle to the marked text.                        *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextStyle(  int p_iStyle );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextColor                        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method sets the textcolor if the marked text.                                 *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextColor(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TextAlign                        // private, slots                    *
    * @return  void                                          //                                   *
    * @param   QAction* p_pqaAction                          //                                   *
    * @comment This method sets the action text alignment to the marked text.                     *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TextAlign(  QAction* p_pqaAction );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::FontChanged                      // private, slots                    *
    * @return  void                                          //                                   *
    * @param   const QFont & p_qfFont                        //                                   *
    * @comment This slot will be called if the font was changed.                                  *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void FontChanged(  const QFont & p_qfFont );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::ColorChanged                     // private, slots                    *
    * @return  void                                          //                                   *
    * @param   const QColor & p_qcColor                      //                                   *
    * @comment This method will be called if the color was changed.                               *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void ColorChanged(  const QColor & p_qcColor );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::AlignmentChanged                 // private, slots                    *
    * @return  void                                          //                                   *
    * @param   int p_iAlignment                              //                                   *
    * @comment This slot will be called if the Alignment of text was changed.                     *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void AlignmentChanged(  int p_iAlignment );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::SetText                          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment This method is the alternative to the load method to display and edit text.        *
    *---------------------------------------------------------------------------------------------*/
   public:
      void SetText(  QString p_qstrText );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::GetText                          // public                            *
    * @return  QString                                       //                                   *
    * @comment This method returns the edited text.                                               *
    *---------------------------------------------------------------------------------------------*/
   public:
      QString GetText(  );

   /** +-=----------------------------------------------------------------------------------------*
    * @method  CoeTextEdit::TableCellEdit                    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called to edit a Table Cell in a own small editor.               *
    *---------------------------------------------------------------------------------------------*/
    private slots:
void TableCellEdit(  );

    public slots:
         /** +-=---------------------------------------------------------Mi 10. Sep 09:45:04 2003*
    * @method  CoeTextEdit::ModifiedSlot                     // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the textchanged signal was emitted. it emits the modified signal, for other moduls.*
    *----------------last changed: Wolfgang Graßhof-------------Mi 10. Sep 09:45:04 2003----------*/
void ModifiedSlot(  );

   private:
   /** +-=---------------------------------------------------------Mi 10. Sep 09:45:32 2003*
    * @method  CoeTextEdit::ModifiedSignal                   // private, signals                  *
    * @return  void                                          //                                   *
    * @comment This signal will be emitted if modification are made in the text.                  *
    *----------------last changed: Wolfgang Graßhof-------------Mi 10. Sep 09:45:32 2003----------*/
    signals:
       void ModifiedSignal(  );

   public:
   /** +-=---------------------------------------------------------Mo 29. Okt 12:06:45 2012-------*
    * @method  CoeTextEdit::GetTextEdit                      // public                            *
    * @return  QTextEdit*                                    //                                   *
    * @comment This method returns the pointer of the textedit.                                   *
    *----------------last changed: -----------------------------Mo 29. Okt 12:06:45 2012----------*/
    QTextEdit* GetTextEdit();

   public:
   /** +-=---------------------------------------------------------Di 18. Jan 08:49:07 2005*
    * @method  CoeTextEdit::SetDefaultFontType               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFontType                        //                                   *
    * @comment sets the default fonttype for the textedit widget.                                 *
    *----------------last changed: -----------------------------Di 18. Jan 08:49:07 2005----------*/
void SetDefaultFontType(  QString p_qstrFontType );

   public:
   /** +-=---------------------------------------------------------Di 18. Jan 08:49:39 2005*
    * @method  CoeTextEdit::SetDefaultFontSize               // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iFontSize                               //                                   *
    * @comment This method sets the default fontsize of the textedit.                             *
    *----------------last changed: -----------------------------Di 18. Jan 08:49:39 2005----------*/
void SetDefaultFontSize(  int p_iFontSize );

    private slots:
   /** +-=---------------------------------------------------------Mi 9. Mrz 23:12:45 2005*
    * @method  CoeTextEdit::InsertHorizontalLine             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot inserts a horizontal line into the textedit.                             *
    *----------------last changed: -----------------------------Mi 9. Mrz 23:12:45 2005-----------*/
void InsertHorizontalLine(  );

    private slots:
   /** +-=---------------------------------------------------------So 20. Nov 10:08:14 2005*
    * @method  CoeTextEdit::FontDialog                       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to call the font dialog.                *
    *----------------last changed: -----------------------------So 20. Nov 10:08:14 2005----------*/
void FontDialog(  );

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 13:34:09 2012-------*
    * @method  CoeTextEdit::MergeFormatOnWordOrSelection     // private                           *
    * @return  void                                          //                                   *
    * @param   const QTextCharFormat &format                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 13:34:09 2012----------*/
    void MergeFormatOnWordOrSelection(const QTextCharFormat &format);
};


#endif //
