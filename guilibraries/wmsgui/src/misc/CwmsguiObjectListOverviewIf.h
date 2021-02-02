/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 ** CVS Changes: $Id: CwmsguiObjectListOverviewIf.h,v 1.2 2005/08/20 12:05:22 Wolfi Exp $
 ******************************************************************************/

#ifndef CWMSGUIOBJECTLISTOVERVIEWIF_H
#define CWMSGUIOBJECTLISTOVERVIEWIF_H


// System and QT Includes



// own Includes
#include "wmsgui.h"
#include "cwmguiobjectlistoverview.h"


// forwards
class CdmObjectList;
class QListViewItem;



class WMSGUI_API CwmsguiObjectListOverviewIf : public CwmGuiObjectListOverview
{
   Q_OBJECT

   private:
      CdmObjectList* m_rpCdmObjectList;
      QListViewItem* m_pqlviCurrent;



   /** +-=---------------------------------------------------------Tue Dec 16 09:49:29 2003-------*
    * @method  CwmsguiObjectListOverviewIf::CwmsguiObjectListOverviewIf // public                 *
    * @return                                                //                                   *
    * @param   CdmObjectList* p_pCdmObjectList               //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @param   const char* name = NULL                       //                                   *
    * @param   bool modal = FALSE                            //                                   *
    * @param   WFlags fl = 0                                 //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Tue Dec 16 09:49:29 2003------*/
   public:
      CwmsguiObjectListOverviewIf(  CdmObjectList* p_pCdmObjectList,
                                              QWidget* parent = NULL,
                                              const char* name = NULL,
                                              bool modal = FALSE,
                                              WFlags fl = 0 );

   /** +-=---------------------------------------------------------Tue Dec 16 09:50:24 2003-------*
    * @method  CwmsguiObjectListOverviewIf::~CwmsguiObjectListOverviewIf // public, virtual       *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsguiObjectListOverviewIf                                *
    *                                                                                             *
    *---------------------------------------------------------------Tue Dec 16 09:50:24 2003------*/
   public:
      virtual ~CwmsguiObjectListOverviewIf(  );

   /** +-=---------------------------------------------------------Tue Dec 16 09:51:40 2003-------*
    * @method  CwmsguiObjectListOverviewIf::ObjectSelectedSlot // protected, virtual, slots       *
    * @return  void                                          //                                   *
    * @param   QListViewItem* p_pqlviItem                    //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Tue Dec 16 09:51:40 2003------*/
    protected slots:
      virtual void ObjectSelectedSlot(  QListViewItem* p_pqlviItem );

   /** +-=---------------------------------------------------------Tue Dec 16 09:52:18 2003-------*
    * @method  CwmsguiObjectListOverviewIf::NewClickedSlot   // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the new button was clicked. It creates a new object in *
    *          the objectlist.                                                                    *
    *---------------------------------------------------------------Tue Dec 16 09:52:18 2003------*/
    protected slots:
      virtual void NewClickedSlot(  );

   /** +-=---------------------------------------------------------Tue Dec 16 09:53:00 2003-------*
    * @method  CwmsguiObjectListOverviewIf::DeleteClickedSlot // protected, slots                 *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the delete button was clicked. it deletes an object    *
    *          from list.                                                                         *
    *---------------------------------------------------------------Tue Dec 16 09:53:00 2003------*/
    protected slots:
void DeleteClickedSlot(  );

   /** +-=---------------------------------------------------------Tue Dec 16 09:53:34 2003-------*
    * @method  CwmsguiObjectListOverviewIf::CopyClickedSlot  // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the copy button was clicked. It copies an object.      *
    *---------------------------------------------------------------Tue Dec 16 09:53:34 2003------*/
    protected slots:
      virtual void CopyClickedSlot(  );

   /** +-=---------------------------------------------------------Tue Dec 16 09:54:16 2003-------*
    * @method  CwmsguiObjectListOverviewIf::CloseClickedSlot // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the close button was clicked. It closes the dialog.    *
    *---------------------------------------------------------------Tue Dec 16 09:54:16 2003------*/
    protected slots:
      virtual void CloseClickedSlot(  );

   /** +-=---------------------------------------------------------Tue Dec 16 09:55:00 2003-------*
    * @method  CwmsguiObjectListOverviewIf::show             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method will be called if the user wants to show the dialog.                   *
    *---------------------------------------------------------------Tue Dec 16 09:55:00 2003------*/
   public:
      virtual void show(  );
};

#endif
