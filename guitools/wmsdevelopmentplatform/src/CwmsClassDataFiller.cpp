// System and QT Includes
#include <qtreewidget.h>
#include <qapplication.h>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmPackage.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmClassMethod.h"
#include "CdmMember.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsObjectContainerDataFiller.h"
#include "CwmsAdminMainWindowIf.h"
#include "CwmsClassDataFiller.h"



/** +-=---------------------------------------------------------Mi 18. Sep 19:10:00 2013----------*
 * @method  CwmsClassDataFiller::FillClasses                 // public, static                    *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pClassManager                 //                                   *
 * @param   QTreeWidgetItem* p_pParent                       //                                   *
 * @param   bool p_bAddObjectContainers                      //                                   *
 * @param   bool p_bShowTechnicalItems                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 19:10:00 2013----------*/
void CwmsClassDataFiller::FillClasses(CdmClassManager* p_pClassManager,
                                      QTreeWidgetItem* p_pParent,
                                      bool p_bAddObjectContainers,
                                      bool p_bShowTechnicalItems)
{
   QList<CdmClass*> qvlClasses;
   p_pClassManager->GetClassList(qvlClasses);
   QList<CdmPackage*> qlPackages = p_pClassManager->GetPackageList();

   for (int iPos = 0; iPos < qlPackages.count(); ++iPos)
   {
       CdmPackage* pPackage = qlPackages[iPos];

       if (p_bShowTechnicalItems || !IsTechnicalPackage(pPackage))
       {
           FillPackage(pPackage, p_pParent);
       }
   }

   if (qvlClasses.count() > 0)
   {
      QList<CdmClass*>::iterator qvlIt = qvlClasses.begin();
      QList<CdmClass*>::iterator qvlItEnd = qvlClasses.end();

      for (; qvlIt != qvlItEnd; ++ qvlIt)
      {
         CdmClass* pCdmClass = (*qvlIt); 

         if (CHKPTR(pCdmClass) && pCdmClass->GetPackage() == nullptr)
         {
            if (p_bShowTechnicalItems || !IsTechnicalClass(pCdmClass))
            {
               FillClass(pCdmClass, p_pParent, p_bAddObjectContainers);
            }
         }
      }

      p_pParent->setExpanded(true);
      CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pParent->treeWidget());
   }
}

bool CwmsClassDataFiller::IsTechnicalPackage(CdmPackage* p_pPackage)
{
    return (p_pPackage->GetPackageString().startsWith("Technical") || p_pPackage->GetPackageString().startsWith("plugins"));
}

void CwmsClassDataFiller::FillPackage(CdmPackage* p_pPackage, QTreeWidgetItem* p_pParent)
{
    if (CHKPTR(p_pPackage))
    {
        QTreeWidgetItem* pPackage = new QTreeWidgetItem(p_pParent);
        pPackage->setText(0, p_pPackage->GetCaption());
        pPackage->setData(0, Qt::UserRole, p_pPackage->GetUriInternal());
        pPackage->setData(1, Qt::UserRole, eWmsTreeItemTypePackage);
        QList<CdmClass*> qlClasses = p_pPackage->GetClassList();

        for (int iClassPos = 0; iClassPos < qlClasses.count(); ++iClassPos)
        {
            FillClass(qlClasses[iClassPos], pPackage, false);
        }

        QList<CdmPackage*> qlChildren;
        p_pPackage->GetChildren(qlChildren);

        for (int iChildPos = 0; iChildPos < qlChildren.count(); ++iChildPos)
        {
            FillPackage(qlChildren[iChildPos], pPackage);
        }

        pPackage->setExpanded(true);
    }
}

/** +-=---------------------------------------------------------Mi 18. Sep 19:05:12 2013----------*
 * @method  CwmsClassDataFiller::FillClass                   // public, static                    *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QTreeWidgetItem* p_pqtwClass                     //                                   *
 * @param   bool p_bAddObjectContainers                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 19:05:12 2013----------*/
