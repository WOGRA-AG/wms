#ifndef CDMVALUEUSERGROUP_H
#define CDMVALUEUSERGROUP_H

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
class WMSMANAGER_API CdmValueUserGroup : public CdmValueInt
{
    Q_OBJECT

public:
    CdmValueUserGroup( long p_lDatabaseId,
                       long p_lId,
                       QString p_qstrKeyname,
                       CdmObject* p_pCdmObject);
    CdmValueUserGroup( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueUserGroup( );

    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Restore(QString p_qstrValue);

public slots:
    CumUserGroup* GetUserGroup( );
    void SetUserGroup( CumUserGroup* p_pCumUserGroup);
    virtual QString GetDisplayString( ) const;


};

#endif //
