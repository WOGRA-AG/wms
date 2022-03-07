/******************************************************************************
 ** WOGRA Middleware Server Licence Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSLICENCEMANAGERIF_H
#define CWMSLICENCEMANAGERIF_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <qstring.h>
#include <QSqlDatabase>

// WMS Includes
#include "CdmSettings.h"

// own Includes
#include "wmsgui.h"
#include "ui_CwmsLicenceManagerDlg.h"

// forwards
class QSqlDatabase;

class WMSGUI_API CwmsLicenceManagerIf : public QDialog, public Ui::CwmsLicenceManagerDlg
{
   Q_OBJECT

   private:
      CdmSettings m_cCdmSettings;
      QString m_qstrSoftware;
      QSqlDatabase m_pqsqlDatabase;
      int m_iCurrentSessionId;


   public:
   /** +-=---------------------------------------------------------Di 28. Sep 14:36:53 2010-------*
    * @method  CwmsLicenceManagerIf::CwmsLicenceManagerIf    // public                            *
    * @return                                                //                                   *
    * @param   QString p_qstrSoftware                        //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 14:36:53 2010----------*/
    CwmsLicenceManagerIf( QString p_qstrSoftware, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 28. Dez 15:22:09 2005*
    * @method  CwmsLicenceManagerIf::~CwmsLicenceManagerIf   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsLicenceManagerIf                                       *
    *                                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Mi 28. Dez 15:22:09 2005----------*/
virtual ~CwmsLicenceManagerIf(  );

   private:
   /** +-=---------------------------------------------------------Mi 28. Dez 15:22:31 2005*
    * @method  CwmsLicenceManagerIf::FillDialog              // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog with the licencedata                                  *
    *----------------last changed: Wolfgang Graßhof-------------Mi 28. Dez 15:22:31 2005----------*/
void FillDialog(  );

    private slots:
   /** +-=---------------------------------------------------------Mi 28. Dez 15:36:13 2005*
    * @method  CwmsLicenceManagerIf::AddClickedSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the add button was clicked. it adds a new licence to the licencemanager.*
    *----------------last changed: Wolfgang Graßhof-------------Mi 28. Dez 15:36:13 2005----------*/
void AddClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Mi 28. Dez 15:37:15 2005*
    * @method  CwmsLicenceManagerIf::FinishSessionClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment This slot will be called to finish a session                                       *
    *----------------last changed: Wolfgang Graßhof-------------Mi 28. Dez 15:37:15 2005----------*/
void FinishSessionClickedSlot(  );

   private:
   /** +-=---------------------------------------------------------Fr 30. Dez 12:49:51 2005*
    * @method  CwmsLicenceManagerIf::InitDatabase            // private                           *
    * @return  bool                                          //                                   *
    * @comment This method inits the database.                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 30. Dez 12:49:51 2005----------*/
bool InitDatabase(  );

   private:
   /** +-=---------------------------------------------------------Mi 28. Dez 16:41:45 2005*
    * @method  CwmsLicenceManagerIf::FillSessions            // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the session lsitview.                                            *
    *----------------last changed: Wolfgang Graßhof-------------Mi 28. Dez 16:41:45 2005----------*/
void FillSessions(  );

   private:
   /** +-=---------------------------------------------------------Mi 28. Dez 16:43:38 2005*
    * @method  CwmsLicenceManagerIf::FillLicences            // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the licencelistview                                              *
    *----------------last changed: Wolfgang Graßhof-------------Mi 28. Dez 16:43:38 2005----------*/
void FillLicences(  );

   private:
   /** +-=---------------------------------------------------------Do 29. Dez 11:44:53 2005*
    * @method  CwmsLicenceManagerIf::CheckUnique             // private                           *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrSoftware                        //                                   *
    * @param   QString p_qstrLicencee                        //                                   *
    * @comment This method checks if the licence is unique.                                       *
    *----------------last changed: Wolfgang Graßhof-------------Do 29. Dez 11:44:53 2005----------*/
bool CheckUnique(  QString p_qstrSoftware, QString p_qstrLicencee );

    private slots:
   /** +-=---------------------------------------------------------Do 29. Dez 12:23:25 2005*
    * @method  CwmsLicenceManagerIf::RefreshClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method refreshes all views.                                                   *
    *----------------last changed: Wolfgang Graßhof-------------Do 29. Dez 12:23:25 2005----------*/
void RefreshClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Do 29. Dez 12:23:49 2005*
    * @method  CwmsLicenceManagerIf::DeleteLicenceClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment This method deletes the selcetd licence.                                           *
    *----------------last changed: Wolfgang Graßhof-------------Do 29. Dez 12:23:49 2005----------*/
void DeleteLicenceClickedSlot(  );


   public:
   /** +-=---------------------------------------------------------So 18. Aug 22:31:59 2013-------*
    * @method  CwmsLicenceManagerIf::CwmsLicenceManagerIf    // public                            *
    * @return                                                //                                   *
    * @param   int p_iCurrentSessionId                       //                                   *
    * @param   QString p_qstrSoftware                        //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Aug 22:31:59 2013----------*/
    CwmsLicenceManagerIf( int p_iCurrentSessionId, QString p_qstrSoftware, QWidget* parent = NULL);

    private slots:
   /** +-=---------------------------------------------------------Sa 6. Jun 19:00:19 2009--------*
    * @method  CwmsLicenceManagerIf::StopAllSessionsClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to stop all sesions.                    *
    *----------------last changed: -----------------------------Sa 6. Jun 19:00:19 2009-----------*/
void StopAllSessionsClickedSlot( );
};

#endif //