void CwmsClassDataFiller::FillClass(CdmClass* p_pCdmClass,
                                    QTreeWidgetItem* p_pqtwClass,
                                    bool p_bAddObjectContainers)
{
   if (CHKPTR(p_pCdmClass))
   {
      QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(p_pqtwClass);

      pqlviItem->setText(0, p_pCdmClass->GetKeyname());
      pqlviItem->setText(1, p_pCdmClass->GetCaption());
      pqlviItem->setData(0, Qt::UserRole, p_pCdmClass->GetId());
      pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeClass);

      if (!p_pCdmClass->IsAbstract() && p_bAddObjectContainers)
      {
         CwmsObjectContainerDataFiller::FillObjectContainersToClass(p_pCdmClass, pqlviItem);
      }
      
      FillMembersAndGroups(p_pCdmClass, pqlviItem);
      FillFunctions(p_pCdmClass, pqlviItem);
      CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pqtwClass->treeWidget());
   }
}

/** +-=---------------------------------------------------------Mi 18. Sep 19:04:54 2013----------*
 * @method  CwmsClassDataFiller::FillMembersAndGroups        // private, static                   *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QTreeWidgetItem* p_pqtwClass                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 19:04:54 2013----------*/
void CwmsClassDataFiller::FillMembersAndGroups(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass)
{
   if (CHKPTR(p_pqtwClass) && CHKPTR(p_pCdmClass))
   {
      QTreeWidgetItem* pqlviGroupItem = new QTreeWidgetItem(p_pqtwClass);
      pqlviGroupItem->setData(1, Qt::UserRole, eWmsTreeItemTypeMemberParent);
      QMap<const CdmClassGroup*, QTreeWidgetItem*> qmCreatedGroups;

      QMap<int, CdmClassGroup*> qmGroups = p_pCdmClass->GetClassGroups();

      QMap<int, CdmClassGroup*>::iterator qmGroupIt = qmGroups.begin();
      QMap<int, CdmClassGroup*>::iterator qmGroupItEnd = qmGroups.end();

      for (; qmGroupIt != qmGroupItEnd; ++qmGroupIt)
      {
         CdmClassGroup* pCdmGroup = qmGroupIt.value();

         if (pCdmGroup)
         {
            QTreeWidgetItem* pqlviGroup = new QTreeWidgetItem(pqlviGroupItem);
            pqlviGroup->setText(0, pCdmGroup->GetName());
            qmCreatedGroups.insert(pCdmGroup, pqlviGroup);
            pqlviGroup->setData(1, Qt::UserRole, eWmsTreeItemTypeGroup);
         }
      }
   
      QMap<qint64, CdmMember*> qmMembers;
      p_pCdmClass->GetMemberMap(qmMembers);


      QMap<qint64, CdmMember*>::iterator qmItMember = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItMemberEnd = qmMembers.end();

      for (; qmItMember != qmItMemberEnd; ++qmItMember)
      {
         CdmMember* pCdmMember = qmItMember.value();

         if (CHKPTR(pCdmMember))
         {
            const CdmClassGroup* pCdmGroup = pCdmMember->GetGroup();
            QTreeWidgetItem* pqtwParent = nullptr;

            if (pCdmGroup && qmCreatedGroups.contains(pCdmGroup))
            {
               pqtwParent = qmCreatedGroups[pCdmGroup];
            }
            else
            {
               pqtwParent = pqlviGroupItem;
            }

            QTreeWidgetItem* pqtwMember = new QTreeWidgetItem(pqtwParent);
            pqtwMember->setText(0, pCdmMember->GetCaption());
            pqtwMember->setText(1, pCdmMember->GetKeyname() + " (" + pCdmMember->GetValueTypeAsString() + ")");
            pqtwMember->setData(0, Qt::UserRole, pCdmMember->GetUriInternal());
            pqtwMember->setData(1, Qt::UserRole, eWmsTreeItemTypeMember);
         }
      }

      pqlviGroupItem->setText(0, QObject::tr("Members") + " (" + QString::number(qmMembers.count()) + ")");
   }
}

/** +-=---------------------------------------------------------Mi 18. Sep 19:04:29 2013----------*
 * @method  CwmsClassDataFiller::FillFunctions               // private, static                   *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QTreeWidgetItem* p_pqtwClass                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 19:04:29 2013----------*/
