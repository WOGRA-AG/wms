#ifndef CDBCOMMANDGETCONTAINERLIST_H
#define CDBCOMMANDGETCONTAINERLIST_H

// Own Includes
#include "CdbAbstractCommand.h"

class CdbCommandGetContainerList : public CdbAbstractCommand
{
private:
    long m_lSchemeId;
    long m_lClassId;
    QMap<long, QString> m_qmContainer;
    QList<long> GetClassList();
    QString GetClassListString();
public:
    CdbCommandGetContainerList(long p_lSchemeId, long p_lClassId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetContainerList();
    void GetResult(QMap<long, QString>& p_rqmContainerList);

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCONTAINERLIST_H
