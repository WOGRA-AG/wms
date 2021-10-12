#ifndef CDBCOMMANDGETOBJECTREFERENCES_H
#define CDBCOMMANDGETOBJECTREFERENCES_H

#include "CdbAbstractCommand.h"

class CdbCommandGetObjectReferences : public CdbAbstractCommand
{
private:
   qint64 m_lContainerId;
   qint64 m_lObjectId;
    QMap<qint64,qint64> m_qmReferences;
public:
    CdbCommandGetObjectReferences(qint64 p_lContainerId,qint64 p_lObjectId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetObjectReferences();

    QMap<qint64,qint64> GetResult();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOBJECTREFERENCES_H
