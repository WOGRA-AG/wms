/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsQueryEditor.h
 ** Started Implementation: 2012/07/26
 ** Description:
 ** 
 ** Implements the ui of the queryeditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSQUERYEDITOR_H
#define CWMSQUERYEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmQueryModel.h"

// Own Includes
#include "ui_CwmsQueryEditor.h"
#include "wmsgui.h"

// Forwards
class CdmQueryElement;
class CdmQueryEnhanced;

// TypeDefs


/* 
 * This class implements the ui of the queryeditor
 */
class WMSGUI_API CwmsQueryEditor : public QWidget, public Ui::CwmsQueryEditorWidget
{
   Q_OBJECT

   private:
      CdmQueryEnhanced* m_pCdmQuery;
      CdmQueryModel m_cCdmModel;

   public:
   /** +-=---------------------------------------------------------Do 26. Jul 11:26:32 2012-------*
    * @method  CwmsQueryEditor::CwmsQueryEditor              // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Jul 11:26:32 2012----------*/
    CwmsQueryEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 26. Jul 11:27:00 2012-------*
    * @method  CwmsQueryEditor::~CwmsQueryEditor             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsQueryEditor                                            *
    *----------------last changed: -----------------------------Do 26. Jul 11:27:00 2012----------*/
    virtual ~CwmsQueryEditor( );

    private slots:
   /** +-=---------------------------------------------------------Do 26. Jul 11:39:27 2012-------*
    * @method  CwmsQueryEditor::ExecuteClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Jul 11:39:27 2012----------*/
void ExecuteClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 26. Jul 11:39:42 2012-------*
    * @method  CwmsQueryEditor::SaveClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Jul 11:39:42 2012----------*/
void SaveClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 26. Jul 11:39:53 2012-------*
    * @method  CwmsQueryEditor::SaveResultClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Jul 11:39:53 2012----------*/
void SaveResultClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 26. Jul 11:40:05 2012-------*
    * @method  CwmsQueryEditor::ClearResultClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Jul 11:40:05 2012----------*/
void ClearResultClickedSlot( );

void EditClickedSlot();
   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 13:29:13 2012-------*
    * @method  CwmsQueryEditor::FillQueryAnalyzer            // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pqTreeWidget                   //                                   *
    * @param   CdmQueryEnhanced* p_pQuery                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 13:29:13 2012----------*/
    static void FillQueryAnalyzer(QTreeWidget* p_pqTreeWidget, CdmQuery* p_pQuery);

public slots:
    void SystemVariablesChangedSlot(QString);
    void QueryChangedSlot();
private:
   /** +-=---------------------------------------------------------Fr 24. Aug 13:53:43 2012-------*
    * @method  CwmsQueryEditor::AddQueryElement              // private, static                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmElement                //                                   *
    * @param   QTreeWidgetItem* p_pqParent                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 13:53:43 2012----------*/
    static void AddQueryElement(CdmQueryElement* p_pCdmElement, QTreeWidgetItem* p_pqParent);
};

#endif // CWMSQUERYEDITOR_H
