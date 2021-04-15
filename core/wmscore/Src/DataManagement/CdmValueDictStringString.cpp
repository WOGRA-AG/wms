// System and QT Includes
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueDictStringString.h"

CdmValueDictStringString::CdmValueDictStringString(long p_lDatabaseId,
                                         long p_lId,
                                         QString p_qstrKeyname,
                                         CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictStringString, p_pCdmObject)
{
}


CdmValueDictStringString::CdmValueDictStringString(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

CdmValueDictStringString::~CdmValueDictStringString()
{
}

void CdmValueDictStringString::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

void CdmValueDictStringString::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

QString CdmValueDictStringString::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

QString CdmValueDictStringString::GetValue(QString p_qstrKey)
{
   QString qstrRet = "";

   if (m_qmMap.contains(p_qstrKey))
   {
      qstrRet = m_qmMap[p_qstrKey];
   }

   return qstrRet;
}


bool CdmValueDictStringString::ExistValue(QString p_qstrKey)
{
   bool bRet = false;

   if (m_qmMap.contains(p_qstrKey))
   {
      bRet = true;
   }

   return bRet;
}

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

void CdmValueDictStringString::SetValue(QString p_qstrKey, QString p_qstrData)
{
   m_qmMap[p_qstrKey] = p_qstrData;
   ValueChanged();
}

void CdmValueDictStringString::SetValue(QMap<QString, QString> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}

void CdmValueDictStringString::RemoveValue(QString p_qstrKey)
{
   m_qmMap.remove(p_qstrKey);
   ValueChanged();
}

void CdmValueDictStringString::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

QMap<QString, QString> CdmValueDictStringString::GetDict() const
{
   return m_qmMap;
}

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
