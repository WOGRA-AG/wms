#ifndef CDMDATE_H
#define CDMDATE_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements a date value
 */
class WMSMANAGER_API CdmValueDate : public CdmValue 
{
    Q_OBJECT
private:    
    QDate m_qdValue;

public:
    CdmValueDate(qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueDate( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueDate();
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QVariant GetValueVariant() const;
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    QString GetDisplayString() const;
    void SetValue(const QDate& p_rqdDate);
    QDate GetValue() const;
    void SetValue(const qint64 p_lDate);
    void GetValue(qint64& p_dValue) const;

private:
    void XmlImportDate(QDomElement& p_rqDomElement);
};
#endif // //CDMDATE_H
