#ifndef CDBCOMMANDGETOBJECTREFERENCES_H
#define CDBCOMMANDGETOBJECTREFERENCES_H

#include "CftlAbstractCommand.h"

class CftlCommandGetObjectReferences : public CftlAbstractCommand
{
private:
   qint64 m_lContainerId;
   qint64 m_lObjectId;
    QMap<qint64,qint64> m_qmReferences;
public:
    CftlCommandGetObjectReferences(qint64 p_lContainerId,qint64 p_lObjectId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetObjectReferences();

    QMap<qint64,qint64> GetResult();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOBJECTREFERENCES_H
