#ifndef CWNCOMMANDGETCONTAINERLIST_H
#define CWNCOMMANDGETCONTAINERLIST_H

#include "CwnCommandBase.h"

class CwnCommandGetContainerList : public CwnCommandBase
{

private:
    long m_lSchemeId;
    long m_lClassId;
    QMap<long, QString> m_qmContainer;
    QList<long> GetClassList();
    QString GetClassListString();
    QString GetContainerQuery();

public:
    CwnCommandGetContainerList(long p_lSchemeId, long p_lClassId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetContainerList();
    void GetResult(QMap<long, QString>& p_rqmContainerList);
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual bool CheckValid();
    virtual int Execute();
};


#endif // CWNCOMMANDGETCONTAINERLIST_H
