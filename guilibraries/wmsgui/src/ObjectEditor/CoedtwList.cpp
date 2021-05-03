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
#include <QTextEdit>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QTreeWidget>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>
#include <QList>
#include <QList>
#include <QString>

// WMS Includes
#include "CdmPackage.h"
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmObject.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmContainerManager.h"
#include "CdmLogging.h"
#include "CdmValueListString.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListObjects.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringString.h"

// own Includes
#include "CwmsClassSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "CoeTextEditIf.h"
#include "CoedtwAddValueDlgIf.h"
#include "CoedtwList.h"

/** +-=---------------------------------------------------------Mi 22. Aug 11:00:35 2012----------*
 * @method  CoedtwList::CoedtwList                           // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:00:35 2012----------*/
CoedtwList::CoedtwList(QWidget* p_pqwParent)
   : CoeValueWidget(nullptr, p_pqwParent),
m_pqtwTreeWidget(nullptr),
m_pqpbEdit(nullptr),
m_pqpbAdd(nullptr),
m_pqpbRemove(nullptr),
m_pqwParent(nullptr)
{

}

/** +-=---------------------------------------------------------Mi 22. Aug 11:00:58 2012----------*
 * @method  CoedtwList::CoedtwList                           // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:00:58 2012----------*/
CoedtwList::CoedtwList(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqtwTreeWidget(nullptr),
  m_pqpbEdit(nullptr),
  m_pqpbAdd(nullptr),
  m_pqpbRemove(nullptr),
  m_pqwParent(nullptr)
{

}

CoedtwList::CoedtwList(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
   m_pqtwTreeWidget(nullptr),
   m_pqpbEdit(nullptr),
   m_pqpbAdd(nullptr),
   m_pqpbRemove(nullptr),
   m_pqwParent(nullptr)
{

}

/** +-=---------------------------------------------------------Do 4. Sep 18:57:29 2008-----------*
 * @method  CoedtwList::~CoedtwList                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwList                                                    *
 *----------------last changed: --------------------------------Do 4. Sep 18:57:29 2008-----------*/
CoedtwList::~CoedtwList()
{
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:35:22 2012-----------*
 * @method  CoedtwList::GetTabEditWidget                     // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:35:22 2012-----------*/
QWidget* CoedtwList::GetTabEditWidget(QWidget* p_pqwParent)
{
   return GetEditWidget(p_pqwParent);
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:34:48 2012----------*
 * @method  CoedtwList::GetEditWidget                        // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:34:48 2012----------*/
QWidget* CoedtwList::GetEditWidget(QWidget* p_pqwParent)
{
   if (!m_pqwParent)
   {
      m_pqwParent = new QWidget(p_pqwParent);
      QVBoxLayout* pqvblLayout = new QVBoxLayout(m_pqwParent);
      m_pqtwTreeWidget = new QTreeWidget(m_pqwParent);
      m_pqtwTreeWidget->setSortingEnabled(false);
      pqvblLayout->addWidget(m_pqtwTreeWidget);

      QHBoxLayout* pqhbButton = new QHBoxLayout();

      QSpacerItem* pqSeperator = new QSpacerItem(1,1, QSizePolicy::Expanding);
      pqhbButton->addItem(pqSeperator);

      m_pqpbAdd = new QPushButton(m_pqwParent);
      m_pqpbAdd->setText(tr("Hinzufügen"));
      m_pqpbAdd->setMaximumWidth(90);
      pqhbButton->addWidget(m_pqpbAdd);

      m_pqpbEdit = new QPushButton(m_pqwParent);
      m_pqpbEdit->setText(tr("Bearbeiten"));
      m_pqpbEdit->setMaximumWidth(90);
      pqhbButton->addWidget(m_pqpbEdit);

      m_pqpbRemove = new QPushButton(m_pqwParent);
      m_pqpbRemove->setText(tr("Entfernen"));
      m_pqpbRemove->setMaximumWidth(90);
      pqhbButton->addWidget(m_pqpbRemove);
      pqvblLayout->addLayout(pqhbButton);

      connect(m_pqpbEdit, SIGNAL(clicked()), this, SLOT(EditClickedSlot()));
      connect(m_pqpbRemove, SIGNAL(clicked()), this, SLOT(RemoveClickedSlot()));
      connect(m_pqpbAdd, SIGNAL(clicked()), this, SLOT(AddClickedSlot()));
   }

   return m_pqwParent;
}

/** +-=---------------------------------------------------------Mi 18. Jan 18:59:24 2012----------*
 * @method  CoedtwList::SetValue                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Mi 18. Jan 18:59:24 2012----------*/
void CoedtwList::SetValue(CdmValue* p_pCdmValue)
{
   if (CHKPTR(m_pqtwTreeWidget) && CHKPTR(p_pCdmValue))
   {
      m_pqtwTreeWidget->clear();
      m_rpCdmValue = p_pCdmValue;
      m_rpCdmMember = m_rpCdmValue->GetMember();

      switch(p_pCdmValue->GetValueType())
      {
      case eDmValueDictIntDouble:
         {
            QMap<int, double> qmIntDouble = ((CdmValueDictIntDouble*)p_pCdmValue)->GetDict();
            FillTreeWidget(qmIntDouble);
         }
         break;
      case eDmValueDictIntString:
         {
            QMap<int, QString> qmIntString = ((CdmValueDictIntString*)p_pCdmValue)->GetDict();
            FillTreeWidget(qmIntString);
         }
         break;
      case eDmValueDictIntInt:
         {
            QMap<int, int> qmIntInt = ((CdmValueDictIntInt*)p_pCdmValue)->GetDict();
            FillTreeWidget(qmIntInt);
         }
         break;
      case eDmValueDictStringDouble:
         {
            QMap<QString, double> qmStringDouble = ((CdmValueDictStringDouble*)p_pCdmValue)->GetDict();
            FillTreeWidget(qmStringDouble);
         }
         break;
      case eDmValueDictStringInt:
         {
            QMap<QString, int> qmStringInt = ((CdmValueDictStringInt*)p_pCdmValue)->GetDict();
            FillTreeWidget(qmStringInt);
         }
         break;
      case eDmValueDictStringString:
         {
            QMap<QString, QString> qmStringString = ((CdmValueDictStringString*)p_pCdmValue)->GetDict();
            FillTreeWidget(qmStringString);
         }
         break;
      case eDmValueListDouble:
         {
            m_pqpbEdit->hide();
            QList<double> qvlDoubles = ((CdmValueListDouble*)p_pCdmValue)->GetList();
            FillTreeWidget(qvlDoubles);
         }
         break;
      case eDmValueListInt:
         {
            m_pqpbEdit->hide();
            QList<int> qvlInt = ((CdmValueListInt*)p_pCdmValue)->GetList();
            FillTreeWidget(qvlInt);
         }
         break;
      case eDmValueListString:
         {
            m_pqpbEdit->hide();
            QList<QString> qvlStrings = ((CdmValueListString*)p_pCdmValue)->GetList();
            FillTreeWidget(qvlStrings);

         }
         break;
      case eDmValueListObjects:
         {
            m_pqpbEdit->hide();
            QList<CdmObject*> qvlObjects;
            ((CdmValueListObjects*)p_pCdmValue)->GetList(qvlObjects);
            FillTreeWidget(qvlObjects);
         }
         break;
      default:
          INFO("No List or Map Type");
      }

   }
}

/** +-=---------------------------------------------------------Mi 9. Jan 14:53:12 2013-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QList<CdmObject*> p_rqvlList               //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Mi 9. Jan 14:53:12 2013-----------*/
void CoedtwList::FillTreeWidget(QList<CdmObject*> p_rqvlList)
{
   QList<CdmObject*>::iterator qllIt = p_rqvlList.begin();
   QList<CdmObject*>::iterator qllItEnd = p_rqvlList.end();
   m_pqtwTreeWidget->setColumnCount(1);
   m_pqtwTreeWidget->setHeaderLabel(tr("Werte"));

   for (; qllIt != qllItEnd; ++qllIt)
   {
      CdmObject* pObject = (*qllIt);
      
      if (pObject)
      {
         QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
         pqtwItem->setText(0, pObject->GetCaption());
         pqtwItem->setData(0, Qt::UserRole, pObject->GetUri());
      }
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 19:17:23 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QList<QString> p_rqvlList                  //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:17:23 2008-----------*/
void CoedtwList::FillTreeWidget(QList<QString> p_rqvlList)
{
   QList<QString>::iterator qllIt = p_rqvlList.begin();
   QList<QString>::iterator qllItEnd = p_rqvlList.end();
   m_pqtwTreeWidget->setColumnCount(1);
   m_pqtwTreeWidget->setHeaderLabel(tr("Werte"));

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QString qstrValue = (*qllIt);
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrValue);
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 19:17:31 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QList<int> p_rqvlList                      //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:17:31 2008-----------*/
void CoedtwList::FillTreeWidget(QList<int> p_rqvlList)
{
   QList<int>::iterator qllIt = p_rqvlList.begin();
   QList<int>::iterator qllItEnd = p_rqvlList.end();
   m_pqtwTreeWidget->setColumnCount(1);
   m_pqtwTreeWidget->setHeaderLabel(tr("Werte"));

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QString qstrValue = QString::number(*qllIt);
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrValue);
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 19:17:37 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QList<double> p_rqvlList                   //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:17:37 2008-----------*/
void CoedtwList::FillTreeWidget(QList<double> p_rqvlList)
{
   QList<double>::iterator qllIt = p_rqvlList.begin();
   QList<double>::iterator qllItEnd = p_rqvlList.end();
   m_pqtwTreeWidget->setColumnCount(1);
   m_pqtwTreeWidget->setHeaderLabel(tr("Werte"));

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QString qstrValue = QString::number(*qllIt);
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrValue);
   }
}


/** +-=---------------------------------------------------------Do 4. Sep 19:17:43 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<QString, QString> p_rqmIntDouble            //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:17:43 2008-----------*/
void CoedtwList::FillTreeWidget(QMap<QString, QString> p_rqmIntDouble)
{
   QMap<QString, QString>::iterator qmIt = p_rqmIntDouble.begin();
   QMap<QString, QString>::iterator qmItEnd = p_rqmIntDouble.end();
   m_pqtwTreeWidget->setColumnCount(2);
   QStringList qstrList;
   qstrList.append(tr("Schlüssel"));
   qstrList.append(tr("Wert"));
   m_pqtwTreeWidget->setHeaderLabels(qstrList);

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = qmIt.key();
      QString qstrData = qmIt.value();
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrKey);
      pqtwItem->setText(1, qstrData);
   }
}


/** +-=---------------------------------------------------------Do 4. Sep 19:17:50 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<QString, double> p_rqmIntDouble             //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:17:50 2008-----------*/
void CoedtwList::FillTreeWidget(QMap<QString, double> p_rqmIntDouble)
{
   QMap<QString, double>::iterator qmIt = p_rqmIntDouble.begin();
   QMap<QString, double>::iterator qmItEnd = p_rqmIntDouble.end();
   m_pqtwTreeWidget->setColumnCount(2);
   QStringList qstrList;
   qstrList.append(tr("Schlüssel"));
   qstrList.append(tr("Wert"));
   m_pqtwTreeWidget->setHeaderLabels(qstrList);

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = qmIt.key();
      QString qstrData = QString::number(qmIt.value());
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrKey);
      pqtwItem->setText(1, qstrData);
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 19:17:57 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<QString, int> p_rqmIntDouble                //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:17:57 2008-----------*/
void CoedtwList::FillTreeWidget(QMap<QString, int> p_rqmIntDouble)
{
   QMap<QString, int>::iterator qmIt = p_rqmIntDouble.begin();
   QMap<QString, int>::iterator qmItEnd = p_rqmIntDouble.end();
   m_pqtwTreeWidget->setColumnCount(2);
   QStringList qstrList;
   qstrList.append(tr("Schlüssel"));
   qstrList.append(tr("Wert"));
   m_pqtwTreeWidget->setHeaderLabels(qstrList);

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = qmIt.key();
      QString qstrData = QString::number(qmIt.value());
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrKey);
      pqtwItem->setText(1, qstrData);
   }
}


