/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graï¿½of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 ** CVS Changes: $Id: CwmsguiObjectListOverviewIf.cpp,v 1.5 2007/03/11 19:31:51 wgrasshof Exp $
 ******************************************************************************/


// System and QT Includes
#include <qvaluelist.h>
#include <qlistview.h>


// own Includes
#include "CdmError.h"
#include "CdmObjectList.h"
#include "CdmObject.h"
#include "CwmsguiObjectListOverviewIf.h"


/** +-=---------------------------------------------------------Tue Dec 16 09:49:29 2003----------*
 * @method  CwmsguiObjectListOverviewIf::CwmsguiObjectListOverviewIf // public                    *
 * @return                                                   //                                   *
 * @param   CdmObjectList* p_pCdmObjectList                  //                                   *
 * @param   QWidget* parent = NULL                           //                                   *
 * @param   const char* name = NULL                          //                                   *
 * @param   bool modal = FALSE                               //                                   *
 * @param   WFlags fl = 0                                    //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Tue Dec 16 09:49:29 2003---------*/
CwmsguiObjectListOverviewIf::CwmsguiObjectListOverviewIf(  CdmObjectList* p_pCdmObjectList,
                                                          QWidget* parent,
                                                          const char* name,
                                                          bool modal,
                                                          WFlags fl )
: CwmGuiObjectListOverview(parent, name, modal, fl),
  m_rpCdmObjectList(p_pCdmObjectList),
  m_pqlviCurrent(NULL)
{

}

/** +-=---------------------------------------------------------Tue Dec 16 09:50:24 2003----------*
 * @method  CwmsguiObjectListOverviewIf::~CwmsguiObjectListOverviewIf // public, virtual          *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsguiObjectListOverviewIf                                   *
 *                                                                                                *
 *---------------------------------------------------------------Tue Dec 16 09:50:24 2003---------*/
CwmsguiObjectListOverviewIf::~CwmsguiObjectListOverviewIf(  )
{
   // todo
}

/** +-=---------------------------------------------------------Tue Dec 16 09:55:00 2003----------*
 * @method  CwmsguiObjectListOverviewIf::show                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method will be called if the user wants to show the dialog.                      *
 *---------------------------------------------------------------Tue Dec 16 09:55:00 2003---------*/
void CwmsguiObjectListOverviewIf::show(  )
{
   if ( CHKPTR(m_rpCdmObjectList) )
   {
      QValueList<CdmObject*> qvlObjects;
      
      m_rpCdmObjectList->GetObjectList(qvlObjects);

      QValueListIterator<CdmObject*> it    = qvlObjects.begin();
      QValueListIterator<CdmObject*> itEnd = qvlObjects.end();

      for (; it != itEnd; ++it)
      {
         CdmObject* pCdmObject = (*it);

         if ( pCdmObject )
         {
            QListViewItem* pqlviItem = new QListViewItem(m_pqlvObjects);
            pqlviItem->setText(0, QString::number(pCdmObject->GetId()));
         }

      }

      CwmGuiObjectListOverview::show();
   }
}

/** +-=---------------------------------------------------------Tue Dec 16 09:51:40 2003----------*
 * @method  CwmsguiObjectListOverviewIf::ObjectSelectedSlot  // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @param   QListViewItem* p_pqlviItem                       //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Tue Dec 16 09:51:40 2003---------*/
void CwmsguiObjectListOverviewIf::ObjectSelectedSlot(  QListViewItem* p_pqlviItem )
{
   m_pqlviCurrent = p_pqlviItem;
   if ( m_pqlviCurrent )
   {
      // todo
   }
}

/** +-=---------------------------------------------------------Tue Dec 16 09:52:18 2003----------*
 * @method  CwmsguiObjectListOverviewIf::NewClickedSlot      // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the new button was clicked. It creates a new object in    *
 *          the objectlist.                                                                       *
 *---------------------------------------------------------------Tue Dec 16 09:52:18 2003---------*/
void CwmsguiObjectListOverviewIf::NewClickedSlot(  )
{
   if ( m_rpCdmObjectList )
   {
      //@todo SessionId for object creation!!!!
      CdmObject* pCdmObject = m_rpCdmObjectList->CreateNewObject(0);

      if ( pCdmObject )
      {
         QListViewItem* pqlviItem = new QListViewItem(m_pqlvObjects);
         pqlviItem->setText(0, QString::number(pCdmObject->GetId()));
      }
   }
}

/** +-=---------------------------------------------------------Tue Dec 16 09:53:00 2003----------*
 * @method  CwmsguiObjectListOverviewIf::DeleteClickedSlot   // protected, slots                  *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the delete button was clicked. it deletes an object       *
 *          from list.                                                                            *
 *---------------------------------------------------------------Tue Dec 16 09:53:00 2003---------*/
void CwmsguiObjectListOverviewIf::DeleteClickedSlot(  )
{
   if (m_pqlviCurrent && m_rpCdmObjectList)
   {
      long lId = m_pqlviCurrent->text(0).toLong();
      //@todo SessionId for object creation!!!!
      m_rpCdmObjectList->DeleteObject(lId);
   }
}

/** +-=---------------------------------------------------------Tue Dec 16 09:53:34 2003----------*
 * @method  CwmsguiObjectListOverviewIf::CopyClickedSlot     // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the copy button was clicked. It copies an object.         *
 *---------------------------------------------------------------Tue Dec 16 09:53:34 2003---------*/
void CwmsguiObjectListOverviewIf::CopyClickedSlot(  )
{
   if (m_pqlviCurrent && m_rpCdmObjectList)
   {
      long lId = m_pqlviCurrent->text(0).toLong();
      //@todo SessionId for object creation!!!!
      CdmObject* pCdmObject = m_rpCdmObjectList->CopyObject(lId);

      if (CHKPTR(pCdmObject))
      {
         QListViewItem* pqlviItem = new QListViewItem(m_pqlvObjects);
         pqlviItem->setText(0, QString::number(pCdmObject->GetId()));
      }
   }
}

/** +-=---------------------------------------------------------Tue Dec 16 09:54:16 2003----------*
 * @method  CwmsguiObjectListOverviewIf::CloseClickedSlot    // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the close button was clicked. It closes the dialog.       *
 *---------------------------------------------------------------Tue Dec 16 09:54:16 2003---------*/
void CwmsguiObjectListOverviewIf::CloseClickedSlot(  )
{
   accept();
}
