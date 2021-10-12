#ifndef CWNCOMMANDFINDSCHEME_H
#define CWNCOMMANDFINDSCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"

// Forwards
class CdbDataAccess;
class CdmScheme;


class CwnCommandFindScheme : public CwnCommandBase
{

private:
    QString m_qstrSchemeName;
   qint64 m_lSchemeId;
    CdmScheme* m_pScheme;


public:
    CwnCommandFindScheme(QString p_qstrSchemeName, CwnDataAccess* p_pDataAccess);
    CwnCommandFindScheme(qint64 p_lId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandFindScheme();

    CdmScheme *GetResult();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDFINDSCHEME_H