/** +-=---------------------------------------------------------Do 4. Sep 19:18:02 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<int, int> p_rqmIntDouble                    //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:18:02 2008-----------*/
void CoedtwList::FillTreeWidget(QMap<int, int> p_rqmIntDouble)
{
   QMap<int, int>::iterator qmIt = p_rqmIntDouble.begin();
   QMap<int, int>::iterator qmItEnd = p_rqmIntDouble.end();
   m_pqtwTreeWidget->setColumnCount(2);
   QStringList qstrList;
   qstrList.append(tr("Schlüssel"));
   qstrList.append(tr("Wert"));
   m_pqtwTreeWidget->setHeaderLabels(qstrList);

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = QString::number(qmIt.key());
      QString qstrData = QString::number(qmIt.value());
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrKey);
      pqtwItem->setText(1, qstrData);
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 19:18:12 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<int, QString> p_rqmIntDouble                //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:18:12 2008-----------*/
void CoedtwList::FillTreeWidget(QMap<int, QString> p_rqmIntDouble)
{
   QMap<int, QString>::iterator qmIt = p_rqmIntDouble.begin();
   QMap<int, QString>::iterator qmItEnd = p_rqmIntDouble.end();
   m_pqtwTreeWidget->setColumnCount(2);
   QStringList qstrList;
   qstrList.append(tr("Schlüssel"));
   qstrList.append(tr("Wert"));
   m_pqtwTreeWidget->setHeaderLabels(qstrList);

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = QString::number(qmIt.key());
      QString qstrData = qmIt.value();
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrKey);
      pqtwItem->setText(1, qstrData);
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 19:18:18 2008-----------*
 * @method  CoedtwList::FillTreeWidget                       // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<int, double> p_rqmIntDouble                 //                                   *
 * @comment This method fills the treewidget.                                                     *
 *----------------last changed: --------------------------------Do 4. Sep 19:18:18 2008-----------*/
