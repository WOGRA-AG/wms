#ifndef CFTLCONTAINERTABLESELECT_H
#define CFTLCONTAINERTABLESELECT_H


// Own Includes
#include "CftlContainerTableBase.h"

// Forwards
class CdmObjectContainer;



class CftlContainerTableSelect : public CftlContainerTableBase
{
private:
    CdmObjectContainer* m_rpContainer;
    QList<long> m_qlObjectIds;
    QList<QString> m_qlObjectKeynames;
    QMap<long, CdmMember*> m_qmMembers;
    QStringList m_qstrlLeftJoins;
    int m_iValueStartPos;

    QString GenerateFields(const CdmClass* p_pClass);
    QString GenerateInStringIds();
    void AddCommonFields(QString &qstrFields);
    QString GenerateInStringKeynames();
public:
    CftlContainerTableSelect(CdmObjectContainer* p_pContainer, CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableSelect();
    void SetObjectList(QList<long>& p_qlObjectIds);
    void SetObjectList(QList<QString>& p_qlObjectKeynames);
    int GetValueStartPos();

    QMap<long, CdmMember *> &GetMemberMap();
protected:
    virtual QStringList GenerateSqls();
    virtual bool IsValid();
};

#endif // CFTLCONTAINERTABLESELECT_H
