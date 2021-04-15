#ifndef CDMDOUBLE_H
#define CDMDOUBLE_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements the double value
 */
class WMSMANAGER_API CdmValueDouble : public CdmValue 
{
    Q_OBJECT

private:
    
    /*
       * The double value
       */
    double m_dValue;

public:
    CdmValueDouble(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    CdmValueDouble( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueDouble(  );
    void SetDefaultValue(  const CdmMember* p_pCdmMember );
    int IsEqual(  QVariant* p_pqVariant ) const;
    int IsSmaller(  QVariant* p_pqVariant ) const;
    int IsSmallerEqual(  QVariant* p_pqVariant ) const;
    int IsLarger(  QVariant* p_pqVariant ) const;
    int IsLargerEqual(  QVariant* p_pqVariant ) const;
    int IsNotEqual(  QVariant* p_pqVariant ) const;
    virtual QString GetDisplayString() const;
    int FromStringToValue(  QString p_qstrValue );
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    void SetValue( double p_dValue);
    double GetValue( ) const;

};
#endif // //CDMDOUBLE_H
