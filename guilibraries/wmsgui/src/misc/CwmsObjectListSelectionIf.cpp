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
#include <qmap.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "IdmDataAccess.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsObjectListSelectionIf.h"



/** +-=---------------------------------------------------------Di 28. Sep 14:38:59 2010----------*
 * @method  CwmsObjectListSelectionIf::CwmsObjectListSelectionIf // public                        *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment The constructor                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 14:38:59 2010----------*/
CwmsContainerSelectionIf::CwmsContainerSelectionIf(QWidget* parent)
   : QDialog(parent),
   m_lDbId(0)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mo 23. Jan 21:26:24 2006----------*
 * @method  CwmsObjectListSelectionIf::~CwmsObjectListSelectionIf // public, virtual              *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectListSelectionIf                                     *
 *                                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 21:26:24 2006----------*/
CwmsContainerSelectionIf::~CwmsContainerSelectionIf(  )
{
}

/** +-=---------------------------------------------------------Mo 23. Jan 21:26:53 2006----------*
 * @method  CwmsObjectListSelectionIf::SetClass              // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* pCdmClass                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 21:26:53 2006----------*/
void CwmsContainerSelectionIf::SetClass(  CdmClass* pCdmClass )
{
   if(CHKPTR(pCdmClass))
   {
      SetClass(pCdmClass->GetSchemeId(), pCdmClass->GetId());
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 21:52:52 2006----------*
 * @method  CwmsObjectListSelectionIf::SetClass              // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 21:52:52 2006----------*/
void CwmsContainerSelectionIf::SetClass( qint64 p_lDbId,qint64 p_lClassId )
{
   if(p_lClassId >= 0)
   {
      m_lDbId = p_lDbId;
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if(CHKPTR(pCdmManager))
      {
         IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

         if(CHKPTR(pIdmDataAccess))
         {
            QMap<qint64, QString> qmObjectLists;
            pIdmDataAccess->GetContainerList(p_lDbId,
                                             p_lClassId,
                                             qmObjectLists);


            
            QMap<qint64, QString>::iterator qmIt = qmObjectLists.begin();
            QMap<qint64, QString>::iterator qmItEnd = qmObjectLists.end();

            for(; qmIt != qmItEnd; ++qmIt)
            {
               QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvObjectLists);
               pqlviItem->setText(0, QString::number(qmIt.key()));
               pqlviItem->setText(1, qmIt.value());

               if (qmObjectLists.count() == 1)
               {
                  pqlviItem->setSelected(true);
               }
            }
         }
      }
   }
   else
   {
      ERR("Invalid Class Id");
   }
}

int CwmsContainerSelectionIf::GetContainerCount()
{
   return m_pqlvObjectLists->topLevelItemCount();
}



/** +-=---------------------------------------------------------Mo 23. Jan 22:00:49 2006----------*
 * @method  CwmsObjectListSelectionIf::GetSelectedObjectList // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment This method returns the selected obejctlist.                                          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 22:00:49 2006----------*/
CdmObjectContainer* CwmsContainerSelectionIf::GetSelectedObjectContainer(  )
{
   CdmObjectContainer* pContainer = nullptr;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(m_lDbId);

      if(CHKPTR(pContainerManager))
      {
         QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvObjectLists);

         if(pqlviItem)
         {
            pContainer = pContainerManager->FindContainerById(pqlviItem->text(0).toLong());
         }
      }
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Mo 23. Jan 22:35:56 2006----------*
 * @method  CwmsObjectListSelectionIf::GetObjectContainer         // public, static                    *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment This method does the static method call.                                              *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 22:35:56 2006----------*/
CdmObjectContainer* CwmsContainerSelectionIf::GetObjectContainer( qint64 p_lDbId,
                                                        qint64 p_lClassId,
                                                         QWidget* p_pqwParent )
{
   CdmObjectContainer* pContainer = nullptr;

   CwmsContainerSelectionIf* pCdmSelection = new CwmsContainerSelectionIf(p_pqwParent);
   pCdmSelection->SetClass(p_lDbId, p_lClassId);

   if (pCdmSelection->GetContainerCount() == 1)
   {
      pContainer = pCdmSelection->GetSelectedObjectContainer();
   }
   else if (pCdmSelection->GetContainerCount() > 1)
   {
      if(pCdmSelection->exec() == QDialog::Accepted)
      {
         pContainer = pCdmSelection->GetSelectedObjectContainer();
      }
   }
   else
   {
      MSG_INFO(("Kein Container vorhanden"),
                                     ("Es ist kein Container vom erwarteten Typ vorhanden.\n"
                                        "Auswahl kann nicht durchgeführt werden."));
   }

   delete pCdmSelection;
   return pContainer;
}
