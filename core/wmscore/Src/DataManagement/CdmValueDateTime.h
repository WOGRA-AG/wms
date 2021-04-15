#ifndef CDMDATETIME_H
#define CDMDATETIME_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"

// forwards

class WMSMANAGER_API CdmValueDateTime : public CdmValue 
{
    Q_OBJECT

private:    
    QDateTime m_qdtValue;

public:
    CdmValueDateTime(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    virtual ~CdmValueDateTime(  );
    void SetDefaultValue(  const CdmMember* p_pCdmMember );
    CdmValueDateTime(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );
    QString GetDisplayString() const;
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    CdmValueDateTime( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);
    void SetValue(  double p_dValue );
    void GetValue(double& p_dDateTime) const;

public slots:
    void SetValue(const QDateTime& p_rqdtDateTime);
    QDateTime GetValue() const;


};
#endif
