#ifndef CDBCOMMANDGETCONTAINERLIST_H
#define CDBCOMMANDGETCONTAINERLIST_H

// Own Includes
#include "CdbAbstractCommand.h"

class CdbCommandGetContainerList : public CdbAbstractCommand
{
private:
   qint64 m_lSchemeId;
   qint64 m_lClassId;
    QMap<qint64, QString> m_qmContainer;
    QList<qint64> GetClassList();
    QString GetClassListString();
public:
    CdbCommandGetContainerList(qint64 p_lSchemeId,qint64 p_lClassId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetContainerList();
    void GetResult(QMap<qint64, QString>& p_rqmContainerList);

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCONTAINERLIST_H