void CoedtwList::FillTreeWidget(QMap<int, double> p_rqmIntDouble)
{
   QMap<int, double>::iterator qmIt = p_rqmIntDouble.begin();
   QMap<int, double>::iterator qmItEnd = p_rqmIntDouble.end();
   m_pqtwTreeWidget->setColumnCount(2);
   QStringList qstrList;
   qstrList.append(tr("Schlüssel"));
   qstrList.append(tr("Wert"));
   m_pqtwTreeWidget->setHeaderLabels(qstrList);

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = QString::number(qmIt.key());
      QString qstrData = QString::number(qmIt.value());
      QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwTreeWidget);
      pqtwItem->setText(0, qstrKey);
      pqtwItem->setText(1, qstrData);
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 18:58:11 2008-----------*
 * @method  CoedtwList::ValueChangedSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *----------------last changed: --------------------------------Do 4. Sep 18:58:11 2008-----------*/
void CoedtwList::ValueChangedSlotByUser()
{
}

/** +-=---------------------------------------------------------Do 4. Sep 18:58:18 2008-----------*
 * @method  CoedtwList::SetReadOnly                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                            *
 *----------------last changed: --------------------------------Do 4. Sep 18:58:18 2008-----------*/
void CoedtwList::SetReadOnly()
{
   m_pqpbEdit->hide();
}

