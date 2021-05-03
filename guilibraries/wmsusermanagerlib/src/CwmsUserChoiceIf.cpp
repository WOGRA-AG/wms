// Header is missing impl started on 27.1.2005


// System and QT includes


// WMS Includes
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CumUserManager.h"
#include "CumUser.h"

// own Includes
#include "CwmsUserManagerIf.h"
#include "CwmsUserChoiceIf.h"



/** +-=---------------------------------------------------------Do 27. Jan 07:17:06 2005----------*
 * @method  CwmsUserChoiceIf::CwmsUserChoiceIf               // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 27. Jan 07:17:06 2005----------*/
CwmsUserChoiceIf::CwmsUserChoiceIf(QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
}


/** +-=---------------------------------------------------------Do 27. Jan 07:17:12 2005----------*
 * @method  CwmsUserChoiceIf::~CwmsUserChoiceIf              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsUserChoiceIf                                              *
 *                                                                                                *
 *----------------last changed: --------------------------------Do 27. Jan 07:17:12 2005----------*/
CwmsUserChoiceIf::~CwmsUserChoiceIf(  )
{
}

/** +-=---------------------------------------------------------Mo 29. Okt 15:16:59 2012----------*
 * @method  CwmsUserChoiceIf::GetSelectedUserId              // public                            *
 * @return  int                                              //                                   *
 * @comment This method returns the selected User.                                                *
 *----------------last changed: --------------------------------Mo 29. Okt 15:16:59 2012----------*/
int CwmsUserChoiceIf::GetSelectedUserId()
{
   int iUserId = -1;
   QTreeWidgetItem* pItem = CwmsUserManagerIf::GetSelectedItem(m_pqlvUsers);
   
   if(pItem)
   {
      iUserId = pItem->data(0, Qt::UserRole).toInt();
   }

   return iUserId;
}

/** +-=---------------------------------------------------------Do 27. Jan 07:17:52 2005----------*
 * @method  CwmsUserChoiceIf::OKClickedSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the OK Button was clicked.                                *
 *----------------last changed: --------------------------------Do 27. Jan 07:17:52 2005----------*/
void CwmsUserChoiceIf::OKClickedSlot(  )
{
   accept();
}

/** +-=---------------------------------------------------------Do 27. Jan 07:18:13 2005----------*
 * @method  CwmsUserChoiceIf::CancelClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the cancel button was clicked.                            *
 *----------------last changed: --------------------------------Do 27. Jan 07:18:13 2005----------*/
void CwmsUserChoiceIf::CancelClickedSlot(  )
{
   reject();
}


/** +-=---------------------------------------------------------Do 27. Jan 07:42:30 2005----------*
 * @method  CwmsUserChoiceIf::GetUserSelection               // public, static                    *
 * @return  long                                             // UserId                            *
 * @param   QWidget* parent                                  //                                   *
 * @comment This static member function gets a selected user from the complete user list.         *
 *----------------last changed: --------------------------------Do 27. Jan 07:42:30 2005----------*/
long CwmsUserChoiceIf::GetUserSelection(  QWidget* parent )
{
   long lUserId = -1;
   CwmsUserChoiceIf* pCwmsUserChoiceIf = new CwmsUserChoiceIf(parent);

   if(pCwmsUserChoiceIf->exec() == QDialog::Accepted)
   {
      lUserId = pCwmsUserChoiceIf->GetSelectedUserId();
   }

   delete pCwmsUserChoiceIf;
   return lUserId;
}

void CwmsUserChoiceIf::SearchUserClickedSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
    QString qstrSearchString = m_pqleInputSearch->text();
    QList<CumUser*> qllUsers = pCumUserManager->FindUsersUnmanaged(qstrSearchString);

    m_pqlvUsers->clear();

    QList<CumUser*>::iterator qvlIt    = qllUsers.begin();
    QList<CumUser*>::iterator qvlItEnd = qllUsers.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
       CumUser* pCumUser = (*qvlIt);

       if(pCumUser)
       {
          QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvUsers);
          pItem->setText(0, QString::number(pCumUser->GetId()));
          pItem->setData(0, Qt::UserRole, (int)pCumUser->GetId());
          pItem->setText(1, pCumUser->GetFirstName());
          pItem->setText(2, pCumUser->GetLastName());
          pItem->setText(3, pCumUser->GetLogin());
       }
    }

    qvlIt    = qllUsers.begin();
    qvlItEnd = qllUsers.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        DELPTR(*qvlIt);
    }

    qllUsers.clear();
}
