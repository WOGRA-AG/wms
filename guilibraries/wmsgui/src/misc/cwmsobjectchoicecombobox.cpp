/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and Qt Includes
#include <QLinkedList>
#include <QKeyEvent>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmValue.h"
#include "CdmClass.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"


// own Includes
#include "CdmEnhancedQueryProxy.h"
#include "cwmsobjectchoicecombobox.h"


/** +-=---------------------------------------------------------So 8. Jan 21:53:55 2006-----------*
 * @method  CwmsObjectChoiceComboBox::CwmsObjectChoiceComboBox // public                          *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 8. Jan 21:53:55 2006-----------*/
CwmsObjectChoiceComboBox::CwmsObjectChoiceComboBox(  QWidget* parent)
: QComboBox(parent),
  m_rpCdmProxy(nullptr)
{
   connect(this, SIGNAL(activated(int)), this, SLOT(ComboBoxActivatedSlot()));
}

/** +-=---------------------------------------------------------So 8. Jan 21:54:07 2006-----------*
 * @method  CwmsObjectChoiceComboBox::~CwmsObjectChoiceComboBox // public, virtual                *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectChoiceComboBox                                      *
 *                                                                                                *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 8. Jan 21:54:07 2006-----------*/
CwmsObjectChoiceComboBox::~CwmsObjectChoiceComboBox(  )
{
   // nothing to do because the map contains only references
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:44:55 2012-----------*
 * @method  CwmsObjectChoiceComboBox::SetProxy               // public                            *
 * @return  void                                             //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCdmProxy               //                                   *
 * @comment This method sets the proxy.                                                           *
 *----------------last changed: --------------------------------Mi 3. Okt 11:44:55 2012-----------*/
void CwmsObjectChoiceComboBox::SetProxy(CdmEnhancedQueryProxy* p_pCdmProxy)
{
   m_rpCdmProxy = p_pCdmProxy;
   
   if (m_rpCdmProxy)
   {
      connect(m_rpCdmProxy, SIGNAL(UpdateSignal()), this, SLOT(Refresh()));
   }
}

/** +-=---------------------------------------------------------Fr 10. Feb 10:12:16 2012----------*
 * @method  CwmsObjectChoiceComboBox::SetObjectListAndDisplayValue // public                      *
 * @return  void                                             //                                   *
 * @param   QString p_qstrObjectListKeyname                  //                                   *
 * @param   QString p_qstrValueKeyname                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 10. Feb 10:12:16 2012----------*/
void CwmsObjectChoiceComboBox::SetContainerAndDisplayValue(QString p_qstrObjectListKeyname,
                                                            QString p_qstrValueKeyname)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(pCdmManager->GetCurrentScheme());

      if(CHKPTR(pContainerManager))
      {
         CdmObjectContainer* pContainer = nullptr;
         pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrObjectListKeyname);

         if (pContainer)
         {
            SetContainerAndDisplayValue(pContainer, p_qstrValueKeyname);
         }
      }
   }
}

void CwmsObjectChoiceComboBox::FillProxyData()
{
    if (CHKPTR(m_rpCdmProxy))
    {
       m_rpCdmProxy->CreateQuery(GetContainer());
        CdmQuery* pCdmQuery = m_rpCdmProxy->GetQuery();
        FillWidget(*pCdmQuery);
    }
}

/** +-=---------------------------------------------------------So 8. Jan 21:55:22 2006-----------*
 * @method  CwmsObjectChoiceComboBox::SetObjectListAndDisplayValue // public                      *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrValueKeyname                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 8. Jan 21:55:22 2006-----------*/
