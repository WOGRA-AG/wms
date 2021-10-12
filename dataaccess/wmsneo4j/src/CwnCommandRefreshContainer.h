#ifndef CWNCOMMANDREFRESHCONTAINER_H
#define CWNCOMMANDREFRESHCONTAINER_H


#include "CwnCommandBase.h"
#include "CdmObjectContainer.h"
#include "CwnDataAccess.h"

class CwnCommandRefreshContainer : public CwnCommandBase
{
private:
    QString payload;
    QDateTime qdtLastChange;
    CdmObjectContainer* m_rpContainer;
    QString GetObjectQuery();
    QString GetContainerQuery();
    QString GetRightsQuery();
    QList<qint64> qvlObjects;

    bool interpretAnswerForRefreshContainer(const QVariantList *dataList, QVariant &Ret);
    bool interpretAnswerForObjects(const QVariantList *dataList);
    bool interpretAnswerForRights(const QVariantList *dataList);

public:
    CwnCommandRefreshContainer(CdmObjectContainer* p_pContainer, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandRefreshContainer();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};


#endif // CWNCOMMANDREFRESHCONTAINER_H
