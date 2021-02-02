#ifndef CWICOMMANDGETSERVERSETTINGS_H
#define CWICOMMANDGETSERVERSETTINGS_H

// System and Qt Includes

// own Includes
#include "IwiCommand.h"


class CwiCommandGetServerSettings : public IwiCommand
{
private:
    CwmscomData* m_rpData;
public:
    CwiCommandGetServerSettings(CwmscomData* p_pData);
    virtual ~CwiCommandGetServerSettings();
    virtual void Execute();
};

#endif // CWICOMMANDGETSERVERSETTINGS_H
