// System and QT Includes
#include <qdom.h>
#include <QList>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueListDouble.h"

CdmValueListDouble::CdmValueListDouble(long p_lDatabaseId,
                             long p_lId,
                             QString p_qstrKeyname,
                             CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListDouble, p_pCdmObject)
{
}

CdmValueListDouble::CdmValueListDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

CdmValueListDouble::~CdmValueListDouble()
{
}

void CdmValueListDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

void CdmValueListDouble::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

QString CdmValueListDouble::GetValue() const
{
   Serialize();
   return m_qstrDocument;
}

void CdmValueListDouble::Serialize() const
{
   QDomDocument qddDocument(WMS_LIST);

   QList<double>::const_iterator qvlIt = m_qvlDoubles.begin();
   QList<double>::const_iterator qvlItEnd = m_qvlDoubles.end();

   QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
   qddDocument.appendChild(qdeElement);
   int iCounter = 1;

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
      qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
      qdeMapEntry.setAttribute(WMS_DATA, QString::number(*qvlIt, 'f', 16));
      qdeElement.appendChild(qdeMapEntry);
      ++iCounter;
   }

   m_qstrDocument = qddDocument.toString();
}

void CdmValueListDouble::Deserialize()
{
    CdmValueListDouble::DeserializeXmlToDoubleList(m_qstrDocument, m_qvlDoubles);
}

void CdmValueListDouble::DeserializeXmlToDoubleList(QString& p_qstrXml, QList<double>& p_qllList)
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
       p_qllList.append(qstrData.toDouble());
       qdnNode = qdnNode.nextSibling();
    }
}

void CdmValueListDouble::AddValue(double p_dValue)
{
   if (!m_qvlDoubles.contains(p_dValue))
   {
      m_qvlDoubles.append(p_dValue);
      ValueChanged();
   }
}

void CdmValueListDouble::RemoveValue(double p_dValue)
{
   m_qvlDoubles.removeOne(p_dValue);
   ValueChanged();
}

QList<double> CdmValueListDouble::GetList() const
{
   return m_qvlDoubles;
}

void CdmValueListDouble::SetList(QList<double> p_qllDoubles)
{
   m_qvlDoubles = p_qllDoubles;
   ValueChanged();
}

QString CdmValueListDouble::GetValueAsString() const
{
   QString qstrList;

   QList<double>::const_iterator qvlIt = m_qvlDoubles.begin();
   QList<double>::const_iterator qvlItEnd = m_qvlDoubles.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      qstrList += QString::number(*qvlIt) + "\n";
   }

   return qstrList;
}

QVariant CdmValueListDouble::GetValueVariant() const
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

void CdmValueListDouble::SetValueVariant(QVariant& p_rVariant)
{
    QVariantList values = p_rVariant.toList();
    m_qvlDoubles.clear();
    for(QVariant v: values) {
        bool success;
        double iVal = v.toDouble(&success);
        if(success){
            m_qvlDoubles.append(iVal);
        }
    }
}
