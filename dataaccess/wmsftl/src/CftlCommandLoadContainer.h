#ifndef CDBCOMMANDLOADCONTAINER_H
#define CDBCOMMANDLOADCONTAINER_H

#include "CftlAbstractCommand.h"

// Forwards
class CdmContainer;

class CftlCommandLoadContainer : public CftlAbstractCommand
{
private:
   qint64 m_lContainerId;
    bool m_bLoadObjects;
   qint64 m_lSchemeId;
    QString m_qstrKeyname;
    CdmObjectContainer* m_rpContainer;

   qint64 LoadContainerRights();
    void LoadObjects();
    void GenerateContainerQuery(QSqlQuery& p_rQuery);
public:
    CftlCommandLoadContainer(qint64 p_lContainerId, bool p_bLoadObjects, CftlDataAccess* p_pDataAccess);
    CftlCommandLoadContainer(qint64 p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadContainer();

    CdmObjectContainer *GetResult();
protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADCONTAINER_H
