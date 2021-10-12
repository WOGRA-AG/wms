#ifndef CFTLCONTAINERTABLEUPDATE_H
#define CFTLCONTAINERTABLEUPDATE_H

#include <QVariantMap>

#include "CftlContainerTableBase.h"

// Forwards
class CdmObject;


class CftlContainerTableUpdate : public CftlContainerTableBase
{
private:
    CdmObject* m_rpObject;
    QString m_qstrSetArea;
    QVariantMap m_qvValueBindings;

    void BuildFieldValuesForUpdate(CftlInterface *p_pInterface);
    QString BuildWhereCondition();
    void AddUpdateValue(CdmValue *p_pValue, CftlInterface *p_pInterface);
    void AddModifierFields();
public:
    CftlContainerTableUpdate(CdmObject* p_Object, CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableUpdate();
    virtual qint64 Execute(CftlInterface* p_pInterface);

protected:
    virtual QStringList GenerateSqls();
    virtual bool IsValid();
};

#endif // CFTLCONTAINERTABLEUPDATE_H
