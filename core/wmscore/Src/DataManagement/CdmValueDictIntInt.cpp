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
#include "CdmValueDictIntInt.h"


/** +-=---------------------------------------------------------Sa 11. Aug 20:48:44 2007----------*
 * @method  CdmValueDictIntInt::CdmValueDictIntInt                     // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:48:44 2007----------*/
CdmValueDictIntInt::CdmValueDictIntInt(qint64 p_lDatabaseId,
                            qint64 p_lId,
                             QString p_qstrKeyname,
                             CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictIntInt, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Sa 11. Apr 09:48:28 2009----------*
 * @method  CdmValueDictIntInt::CdmValueDictIntInt           // public                            *
 * @return  void                                             //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: --------------------------------Sa 11. Apr 09:48:28 2009----------*/
CdmValueDictIntInt::CdmValueDictIntInt(EdmValueType p_eDmValue,
                                      qint64 p_lDatabaseId,
                                      qint64 p_lId,
                                       QString p_qstrKeyname,
                                       CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, p_eDmValue, p_pCdmObject)
{

}

/** +-=---------------------------------------------------------Mo 16. Apr 11:30:03 2012----------*
 * @method  CdmValueDictIntInt::CdmValueDictIntInt           // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:30:03 2012----------*/
CdmValueDictIntInt::CdmValueDictIntInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 11. Aug 20:48:54 2007----------*
 * @method  CdmValueDictIntInt::~CdmValueDictIntInt                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:48:54 2007----------*/
CdmValueDictIntInt::~CdmValueDictIntInt()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:33:54 2012-----------*
 * @method  CdmValueDictIntInt::Deploy                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:33:54 2012-----------*/
void CdmValueDictIntInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:31:09 2008----------*
 * @method  CdmValueDictIntInt::SetValue                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:31:09 2008----------*/
void CdmValueDictIntInt::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 28. Mai 14:52:36 2013----------*
 * @method  CdmValueDictIntInt::SetValue                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QMap<int, int> p_qmValue                         //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 28. Mai 14:52:36 2013----------*/
void CdmValueDictIntInt::SetValue(QMap<int, int> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:54:26 2013----------*
 * @method  CdmValueDictIntInt::GetValue                     // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:54:26 2013----------*/
QString CdmValueDictIntInt::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Di 12. Feb 10:54:34 2013----------*
 * @method  CdmValueDictIntInt::Serialize                    // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:54:34 2013----------*/
void CdmValueDictIntInt::Serialize() const
{
   QDomDocument qddDocument(WMS_MAP);

   QMap<int, int>::const_iterator qmIt = m_qmMap.begin();
   QMap<int, int>::const_iterator qmItEnd = m_qmMap.end();

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

/** +-=---------------------------------------------------------Sa 11. Aug 20:49:32 2007----------*
 * @method  CdmValueDictIntInt::Deserialize                       // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: Wolfgang Graßhof----------------Sa 11. Aug 20:49:32 2007----------*/
void CdmValueDictIntInt::Deserialize()
{
  DeserializeXmlToMap(m_qstrDocument, m_qmMap);
}

void CdmValueDictIntInt::DeserializeXmlToMap(QString& p_qstrXml, QMap<int,int>& p_qMao)
{
   p_qMao.clear();
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
         p_qMao[qstrKey.toInt()] = qstrData.toInt();
      }

      qdnNode = qdnNode.nextSibling();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:31:13 2012----------*
 * @method  CdmValueDictIntInt::SetValue                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @param   int p_iData                                      //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:31:13 2012----------*/
void CdmValueDictIntInt::SetValue(int p_iKey, int p_iData)
{
   if (!m_qmMap.contains(p_iKey) || m_qmMap[p_iKey] != p_iData)
   {
      m_qmMap[p_iKey] = p_iData;
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 09:31:23 2012----------*
 * @method  CdmValueDictIntInt::RemoveValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:31:23 2012----------*/
void CdmValueDictIntInt::RemoveValue(int p_iKey)
{

   m_qmMap.remove(p_iKey);
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:31:31 2012----------*
 * @method  CdmValueDictIntInt::ClearDict                    // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:31:31 2012----------*/
void CdmValueDictIntInt::ClearDict()
{

   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:00:30 2013----------*
 * @method  CdmValueDictIntInt::GetDict                      // public, const, slots              *
 * @return  QMap<int, int>                                   //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:00:30 2013----------*/
QMap<int, int> CdmValueDictIntInt::GetDict() const
{
   return m_qmMap;
}

/** +-=---------------------------------------------------------So 10. Feb 09:00:42 2013----------*
 * @method  CdmValueDictIntInt::GetValueAsString             // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:00:42 2013----------*/
QString CdmValueDictIntInt::GetValueAsString() const
{
   QString qstrList;

   QMap<int, int>::const_iterator qmIt = m_qmMap.begin();
   QMap<int, int>::const_iterator qmItEnd = m_qmMap.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qstrList += QString::number(qmIt.key()) + "|" + QString::number(qmIt.value()) + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:00:52 2013----------*
 * @method  CdmValueDictIntInt::GetValueVariant              // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:00:52 2013----------*/
QVariant CdmValueDictIntInt::GetValueVariant() const
{
   QVariantMap qvVariant;

   for (auto key : m_qmMap.keys())
   {
       qvVariant.insert(QString::number(key), m_qmMap[key]);
   }

   return qvVariant;
}

void CdmValueDictIntInt::SetValueVariant(QVariant& p_rVariant)
{
   QVariantMap values = p_rVariant.toMap();
   m_qmMap.clear();

   for(auto v: values.keys())
   {
       bool bSuccess = false;
       int iKey = v.toInt(&bSuccess);
       int iValue = values[v].toInt();

       if (bSuccess)
       {
           m_qmMap.insert(iKey, iValue);
       }
       else
       {
           ERR("Entry " + v + " is not a number");
       }
   }
}
