#ifndef CSCRIPTCLASSMANAGER
#define CSCRIPTCLASSMANAGER

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CdmClassManager;

class WMSMANAGER_API CsaClassManager : public CsaLocatedElement
{
    Q_OBJECT

friend class CsaFactory;

    private:
        CdmClassManager* m_pClassManager;
        CsaClassManager(CdmClassManager* p_pClassManager);
        virtual ~CsaClassManager();

    public slots:
        QObject *findClass(QString p_qstrKeyname);
        QVariantList getClassList();
        bool existClass(QString p_qstrKeyname);

    public:
        CdmClassManager* getInternals();



        // CsaLocatedElement interface
public:
        virtual QVariant getDetailedVariant();

};

#endif //
