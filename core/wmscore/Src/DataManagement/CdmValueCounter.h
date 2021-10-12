#ifndef CDMCOUNTER_H
#define CDMCOUNTER_H


// System and QT Includes

// own Includes
#include "CdmValueLong.h"

// forwards


/*
 * This method implements the counter value.
 * The counter value is a value which will
 * automatically set by the database. dependent
 * from start value.
 */
class WMSMANAGER_API CdmValueCounter : public CdmValueLong 
{
    Q_OBJECT

public:
    CdmValueCounter( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    virtual ~CdmValueCounter(  );
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    CdmValueCounter( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMCOUNTER_H
