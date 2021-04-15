#ifndef CDMVALUEENUM_H
#define CDMVALUEENUM_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QStringList>

// Own Includes
#include "CdmValueInt.h"


// Forwards


// Enumerations

/* 
 * This class implements the user value
 */
class WMSMANAGER_API CdmValueEnum : public CdmValueInt
{
    Q_OBJECT

public:
    CdmValueEnum( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueEnum( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueEnum( );
    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Restore(QString p_qstrValue);

public slots:
    QStringList GetSelectionList( ) const;
    virtual QString GetDisplayString( ) const;

};

#endif //
