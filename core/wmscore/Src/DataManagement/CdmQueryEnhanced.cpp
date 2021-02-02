/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmQueryEnhanced.cpp
 ** Started Implementation: 2010/11/10
 ** Description:
 ** 
 ** This class implements the enhanced query for reading single values.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QStringList>

// Own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmQueryEnhanced.h"


CdmQueryEnhanced::CdmQueryEnhanced(QObject* parent)
: CdmQuery(parent)
{
    m_bForceEnhanced = true;
}

CdmQueryEnhanced::CdmQueryEnhanced(CdmObjectContainer* p_pContainer, QObject* parent)
: CdmQuery(p_pContainer, parent)
{
    m_bForceEnhanced = true;
}

CdmQueryEnhanced::CdmQueryEnhanced(CdmClass* p_pCdmClass, QObject* parent)
: CdmQuery(p_pCdmClass, parent)
{
    m_bForceEnhanced = true;
}

CdmQueryEnhanced::CdmQueryEnhanced(QVariantMap &p_rqvHash, QObject* parent)
: CdmQuery(p_rqvHash, parent)
{
    m_bForceEnhanced = true;
}

CdmQueryEnhanced::CdmQueryEnhanced(const CdmQuery &p_rQuery, QObject* parent)
: CdmQuery(p_rQuery, parent)
{
    m_bForceEnhanced = true;
}
