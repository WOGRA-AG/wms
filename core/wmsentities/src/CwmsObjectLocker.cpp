#include "CwmsObjectLocker.h"

CwmsObjectLocker::CwmsObjectLocker()
{

}

CwmsObjectLocker::CwmsObjectLocker(CdmObject* p_pObject)
{
    LockObject(p_pObject);
}

CwmsObjectLocker::~CwmsObjectLocker()
{
    UnlockObject();
}


int CwmsObjectLocker::LockObject(CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        m_cAdaptor.SetObject(p_pObject);
        return p_pObject->LockObjectOnDb();
    }

    return EC(eDmInvalidPtr);
}

int CwmsObjectLocker::UnlockObject()
{
    auto pObject = m_cAdaptor.GetObject();

    if (pObject)
    {
        return pObject->UnlockObjectOnDb();
    }

    return EC(eDmInvalidPtr);
}
