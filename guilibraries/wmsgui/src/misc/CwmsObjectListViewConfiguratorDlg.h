/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsObjectListViewConfiguratorDlg.h
 ** Started Implementation: 2010/05/18
 ** Description:
 ** 
 ** Implements the configurator for the listview
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSOBJECTLISTVIEWCONFIGURATORDLG_H
#define CWMSOBJECTLISTVIEWCONFIGURATORDLG_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes
#include <QDialog>
#include <QMap>

// Own Includes
#include "ui_CwmsObjectListViewConfiguratorDlg.h"


// Forwards
class CwmsObjectListListViewConfigurator;
class CdmMember;
class CdmClass;

// Enumerations

/* 
 * This class implements the configurator for the listview
 */
class CwmsObjectListViewConfiguratorDlg : public QDialog, public Ui::CwmsObjectListViewConfiguratorDlgClass
{
   Q_OBJECT

   private:
      CwmsObjectListListViewConfigurator* m_rpCwmsConfig;

   public:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:32:26 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::CwmsObjectListViewConfiguratorDlg // public     *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:32:26 2010----------*/
    CwmsObjectListViewConfiguratorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Fr 21. Mai 17:36:55 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::~CwmsObjectListViewConfiguratorDlg // public, virtual*
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectListViewConfiguratorDlg                          *
    *----------------last changed: -----------------------------Fr 21. Mai 17:36:55 2010----------*/
    virtual ~CwmsObjectListViewConfiguratorDlg( );

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:46:36 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::FillDialog // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsObjectListListViewConfigurator* p_pCwmsConfig//                                *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:46:36 2010----------*/
    void FillDialog(CwmsObjectListListViewConfigurator* p_pCwmsConfig);

   private:
   /** +-=---------------------------------------------------------So 28. Okt 11:05:24 2012-------*
    * @method  CwmsObjectListViewConfiguratorDlg::FillChildMembers // private                     *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QTreeWidgetItem* p_pqlvItem                   //                                   *
    * @param   int p_iDepth                                  //                                   *
    * @param   CdmClass* p_pCdmRequestClass                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 28. Okt 11:05:24 2012----------*/
    void FillChildMembers(CdmMember* p_pCdmMember,
                          QTreeWidgetItem* p_pqlvItem,
                          int p_iDepth,
                          CdmClass* p_pCdmRequestClass);

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 18:07:17 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::FillSourceListView // private                   *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 18:07:17 2010----------*/
    void FillSourceListView(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Mo 24. Mai 10:27:38 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::FillTargetListView // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 24. Mai 10:27:38 2010----------*/
    void FillTargetListView();

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 18:47:18 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::AddDisplayItem // private                       *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 18:47:18 2010----------*/
    void AddDisplayItem(QString p_qstrKeyname);

    private slots:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:09:45 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::AddColumnClickedSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:09:45 2010----------*/
void AddColumnClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:09:56 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::RemoveColumnClickedSlot // private, slots       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:09:56 2010----------*/
void RemoveColumnClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:10:23 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::UpClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:10:23 2010----------*/
void UpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:10:37 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::DownClickedSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:10:37 2010----------*/
void DownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:11:02 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::ChangeNameClickedSlot // private, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:11:02 2010----------*/
void ChangeNameClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 19:11:31 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::SaveData   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 19:11:31 2010----------*/
    void SaveData();

   public:
   /** +-=---------------------------------------------------------So 23. Mai 09:54:35 2010-------*
    * @method  CwmsObjectListViewConfiguratorDlg::EditColumnConfiguration // public, static       *
    * @return  void                                          //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @param   CwmsObjectListListViewConfigurator* p_pCwmsConfig//                                *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 09:54:35 2010----------*/
    static void EditColumnConfiguration(QWidget* p_pqwParent,
                                        CwmsObjectListListViewConfigurator* p_pCwmsConfig);
};

#endif
