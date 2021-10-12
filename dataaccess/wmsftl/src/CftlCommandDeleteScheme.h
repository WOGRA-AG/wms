#ifndef CDBCOMMANDDELETESCHEME_H
#define CDBCOMMANDDELETESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandDeleteScheme : public CftlAbstractTransactionalCommand
{
private:
    QString m_qstrSchemeName;

   qint64 GetSchemeId();
    void DeleteLanguages(qint64 p_lSchemeId);
    int DropClassTables(qint64 p_lSchemeId);
public:
    CftlCommandDeleteScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteScheme();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETESCHEME_H
