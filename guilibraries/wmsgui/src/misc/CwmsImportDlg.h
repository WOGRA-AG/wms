/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportDlg.h
 ** Started Implementation: 2008/10/25
 ** Description:
 ** 
 ** This class implements the importdlg for defining and executing the import.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORTDLG_H
#define CWMSIMPORTDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>


// Own Includes
#include "wmsgui.h"
#include "ui_CwmsImportDlg.h"



// Forwards
class CwmsImportSettings;
class CwmsImport;

// Enumerations


/* 
* This class implements the importdlg for defining and executing the import.
*/
class WMSGUI_API CwmsImportDlg : public QDialog, public Ui::CwmsImportSettingsDlg
{
    Q_OBJECT

   private:
      CwmsImportSettings* m_rpCwmsImportSettings;
      CwmsImport* m_rpCwmsImport;
     qint64 m_lClassId;
   


   public:
   /** +-=---------------------------------------------------------Mi 29. Okt 18:20:52 2008-------*
    * @method  CwmsImportDlg::CwmsImportDlg                  // public                            *
    * @return                                                //                                   *
    * @param   CwmsImportSettings* p_pImportSettings         //                                   *
    * @param   CwmsImport* p_pCwmsImport                     //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mi 29. Okt 18:20:52 2008----------*/
    CwmsImportDlg( CwmsImportSettings* p_pImportSettings,
                   CwmsImport* p_pCwmsImport,
                   QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Sa 25. Okt 11:53:02 2008-------*
    * @method  CwmsImportDlg::~CwmsImportDlg                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImportDlg                                              *
    *----------------last changed: -----------------------------Sa 25. Okt 11:53:02 2008----------*/
    virtual ~CwmsImportDlg( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:49:09 2008-------*
    * @method  CwmsImportDlg::ChooseSourceFileClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:49:09 2008----------*/
void ChooseSourceFileClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:49:36 2008-------*
    * @method  CwmsImportDlg::AddColumnClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:49:36 2008----------*/
void AddColumnClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:50:01 2008-------*
    * @method  CwmsImportDlg::RemoveColumnClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:50:01 2008----------*/
void RemoveColumnClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:50:16 2008-------*
    * @method  CwmsImportDlg::SaveClickedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:50:16 2008----------*/
void SaveClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:50:36 2008-------*
    * @method  CwmsImportDlg::LoadClickedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:50:36 2008----------*/
void LoadClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:51:11 2008-------*
    * @method  CwmsImportDlg::CancelClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:51:11 2008----------*/
void CancelClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 10:51:23 2008-------*
    * @method  CwmsImportDlg::OKClickedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 10:51:23 2008----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------So 26. Okt 11:18:31 2008-------*
    * @method  CwmsImportDlg::FillSettingsData               // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 11:18:31 2008----------*/
    void FillSettingsData();

   private:
   /** +-=---------------------------------------------------------So 26. Okt 11:44:07 2008-------*
    * @method  CwmsImportDlg::FilDialogWithSettings          // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog with the settings.                                    *
    *----------------last changed: -----------------------------So 26. Okt 11:44:07 2008----------*/
    void FilDialogWithSettings();

   private:
   /** +-=---------------------------------------------------------So 26. Okt 12:13:28 2008-------*
    * @method  CwmsImportDlg::FillListView                   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 12:13:28 2008----------*/
    void FillListView();

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 12:37:42 2008-------*
    * @method  CwmsImportDlg::MoveUpClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 12:37:42 2008----------*/
void MoveUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 12:37:56 2008-------*
    * @method  CwmsImportDlg::MoveDownClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 12:37:56 2008----------*/
void MoveDownClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 29. Okt 19:53:44 2008-------*
    * @method  CwmsImportDlg::GetSelectedItemPos             // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Okt 19:53:44 2008----------*/
    int GetSelectedItemPos();

private:
   /** +-=---------------------------------------------------------Di 4. Nov 18:00:42 2008--------*
    * @method  CwmsImportDlg::ValidateSettings               // private                           *
    * @return  bool                                          //                                   *
    * @comment This method validates the methods.                                                 *
    *----------------last changed: -----------------------------Di 4. Nov 18:00:42 2008-----------*/
    bool ValidateSettings();
};

#endif // // CWMSIMPORTDLG_H
