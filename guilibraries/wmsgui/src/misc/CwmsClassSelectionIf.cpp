/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: CwmsClassSelectionIf.cpp
 ** Started Implementation: 2008/05/19
 ** Description:
 ** 
 ** the gui of the class selection
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

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

/** +-=---------------------------------------------------------Mi 5. Sep 15:22:49 2012-----------*
 * @method  CwmsClassSelectionIf::CwmsClassSelectionIf       // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 15:22:49 2012-----------*/
CwmsClassSelectionIf::CwmsClassSelectionIf(QWidget* parent)
   : QDialog(parent),
   m_bShowAbstractClasses(true)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mo 19. Mai 20:25:09 2008----------*
 * @method  CwmsClassSelectionIf::~CwmsClassSelectionIf      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsClassSelectionIf                                          *
 *----------------last changed: --------------------------------Mo 19. Mai 20:25:09 2008----------*/
CwmsClassSelectionIf::~CwmsClassSelectionIf()
{
}

/** +-=---------------------------------------------------------So 30. Dez 11:31:21 2012----------*
 * @method  CwmsClassSelectionIf::FillDialog                 // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 11:31:21 2012----------*/
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

/** +-=---------------------------------------------------------So 30. Dez 11:41:16 2012----------*
 * @method  CwmsClassSelectionIf::ShowTechnicalClassesClickedSlot // private, slots               *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 11:41:16 2012----------*/
void CwmsClassSelectionIf::ShowTechnicalClassesClickedSlot()
{
   FillDialog(m_bShowAbstractClasses);
}

/** +-=---------------------------------------------------------Mo 19. Mai 20:30:46 2008----------*
 * @method  CwmsClassSelectionIf::GetSelectedClass           // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 20:30:46 2008----------*/
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

/** +-=---------------------------------------------------------Mo 3. Sep 18:25:35 2012-----------*
 * @method  CwmsClassSelectionIf::GetClass                   // public, static                    *
 * @return  CdmClass*                                        //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 18:25:35 2012-----------*/
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
