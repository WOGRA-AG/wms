
// System and QT Includes
#include <QCoreApplication>

// WMS Includes
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsErrorMessenger.h"


CwmsErrorMessenger::CwmsErrorMessenger()
    : m_iSeverity(eDmError | eDmFatal)
{
}

CwmsErrorMessenger::~CwmsErrorMessenger()
{

}

void CwmsErrorMessenger::AddError(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmError)
    {
        CdmMessageManager::critical(qApp->tr("Es ist ein Fehler aufgetreten"), p_Entry.GetEventText());
    }
}

void CwmsErrorMessenger::AddInfo(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmInfo)
    {
        CdmMessageManager::information(qApp->tr("Systeminformation"), p_Entry.GetEventText());
    }
}

void CwmsErrorMessenger::AddWarning(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmWarning)
    {
        CdmMessageManager::warning(qApp->tr("Warnungshinweis des Systems"), p_Entry.GetEventText());
    }
}

void CwmsErrorMessenger::AddFatal(CdmLogEntry &p_Entry)
{
    if (m_iSeverity & eDmFatal)
    {
        CdmMessageManager::critical(qApp->tr("Es ist ein schwerwiegender Fehler aufgetreten"), p_Entry.GetEventText());
    }
}

void CwmsErrorMessenger::AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode)
{
    Q_UNUSED(p_qdtTimeStamp);
    Q_UNUSED(p_iCode);
}

int CwmsErrorMessenger::GetSeverity() const
{
    return m_iSeverity;
}

void CwmsErrorMessenger::SetSeverity(int iSeverity)
{
    m_iSeverity = iSeverity;
}
