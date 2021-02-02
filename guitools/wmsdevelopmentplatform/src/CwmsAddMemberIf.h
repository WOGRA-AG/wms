/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: CwmsAddMemberIf.h
 ** Started Implementation: 2008/05/22
 ** Description:
 ** 
 ** implements the form for adding and editing members 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

#ifndef CWMSADDMEMBERIF_H
#define CWMSADDMEMBERIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// WMS Core Includes
#include "CdmMember.h"

// Own Includes
#include "ui_cwmsaddclassmemberdlg.h"


// Forwards

class CdmClass;

// Enumerations

/* 
 * This class implements ...
 */
class CwmsAddMemberIf : public QDialog, public Ui::CwmsAddClassMemberDlg
{
   Q_OBJECT

   private:
      CdmMember* m_rpCdmMember;
      CdmClass*  m_rpCdmClass;
      QString m_qstrValidationOriginalText;
      QMap<EdmValueType, int> m_qmTypeIndexMapper;


   public:
   /** +-=---------------------------------------------------------Di 21. Aug 18:20:16 2012-------*
    * @method  CwmsAddMemberIf::CwmsAddMemberIf              // public                            *
    * @return                                                //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Aug 18:20:16 2012----------*/
    CwmsAddMemberIf( CdmClass* p_pCdmClass, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Do 22. Mai 21:09:57 2008-------*
    * @method  CwmsAddMemberIf::~CwmsAddMemberIf             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsAddMemberIf                                            *
    *----------------last changed: -----------------------------Do 22. Mai 21:09:57 2008----------*/
    virtual ~CwmsAddMemberIf( );

   public:
   /** +-=---------------------------------------------------------Do 22. Mai 21:11:57 2008-------*
    * @method  CwmsAddMemberIf::SetMember                    // public                            *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment sets the member to the dialog.                                                     *
    *----------------last changed: -----------------------------Do 22. Mai 21:11:57 2008----------*/
    void SetMember(CdmMember* p_pCdmMember);

    private slots:
   /** +-=---------------------------------------------------------Do 22. Mai 21:18:04 2008-------*
    * @method  CwmsAddMemberIf::CancelClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 22. Mai 21:18:04 2008----------*/
void CancelClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 22. Mai 21:18:20 2008-------*
    * @method  CwmsAddMemberIf::OKClickedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 22. Mai 21:18:20 2008----------*/
void OKClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 23. Mai 16:39:47 2008-------*
    * @method  CwmsAddMemberIf::ClassSelectionClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to select a class reference.            *
    *----------------last changed: -----------------------------Fr 23. Mai 16:39:47 2008----------*/
void ClassSelectionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 15. Aug 14:17:37 2012-------*
    * @method  CwmsAddMemberIf::TestValidationClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 15. Aug 14:17:37 2012----------*/
void TestValidationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 15. Aug 14:18:01 2012-------*
    * @method  CwmsAddMemberIf::DataTypeSelectionChangedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 15. Aug 14:18:01 2012----------*/
void DataTypeSelectionChangedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 15. Aug 14:39:13 2012-------*
    * @method  CwmsAddMemberIf::SetSystemValuesReadOnly      // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 15. Aug 14:39:13 2012----------*/
    void SetSystemValuesReadOnly();

    private slots:
   /** +-=---------------------------------------------------------Do 16. Aug 14:54:15 2012-------*
    * @method  CwmsAddMemberIf::RightsClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:54:15 2012----------*/
void RightsClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 20. Aug 10:52:47 2012-------*
    * @method  CwmsAddMemberIf::NewTranslationClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 10:52:47 2012----------*/
void NewTranslationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 20. Aug 10:52:31 2012-------*
    * @method  CwmsAddMemberIf::EditTranslationClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 10:52:31 2012----------*/
void EditTranslationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 20. Aug 10:53:00 2012-------*
    * @method  CwmsAddMemberIf::DeleteTranslationClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 10:53:00 2012----------*/
void DeleteTranslationClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 20. Aug 10:53:11 2012-------*
    * @method  CwmsAddMemberIf::FillTranslations             // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 10:53:11 2012----------*/
    void FillTranslations();

   private:
   /** +-=---------------------------------------------------------Mo 20. Aug 13:10:56 2012-------*
    * @method  CwmsAddMemberIf::GetSelectedTranslationItem   // private                           *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 13:10:56 2012----------*/
    QTreeWidgetItem* GetSelectedTranslationItem();

   private:
   /** +-=---------------------------------------------------------Di 21. Aug 17:54:53 2012-------*
    * @method  CwmsAddMemberIf::FillGroups                   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Aug 17:54:53 2012----------*/
    void FillGroups();

   private:
   /** +-=---------------------------------------------------------Fr 16. Nov 15:38:12 2012-------*
    * @method  CwmsAddMemberIf::Validate                     // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 16. Nov 15:38:12 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 16. Nov 15:38:36 2012-------*
    * @method  CwmsAddMemberIf::SaveData                     // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 16. Nov 15:38:36 2012----------*/
    bool SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mo 10. Dez 10:49:23 2012-------*
    * @method  CwmsAddMemberIf::OwnerClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Dez 10:49:23 2012----------*/
void OwnerClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 10. Dez 11:46:21 2012-------*
    * @method  CwmsAddMemberIf::Init                         // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Dez 11:46:21 2012----------*/
    void Init();
};

#endif //
