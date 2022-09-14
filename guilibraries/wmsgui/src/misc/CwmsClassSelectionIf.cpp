// System and QT Includes
#include <QList>

// WMS Includes
#include "CdmClass.h"
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmPackage.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsClassSelectionIf.h"

CwmsClassSelectionIf::CwmsClassSelectionIf(QWidget* parent)
   : QDialog(parent),
   m_bShowAbstractClasses(true)
{
   setupUi(this);
}

CwmsClassSelectionIf::~CwmsClassSelectionIf()
{
}

void CwmsClassSelectionIf::FillDialog(bool p_bShowAbstractClasses)
{
   m_bShowAbstractClasses = p_bShowAbstractClasses;
   m_pqlvClasses->clear();
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetCurrentScheme()->GetClassManager();

      if (CHKPTR(pCdmClassManager))
      {
         QList<CdmClass*> qvlClasses;
         pCdmClassManager->GetClassList(qvlClasses);

         QList<CdmClass*>::iterator qvlIt = qvlClasses.begin();
         QList<CdmClass*>::iterator qvlItEnd = qvlClasses.end();

         for (; qvlIt != qvlItEnd; qvlIt++)
         {
            CdmClass* pCdmClass = (*qvlIt);

            if (CHKPTR(pCdmClass))
            {
               bool bInsertClass = true;

               if (!m_bShowAbstractClasses && pCdmClass->IsAbstract())
               {
                  bInsertClass = false;
               }

               if (!m_pqchbShowTechnicalClasses->isChecked())
               {
                  if (IsTechnicalClass(pCdmClass))
                  {
                     bInsertClass = false;
                  }
               }

               if (bInsertClass)
               {
                  QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvClasses);
                  pqlviItem->setData(0, Qt::UserRole, pCdmClass->GetId());
                  pqlviItem->setText(0, pCdmClass->GetFullQualifiedName());
                  pqlviItem->setText(1, pCdmClass->GetCaption());
               }
            }
         }

         m_pqlvClasses->sortItems(0, Qt::AscendingOrder);
      }
   }
}

void CwmsClassSelectionIf::ShowTechnicalClassesClickedSlot()
{
   FillDialog(m_bShowAbstractClasses);
}

qint64 CwmsClassSelectionIf::GetSelectedClass()
{
  qint64 lRet = 0;

   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvClasses);

   if (pqlviItem)
   {
      lRet = pqlviItem->data(0, Qt::UserRole).toInt();
   }

   return lRet;
}

void CwmsClassSelectionIf::FilterClassesSlot()
{
    QString qstrFilter = m_pqleFilter->text();
    for (int counter = 0; counter < m_pqlvClasses->topLevelItemCount(); ++counter)
    {
        QTreeWidgetItem* pItem =  m_pqlvClasses->topLevelItem(counter);

        if (CHKPTR(pItem))
        {
            if (qstrFilter.isEmpty())
            {
                pItem->setHidden(false);
            }
            else
            {
                QString qstrView = pItem->text(0).toUpper();

                if (qstrView.contains(qstrFilter.toUpper()))
                {
                    pItem->setHidden(false);
                }
                else
                {
                    pItem->setHidden(true);
                }
            }
        }
    }
}

CdmClass* CwmsClassSelectionIf::GetClass(QWidget* p_pqwParent, bool p_bShowAbstractClasses)
{
   CdmClass* pCdmClass = nullptr;
   CwmsClassSelectionIf* pCdmSelector = new CwmsClassSelectionIf(p_pqwParent);
   pCdmSelector->FillDialog(p_bShowAbstractClasses);

   if (pCdmSelector->exec() == QDialog::Accepted)
   {
     qint64 lClassId = pCdmSelector->GetSelectedClass();
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetCurrentScheme()->GetClassManager();

         if (CHKPTR(pCdmClassManager))
         {
            pCdmClass = pCdmClassManager->FindClassById(lClassId);
         }
      }
   }

   return pCdmClass;
}

bool CwmsClassSelectionIf::IsTechnicalClass(CdmClass* p_pClass)
{
   bool bRet = false;

   if (CHKPTR(p_pClass))
   {
      QString qstrKeyname = p_pClass->GetKeyname();
      if (qstrKeyname.startsWith("Technical") ||
            qstrKeyname.startsWith("Workflow"))
      {
         bRet = true;
      }

      if (!bRet)
      {
          CdmPackage* pPackage = p_pClass->GetPackage();

          if (pPackage && IsTechnicalPackage(pPackage))
          {
              bRet = true;
          }
      }
   }

   return bRet;
}

bool CwmsClassSelectionIf::IsTechnicalPackage(CdmPackage* p_pPackage)
{
    return (p_pPackage->GetPackageString().startsWith("Technical") || p_pPackage->GetPackageString().startsWith("plugins"));
}
