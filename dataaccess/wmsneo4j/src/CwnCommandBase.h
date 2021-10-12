#ifndef CWNCOMMANDBASE_H
#define CWNCOMMANDBASE_H

#include "wmsneo4j.h"
#include "IwnCommand.h"
#include <QByteArray>
#include <QString>
#include <QVariant>

#include "CwnCommandBase.h"

// forward
class CwnDataAccess;
class CwnDataAccessConfigurator;

class WMSNEO4J_API CwnCommandBase : public IwnCommand
{
private:
    CwnDataAccess* m_rpDataAccess;
    bool Validate();

public:
    CwnCommandBase(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandBase();
   qint64 Run();

protected:
    enum exe_type {executeCommit=1, traverseDepthSearchFullPath=2, openTransaction=3, rollbackTransaction=4, commitTransaction=5};
    QString location;
    QByteArray answer;
    const QVariantMap* qResult;
    const QVariantList* qResultList;
    bool CheckSession();
    void ConnectAndExecute(int role, QString payload, QString location, QString startNode);
    QString createJson(QString p_qstrQuery);
    QString startJsonWCommand(QString p_qstrQuery);
    QString addJsonCommand(QString p_qstrQuery);
    QString endJsonCommand();
    virtual void interpretAnswer(QVariant& Ret)=0;
    virtual const QVariantList *getDataListPtr();
    virtual const QVariantList *getErrorsList();
    virtual bool checkForErrors(const QVariantMap *qresult, QString &queryCausedError);
    CwnDataAccess *GetDataAccess();

    bool hasErrors();
};

#endif // CWNCOMMANDBASE_H
