#ifndef CDBCOMMANDLOADCONTAINER_H
#define CDBCOMMANDLOADCONTAINER_H

#include "CdbAbstractCommand.h"

// Forwards
class CdmContainer;

class CdbCommandLoadContainer : public CdbAbstractCommand
{
private:
   qint64 m_lContainerId;
    bool m_bLoadObjects;
   qint64 m_lSchemeId;
    QString m_qstrKeyname;
    CdmObjectContainer* m_rpContainer;

   qint64 LoadObjectListRights();
    void LoadObjects();
    QString GetObjectQuery();
    QString GetContainerQuery();
public:
    CdbCommandLoadContainer(qint64 p_lContainerId, bool p_bLoadObjects, CdbDataAccess* p_pDataAccess);
    CdbCommandLoadContainer(qint64 p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadContainer();

    CdmObjectContainer *GetResult();
protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADCONTAINER_H
