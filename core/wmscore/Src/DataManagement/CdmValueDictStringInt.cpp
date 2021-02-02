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
#include "CdmValueDictStringInt.h"


/** +-=---------------------------------------------------------Mo 13. Aug 15:44:43 2007----------*
 * @method  CdmValueDictStringInt::CdmValueDictStringInt               // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:44:43 2007----------*/
CdmValueDictStringInt::CdmValueDictStringInt(long p_lDatabaseId,
                                   long p_lId,
                                   QString p_qstrKeyname,
                                   CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictStringInt, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 13. Aug 16:21:44 2007----------*
 * @method  CdmValueDictStringInt::CdmValueDictStringInt               // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 16:21:44 2007----------*/
CdmValueDictStringInt::CdmValueDictStringInt(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:39:34 2012----------*
 * @method  CdmValueDictStringInt::CdmValueDictStringInt     // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObejct                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:39:34 2012----------*/
CdmValueDictStringInt::CdmValueDictStringInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObejct)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObejct)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:44:50 2007----------*
 * @method  CdmValueDictStringInt::~CdmValueDictStringInt              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:44:50 2007----------*/
CdmValueDictStringInt::~CdmValueDictStringInt()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:35:08 2012-----------*
 * @method  CdmValueDictStringInt::Deploy                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:35:08 2012-----------*/
void CdmValueDictStringInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Fr 13. Jun 16:50:58 2008----------*
 * @method  CdmValueDictStringInt::SetValue                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Fr 13. Jun 16:50:58 2008----------*/
void CdmValueDictStringInt::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:55:55 2013----------*
 * @method  CdmValueDictStringInt::GetValue                  // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:55:55 2013----------*/
QString CdmValueDictStringInt::GetValue() const
{
   Serialize();
   return m_qstrDocument;
} 

/** +-=---------------------------------------------------------Di 12. Feb 10:56:00 2013----------*
 * @method  CdmValueDictStringInt::Serialize                 // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:56:00 2013----------*/
void CdmValueDictStringInt::Serialize() const
{
   QDomDocument qddDocument(WMS_MAP);

   QMap<QString, int>::const_iterator qmIt = m_qmMap.begin();
   QMap<QString, int>::const_iterator qmItEnd = m_qmMap.end();

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

/** +-=---------------------------------------------------------Mo 13. Aug 15:23:47 2007----------*
 * @method  CdmValueDictStringInt::Deserialize                    // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: --------------------------------Mo 13. Aug 15:23:47 2007----------*/
void CdmValueDictStringInt::Deserialize()
{
    DeserializeXmlToMap(m_qstrDocument, m_qmMap);
}

void CdmValueDictStringInt::DeserializeXmlToMap(QString& p_qstrXml, QMap<QString,int>& p_qmMap)
{
   p_qmMap.clear();
   QDomDocument qddDocument("DictStringDouble");
   QString qstrKey;
   QString qstrData;
   qddDocument.setContent(p_qstrXml);
   QString qstrTest = qddDocument.toString();
   QDomElement qdeElement = qddDocument.documentElement(); // List Entries
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
         p_qmMap[qstrKey] = qstrData.toInt();
      }

      qdnNode = qdnNode.nextSibling();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 09:34:44 2012----------*
 * @method  CdmValueDictStringInt::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   int p_iData                                      //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:34:44 2012----------*/
void CdmValueDictStringInt::SetValue(QString p_qstrKey, int p_iData)
{

   m_qmMap[p_qstrKey] = p_iData;
   ValueChanged();
}

/** +-=---------------------------------------------------------Di 20. Nov 09:34:53 2012----------*
 * @method  CdmValueDictStringInt::SetValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QMap<QString, int> p_qmValue                     //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:34:53 2012----------*/
void CdmValueDictStringInt::SetValue(QMap<QString, int> p_qmValue)
{
   m_qmMap= p_qmValue;
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:03:09 2013----------*
 * @method  CdmValueDictStringInt::ExistValue                // public, const, slots              *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment returns if a value exists.                                                            *
 *----------------last changed: --------------------------------So 10. Feb 09:03:09 2013----------*/
bool CdmValueDictStringInt::ExistValue(QString p_qstrKey) const
{
   bool bRet = false;

   if (m_qmMap.contains(p_qstrKey))
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 10. Feb 09:03:32 2013----------*
 * @method  CdmValueDictStringInt::GetValue                  // public, const, slots              *
 * @return  int                                              //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment returns the value to the given key.                                                   *
 *----------------last changed: --------------------------------So 10. Feb 09:03:32 2013----------*/
int CdmValueDictStringInt::GetValue(QString p_qstrKey) const
{
   int iRet = -1;

   if (m_qmMap.contains(p_qstrKey))
   {
      iRet = m_qmMap[p_qstrKey];
   }

   return iRet;
}


/** +-=---------------------------------------------------------Di 20. Nov 09:35:19 2012----------*
 * @method  CdmValueDictStringInt::RemoveValue               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:35:19 2012----------*/
void CdmValueDictStringInt::RemoveValue(QString p_qstrKey)
{
   m_qmMap.remove(p_qstrKey);
   ValueChanged();
}


/** +-=---------------------------------------------------------Di 20. Nov 09:35:26 2012----------*
 * @method  CdmValueDictStringInt::ClearDict                 // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:35:26 2012----------*/
void CdmValueDictStringInt::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:03:41 2013----------*
 * @method  CdmValueDictStringInt::GetDict                   // public, const, slots              *
 * @return  QMap<QString, int>                               //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:03:41 2013----------*/
QMap<QString, int> CdmValueDictStringInt::GetDict() const
{
   return m_qmMap;
}

/** +-=---------------------------------------------------------So 10. Feb 09:03:50 2013----------*
 * @method  CdmValueDictStringInt::GetValueAsString          // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:03:50 2013----------*/
QString CdmValueDictStringInt::GetValueAsString() const
{
   QString qstrList;

   QMap<QString, int>::const_iterator qmIt = m_qmMap.begin();
   QMap<QString, int>::const_iterator qmItEnd = m_qmMap.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qstrList += qmIt.key() + "|" + QString::number(qmIt.value()) + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:03:58 2013----------*
 * @method  CdmValueDictStringInt::GetValueVariant           // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:03:58 2013----------*/
QVariant CdmValueDictStringInt::GetValueVariant() const
{
    QVariantMap qvVariant;

    for (auto key : m_qmMap.keys())
    {
        qvVariant.insert(key, m_qmMap[key]);
    }

    return qvVariant;
}

void CdmValueDictStringInt::SetValueVariant(QVariant& p_rVariant)
{
    QVariantMap values = p_rVariant.toMap();
    m_qmMap.clear();

    for(auto v: values.keys())
    {
        int iValue = values[v].toInt();
        m_qmMap.insert(v, iValue);
    }
}
