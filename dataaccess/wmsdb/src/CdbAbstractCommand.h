#ifndef CDBABSTRACTCOMMAND_H
#define CDBABSTRACTCOMMAND_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "IdbCommand.h"

// Forwards
class CdbDataAccess;


class CdbAbstractCommand : public IdbCommand
{
private:
    CdbDataAccess* m_rpDataAccess;
    QMutex m_qMutex;


    void UpdateSession();
public:
    CdbAbstractCommand(CdbDataAccess* p_pDataAccess);
    virtual ~CdbAbstractCommand();
    virtual int Run();
protected:
    bool Validate();
    CdbInterface *GetInterface();
    int SessionCheck();
   qint64 ExecuteQuery(QString p_qstrQuery, QSqlQuery &p_rqsqlQuery);
    CdbDataAccess *GetDataAccess();
    virtual bool NeedsActiveSession();
   qint64 ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    QSqlDatabase GetSqlDatabase();
};

#endif // CDBABSTRACTCOMMAND_H
