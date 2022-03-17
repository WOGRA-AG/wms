#ifndef CSCRIPTDATABASE
#define CSCRIPTDATABASE

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CdmScheme;

class WMSMANAGER_API CsaScheme : public CsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;

private:
    CdmScheme* m_rpDatabase;

public:
    CdmScheme* getInternals();
    CsaScheme(CdmScheme* p_pDatabase);
    virtual ~CsaScheme();
    CsaScheme(): m_rpDatabase(NULL){}
    virtual QVariant getDetailedVariant();


public slots:
    QString getName();
    int getVersion();
};

#endif //
