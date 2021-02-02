#ifndef CDBCOMMANDFINDSCHEME_H
#define CDBCOMMANDFINDSCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;
class CdmScheme;

class CdbCommandFindScheme : public CdbAbstractCommand
{
private:
    QString m_qstrSchemeName;
    long m_lSchemeId;
    CdmScheme* m_pScheme;

    void LoadLanguages();
public:
    CdbCommandFindScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess);
    CdbCommandFindScheme(long p_lId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandFindScheme();

    CdmScheme *GetResult();
protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDFINDSCHEME_H
