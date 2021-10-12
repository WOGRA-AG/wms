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
#include "CdmValueDictIntDouble.h"


/** +-=---------------------------------------------------------Sa 11. Aug 20:41:38 2007----------*
 * @method  CdmValueDictIntDouble::CdmValueDictIntDouble               // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:41:38 2007----------*/
CdmValueDictIntDouble::CdmValueDictIntDouble(qint64 p_lDatabaseId,
                                  qint64 p_lId,
                                   QString p_qstrKeyname,
                                   CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictIntDouble, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:25:37 2012----------*
 * @method  CdmValueDictIntDouble::CdmValueDictIntDouble     // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:25:37 2012----------*/
CdmValueDictIntDouble::CdmValueDictIntDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 11. Aug 20:02:52 2007----------*
 * @method  CdmValueDictIntDouble::~CdmValueDictIntDouble              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:02:52 2007----------*/
CdmValueDictIntDouble::~CdmValueDictIntDouble()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:33:17 2012-----------*
 * @method  CdmValueDictIntDouble::Deploy                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:33:17 2012-----------*/
void CdmValueDictIntDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:30:42 2008----------*
 * @method  CdmValueDictIntDouble::SetValue                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:30:42 2008----------*/
void CdmValueDictIntDouble::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 28. Mai 14:52:09 2013----------*
 * @method  CdmValueDictIntDouble::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QMap<int, double> p_qmValue                      //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 28. Mai 14:52:09 2013----------*/
void CdmValueDictIntDouble::SetValue(QMap<int, double> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}

/** +-=---------------------------------------------------------Sa 9. Feb 13:00:34 2013-----------*
 * @method  CdmValueDictIntDouble::GetValue                  // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Sa 9. Feb 13:00:34 2013-----------*/
QString CdmValueDictIntDouble::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Mo 11. Feb 10:06:02 2013----------*
 * @method  CdmValueDictIntDouble::Serialize                 // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Mo 11. Feb 10:06:02 2013----------*/
void CdmValueDictIntDouble::Serialize() const
{
   QDomDocument qddDocument(WMS_MAP);

   QMap<int, double>::const_iterator qmIt = m_qmMap.begin();
   QMap<int, double>::const_iterator qmItEnd = m_qmMap.end();

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

/** +-=---------------------------------------------------------Sa 11. Aug 20:03:09 2007----------*
 * @method  CdmValueDictIntDouble::Deserialize                    // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:03:09 2007----------*/
void CdmValueDictIntDouble::Deserialize()
{
    DeserializeXmlToMap(m_qstrDocument, m_qmMap);
}

void CdmValueDictIntDouble::DeserializeXmlToMap(QString& p_qstrXml, QMap<int,double>& p_qmMap)
{
   p_qmMap.clear();
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
      qstrKey = qdeElement.attribute(WMS_KEY);
      qstrData = qdeElement.attribute(WMS_DATA);

      if (qstrKey != "")
      {
         p_qmMap[qstrKey.toInt()] = qstrData.toDouble();
      }

      qdnNode = qdnNode.nextSibling();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:29:28 2012----------*
 * @method  CdmValueDictIntDouble::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @param   double p_dData                                   //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:29:28 2012----------*/
void CdmValueDictIntDouble::SetValue(int p_iKey, double p_dData)
{
   m_qmMap[p_iKey] = p_dData;
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:29:40 2012----------*
 * @method  CdmValueDictIntDouble::RemoveValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:29:40 2012----------*/
void CdmValueDictIntDouble::RemoveValue(int p_iKey)
{
   m_qmMap.remove(p_iKey);
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:29:51 2012----------*
 * @method  CdmValueDictIntDouble::ClearDict                 // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:29:51 2012----------*/
void CdmValueDictIntDouble::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------Sa 9. Feb 13:01:08 2013-----------*
 * @method  CdmValueDictIntDouble::GetDict                   // public, const, slots              *
 * @return  QMap<int, double>                                //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------Sa 9. Feb 13:01:08 2013-----------*/
QMap<int, double> CdmValueDictIntDouble::GetDict() const
{
   return m_qmMap;
}

/** +-=---------------------------------------------------------Sa 9. Feb 13:01:15 2013-----------*
 * @method  CdmValueDictIntDouble::GetValueAsString          // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 13:01:15 2013-----------*/
QString CdmValueDictIntDouble::GetValueAsString() const
{
   QString qstrList;

   QMap<int, double>::const_iterator qmIt = m_qmMap.begin();
   QMap<int, double>::const_iterator qmItEnd = m_qmMap.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qstrList += QString::number(qmIt.key()) + "|" + QString::number(qmIt.value()) + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------Sa 9. Feb 13:01:35 2013-----------*
 * @method  CdmValueDictIntDouble::GetValueVariant           // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 13:01:35 2013-----------*/
QVariant CdmValueDictIntDouble::GetValueVariant() const
{
    QVariantMap qvVariant;

    for (auto key : m_qmMap.keys())
    {
        qvVariant.insert(QString::number(key), m_qmMap[key]);
    }

    return qvVariant;
}

void CdmValueDictIntDouble::SetValueVariant(QVariant& p_rVariant)
{
    QVariantMap values = p_rVariant.toMap();
    m_qmMap.clear();

    for(auto v: values.keys())
    {
        bool bSuccess = false;
        int iKey = v.toInt(&bSuccess);
        double dValue = values[v].toDouble();

        if (bSuccess)
        {
            m_qmMap.insert(iKey, dValue);
        }
        else
        {
            ERR("Entry " + v + " is not a number");
        }
    }
}
