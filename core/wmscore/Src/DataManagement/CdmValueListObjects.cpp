/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueListObjects.cpp
 ** Started Implementation: 2009/04/10
 ** Description:
 ** 
 ** implements the list of objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>


// Own Includes
#include "wmsdefines.h"
#include "CdmObject.h"
#include "CdmMember.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmLogging.h"
#include "CdmValueListObjects.h"




/** +-=---------------------------------------------------------Fr 10. Apr 19:54:08 2009----------*
 * @method  CdmValueListObjects::CdmValueListObjects         // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lDatabaseId                               // The Database Id                   *
 * @param   long p_lId                                       // The Value Id                      *
 * @param   QString p_qstrKeyname                            // the value keyname                 *
 * @param   CdmObject* p_pCdmObject                          // the parent object                 *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 10. Apr 19:54:08 2009----------*/
CdmValueListObjects::CdmValueListObjects(long p_lDatabaseId,
                                         long p_lId,
                                         QString p_qstrKeyname,
                                         CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListObjects, p_pCdmObject)
{
   // NOTHING TO DO
}

/** +-=---------------------------------------------------------Sa 11. Apr 20:21:10 2009----------*
 * @method  CdmValueListObjects::CdmValueListObjects         // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 11. Apr 20:21:10 2009----------*/
CdmValueListObjects::CdmValueListObjects(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
    : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
   // NOTHING TO DO
}

/** +-=---------------------------------------------------------Mo 16. Apr 14:12:17 2012----------*
 * @method  CdmValueListObjects::CdmValueListObjects         // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 14:12:17 2012----------*/
CdmValueListObjects::CdmValueListObjects(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
    : CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
    Deserialize();
}

/** +-=---------------------------------------------------------Fr 10. Apr 19:54:36 2009----------*
 * @method  CdmValueListObjects::~CdmValueListObjects        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueListObjects                                           *
 *----------------last changed: --------------------------------Fr 10. Apr 19:54:36 2009----------*/
CdmValueListObjects::~CdmValueListObjects()
{
}

void CdmValueListObjects::Deploy(QVariantMap& p_rqvHash)
{
    CdmValueCharacterDocument::Deploy(p_rqvHash);
    Deserialize();
}

void CdmValueListObjects::SetValue(QString p_qstrValue)
{
    CdmValueCharacterDocument::SetValue(p_qstrValue);
    Deserialize();
}

QString CdmValueListObjects::GetValue() const
{
    Serialize();
    return m_qstrDocument;
}

/** +-=---------------------------------------------------------Mi 9. Jan 15:06:09 2013-----------*
 * @method  CdmValueListObjects::SetList                     // public                            *
 * @return  void                                             //                                   *
 * @param   QLinkedList<CdmObject*>& p_rqvlObjects           //                                   *
 * @comment fills the list of objects                                                             *
 *----------------last changed: --------------------------------Mi 9. Jan 15:06:09 2013-----------*/
void CdmValueListObjects::SetList(QLinkedList<CdmObject*>& p_rqvlObjects)
{
    ClearList();

   QLinkedList<CdmObject*>::iterator qllIt = p_rqvlObjects.begin();
   QLinkedList<CdmObject*>::iterator qllItEnd = p_rqvlObjects.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      AddValue(*qllIt);
   }
}

/** +-=---------------------------------------------------------So 10. Feb 11:40:24 2013----------*
 * @method  CdmValueListObjects::GetList                     // public, const                     *
 * @return  void                                             //                                   *
 * @param   QLinkedList<CdmObject*>& p_rqvlObjects           //                                   *
 * @comment fills the list of objects                                                             *
 *----------------last changed: --------------------------------So 10. Feb 11:40:24 2013----------*/
