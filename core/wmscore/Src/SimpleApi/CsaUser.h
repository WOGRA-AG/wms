/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSCRIPTUSER
#define CSCRIPTUSER

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CumUser;
class CsaFactory;


class WMSMANAGER_API CsaUser : public CsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;

private:
    CsaUser(CumUser* p_pUser);
    CsaUser(){}
    ~CsaUser();

public:
    CumUser* getInternals();

public slots:
    int getId();
    QString getFirstName();
    QString getLastName();
    QString getLogin();
    QString getEmail();
    bool isActive();
    bool isAdmin();
    QVariantList getGroups();





    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();

};

#endif //
