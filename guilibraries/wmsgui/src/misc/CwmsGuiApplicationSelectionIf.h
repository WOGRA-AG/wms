/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsApplicationSelectionIf.h
 ** Started Implementation: 2008/05/18
 ** Description:
 ** 
 ** the interface for the application selection dlg
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSAPPLICATIONSELECTIONIF_H
#define CWMSAPPLICATIONSELECTIONIF_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes
#include <QDialog>

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsApplicationSelectionDlg.h"


// Forwards


// Enumerations

/* 
 * This class implements the interface for the application selection dlg
 */
class WMSGUI_API CwmsGuiApplicationSelectionIf : public QDialog, public Ui::CwmsApplicationSelectionDlg
{
   Q_OBJECT

   private:
      QString m_qstrApplicationName;
   

   public:
   /** +-=---------------------------------------------------------Di 28. Sep 08:15:10 2010-------*
    * @method  CwmsApplicationSelectionIf::CwmsApplicationSelectionIf // public                   *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @param   Qt::WFlags fl = 0                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 08:15:10 2010----------*/
    CwmsGuiApplicationSelectionIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 26. Nov 19:30:04 2008-------*
    * @method  CwmsApplicationSelectionIf::~CwmsApplicationSelectionIf // public, virtual         *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsApplicationSelectionIf                                 *
    *----------------last changed: -----------------------------Mi 26. Nov 19:30:04 2008----------*/
    virtual ~CwmsGuiApplicationSelectionIf( );

   public:
   /** +-=---------------------------------------------------------So 18. Mai 12:00:36 2008-------*
    * @method  CwmsApplicationSelectionIf::GetApplicationString // public, static                 *
    * @return  QString                                       //                                   *
    * @comment returns the application string which was selected by te user.                      *
    *----------------last changed: -----------------------------So 18. Mai 12:00:36 2008----------*/
    static QString GetApplicationString();

    private slots:
   /** +-=---------------------------------------------------------Mi 26. Nov 20:11:01 2008-------*
    * @method  CwmsApplicationSelectionIf::FillDialog        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 26. Nov 20:11:01 2008----------*/
void FillDialog( );


};

#endif
