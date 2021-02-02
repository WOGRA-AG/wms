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

// System and QT Includes
#include <QCoreApplication>

// own Includes
#include "CwmsErrorCollector.h"


CwmsErrorCollector::CwmsErrorCollector()
: m_iSeverity(eDmError | eDmFatal)
{
}

CwmsErrorCollector::~CwmsErrorCollector()
{

}

int CwmsErrorCollector::GetEntryCount() const
{
    return m_qlCollectedEntries.count();
}

bool CwmsErrorCollector::HasEntries() const
{
    return (GetEntryCount() > 0);
}

void CwmsErrorCollector::AddError(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmError)
    {
        m_qlCollectedEntries.append(p_Entry);
    }
}

void CwmsErrorCollector::AddInfo(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmInfo)
    {
        m_qlCollectedEntries.append(p_Entry);
    }
}

void CwmsErrorCollector::AddWarning(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmWarning)
    {
        m_qlCollectedEntries.append(p_Entry);
    }
}

void CwmsErrorCollector::AddFatal(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmFatal)
    {
        m_qlCollectedEntries.append(p_Entry);
    }
}

void CwmsErrorCollector::AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode)
{
    Q_UNUSED(p_qdtTimeStamp);
    Q_UNUSED(p_iCode);
}

int CwmsErrorCollector::GetSeverity() const
{
    return m_iSeverity;
}

void CwmsErrorCollector::SetSeverity(int iSeverity)
{
    m_iSeverity = iSeverity;
}

QVariant CwmsErrorCollector::ToJson() const
{
    QVariantMap qvmErrorInfo;
    QVariantList qvlErrors;
    int iErrors = 0;
    int iWarnings = 0;
    int iInfos = 0;
    int iFatals = 0;
    qvmErrorInfo.insert("EntriesCount", GetEntryCount());
    qvmErrorInfo.insert("HasEntries", HasEntries());


    for(int iCounter = 0; iCounter < m_qlCollectedEntries.count(); ++iCounter)
    {
        qvlErrors.append(m_qlCollectedEntries[iCounter].toJson());
        EdmErrorSeverity eSeverity = m_qlCollectedEntries[iCounter].GetErrorSeverity();

        switch (eSeverity)
        {
            case eDmInfo:
                ++iInfos;
                break;
            case eDmWarning:
                ++iWarnings;
                break;
            case eDmError:
                ++iErrors;
                break;
            case eDmFatal:
                ++iFatals;
                break;
            default:
                ++iFatals;
                break;
        }
    }

    if (iErrors == 0 && iFatals == 0)
    {
        qvmErrorInfo.insert("Success", true);
    }
    else
    {
        qvmErrorInfo.insert("Success", false);
    }

    qvmErrorInfo.insert("InfoCount", iInfos);
    qvmErrorInfo.insert("WarningCount", iWarnings);
    qvmErrorInfo.insert("ErrorCount", iErrors);
    qvmErrorInfo.insert("FatalCount", iFatals);
    qvmErrorInfo.insert("Entries", qvlErrors);

    return qvmErrorInfo;
}

QString CwmsErrorCollector::ToString() const
{
    QString qstrErrors;

    for(int iCounter = 0; iCounter < m_qlCollectedEntries.count(); ++iCounter)
    {
        qstrErrors += m_qlCollectedEntries[iCounter].ToString() + "\n";
    }

    return qstrErrors;
}

QString CwmsErrorCollector::GetDisplayString() const
{
    QString qstrRet;

    qstrRet += qApp->tr("Folgende Fehler sind aufgetreten:\n");

    for(int iCounter = 0; iCounter < m_qlCollectedEntries.count(); ++iCounter)
    {
        qstrRet += m_qlCollectedEntries[iCounter].GetEventText() + "\n";
    }


    return qstrRet;
}

QList<CdmLogEntry> CwmsErrorCollector::GetCollectedEntries() const
{
    return m_qlCollectedEntries;
}

QList<CdmLogEntry> CwmsErrorCollector::GetInformationEntries() const
{
    QList<CdmLogEntry> qlEntries;
    FillEntries(qlEntries, eDmInfo);
    return qlEntries;
}

QList<CdmLogEntry> CwmsErrorCollector::GetWarningEntries() const
{
    QList<CdmLogEntry> qlEntries;
    FillEntries(qlEntries, eDmWarning);
    return qlEntries;
}

QList<CdmLogEntry> CwmsErrorCollector::GetErrorEntries() const
{
    QList<CdmLogEntry> qlEntries;
    FillEntries(qlEntries, eDmError);
    return qlEntries;
}

QList<CdmLogEntry> CwmsErrorCollector::GetFatalEntries() const
{
    QList<CdmLogEntry> qlEntries;
    FillEntries(qlEntries, eDmFatal);
    return qlEntries;
}

void CwmsErrorCollector::FillEntries(QList<CdmLogEntry> &p_qlList,
                                     EdmErrorSeverity p_eSeverity) const
{
    for(int iCounter = 0; iCounter < m_qlCollectedEntries.count(); ++iCounter)
    {
        if (m_qlCollectedEntries[iCounter].GetErrorSeverity() == p_eSeverity)
        {
            p_qlList.append(m_qlCollectedEntries[iCounter]);
        }
    }
}