void CwmsObjectChoiceComboBox::SetContainerAndDisplayValue(  CdmObjectContainer* p_pContainer,
                                                             QString p_qstrValueKeyname )
{
   if(p_pContainer)
   {
      m_qstrDisplayName = p_qstrValueKeyname;

      if (p_pContainer != GetContainer())
      {
         CdmContainerAdaptor::SetContainer(p_pContainer);
      }
      
      if(m_rpCdmProxy)
      {
         QLinkedList<long> qvlResults;

         m_rpCdmProxy->CreateQuery(p_pContainer);
         CdmQuery* pCdmQuery = m_rpCdmProxy->GetQuery();

         if (CHKPTR(pCdmQuery))
         {
            pCdmQuery->DeleteResultElements();
            pCdmQuery->AddResultElement(p_qstrValueKeyname);

            if (pCdmQuery->Execute() > 0)
            {
               FillWidget(*pCdmQuery);
            }
         }
      }
      else
      {
         CdmQueryEnhanced cCdmQuery;
         cCdmQuery.DeleteResultElements();
         cCdmQuery.SetContainer(p_pContainer);

         if (!p_qstrValueKeyname.isEmpty())
         {
            cCdmQuery.AddResultElement(p_qstrValueKeyname);
         }
         else
         {
            const CdmClass* pCdmClass = p_pContainer->GetClass();

            if (CHKPTR(pCdmClass))
            {
               cCdmQuery.AddResultElement(pCdmClass->GetCaptionMemberKeyname());
            }
         }
         

         if (SUCCESSFULL(cCdmQuery.Execute()))
         {
            FillWidget(cCdmQuery);
         }
      }
   }
   else
   {
      WARNING("Invalid Pointer!");
   }
}

void CwmsObjectChoiceComboBox::SetContainerAndDisplayFilteredValue(CdmObjectContainer* p_pContainer,
                                                             QString p_qstrValueKeyname, QString qstrFilter)
{
   if(p_pContainer)
   {
      m_qstrDisplayName = p_qstrValueKeyname;

      if (p_pContainer != GetContainer())
      {
         CdmContainerAdaptor::SetContainer(p_pContainer);
      }

      QString qstrWql = QString("select from %1").arg(p_pContainer->GetKeyname());
      qstrWql += QString("where Name = \"%2\"").arg(qstrFilter);
      CdmQueryEnhanced *pQuery = nullptr;
      pQuery = dynamic_cast<CdmQueryEnhanced*> (CdmQueryBuilder::ExecuteQuery(qstrWql));

      if (CHKPTR(pQuery))
      {
          pQuery->DeleteResultElements();
          pQuery->SetContainer(p_pContainer);
          if (!p_qstrValueKeyname.isEmpty())
          {
             pQuery->AddResultElement(p_qstrValueKeyname);
          }
          else
          {
             const CdmClass* pCdmClass = p_pContainer->GetClass();

             if (CHKPTR(pCdmClass))
             {
                pQuery->AddResultElement(pCdmClass->GetCaptionMemberKeyname());
             }
          }

          FillWidget(*pQuery);
      }
   }
   else
   {
      WARNING("Invalid Pointer!");
   }
}



void CwmsObjectChoiceComboBox::SetContainerAndDisplayValueByWql(CdmObjectContainer* p_pContainer, QString qstrWql)
{
    if(CHKPTR(p_pContainer) && !qstrWql.isEmpty())
    {
       if (p_pContainer != GetContainer())
       {
          CdmContainerAdaptor::SetContainer(p_pContainer);
       }

       QScopedPointer<CdmQueryEnhanced> pQuery(dynamic_cast<CdmQueryEnhanced*> (CdmQueryBuilder::ExecuteQuery(qstrWql)));

       //@Wolfi: hier hab ich die Query und er hat alles drin. Lediglich beim FillWidget befüllt er es noch nicht, obwohl der Ansprechpartner da ist.
       if (CHKPTR(pQuery))
       {
           FillWidget(*pQuery);
       }
    }
    else
    {
       WARNING("Invalid Pointer!");
    }
}

void CwmsObjectChoiceComboBox::SetContainerAndDisplayValueByWql(QString qstrWql)
{
    if(!qstrWql.isEmpty())
    {
       QScopedPointer<CdmQueryEnhanced> pQuery(dynamic_cast<CdmQueryEnhanced*> (CdmQueryBuilder::ExecuteQuery(qstrWql)));

       if (CHKPTR(pQuery))
       {
           CdmObjectContainer* pContainer = pQuery->GetContainer();
           if (pContainer != GetContainer())
           {
              CdmContainerAdaptor::SetContainer(pContainer);
           }

           FillWidget(*pQuery);
       }
    }
    else
    {
       WARNING("Invalid Pointer!");
    }
}

/** +-=---------------------------------------------------------Sa 7. Mai 13:58:23 2011-----------*
 * @method  CwmsObjectChoiceComboBox::FillWidget             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmQueryEnhanced& p_rcCdmQuery                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 13:58:23 2011-----------*/
