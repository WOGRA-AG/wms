#ifndef CSCRIPTMANAGER
#define CSCRIPTMANAGER

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CdmDataProvider;
class CsaFactory;

class WMSMANAGER_API CsaManager : public CsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;

public:
    CdmDataProvider* getInternals();

public slots:
    QString getWmsVersion();
    QString getWmsBuild();
    QString getApplicationVersion();
    QObject* getCurrentUser();
    int getSessionId();
    QObject *getUserByLogin(QString pLoginName);
    QObject *getUsergroupByName(QString pGroupName);
private:
    CdmDataProvider* m_rpManager;
    CsaManager(CdmDataProvider* p_pManager);
    virtual ~CsaManager();

    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();
    virtual QString getUri() const;
};

#endif //
