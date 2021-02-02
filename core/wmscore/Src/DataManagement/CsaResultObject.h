#ifndef CSARESULTOBJECT_H
#define CSARESULTOBJECT_H

// System and Qt Includes
#include <QObject>

// own Includes
#include "CdmValue.h"
#include "datamanager.h"

class WMSMANAGER_API CsaResultObject : public QObject
{
    Q_OBJECT

  private:
    QVariant m_qResult;
    EdmValueType m_eResultType;
    QString m_qstrMimeType;

public:
    CsaResultObject(QObject* parent = NULL);
    virtual ~CsaResultObject();
    QVariant getVariantMap();

public slots:
    void setResult(QVariant p_qvResult);
    QVariant getResult();
    void setResultType(EdmValueType p_eValue);
    EdmValueType getResultType();
    void setMimeType(QString p_qstrMimeType);
    QString getMimeType();
};



#endif // CSARESULTOBJECT_H
