#ifndef CWNCOMMANDEXISTCONTAINER_H
#define CWNCOMMANDEXISTCONTAINER_H

#include "CwnDataAccess.h"
#include "CwnCommandBase.h"

class CwnCommandExistContainer: public CwnCommandBase
{
private:
     qint64 m_lClassId;
      QString m_qstrContainerKeyname;

public:
    CwnCommandExistContainer(qint64 p_lClassId, QString p_qstrContainer, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandExistContainer();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDEXISTCONTAINER_H
