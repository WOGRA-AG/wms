// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueCounter.h"

CdmValueCounter::CdmValueCounter(  long p_lDatabaseId,
                        long p_lId,
                        QString p_qstrKeyname,
                        CdmObject* p_pCdmObject )
   : CdmValueLong( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueCounter, p_pCdmObject)
{
   // nothing to do
}

CdmValueCounter::CdmValueCounter(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueLong(p_rqvHash, p_pCdmObject)
{
   // nothing to do
}

CdmValueCounter::~CdmValueCounter()
{
   // nothing to do
}

void CdmValueCounter::SetDefaultValue(const CdmMember*)
{
   // there are no default values for this Value must be ignored
}


void CdmValueCounter::SetValue(QString , QString)
{
   ERR("Set Value is not supported by Counters");
}

void CdmValueCounter::SetVariant(QVariantMap& p_rqvHash)
{
   // Does nothing
   Q_UNUSED(p_rqvHash);
}
