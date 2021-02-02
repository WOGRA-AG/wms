/******************************************************************************
 ** WOGRA Middleware Server GUI Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSERRORIF_H
#define CWMSERRORIF_H

// System and QT Includes
#include <qmap.h>

// own Includes
#include "wmsgui.h"
#include "CdmLoggingAdaptor.h"
#include "ui_CwmsErrorDlg.h"

// forwards


class WMSGUI_API CwmsErrorIf : public QDialog, public Ui::CwmsErrorDlg, public CdmLoggingAdaptor
{

   Q_OBJECT

   private:
      int m_iInfoMessageCount;
      int m_iWarningMessageCount;
      int m_iErrorMessageCount;
      int m_iFatalMessageCount;
      /*
       * This map stores the settings for the fileseverity
       * <Filename,Severity>
       */
      QMap<QString,int> m_qmDisplayFilesSeverity;
 

   public:
   /** +-=---------------------------------------------------------Di 28. Sep 14:36:13 2010-------*
    * @method  CwmsErrorIf::CwmsErrorIf                      // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 14:36:13 2010----------*/
    CwmsErrorIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 20:26:31 2007--------*
    * @method  CwmsErrorIf::~CwmsErrorIf                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsErrorIf                                                *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 20:26:31 2007-----------*/
    virtual ~CwmsErrorIf( );

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:19:51 2007--------*
    * @method  CwmsErrorIf::AddError                         // public                            *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:19:51 2007-----------*/
    void AddError(CdmLogEntry& p_Entry);

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:20:00 2007--------*
    * @method  CwmsErrorIf::AddInfo                          // public                            *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:20:00 2007-----------*/
    void AddInfo(CdmLogEntry& p_Entry);

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:20:10 2007--------*
    * @method  CwmsErrorIf::AddWarning                       // public                            *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:20:10 2007-----------*/
    void AddWarning(CdmLogEntry& p_Entry);

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:20:19 2007--------*
    * @method  CwmsErrorIf::AddFatal                         // public                            *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:20:19 2007-----------*/
    void AddFatal(CdmLogEntry& p_Entry);

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 20:27:59 2007--------*
    * @method  CwmsErrorIf::AddErrorCode                     // public                            *
    * @return  void                                          //                                   *
    * @param   QDateTime p_qdtTimeStamp                      //                                   *
    * @param   int p_iCode                                   //                                   *
    * @comment This method adds an error code to the adaptor.                                     *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 20:27:59 2007-----------*/
    void AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode);


   public:
   /** +-=---------------------------------------------------------Do 13. Sep 11:50:11 2012-------*
    * @method  CwmsErrorIf::SetItemVisible                   // public                            *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pqlviItem                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 11:50:11 2012----------*/
    void SetItemVisible(QTreeWidgetItem* p_pqlviItem);


   public:
   /** +-=---------------------------------------------------------Sa 7. Jul 17:40:48 2007--------*
    * @method  CwmsErrorIf::show                             // public                            *
    * @return  void                                          //                                   *
    * @comment overwritten to update some fields in the dialog.                                   *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jul 17:40:48 2007-----------*/
    void show();

   public:
   /** +-=---------------------------------------------------------Fr 27. Jul 08:31:23 2007-------*
    * @method  CwmsErrorIf::UpdateCounter                    // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 27. Jul 08:31:23 2007----------*/
    void UpdateCounter();

    protected slots:
   /** +-=---------------------------------------------------------Fr 27. Jul 08:33:52 2007-------*
    * @method  CwmsErrorIf::ConfigClickedSlot                // protected, slots                  *
    * @return  void                                          //                                   *
    * @comment This slot will be called to edit the messageconfiguration.                         *
    *----------------last changed: Wolfgang Graßhof-------------Fr 27. Jul 08:33:52 2007----------*/
void ConfigClickedSlot( );

    public slots:
         /** +-=---------------------------------------------------------Do 13. Sep 11:48:59 2012-------*
    * @method  CwmsErrorIf::ItemSelectedSlot                 // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 11:48:59 2012----------*/
void ItemSelectedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Di 8. Okt 20:31:04 2013--------*
    * @method  CwmsErrorIf::SeverityChangedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Okt 20:31:04 2013-----------*/
void SeverityChangedSlot( );
};

#endif //