void CoedtwList::SetEditable()
{
    m_pqpbEdit->show();
}

/** +-=---------------------------------------------------------Do 4. Sep 18:58:24 2008-----------*
 * @method  CoedtwList::EditClickedSlot                      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the edit button was clicked. it opens the edit            *
 *          dialog.                                                                               *
 *----------------last changed: --------------------------------Do 4. Sep 18:58:24 2008-----------*/
void CoedtwList::EditClickedSlot()
{
   CoedtwAddValueDlgIf* pCoedtwAddValueDlgIf = nullptr;

   QList<QTreeWidgetItem*> qlItems = m_pqtwTreeWidget->selectedItems();

   if (qlItems.count() == 1)
   {
      pCoedtwAddValueDlgIf->SetKey(qlItems.at(0)->text(0));
      pCoedtwAddValueDlgIf->SetValue(qlItems.at(0)->text(1));
      switch(m_rpCdmValue->GetValueType())
      {
      case eDmValueDictIntDouble:
         {
            pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);
            
            if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
            {
               ((CdmValueDictIntDouble*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsInt(), 
                  pCoedtwAddValueDlgIf->GetValueAsDouble());
            }
         }
         break;
      case eDmValueDictIntString:
         {
            pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

            if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
            {
               ((CdmValueDictIntString*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsInt(), 
                  pCoedtwAddValueDlgIf->GetValueAsString());
            }
         }
         break;
      case eDmValueDictIntInt:
         {
            pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

            if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
            {
               ((CdmValueDictIntInt*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsInt(), 
                  pCoedtwAddValueDlgIf->GetValueAsInt());
            }
         }
         break;
      case eDmValueDictStringDouble:
         {
            pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

            if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
            {
               ((CdmValueDictStringDouble*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsString(), 
                  pCoedtwAddValueDlgIf->GetValueAsDouble());

            }
         }
         break;
      case eDmValueDictStringInt:
         {
            pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

            if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
            {
               ((CdmValueDictStringInt*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsString(), 
                  pCoedtwAddValueDlgIf->GetValueAsInt());
            }
         }
         break;
      case eDmValueDictStringString:
         {
            pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

            if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
            {
               ((CdmValueDictStringString*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsString(), 
                  pCoedtwAddValueDlgIf->GetValueAsString());
            }
         }
         break;
      case eDmValueListDouble:
         {
            double dValue = QInputDialog::getDouble(nullptr, tr("Wert hinzufügen"), tr("Bitte tragen Sie den Wert ein."));
            ((CdmValueListDouble*)m_rpCdmValue)->AddValue(dValue);
         }
         break;
      case eDmValueListObjects:
         {
            CdmClass* pClass = CwmsClassSelectionIf::GetClass(nullptr);

            if (pClass)
            {
               CdmObjectContainer* pList = CwmsContainerSelectionIf::GetObjectContainer(pClass->GetSchemeId(), pClass->GetId(), nullptr);

               if (pList)
               {
                  CdmObject* pObject = CwmsObjectSelectionIf::GetObject(pList, nullptr, nullptr);

                  if (pObject)
                  {
                     ((CdmValueListObjects*)m_rpCdmValue)->AddValue(pObject);
                  }
               }
            }
         }
          break;
      default:
          ERR("Wrong type for List");
      }

      SetValue(m_rpCdmValue);
   }
   else
   {
      CdmMessageManager::warning(tr("Bitte Auswahl anpassen"), 
                           tr("Es darf höchstens eine Zeile ausgewählt sein."));
   }
}

/** +-=---------------------------------------------------------Do 4. Sep 18:58:44 2008-----------*
 * @method  CoedtwList::AddClickedSlot                       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment adds a new item to the list.                                                          *
 *----------------last changed: --------------------------------Do 4. Sep 18:58:44 2008-----------*/
void CoedtwList::AddClickedSlot()
{
   CoedtwAddValueDlgIf* pCoedtwAddValueDlgIf = nullptr;
   switch(m_rpCdmValue->GetValueType())
   {
   case eDmValueDictIntDouble:
      {
         pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

         if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
         {
            ((CdmValueDictIntDouble*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsInt(), 
                                                             pCoedtwAddValueDlgIf->GetValueAsDouble());
         }
      }
      break;
   case eDmValueDictIntString:
      {
         pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

         if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
         {
            ((CdmValueDictIntString*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsInt(), 
                                                             pCoedtwAddValueDlgIf->GetValueAsString());
         }
      }
      break;
   case eDmValueDictIntInt:
      {
         pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

         if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
         {
            ((CdmValueDictIntInt*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsInt(), 
                                                             pCoedtwAddValueDlgIf->GetValueAsInt());
         }
      }
      break;
   case eDmValueDictStringDouble:
      {
         pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

         if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
         {
            ((CdmValueDictStringDouble*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsString(), 
                                                             pCoedtwAddValueDlgIf->GetValueAsDouble());

         }
      }
      break;
   case eDmValueDictStringInt:
      {
         pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

         if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
         {
            ((CdmValueDictStringInt*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsString(), 
                                                             pCoedtwAddValueDlgIf->GetValueAsInt());
         }
      }
      break;
   case eDmValueDictStringString:
      {
         pCoedtwAddValueDlgIf = new CoedtwAddValueDlgIf(nullptr);

         if (pCoedtwAddValueDlgIf->exec() == QDialog::Accepted)
         {
            ((CdmValueDictStringString*)m_rpCdmValue)->SetValue(pCoedtwAddValueDlgIf->GetKeyAsString(), 
                                                             pCoedtwAddValueDlgIf->GetValueAsString());
         }
      }
      break;
   case eDmValueListDouble:
      {
         double dValue = QInputDialog::getDouble(nullptr, tr("Wert hinzufügen"), tr("Bitte tragen Sie den Wert ein."));
         ((CdmValueListDouble*)m_rpCdmValue)->AddValue(dValue);
      }

      break;
   case eDmValueListInt:
      {
         int iValue = QInputDialog::getInt(nullptr, tr("Wert hinzufügen"), tr("Bitte tragen Sie den Wert ein."));
         ((CdmValueListInt*)m_rpCdmValue)->AddValue(iValue);
      }

      break;
   case eDmValueListString:
      {
         QString qstrValue = QInputDialog::getText(nullptr, tr("Wert hinzufügen"), tr("Bitte tragen Sie den Wert ein."));
         ((CdmValueListString*)m_rpCdmValue)->AddValue(qstrValue);
      }

      break;
   case eDmValueListObjects:
      {
         CdmClass *pListObjectClass = getListObjectClass(m_rpCdmValue);

         if(pListObjectClass)
         {
             if(pListObjectClass->IsEventSourcingActive() || pListObjectClass->IsEventClass())
             {
                 FillValueList(pListObjectClass);
             }
         }
         else
         {
             const CdmMember* pMember = m_rpCdmValue->GetMember();
             CdmClass* pClass = nullptr;

             if (CHKPTR(pMember))
             {
                if (pMember->GetClassReference() > 0)
                {
                   CdmClassManager* pClassManager = pMember->GetClassManager();

                   if (CHKPTR(pClassManager))
                   {
                      pClass = pClassManager->FindClassById(pMember->GetClassReference());

                      if (!pClass)
                      {
                         pClass = CwmsClassSelectionIf::GetClass(nullptr);
                      }
                   }
                }
                else
                {
                   pClass = CwmsClassSelectionIf::GetClass(nullptr);
                }
             }

             if (pClass)
             {
                CdmObjectContainer* pList = CwmsContainerSelectionIf::GetObjectContainer(pClass->GetSchemeId(), pClass->GetId(), nullptr);

                if (pList)
                {
                   CdmObject* pObject = CwmsObjectSelectionIf::GetObject(pList, nullptr, nullptr);

                   if (pObject)
                   {
                      ((CdmValueListObjects*)m_rpCdmValue)->AddValue(pObject);
                   }
                }
             }
         }
      }

      break;
   default:
       ERR("Wrong type for List");
   }

   SetValue(m_rpCdmValue);
}

CdmClass *CoedtwList::getListObjectClass(CdmValue *pCdmValue)
{
    return findListObjectClassInPackage(pCdmValue->GetKeyname());
}

CdmClass *CoedtwList::findListObjectClassInPackage(QString qstrClassKeyname)
{
    CdmSessionManager *pSessionManager = CdmSessionManager::GetSessionManager();
    CdmDataProvider *pDataProvider = pSessionManager->GetDataProvider();
    CdmClassManager *pClassManager = pDataProvider->GetClassManager();

    QList<CdmPackage*> qlPackages = pClassManager->GetPackageList();
    for(int i = 0; i < qlPackages.count(); ++i)
    {
        CdmPackage *pPackage = qlPackages.at(i);
        QList<CdmClass*> qlClasses = pPackage->GetClassList();
        for(int i = 0; i < qlClasses.count(); ++i)
        {
            QString qstr_Keyname = qlClasses.at(i)->GetKeyname();
            if(qstr_Keyname == qstrClassKeyname)
            {
                return qlClasses.at(i);
            }
        }
    }
    return nullptr;
}

void CoedtwList::FillValueList(CdmClass *pListObjectClass)
{
    if (pListObjectClass)
    {
       CdmObjectContainer* pList = CwmsContainerSelectionIf::GetObjectContainer(pListObjectClass->GetSchemeId(), pListObjectClass->GetId(), nullptr);

       if (pList)
       {
          CdmObject* pObject = CwmsObjectSelectionIf::GetObject(pList, nullptr, nullptr);

          if (pObject)
          {
             ((CdmValueListObjects*)m_rpCdmValue)->AddEventValue(pObject, pListObjectClass);
          }
       }
    }
}

/** +-=---------------------------------------------------------Do 4. Sep 18:58:51 2008-----------*
 * @method  CoedtwList::RemoveClickedSlot                    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment removes the selected items from list.                                                 *
 *----------------last changed: --------------------------------Do 4. Sep 18:58:51 2008-----------*/
void CoedtwList::RemoveClickedSlot()
{
   QList<QTreeWidgetItem*> qlItems = m_pqtwTreeWidget->selectedItems();

   for (int iCounter = 0; iCounter < qlItems.size(); ++iCounter)
   {
      QTreeWidgetItem* pqtwItem = qlItems.at(iCounter);

      if(pqtwItem)
      {
         QString qstrKey = pqtwItem->text(0);
         QString qstrUri = pqtwItem->data(0, Qt::UserRole).toString();

         switch(m_rpCdmValue->GetValueType())
         {
         case eDmValueDictIntDouble:
            ((CdmValueDictIntDouble*)m_rpCdmValue)->RemoveValue(qstrKey.toInt());
            break;
         case eDmValueDictIntString:
            ((CdmValueDictIntString*)m_rpCdmValue)->RemoveValue(qstrKey.toInt());
            break;
         case eDmValueDictIntInt:
            ((CdmValueDictIntInt*)m_rpCdmValue)->RemoveValue(qstrKey.toInt());
            break;
         case eDmValueDictStringDouble:
            ((CdmValueDictStringDouble*)m_rpCdmValue)->RemoveValue(qstrKey);
            break;
         case eDmValueDictStringInt:
            ((CdmValueDictStringInt*)m_rpCdmValue)->RemoveValue(qstrKey);
            break;
         case eDmValueDictStringString:
            ((CdmValueDictStringString*)m_rpCdmValue)->RemoveValue(qstrKey);
            break;
         case eDmValueListDouble:
            ((CdmValueListDouble*)m_rpCdmValue)->RemoveValue(qstrKey.toDouble());
            break;
         case eDmValueListInt:
            ((CdmValueListInt*)m_rpCdmValue)->RemoveValue(qstrKey.toInt());
            break;
         case eDmValueListString:
            ((CdmValueListString*)m_rpCdmValue)->RemoveValue(qstrKey);
            break;
         case eDmValueListObjects:
            {
              CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

               if (pManager)
               {
                  CdmObject* pObject = (CdmObject*) pManager->GetUriObject(qstrUri);
                  ((CdmValueListObjects*)m_rpCdmValue)->RemoveValue(pObject);
               }
            }
            break;               
         default:
             INFO("No List or Dict type");
         }

      }
   }

   SetValue(m_rpCdmValue);
}
