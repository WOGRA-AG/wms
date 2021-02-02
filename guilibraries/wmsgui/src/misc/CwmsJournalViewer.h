/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsJournalViewer.h
 ** Started Implementation: 2012/08/29
 ** Description:
 ** 
 ** implements the viewer for journal data
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSJOURNALVIEWER_H
#define CWMSJOURNALVIEWER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsJournalViewer.h"


// Forwards
class CdmScheme;
class CdmObjectContainer;
class CdmObject;

// TypeDefs


/* 
 * This class implements the viewer for journal data
 */
class WMSGUI_API CwmsJournalViewer : public QDialog, public Ui::CwmsJournalViewerClass
{
   Q_OBJECT

   private:
      CdmScheme*   m_rpCdmDatabase;
      CdmObjectContainer* m_rpContainer;
      CdmObject*     m_rpCdmObject;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 15:50:16 2012-------*
    * @method  CwmsJournalViewer::CwmsJournalViewer          // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 15:50:16 2012----------*/
    CwmsJournalViewer( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 15:53:03 2012-------*
    * @method  CwmsJournalViewer::~CwmsJournalViewer         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsJournalViewer                                          *
    *----------------last changed: -----------------------------Mi 29. Aug 15:53:03 2012----------*/
    virtual ~CwmsJournalViewer( );

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 19:17:26 2012-------*
    * @method  CwmsJournalViewer::FillDialog                 // public                            *
    * @return  void                                          //                                   *
    * @param   CdmDatabase* p_pCdmDtabase                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 19:17:26 2012----------*/
    void FillDialog(CdmScheme* p_pCdmDtabase);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 19:17:38 2012-------*
    * @method  CwmsJournalViewer::FillDialog                 // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 19:17:38 2012----------*/
    void FillDialog(CdmObjectContainer* p_pContainer);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 19:17:44 2012-------*
    * @method  CwmsJournalViewer::FillDialog                 // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 19:17:44 2012----------*/
    void FillDialog(CdmObject* p_pCdmObject);

    private slots:
   /** +-=---------------------------------------------------------Mi 29. Aug 16:04:19 2012-------*
    * @method  CwmsJournalViewer::RefreshClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 16:04:19 2012----------*/
void RefreshClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 16:06:13 2012-------*
    * @method  CwmsJournalViewer::SetFromToDefaultData       // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 16:06:13 2012----------*/
    void SetFromToDefaultData();



   private:
   /** +-=---------------------------------------------------------Mi 29. Aug 16:16:51 2012-------*
    * @method  CwmsJournalViewer::AddObjectListHeader        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 16:16:51 2012----------*/
    void AddObjectListHeader();

   private:
   /** +-=---------------------------------------------------------Mi 29. Aug 16:16:57 2012-------*
    * @method  CwmsJournalViewer::AddDbHeader                // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 16:16:57 2012----------*/
    void AddDbHeader();

   private:
   /** +-=---------------------------------------------------------Mi 29. Aug 16:17:44 2012-------*
    * @method  CwmsJournalViewer::AddObjectHeader            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 16:17:44 2012----------*/
    void AddObjectHeader();

};

#endif // CWMSJOURNALVIEWER_H
