/*****************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsErrorCollectorSession
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


// own Includes
#include "CwmsErrorCollectorSession.h"


CwmsErrorCollectorSession::CwmsErrorCollectorSession(int p_iSessionId)
: m_iSessionId(p_iSessionId)
  
{

}

CwmsErrorCollectorSession::~CwmsErrorCollectorSession()
{

}

void CwmsErrorCollectorSession::AddError(CdmLogEntry &p_Entry)
{
    if (p_Entry.GetSessionId() == m_iSessionId || m_iSessionId == 0)
    {
        CwmsErrorCollector::AddError(p_Entry);
    }
}

void CwmsErrorCollectorSession::AddInfo(CdmLogEntry &p_Entry)
{
    if (p_Entry.GetSessionId() == m_iSessionId || m_iSessionId == 0)
    {
        CwmsErrorCollector::AddInfo(p_Entry);
    }
}

void CwmsErrorCollectorSession::AddWarning(CdmLogEntry &p_Entry)
{
    if (p_Entry.GetSessionId() == m_iSessionId || m_iSessionId == 0)
    {
        CwmsErrorCollector::AddWarning(p_Entry);
    }
}

void CwmsErrorCollectorSession::AddFatal(CdmLogEntry &p_Entry)
{
    if (p_Entry.GetSessionId() == m_iSessionId || m_iSessionId == 0)
    {
        CwmsErrorCollector::AddFatal(p_Entry);
    }
}

int CwmsErrorCollectorSession::GetSessionId() const
{
    return m_iSessionId;
}
