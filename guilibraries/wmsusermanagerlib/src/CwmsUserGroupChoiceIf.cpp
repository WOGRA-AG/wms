// Header is missing impl started on 27.1.2005


// System and QT includes


// WMS Includes
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"

// own Includes
#include "CwmsUserManagerIf.h"
#include "CwmsUserGroupChoiceIf.h"



/** +-=---------------------------------------------------------Do 27. Jan 07:17:06 2005----------*
 * @method  CwmsUserGroupChoiceIf::CwmsUserGroupChoiceIf               // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 27. Jan 07:17:06 2005----------*/
CwmsUserGroupChoiceIf::CwmsUserGroupChoiceIf(QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
}


/** +-=---------------------------------------------------------Do 27. Jan 07:17:12 2005----------*
 * @method  CwmsUserGroupChoiceIf::~CwmsUserGroupChoiceIf              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsUserGroupChoiceIf                                              *
 *                                                                                                *
 *----------------last changed: --------------------------------Do 27. Jan 07:17:12 2005----------*/
CwmsUserGroupChoiceIf::~CwmsUserGroupChoiceIf(  )
{
}

int CwmsUserGroupChoiceIf::GetSelectedGroupId()
{
   int iGroupId = -1;
   QTreeWidgetItem* pItem = CwmsUserManagerIf::GetSelectedItem(m_pqlvGroups);
   
   if(pItem)
   {
      iGroupId = pItem->data(0, Qt::UserRole).toInt();
   }

   return iGroupId;
}

/** +-=---------------------------------------------------------Do 27. Jan 07:17:52 2005----------*
 * @method  CwmsUserGroupChoiceIf::OKClickedSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the OK Button was clicked.                                *
 *----------------last changed: --------------------------------Do 27. Jan 07:17:52 2005----------*/
void CwmsUserGroupChoiceIf::OKClickedSlot(  )
{
   accept();
}

/** +-=---------------------------------------------------------Do 27. Jan 07:18:13 2005----------*
 * @method  CwmsUserGroupChoiceIf::CancelClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the cancel button was clicked.                            *
 *----------------last changed: --------------------------------Do 27. Jan 07:18:13 2005----------*/
void CwmsUserGroupChoiceIf::CancelClickedSlot(  )
{
   reject();
}

qint64 CwmsUserGroupChoiceIf::GetGroupSelection(QWidget* parent)
{
  qint64 lGroupId = -1;
   CwmsUserGroupChoiceIf* pCwmsUserGroupChoiceIf = new CwmsUserGroupChoiceIf(parent);

   if(pCwmsUserGroupChoiceIf->exec() == QDialog::Accepted)
   {
      lGroupId = pCwmsUserGroupChoiceIf->GetSelectedGroupId();
   }

   delete pCwmsUserGroupChoiceIf;
   return lGroupId;
}

void CwmsUserGroupChoiceIf::SearchGroupClickedSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
    QString qstrSearchString = m_pqleInputSearch->text();
    QList<CumUserGroup*> qlGroups = pCumUserManager->FindUserGroupsByNameUnmanaged(qstrSearchString);
    m_pqlvGroups->clear();

    QList<CumUserGroup*>::iterator qllIt = qlGroups.begin();
    QList<CumUserGroup*>::iterator qllItEnd = qlGroups.end();

    for(; qllIt != qllItEnd; ++qllIt)
    {
       CumUserGroup* pGroup = *qllIt;

       if(pGroup)
       {
          QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvGroups);
          pItem->setText(0, QString::number(pGroup->GetId()));
          pItem->setData(0, Qt::UserRole, pGroup->GetId());
          pItem->setText(1, pGroup->GetGroupName());
       }

       DELPTR(pGroup);
    }
    qlGroups.clear();
}
