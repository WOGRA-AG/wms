/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CslTextedit.cpp
 ** Started Implementation: 19.3.02
 ** Description:
 ** 
 ** Implements the gui wysiwyg editor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QIcon>
#include <QTextEdit>
#include <QTextList>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QTabWidget>
#include <QApplication>
#include <QFontDatabase>
#include <QPrintDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <QPrinter>
#include <QFontDialog>
#include <QColorDialog>
#include <QPainter>
#include <QList>
#include <QPixmap>
#include <QTextStream>

// own Includes
/*
#include "Texteditorcopy.xpm"
#include "Texteditorcut.xpm"
#include "Texteditorpaste.xpm"
#include "Texteditorredo.xpm"
#include "Texteditorundo.xpm"
#include "Texteditorprint.xpm"
#include "Texteditorsave.xpm"
#include "Texteditorbold.xpm"
#include "Texteditoraligncenter.xpm"
#include "Texteditoralignjustify.xpm"
#include "Texteditoralignleft.xpm"
#include "Texteditoralignright.xpm"
#include "Texteditoritalic.xpm"
#include "Texteditorunderlined.xpm"
#include "Texteditorfonttypesize.xpm"
#include "Texteditorcolor.xpm"
*/
#include "coetextedit.h"


/** +-=---------------------------------------------------------Mo 29. Okt 11:41:54 2012----------*
 * @method  CoeTextEdit::CoeTextEdit                         // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment This is the textedit constructor. This class is a mainwindow class to provide         *
 *          text                                                                                  *
 *          editing.                                                                              *
 *----------------last changed: --------------------------------Mo 29. Okt 11:41:54 2012----------*/
CoeTextEdit::CoeTextEdit(QWidget* parent)
   : QMainWindow( parent)
{
   m_pqteEdit = nullptr;
   
   SetupFileActions();
   SetupEditActions();
   SetupTextActions();
}

/** +-=---------------------------------------------------------Mo 29. Okt 11:42:09 2012----------*
 * @method  CoeTextEdit::CoeTextEdit                         // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment This is the textedit constructor. This class is a mainwindow class to provide         *
 *          text                                                                                  *
 *          editing.                                                                              *
 *----------------last changed: --------------------------------Mo 29. Okt 11:42:09 2012----------*/
