#ifndef CWMSOBJECTLOCKER_H
#define CWMSOBJECTLOCKER_H


// Own Includes
#include "basetools.h"

class BASETOOLS_API CwmsObjectLocker
{
private:
    CdmObjectAdaptor m_cAdaptor;
public:
    CwmsObjectLocker();
    CwmsObjectLocker(CdmObject *p_PObject);
    ~CwmsObjectLocker();
    int LockObject(CdmObject *p_pObject);
    int UnlockObject();
};

#endif // CWMSOBJECTLOCKER_H
