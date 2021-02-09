/******************************************************************************
 ** WOGRA Middleware Server GUI Tools Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CWMSOBJECTLISTEDITORIF_H
#define CWMSOBJECTLISTEDITORIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes 
#include <QDialog>
#include <qmap.h>
#include <qpair.h>

// own Includes
#include "wmsgui.h"
#include "CwmsObjectListEditorBase.h"
#include "ui_CwmsObjectListEditor.h"


// forwards
class CdmEnhancedQueryProxy;
class CwmsguiValidator;
class CdmObjectContainer;

typedef QPair<QString,QString> StringPair;

class WMSGUI_API CwmsObjectListEditorIf : public QDialog, public Ui::CwmsObjectListEditor, public CwmsContainerEditorBase
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------So 23. Mai 11:00:55 2010-------*
    * @method  CwmsObjectListEditorIf::CwmsObjectListEditorIf // public                           *
    * @return                                                //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 11:00:55 2010----------*/
    CwmsObjectListEditorIf( CdmObjectContainer* p_pContainer, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Fr 6. Jan 15:02:19 2006*
    * @method  CwmsObjectListEditorIf::~CwmsObjectListEditorIf // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectListEditorIf                                     *
    *                                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 15:02:19 2006-----------*/
virtual ~CwmsObjectListEditorIf(  );

   public:
   /** +-=---------------------------------------------------------Fr 6. Jan 16:16:53 2006*
    * @method  CwmsObjectListEditorIf::AddColumn             // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrColumn                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 16:16:53 2006-----------*/
void AddColumn(  QString p_qstrColumn );




   private:
 
   public:
   /** +-=---------------------------------------------------------Fr 6. Jan 15:32:59 2006*
    * @method  CwmsObjectListEditorIf::FillDialog            // public                            *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog after all settings were done.                         *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 15:32:59 2006-----------*/
void FillDialog(  );
CwmsObjectListEditorWidgetIf* GetContainerEditorWidgetIf();

    private slots:
   /** +-=---------------------------------------------------------Fr 6. Jan 15:36:56 2006*
    * @method  CwmsObjectListEditorIf::CloseClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 15:36:56 2006-----------*/
void CloseClickedSlot(  );

   public:
   /** +-=---------------------------------------------------------So 8. Jan 12:03:22 2006*
    * @method  CwmsObjectListEditorIf::SetObjectList         // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 8. Jan 12:03:22 2006-----------*/
void SetContainer(  CdmObjectContainer* p_pContainer );

   public:
   /** +-=---------------------------------------------------------So 23. Mai 10:59:17 2010-------*
    * @method  CwmsObjectListEditorIf::CwmsObjectListEditorIf // public                           *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 10:59:17 2010----------*/
    CwmsObjectListEditorIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 25. Sep 15:08:27 2012-------*
    * @method  CwmsObjectListEditorIf::SetModel              // public                            *
    * @return  void                                          //                                   *
    * @param   CdmQueryModel* p_pModel                     //                                   *
    * @comment This method sets the proxy for this gui component.                                 *
    *----------------last changed: -----------------------------Di 25. Sep 15:08:27 2012----------*/
    void SetModel(CdmQueryModel* p_pModel);


   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:59:13 2006-------*
    * @method  CwmsObjectListEditorIf::SetDefaultValueForNewObject // public                      *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValueName                       //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:59:13 2006----------*/
    void SetDefaultValueForNewObject(QString p_qstrValueName,
                                     QString p_qstrValue,
                                     QString p_qstrValue2);




   public:
   /** +-=---------------------------------------------------------Di 4. Sep 12:10:38 2012--------*
    * @method  CwmsObjectListEditorIf::GetListView           // public                            *
    * @return  QTreeView*                                    //                                   *
    * @comment returns the litview.                                                               *
    *----------------last changed: -----------------------------Di 4. Sep 12:10:38 2012-----------*/
    QTreeView* GetListView();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 11:14:14 2012-------*
    * @method  CwmsObjectListEditorIf::AddPopupItem          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrItem                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 11:14:14 2012----------*/
    void AddPopupItem(QString p_qstrItem);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:44:48 2012-------*
    * @method  CwmsObjectListEditorIf::ClearMenu             // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:44:48 2012----------*/
    void ClearMenu();

    public slots:
         /** +-=---------------------------------------------------------Mo 27. Aug 10:45:16 2012-------*
    * @method  CwmsObjectListEditorIf::DeleteClickedSlot     // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:45:16 2012----------*/
void DeleteClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 11:03:49 2012-------*
    * @method  CwmsObjectListEditorIf::GetObjectList         // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 11:03:49 2012----------*/
    CdmObjectContainer* GetObjectList();

public slots:
void NewClickedSlot( );
void EditClickedSlot();
};

#endif //
