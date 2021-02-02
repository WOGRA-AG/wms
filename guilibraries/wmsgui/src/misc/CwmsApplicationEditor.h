/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsApplicationEditor.h
 ** Started Implementation: 2012/08/30
 ** Description:
 ** 
 ** implements the editor for applications
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSAPPLICATIONEDITOR_H
#define CWMSAPPLICATIONEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmQueryModel.h"

// Own Includes
#include "wmsgui.h"
#include "CwmsApplication.h"
#include "ui_CwmsApplicationEditor.h"

// Forwards


// TypeDefs


/* 
 * This class implements the editor for applications
 */
class WMSGUI_API CwmsApplicationEditor : public QWidget, public Ui::CwmsApplicationEditorClass
{
   Q_OBJECT

   private:
      CwmsApplication m_cApp;
      CdmQueryModel m_modelModules;
      CdmQueryModel m_modelTranslations;
      CdmObject* m_rpCdmMainWindow;
      QString m_qstrIconName;
      QByteArray m_qbaIcon;

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 16:34:55 2012-------*
    * @method  CwmsApplicationEditor::CwmsApplicationEditor  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:34:55 2012----------*/
    CwmsApplicationEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 16:35:21 2012-------*
    * @method  CwmsApplicationEditor::~CwmsApplicationEditor // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsApplicationEditor                                      *
    *----------------last changed: -----------------------------Do 30. Aug 16:35:21 2012----------*/
    virtual ~CwmsApplicationEditor( );

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 16:42:29 2012-------*
    * @method  CwmsApplicationEditor::FillWidget             // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplication p_cApp                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:42:29 2012----------*/
    void FillWidget(CwmsApplication p_cApp);

public slots:
    void MoveModuleDownClickedSlot();
    void MoveModuleUpClickedSlot();
private slots:
   /** +-=---------------------------------------------------------Do 30. Aug 16:51:43 2012-------*
    * @method  CwmsApplicationEditor::EditHelpClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:51:43 2012----------*/
void EditHelpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 30. Aug 16:51:57 2012-------*
    * @method  CwmsApplicationEditor::AddModuleClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:51:57 2012----------*/
void AddModuleClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 30. Aug 16:52:09 2012-------*
    * @method  CwmsApplicationEditor::DeleteModuleClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:52:09 2012----------*/
void DeleteModuleClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 30. Aug 16:52:27 2012-------*
    * @method  CwmsApplicationEditor::CancelChangesClickedSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:52:27 2012----------*/
void CancelChangesClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 30. Aug 16:53:06 2012-------*
    * @method  CwmsApplicationEditor::UpdateApplicationClickedSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:53:06 2012----------*/
void UpdateApplicationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 30. Aug 16:53:25 2012-------*
    * @method  CwmsApplicationEditor::EditApplicationClickedSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:53:25 2012----------*/
void EditApplicationClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 30. Aug 18:22:04 2012-------*
    * @method  CwmsApplicationEditor::FillModules            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 18:22:04 2012----------*/
    void FillModules();

   private:
   /** +-=---------------------------------------------------------Fr 31. Aug 15:37:26 2012-------*
    * @method  CwmsApplicationEditor::Validate               // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 31. Aug 15:37:26 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 31. Aug 15:38:44 2012-------*
    * @method  CwmsApplicationEditor::SaveData               // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 31. Aug 15:38:44 2012----------*/
    void SaveData();

    private slots:
   /** +-=---------------------------------------------------------Di 4. Sep 10:27:49 2012--------*
    * @method  CwmsApplicationEditor::EditModuleClickedSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 10:27:49 2012-----------*/
void EditModuleClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 5. Sep 11:46:37 2012--------*
    * @method  CwmsApplicationEditor::EditLicenceClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 11:46:37 2012-----------*/
void EditLicenceClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 7. Sep 10:27:12 2012--------*
    * @method  CwmsApplicationEditor::RightsClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 10:27:12 2012-----------*/
void RightsClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 7. Sep 14:42:44 2012--------*
    * @method  CwmsApplicationEditor::FillTranslations       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 14:42:44 2012-----------*/
    void FillTranslations();

    private slots:
   /** +-=---------------------------------------------------------Fr 7. Sep 14:53:58 2012--------*
    * @method  CwmsApplicationEditor::LanguageChangedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 14:53:58 2012-----------*/
   void LanguageChangedSlot( );
   private slots:
   void SelectMainWindowClickedSlot();
   void SelectIconSlot();
};

#endif // CWMSAPPLICATIONEDITOR_H
