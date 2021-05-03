#ifndef CWMSAPPSTOREDATA_H
#define CWMSAPPSTOREDATA_H

#include "basetools.h"

// Forwards
class CdmScheme;
class CdmObjectContainer;
class CdmObject;

class BASETOOLS_API CwmsAppStoreData
{
private:
    CdmScheme* m_rpCurrentScheme;

    CdmObjectContainer* LoadData();
    void ReadData(QVariantList &p_rqvlApps, QList<CdmObject *> &p_rqllObjects);
    void AddDataToVariant(QVariantList &p_rqvlApps, CdmObject *p_pObject);
    long AddAppScheme(CdmObjectContainer *p_pContainer, QVariantMap &p_rMap);
    bool DeleteAppScheme(CdmObjectContainer *p_pContainer, long p_lAppSchemeId);
public:
    void GetAppStoreData(QVariantList &p_rMap);
    long AddAppScheme(QVariantMap &p_rMap);
    bool DeleteAppScheme(long p_lAppSchemeId);
    CwmsAppStoreData();
    virtual ~CwmsAppStoreData();
};

#endif // CWMSAPPSTOREDATA_H
