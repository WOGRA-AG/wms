#ifndef CDMLONG_H
#define CDMLONG_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"



/*
 * This class implements the qint64 value
 * of the framework
 */
class WMSMANAGER_API CdmValueLong : public CdmValue 
{
    Q_OBJECT

private:
    /*
       * The qint64 value
       */
   qint64 m_lValue;

public:
    CdmValueLong( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
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
    void SetValue(qint64 p_lValue);
   qint64 GetValue( ) const;


protected:
    CdmValueLong(qint64 p_lDatabaseId,
                qint64 p_lId,
                 QString p_qstrKeyname,
                 EdmValueType p_eDmValue,
                 CdmObject* p_pCdmObject );

};
#endif // //CDMLONG_H
