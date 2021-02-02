#ifndef CDBCOMMANDFINDSCHEME_H
#define CDBCOMMANDFINDSCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;
class CdmScheme;

class CftlCommandFindScheme : public CftlAbstractCommand
{
private:
    QString m_qstrSchemeName;
    long m_lSchemeId;
    CdmScheme* m_pScheme;

    void LoadLanguages();
public:
    CftlCommandFindScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess);
    CftlCommandFindScheme(long m_lSchemeId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandFindScheme();

    CdmScheme *GetResult();
protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDFINDSCHEME_H
