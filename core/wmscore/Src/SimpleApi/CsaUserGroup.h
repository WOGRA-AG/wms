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
    virtual QVariant getDetailedVariant();

    public slots:
    int getId();
    QString getName();
    QVariantList getUsers();
};

#endif //