void CwmsObjectChoiceComboBox::FillWidget(CdmQuery& p_rcCdmQuery)
{
    ClearEntries();
   //int iIndex = 0;
   m_qmEntries.insert("-", 0);

   int iCount = p_rcCdmQuery.GetResultCount();
   int iColumns = p_rcCdmQuery.GetColumnCount();

   for (int iRowPos = 0; iRowPos < iCount; ++iRowPos)
   {
      bool bFirst = true;
      QString qstrDisplayValue;

      QStringList qstrlDisplayValue;

      for (int iColPos = 0; iColPos < iColumns; ++iColPos)
      {
         if (!bFirst)
         {
            qstrlDisplayValue.append(", ");
         }

         QString qstrValue = p_rcCdmQuery.GetResultAt(iColPos, iRowPos).toString();

         if(!qstrValue.isEmpty())
         {
             qstrlDisplayValue.append(qstrValue);
             bFirst = false;
         }
         else
         {
             bFirst = true;
         }
      }

      if(qstrlDisplayValue.count() == 2)
      {
          qstrDisplayValue = qstrlDisplayValue.at(0);
      }
      else if(qstrlDisplayValue.count() == 4)
      {
          qstrDisplayValue += qstrlDisplayValue.at(0);
          qstrDisplayValue += " " + qstrlDisplayValue.at(2);
      }
      else
      {
          for(int i = 0; i < qstrlDisplayValue.count(); ++i)
          {
              qstrDisplayValue += qstrlDisplayValue.at(i);
          }
      }
      
      long lObjectId = p_rcCdmQuery.GetObjectIdAt(iRowPos);

      if (lObjectId > 0)
      {
         AddEntry(lObjectId, qstrDisplayValue);
      }
      else
      {
         ERR("ObjectId not found!");
      }
   }

   FillEntries();
}

/** +-=---------------------------------------------------------Fr 12. Jan 19:54:58 2007----------*
 * @method  CwmsObjectChoiceComboBox::FillDialog             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrValueKeyname                       //                                   *
 * @param   QValueList<long>& p_rqvlObjects                  //                                   *
 * @comment This method fills the Combobox with the results of the proxy.                         *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 12. Jan 19:54:58 2007----------*/
void CwmsObjectChoiceComboBox::FillDialog(CdmObjectContainer* p_pContainer,
                                          QString p_qstrValueKeyname,
                                          QLinkedList<long>& p_rqvlObjects)
{
	ClearEntries();
   QString qstrValueKeyname = p_qstrValueKeyname;

   if (p_pContainer)
   {
      int iIndex = 0;

      m_qmEntries.insert("-", 0);

      if (p_rqvlObjects.count() > 0)
      {
         QLinkedList<long>::iterator qvlIt = p_rqvlObjects.begin();
         QLinkedList<long>::iterator qvlItEnd = p_rqvlObjects.end();

         for(; qvlIt != qvlItEnd; ++qvlIt, ++iIndex)
         {
            long lObjectId = (*qvlIt);
            CdmObject* pCdmObject = p_pContainer->FindObjectById(lObjectId);

            if(CHKPTR(pCdmObject))
            {
               AddEntry(pCdmObject, p_qstrValueKeyname);
            }
         }
      }

      FillEntries();
   }
}

/** +-=---------------------------------------------------------Do 23. Feb 15:45:10 2006----------*
 * @method  CwmsObjectChoiceComboBox::FillDialog             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrValueKeyname                       //                                   *
 * @comment This method fills the objectlist without proxy limitations.                           *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 23. Feb 15:45:10 2006----------*/
void CwmsObjectChoiceComboBox::FillDialog(CdmObjectContainer* p_pContainer,
                                          QString p_qstrValueKeyname)
{
	ClearEntries();

   if(CHKPTR(p_pContainer))
   {
      QLinkedList<CdmObject*> qvlObjects;
      p_pContainer->GetObjectList(qvlObjects);
      int iIndex = 0;

      m_qmEntries.insert("-", 0);
      //insertItem("-");
      ++iIndex;

      QLinkedList<CdmObject*>::iterator qvlIt = qvlObjects.begin();
      QLinkedList<CdmObject*>::iterator qvlItEnd = qvlObjects.end();

      for(; qvlIt != qvlItEnd; ++qvlIt, ++iIndex)
      {
         CdmObject* pCdmObject = (*qvlIt);

         if(CHKPTR(pCdmObject))
         {
            AddEntry(pCdmObject, p_qstrValueKeyname);
         }
      }

      FillEntries();
   }
}

