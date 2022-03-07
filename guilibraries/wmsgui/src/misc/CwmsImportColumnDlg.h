/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportColumnDlg.h
 ** Started Implementation: 2008/10/26
 ** Description:
 ** 
 ** This class implements the dialog for defning columns for the import.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORTCOLUMNDLG_H
#define CWMSIMPORTCOLUMNDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>


// Own Includes
#include "ui_CwmsImportColumnDlg.h"



// Forwards
class CdmClass;
class CwmsImport;
class CdmMember;
class CwmsImportSettingsColumn;

// Enumerations

// namespaces
using namespace Ui;


/* 
 * This class implements the dialog for defning columns for the import.
 */
class CwmsImportColumnDlg : public QDialog, public CwmsImportColumnDlgClass
{
    Q_OBJECT


   public:
   /** +-=---------------------------------------------------------So 26. Okt 13:07:51 2008-------*
    * @method  CwmsImportColumnDlg::CwmsImportColumnDlg      // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------So 26. Okt 13:07:51 2008----------*/
    CwmsImportColumnDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------So 26. Okt 13:08:10 2008-------*
    * @method  CwmsImportColumnDlg::~CwmsImportColumnDlg     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImportColumnDlg                                        *
    *----------------last changed: -----------------------------So 26. Okt 13:08:10 2008----------*/
    virtual ~CwmsImportColumnDlg( );


    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 13:09:13 2008-------*
    * @method  CwmsImportColumnDlg::CancelClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 13:09:13 2008----------*/
void CancelClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------So 26. Okt 13:09:24 2008-------*
    * @method  CwmsImportColumnDlg::OKClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 13:09:24 2008----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:04:34 2013-------*
    * @method  CwmsImportColumnDlg::FillMemberListView       // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmClass* p_pCdmClass                   //                                   *
    * @param   CwmsImport* p_pCwmsImport                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:04:34 2013----------*/
    void FillMemberListView(const CdmClass* p_pCdmClass, CwmsImport* p_pCwmsImport);

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:19:33 2013-------*
    * @method  CwmsImportColumnDlg::FillChildMembers         // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QTreeWidgetItem* p_pqlvItem                   //                                   *
    * @param   int p_iDepth                                  //                                   *
    * @param   const CdmClass* p_pCdmRequestClass            //                                   *
    * @param   CwmsImport* p_pCwmsImport                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:19:33 2013----------*/
    void FillChildMembers(CdmMember* p_pCdmMember,
                          QTreeWidgetItem* p_pqlvItem,
                          int p_iDepth,
                          const CdmClass* p_pCdmRequestClass,
                          CwmsImport* p_pCwmsImport);

   public:
   /** +-=---------------------------------------------------------So 26. Okt 14:13:45 2008-------*
    * @method  CwmsImportColumnDlg::GetColumnSetttings       // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsImportSettingsColumn* p_pColumn           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 14:13:45 2008----------*/
    void GetColumnSetttings(CwmsImportSettingsColumn* p_pColumn);

   public:
   /** +-=---------------------------------------------------------Mo 27. Okt 17:36:47 2008-------*
    * @method  CwmsImportColumnDlg::GetSelectedMember        // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Okt 17:36:47 2008----------*/
    QString GetSelectedMember();
};

#endif // // CWMSIMPORTCOLUMNDLG_H
