// System and QT Includes
#include <qdom.h>
#include <QList>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueListInt.h"

CdmValueListInt::CdmValueListInt(qint64 p_lDatabaseId,
                      qint64 p_lId,
                       QString p_qstrKeyname,
                       CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListInt, p_pCdmObject)
{
}

CdmValueListInt::CdmValueListInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

CdmValueListInt::~CdmValueListInt()
{
}

void CdmValueListInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

void CdmValueListInt::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

QString CdmValueListInt::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

void CdmValueListInt::Serialize() const
{
   QDomDocument qddDocument(WMS_LIST);

   QList<int>::const_iterator qvlIt = m_qvlInts.begin();
   QList<int>::const_iterator qvlItEnd = m_qvlInts.end();

   QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
   qddDocument.appendChild(qdeElement);
   int iCounter = 1;

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
      qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
      qdeMapEntry.setAttribute(WMS_DATA, QString::number(*qvlIt));
      qdeElement.appendChild(qdeMapEntry);
      ++iCounter;
   }


   m_qstrDocument = qddDocument.toString();
}

void CdmValueListInt::Deserialize()
{
   DeserializeXmlToIntList(m_qstrDocument, m_qvlInts);
}

void CdmValueListInt::DeserializeXmlToIntList(QString& p_qstrXml, QList<int>& p_qllList)
{
   p_qllList.clear();
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
      p_qllList.append(qstrData.toInt());

      qdnNode = qdnNode.nextSibling();
   }
}

void CdmValueListInt::AddValue(int p_iValue)
{
   if (!m_qvlInts.contains(p_iValue))
   {
      m_qvlInts.append(p_iValue);
      ValueChanged();
   }
}

void CdmValueListInt::RemoveValue(int p_iValue)
{
   m_qvlInts.removeOne(p_iValue);
   ValueChanged();
}

QList<int> CdmValueListInt::GetList() const
{
   return m_qvlInts;
}

void CdmValueListInt::SetList(QList<int> p_qllInts)
{
   m_qvlInts = p_qllInts;
   ValueChanged();
}

QString CdmValueListInt::GetValueAsString() const
{
   QString qstrList;

   QList<int>::const_iterator qvlIt = m_qvlInts.begin();
   QList<int>::const_iterator qvlItEnd = m_qvlInts.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      qstrList += QString::number(*qvlIt) + "\n";
   }

   return qstrList;
}

QVariant CdmValueListInt::GetValueVariant() const
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

void CdmValueListInt::SetValueVariant(QVariant& p_rVariant)
{
    QVariantList values = p_rVariant.toList();
    m_qvlInts.clear();

    for(QVariant v: values)
    {
        bool success;
        int iVal = v.toInt(&success);
        if(success)
        {
            m_qvlInts.append(iVal);
        }
    }
}
