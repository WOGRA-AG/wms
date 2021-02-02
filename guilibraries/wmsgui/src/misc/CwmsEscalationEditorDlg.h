/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsEscalationEditorDlg.h
 ** Started Implementation: 2012/10/10
 ** Description:
 ** 
 ** implements the editor for escalations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSESCALATIONEDITORDLG_H
#define CWMSESCALATIONEDITORDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS BASETOOLS Includes
#include "CwmsEscalation.h"

// Own Includes
#include "IwmsObjectEditorDescriptor.h"
#include "ui_CwmsEscalationEditorDlg.h"

// Forwards


// TypeDefs


/* 
 * This class implements the escalation editor
 */
class WMSGUI_API CwmsEscalationEditorDlg : public QDialog, public Ui::CwmsEscalationEditorDlgClass
{
   Q_OBJECT

   private:
      CwmsEscalation m_cEscalation;
      bool m_bNew;

   public:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:32:19 2012-------*
    * @method  CwmsEscalationEditorDlg::CwmsEscalationEditorDlg // public                           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:32:19 2012----------*/
    CwmsEscalationEditorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:34:28 2012-------*
    * @method  CwmsEscalationEditorDlg::~CwmsEscalationEditorDlg // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsEscalationEditorDlg                                     *
    *----------------last changed: -----------------------------Mi 10. Okt 13:34:28 2012----------*/
    virtual ~CwmsEscalationEditorDlg( );

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 14:52:48 2012-------*
    * @method  CwmsEscalationEditorDlg::FillDialog           // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsEscalation p_cEscalation                  //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 14:52:48 2012----------*/
    void FillDialog(CwmsEscalation p_cEscalation, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:35:26 2012-------*
    * @method  CwmsEscalationEditorDlg::Validate              // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:35:26 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:36:01 2012-------*
    * @method  CwmsEscalationEditorDlg::SaveData              // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:36:01 2012----------*/
    void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mi 10. Okt 13:36:15 2012-------*
    * @method  CwmsEscalationEditorDlg::OKClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 13:36:15 2012----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 14:52:25 2012-------*
    * @method  CwmsEscalationEditorDlg::Edit                 // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CwmsEscalation p_cEscalation                  //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 14:52:25 2012----------*/
    static bool Edit(CwmsEscalation p_cEscalation, bool p_bNew, QWidget* p_pqwParent);

    private slots:
   /** +-=---------------------------------------------------------Do 11. Okt 09:43:56 2012-------*
    * @method  CwmsEscalationEditorDlg::AddEmployeeClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Okt 09:43:56 2012----------*/
void AddEmployeeClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 11. Okt 09:44:06 2012-------*
    * @method  CwmsEscalationEditorDlg::RemoveEmployeeClickedSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Okt 09:44:06 2012----------*/
void RemoveEmployeeClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mi 10. Okt 18:07:02 2012-------*
    * @method  CwmsEscalationEditorDlg::FillEmployees         // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 18:07:02 2012----------*/
    void FillEmployees();


   private:
   /** +-=---------------------------------------------------------Mi 10. Okt 18:21:02 2012-------*
    * @method  CwmsEscalationEditorDlg::AddUserToTree         // private                           *
    * @return  void                                          //                                   *
    * @param   CumUser* p_pCumUser                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Okt 18:21:02 2012----------*/
    void AddUserToTree(CumUser* p_pCumUser);
};


class WMSGUI_API CwmsEscalationObjectEditorDescriptor : public IwmsObjectEditorDescriptor
{


   public:
   /** +-=---------------------------------------------------------So 30. Dez 14:24:35 2012-------*
    * @method  CwmsEscalationObjectEditorDescriptor::GetClassKeyname // public                    *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 14:24:35 2012----------*/
    QString GetClassKeyname();

   protected:
   /** +-=---------------------------------------------------------So 30. Dez 14:24:40 2012-------*
    * @method  CwmsEscalationObjectEditorDescriptor::DisplayEditor // protected                   *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 14:24:40 2012----------*/
    bool DisplayEditor(CdmObject* p_pCdmObject,
                       EwmsGuiDisplayMode p_eDisplayMode,
                       QWidget* p_pqwParent);
};

#endif // CBGESCALATIONEDITORDLG_H
