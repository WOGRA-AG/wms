#ifndef CWNCOMMANDGETCONTAINERLIST_H
#define CWNCOMMANDGETCONTAINERLIST_H

#include "CwnCommandBase.h"

class CwnCommandGetContainerList : public CwnCommandBase
{

private:
   qint64 m_lSchemeId;
   qint64 m_lClassId;
    QMap<qint64, QString> m_qmContainer;
    QList<qint64> GetClassList();
    QString GetClassListString();
    QString GetContainerQuery();

public:
    CwnCommandGetContainerList(qint64 p_lSchemeId,qint64 p_lClassId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetContainerList();
    void GetResult(QMap<qint64, QString>& p_rqmContainerList);
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual bool CheckValid();
    virtual int Execute();
};


#endif // CWNCOMMANDGETCONTAINERLIST_H
