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
#include "CdmValueListString.h"


/** +-=---------------------------------------------------------Mo 13. Aug 15:45:28 2007----------*
 * @method  CdmValueListString::CdmValueListString                     // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:28 2007----------*/
CdmValueListString::CdmValueListString(long p_lDatabaseId,
                             long p_lId,
                             QString p_qstrKeyname,
                             CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListString,p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 13. Aug 16:25:21 2007----------*
 * @method  CdmValueListString::CdmValueListString                     // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 16:25:21 2007----------*/
CdmValueListString::CdmValueListString(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 14:07:52 2012----------*
 * @method  CdmValueListString::CdmValueListString           // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 14:07:52 2012----------*/
CdmValueListString::CdmValueListString(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:45:32 2007----------*
 * @method  CdmValueListString::~CdmValueListString                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:32 2007----------*/
CdmValueListString::~CdmValueListString()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:42:27 2012-----------*
 * @method  CdmValueListString::Deploy                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:42:27 2012-----------*/
void CdmValueListString::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:46:18 2008----------*
 * @method  CdmValueListString::SetValue                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:46:18 2008----------*/
void CdmValueListString::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:52:42 2013----------*
 * @method  CdmValueListString::GetValue                     // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:52:42 2013----------*/
QString CdmValueListString::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Di 12. Feb 10:52:47 2013----------*
 * @method  CdmValueListString::Serialize                    // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:52:47 2013----------*/
void CdmValueListString::Serialize() const
{
   QDomDocument qddDocument(WMS_LIST);

   QLinkedList<QString>::const_iterator qvlIt = m_qvlStrings.begin();
   QLinkedList<QString>::const_iterator qvlItEnd = m_qvlStrings.end();

   QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
   qddDocument.appendChild(qdeElement);
   int iCounter = 1;

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
      qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
      qdeMapEntry.setAttribute(WMS_DATA, *qvlIt);
      qdeElement.appendChild(qdeMapEntry);
      ++iCounter;
   }


   m_qstrDocument = qddDocument.toString();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:33:58 2007----------*
 * @method  CdmValueListString::Deserialize                       // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: --------------------------------Mo 13. Aug 15:33:58 2007----------*/
void CdmValueListString::Deserialize()
{
    DeserializeXmlToStringList(m_qstrDocument, m_qvlStrings);
}

void CdmValueListString::DeserializeXmlToStringList(QString& p_qstrXml, QLinkedList<QString>& p_qllResultList)
{
    p_qllResultList.clear();
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
       p_qllResultList.append(qstrData);

       qdnNode = qdnNode.nextSibling();
    }
}

/** +-=---------------------------------------------------------Di 20. Nov 11:49:07 2012----------*
 * @method  CdmValueListString::AddValue                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 11:49:07 2012----------*/
void CdmValueListString::AddValue(QString p_qstrValue)
{

   if (!m_qvlStrings.contains(p_qstrValue))
   {
      m_qvlStrings.append(p_qstrValue);
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 11:49:14 2012----------*
 * @method  CdmValueListString::RemoveValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 11:49:14 2012----------*/
void CdmValueListString::RemoveValue(QString p_qstrValue)
{

   m_qvlStrings.removeOne(p_qstrValue);
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 10:30:17 2013----------*
 * @method  CdmValueListString::GetList                      // public, const, slots              *
 * @return  QLinkedList<QString>                             //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 10:30:17 2013----------*/
QLinkedList<QString> CdmValueListString::GetList() const
{
   return m_qvlStrings;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:49:27 2012----------*
 * @method  CdmValueListString::ClearList                    // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This method clears the list.                                                          *
 *----------------last changed: --------------------------------Di 20. Nov 11:49:27 2012----------*/
void CdmValueListString::ClearList()
{
   m_qvlStrings.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------So 6. Jun 11:43:23 2010-----------*
 * @method  CdmValueListString::SetList                      // public                            *
 * @return  void                                             //                                   *
 * @param   QLinkedList<QString> p_qllStrings                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 6. Jun 11:43:23 2010-----------*/
void CdmValueListString::SetList(QLinkedList<QString> p_qllStrings)
{
   m_qvlStrings = p_qllStrings;
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 10:30:43 2013----------*
 * @method  CdmValueListString::GetValueAsString             // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:30:43 2013----------*/
QString CdmValueListString::GetValueAsString() const
{
   QString qstrList;
   QLinkedList<QString>::const_iterator qvlIt = m_qvlStrings.begin();
   QLinkedList<QString>::const_iterator qvlItEnd = m_qvlStrings.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      qstrList += *qvlIt + "\n";
   }

   return qstrList;
}

QStringList CdmValueListString::GetStringList() const
{
    QStringList qstrlReturn;

    for (QString qstrValue : m_qvlStrings)
    {
        qstrlReturn.append(qstrValue);
    }

    return qstrlReturn;
}

int CdmValueListString::GetListSize() const
{
    return m_qvlStrings.count();
}

/** +-=---------------------------------------------------------So 10. Feb 10:30:55 2013----------*
 * @method  CdmValueListString::GetValueVariant              // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:30:55 2013----------*/
QVariant CdmValueListString::GetValueVariant() const
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

void CdmValueListString::SetValueVariant(QVariant& p_rVariant)
{
    QVariantList values = p_rVariant.toList();
    m_qvlStrings.clear();

    for(QVariant v: values)
    {
        QString iVal = v.toString();
        m_qvlStrings.append(iVal);
    }
}
