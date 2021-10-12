#ifndef CDBCOMMANDCHECKOBJECTUSED_H
#define CDBCOMMANDCHECKOBJECTUSED_H

#include "CdbAbstractCommand.h"

class CdbCommandCheckObjectUsed : public CdbAbstractCommand
{
private:
   qint64 m_lObjectId;
   qint64 m_lContainerId;
public:
    CdbCommandCheckObjectUsed(qint64 p_lObjectId,qint64 p_lContainerId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCheckObjectUsed();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKOBJECTUSED_H
