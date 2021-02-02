#ifndef CDBCOMMANDLOADCONTAINER_H
#define CDBCOMMANDLOADCONTAINER_H

#include "CftlAbstractCommand.h"

// Forwards
class CdmContainer;

class CftlCommandLoadContainer : public CftlAbstractCommand
{
private:
    long m_lContainerId;
    bool m_bLoadObjects;
    long m_lSchemeId;
    QString m_qstrKeyname;
    CdmObjectContainer* m_rpContainer;

    long LoadContainerRights();
    void LoadObjects();
    void GenerateContainerQuery(QSqlQuery& p_rQuery);
public:
    CftlCommandLoadContainer(long p_lContainerId, bool p_bLoadObjects, CftlDataAccess* p_pDataAccess);
    CftlCommandLoadContainer(long p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadContainer();

    CdmObjectContainer *GetResult();
protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADCONTAINER_H
