#ifndef CWNCOMMANDLOADCLASSMANAGER_H
#define CWNCOMMANDLOADCLASSMANAGER_H

#include "CwnCommandBase.h"

class CwnCommandLoadClassManager : public CwnCommandBase
{
private:
   qint64 m_lSchemeId;
    CdmClassManager* m_pClassManager;


public:
    CwnCommandLoadClassManager(qint64 p_lSchemeId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandLoadClassManager();
    CdmClassManager* GetResult();
    QString createQuery();
    QString queryCausedError;

protected:
    virtual int Execute();
    virtual bool CheckValid();
    void interpretAnswer(QVariant& Ret);
};

#endif // CWNCOMMANDLOADCLASSMANAGER_H
