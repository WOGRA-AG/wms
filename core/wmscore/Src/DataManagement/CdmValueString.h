#ifndef CDMSTRING_H
#define CDMSTRING_H

// Sytsem and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueString : public CdmValue 
{
    Q_OBJECT

private:
    QString m_qstrValue;

public:
    CdmValueString(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    CdmValueString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueString(  );
    void SetDefaultValue(  const CdmMember* p_pCdmMember );
    int FromStringToValue(  QString p_qstrValue );
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    virtual QString GetValue( ) const;
    virtual void SetValue( const QString& p_qstrValue);
    virtual QString GetDisplayString( ) const;
    virtual QVariant GetValueVariant( ) const;
    virtual QString GetValueAsString( ) const;
    virtual bool HasValue( ) const;

};
#endif // //CDMSTRING_H
