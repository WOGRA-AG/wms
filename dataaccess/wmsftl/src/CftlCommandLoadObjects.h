#ifndef CDBCOMMANDLOADOBJECTS_H
#define CDBCOMMANDLOADOBJECTS_H

// System and Qt Includes
#include <QList>

// Own Includes
#include "CftlAbstractCommand.h"
#include "CftlContainerTableSelect.h"

// Forwards
class CdmValueCharacterDocument;
class CdmObjectContainer;

class CftlCommandLoadObjects : public CftlAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
    QList<qint64> m_qvlObjectIds;
    QList<QString> m_qvlObjectKeynames;

public:
    CftlCommandLoadObjects(CdmObjectContainer* p_pContainer, QList<qint64>& p_qlObjectIds, CftlDataAccess* p_pDataAccess);
    CftlCommandLoadObjects(CdmObjectContainer* p_pContainer, QList<QString>& p_qlObjectKeynames, CftlDataAccess* p_pDataAccess);
    CftlCommandLoadObjects(CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadObjects();


protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDLOADOBJECTS_H
