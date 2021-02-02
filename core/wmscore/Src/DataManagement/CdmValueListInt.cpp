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
#include <qdom.h>
#include <QLinkedList>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueListInt.h"


/** +-=---------------------------------------------------------Mo 13. Aug 15:45:14 2007----------*
 * @method  CdmValueListInt::CdmValueListInt                           // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the intlist.                                                       *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:14 2007----------*/
CdmValueListInt::CdmValueListInt(long p_lDatabaseId,
                       long p_lId,
                       QString p_qstrKeyname,
                       CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListInt, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 13. Aug 16:24:43 2007----------*
 * @method  CdmValueListInt::CdmValueListInt                           // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 16:24:43 2007----------*/
CdmValueListInt::CdmValueListInt(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 13:33:50 2012----------*
 * @method  CdmValueListInt::CdmValueListInt                 // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 13:33:50 2012----------*/
CdmValueListInt::CdmValueListInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:45:19 2007----------*
 * @method  CdmValueListInt::~CdmValueListInt                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:19 2007----------*/
CdmValueListInt::~CdmValueListInt()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:39:12 2012-----------*
 * @method  CdmValueListInt::Deploy                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:39:12 2012-----------*/
void CdmValueListInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:46:00 2008----------*
 * @method  CdmValueListInt::SetValue                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:46:00 2008----------*/
void CdmValueListInt::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:32:37 2007----------*
 * @method  CdmValueListInt::GetValue                             // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:32:37 2007----------*/
QString CdmValueListInt::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:32:42 2007----------*
 * @method  CdmValueListInt::Serialize                            // private                           *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 15:32:42 2007----------*/
void CdmValueListInt::Serialize() const
{
   QDomDocument qddDocument(WMS_LIST);

   QLinkedList<int>::const_iterator qvlIt = m_qvlInts.begin();
   QLinkedList<int>::const_iterator qvlItEnd = m_qvlInts.end();

   QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
   qddDocument.appendChild(qdeElement);
   int iCounter = 1;

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
      qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
      qdeMapEntry.setAttribute(WMS_DATA, QString::number(*qvlIt));
      qdeElement.appendChild(qdeMapEntry);
      ++iCounter;
   }


   m_qstrDocument = qddDocument.toString();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:32:46 2007----------*
 * @method  CdmValueListInt::Deserialize                          // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: --------------------------------Mo 13. Aug 15:32:46 2007----------*/
void CdmValueListInt::Deserialize()
{
   DeserializeXmlToIntList(m_qstrDocument, m_qvlInts);
}

void CdmValueListInt::DeserializeXmlToIntList(QString& p_qstrXml, QLinkedList<int>& p_qllList)
{
   p_qllList.clear();
   QDomDocument qddDocument;
   QString qstrKey;
   QString qstrData;
   qddDocument.setContent(p_qstrXml);
   QDomElement qdeElement = qddDocument.documentElement();
   QDomNode qdnNode = qdeElement.firstChild();

   while(!qdnNode.isNull())
   {
      qstrData = "";
      qstrKey = "";
      QDomElement qdeElement = qdnNode.toElement(); // try to convert the node to an element.
      qstrData = qdeElement.attribute(WMS_DATA);
      p_qllList.append(qstrData.toInt());

      qdnNode = qdnNode.nextSibling();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:49:34 2012----------*
 * @method  CdmValueListInt::AddValue                        // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:49:34 2012----------*/
void CdmValueListInt::AddValue(int p_iValue)
{
   if (!m_qvlInts.contains(p_iValue))
   {
      m_qvlInts.append(p_iValue);
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 09:49:44 2012----------*
 * @method  CdmValueListInt::RemoveValue                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:49:44 2012----------*/
void CdmValueListInt::RemoveValue(int p_iValue)
{
   m_qvlInts.removeOne(p_iValue);
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:13:35 2013----------*
 * @method  CdmValueListInt::GetList                         // public, const, slots              *
 * @return  QLinkedList<int>                                 //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:13:35 2013----------*/
QLinkedList<int> CdmValueListInt::GetList() const
{
   return m_qvlInts;
}

/** +-=---------------------------------------------------------Di 20. Nov 09:50:15 2012----------*
 * @method  CdmValueListInt::SetList                         // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QLinkedList<int> p_qllInts                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:50:15 2012----------*/
void CdmValueListInt::SetList(QLinkedList<int> p_qllInts)
{
   m_qvlInts = p_qllInts;
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:13:45 2013----------*
 * @method  CdmValueListInt::GetValueAsString                // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:13:45 2013----------*/
QString CdmValueListInt::GetValueAsString() const
{
   QString qstrList;

   QLinkedList<int>::const_iterator qvlIt = m_qvlInts.begin();
   QLinkedList<int>::const_iterator qvlItEnd = m_qvlInts.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      qstrList += QString::number(*qvlIt) + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:14:08 2013----------*
 * @method  CdmValueListInt::GetValueVariant                 // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:14:08 2013----------*/
QVariant CdmValueListInt::GetValueVariant() const
{
    QVariantList qvVariant;
    QString qstrValue = GetValueAsString();
    QStringList qList = qstrValue.split("\n", QString::SkipEmptyParts);

    for (int iPos = 0; iPos < qList.count(); ++iPos)
    {
        qvVariant.append(qList[iPos]);
    }
   return qvVariant;
}

void CdmValueListInt::SetValueVariant(QVariant& p_rVariant)
{
    QVariantList values = p_rVariant.toList();
    m_qvlInts.clear();

    for(QVariant v: values)
    {
        bool success;
        int iVal = v.toInt(&success);
        if(success)
        {
            m_qvlInts.append(iVal);
        }
    }
}
