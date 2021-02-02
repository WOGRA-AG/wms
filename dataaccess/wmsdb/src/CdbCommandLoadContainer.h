#ifndef CDBCOMMANDLOADCONTAINER_H
#define CDBCOMMANDLOADCONTAINER_H

#include "CdbAbstractCommand.h"

// Forwards
class CdmContainer;

class CdbCommandLoadContainer : public CdbAbstractCommand
{
private:
    long m_lContainerId;
    bool m_bLoadObjects;
    long m_lSchemeId;
    QString m_qstrKeyname;
    CdmObjectContainer* m_rpContainer;

    long LoadObjectListRights();
    void LoadObjects();
    QString GetObjectQuery();
    QString GetContainerQuery();
public:
    CdbCommandLoadContainer(long p_lContainerId, bool p_bLoadObjects, CdbDataAccess* p_pDataAccess);
    CdbCommandLoadContainer(long p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadContainer();

    CdmObjectContainer *GetResult();
protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADCONTAINER_H
