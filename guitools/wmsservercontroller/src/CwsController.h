/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CbmswsController.h
 ** Started Implementation: 2012/04/09
 ** Description:
 ** 
 ** Implements the user interface for the webserver
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSWSCONTROLLER_H
#define CBMSWSCONTROLLER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include "qtservice.h"

// WMS GUI Includes
#include "CwmsServerSettings.h"



// Own Includes
#include "ui_CwsController.h"

// Forwards

class QSystemTrayIcon;
class QMenu;
class QAction;

// TypeDefs


/* 
 * This class implements the user interface for the webserver
 */
class CwsController : public QDialog, public Ui::CbmswsControllerClass
{
   Q_OBJECT

   private:
      QMenu* m_pTrayIconMenu;
      QSystemTrayIcon* m_pTrayIcon;
      QAction* m_pqaStart;
      QAction* m_pqaStop;
      QAction* m_pqaConfiguration;
      QAction* m_pqaExit;
      QAction* m_pqaShowCommandWindow;
      QAction* m_pqaShowLogger;
      QtServiceController m_cController;



   public:
   /** +-=---------------------------------------------------------Di 10. Apr 08:36:32 2012-------*
    * @method  CbmswsController::CbmswsController            // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pParent                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 10. Apr 08:36:32 2012----------*/
    CwsController(QWidget* p_pParent);

    private:
    void InstallLogging();
    int ExtractSeverity( CwmsServerSettings &cSettings );



    void UpdateUiState();
public:
   /** +-=---------------------------------------------------------Di 10. Apr 08:36:39 2012-------*
    * @method  CbmswsController::~CbmswsController           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbmswsController                                           *
    *----------------last changed: -----------------------------Di 10. Apr 08:36:39 2012----------*/
    virtual ~CwsController( );

    public slots:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:45:00 2012--------*
    * @method  CbmswsController::StartClickedSlot            // public, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:45:00 2012-----------*/
void StartClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:45:11 2012--------*
    * @method  CbmswsController::StopClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:45:11 2012-----------*/
void StopClickedSlot( );


    private slots:
   /** +-=---------------------------------------------------------Do 31. Mai 08:42:10 2012-------*
    * @method  CbmswsController::QuitClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 31. Mai 08:42:10 2012----------*/
   void QuitClickedSlot( );

   public slots:
   void ConfigurationClickedSlot();
   void OpenLogFileClickedSlot();
   virtual void closeEvent(QCloseEvent *event);
   void ResumeClickedSlot();
   void PauseClickedSlot();
   void InstallClickedSlot();
   void UninstallClickedSlot();
};

#endif // CBMSWSCONTROLLER_H
