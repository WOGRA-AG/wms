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
#endif

// System and QT Includes

// WMS Includes
#include "CdmQueryModel.h"

// Own Includes
#include "ui_CwmsQueryEditor.h"

// Forwards
class CdmQueryEnhanced;

// TypeDefs


/* 
 * This class implements the ui of the queryeditor
 */
class CwmsQueryEditor : public QWidget, public Ui::CwmsQueryEditorWidget
{
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

   private:
   /** +-=---------------------------------------------------------Di 14. Aug 09:56:37 2012-------*
    * @method  CwmsQueryEditor::AskForFilename               // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrFileType                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 09:56:37 2012----------*/
    QString AskForFilename(QString p_qstrFileType);

   private:
   /** +-=---------------------------------------------------------Di 14. Aug 10:10:25 2012-------*
    * @method  CwmsQueryEditor::SaveContent                  // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrContent                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 10:10:25 2012----------*/
    void SaveContent(QString p_qstrFilename, QString p_qstrContent);
};

#endif
