#ifndef CFTLCONTAINERTABLEBASE_H
#define CFTLCONTAINERTABLEBASE_H

#include <QSqlQuery>

class CftlDialect;
class CftlInterface;
class CftlContainerTableBase
{
private:
    CftlDialect* m_rpDialect;
    QSqlQuery m_qsqlQuery;


public:
    CftlContainerTableBase(CftlDialect* p_ppDialect);
    virtual ~CftlContainerTableBase();
    CftlDialect* GetDialect();
    virtual qint64 Execute(CftlInterface* p_pInterface);
    QSqlQuery& GetQuery();
protected:
    bool CheckValid();
    virtual QStringList GenerateSqls() = 0;
    virtual bool IsValid() = 0;
};

#endif // CFTLCONTAINERTABLEBASE_H
