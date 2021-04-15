#ifndef CDMVALUEFORMULA_H
#define CDMVALUEFORMULA_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptValue>

// Own Includes
#include "CdmValue.h"


// Forwards


// Enumerations

/* 
 * This class implements formular value member
 */
class WMSMANAGER_API CdmValueFormula : public CdmValue
{
    Q_OBJECT

public:
    CdmValueFormula(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    virtual ~CdmValueFormula();
    void SetDefaultValue(const CdmMember*p_pCdmMember);

    int GetValueAsInt( );
    double GetValueAsDouble( );
    QDateTime GetValueAsTimestamp( );
    QDate GetValueAsDate( );
    QTime GetValueAsTime( );
    int FromStringToValue(QString p_qstrValue);
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void SetVariant(QVariantMap& p_rqvHash);

public slots:
    virtual QVariant GetValueVariant( ) const;
    QString GetDisplayString( ) const;
    virtual QString GetValueAsString( ) const;

private:
    QVariant Evaluate() const;
};

#endif //

