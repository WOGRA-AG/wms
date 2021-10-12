#ifndef CWNCOMMANDDELETEOBJECT_H
#define CWNCOMMANDDELETEOBJECT_H

// Own Includes
#include "CwnCommandBase.h"


class CwnCommandDeleteObject : public CwnCommandBase
{
private:
   qint64 m_lObjectId;
   qint64 m_lSessionId;

public:
    CwnCommandDeleteObject(qint64 p_lObjectId,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandDeleteObject();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEOBJECT_H
