/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmMemberRights.h
 ** Started Implementation: 2012/06/18
 ** Description:
 **
 ** Implements the rights for class groups
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CDMRIGHTS_H
#define CDMRIGHTS_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>

// Own Includes
#include "CdmLocatedElement.h"
#include "datamanager.h"

// Forwards
class CdmModelElement;
class CumUser;
class CumAccessor;

// TypeDefs

// Enumerations
enum EdmRight
{
    eDmRightNone,
    eDmRightRead,
    eDmRightWrite,
    eDmRightCreateOnly,
    eDmRightEditOnly,
    eDmRightCreateDeleteOnly,
    eDmRightEditDeleteOnly
};

/* 
 * This class implements the rights for class groups
 */
class WMSMANAGER_API CdmRights : public CdmLocatedElement
{
    Q_OBJECT

private:
    QMap<int, EdmRight> m_qmRights; // UserbaseId - RightType
    CdmModelElement* m_rpElement;

    CdmRights( const CdmRights&);
    QString GetUserUri(long p_iUserId) const;
    EdmRight FindRight(const CumUser* p_pCumUser) const;


public:
    CdmRights();
    CdmRights(CdmModelElement* p_pElement);
    CdmRights(CdmModelElement* p_pElement, QVariantMap& p_rqvHash);
    virtual ~CdmRights();
    void AddRight(int p_iUserBaseId, EdmRight p_eRight);
    void DeleteRight(int p_iUserBaseId);
    QVariant GetVariant() const;

    void SetVariant(QVariantMap& p_rqvHash);
    bool HasRight(int p_lUserBaseId) const;
    bool HasRight(CumAccessor* p_pCumAccessor) const;
    QMap<int, EdmRight> GetRights() const;
    bool HasRightConfigured(CumAccessor* p_pCumAccessor) const;
    bool HasRightConfigured(int p_lUserBaseId) const;
    void AddRight(CumAccessor *p_pAccessor, EdmRight p_eRight);

public slots:
    bool HasReadAccess( int p_iUserBaseId) const;
    bool HasWriteAccess( int p_iUserBaseId) const;
    bool HasCurrentUserWriteAccess( ) const;
    bool HasCurrentUserReadAccess( ) const;
};

#endif //
