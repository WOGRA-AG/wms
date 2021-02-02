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

#ifndef CWMSQMLAPPLICATIONSELECTIONIF_H
#define CWMSQMLAPPLICATIONSELECTIONIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "wmsqml_global.h"


// Forwards
class CwmsInitApplication;

// Enumerations

/* 
 * This class implements the interface for the application selection dlg
 */
class WMSQML_EXPORT CwmsQmlApplicationSelection : public QObject
{
   Q_OBJECT

   private:
      CwmsInitApplication* m_pInit;
   

   public:
   /** +-=---------------------------------------------------------Di 28. Sep 08:15:10 2010-------*
    * @method  CwmsApplicationSelectionIf::CwmsApplicationSelectionIf // public                   *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 08:15:10 2010----------*/
    CwmsQmlApplicationSelection(CwmsInitApplication* p_pInit);

   public:
   /** +-=---------------------------------------------------------Mi 26. Nov 19:30:04 2008-------*
    * @method  CwmsApplicationSelectionIf::~CwmsApplicationSelectionIf // public, virtual         *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsApplicationSelectionIf                                 *
    *----------------last changed: -----------------------------Mi 26. Nov 19:30:04 2008----------*/
    virtual ~CwmsQmlApplicationSelection( );

    public:
    void selectApplication();
    void openSelectionDialog(QStringList& qstrlDatabases);

   public slots:
   /** +-=---------------------------------------------------------Di 4. Sep 15:17:02 2012--------*
    * @method  CwmsDatabaseSelection::LoadSelection           // public slots                           *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrSelection                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 15:17:02 2012-----------*/
    bool loadSelection(QString p_qstrSelection);
    void cancel();
    void ok();
};

#endif 
