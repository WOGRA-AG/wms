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


// Own Includes
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CsaFactory.h"
#include "CsaUser.h"


CsaUser::CsaUser(CumUser *p_pUser)
{
    setElement(p_pUser);
}


CsaUser::~CsaUser()
{
}

int CsaUser::getId()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->GetId();
    }

    return -1;
}

QString CsaUser::getFirstName()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->GetLastName();
    }

    return "";
}

QString CsaUser::getLastName()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->GetFirstName();
    }

    return "";
}

QString CsaUser::getLogin()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->GetLogin();
    }

    return "";
}

QString CsaUser::getEmail()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->GetEmail();
    }

    return "";
}

bool CsaUser::isActive()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->IsActive();
    }

    return false;
}

bool CsaUser::isAdmin()
{
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        return pUser->IsAdministrator();
    }

    return false;
}

QVariantList CsaUser::getGroups()
{
    QVariantList qlGroups;
    QList<CumUserGroup*> qllGroups;

    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
        pUser->GetUserGroups(qllGroups);
    }

    QList<CumUserGroup*>::iterator qllIt = qllGroups.begin();
    QList<CumUserGroup*>::iterator qllItEnd = qllGroups.end();

    for(; qllIt != qllItEnd; ++qllIt)
    {
        CsaLocatedElement* pElement = getFactory()->createScriptObject(*qllIt);
        qlGroups.append(QVariant::fromValue(pElement));
    }

    return qlGroups;
}

CumUser *CsaUser::getInternals()
{
    return dynamic_cast<CumUser*> (getElement());
}


QVariant CsaUser::getDetailedVariant()
{
    QVariantMap qvm;
    CumUser* pUser = getInternals();

    if (CHKPTR(pUser))
    {
       qvm = pUser->GetVariant().toMap();
    }

    return qvm;
}


