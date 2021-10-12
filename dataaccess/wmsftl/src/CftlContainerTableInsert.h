#ifndef CFTLCONTAINERTABLEINSERT_H
#define CFTLCONTAINERTABLEINSERT_H


// Own Includes
#include "CftlContainerTableBase.h"

// Forwards
class CdmObject;


class CftlContainerTableInsert : public CftlContainerTableBase
{
private:
    CdmObject* m_rpObject;
    QString m_qstrFields;
    QString m_qstrFieldPlaceholders;
   qint64 m_lObjectId;
    QVariantMap m_qvmFieldValues;
    void BuildFieldValuesForInsert(const CdmClass* p_pClass, CftlInterface *p_pInterface);
    void AddObjectProperties(QString p_qstrFieldName, QVariant p_qvValue);
    void ReadCreatedObjectId(CftlInterface *p_pInterface, QString p_qstrClassTableName);
public:
    CftlContainerTableInsert(CdmObject* p_Object, CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableInsert();
    virtual qint64 Execute(CftlInterface* p_pInterface);

   qint64 GetCreatedObjectId();
protected:
    virtual QStringList GenerateSqls();
    virtual bool IsValid();
};

#endif // CFTLCONTAINERTABLEINSERT_H
