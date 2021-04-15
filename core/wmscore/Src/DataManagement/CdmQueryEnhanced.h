/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmQueryEnhanced.h
 ** Started Implementation: 2010/11/10
 ** Description:
 ** 
 ** This class implements the enhanced query for reading single values.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMQUERYENHANCED_H
#define CDMQUERYENHANCED_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// Own Includes
#include "datamanager.h"
#include "CdmQuery.h"


// Forwards


// Enumerations

// defines
#define SCOPED_ENHANCE_QUERY(a,b) QScopedPointer<CdmQueryEnhanced> a(dynamic_cast<CdmQueryEnhanced*>(CdmQueryBuilder::ExecuteQuery(b)));

/* 
 * This class implements the enhanced query for reading single values.
 */
class WMSMANAGER_API CdmQueryEnhanced : public CdmQuery
{
    Q_OBJECT

    friend class IdmDataAccess;
    friend class CdmDataAccessHelper;

public:
    CdmQueryEnhanced(QObject* parent = nullptr);

    CdmQueryEnhanced(CdmObjectContainer* p_pContainer, QObject* parent = nullptr);

    CdmQueryEnhanced(CdmClass* p_pCdmClass, QObject* parent = nullptr);

    CdmQueryEnhanced(QVariantMap &p_rqvHash, QObject* parent = nullptr);

    CdmQueryEnhanced(const CdmQuery &p_rQuery, QObject* parent = nullptr);
};

#endif //
