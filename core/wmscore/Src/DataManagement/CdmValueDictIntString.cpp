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


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueDictIntString.h"


/** +-=---------------------------------------------------------Sa 11. Aug 20:51:34 2007----------*
 * @method  CdmValueDictIntString::CdmValueDictIntString               // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:51:34 2007----------*/
CdmValueDictIntString::CdmValueDictIntString(long p_lDatabaseId,
                                   long p_lId,
                                   QString p_qstrKeyname,
                                   CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictIntString, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:31:25 2012----------*
 * @method  CdmValueDictIntString::CdmValueDictIntString     // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:31:25 2012----------*/
CdmValueDictIntString::CdmValueDictIntString(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 11. Aug 20:51:51 2007----------*
 * @method  CdmValueDictIntString::~CdmValueDictIntString              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:51:51 2007----------*/
CdmValueDictIntString::~CdmValueDictIntString()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:34:25 2012-----------*
 * @method  CdmValueDictIntString::Deploy                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:34:25 2012-----------*/
void CdmValueDictIntString::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:31:44 2008----------*
 * @method  CdmValueDictIntString::SetValue                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:31:44 2008----------*/
void CdmValueDictIntString::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 28. Mai 14:53:04 2013----------*
 * @method  CdmValueDictIntString::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QMap<int, QString> p_qmValue                     //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 28. Mai 14:53:04 2013----------*/
void CdmValueDictIntString::SetValue(QMap<int, QString> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:54:55 2013----------*
 * @method  CdmValueDictIntString::GetValue                  // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:54:55 2013----------*/
QString CdmValueDictIntString::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Di 12. Feb 10:55:05 2013----------*
 * @method  CdmValueDictIntString::Serialize                 // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:55:05 2013----------*/
void CdmValueDictIntString::Serialize() const
{
   QDomDocument qddDocument(WMS_MAP);

   QMap<int, QString>::const_iterator qmIt = m_qmMap.begin();
   QMap<int, QString>::const_iterator qmItEnd = m_qmMap.end();

   QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
   qddDocument.appendChild(qdeElement);
   int iCounter = 1;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
      qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
      qdeMapEntry.setAttribute(WMS_KEY, qmIt.key());
      qdeMapEntry.setAttribute(WMS_DATA, qmIt.value());
      qdeElement.appendChild(qdeMapEntry);
      ++iCounter;
   }


   m_qstrDocument = qddDocument.toString();
}

/** +-=---------------------------------------------------------Sa 11. Aug 20:52:09 2007----------*
 * @method  CdmValueDictIntString::Deserialize                    // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:52:09 2007----------*/
void CdmValueDictIntString::Deserialize()
{
   DeserializeXmlToMap(m_qstrDocument, m_qmMap);
}

void CdmValueDictIntString::DeserializeXmlToMap(QString& p_qstrDocument, QMap<int,QString>& p_qmMap)
{
   p_qmMap.clear();
   QDomDocument qddDocument;
   QString qstrKey;
   QString qstrData;
   qddDocument.setContent(p_qstrDocument);
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
         p_qmMap[qstrKey.toInt()] = qstrData;
      }

      qdnNode = qdnNode.nextSibling();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:32:13 2012----------*
 * @method  CdmValueDictIntString::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @param   QString p_qstrData                               //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:32:13 2012----------*/
void CdmValueDictIntString::SetValue(int p_iKey, QString p_qstrData)
{
   m_qmMap[p_iKey] = p_qstrData;
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:32:19 2012----------*
 * @method  CdmValueDictIntString::RemoveValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:32:19 2012----------*/
void CdmValueDictIntString::RemoveValue(int p_iKey)
{
   m_qmMap.remove(p_iKey);
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 20. Nov 09:32:27 2012----------*
 * @method  CdmValueDictIntString::ClearDict                 // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:32:27 2012----------*/
void CdmValueDictIntString::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:01:29 2013----------*
 * @method  CdmValueDictIntString::GetDict                   // public, const, slots              *
 * @return  QMap<int, QString>                               //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:01:29 2013----------*/
QMap<int, QString> CdmValueDictIntString::GetDict() const
{

   return m_qmMap;
}

/** +-=---------------------------------------------------------So 10. Feb 09:01:36 2013----------*
 * @method  CdmValueDictIntString::GetValueAsString          // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:01:36 2013----------*/
QString CdmValueDictIntString::GetValueAsString() const
{

   QString qstrList;

   QMap<int, QString>::const_iterator qmIt = m_qmMap.begin();
   QMap<int, QString>::const_iterator qmItEnd = m_qmMap.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qstrList += QString::number(qmIt.key()) + "|" + qmIt.value() + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:01:42 2013----------*
 * @method  CdmValueDictIntString::GetValueVariant           // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:01:42 2013----------*/
QVariant CdmValueDictIntString::GetValueVariant() const
{
    QVariantMap qvVariant;

    for (auto key : m_qmMap.keys())
    {
        qvVariant.insert(QString::number(key), m_qmMap[key]);
    }

    return qvVariant;
}


void CdmValueDictIntString::SetValueVariant(QVariant& p_rVariant)
{
    QVariantMap values = p_rVariant.toMap();
    m_qmMap.clear();

    for(auto v: values.keys())
    {
        bool bSuccess = false;
        int iKey = v.toInt(&bSuccess);
        QString qstrValue = values[v].toString();

        if (bSuccess)
        {
            m_qmMap.insert(iKey, qstrValue);
        }
        else
        {
            ERR("Entry " + v + " is not a number");
        }
    }
}