void CdmValueListObjects::GetList(QLinkedList<CdmObject*>& p_rqvlObjects) const
{
   const CdmObject* pCdmObject = GetObject();
  
   if (CHKPTR(pCdmObject))
   {
      CdmContainerManager* pCdmOLManager = pCdmObject->GetContainerManager();

      if (CHKPTR(pCdmOLManager))
      {
            QLinkedList<QPair<long, long> >::const_iterator qllIt = m_qllObjects.begin();
            QLinkedList<QPair<long, long> >::const_iterator qllItEnd = m_qllObjects.end();

            for (; qllIt != qllItEnd; ++qllIt)
         {
                QPair<long,long> qPair = *qllIt;
                long lObjectId = qPair.first;
                long lContainerId = qPair.second;
                CdmObjectContainer* pContainer = pCdmOLManager->FindContainerById(lContainerId);

            if (CHKPTR(pContainer))
            {
                    CdmObject* pCdmObjectTemp = pContainer->FindObjectById(lObjectId);

               if (CHKPTR(pCdmObjectTemp))
               {
                  p_rqvlObjects.append(pCdmObjectTemp);
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 9. Jan 15:09:20 2013-----------*
 * @method  CdmValueListObjects::AddValue                    // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCmObject                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Jan 15:09:20 2013-----------*/
void CdmValueListObjects::AddValue(CdmObject* p_pCmObject)
{
   if (CHKPTR(p_pCmObject))
   {
      const CdmMember* pMember = GetMember();

      if (CHKPTR(pMember))
      {
         int iClassRefId = pMember->GetClassReference();

         CdmClass* pClass = GetClassManager()->FindClassById(iClassRefId);

         if (p_pCmObject->IsTypeOf(pClass))
         {
            SetValue(p_pCmObject->GetId(), p_pCmObject->GetObjectContainerId());
         }
         else
         {
            ERR("Wrong Type to add to list");
         }
      }
   }
}

void CdmValueListObjects::AddEventValue(CdmObject *pCdmObject, CdmClass *pObjectClass)
{
    if(CHKPTR(pCdmObject) && CHKPTR(pObjectClass))
    {
        if(pCdmObject->IsTypeOf(pObjectClass))
        {
            SetValue(pCdmObject->GetId(), pCdmObject->GetObjectContainerId());
        }
        else
        {
            ERR("Wrong Type to add to List.");
        }
    }
}

/** +-=---------------------------------------------------------Mi 9. Jan 15:09:31 2013-----------*
 * @method  CdmValueListObjects::RemoveValue                 // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Jan 15:09:31 2013-----------*/
void CdmValueListObjects::RemoveValue(CdmObject* p_pCdmObject)
{
   if (CHKPTR(p_pCdmObject))
   {
        RemoveValue(p_pCdmObject->GetId());
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 12:01:17 2012----------*
 * @method  CdmValueListObjects::FindObjectById              // public, slots                     *
 * @return  CdmObject*                                       //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment finds the object in the list. if it is not in the list nullptr will returned.            *
 *----------------last changed: --------------------------------Di 20. Nov 12:01:17 2012----------*/
CdmObject* CdmValueListObjects::FindObjectById(int p_iId)
{
    CdmObject* pResult = nullptr;
   const CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      CdmContainerManager* pCdmOLManager = pCdmObject->GetContainerManager();
      pCdmObject = nullptr;

      if (CHKPTR(pCdmOLManager))
      {
            QLinkedList<QPair<long, long> >::const_iterator qllIt = m_qllObjects.begin();
            QLinkedList<QPair<long, long> >::const_iterator qllItEnd = m_qllObjects.end();

            for (; qllIt != qllItEnd; ++qllIt)
         {
                QPair<long,long> qPair = *qllIt;

                if (qPair.first == p_iId)
                {
                    long lContainerId = qPair.second;
                    CdmObjectContainer* pContainer = pCdmOLManager->FindContainerById(lContainerId);

            if (CHKPTR(pContainer))
            {
                        pResult = pContainer->FindObjectById(p_iId);
                    }

                    break;
                }
            }
        }
    }

    return pResult;
}

void CdmValueListObjects::Serialize() const
{
    QDomDocument qddDocument(WMS_MAP);
    QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
    qddDocument.appendChild(qdeElement);
    int iCounter = 1;

    QLinkedList<QPair<long, long> >::const_iterator qllIt = m_qllObjects.begin();
    QLinkedList<QPair<long, long> >::const_iterator qllItEnd = m_qllObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        QPair<long,long> qPair = *qllIt;
        QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
        qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
        qdeMapEntry.setAttribute(WMS_KEY, QString::number(qPair.first));
        qdeMapEntry.setAttribute(WMS_DATA, QString::number(qPair.second));
        qdeElement.appendChild(qdeMapEntry);
        ++iCounter;
    }

    m_qstrDocument = qddDocument.toString();
}

void CdmValueListObjects::Deserialize()
{
    m_qllObjects.clear();
    QDomDocument qddDocument;
    QString qstrKey;
    QString qstrData;
    qddDocument.setContent(m_qstrDocument);
    QDomElement qdeElement = qddDocument.documentElement();
    QDomNode qdnNode = qdeElement.firstChild();

    while(!qdnNode.isNull())
    {
        qstrData = "";
        qstrKey = "";
        QDomElement qdeElement = qdnNode.toElement(); // try to convert the node to an element.
        qstrKey = qdeElement.attribute(WMS_KEY);
        qstrData = qdeElement.attribute(WMS_DATA);

        if (qstrKey != "")
        {
            SetValue(qstrKey.toInt(), qstrData.toInt());
        }

        qdnNode = qdnNode.nextSibling();
    }
}

void CdmValueListObjects::RemoveValue(long p_iObjectId)
{
    QLinkedList<QPair<long, long> >::iterator qllIt = m_qllObjects.begin();
    QLinkedList<QPair<long, long> >::iterator qllItEnd = m_qllObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        QPair<long,long> qPair = *qllIt;

        if (qPair.first == p_iObjectId)
        {
            m_qllObjects.erase(qllIt);
            break;
        }
    }

    ValueChanged();
}

void CdmValueListObjects::SetValue(int p_iObjectId, int p_iContainerId)
{
    QPair<long, long> qPair;
    qPair.first = p_iObjectId;
    qPair.second = p_iContainerId;
    m_qllObjects.append(qPair);
    ValueChanged();
}

void CdmValueListObjects::ClearList()
{
    CdmValueCharacterDocument::SetValue("");
    m_qllObjects.clear();
    ValueChanged();
}

QString CdmValueListObjects::GetValueAsString() const
{
    QString qstrList;

    QLinkedList<QPair<long, long> >::const_iterator qllIt = m_qllObjects.begin();
    QLinkedList<QPair<long, long> >::const_iterator qllItEnd = m_qllObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        QPair<long,long> qPair = *qllIt;
        qstrList += QString::number(qPair.first) + "|" + QString::number(qPair.second) + "\n";
         }

    return qstrList;
      }

QVariant CdmValueListObjects::GetValueVariant() const
{
    QVariantList qvVariant;

    QLinkedList<QPair<long, long> >::const_iterator qllIt = m_qllObjects.begin();
    QLinkedList<QPair<long, long> >::const_iterator qllItEnd = m_qllObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        QPair<long,long> qPair = *qllIt;
        QVariantMap qvmEntry;
        qvmEntry.insert(WMS_URI, CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), QString::number(qPair.second), QString::number(qPair.first)));
        qvVariant.append(qvmEntry);
    }

    return qvVariant;
}


void CdmValueListObjects::SetValueVariant(QVariant& p_rVariant)
{
    QString qstrVariant = p_rVariant.toString();
    QStringList qstrlVariant = qstrVariant.split("\n");
    m_qllObjects.clear();

    for (int iCounter = 0; iCounter < qstrlVariant.count(); ++iCounter)
    {
        QString qstrLine = qstrlVariant[iCounter];

        if (!qstrLine.isEmpty())
        {
            QString qstrLine = qstrlVariant[iCounter];

            if (!qstrLine.isEmpty())
            {
                QStringList qstrlDictEntry = qstrlVariant[iCounter].split("|");
                if (qstrlDictEntry.count() == 2)

                {
                    int iKey = qstrlDictEntry[0].toInt();
                    int iValue = qstrlDictEntry[1].toInt();
                    m_qllObjects.append(QPair<long,long>(iKey,iValue));
                }
            }
        }
    }
}
