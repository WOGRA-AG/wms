/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmProxyBase.h
 ** Started Implementation: 2011/08/25
 ** Description:
 **
 ** the base class for all proxies
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CDMPROXYBASE_H
#define CDMPROXYBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QList>
#include <QString>
#include <QSet>

// Own Includes
#include "datamanager.h"

// Forwards
class CdmObjectContainer;
class CdmObject;
class CdmQuery;


/* 
 * This class implements the base class for all proxies
 */
class WMSMANAGER_API CdmProxyBase
{
protected:
    bool m_bValid;
    int m_iTimeout;

protected:
    void SetValid();
    virtual void ValueChanged()= 0;
    virtual bool Check(CdmObject* p_pCdmObject);


public:
    CdmProxyBase( );
    bool IsValid();
    void SetValueChangeTimeout(int p_iTimeout);
    int GetValueChangeTimeout() const;
    virtual ~CdmProxyBase( );
    virtual CdmQuery* GetQuery()= 0;
    virtual void CreateQuery(CdmObjectContainer* p_pContainer)= 0;
};

#endif // CDMPROXYBASE_H
