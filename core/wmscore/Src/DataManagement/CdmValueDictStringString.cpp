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
#include "CdmValueDictStringString.h"


/** +-=---------------------------------------------------------Mo 13. Aug 15:44:57 2007----------*
 * @method  CdmValueDictStringString::CdmValueDictStringString         // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:44:57 2007----------*/
CdmValueDictStringString::CdmValueDictStringString(long p_lDatabaseId,
                                         long p_lId,
                                         QString p_qstrKeyname,
                                         CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictStringString, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 13. Aug 16:24:15 2007----------*
 * @method  CdmValueDictStringString::CdmValueDictStringString         // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 16:24:15 2007----------*/
CdmValueDictStringString::CdmValueDictStringString(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:40:43 2012----------*
 * @method  CdmValueDictStringString::CdmValueDictStringString // public                          *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:40:43 2012----------*/
CdmValueDictStringString::CdmValueDictStringString(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:45:02 2007----------*
 * @method  CdmValueDictStringString::~CdmValueDictStringString        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:02 2007----------*/
CdmValueDictStringString::~CdmValueDictStringString()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:35:39 2012-----------*
 * @method  CdmValueDictStringString::Deploy                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:35:39 2012-----------*/
void CdmValueDictStringString::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:45:16 2008----------*
 * @method  CdmValueDictStringString::SetValue               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:45:16 2008----------*/
void CdmValueDictStringString::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:56:19 2013----------*
 * @method  CdmValueDictStringString::GetValue               // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:56:19 2013----------*/
QString CdmValueDictStringString::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Di 20. Nov 09:36:48 2012----------*
 * @method  CdmValueDictStringString::GetValue               // public, slots                     *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment returns the value to the given key.                                                   *
 *----------------last changed: --------------------------------Di 20. Nov 09:36:48 2012----------*/
QString CdmValueDictStringString::GetValue(QString p_qstrKey)
{
   QString qstrRet = "";

   if (m_qmMap.contains(p_qstrKey))
   {
      qstrRet = m_qmMap[p_qstrKey];
   }

   return qstrRet;
}


/** +-=---------------------------------------------------------Di 20. Nov 09:36:56 2012----------*
 * @method  CdmValueDictStringString::ExistValue             // public, slots                     *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment returns if a value exists.                                                            *
 *----------------last changed: --------------------------------Di 20. Nov 09:36:56 2012----------*/
bool CdmValueDictStringString::ExistValue(QString p_qstrKey)
{
   bool bRet = false;

   if (m_qmMap.contains(p_qstrKey))
   {
      bRet = true;
   }

   return bRet;
}


/** +-=---------------------------------------------------------Di 12. Feb 10:56:32 2013----------*
 * @method  CdmValueDictStringString::Serialize              // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:56:32 2013----------*/
void CdmValueDictStringString::Serialize() const
{
   QDomDocument qddDocument(WMS_MAP);

   QMap<QString, QString>::const_iterator qmIt = m_qmMap.begin();
   QMap<QString, QString>::const_iterator qmItEnd = m_qmMap.end();

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

/** +-=---------------------------------------------------------Mo 13. Aug 15:11:20 2007----------*
 * @method  CdmValueDictStringString::Deserialize                 // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: --------------------------------Mo 13. Aug 15:11:20 2007----------*/
void CdmValueDictStringString::Deserialize()
{
   DeserializeXmlToMap(m_qstrDocument, m_qmMap);
}

void CdmValueDictStringString::DeserializeXmlToMap(QString& p_qstrXml, QMap<QString,QString>& p_qmMap)
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
         p_qmMap[qstrKey] = qstrData;
      }

      qdnNode = qdnNode.nextSibling();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:37:21 2012----------*
 * @method  CdmValueDictStringString::SetValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   QString p_qstrData                               //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:37:21 2012----------*/
void CdmValueDictStringString::SetValue(QString p_qstrKey, QString p_qstrData)
{
   m_qmMap[p_qstrKey] = p_qstrData;
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 20. Nov 09:37:43 2012----------*
 * @method  CdmValueDictStringString::SetValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QMap<QString, QString> p_qmValue                 //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:37:43 2012----------*/
void CdmValueDictStringString::SetValue(QMap<QString, QString> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:38:51 2012----------*
 * @method  CdmValueDictStringString::RemoveValue            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:38:51 2012----------*/
void CdmValueDictStringString::RemoveValue(QString p_qstrKey)
{
   m_qmMap.remove(p_qstrKey);
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 20. Nov 09:39:00 2012----------*
 * @method  CdmValueDictStringString::ClearDict              // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:39:00 2012----------*/
void CdmValueDictStringString::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:04:28 2013----------*
 * @method  CdmValueDictStringString::GetDict                // public, const, slots              *
 * @return  QMap<QString, QString>                           //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:04:28 2013----------*/
QMap<QString, QString> CdmValueDictStringString::GetDict() const
{
   return m_qmMap;
}

/** +-=---------------------------------------------------------So 10. Feb 09:04:34 2013----------*
 * @method  CdmValueDictStringString::GetValueAsString       // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:04:34 2013----------*/
QString CdmValueDictStringString::GetValueAsString() const
{
   QString qstrList;

   QMap<QString, QString>::const_iterator qmIt = m_qmMap.begin();
   QMap<QString, QString>::const_iterator qmItEnd = m_qmMap.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qstrList += qmIt.key() + "|" + qmIt.value() + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:04:39 2013----------*
 * @method  CdmValueDictStringString::GetValueVariant        // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:04:39 2013----------*/
QVariant CdmValueDictStringString::GetValueVariant() const
{
    QVariantMap qvVariant;

    for (auto key : m_qmMap.keys())
    {
        qvVariant.insert(key, m_qmMap[key]);
    }

    return qvVariant;
}

void CdmValueDictStringString::SetValueVariant(QVariant& p_rVariant)
{
    QVariantMap values = p_rVariant.toMap();
    m_qmMap.clear();

    for(auto v: values.keys())
    {
        QString qstrValue = values[v].toString();
        m_qmMap.insert(v, qstrValue);
    }
}
