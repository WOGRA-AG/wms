/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsGroupEditorDlg.h
 ** Started Implementation: 2012/08/17
 ** Description:
 ** 
 ** implements the editor for groups
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSGROUPEDITORDLG_H
#define CWMSGROUPEDITORDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "ui_CwmsGroupEditorDlg.h"

// Forwards
class CdmClassGroup;

// TypeDefs


/* 
 * This class implements the editor for groups
 */
class CwmsGroupEditorDlg : public QDialog, public Ui::CwmsGroupEditorDlgClass
{
   Q_OBJECT

   private:
      CdmClassGroup* m_rpCdmGroup;

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:09:25 2012-------*
    * @method  CwmsGroupEditorDlg::CwmsGroupEditorDlg        // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:09:25 2012----------*/
    CwmsGroupEditorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:10:01 2012-------*
    * @method  CwmsGroupEditorDlg::~CwmsGroupEditorDlg       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsGroupEditorDlg                                         *
    *----------------last changed: -----------------------------Fr 17. Aug 14:10:01 2012----------*/
    virtual ~CwmsGroupEditorDlg( );

   public:
   /** +-=---------------------------------------------------------Mo 20. Aug 15:36:16 2012-------*
    * @method  CwmsGroupEditorDlg::FillDialog                // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClassGroup* p_pCdmGroup                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 15:36:16 2012----------*/
    void FillDialog(CdmClassGroup* p_pCdmGroup);

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:21:22 2012-------*
    * @method  CwmsGroupEditorDlg::OKClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:21:22 2012----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:21:33 2012-------*
    * @method  CwmsGroupEditorDlg::Validate                  // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:21:33 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:22:04 2012-------*
    * @method  CwmsGroupEditorDlg::SaveData                  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:22:04 2012----------*/
    void SaveData();


    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:45:05 2012-------*
    * @method  CwmsGroupEditorDlg::AddTranslationClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:45:05 2012----------*/
void AddTranslationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:45:16 2012-------*
    * @method  CwmsGroupEditorDlg::EditTranslationClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:45:16 2012----------*/
void EditTranslationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 14:45:26 2012-------*
    * @method  CwmsGroupEditorDlg::RemoveTranslationClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 14:45:26 2012----------*/
void RemoveTranslationClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 20. Aug 15:21:47 2012-------*
    * @method  CwmsGroupEditorDlg::GetSelectedTranslationItem // private                          *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 15:21:47 2012----------*/
    QTreeWidgetItem* GetSelectedTranslationItem();

   private:
   /** +-=---------------------------------------------------------Mo 20. Aug 15:35:12 2012-------*
    * @method  CwmsGroupEditorDlg::FillTranslations          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 15:35:12 2012----------*/
    void FillTranslations();

    private slots:
   /** +-=---------------------------------------------------------Mi 22. Aug 16:46:28 2012-------*
    * @method  CwmsGroupEditorDlg::RightsClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 16:46:28 2012----------*/
void RightsClickedSlot( );
};

#endif // CWMSGROUPEDITORDLG_H
