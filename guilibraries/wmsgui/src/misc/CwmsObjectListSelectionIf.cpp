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

CwmsContainerSelectionIf::CwmsContainerSelectionIf(QWidget* parent)
   : QDialog(parent),
   m_lDbId(0)
{
   setupUi(this);
}

CwmsContainerSelectionIf::~CwmsContainerSelectionIf()
{
}

void CwmsContainerSelectionIf::SetClass(CdmClass* pCdmClass)
{
   if(CHKPTR(pCdmClass))
   {
      SetClass(pCdmClass->GetSchemeId(), pCdmClass->GetId());
   }
}

void CwmsContainerSelectionIf::SetClass(qint64 p_lDbId, qint64 p_lClassId)
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

   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvObjectLists);
}

int CwmsContainerSelectionIf::GetContainerCount()
{
   return m_pqlvObjectLists->topLevelItemCount();
}

CdmObjectContainer* CwmsContainerSelectionIf::GetSelectedObjectContainer()
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

CdmObjectContainer* CwmsContainerSelectionIf::GetObjectContainer(qint64 p_lDbId,
                                                                 qint64 p_lClassId,
                                                                 QWidget* p_pqwParent)
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
