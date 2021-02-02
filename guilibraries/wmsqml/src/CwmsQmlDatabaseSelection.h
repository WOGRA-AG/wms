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

#ifndef CWMSQMLDATABASESELECTION_H
#define CWMSQMLDATABASESELECTION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>


// WMS Includes


// own Includes
#include "wmsqml_global.h"

// Forwards
class CwmsInitApplication;

class WMSQML_EXPORT CwmsQmlDatabaseSelection : public QObject
{
   Q_OBJECT

   private:
    CwmsInitApplication* m_pInit;
      bool m_bNeedToShow;

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 14:26:47 2012--------*
    * @method  CwmsDatabaseSelection::CwmsDatabaseSelection  // public                            *
    * @return                                                //                                   *
    * @comment The constructor of the chosse mandatorif class it initializes the members.         *
    *----------------last changed: -----------------------------Di 4. Sep 14:26:47 2012-----------*/
    CwmsQmlDatabaseSelection(CwmsInitApplication* p_pInit);

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 14:26:57 2012--------*
    * @method  CwmsDatabaseSelection::~CwmsDatabaseSelection // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CfbChooseMandatorIf                                        *
    *----------------last changed: -----------------------------Di 4. Sep 14:26:57 2012-----------*/
    virtual ~CwmsQmlDatabaseSelection( );

   public:

   public slots:
   /** +-=---------------------------------------------------------Di 4. Sep 15:17:02 2012--------*
    * @method  CwmsDatabaseSelection::LoadSelection           // public slots                           *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrDatabase                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 15:17:02 2012-----------*/
    bool loadSelection(QString p_qstrDatabase);
    QStringList getDatabaseList();
    void cancel();
    void ok();
};

#endif //