CoeTextEdit::CoeTextEdit(QString p_qstrFilename, QWidget* parent)
: QMainWindow(parent)
{
   m_pqteEdit = nullptr;
   SetupFileActions();
   SetupEditActions();
   SetupTextActions();
   
   m_qstrFilename = p_qstrFilename;
   Load(p_qstrFilename);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::~CoeTextEdit                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoeTextEdit                                                   *
 *                                                                                                *
 *------------------------------------------------------------------------------------------------*/
CoeTextEdit::~CoeTextEdit(  )
{
   // nothing to do qt does it all for us :-)
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::SetupFileActions                    // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment This method creates the actions for the file menu.                                    *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::SetupFileActions(  )
{
    QToolBar *tb = new QToolBar( this );
    tb->setWindowTitle(tr("Datei Funktionen"));
    QMenu *menu = new QMenu(this);
    menu->setTitle(tr("Datei"));
    menuBar()->addMenu(menu);

    QAction *a;
    actionSave = new QAction(tr("&Speichern..."), this);
    connect(actionSave, SIGNAL(activated()), this, SLOT(FileSave()));
    menu->addAction(actionSave);
    tb->addAction(actionSave);
 
    a = new QAction(tr("&Drucken..."),this);
    connect(a, SIGNAL(activated()), this, SLOT(FilePrint()));
    menu->addAction(a);
    tb->addAction(a);
   
    actionQuit = new QAction(tr( "Editor beenden" ), this);
    connect( actionQuit, SIGNAL(activated()), this, SLOT(FileExit()));
    menu->addAction(actionQuit);
    tb->addAction(actionQuit);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::SetupEditActions                    // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment his mehtod creates the edit menu.                                                     *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::SetupEditActions(  )
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Bearbeiten Funktionen"));
    QMenu *menu = new QMenu(this);
    menu->setTitle(tr("Bearbeiten"));
    menuBar()->addMenu(menu);

    QAction* a;
    a = new QAction(tr("&Rückgängig"), this);
    connect(a, SIGNAL(activated()), this, SLOT(EditUndo()));
    menu->addAction(a);
    tb->addAction(a);
    a = new QAction(tr("&Wiederholen"), this);
    connect(a, SIGNAL(activated()), this, SLOT(EditRedo()));
    menu->addAction(a);
    tb->addAction(a);
    menu->insertSeparator(a);
    a = new QAction(tr("Kopieren"), this);
    connect(a, SIGNAL(activated()), this, SLOT(EditCopy()));
    menu->addAction(a);
    tb->addAction(a);
    a = new QAction(tr("&Ausschneiden"), this);
    connect(a, SIGNAL(activated()), this, SLOT(EditCut()));
    menu->addAction(a);
    tb->addAction(a);
    a = new QAction(tr("Einfügen"), this);
    connect(a, SIGNAL(activated()), this, SLOT(EditPaste()));
    menu->addAction(a);
    tb->addAction(a);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::SetupTextActions                    // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment This method creates the text menu.                                                    *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::SetupTextActions(  )
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle( "Format Actions" );
    QMenu *menu = new QMenu(this);
    menu->setTitle(tr("Format"));
    menuBar()->addMenu( menu);

    comboStyle = new QComboBox(tb);
    comboStyle->setEditable(false);
    comboStyle->addItem(tr("Standard"));
    comboStyle->addItem(tr("ungeordnete Liste (Disc)"));
    comboStyle->addItem(tr("ungeordnete Liste (Kreis)")); 
    comboStyle->addItem(tr("ungeordnete Liste (Rechteck)"));
    comboStyle->addItem(tr("geordnete Liste (numerisch)"));
    comboStyle->addItem(tr("geordnete Liste (Alphanumerisch Kleinbuchstaben)"));
    comboStyle->addItem(tr("geordnete Liste (Alphanumerisch Großbuchstaben)"));
    connect(comboStyle, SIGNAL(activated(int)), this, SLOT(TextStyle(int)));

    comboFont = new QComboBox(tb);
    comboFont->setEditable(true);
    QFontDatabase db;
    comboFont->addItems(db.families());
    connect(comboFont, SIGNAL(activated(const QString &)), this, SLOT(TextFamily(const QString &)));
    comboFont->lineEdit()->setText(QApplication::font().family());

    comboSize = new QComboBox(tb);
    comboSize->setEditable(true);
    QList<int> sizes = db.standardSizes();
    QList<int>::Iterator it = sizes.begin();
    
    for ( ; it != sizes.end(); ++it )
    {
	      comboSize->addItem(QString::number(*it));
    }
    
    connect(comboSize, SIGNAL(activated(const QString &)), this, SLOT(TextSize( const QString &)));
    comboSize->lineEdit()->setText(QString::number(QApplication::font().pointSize()));

    actionTextBold = new QAction(tr("Fett"), this);
    connect( actionTextBold, SIGNAL( activated() ), this, SLOT( TextBold() ) );
    tb->addAction(actionTextBold);
    menu->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(tr("Kursiv"), this);
    connect(actionTextItalic, SIGNAL(activated()), this, SLOT(TextItalic()));
    tb->addAction(actionTextItalic);
    menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(tr("Unterstrichen"), this);
    connect(actionTextUnderline, SIGNAL(activated()), this, SLOT(TextUnderline()));
    tb->addAction(actionTextUnderline);
    menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);
    actionTextUnderline->setCheckable(true);
    QAction* pqgaFont = new QAction(tr("Schriftart und Größe"), this);
    connect( pqgaFont, SIGNAL( activated() ), this, SLOT( FontDialog() ) );
    tb->addAction(pqgaFont);
    menu->addAction(pqgaFont);
    menu->insertSeparator(pqgaFont);

    QActionGroup *grp = new QActionGroup(this);
    grp->setExclusive( true );
    connect(grp, SIGNAL(selected(QAction*)), this, SLOT(TextAlign(QAction*)));

    actionAlignLeft = new QAction(tr("Linksbündig"), grp);
    tb->addAction(actionAlignLeft);
    menu->addAction(actionAlignLeft);
    actionAlignLeft->setCheckable(true);

    actionAlignCenter = new QAction(tr( "Zentriert"), grp);
    tb->addAction(actionAlignCenter);
    menu->addAction(actionAlignCenter);
    actionAlignCenter->setCheckable(true);

    actionAlignRight = new QAction(tr("Rechtsbündig"), grp);
    tb->addAction(actionAlignRight);
    menu->addAction(actionAlignRight);
    actionAlignRight->setCheckable(true);

    actionAlignJustify = new QAction(tr("&Blocksatz"), grp);
    tb->addAction(actionAlignJustify);
    menu->addAction(actionAlignJustify);
    actionAlignJustify->setCheckable(true);

    menu->insertSeparator(actionAlignJustify);

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(tr("Farbe"), this);
    connect(actionTextColor, SIGNAL(activated()), this, SLOT(TextColor()));
    tb->addAction(actionTextColor);
    menu->addAction(actionTextColor);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::Load                                // public                            *
 * @return  void                                             //                                   *
 * @param   QString & p_qstrFilename                         //                                   *
 * @comment This method loads the file which should be edited.                                    *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::Load(  QString & p_qstrFilename )
{
   if (!p_qstrFilename.isEmpty())
   {
      if (QFile::exists(p_qstrFilename))
      {
         if (m_pqteEdit)
         {
            delete m_pqteEdit;
         }
         
         m_pqteEdit = new QTextEdit(this);
         DoConnections(m_pqteEdit);
         m_pqteEdit->setWordWrapMode(QTextOption::WordWrap);
         setCentralWidget(m_pqteEdit);
         QFile file(p_qstrFilename);
         
         if (file.open(QIODevice::ReadOnly))
         {
            QTextStream ts(&file);
            m_pqteEdit->setText(ts.readAll());
            m_pqteEdit->viewport()->setFocus();
         }
      }
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::SetText                             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment This method is the alternative to the load method to display and edit text.           *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::SetText(  QString p_qstrText )
{
   if (!m_pqteEdit)
   {
      m_pqteEdit = new QTextEdit(this);
      connect(m_pqteEdit, SIGNAL(textChanged()), this, SLOT(ModifiedSlot()));
   }

   setCentralWidget(m_pqteEdit);
   m_pqteEdit->show();
   DoConnections( m_pqteEdit );
   m_pqteEdit->setText( p_qstrText );
   actionQuit->setEnabled( false );
   actionQuit->setVisible(false);
   actionSave->setEnabled( true );
}

/** +-=---------------------------------------------------------Mi 9. Mrz 23:12:45 2005-----------*
 * @method  CoeTextEdit::InsertHorizontalLine                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot inserts a horizontal line into the textedit.                                *
 *----------------last changed: --------------------------------Mi 9. Mrz 23:12:45 2005-----------*/
void CoeTextEdit::InsertHorizontalLine(  )
{
   if(m_pqteEdit)
   {
      m_pqteEdit->insertHtml("<br><hr><br>");
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::GetText                             // public                            *
 * @return  QString                                          //                                   *
 * @comment This method returns the edited text.                                                  *
 *------------------------------------------------------------------------------------------------*/
QString CoeTextEdit::GetText(  )
{
   QString qstrText;
   
   if ( m_pqteEdit )
   {
      qstrText = m_pqteEdit->toHtml();
   }
   
   return qstrText;
}

/** +-=---------------------------------------------------------Mo 29. Okt 12:06:45 2012----------*
 * @method  CoeTextEdit::GetTextEdit                         // public                            *
 * @return  QTextEdit*                                       //                                   *
 * @comment This method returns the pointer of the textedit.                                      *
 *----------------last changed: --------------------------------Mo 29. Okt 12:06:45 2012----------*/
QTextEdit* CoeTextEdit::GetTextEdit()
{
   return m_pqteEdit;
}



/** +-=---------------------------------------------------------Mo 29. Okt 11:59:52 2012----------*
 * @method  CoeTextEdit::DoConnections                       // private                           *
 * @return  void                                             //                                   *
 * @param   QTextEdit* pqteEdit                              //                                   *
 * @comment This method connects the textedit with the several slots.                             *
 *----------------last changed: --------------------------------Mo 29. Okt 11:59:52 2012----------*/
void CoeTextEdit::DoConnections(QTextEdit* pqteEdit)
{
    connect( pqteEdit,
             SIGNAL( currentFontChanged( const QFont & ) ),
             this,
             SLOT( FontChanged( const QFont & ) ) );

    connect( pqteEdit,
             SIGNAL( currentColorChanged( const QColor & ) ),
             this,
             SLOT( ColorChanged( const QColor & ) ) );

    connect( pqteEdit,
             SIGNAL( currentAlignmentChanged( int ) ),
             this,
             SLOT( AlignmentChanged( int ) ) );
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::FileSave                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This message saves the file.                                                          *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::FileSave(  )
{
    if ( m_pqteEdit )
    {
       QString fn;
       QFile file( m_qstrFilename );
       
       if ( !file.open( QIODevice::WriteOnly ) )
       {
          return;
       }
       
       QTextStream ts( &file );
       ts << m_pqteEdit->toHtml();
    }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::FilePrint                           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This message prints the file.                                                         *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::FilePrint(  )
{
#ifndef QT_NO_PRINTER
   QPrinter printer(QPrinter::HighResolution);
   QPrintDialog *dlg = new QPrintDialog(&printer, this);
   if (m_pqteEdit->textCursor().hasSelection())
      dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
   dlg->setWindowTitle(tr("Print Document"));
   if (dlg->exec() == QDialog::Accepted) {
      m_pqteEdit->print(&printer);
   }
   delete dlg;
#endif //
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::FileExit                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method exits the Editor.                                                         *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::FileExit(  )
{
   hide();
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::EditUndo                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method undo`s the last edit step.                                                *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::EditUndo(  )
{
   if ( m_pqteEdit )
   {
      m_pqteEdit->undo();
   }
   
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::EditRedo                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method redo`s the last edit step.                                                *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::EditRedo(  )
{
   if ( m_pqteEdit )
   {
      m_pqteEdit->redo();
   }
   
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::EditCut                             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method cuts the selection from editor.                                           *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::EditCut(  )
{
    if ( m_pqteEdit )
    {
       m_pqteEdit->cut();
    }
    
}
/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::EditCopy                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method copies the selected text.                                                 *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::EditCopy(  )
{
   if ( m_pqteEdit )
	{
      m_pqteEdit->copy();
   }
   
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::EditPaste                           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method inserts copied text.                                                      *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::EditPaste(  )
{
   if (m_pqteEdit)
	{
      m_pqteEdit->paste();
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextBold                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot changed the marked text to bold font.                                       *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextBold(  )
{
   QTextCharFormat fmt;
   fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
   MergeFormatOnWordOrSelection(fmt);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextUnderline                       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method underlines the marked text.                                               *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextUnderline(  )
{
   QTextCharFormat fmt;
   fmt.setFontUnderline(actionTextUnderline->isChecked());
   MergeFormatOnWordOrSelection(fmt);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextItalic                          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method sets the marked text to italic font.                                      *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextItalic(  )
{
   QTextCharFormat fmt;
   fmt.setFontItalic(actionTextItalic->isChecked());
   MergeFormatOnWordOrSelection(fmt);
}

/** +-=---------------------------------------------------------Mo 29. Okt 13:34:09 2012----------*
 * @method  CoeTextEdit::MergeFormatOnWordOrSelection        // private                           *
 * @return  void                                             //                                   *
 * @param   const QTextCharFormat &format                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 13:34:09 2012----------*/
void CoeTextEdit::MergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
   QTextCursor cursor = m_pqteEdit->textCursor();

   if (!cursor.hasSelection())
   {
      cursor.select(QTextCursor::WordUnderCursor);
   }

   cursor.mergeCharFormat(format);
   m_pqteEdit->mergeCurrentCharFormat(format);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextFamily                          // private, slots                    *
 * @return  void                                             //                                   *
 * @param   const QString & p_qstrFamily                     //                                   *
 * @comment This method sets the marked text to the font family p_qstrFamily.                     *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextFamily(  const QString & p_qstrFamily )
{
   QTextCharFormat fmt;
   fmt.setFontFamily(p_qstrFamily);
   MergeFormatOnWordOrSelection(fmt);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextSize                            // private, slots                    *
 * @return  void                                             //                                   *
 * @param   const QString & p_qstrSize                       //                                   *
 * @comment This method sets the textsize of the marked text.                                     *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextSize(  const QString & p_qstrSize )
{
   qreal pointSize = p_qstrSize.toFloat();

   if (p_qstrSize.toFloat() > 0) 
   {
      QTextCharFormat fmt;
      fmt.setFontPointSize(pointSize);
      MergeFormatOnWordOrSelection(fmt);
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextStyle                           // private, slots                    *
 * @return  void                                             //                                   *
 * @param   int p_iStyle                                     //                                   *
 * @comment This method sets the textstyle p_iStyle to the marked text.                           *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextStyle(  int p_iStyle )
{
   QTextCursor cursor = m_pqteEdit->textCursor();

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
          case 7:
             style = QTextListFormat::ListLowerRoman;
             break;
          case 8:
             style = QTextListFormat::ListUpperRoman;
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

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextColor                           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method sets the textcolor if the marked text.                                    *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextColor(  )
{
   if (m_pqteEdit)
   {
      QColor col = QColorDialog::getColor(m_pqteEdit->textColor(), this);
      if (!col.isValid())
      {
         return;
      }

      QTextCharFormat fmt;
      fmt.setForeground(col);
      MergeFormatOnWordOrSelection(fmt);
      ColorChanged(col);
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TextAlign                           // private, slots                    *
 * @return  void                                             //                                   *
 * @param   QAction* p_pqaAction                             //                                   *
 * @comment This method sets the action text alignment to the marked text.                        *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TextAlign(  QAction* p_pqaAction )
{
   if (m_pqteEdit)
   {
      if (p_pqaAction == actionAlignLeft)
         m_pqteEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
      else if (p_pqaAction == actionAlignCenter)
         m_pqteEdit->setAlignment(Qt::AlignHCenter);
      else if (p_pqaAction == actionAlignRight)
         m_pqteEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
      else if (p_pqaAction == actionAlignJustify)
         m_pqteEdit->setAlignment(Qt::AlignJustify);
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::FontChanged                         // private, slots                    *
 * @return  void                                             //                                   *
 * @param   const QFont & p_qfFont                           //                                   *
 * @comment This slot will be called if the font was changed.                                     *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::FontChanged(  const QFont & p_qfFont )
{
   comboFont->setCurrentIndex(comboFont->findText(QFontInfo(p_qfFont).family()));
   comboSize->setCurrentIndex(comboSize->findText(QString::number(p_qfFont.pointSize())));
   actionTextBold->setChecked(p_qfFont.bold());
   actionTextItalic->setChecked(p_qfFont.italic());
   actionTextUnderline->setChecked(p_qfFont.underline());
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::ColorChanged                        // private, slots                    *
 * @return  void                                             //                                   *
 * @param   const QColor & p_qcColor                         //                                   *
 * @comment This method will be called if the color was changed.                                  *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::ColorChanged(  const QColor & p_qcColor )
{
   QPixmap pix(16, 16);
   pix.fill(p_qcColor);
   actionTextColor->setIcon(pix);
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::AlignmentChanged                    // private, slots                    *
 * @return  void                                             //                                   *
 * @param   int p_iAlignment                                 //                                   *
 * @comment This slot will be called if the Alignment of text was changed.                        *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::AlignmentChanged(  int p_iAlignment )
{
   if (p_iAlignment & Qt::AlignLeft) {
      actionAlignLeft->setChecked(true);
   } else if (p_iAlignment & Qt::AlignHCenter) {
      actionAlignCenter->setChecked(true);
   } else if (p_iAlignment & Qt::AlignRight) {
      actionAlignRight->setChecked(true);
   } else if (p_iAlignment & Qt::AlignJustify) {
      actionAlignJustify->setChecked(true);
   }
}

/** +-=-------------------------------------------------------------------------------------------*
 * @method  CoeTextEdit::TableCellEdit                       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called to edit a Table Cell in a own small editor.                  *
 *------------------------------------------------------------------------------------------------*/
void CoeTextEdit::TableCellEdit(  )
{
   if ( m_pqteEdit )
   {
      QTextCursor cursor = m_pqteEdit->textCursor();
   }
}

/** +-=---------------------------------------------------------Di 18. Jan 08:49:07 2005----------*
 * @method  CoeTextEdit::SetDefaultFontType                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFontType                           //                                   *
 * @comment sets the default fonttype for the textedit widget.                                    *
 *----------------last changed: --------------------------------Di 18. Jan 08:49:07 2005----------*/
void CoeTextEdit::SetDefaultFontType(  QString p_qstrFontType )
{
   comboFont->lineEdit()->setText(p_qstrFontType);
   TextFamily(p_qstrFontType);
}

/** +-=---------------------------------------------------------Di 18. Jan 08:49:39 2005----------*
 * @method  CoeTextEdit::SetDefaultFontSize                  // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iFontSize                                  //                                   *
 * @comment This method sets the default fontsize of the textedit.                                *
 *----------------last changed: --------------------------------Di 18. Jan 08:49:39 2005----------*/
void CoeTextEdit::SetDefaultFontSize(  int p_iFontSize )
{
   comboSize->lineEdit()->setText(QString::number(p_iFontSize));
   TextSize(QString::number(p_iFontSize));
}


/** +-=---------------------------------------------------------Mi 10. Sep 09:45:04 2003----------*
 * @method  CoeTextEdit::ModifiedSlot                        // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the textchanged signal was emitted. it emits the modified signal, for other moduls.*
 *----------------last changed: Wolfgang Graßhof----------------Mi 10. Sep 09:45:04 2003----------*/
void CoeTextEdit::ModifiedSlot(  )
{
   emit ModifiedSignal();
}

/** +-=---------------------------------------------------------So 20. Nov 10:08:14 2005----------*
 * @method  CoeTextEdit::FontDialog                          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to call the font dialog.                   *
 *----------------last changed: --------------------------------So 20. Nov 10:08:14 2005----------*/
void CoeTextEdit::FontDialog(  )
{
   QFont qfFont = m_pqteEdit->currentFont();
   bool bOk = false;

   QFont qfNewFont = QFontDialog::getFont(&bOk, qfFont, this);  

   if(bOk)
   {
      m_pqteEdit->setCurrentFont(qfNewFont);
   }
}

/** +-=---------------------------------------------------------Mi 10. Sep 09:45:32 2003----------*
 * @method  CoeTextEdit::ModifiedSignal                      // private, signals                  *
 * @return  void                                             //                                   *
 * @comment This signal will be emitted if modification are made in the text.                     *
 *----------------last changed: Wolfgang Graßhof----------------Mi 10. Sep 09:45:32 2003----------*/

