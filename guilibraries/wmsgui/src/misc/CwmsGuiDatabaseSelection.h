/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CbgMandatorSelectionIf.h
 ** Started Implementation: 14.7.2005
 ** Description:
 ** Implements the selection dlg for databases
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSDATABASESELECTION_H
#define CWMSDATABASESELECTION_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes
#include <QDialog>


// WMS Includes


// own Includes
#include "wmsgui.h"
#include "ui_CwmsDatabaseSelection.h"


class WMSGUI_API CwmsGuiDatabaseSelection : public QDialog, public Ui::CwmsDatabaseSelectionClass
{
   Q_OBJECT

   private:
      bool m_bNeedToShow;

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 14:26:47 2012--------*
    * @method  CwmsDatabaseSelection::CwmsDatabaseSelection  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment The constructor of the chosse mandatorif class it initializes the members.         *
    *----------------last changed: -----------------------------Di 4. Sep 14:26:47 2012-----------*/
    CwmsGuiDatabaseSelection( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 14:26:57 2012--------*
    * @method  CwmsDatabaseSelection::~CwmsDatabaseSelection // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CfbChooseMandatorIf                                        *
    *----------------last changed: -----------------------------Di 4. Sep 14:26:57 2012-----------*/
    virtual ~CwmsGuiDatabaseSelection( );

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 14:27:10 2012--------*
    * @method  CwmsDatabaseSelection::FillDialog             // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog with the mandators.                                   *
    *----------------last changed: -----------------------------Di 4. Sep 14:27:10 2012-----------*/
	   void FillDialog(QList<QString>& p_rqllDatabases);

    private slots:
   /** +-=---------------------------------------------------------Di 4. Sep 14:28:07 2012--------*
    * @method  CwmsDatabaseSelection::ListBoxDoubleClickedSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment This slot will be called if a mandator is double clicked by the listbox.           *
    *----------------last changed: -----------------------------Di 4. Sep 14:28:07 2012-----------*/
void ListBoxDoubleClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 4. Sep 14:29:02 2012--------*
    * @method  CwmsDatabaseSelection::CancelClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to cancel this application.             *
    *----------------last changed: -----------------------------Di 4. Sep 14:29:02 2012-----------*/
void CancelClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 4. Sep 14:29:12 2012--------*
    * @method  CwmsDatabaseSelection::OKClickedSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the ok button was clicked.                             *
    *----------------last changed: -----------------------------Di 4. Sep 14:29:12 2012-----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Di 4. Sep 14:31:29 2012--------*
    * @method  CwmsDatabaseSelection::GetSelectedItem        // private                           *
    * @return  QListWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 14:31:29 2012-----------*/
    QListWidgetItem* GetSelectedItem();

   private:
   /** +-=---------------------------------------------------------Di 4. Sep 15:17:02 2012--------*
    * @method  CwmsDatabaseSelection::LoadDatabase           // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDataabse                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 15:17:02 2012-----------*/
    void LoadScheme(QString p_qstrDataabse);
};

#endif
