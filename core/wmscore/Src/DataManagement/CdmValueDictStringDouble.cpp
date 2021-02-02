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
#include "CdmValueDictStringDouble.h"


/** +-=---------------------------------------------------------Mo 13. Aug 15:44:30 2007----------*
 * @method  CdmValueDictStringDouble::CdmValueDictStringDouble         // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:44:30 2007----------*/
CdmValueDictStringDouble::CdmValueDictStringDouble(long p_lDatabaseId,
                                         long p_lId,
                                         QString p_qstrKeyname,
                                         CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictStringDouble, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 13. Aug 16:21:19 2007----------*
 * @method  CdmValueDictStringDouble::CdmValueDictStringDouble         // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 16:21:19 2007----------*/
CdmValueDictStringDouble::CdmValueDictStringDouble(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:33:22 2012----------*
 * @method  CdmValueDictStringDouble::CdmValueDictStringDouble // public                          *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:33:22 2012----------*/
CdmValueDictStringDouble::CdmValueDictStringDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:44:34 2007----------*
 * @method  CdmValueDictStringDouble::~CdmValueDictStringDouble        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:44:34 2007----------*/
CdmValueDictStringDouble::~CdmValueDictStringDouble()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:34:46 2012-----------*
 * @method  CdmValueDictStringDouble::Deploy                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:34:46 2012-----------*/
void CdmValueDictStringDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:32:04 2008----------*
 * @method  CdmValueDictStringDouble::SetValue               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:32:04 2008----------*/ 
void CdmValueDictStringDouble::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:55:27 2013----------*
 * @method  CdmValueDictStringDouble::GetValue               // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:55:27 2013----------*/
QString CdmValueDictStringDouble::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Di 12. Feb 10:55:35 2013----------*
 * @method  CdmValueDictStringDouble::Serialize              // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:55:35 2013----------*/
void CdmValueDictStringDouble::Serialize() const
{
   QDomDocument qddDocument(WMS_MAP);

   QMap<QString, double>::const_iterator qmIt = m_qmMap.begin();
   QMap<QString, double>::const_iterator qmItEnd = m_qmMap.end();

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

/** +-=---------------------------------------------------------Mo 13. Aug 15:22:11 2007----------*
 * @method  CdmValueDictStringDouble::Deserialize                 // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: --------------------------------Mo 13. Aug 15:22:11 2007----------*/
void CdmValueDictStringDouble::Deserialize()
{
    DeserializeXmlToMap(m_qstrDocument, m_qmMap);
}

void CdmValueDictStringDouble::DeserializeXmlToMap(QString& p_qstrDocument, QMap<QString, double>& p_qmMap)
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
         p_qmMap[qstrKey] = qstrData.toDouble();
      }

      qdnNode = qdnNode.nextSibling();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:33:34 2012----------*
 * @method  CdmValueDictStringDouble::SetValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   double p_dData                                   //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:33:34 2012----------*/
void CdmValueDictStringDouble::SetValue(QString p_qstrKey, double p_dData)
{
   m_qmMap[p_qstrKey] = p_dData;
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 28. Mai 14:51:43 2013----------*
 * @method  CdmValueDictStringDouble::SetValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QMap<QString, double> p_qmValue                  //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 28. Mai 14:51:43 2013----------*/
void CdmValueDictStringDouble::SetValue(QMap<QString, double> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 20. Nov 09:33:44 2012----------*
 * @method  CdmValueDictStringDouble::RemoveValue            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:33:44 2012----------*/
void CdmValueDictStringDouble::RemoveValue(QString p_qstrKey)
{
   m_qmMap.remove(p_qstrKey);
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:33:51 2012----------*
 * @method  CdmValueDictStringDouble::ClearDict              // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:33:51 2012----------*/
void CdmValueDictStringDouble::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:02:14 2013----------*
 * @method  CdmValueDictStringDouble::GetDict                // public, const, slots              *
 * @return  QMap<QString, double>                            //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:02:14 2013----------*/
QMap<QString, double> CdmValueDictStringDouble::GetDict() const
{
   return m_qmMap;
}

/** +-=---------------------------------------------------------So 10. Feb 09:02:32 2013----------*
 * @method  CdmValueDictStringDouble::GetValueAsString       // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:02:32 2013----------*/
QString CdmValueDictStringDouble::GetValueAsString() const
{
   QString qstrList;

   QMap<QString, double>::const_iterator qmIt = m_qmMap.begin();
   QMap<QString, double>::const_iterator qmItEnd = m_qmMap.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qstrList += qmIt.key() + "|" + QString::number(qmIt.value()) + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:02:42 2013----------*
 * @method  CdmValueDictStringDouble::GetValueVariant        // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:02:42 2013----------*/
QVariant CdmValueDictStringDouble::GetValueVariant() const
{
    QVariantMap qvVariant;

    for (auto key : m_qmMap.keys())
    {
        qvVariant.insert(key, m_qmMap[key]);
    }

    return qvVariant;
}

void CdmValueDictStringDouble::SetValueVariant(QVariant& p_rVariant)
{
    QVariantMap values = p_rVariant.toMap();
    m_qmMap.clear();

    for(auto v: values.keys())
    {
        double dValue = values[v].toDouble();
        m_qmMap.insert(v, dValue);
    }
}
