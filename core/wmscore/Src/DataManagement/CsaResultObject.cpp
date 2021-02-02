#include "CsaResultObject.h"
#include "CsaFactory.h"

#define RESULTVALUE "Value"
#define RESULTTYPE "Type"
#define RESULTMIMETYPE "MimeType"

CsaResultObject::CsaResultObject(QObject* parent)
  : QObject(parent),
    m_eResultType(eDmValueNone)
{

}

CsaResultObject::~CsaResultObject()
{

}

QVariant CsaResultObject::getVariantMap()
{
    QVariantMap qvObject;

    QVariant qConvertedResult = CsaFactory::convertToResultVariant(m_qResult);
    qvObject.insert(RESULTVALUE, qConvertedResult);
    qvObject.insert(RESULTTYPE, m_eResultType);
    qvObject.insert(RESULTMIMETYPE, m_qstrMimeType);

    return qvObject;
}

void CsaResultObject::setResult(QVariant p_qvResult)
{
    m_qResult = p_qvResult;
}

QVariant CsaResultObject::getResult()
{
    return m_qResult;
}

void CsaResultObject::setResultType(EdmValueType p_eValue)
{
    m_eResultType = p_eValue;
}

EdmValueType CsaResultObject::getResultType()
{
    return m_eResultType;
}

void CsaResultObject::setMimeType(QString p_qstrMimeType)
{
    m_qstrMimeType = p_qstrMimeType;
}

QString CsaResultObject::getMimeType()
{
    return m_qstrMimeType;
}