/** +-=---------------------------------------------------------Mo 4. Jan 15:40:53 2010-----------*
 * @method  CwmsObjectChoiceComboBox::AddEntry               // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jan 15:40:53 2010-----------*/
void CwmsObjectChoiceComboBox::AddEntry(CdmObject* p_pCdmObject, QString p_qstrValue)
{
   if(CHKPTR(p_pCdmObject))
   {
      AddEntry(p_pCdmObject->GetId(), p_qstrValue);
   }
}

/** +-=---------------------------------------------------------Sa 7. Mai 14:33:00 2011-----------*
 * @method  CwmsObjectChoiceComboBox::AddEntry               // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 14:33:00 2011-----------*/
void CwmsObjectChoiceComboBox::AddEntry(long p_lObjectId, QString p_qstrValue)
{
    if(m_qmEntries.value(p_qstrValue) != p_lObjectId)
    {
        m_qmEntries.insert(p_qstrValue, p_lObjectId);
    }
}

void CwmsObjectChoiceComboBox::ClearEntries()
{
   clear();
   m_qmEntries.clear();
}

/** +-=---------------------------------------------------------So 4. Apr 18:42:33 2010-----------*
 * @method  CwmsObjectChoiceComboBox::FillEntries            // public                            *
 * @return  void                                             //                                   *
 * @comment fills the entries to the combobox.                                                    *
 *----------------last changed: --------------------------------So 4. Apr 18:42:33 2010-----------*/
void CwmsObjectChoiceComboBox::FillEntries()
{
   if (!m_qmEntries.contains("-"))
   {
      m_qmEntries.insert("-", 0);
   }

   QMap<QString, long>::iterator qmIt = m_qmEntries.begin();
   QMap<QString, long>::iterator qmItEnd = m_qmEntries.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = qmIt.key();
      addItem(qstrKey);
   }
}

/** +-=---------------------------------------------------------Sa 24. Jun 13:35:08 2006----------*
 * @method  CwmsObjectChoiceComboBox::Refresh                // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This method refreshes the dialog and shows the changed data.                          *
 *----------------last changed: Wolfgang GraÃŸhof----------------Sa 24. Jun 13:35:08 2006----------*/
void CwmsObjectChoiceComboBox::Refresh()
{
   // storing the old value
  long lObjectId = GetSelectedObjectId();

   ClearEntries();

   if(CHKPTR(GetContainer()))
   {
      SetContainerAndDisplayValue(GetContainer(), m_qstrDisplayName);
   }

   if (lObjectId > 0)
   {
      SetCurrentObjectId(lObjectId);
   }

}

/** +-=---------------------------------------------------------Fr 1. Jun 10:06:02 2012-----------*
 * @method  CwmsObjectChoiceComboBox::SetCurrentObjectId     // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @comment This method sets the current selected object in the combobox.                         *
 *----------------last changed: --------------------------------Fr 1. Jun 10:06:02 2012-----------*/
void CwmsObjectChoiceComboBox::SetCurrentObjectId(long p_lId)
{
   if(p_lId > 0)
   {
      int iIndex = FindIndexById(p_lId);

      if(iIndex >= 0)
      {
         setCurrentIndex(iIndex);
      }
      else
      {
          setCurrentIndex(0);
      }
   }
   else
   {
      setCurrentIndex(0);
   }
}

/** +-=---------------------------------------------------------So 23. Sep 13:59:53 2012----------*
 * @method  CwmsObjectChoiceComboBox::SetCurrentObject       // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment This method sets the current selected object in the combobox.                         *
 *----------------last changed: --------------------------------So 23. Sep 13:59:53 2012----------*/
void CwmsObjectChoiceComboBox::SetCurrentObject(CdmObject* p_pCdmObject)
{
   if(p_pCdmObject)
   {
      SetCurrentObjectId(p_pCdmObject->GetId());
   }
   else
   {
      setCurrentIndex(0);
   }
}

