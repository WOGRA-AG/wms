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

// WMS Commons Includes
#include "wmsdefines.h"

// own Includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CsaMember.h"


CsaMember::CsaMember(CdmMember *p_pElement)
    : CsaModelElement(p_pElement)
{

}


CsaMember::~CsaMember()
{

}


CdmMember *CsaMember::getInternals()
{
    return static_cast<CdmMember*>(getElement());
}

int CsaMember::getType()
{
    return getInternals()->GetValueType();
}

QString CsaMember::getTypeAsString()
{
    return getInternals()->GetValueTypeAsString();
}

int CsaMember::getAccessMode()
{
    return getInternals()->GetAccessMode();
}

bool CsaMember::isPrivate()
{
    return (getInternals()->GetAccessMode() == eDmMemberAccessPrivate);
}

bool CsaMember::isProtected()
{
    return (getInternals()->GetAccessMode() == eDmMemberAccessProtected);
}

bool CsaMember::isPublic()
{
    return (getInternals()->GetAccessMode() == eDmMemberAccessPublic);
}

bool CsaMember::isMust()
{
    return getInternals()->IsMust();
}

bool CsaMember::isTree()
{
    return getInternals()->IsTree();
}

bool CsaMember::isPersistent()
{
    return getInternals()->IsPersistent();
}

bool CsaMember::isUnique()
{
   return getInternals()->IsUnique();
}

bool CsaMember::isSystemMember()
{
    return getInternals()->IsSystemMember();
}

int CsaMember::getSize()
{
    return getInternals()->GetSize();
}

int CsaMember::getCounterStart()
{
    return getInternals()->GetCounterStart();
}

int CsaMember::getDecimalCountOutput()
{
    return getInternals()->GetDecimalCountOutput();
}

int CsaMember::getDecimalCountInput()
{
    return getInternals()->GetDecimalCountInput();
}

QString CsaMember::getPrefix()
{
    return getInternals()->GetPrefix();
}

QString CsaMember::getSufffix()
{
    return getInternals()->GetSuffix();
}

QString CsaMember::getGroupName()
{
return getInternals()->GetGroupName();
}

QString CsaMember::getComment()
{
    return getInternals()->GetComment();
}

QVariant CsaMember::getDefault()
{
    return getInternals()->GetDefaultValue();
}

bool CsaMember::isOwner()
{
    return getInternals()->IsOwner();
}

QVariant CsaMember::getRoughVariant()
{
    QVariantMap qvm;
    addVariantData(qvm);
    qvm.insert(WMS_TYPE, getTypeAsString());
    qvm.insert(WMS_ACCESS, getInternals()->GetAccessModeAsString());
    qvm.insert(WMS_DETAIL,  getUri());
    return qvm;
}


QVariant CsaMember::getDetailedVariant()
{
    QVariantMap qvm = getRoughVariant().toMap();
    CdmMember* pMember = getInternals();

    qvm.insert(WMS_MUST, isMust());
    qvm.insert(WMS_OWNER, isOwner());
    qvm.insert(WMS_PERSISTENT, isPersistent());
    qvm.insert(WMS_UNIQUE, isUnique());
    qvm.insert(WMS_COUNTERSTART, getCounterStart());
    qvm.insert(WMS_GROUPS, getGroupName());
    qvm.insert(WMS_COMMENT, getComment());
    qvm.insert(WMS_DEFAULT, getDefault());
    qvm.insert(WMS_SUFFIX, getSufffix());
    qvm.insert(WMS_PREFIX, getPrefix());
    qvm.insert(WMS_DECIMALCOUNTINPUT, getDecimalCountInput());
    qvm.insert(WMS_DECIMALCOUNTOUTPUT, getDecimalCountOutput());
    qvm.insert(WMS_SIZE, getSize());
    qvm.insert(WMS_SYSTEMVALUE, isSystemMember());
    qvm.insert(WMS_TREE, isTree());

    long lClassReference = pMember->GetClassReference();
    CdmClassManager* pClassManager = getInternals()->GetClassManager();

    if (CHKPTR(pClassManager))
    {
        if (lClassReference >= 0)
        {
            CdmClass* pRefClass = pClassManager->FindClassById(lClassReference);

            if (CHKPTR(pRefClass))
            {
                qvm.insert(WMS_REFERENCEURI, pRefClass->GetUri());
            }
        }
    }

    return qvm;
}

