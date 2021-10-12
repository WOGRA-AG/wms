#ifndef CDBCOMMANDGETCONTAINERLIST_H
#define CDBCOMMANDGETCONTAINERLIST_H

// Own Includes
#include "CftlAbstractCommand.h"

class CftlCommandGetContainerList : public CftlAbstractCommand
{
private:
   qint64 m_lSchemeId;
   qint64 m_lClassId;
    QMap<qint64, QString> m_qmContainer;
public:
    CftlCommandGetContainerList(qint64 p_lSchemeId,qint64 p_lClassId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetContainerList();
    void GetResult(QMap<qint64, QString>& p_rqmContainerList);

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCONTAINERLIST_H
