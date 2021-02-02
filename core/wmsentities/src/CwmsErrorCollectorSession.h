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

#ifndef CWMSERRORCOLLECTORSESSION_H
#define CWMSERRORCOLLECTORSESSION_H

// System and QT Includes


// own Includes
#include "CwmsErrorCollector.h"
#include "basetools.h"


class BASETOOLS_API CwmsErrorCollectorSession : public CwmsErrorCollector
{
private:
    int m_iSessionId;
public:
    CwmsErrorCollectorSession(int p_iSessionId);
    virtual ~CwmsErrorCollectorSession();
    virtual void AddError(CdmLogEntry& p_Entry);
    virtual void AddInfo(CdmLogEntry& p_Entry);
    virtual void AddWarning(CdmLogEntry& p_Entry);
    virtual void AddFatal(CdmLogEntry& p_Entry);
    int GetSessionId() const;
};

#endif // // CWMSERRORCOLLECTORSESSION_H
