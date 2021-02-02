#ifndef CDBCOMMANDCREATESCHEME_H
#define CDBCOMMANDCREATESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;
class CdmScheme;

class CftlCommandCreateScheme : public CftlAbstractTransactionalCommand
{
private:
    QString m_qstrSchemeName;
    CdmScheme* m_pScheme;

public:
    CftlCommandCreateScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCreateScheme();

    CdmScheme *GetResult();
protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCREATESCHEME_H
