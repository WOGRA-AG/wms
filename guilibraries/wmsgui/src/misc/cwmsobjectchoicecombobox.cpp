// System and Qt Includes
#include <QList>
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
#include "CdmQueryModel.h"
#include "cwmsobjectchoicecombobox.h"


CwmsObjectChoiceComboBox::CwmsObjectChoiceComboBox(QWidget* parent)
: QComboBox(parent),
  m_rpCdmProxy(nullptr)
{
   connect(this, SIGNAL(activated(int)), this, SLOT(ComboBoxActivatedSlot()));
}

CwmsObjectChoiceComboBox::~CwmsObjectChoiceComboBox()
{
   // nothing to do because the map contains only references
}

void CwmsObjectChoiceComboBox::SetProxy(CdmQueryModel* p_pCdmProxy)
{
   m_rpCdmProxy = p_pCdmProxy;
   
   if (m_rpCdmProxy)
   {
      connect(m_rpCdmProxy, SIGNAL(UpdateSignal()), this, SLOT(Refresh()));
   }
}

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
        m_rpCdmProxy->Execute();
        CdmQuery* pCdmQuery = m_rpCdmProxy->GetQuery();
        FillWidget(*pCdmQuery);
    }
}

void CwmsObjectChoiceComboBox::SetContainerAndDisplayValue(CdmObjectContainer* p_pContainer,
                                                           QString p_qstrValueKeyname)
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
         disconnect(m_rpCdmProxy, SIGNAL(UpdateSignal()), this, SLOT(Refresh()));
         QList<qint64> qvlResults;
         m_rpCdmProxy->CreateQuery(p_pContainer);
         m_rpCdmProxy->Execute();
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

         connect(m_rpCdmProxy, SIGNAL(UpdateSignal()), this, SLOT(Refresh()));
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

      QString qstrWql = QString("select from %1 where Name = \"%2\"").arg(p_pContainer->GetKeyname(),qstrFilter);
      CdmQuery *pQuery = nullptr;
      pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

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

       QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));

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

void CwmsObjectChoiceComboBox::FillWidget(CdmQuery& p_rcCdmQuery)
{
    SetContainer(p_rcCdmQuery.GetContainer());
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

         QString qstrValue = p_rcCdmQuery.GetResultAsDisplayStringAt(iColPos, iRowPos);

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
      
     qint64 lObjectId = p_rcCdmQuery.GetObjectIdAt(iRowPos);

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

void CwmsObjectChoiceComboBox::FillDialog(CdmObjectContainer* p_pContainer,
                                          QString p_qstrValueKeyname,
                                          QList<qint64>& p_rqvlObjects)
{
    ClearEntries();
   QString qstrValueKeyname = p_qstrValueKeyname;

   if (p_pContainer)
   {
      int iIndex = 0;

      m_qmEntries.insert("-", 0);

      if (p_rqvlObjects.count() > 0)
      {
         QList<qint64>::iterator qvlIt = p_rqvlObjects.begin();
         QList<qint64>::iterator qvlItEnd = p_rqvlObjects.end();

         for(; qvlIt != qvlItEnd; ++qvlIt, ++iIndex)
         {
           qint64 lObjectId = (*qvlIt);
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

void CwmsObjectChoiceComboBox::FillDialog(CdmObjectContainer* p_pContainer,
                                          QString p_qstrValueKeyname)
{
	ClearEntries();

   if(CHKPTR(p_pContainer))
   {
      QList<CdmObject*> qvlObjects;
      p_pContainer->GetObjectList(qvlObjects);
      int iIndex = 0;

      m_qmEntries.insert("-", 0);
      //insertItem("-");
      ++iIndex;

      QList<CdmObject*>::iterator qvlIt = qvlObjects.begin();
      QList<CdmObject*>::iterator qvlItEnd = qvlObjects.end();

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

void CwmsObjectChoiceComboBox::AddEntry(CdmObject* p_pCdmObject, QString p_qstrValue)
{
   if(CHKPTR(p_pCdmObject))
   {
      AddEntry(p_pCdmObject->GetId(), p_qstrValue);
   }
}

void CwmsObjectChoiceComboBox::AddEntry(qint64 p_lObjectId, QString p_qstrValue)
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

void CwmsObjectChoiceComboBox::FillEntries()
{
   if (!m_qmEntries.contains("-"))
   {
      m_qmEntries.insert("-", 0);
   }

   QMap<QString,qint64>::iterator qmIt = m_qmEntries.begin();
   QMap<QString,qint64>::iterator qmItEnd = m_qmEntries.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrKey = qmIt.key();
      addItem(qstrKey);
   }
}

void CwmsObjectChoiceComboBox::Refresh()
{
   // storing the old value
 qint64 lObjectId = GetSelectedObjectId();

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

void CwmsObjectChoiceComboBox::SetCurrentObjectId(qint64 p_lId)
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

int CwmsObjectChoiceComboBox::FindIndexById(qint64 p_lObjectId)
{
   int iRet = -1;

   if(p_lObjectId > 0)
   {
      QMap<QString,qint64>::iterator qmIt = m_qmEntries.begin();
      QMap<QString,qint64>::iterator qmItEnd = m_qmEntries.end();

      for(; qmIt != qmItEnd; ++qmIt)
      {
        qint64 lObjectTemp = qmIt.value();

         if(lObjectTemp == p_lObjectId)
         {
            iRet = findText(qmIt.key());
            break;
         }
      }
   }

   return iRet;
}

qint64 CwmsObjectChoiceComboBox::GetSelectedObjectId()
{
   QString qstrCurrent = currentText();
   return m_qmEntries[qstrCurrent];
}

CdmObject* CwmsObjectChoiceComboBox::GetSelectedObject()
{
   CdmObject* pCdmObject = nullptr;
  qint64 lObjectId = GetSelectedObjectId();

   CdmObjectContainer* pContainer = CdmContainerAdaptor::GetContainer();

   if (pContainer)
   {
      pCdmObject = pContainer->FindObjectById(lObjectId);
   }
   
   return pCdmObject;
}

CdmObject *CwmsObjectChoiceComboBox::GetSelectedObjectByIndex(int iIndex)
{
    CdmObject *pCurrentObject = nullptr;
    QList<qint64> qlValues = m_qmEntries.values();
    if(iIndex >= 0)
    {
       qint64 lObjectIdByIndex = qlValues.at(iIndex);
        pCurrentObject = FindObject(lObjectIdByIndex);
    }
    return pCurrentObject;
}

void CwmsObjectChoiceComboBox::ComboBoxActivatedSlot()
{
   CdmObject* pCdmObject = GetSelectedObject();

   emit ObjectSelectedSignal();
   emit ObjectSelectedSignal(pCdmObject);
}

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

void CwmsObjectChoiceComboBox::ObjectCreatedEvent(qint64)
{
   Refresh();
}

void CwmsObjectChoiceComboBox::ObjectModifiedEvent(qint64)
{
}

void CwmsObjectChoiceComboBox::ObjectRefModifiedEvent(qint64)
{
}

void CwmsObjectChoiceComboBox::ObjectDeletedEvent(qint64)
{
   Refresh();
}

void CwmsObjectChoiceComboBox::ObjectCommitedEvent(qint64)
{
   //Refresh();
}
