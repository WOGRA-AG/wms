/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwqQmlEditor.h
 ** Started Implementation: 2013/09/02
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSQMLEDITOR_H
#define CWMSQMLEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QWidget>
#include <QFileSystemWatcher>

// WMS Includes
#include "CwmsFormUserDefined.h"

// own Includes
#include "IwmsSciprtEditor.h"
#include "ui_CwmsqmlEditor.h"
#include "wmsgui.h"

// Forwards
class QQuickView;
class CdmObject;
class CdmObjectContainer;
class QTreeWidgetItem;

// TypeDefs

// enums

/* 
 * This class implements the main test class which starts all tests
 */
class WMSGUI_API CwmsQmlEditor : public QWidget, public Ui::CwmsqmlEditor, public IwmsScriptEditor
{
   Q_OBJECT
      
   private:
      CwmsFormUserDefined m_Form;
      QFileSystemWatcher m_FileWatcher;
      QString m_qstrOriginalCode;
      QTreeWidgetItem * m_rpItem;


   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 21:25:22 2013-------*
    * @method  CwmsQmlEditor::CwmsQmlEditor                  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pParent                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 21:25:22 2013----------*/
    CwmsQmlEditor( QWidget* p_pParent);

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 21:25:33 2013-------*
    * @method  CwmsQmlEditor::~CwmsQmlEditor                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwqQmlEditor                                               *
    *----------------last changed: -----------------------------Mo 23. Sep 21:25:33 2013----------*/
    virtual ~CwmsQmlEditor( );

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 21:25:46 2013-------*
    * @method  CwmsQmlEditor::FillDialog                     // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsFormUserDefined p_Form                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 21:25:46 2013----------*/
    void FillDialog(CwmsFormUserDefined p_Form);


   private:
   /** +-=---------------------------------------------------------Mo 23. Sep 21:26:31 2013-------*
    * @method  CwmsQmlEditor::Validate                       // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 21:26:31 2013----------*/
    bool Validate();

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 21:26:50 2013-------*
    * @method  CwmsQmlEditor::Save                           // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 21:26:50 2013----------*/
    virtual bool Save();
    virtual void Revert();
    virtual void SetItem(QTreeWidgetItem*);
    virtual bool IsModified();

    virtual void Debug();
    virtual void Execute();

    private slots:
   /** +-=---------------------------------------------------------Mo 23. Sep 21:27:28 2013-------*
    * @method  CwmsQmlEditor::SelectClassClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 21:27:28 2013----------*/
void SelectClassClickedSlot( );

    private slots:
    void OpenInExternalEditorSlot();

    private slots:
    void FileChangedSlot(QString p_qstrFile);


    private slots:
   /** +-=---------------------------------------------------------Mo 23. Sep 22:13:49 2013-------*
    * @method  CwmsQmlEditor::PreviewClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 22:13:49 2013----------*/
    void PreviewClickedSlot( );
    void SaveClickedSlot();
};

#endif //

