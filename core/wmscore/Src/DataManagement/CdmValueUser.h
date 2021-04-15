#ifndef CDMVALUEUSER_H
#define CDMVALUEUSER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CdmValueInt.h"


// Forwards


// Enumerations

/* 
 * This class implements the user value
 */
class WMSMANAGER_API CdmValueUser : public CdmValueInt
{
    Q_OBJECT

public:
    CdmValueUser( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    virtual ~CdmValueUser( );


public:
    virtual QVariant GetVariant() const;
    CdmValueUser( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Restore(QString p_qstrValue);

public slots:
    CumUser* GetUser( );
    void SetUser( CumUser* p_pCumUser);
    virtual QString GetDisplayString( ) const;
    virtual QString GetLogin( ) const;

};

#endif //
