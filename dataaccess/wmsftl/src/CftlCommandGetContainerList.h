#ifndef CDBCOMMANDGETCONTAINERLIST_H
#define CDBCOMMANDGETCONTAINERLIST_H

// Own Includes
#include "CftlAbstractCommand.h"

class CftlCommandGetContainerList : public CftlAbstractCommand
{
private:
    long m_lSchemeId;
    long m_lClassId;
    QMap<long, QString> m_qmContainer;
public:
    CftlCommandGetContainerList(long p_lSchemeId, long p_lClassId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetContainerList();
    void GetResult(QMap<long, QString>& p_rqmContainerList);

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCONTAINERLIST_H
