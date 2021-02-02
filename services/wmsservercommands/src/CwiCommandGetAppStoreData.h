#ifndef CWICOMMANDGETAPPSTOREDATA_H
#define CWICOMMANDGETAPPSTOREDATA_H


// own include
#include "IwiCommand.h"

class CwiCommandGetAppStoreData : public IwiCommand
{
private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetAppStoreData(CwmscomData* p_pData);
    virtual ~CwiCommandGetAppStoreData();
    virtual void Execute();
};

#endif // CWICOMMANDGETAPPSTOREDATA_H
