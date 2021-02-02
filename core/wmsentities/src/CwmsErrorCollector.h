/*****************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsErrorCollector
 ** Started Implementation: 21.11.13
 ** Description:
 ** Implements a collector for erros
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/

#ifndef CWMSERRORCOLLECTOR_H
#define CWMSERRORCOLLECTOR_H

// System and QT Includes
#include <QList>

// own includes
#include "CdmLogEntry.h"
#include "CdmLoggingAdaptor.h"
#include "basetools.h"

// forwards

class BASETOOLS_API CwmsErrorCollector : public CdmLoggingAdaptor
{
private:
    QList<CdmLogEntry> m_qlCollectedEntries;
    int m_iSeverity;

    void FillEntries(QList<CdmLogEntry>& p_qlList, EdmErrorSeverity p_eSeverity) const;
public:
    CwmsErrorCollector();
    virtual ~CwmsErrorCollector();
    int GetEntryCount() const;
    int GetSeverity() const;
    bool HasEntries() const;
    void SetSeverity(int iSeverity);
    QVariant ToJson() const;
    QString ToString() const;
    QString GetDisplayString() const;
    virtual void AddError(CdmLogEntry& p_Entry);
    virtual void AddInfo(CdmLogEntry& p_Entry);
    virtual void AddWarning(CdmLogEntry& p_Entry);
    virtual void AddFatal(CdmLogEntry& p_Entry);
    virtual void AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode);
    QList<CdmLogEntry> GetCollectedEntries() const;
    QList<CdmLogEntry> GetInformationEntries() const;
    QList<CdmLogEntry> GetWarningEntries() const;
    QList<CdmLogEntry> GetErrorEntries() const;
    QList<CdmLogEntry> GetFatalEntries() const;


};

#endif // // CWMSERRORCOLLECTOR_H
