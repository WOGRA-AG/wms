/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsExportSettingsIf.h
 ** Started Implementation: 2008/04/13
 ** Description:
 ** 
 ** the dialog for the export settings.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSEXPORTSETTINGSIF_H
#define CWMSEXPORTSETTINGSIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <qdialog.h>
#include <QLinkedList>

// Own Includes
#include "ui_CwmsExportDlg.h"
#include "CwmsExportSettings.h"
#include "wmsgui.h"


// Forwards
class CdmClass;
class CdmMember; 
class CwmsSearchWidgetIf;

// Enumerations

/* 
 * This class implements the export settings dlg.
 */
class WMSGUI_API CwmsExportSettingsIf : public QDialog, public Ui::CwmsExportDlg
{
   Q_OBJECT

   private: 
      CwmsExportSettings& m_rCwmsExportSettings;
      QLinkedList<QString> m_qstrlHiddenMembers;
      QString m_qstrFilename;
      long m_lClassId;


   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 10:05:11 2012--------*
    * @method  CwmsExportSettingsIf::CwmsExportSettingsIf    // public                            *
    * @return                                                //                                   *
    * @param   CwmsExportSettings& p_rCwmsExportSettings     //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 10:05:11 2012-----------*/
    CwmsExportSettingsIf( CwmsExportSettings& p_rCwmsExportSettings, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------So 13. Apr 11:58:32 2008-------*
    * @method  CwmsExportSettingsIf::~CwmsExportSettingsIf   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsExportSettingsIf                                       *
    *----------------last changed: -----------------------------So 13. Apr 11:58:32 2008----------*/
    virtual ~CwmsExportSettingsIf( );

   public:
   /** +-=---------------------------------------------------------Mo 21. Apr 17:27:49 2008-------*
    * @method  CwmsExportSettingsIf::FillDialog              // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Apr 17:27:49 2008----------*/
    void FillDialog();

    private slots:
   /** +-=---------------------------------------------------------So 13. Apr 12:00:04 2008-------*
    * @method  CwmsExportSettingsIf::DataFormatChangedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 13. Apr 12:00:04 2008----------*/
void DataFormatChangedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 13. Apr 12:00:16 2008-------*
    * @method  CwmsExportSettingsIf::SearchClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 13. Apr 12:00:16 2008----------*/
void SearchClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 13. Apr 12:00:31 2008-------*
    * @method  CwmsExportSettingsIf::CancelClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 13. Apr 12:00:31 2008----------*/
void CancelClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 13. Apr 12:00:42 2008-------*
    * @method  CwmsExportSettingsIf::OKClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 13. Apr 12:00:42 2008----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:21:00 2013-------*
    * @method  CwmsExportSettingsIf::FillMemberListView      // private                           *
    * @return  void                                          //                                   *
    * @param   const CdmClass* p_pCdmClass                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:21:00 2013----------*/
    void FillMemberListView(const CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:31:51 2013-------*
    * @method  CwmsExportSettingsIf::FillChildMembers        // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QTreeWidgetItem* p_pqlvItem                   //                                   *
    * @param   int p_iDepth                                  //                                   *
    * @param   const CdmClass* p_pCdmRequestClass            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:31:51 2013----------*/
    void FillChildMembers(CdmMember* p_pCdmMember,
                          QTreeWidgetItem* p_pqlvItem,
                          int p_iDepth,
                          const CdmClass* p_pCdmRequestClass);



    private slots:
   /** +-=---------------------------------------------------------Do 17. Apr 23:36:23 2008-------*
    * @method  CwmsExportSettingsIf::SelectClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 17. Apr 23:36:23 2008----------*/
void SelectClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 17. Apr 23:36:36 2008-------*
    * @method  CwmsExportSettingsIf::DeselectClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 17. Apr 23:36:36 2008----------*/
void DeselectClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 21. Apr 16:49:23 2008-------*
    * @method  CwmsExportSettingsIf::AddHiddenMember         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrHiddenMember                    //                                   *
    * @comment This method adds hidden members to the list. this members won't be displayed for   *
    *----------------last changed: -----------------------------Mo 21. Apr 16:49:23 2008----------*/
    void AddHiddenMember(QString p_qstrHiddenMember);

    private slots:
   /** +-=---------------------------------------------------------Mo 21. Apr 17:08:44 2008-------*
    * @method  CwmsExportSettingsIf::UpClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Apr 17:08:44 2008----------*/
void UpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 21. Apr 17:08:36 2008-------*
    * @method  CwmsExportSettingsIf::DownClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Apr 17:08:36 2008----------*/
void DownClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 21. Apr 17:28:49 2008-------*
    * @method  CwmsExportSettingsIf::SetHiddenList           // public                            *
    * @return  void                                          //                                   *
    * @param   QValueList<QString> p_qvlHiddenMembers        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Apr 17:28:49 2008----------*/
    void SetHiddenList(QLinkedList<QString> p_qvlHiddenMembers);
    
    private slots:
   /** +-=---------------------------------------------------------Mo 21. Apr 18:05:29 2008-------*
    * @method  CwmsExportSettingsIf::SaveClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment saves the export settings.                                                         *
    *----------------last changed: -----------------------------Mo 21. Apr 18:05:29 2008----------*/
void SaveClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 21. Apr 18:05:46 2008-------*
    * @method  CwmsExportSettingsIf::LoadClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment loads the export settings from file.                                               *
    *----------------last changed: -----------------------------Mo 21. Apr 18:05:46 2008----------*/
void LoadClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 21. Apr 18:44:13 2008-------*
    * @method  CwmsExportSettingsIf::FillExportSettings      // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Apr 18:44:13 2008----------*/
    bool FillExportSettings();

    private slots:
   /** +-=---------------------------------------------------------Mi 9. Sep 18:20:53 2009--------*
    * @method  CwmsExportSettingsIf::ReduceExportSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This method opens the searchdlg to reduce the export result.                       *
    *----------------last changed: -----------------------------Mi 9. Sep 18:20:53 2009-----------*/
void ReduceExportSlot( );

   private:
   /** +-=---------------------------------------------------------Mi 9. Sep 18:29:21 2009--------*
    * @method  CwmsExportSettingsIf::ConfigureSearchWidget   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsSearchWidgetIf* p_pCwmsSearchWidget       //                                   *
    * @comment This method configures the searchwidget.                                           *
    *----------------last changed: -----------------------------Mi 9. Sep 18:29:21 2009-----------*/
    void ConfigureSearchWidget(CwmsSearchWidgetIf* p_pCwmsSearchWidget);

   private:
   /** +-=---------------------------------------------------------So 4. Nov 09:22:32 2012--------*
    * @method  CwmsExportSettingsIf::FillMembers             // private                           *
    * @return  bool                                          // Successflag                       *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 09:22:32 2012-----------*/
    bool FillMembers();
};

#endif //