void CwmsClassDataFiller::FillFunctions(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass)
{
   BODY_TRY
   if (CHKPTR(p_pqtwClass) &&
       CHKPTR(p_pCdmClass))
   {
      QTreeWidgetItem* pqlviFunctionItem = new QTreeWidgetItem(p_pqtwClass);
      pqlviFunctionItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFunctionParent);
      QList<QString> qvlObjectLists;

      QMap<QString, CdmClassMethod*> qmMethods = p_pCdmClass->GetMethods();

      QMap<QString, CdmClassMethod*>::iterator qmIt    = qmMethods.begin();
      QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmMethods.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         QString qstrKeyname = qmIt.key();
         QTreeWidgetItem* pqlviMethod = new QTreeWidgetItem(pqlviFunctionItem);
         pqlviMethod->setText(0, qstrKeyname);
         pqlviMethod->setData(0, Qt::UserRole, qmIt.value()->GetUriInternal());
         pqlviMethod->setData(1, Qt::UserRole, eWmsTreeItemTypeFunction);
      }

      pqlviFunctionItem->setText(0, QObject::tr("Funktionen") + " (" + QString::number(qmMethods.count()) + ")");
   }
   BODY_CATCH
}

/** +-=---------------------------------------------------------Fr 20. Sep 15:42:52 2013----------*
 * @method  CwmsClassDataFiller::FillClassesToComboBox       // public, static                    *
 * @return  void                                             //                                   *
 * @param   QComboBox* p_pComboBox                           //                                   *
 * @param   bool p_bAddAbstractClasses                       //                                   *
 * @param   bool p_bFilterMode                               //                                   *
 * @param   bool p_bShowTechnicalClasses                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 15:42:52 2013----------*/
void CwmsClassDataFiller::FillClassesToComboBox(QComboBox* p_pComboBox,
                                                bool p_bAddAbstractClasses,
                                                bool p_bFilterMode,
                                                bool p_bShowTechnicalClasses)
{
   BODY_TRY
   if (CHKPTR(p_pComboBox))
   {
      if (p_bFilterMode)
      {
         p_pComboBox->addItem(QObject::tr("Objektcontainer aller Klassen"));
      }

      CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pManager))
      {
         CdmClassManager* pClassManager = pManager->GetClassManager();

         if (CHKPTR(pClassManager))
         {
            QList<CdmClass*> qvlClasses;
            pClassManager->GetClassList(qvlClasses);
            QMap<QString, QString> qmEntries;

            if (qvlClasses.count() > 0)
            {
               QList<CdmClass*>::iterator qvlIt    = qvlClasses.begin();
               QList<CdmClass*>::iterator qvlItEnd = qvlClasses.end();

               for ( ; qvlIt != qvlItEnd; ++ qvlIt)
               {
                  CdmClass* pCdmClass = *qvlIt;
               
                  if (CHKPTR(pCdmClass))
                  {
                     if (!pCdmClass->IsAbstract() || p_bAddAbstractClasses)
                     {
                        if (p_bShowTechnicalClasses || !IsTechnicalClass(pCdmClass))
                        {
                           qmEntries.insert(pCdmClass->GetFullQualifiedName(), pCdmClass->GetUriInternal());
                        }
                     }
                  }
               }
            }

            QMap<QString, QString>::iterator qmIt    = qmEntries.begin();
            QMap<QString, QString>::iterator qmItEnd = qmEntries.end();

            for ( ; qmIt != qmItEnd; ++qmIt)
            {
                p_pComboBox->addItem(qmIt.key(), qmIt.value());
            }
         }
      }
   }
   BODY_CATCH
}

/** +-=---------------------------------------------------------Do 19. Sep 08:16:59 2013----------*
 * @method  CwmsClassDataFiller::IsTechnicalClass            // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 19. Sep 08:16:59 2013----------*/
bool CwmsClassDataFiller::IsTechnicalClass(CdmClass* p_pClass)
{
    bool bRet = false;

    BODY_TRY
    if (CHKPTR(p_pClass))
    {
        QString qstrKeyname = p_pClass->GetKeyname();

        if (qstrKeyname.startsWith("Technical") || qstrKeyname.startsWith("Workflow"))
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
    BODY_CATCH

    return bRet;
}
