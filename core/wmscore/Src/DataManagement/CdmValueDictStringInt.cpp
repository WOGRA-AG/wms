// System and QT Includes
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueDictStringInt.h"

CdmValueDictStringInt::CdmValueDictStringInt(qint64 p_lDatabaseId,
                                  qint64 p_lId,
                                   QString p_qstrKeyname,
                                   CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictStringInt, p_pCdmObject)
{
}

CdmValueDictStringInt::CdmValueDictStringInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObejct)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObejct)
{
   Deserialize();
}

CdmValueDictStringInt::~CdmValueDictStringInt()
{
}

void CdmValueDictStringInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

void CdmValueDictStringInt::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

QString CdmValueDictStringInt::GetValue() const
{
   Serialize();
   return m_qstrDocument;
} 

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

void CdmValueDictStringInt::SetValue(QString p_qstrKey, int p_iData)
{
   m_qmMap[p_qstrKey] = p_iData;
   ValueChanged();
}

void CdmValueDictStringInt::SetValue(QMap<QString, int> p_qmValue)
{
   m_qmMap= p_qmValue;
   ValueChanged();
}

bool CdmValueDictStringInt::ExistValue(QString p_qstrKey) const
{
   bool bRet = false;

   if (m_qmMap.contains(p_qstrKey))
   {
      bRet = true;
   }

   return bRet;
}

int CdmValueDictStringInt::GetValue(QString p_qstrKey) const
{
   int iRet = -1;

   if (m_qmMap.contains(p_qstrKey))
   {
      iRet = m_qmMap[p_qstrKey];
   }

   return iRet;
}

void CdmValueDictStringInt::RemoveValue(QString p_qstrKey)
{
   m_qmMap.remove(p_qstrKey);
   ValueChanged();
}

void CdmValueDictStringInt::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

QMap<QString, int> CdmValueDictStringInt::GetDict() const
{
   return m_qmMap;
}

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

QVariant CdmValueDictStringInt::GetValueVariant() const
{
    QVariantMap qvVariant;
    QStringList qstrlKeys = m_qmMap.keys();

    for (auto key : qstrlKeys)
    {
        qvVariant.insert(key, m_qmMap[key]);
    }

    return qvVariant;
}

void CdmValueDictStringInt::SetValueVariant(QVariant& p_rVariant)
{
    QVariantMap values = p_rVariant.toMap();
    m_qmMap.clear();
    QStringList qstrlKeys = values.keys();

    for(auto v: qstrlKeys)
    {
        int iValue = values[v].toInt();
        m_qmMap.insert(v, iValue);
    }
}
