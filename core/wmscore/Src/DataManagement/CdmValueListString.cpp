// System and QT Includes
#include <qdom.h>
#include <QList>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueListString.h"

CdmValueListString::CdmValueListString(long p_lDatabaseId,
                             long p_lId,
                             QString p_qstrKeyname,
                             CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListString,p_pCdmObject)
{
}

CdmValueListString::CdmValueListString(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

CdmValueListString::~CdmValueListString()
{
}

void CdmValueListString::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

void CdmValueListString::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

QString CdmValueListString::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

void CdmValueListString::Serialize() const
{
   QDomDocument qddDocument(WMS_LIST);

   QList<QString>::const_iterator qvlIt = m_qvlStrings.begin();
   QList<QString>::const_iterator qvlItEnd = m_qvlStrings.end();

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

void CdmValueListString::Deserialize()
{
    DeserializeXmlToStringList(m_qstrDocument, m_qvlStrings);
}

void CdmValueListString::DeserializeXmlToStringList(QString& p_qstrXml, QList<QString>& p_qllResultList)
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

void CdmValueListString::AddValue(QString p_qstrValue)
{

   if (!m_qvlStrings.contains(p_qstrValue))
   {
      m_qvlStrings.append(p_qstrValue);
      ValueChanged();
   }
}

void CdmValueListString::RemoveValue(QString p_qstrValue)
{

   m_qvlStrings.removeOne(p_qstrValue);
   ValueChanged();
}

QList<QString> CdmValueListString::GetList() const
{
   return m_qvlStrings;
}

void CdmValueListString::ClearList()
{
   m_qvlStrings.clear();
   ValueChanged();
}

void CdmValueListString::SetList(QList<QString> p_qllStrings)
{
   m_qvlStrings = p_qllStrings;
   ValueChanged();
}

QString CdmValueListString::GetValueAsString() const
{
   QString qstrList;
   QList<QString>::const_iterator qvlIt = m_qvlStrings.begin();
   QList<QString>::const_iterator qvlItEnd = m_qvlStrings.end();

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
