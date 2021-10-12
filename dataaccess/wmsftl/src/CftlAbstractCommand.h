#ifndef CDBABSTRACTCOMMAND_H
#define CDBABSTRACTCOMMAND_H

// System and Qt Includes

// WMS Includes
#include "CumAccessor.h"
#include "CdmLogging.h"

// own Includes
#include "IftlCommand.h"
#include "CftlDialect.h"

// Forwards
class CftlDataAccess;



class CftlAbstractCommand : public IftlCommand
{
private:
    CftlDataAccess* m_rpDataAccess;
    void UpdateSession();

public:
    CftlAbstractCommand(CftlDataAccess* p_pDataAccess);
    virtual ~CftlAbstractCommand();
    virtual int Run();

protected:
    bool Validate();
   qint64 ExecuteQuery(QString p_qstrQuery, QSqlQuery &p_rqsqlQuery);
    CftlDataAccess *GetDataAccess();
   qint64 ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    CftlDialect* GetDialect();
    CftlInterface* GetInterface();
    virtual const CdmClass *GetClassFromContainerId(qint64 p_lId);
    QString GetClassTableNameFromContainerId(qint64 p_lId);
    QSqlDatabase GetSqlDatabase();
    QString GetClassTableNameFromObject(const CdmObject *p_pObject);
    QString GetClassTableNameFromContainer(const CdmObjectContainer *p_pContainer);
    int InsertInAccessorTable(EumUserGroupType p_eType);
    int SessionCheck();
    virtual bool NeedsSessionCheck();
};

#endif // CDBABSTRACTCOMMAND_H
