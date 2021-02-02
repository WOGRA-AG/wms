/******************************************************************************
 ** WOGRA Middleware Server GUI Tools Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes


// own Includes
#include "CdmObject.h"
#include "CdmValue.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CwmsObjectListEditorIf.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsguiValidator.h"

/** +-=---------------------------------------------------------So 23. Mai 10:59:17 2010----------*
 * @method  CwmsObjectListEditorIf::CwmsObjectListEditorIf   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 10:59:17 2010----------*/
CwmsObjectListEditorIf::CwmsObjectListEditorIf(QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------So 23. Mai 11:00:55 2010----------*
 * @method  CwmsObjectListEditorIf::CwmsObjectListEditorIf   // public                            *
 * @return                                                   //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 11:00:55 2010----------*/
CwmsObjectListEditorIf::CwmsObjectListEditorIf(CdmObjectContainer* p_pContainer, QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
   m_pCwmsObjectListListView->SetContainer(p_pContainer);
}

/** +-=---------------------------------------------------------Fr 6. Jan 15:02:19 2006-----------*
 * @method  CwmsObjectListEditorIf::~CwmsObjectListEditorIf  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectListEditorIf                                        *
 *                                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Fr 6. Jan 15:02:19 2006-----------*/
CwmsObjectListEditorIf::~CwmsObjectListEditorIf(  )
{
}

/** +-=---------------------------------------------------------Di 25. Sep 15:08:27 2012----------*
 * @method  CwmsObjectListEditorIf::SetModel                 // public                            *
 * @return  void                                             //                                   *
 * @param   CdmQueryModel* p_pModel                        //                                   *
 * @comment This method sets the proxy for this gui component.                                    *
 *----------------last changed: --------------------------------Di 25. Sep 15:08:27 2012----------*/
void CwmsObjectListEditorIf::SetModel(CdmQueryModel* p_pModel)
{
   m_pCwmsObjectListListView->SetModel(p_pModel);
}

/** +-=---------------------------------------------------------So 8. Jan 12:03:22 2006-----------*
 * @method  CwmsObjectListEditorIf::SetObjectList            // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 8. Jan 12:03:22 2006-----------*/
void CwmsObjectListEditorIf::SetContainer(  CdmObjectContainer* p_pContainer )
{
   m_pCwmsObjectListListView->SetContainer(p_pContainer);
}

/** +-=---------------------------------------------------------Fr 6. Jan 16:16:53 2006-----------*
 * @method  CwmsObjectListEditorIf::AddColumn                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrColumn                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Fr 6. Jan 16:16:53 2006-----------*/
void CwmsObjectListEditorIf::AddColumn(  QString p_qstrColumn )
{
   m_pCwmsObjectListListView->AddColumn(p_qstrColumn);
}

/** +-=---------------------------------------------------------Fr 6. Jan 15:32:59 2006-----------*
 * @method  CwmsObjectListEditorIf::FillDialog               // public                            *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog after all settings were done.                            *
 *----------------last changed: Wolfgang Graßhof----------------Fr 6. Jan 15:32:59 2006-----------*/
void CwmsObjectListEditorIf::FillDialog(  )
{
   m_pCwmsObjectListListView->FillDialog();
}

/** +-=---------------------------------------------------------Di 4. Sep 12:10:38 2012-----------*
 * @method  CwmsObjectListEditorIf::GetListView              // public                            *
 * @return  QTreeView*                                       //                                   *
 * @comment returns the litview.                                                                  *
 *----------------last changed: --------------------------------Di 4. Sep 12:10:38 2012-----------*/
QTreeView* CwmsObjectListEditorIf::GetListView()
{
   return m_pCwmsObjectListListView->GetListView();
}

CwmsObjectListEditorWidgetIf* CwmsObjectListEditorIf::GetContainerEditorWidgetIf()
{
   return m_pCwmsObjectListListView;
}

/** +-=---------------------------------------------------------Fr 6. Jan 15:36:56 2006-----------*
 * @method  CwmsObjectListEditorIf::CloseClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Fr 6. Jan 15:36:56 2006-----------*/
void CwmsObjectListEditorIf::CloseClickedSlot(  )
{
   accept();
}

/** +-=---------------------------------------------------------So 18. Jun 18:59:13 2006----------*
 * @method  CwmsObjectListEditorIf::SetDefaultValueForNewObject // public                         *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValueName                          //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:59:13 2006----------*/
void CwmsObjectListEditorIf::SetDefaultValueForNewObject(QString p_qstrValueName,
                                                         QString p_qstrValue,
                                                         QString p_qstrValue2)
{
   m_pCwmsObjectListListView->SetDefaultValueForNewObject(p_qstrValueName, p_qstrValue, p_qstrValue2);
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:44:48 2012----------*
 * @method  CwmsObjectListEditorIf::ClearMenu                // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:44:48 2012----------*/
void CwmsObjectListEditorIf::ClearMenu()
{
   m_pCwmsObjectListListView->ClearMenu();
}

/** +-=---------------------------------------------------------Mo 27. Aug 11:14:14 2012----------*
 * @method  CwmsObjectListEditorIf::AddPopupItem             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrItem                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:14:14 2012----------*/
void CwmsObjectListEditorIf::AddPopupItem(QString p_qstrItem)
{
   m_pCwmsObjectListListView->AddPopupItem(p_qstrItem);
}

/** +-=---------------------------------------------------------Mo 27. Aug 11:34:03 2012----------*
 * @method  CwmsObjectListEditorIf::NewClickedSlot           // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:34:03 2012----------*/
void CwmsObjectListEditorIf::NewClickedSlot()
{
   m_pCwmsObjectListListView->NewClickedSlot();
}

/** +-=---------------------------------------------------------Mo 27. Aug 11:34:29 2012----------*
 * @method  CwmsObjectListEditorIf::EditClickedSlot          // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:34:29 2012----------*/
void CwmsObjectListEditorIf::EditClickedSlot()
{
   m_pCwmsObjectListListView->EditClickedSlot();
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:45:16 2012----------*
 * @method  CwmsObjectListEditorIf::DeleteClickedSlot        // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:45:16 2012----------*/
void CwmsObjectListEditorIf::DeleteClickedSlot()
{
   m_pCwmsObjectListListView->DeleteClicekdSlot();
}

/** +-=---------------------------------------------------------Mo 27. Aug 11:03:49 2012----------*
 * @method  CwmsObjectListEditorIf::GetObjectList            // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:03:49 2012----------*/
CdmObjectContainer* CwmsObjectListEditorIf::GetObjectList()
{
   return m_pCwmsObjectListListView->GetContainer();
}
