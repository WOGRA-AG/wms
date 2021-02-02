/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSCRIPTUSERGROUP
#define CSCRIPTUSERGROUP

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CumUserGroup;
class CsaFactory;

class WMSMANAGER_API CsaUserGroup : public CsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;

    private:
    CsaUserGroup(CumUserGroup* p_pGroup);
    CsaUserGroup(){}
    ~CsaUserGroup();

    public:
    CumUserGroup* getInternals();

    public slots:
    int getId();
    QString getName();
    QVariantList getUsers();

    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();

};

#endif //
