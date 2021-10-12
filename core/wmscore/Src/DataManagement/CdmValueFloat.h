#ifndef CDMFLOAT_H
#define CDMFLOAT_H


// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


/*
 * This class implements the float value
 */
class WMSMANAGER_API CdmValueFloat : public CdmValue 
{
    Q_OBJECT

private:
    /*
       * The float value
       */
    float m_fValue;

public:
    CdmValueFloat( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    CdmValueFloat(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );
    CdmValueFloat( QVariantMap& p_rqHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueFloat(  );
    void SetDefaultValue(  const CdmMember* p_pCdmMember );
    QString GetDisplayString() const;
    int FromStringToValue(  QString p_qstrValue );
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QVariant GetValueVariant() const;
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    void SetValue( float p_fValue);
    float GetValue( ) const;
};
#endif // //CDMFLOAT_H
