/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qstring.h>



// own Includes
#include "CdmLogging.h"
#include "CwmsErrorSettingsIf.h"



/** +-=---------------------------------------------------------Di 28. Sep 08:18:23 2010----------*
 * @method  CwmsErrorSettingsIf::CwmsErrorSettingsIf         // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 08:18:23 2010----------*/
CwmsErrorSettingsIf::CwmsErrorSettingsIf(QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Sa 28. Jul 11:44:26 2007----------*
 * @method  CwmsErrorSettingsIf::~CwmsErrorSettingsIf        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsErrorSettingsIf                                           *
 *----------------last changed: Wolfgang Graßhof----------------Sa 28. Jul 11:44:26 2007----------*/
CwmsErrorSettingsIf::~CwmsErrorSettingsIf()
{
}


/** +-=---------------------------------------------------------Sa 28. Jul 11:46:15 2007----------*
 * @method  CwmsErrorSettingsIf::SetFileSeverities           // public                            *
 * @return  void                                             //                                   *
 * @param   QMap<QString, int>& p_rqmSeverities              //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 28. Jul 11:46:15 2007----------*/
void CwmsErrorSettingsIf::SetFileSeverities(QMap<QString, int>& p_rqmSeverities)
{
   m_rqmFileSeverities = p_rqmSeverities;
   FillTable();
}

/** +-=---------------------------------------------------------Sa 28. Jul 11:46:51 2007----------*
 * @method  CwmsErrorSettingsIf::FillTable                   // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the tables with the fileseverities settings.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 28. Jul 11:46:51 2007----------*/
void CwmsErrorSettingsIf::FillTable()
{
   int iCount = m_rqmFileSeverities.count();

   m_pqtFileTable->setRowCount(iCount);
   
   QMap<QString, int>::iterator qmIt = m_rqmFileSeverities.begin();
   QMap<QString, int>::iterator qmItEnd = m_rqmFileSeverities.end();

   int iRow = 0;

   for (; qmIt != qmItEnd; ++qmIt)
   {
         QString qstrFile = qmIt.key();
         int iVisibility = qmIt.value();

         QTableWidgetItem* pItem = new QTableWidgetItem(qstrFile);
         m_pqtFileTable->setItem(iRow, 0, pItem);
         
         pItem = new QTableWidgetItem();
         pItem->setFlags(Qt::ItemIsUserCheckable);
          m_pqtFileTable->setItem(iRow, 1, pItem);
         
         if (iVisibility & eDmInfo)
         {
            pItem->setCheckState(Qt::Checked);
         }
         else
         {
            pItem->setCheckState(Qt::Unchecked);
         }

         pItem = new QTableWidgetItem();
         pItem->setFlags(Qt::ItemIsUserCheckable);
         m_pqtFileTable->setItem(iRow, 2, pItem);

         if (iVisibility & eDmWarning)
         {
            pItem->setCheckState(Qt::Checked);
         }
         else
         {
            pItem->setCheckState(Qt::Unchecked);
         }

         pItem = new QTableWidgetItem();
         pItem->setFlags(Qt::ItemIsUserCheckable);
         m_pqtFileTable->setItem(iRow, 3, pItem);

         if (iVisibility & eDmError)
         {
            pItem->setCheckState(Qt::Checked);
         }
         else
         {
            pItem->setCheckState(Qt::Unchecked);
         }

         pItem = new QTableWidgetItem();
         pItem->setFlags(Qt::ItemIsUserCheckable);
         m_pqtFileTable->setItem(iRow, 4, pItem);

         if (iVisibility & eDmFatal)
         {
            pItem->setCheckState(Qt::Checked);
         }
         else
         {
            pItem->setCheckState(Qt::Unchecked);
         }

         ++iRow;
   }
}
