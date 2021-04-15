#ifndef CDMLONG_H
#define CDMLONG_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"



/*
 * This class implements the long value
 * of the framework
 */
class WMSMANAGER_API CdmValueLong : public CdmValue 
{
    Q_OBJECT

private:
    /*
       * The long value
       */
    long m_lValue;

public:
    CdmValueLong(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    CdmValueLong( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueLong(  );
    void SetDefaultValue(  const CdmMember* p_pCdmMember );
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);
    virtual QString GetDisplayString() const;
    int FromStringToValue(  QString p_qstrValue );
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;

public slots:
    virtual QVariant GetValueVariant( ) const;
    virtual QString GetValueAsString( ) const;
    void SetValue( long p_lValue);
    long GetValue( ) const;


protected:
    CdmValueLong(long p_lDatabaseId,
                 long p_lId,
                 QString p_qstrKeyname,
                 EdmValueType p_eDmValue,
                 CdmObject* p_pCdmObject );

};
#endif // //CDMLONG_H
