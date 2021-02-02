#ifndef CDBCOMMANDEXISTCONTAINER_H
#define CDBCOMMANDEXISTCONTAINER_H

// Own Includes
#include "CdbAbstractCommand.h"


class CdbCommandExistContainer : public CdbAbstractCommand
{
private:
      QString m_qstrContainerKeyname;
public:
    CdbCommandExistContainer(QString p_qstrContainer, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandExistContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDEXISTCONTAINER_H
