/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFunctionEditor.h
 ** Started Implementation: 2012/09/20
 ** Description:
 ** 
 ** implements the function editor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSFUNCTIONEDITOR_H
#define CWMSFUNCTIONEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>

// WMS GUI Incldues
#include "IwmsSciprtEditor.h"

// Own Includes
#include "ui_CwmsFunctionEditor.h"


// Forwards
class CdmClassMethod;
class CdmClass;
class QTreeWidgetItem;

// TypeDefs


/* 
 * This class implements the function editor
 */
class CwmsFunctionEditor : public QWidget, public Ui::CwmsFunctionEditorClass, public IwmsScriptEditor
{
   Q_OBJECT

   private:
      CdmClassMethod* m_rpCdmFunction;
      CdmClass* m_rpCdmClass;
      QByteArray m_qbaIcon;
      QTreeWidgetItem* m_rpItem;
      bool m_bModified;


   public:
   /** +-=---------------------------------------------------------Do 20. Sep 14:54:01 2012-------*
    * @method  CwmsFunctionEditor::CwmsFunctionEditor        // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 14:54:01 2012----------*/
    CwmsFunctionEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 20. Sep 14:54:26 2012-------*
    * @method  CwmsFunctionEditor::~CwmsFunctionEditor       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFunctionEditor                                         *
    *----------------last changed: -----------------------------Do 20. Sep 14:54:26 2012----------*/
    virtual ~CwmsFunctionEditor( );

   public:
   /** +-=---------------------------------------------------------Do 20. Sep 16:35:47 2012-------*
    * @method  CwmsFunctionEditor::FillDialog                // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassMethod* p_pMethod                     //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 16:35:47 2012----------*/
    void FillDialog(CdmClassMethod* p_pMethod, CdmClass* p_pCdmClass, bool p_bNew);

   private:
   /** +-=---------------------------------------------------------Do 20. Sep 15:06:26 2012-------*
    * @method  CwmsFunctionEditor::FillParameters            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:06:26 2012----------*/
    void FillParameters();

   private:
   /** +-=---------------------------------------------------------Do 20. Sep 15:43:48 2012-------*
    * @method  CwmsFunctionEditor::AddTypesToTypeBox         // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:43:48 2012----------*/
    void AddTypesToTypeBox();


    private slots:
   /** +-=---------------------------------------------------------Do 20. Sep 15:56:02 2012-------*
    * @method  CwmsFunctionEditor::DeleteParameterClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:56:02 2012----------*/
void DeleteParameterClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Sep 15:57:20 2012-------*
    * @method  CwmsFunctionEditor::MoveParameterDownClickedSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:57:20 2012----------*/
void MoveParameterDownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Sep 15:57:46 2012-------*
    * @method  CwmsFunctionEditor::MoveParameterUpClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:57:46 2012----------*/
void MoveParameterUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Sep 15:58:14 2012-------*
    * @method  CwmsFunctionEditor::EnlargeCodeViewClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:58:14 2012----------*/
void EnlargeCodeViewClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 20. Sep 15:58:45 2012-------*
    * @method  CwmsFunctionEditor::RightsClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:58:45 2012----------*/
void RightsClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 20. Sep 15:59:25 2012-------*
    * @method  CwmsFunctionEditor::Validate                  // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 15:59:25 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Fr 9. Nov 15:27:40 2012--------*
    * @method  CwmsFunctionEditor::SaveData                  // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 9. Nov 15:27:40 2012-----------*/
    bool SaveData();

    private slots:
   /** +-=---------------------------------------------------------Mo 12. Nov 13:53:47 2012-------*
    * @method  CwmsFunctionEditor::SyntaxCheckClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 12. Nov 13:53:47 2012----------*/
void SyntaxCheckClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 22. Nov 10:38:16 2012-------*
    * @method  CwmsFunctionEditor::AddParameterClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 22. Nov 10:38:16 2012----------*/
void AddParameterClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 22. Nov 11:16:30 2012-------*
    * @method  CwmsFunctionEditor::TypeIndexChangedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 22. Nov 11:16:30 2012----------*/
void TypeIndexChangedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 22. Nov 11:22:56 2012-------*
    * @method  CwmsFunctionEditor::AddClassesToComboBox      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 22. Nov 11:22:56 2012----------*/
    void AddClassesToComboBox();

    void AddTypesToTypeBox(QComboBox *p_pComboBox);
    void ExecuteFunction(bool p_bDebugger);
    bool Find(QTextDocument::FindFlags flag);
    void SetParameterSelected(QString p_qstrName);
private slots:
   /** +-=---------------------------------------------------------Mo 4. Feb 16:47:07 2013--------*
    * @method  CwmsFunctionEditor::SelectIconClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Feb 16:47:07 2013-----------*/
void SelectIconClickedSlot( );

public:
    virtual bool Save();
    virtual void Revert();
    virtual void SetItem(QTreeWidgetItem*);
    virtual bool IsModified();
    virtual void Debug();
virtual void Execute();
public slots:
void ReplaceAllClickedSlot();
void ReplaceClickedSlot();
void FindPreviousClickedSlot();
void FindNextClickedSlot();
};

#endif // CWMSFUNCTIONEDITOR_H
