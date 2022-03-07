/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CbgMandatorSelectionIf.cpp
 ** Started Implementation: 14.7.2006
 ** Description:
 ** Implements the mandatorselectiondialog
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 


// System and QT Includes
#include <qcursor.h>
#include <qapplication.h>
#include <qinputdialog.h>
#include <qpushbutton.h>
#include <QList>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmRights.h"
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwmsGuiDatabaseSelection.h"


/** +-=---------------------------------------------------------Di 4. Sep 14:26:47 2012-----------*
 * @method  CwmsDatabaseSelection::CwmsDatabaseSelection     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment The constructor of the chosse mandatorif class it initializes the members.            *
 *----------------last changed: --------------------------------Di 4. Sep 14:26:47 2012-----------*/
CwmsGuiDatabaseSelection::CwmsGuiDatabaseSelection(QWidget* parent)
   : QDialog(parent),
   m_bNeedToShow(true)
{
	setupUi(this);
}

/** +-=---------------------------------------------------------Di 4. Sep 14:26:57 2012-----------*
 * @method  CwmsDatabaseSelection::~CwmsDatabaseSelection    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CfbChooseMandatorIf                                           *
 *----------------last changed: --------------------------------Di 4. Sep 14:26:57 2012-----------*/
CwmsGuiDatabaseSelection::~CwmsGuiDatabaseSelection()
{
   // nothing to do here :-) 
}

/** +-=---------------------------------------------------------Di 4. Sep 14:27:10 2012-----------*
 * @method  CwmsDatabaseSelection::FillDialog                // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog with the mandators.                                      *
 *----------------last changed: --------------------------------Di 4. Sep 14:27:10 2012-----------*/
void CwmsGuiDatabaseSelection::FillDialog(QList<QString>& p_rqllDatabases)
{
   m_bNeedToShow = true;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      m_pqlbMandators->clear();

      
	  QList<QString>::iterator qvlIt = p_rqllDatabases.begin();
	  QList<QString>::iterator qvlItEnd = p_rqllDatabases.end();

      for (; qvlIt != qvlItEnd; ++ qvlIt)
      {
         QString qstrDatabase = *qvlIt;

         if (!qstrDatabase.isEmpty() && !qstrDatabase.startsWith("Technical"))
         {
            QListWidgetItem* pItem = new QListWidgetItem(m_pqlbMandators);
            pItem->setText(qstrDatabase);
         }
      }
   
      if (m_pqlbMandators->count() == 1)
      {
         m_pqlbMandators->setCurrentRow(0);
         m_bNeedToShow = false;
         OKClickedSlot();
      }
      else if (m_pqlbMandators->count() == 0) // no rights to databases quit application
      {
         MSG_CRIT("Keine ausreichenden Berechtigungen",
                  "Sie haben keine ausreichende Berchtigungen. Die Applikation wird beendet.");
         m_bNeedToShow = false;
         CancelClickedSlot();
      }
   }
}

/** +-=---------------------------------------------------------Di 4. Sep 14:28:07 2012-----------*
 * @method  CwmsDatabaseSelection::ListBoxDoubleClickedSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if a mandator is double clicked by the listbox.              *
 *----------------last changed: --------------------------------Di 4. Sep 14:28:07 2012-----------*/
void CwmsGuiDatabaseSelection::ListBoxDoubleClickedSlot()
{
   OKClickedSlot();
}

/** +-=---------------------------------------------------------Di 4. Sep 14:29:02 2012-----------*
 * @method  CwmsDatabaseSelection::CancelClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to cancel this application.                *
 *----------------last changed: --------------------------------Di 4. Sep 14:29:02 2012-----------*/
void CwmsGuiDatabaseSelection::CancelClickedSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
      
   if(CHKPTR(pCdmManager))
   {
      CdmSessionManager::Logout();
   }
   
   qApp->quit();
}

/** +-=---------------------------------------------------------Di 4. Sep 14:29:12 2012-----------*
 * @method  CwmsDatabaseSelection::OKClickedSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the ok button was clicked.                                *
 *----------------last changed: --------------------------------Di 4. Sep 14:29:12 2012-----------*/
void CwmsGuiDatabaseSelection::OKClickedSlot()
{
   QListWidgetItem* pqlbiItem = GetSelectedItem();

   if(pqlbiItem)
   {
      QString qstrScheme = pqlbiItem->text();
      LoadScheme(qstrScheme);
   }
   else
   {
      MSG_CRIT("Fehler bei der Schema Auswahl",
               "Kein Schema gewählt!!!");
   }
}

/** +-=---------------------------------------------------------Di 4. Sep 14:31:29 2012-----------*
 * @method  CwmsDatabaseSelection::GetSelectedItem           // private                           *
 * @return  QListWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 14:31:29 2012-----------*/
QListWidgetItem* CwmsGuiDatabaseSelection::GetSelectedItem()
{
   QListWidgetItem* pItem = nullptr;
   QList<QListWidgetItem*> qlItems = m_pqlbMandators->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Di 4. Sep 15:17:02 2012-----------*
 * @method  CwmsDatabaseSelection::LoadDatabase              // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrScheme                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 15:17:02 2012-----------*/
void CwmsGuiDatabaseSelection::LoadScheme(QString p_qstrScheme)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmScheme = nullptr;
      if(pCdmManager->LoadScheme(p_qstrScheme) > 0)
      {
         pCdmScheme = pCdmManager->FindSchemeByName(p_qstrScheme);

         if (CHKPTR(pCdmScheme))
         {
            pCdmManager->SetCurrentScheme(pCdmScheme);
            accept();
         }
         else
         {
            MSG_CRIT("Fehler bei der Schemaauswahl",
                     "Schema konnte nicht geladen werden!!!");
         }
      }
   }
}
