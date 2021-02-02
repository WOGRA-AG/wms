#ifndef CDBCOMMANDEXISTCONTAINER_H
#define CDBCOMMANDEXISTCONTAINER_H

// Own Includes
#include "CftlAbstractCommand.h"


class CftlCommandExistContainer : public CftlAbstractCommand
{
private:
      QString m_qstrContainerKeyname;
public:
    CftlCommandExistContainer(QString p_qstrContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandExistContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDEXISTCONTAINER_H
