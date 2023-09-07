

// Own Includes
#include "CdmQueryEnhanced.h"


CdmQueryEnhanced::CdmQueryEnhanced(QObject* parent)
: CdmQuery(parent)
{
}

CdmQueryEnhanced::CdmQueryEnhanced(CdmObjectContainer* p_pContainer, QObject* parent)
: CdmQuery(p_pContainer, parent)
{
}

CdmQueryEnhanced::CdmQueryEnhanced(CdmClass* p_pCdmClass, QObject* parent)
: CdmQuery(p_pCdmClass, parent)
{
}

CdmQueryEnhanced::CdmQueryEnhanced(QVariantMap &p_rqvHash, QObject* parent)
: CdmQuery(p_rqvHash, parent)
{
}

CdmQueryEnhanced::CdmQueryEnhanced(const CdmQuery &p_rQuery, QObject* parent)
: CdmQuery(p_rQuery, parent)
{
}
