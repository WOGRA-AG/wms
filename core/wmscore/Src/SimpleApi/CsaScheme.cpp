/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include "wmsdefines.h"

// own Includes
#include "CdmScheme.h"
#include "CsaScheme.h"


CsaScheme::CsaScheme(CdmScheme* p_pDatabase)
: CsaLocatedElement(),
  m_rpDatabase(p_pDatabase)
{
    setElement(p_pDatabase);
}

CsaScheme::~CsaScheme()
{
}

CdmScheme *CsaScheme::getInternals()
{
    return m_rpDatabase;
}

QString CsaScheme::getName()
{
    return m_rpDatabase->GetSchemeName();
}

int CsaScheme::getVersion()
{
    return m_rpDatabase->GetVersion();
}


QVariant CsaScheme::getDetailedVariant()
{
    QVariantMap qvm;
    qvm.insert(WMS_NAME, getName());
    qvm.insert(WMS_VERSION, getVersion());
    return qvm;
}