/** +-=---------------------------------------------------------Fr 1. Jun 10:05:31 2012-----------*
 * @method  CwmsObjectChoiceComboBox::FindIndexById          // private                           *
 * @return  int                                              //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @comment This method finds the idnex of the object.                                            *
 *----------------last changed: --------------------------------Fr 1. Jun 10:05:31 2012-----------*/
int CwmsObjectChoiceComboBox::FindIndexById(long p_lObjectId)
{
   int iRet = -1;

   if(p_lObjectId > 0)
   {
      QMap<QString, long>::iterator qmIt = m_qmEntries.begin();
      QMap<QString, long>::iterator qmItEnd = m_qmEntries.end();

      for(; qmIt != qmItEnd; ++qmIt)
      {
         long lObjectTemp = qmIt.value();

         if(lObjectTemp == p_lObjectId)
         {
            QString qstr = qmIt.key();
            iRet = findText(qmIt.key());
            break;
         }
      }
   }

   return iRet;
}

/** +-=---------------------------------------------------------Fr 1. Jun 10:34:08 2012-----------*
 * @method  CwmsObjectChoiceComboBox::GetSelectedObjectId    // public                            *
 * @return  long                                             //                                   *
 * @comment This method returns the selected object.                                              *
 *----------------last changed: --------------------------------Fr 1. Jun 10:34:08 2012-----------*/
long CwmsObjectChoiceComboBox::GetSelectedObjectId()
{
   QString qstrCurrent = currentText();
   return m_qmEntries[qstrCurrent];
}


/** +-=---------------------------------------------------------Fr 1. Jun 10:35:50 2012-----------*
 * @method  CwmsObjectChoiceComboBox::GetSelectedObject      // public                            *
 * @return  CdmObject*                                       //                                   *
 * @comment This method returns the selected object.                                              *
 *                                                                                                *
 *          This loads the object from server if it is doesn't there use it only if you want      *
 *          to change or display the object.                                                      *
 *----------------last changed: --------------------------------Fr 1. Jun 10:35:50 2012-----------*/
CdmObject* CwmsObjectChoiceComboBox::GetSelectedObject()
{
   CdmObject* pCdmObject = nullptr;
   long lObjectId = GetSelectedObjectId();

   CdmObjectContainer* pContainer = CdmContainerAdaptor::GetContainer();

   if (pContainer)
   {
      pCdmObject = pContainer->FindObjectById(lObjectId);
   }
   
   return pCdmObject;
}

/** +-=---------------------------------------------------------So 8. Jan 22:12:14 2006-----------*
 * @method  CwmsObjectChoiceComboBox::ComboBoxActivatedSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the combobox was activated.                               *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 8. Jan 22:12:14 2006-----------*/
void CwmsObjectChoiceComboBox::ComboBoxActivatedSlot(  )
{
   CdmObject* pCdmObject = GetSelectedObject();

   emit ObjectSelectedSignal();
   emit ObjectSelectedSignal(pCdmObject);
}

/** +-=---------------------------------------------------------Do 27. Dez 12:54:40 2007----------*
 * @method  CwmsObjectChoiceComboBox::TextChangedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the text in the combobox was changed.                     *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 27. Dez 12:54:40 2007----------*/
void CwmsObjectChoiceComboBox::TextChangedSlot()
{
   int iCount = count();
   QString qstrText = currentText();
   QPalette qPalette = palette();


   for (int iCounter = 0; iCounter < iCount; ++iCounter)
   {
      if (qstrText == itemText(iCounter))
      {
         setCurrentIndex(iCounter);  
         ComboBoxActivatedSlot();
         break;
      }
   }
}

/** +-=---------------------------------------------------------So 13. Jan 13:16:02 2008----------*
 * @method  CwmsObjectChoiceComboBox::keyPressEvent          // private                           *
 * @return  void                                             //                                   *
 * @param   QKeyEvent * p_pqKeyEvent                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 13. Jan 13:16:02 2008----------*/
