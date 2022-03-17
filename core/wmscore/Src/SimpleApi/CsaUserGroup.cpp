// System and QT Includes

// own Includes
#include "CumUserGroup.h"
#include "CumUser.h"
#include "CsaFactory.h"
#include "CsaUserGroup.h"

CsaUserGroup::CsaUserGroup(CumUserGroup *p_pGroup)
{
    setElement(p_pGroup);
}

CsaUserGroup::~CsaUserGroup()
{
}

QVariantList CsaUserGroup::getUsers()
{
    QList<CumUser*> qllUsers;
    QVariantList qlUsers;
    getInternals()->GetUserListNewPointers(qllUsers);

    QList<CumUser*>::iterator qllIt = qllUsers.begin();
    QList<CumUser*>::iterator qllItEnd = qllUsers.end();

    for(; qllIt != qllItEnd; ++qllIt)
    {
        CsaLocatedElement* pElement = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(*qllIt);
        qlUsers.append(QVariant::fromValue(pElement));
    }

    return qlUsers;
}


QString CsaUserGroup::getName()
{
    CumUserGroup* pGroup = getInternals();

    if (CHKPTR(pGroup))
    {
        return pGroup->GetGroupName();
    }

    return "";
}


int CsaUserGroup::getId()
{
    CumUserGroup* pGroup = getInternals();

    if (CHKPTR(pGroup))
    {
        return pGroup->GetId();
    }

    return -1
            ;
}

CumUserGroup *CsaUserGroup::getInternals()
{
    CdmLocatedElement* pElement = getElement();

    if (CHKPTR(pElement) && pElement->IsUserGroup())
    {
        return static_cast<CumUserGroup*>(pElement);
    }

    return nullptr;
}

QVariant CsaUserGroup::getDetailedVariant()
{
    QVariantMap qvm;
    CumUserGroup* pGroup = getInternals();

    if (CHKPTR(pGroup))
    {
      qvm = pGroup->GetVariant().toMap();
    }

    return qvm;
}
