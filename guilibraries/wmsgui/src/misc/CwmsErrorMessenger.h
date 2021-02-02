#ifndef CWMSERRORMESSENGER_H
#define CWMSERRORMESSENGER_H

// System and QT Includes


// WMS Includes
#include "CdmLoggingAdaptor.h"
#include "CdmLogEntry.h"

// own Includes
#include "wmsgui.h"

// forwards

class WMSGUI_API CwmsErrorMessenger : public CdmLoggingAdaptor
{
private:
        int m_iSeverity;
public:
    CwmsErrorMessenger();
    virtual ~CwmsErrorMessenger();

    virtual void AddError(CdmLogEntry& p_Entry);
    virtual void AddInfo(CdmLogEntry& p_Entry);
    virtual void AddWarning(CdmLogEntry& p_Entry);
    virtual void AddFatal(CdmLogEntry& p_Entry);
    virtual void AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode);


    int GetSeverity() const;
    void SetSeverity(int iSeverity);
};

#endif // // CWMSERRORMESSENGER_H