void CwmsObjectChoiceComboBox::keyPressEvent(QKeyEvent * p_pqKeyEvent)
{
   if (CHKPTR(p_pqKeyEvent))
   {
      if (p_pqKeyEvent->key() == Qt::Key_Plus)
      {
         emit PlusPressedSignal();
         p_pqKeyEvent->accept();
      }
      else if (p_pqKeyEvent->key() == Qt::Key_Minus)
      {
         emit MinusPressedSignal();
         p_pqKeyEvent->accept();
      }
      else if (p_pqKeyEvent->key() == Qt::Key_division)
      {
         emit DivisionPressedSignal();
         p_pqKeyEvent->accept();
      }
      else if (p_pqKeyEvent->key() == Qt::Key_multiply)
      {
         emit MultiplyPressedSignal();
         p_pqKeyEvent->accept();
      }
   }

   QComboBox::keyPressEvent(p_pqKeyEvent);
}

/** +-=---------------------------------------------------------Do 16. Sep 20:32:01 2010----------*
 * @method  CwmsObjectChoiceComboBox::ObjectCreatedEvent     // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   long# p_lObjectId                                //                                   *
 * @comment This method will be called if a new object was created.                               *
 *----------------last changed: --------------------------------Do 16. Sep 20:32:01 2010----------*/
void CwmsObjectChoiceComboBox::ObjectCreatedEvent(long)
{
   Refresh();
}

/** +-=---------------------------------------------------------Do 16. Sep 20:32:14 2010----------*
 * @method  CwmsObjectChoiceComboBox::ObjectModifiedEvent    // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   long# p_lObjectId                                //                                   *
 * @comment This mehtod will be called if a object was modified.                                  *
 *----------------last changed: --------------------------------Do 16. Sep 20:32:14 2010----------*/
void CwmsObjectChoiceComboBox::ObjectModifiedEvent(long)
{
}

/** +-=---------------------------------------------------------Do 16. Sep 20:32:26 2010----------*
 * @method  CwmsObjectChoiceComboBox::ObjectRefModifiedEvent // protected                         *
 * @return  void                                             //                                   *
 * @param   long# p_lObjectId                                //                                   *
 * @comment This mehtod will be called if a object was modified.                                  *
 *----------------last changed: --------------------------------Do 16. Sep 20:32:26 2010----------*/
void CwmsObjectChoiceComboBox::ObjectRefModifiedEvent(long)
{
}

/** +-=---------------------------------------------------------Do 16. Sep 20:32:37 2010----------*
 * @method  CwmsObjectChoiceComboBox::ObjectDeletedEvent     // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   long# p_lObjectId                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Sep 20:32:37 2010----------*/
void CwmsObjectChoiceComboBox::ObjectDeletedEvent(long)
{
   Refresh();
}

/** +-=---------------------------------------------------------Do 16. Sep 20:33:05 2010----------*
 * @method  CwmsObjectChoiceComboBox::ObjectCommitedEvent    // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   long# p_lObjectId                                //                                   *
 * @comment This mehtod will be called if a object was modified.                                  *
 *----------------last changed: --------------------------------Do 16. Sep 20:33:05 2010----------*/
void CwmsObjectChoiceComboBox::ObjectCommitedEvent(long)
{
   Refresh();
}

/** +-=---------------------------------------------------------So 13. Jan 13:16:13 2008----------*
 * @method  CwmsObjectChoiceComboBox::PlusPressedSignal      // private, signals                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 13. Jan 13:16:13 2008----------*/


/** +-=---------------------------------------------------------So 13. Jan 13:16:20 2008----------*
 * @method  CwmsObjectChoiceComboBox::MinusPressedSignal     // private, signals                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 13. Jan 13:16:20 2008----------*/


/** +-=---------------------------------------------------------So 13. Jan 13:16:28 2008----------*
 * @method  CwmsObjectChoiceComboBox::DivisionPressedSignal  // private, signals                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 13. Jan 13:16:28 2008----------*/


/** +-=---------------------------------------------------------So 13. Jan 13:16:34 2008----------*
 * @method  CwmsObjectChoiceComboBox::MultiplyPressedSignal  // private, signals                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 13. Jan 13:16:34 2008----------*/

/** +-=---------------------------------------------------------So 8. Jan 22:14:37 2006-----------*
 * @method  CwmsObjectChoiceComboBox::ObjectSelectedSignal   // public, signals                   *
 * @return  void                                             //                                   *
 * @param   CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 8. Jan 22:14:37 2006-----------*/



/** +-=---------------------------------------------------------So 8. Jan 22:14:47 2006-----------*
 * @method  CwmsObjectChoiceComboBox::ObjectSelectedSignal   // public, signals                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------So 8. Jan 22:14:47 2006-----------*/

