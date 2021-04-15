// System and QT Includes
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueDictStringDouble.h"

CdmValueDictStringDouble::CdmValueDictStringDouble(long p_lDatabaseId,
                                         long p_lId,
                                         QString p_qstrKeyname,
                                         CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDictStringDouble, p_pCdmObject)
{
}

CdmValueDictStringDouble::CdmValueDictStringDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

CdmValueDictStringDouble::~CdmValueDictStringDouble()
{
}

void CdmValueDictStringDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

void CdmValueDictStringDouble::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

QString CdmValueDictStringDouble::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

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

void CdmValueDictStringDouble::SetValue(QString p_qstrKey, double p_dData)
{
   m_qmMap[p_qstrKey] = p_dData;
   ValueChanged();
}

void CdmValueDictStringDouble::SetValue(QMap<QString, double> p_qmValue)
{
   m_qmMap = p_qmValue;
   ValueChanged();
}

void CdmValueDictStringDouble::RemoveValue(QString p_qstrKey)
{
   m_qmMap.remove(p_qstrKey);
   ValueChanged();
}

void CdmValueDictStringDouble::ClearDict()
{
   CdmValueCharacterDocument::SetValue("");
   m_qmMap.clear();
   ValueChanged();
}

QMap<QString, double> CdmValueDictStringDouble::GetDict() const
{
   return m_qmMap;
}

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
