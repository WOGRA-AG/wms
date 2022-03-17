#ifndef CSCRIPTCLASS
#define CSCRIPTCLASS

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaModelElement.h"
#include "IsaClass.h"

// Forwards
class CdmClass;
class CdmClassManager;
class CsaFactory;
class CsaFunction;

class WMSMANAGER_API CsaClass : public CsaModelElement, public IsaClass
{
    Q_OBJECT

friend class CsaFactory;

private:
    QMap<QString, CsaFunction*> m_qmFunctions;

    void addStaticFunctionsToClass();
    void addMembersToVariant(CdmClass* pClass, QVariantMap& qvm);
    void addBaseClassesToVariant(CdmClass* pClass, CdmClassManager* pClassManager, QVariantMap& qvm);
    void addLinksToVariant(QVariantMap &qvm);

    void addFunctionsToVariant(QVariantMap &qvm);
public slots:
        QObject *findMember(QString p_qstrKeyname);
        QVariantList getMembers();
        QVariantList getBaseClasses();
        bool isTypeOf(QObject *p_pClass);
        bool isImmutable();

        QObject *getSingletonObject();
        QString getComment();
        QString getCaptionMember();
public:
    CdmClass *getInternals();
    virtual ~CsaClass();
    CsaClass(CdmClass *p_pClass);
    CsaClass():CsaModelElement(NULL){}
    bool isSingleton();


    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();
    QVariant getRoughVariant();

    CsaFunction *getFunction(QString p_qstrName);
};

#endif //
