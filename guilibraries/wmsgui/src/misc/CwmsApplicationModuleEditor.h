/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsApplicationModuleEditor.h
 ** Started Implementation: 2012/08/31
 ** Description:
 ** 
 ** implements the editor for application modules
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSAPPLICATIONMODULEEDITOR_H
#define CWMSAPPLICATIONMODULEEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>
#include <QByteArray>

// Own Includes
#include "wmsgui.h"
#include "CwmsApplicationModule.h"
#include "ui_CwmsApplicationModuleEditor.h"

// Forwards
class CdmObject;
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the editor for application modules
 */
class CwmsApplicationModuleEditor : public QDialog, Ui::CwmsApplicationModuleEditorClass
{
   Q_OBJECT

   private:
      CdmObject* m_rpCdmForm;
      CdmObject* m_rpCdmView;
      CdmObject* m_rpCdmData;
      CdmObjectContainer* m_rpCdmDataOL;
      CwmsApplicationModule m_cModule;
      QByteArray m_qbaIcon;
      QString m_qstrIconName;

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:18:02 2012--------*
    * @method  CwmsApplicationModuleEditor::CwmsApplicationModuleEditor // public                 *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:18:02 2012-----------*/
    CwmsApplicationModuleEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:18:20 2012--------*
    * @method  CwmsApplicationModuleEditor::~CwmsApplicationModuleEditor // public, virtual       *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsApplicationModuleEditor                                *
    *----------------last changed: -----------------------------Mo 3. Sep 17:18:20 2012-----------*/
    virtual ~CwmsApplicationModuleEditor( );

   private:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:18:49 2012--------*
    * @method  CwmsApplicationModuleEditor::FillDialog       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:18:49 2012-----------*/
    void FillDialog(CwmsApplicationModule p_cModule);

    private slots:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:24:17 2012--------*
    * @method  CwmsApplicationModuleEditor::SelectDataClickedSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:24:17 2012-----------*/
void SelectDataClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:24:31 2012--------*
    * @method  CwmsApplicationModuleEditor::SelectFormClickedSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:24:31 2012-----------*/
void SelectFormClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:24:45 2012--------*
    * @method  CwmsApplicationModuleEditor::SelectViewClickedSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:24:45 2012-----------*/
void SelectViewClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:24:57 2012--------*
    * @method  CwmsApplicationModuleEditor::OKClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:24:57 2012-----------*/
void OKClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 18:39:11 2012--------*
    * @method  CwmsApplicationModuleEditor::EditModule       // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 18:39:11 2012-----------*/
    static void EditModule(CwmsApplicationModule p_cModule, bool p_bNew, QWidget* p_pqwParent);

   private:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:27:23 2012--------*
    * @method  CwmsApplicationModuleEditor::Validate         // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:27:23 2012-----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Mo 3. Sep 17:27:32 2012--------*
    * @method  CwmsApplicationModuleEditor::SaveData         // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 17:27:32 2012-----------*/
    void SaveData(bool p_bNew);

    private slots:
    void SelectIconClickedSlot();
	void DeleteDataClickedSlot();
	void DeleteFormClickedSlot();
	void DeleteViewClickedSlot();
};

#endif // CWMSAPPLICATIONMODULEEDITOR_H
