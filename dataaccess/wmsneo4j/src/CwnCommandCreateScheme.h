#ifndef CWNCOMMANDCREATESCHEME_H
#define CWNCOMMANDCREATESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"

// Forwards
class CwnDataAccess;
class CdmScheme;

class CwnCommandCreateScheme : public CwnCommandBase
{
private:
    QString m_qstrSchemeName;
    CdmScheme* m_pScheme;
    QString createQuery();
    QString queryCausedError;

public:
    CwnCommandCreateScheme(QString p_qstrSchemeName, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCreateScheme();

    CdmScheme *GetResult();
protected:
    virtual bool CheckValid();
    int Execute();
    void interpretAnswer(QVariant& Ret);
};

#endif // CWNCOMMANDCREATESCHEME_H
