#ifndef CSCRIPTMEMBER
#define CSCRIPTMEMBER

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaModelElement.h"
#include "IsaMember.h"

// Forwards
class CdmMember;
class CsaFactory;

class WMSMANAGER_API CsaMember : public CsaModelElement, public IsaMember
{
    Q_OBJECT
    friend class CsaFactory;

    void addLinksToVariant(QVariantMap &qvm);
public:
    CsaMember(CdmMember* p_pElement);
    CsaMember():CsaModelElement(NULL){}
    ~CsaMember();
    CdmMember* getInternals();

    QVariant getRoughVariant();     
    QVariant getDetailedVariant();
public slots:
        virtual int getType();
        virtual QString getTypeAsString();
        virtual int getAccessMode();
        virtual bool isPrivate();
        virtual bool isProtected();
        virtual bool isPublic();
        virtual bool isMust();
        virtual bool isTree();
        virtual bool isOwner();
        virtual bool isPersistent();
        virtual bool isUnique();
        virtual bool isSystemMember();
        virtual int getSize();
        virtual int getCounterStart();
        virtual int getDecimalCountOutput();
        virtual int getDecimalCountInput();
        virtual QString getPrefix();
        virtual QString getSufffix();
        virtual QString getGroupName();
        virtual QVariant getDefault();
        virtual QString getComment();
};

#endif //
