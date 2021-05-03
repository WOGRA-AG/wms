#ifndef CWNCOMMANDLOADCONTAINER_H
#define CWNCOMMANDLOADCONTAINER_H

#include "CwnCommandBase.h"
#include "CdmObjectContainer.h"


// Forwards
class CdmContainer;

class CwnCommandLoadContainer : public CwnCommandBase
{

private:
    QString payload;
    long m_lContainerId;
    bool m_bLoadObjects;
    long m_lSchemeId;
    QString m_qstrKeyname;
    CdmObjectContainer* m_rpContainer;
    QList<long> qvlObjects;

    bool interpretAnswerForContainerLoad(const QVariantList *dataList);
    bool interpretAnswerForObjects(const QVariantList *dataList);
    bool interpretAnswerForRights(const QVariantList *dataList);

    QString GetRightsQuery();
    QString GetObjectQuery();
    QString GetContainerQuery();

public:
    CwnCommandLoadContainer(long p_lContainerId, bool p_bLoadObjects, CwnDataAccess* p_pDataAccess);
    CwnCommandLoadContainer(long p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandLoadContainer();

    CdmObjectContainer *GetResult();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};
#endif // CWNCOMMANDLOADCONTAINER_H
