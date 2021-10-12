/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportColumnDlg.cpp
 ** Started Implementation: 2008/10/26
 ** Description:
 ** 
 ** This class implements the dialog for defning columns for the import.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QLineEdit>
#include <QStringList>
#include <QGroupBox>
#include <QCheckBox>

// WMS Includes
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsImportSettingsColumn.h"
#include "CwmsImportColumnDlg.h"
#include "CwmsImport.h"


/** +-=---------------------------------------------------------So 26. Okt 13:07:51 2008----------*
 * @method  CwmsImportColumnDlg::CwmsImportColumnDlg         // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------So 26. Okt 13:07:51 2008----------*/
CwmsImportColumnDlg::CwmsImportColumnDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
    setupUi(this);
}

/** +-=---------------------------------------------------------So 26. Okt 13:08:10 2008----------*
 * @method  CwmsImportColumnDlg::~CwmsImportColumnDlg        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportColumnDlg                                           *
 *----------------last changed: --------------------------------So 26. Okt 13:08:10 2008----------*/
CwmsImportColumnDlg::~CwmsImportColumnDlg()
{
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:04:34 2013----------*
 * @method  CwmsImportColumnDlg::FillMemberListView          // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @param   CwmsImport* p_pCwmsImport                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:04:34 2013----------*/
void CwmsImportColumnDlg::FillMemberListView(const CdmClass* p_pCdmClass, CwmsImport* p_pCwmsImport)
{
   if (CHKPTR(p_pCdmClass) && CHKPTR(p_pCwmsImport))
   {
      QMap<qint64,CdmMember*> qmMembers;
      p_pCdmClass->GetMemberMap(qmMembers);

      QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();
      QStringList qstrlHiddenMembers = p_pCwmsImport->GetHiddenMembersList();
      QTreeWidgetItem* pqchItem = nullptr;

      for(; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember) && !qstrlHiddenMembers.contains(pCdmMember->GetKeyname()))
         {
            if (pCdmMember->GetValueType() == eDmValueObjectRef)
            {
               pqchItem = new QTreeWidgetItem(m_pqlvColumn, pqchItem);
               pqchItem->setText(0, pCdmMember->GetCaption());
               pqchItem->setText(1, pCdmMember->GetKeyname());

               FillChildMembers(pCdmMember, pqchItem, 0, p_pCdmClass, p_pCwmsImport);
               pqchItem->setExpanded(true);
           
            }
            else if (pCdmMember->GetValueType() != eDmValueBinaryDocument && 
               pCdmMember->GetValueType() != eDmValueListDouble &&
               pCdmMember->GetValueType() != eDmValueListInt &&
               pCdmMember->GetValueType() != eDmValueListString &&
               pCdmMember->GetValueType() != eDmValueDictIntDouble &&
               pCdmMember->GetValueType() != eDmValueDictIntInt &&
               pCdmMember->GetValueType() != eDmValueDictIntString &&
               pCdmMember->GetValueType() != eDmValueDictStringDouble &&
               pCdmMember->GetValueType() != eDmValueDictStringInt &&
               pCdmMember->GetValueType() != eDmValueDictStringString &&
               pCdmMember->GetValueType() != eDmValueContainerRef)
            {
               pqchItem = new QTreeWidgetItem(m_pqlvColumn, pqchItem);
               pqchItem->setText(0, pCdmMember->GetCaption());
               pqchItem->setText(1, pCdmMember->GetKeyname());
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:19:33 2013----------*
 * @method  CwmsImportColumnDlg::FillChildMembers            // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QTreeWidgetItem* p_pqlvItem                      //                                   *
 * @param   int p_iDepth                                     //                                   *
 * @param   const CdmClass* p_pCdmRequestClass               //                                   *
 * @param   CwmsImport* p_pCwmsImport                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:19:33 2013----------*/
void CwmsImportColumnDlg::FillChildMembers(CdmMember* p_pCdmMember,
                                           QTreeWidgetItem* p_pqlvItem,
                                           int p_iDepth,
                                           const CdmClass* p_pCdmRequestClass,
                                           CwmsImport* p_pCwmsImport)
{
   if (CHKPTR(p_pCdmMember) && CHKPTR(p_pqlvItem) && CHKPTR(p_pCwmsImport))
   {  
      int iClassId = p_pCdmMember->GetClassReference();

      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(p_pCdmMember->GetSchemeId());
         QStringList qstrlHiddenMembers = p_pCwmsImport->GetHiddenMembersList();

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(iClassId);

            if (pCdmClass)
            {
               QMap<qint64,CdmMember*> qmMembers;
               pCdmClass->GetMemberMap(qmMembers);

               QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
               QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();
               QTreeWidgetItem* pqchItem = nullptr;

               for(; qmIt != qmItEnd; ++qmIt)
               {
                  CdmMember* pCdmMember = qmIt.value();

                  if (CHKPTR(pCdmMember) && !qstrlHiddenMembers.contains(pCdmMember->GetKeyname()))
                  {
                     if (pCdmMember->GetValueType() == eDmValueObjectRef && 
                        p_iDepth < 2 &&
                        p_pCdmRequestClass->GetId() != pCdmMember->GetClassReference() &&
                        p_pCdmRequestClass->IsInherited(pCdmMember->GetClassReference()) < 1)
                     {
                        pqchItem = new QTreeWidgetItem(p_pqlvItem, pqchItem);
                        pqchItem->setText(0, pCdmMember->GetCaption());
                        pqchItem->setText(1, pCdmMember->GetKeyname());

                        ++p_iDepth;

                        FillChildMembers(pCdmMember, pqchItem, p_iDepth, p_pCdmRequestClass, p_pCwmsImport);
                        pqchItem->setExpanded(true);
                     }
                     else if (pCdmMember->GetValueType() != eDmValueBinaryDocument && 
                        pCdmMember->GetValueType() != eDmValueListDouble &&
                        pCdmMember->GetValueType() != eDmValueListInt &&
                        pCdmMember->GetValueType() != eDmValueListString &&
                        pCdmMember->GetValueType() != eDmValueDictIntDouble &&
                        pCdmMember->GetValueType() != eDmValueDictIntInt &&
                        pCdmMember->GetValueType() != eDmValueDictIntString &&
                        pCdmMember->GetValueType() != eDmValueDictStringDouble &&
                        pCdmMember->GetValueType() != eDmValueDictStringInt &&
                        pCdmMember->GetValueType() != eDmValueDictStringString &&
                        pCdmMember->GetValueType() != eDmValueContainerRef)
                     {
                        pqchItem = new QTreeWidgetItem(p_pqlvItem, pqchItem);
                        pqchItem->setText(0, pCdmMember->GetCaption());
                        pqchItem->setText(1, pCdmMember->GetKeyname());
                     }
                  }
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 27. Okt 17:36:47 2008----------*
 * @method  CwmsImportColumnDlg::GetSelectedMember           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Okt 17:36:47 2008----------*/
QString CwmsImportColumnDlg::GetSelectedMember()
{
   QString qstrRet;

   if (m_pqgbColumnAssignment->isChecked())
   {
      QTreeWidgetItem* pqlviSelectedItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvColumn);

      if (pqlviSelectedItem)
      {
         QTreeWidgetItem* pqlviItem = pqlviSelectedItem;
         qstrRet = pqlviItem->text(1);

         while (pqlviItem->parent() != nullptr)
         {
            pqlviItem = pqlviItem->parent();

            if (pqlviItem)
            {
               qstrRet = pqlviItem->text(1) + "." + qstrRet;
            }
         }
      }
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------So 26. Okt 14:13:45 2008----------*
 * @method  CwmsImportColumnDlg::GetColumnSetttings          // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsImportSettingsColumn* p_pColumn              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 14:13:45 2008----------*/
void CwmsImportColumnDlg::GetColumnSetttings(CwmsImportSettingsColumn* p_pColumn)
{
   if (p_pColumn)
   {
      p_pColumn->SetEndPos(m_pqleEndPos->text().toInt());
      p_pColumn->SetStartPos(m_pqleStartPos->text().toInt());
      p_pColumn->SetUpdateCriteria(m_pqchbUpdateRelevant->isChecked());
      p_pColumn->SetMember(GetSelectedMember());
   }
}


/** +-=---------------------------------------------------------So 26. Okt 13:09:13 2008----------*
 * @method  CwmsImportColumnDlg::CancelClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 13:09:13 2008----------*/
void CwmsImportColumnDlg::CancelClickedSlot()
{
   reject();
}

/** +-=---------------------------------------------------------So 26. Okt 13:09:24 2008----------*
 * @method  CwmsImportColumnDlg::OKClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 13:09:24 2008----------*/
void CwmsImportColumnDlg::OKClickedSlot()
{
   accept();
   /*
   if (m_pqleEndPos->text().toInt() > m_pqleStartPos->text().toInt())
   {
      accept();
   }
   else
   {
      CdmMessageManager::critical(tr("Ungültige Eingabe"), tr("Die Startposition der Spalte muss kleiner sein als die Endposition."));
   }
   */
}