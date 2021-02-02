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
#include <QLinkedList>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmRights.h"
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwmsUserSchemeSelection.h"


CwmsUserSchemeSelection::CwmsUserSchemeSelection(QWidget* parent)
   : QDialog(parent)
{
	setupUi(this);
}

CwmsUserSchemeSelection::~CwmsUserSchemeSelection()
{
   // nothing to do here :-) 
}

void CwmsUserSchemeSelection::FillDialog(QLinkedList<QString>& p_rqllDatabases)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      m_pqlbMandators->clear();
	  QLinkedList<QString>::iterator qvlIt = p_rqllDatabases.begin();
	  QLinkedList<QString>::iterator qvlItEnd = p_rqllDatabases.end();

      for (; qvlIt != qvlItEnd; ++ qvlIt)
      {
         QString qstrDatabase = *qvlIt;

         if (!qstrDatabase.isEmpty() && !qstrDatabase.startsWith("Technical"))
         {
            QListWidgetItem* pItem = new QListWidgetItem(m_pqlbMandators);
            pItem->setText(qstrDatabase);
         }
      }
   }
}

void CwmsUserSchemeSelection::ListBoxDoubleClickedSlot()
{
   OKClickedSlot();
}

void CwmsUserSchemeSelection::CancelClickedSlot()
{
    reject();
}

void CwmsUserSchemeSelection::OKClickedSlot()
{
   QListWidgetItem* pqlbiItem = GetSelectedItem();

   if(pqlbiItem)
   {
      m_qstrScheme = pqlbiItem->text();
      accept();
   }
}

QListWidgetItem* CwmsUserSchemeSelection::GetSelectedItem()
{
   QListWidgetItem* pItem = nullptr;
   QList<QListWidgetItem*> qlItems = m_pqlbMandators->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}


QString CwmsUserSchemeSelection::SelectScheme(QLinkedList<QString>& qllSchemes, QWidget* p_pParent)
{
    QString qstrScheme;
    CwmsUserSchemeSelection selector(p_pParent);
    selector.FillDialog(qllSchemes);

    if (selector.exec() == QDialog::Accepted)
    {
        qstrScheme = selector.m_qstrScheme;
    }

    return qstrScheme;
}
