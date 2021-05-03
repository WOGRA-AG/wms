// System and Qt Includes

// WMS Core Includes
#include "CumUserGroup.h"
#include "CwmsJson.h"

// Own Includes
#include "CwnCommandFindGroups.h"

CwnCommandFindGroups::CwnCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_qstrGroupName(p_qstrGroupName),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
}

CwnCommandFindGroups::~CwnCommandFindGroups()
{
    // NOTHING To DO
}

QList<CumUserGroup *> CwnCommandFindGroups::GetResult()
{
    return m_qllGroups;
}

QString CwnCommandFindGroups::createQuery()
{
    QString query = QString("MATCH(n:Group) WHERE n.groupnamen =~ \'.*%1.*\' RETURN id(n),n.groupname;")
            .arg(m_qstrGroupName);
    return query;
}

void CwnCommandFindGroups::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=EC(eDmInvalidSelectStatement);

    }
    else
    {
        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();

        if(dataListCon->count()>0)
        {
           QList<QVariant>::ConstIterator it;
           for(it=dataListCon->begin();it!=dataListCon->end();it++) // loading each class
           {
               const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
               const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                CumUserGroup* group = new CumUserGroup(row->at(0).toInt(), nullptr);
                group->SetGroupName(row->at(1).toString());

                m_qllGroups.append(group);
            }
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("There are no Groups in the Database.");
        }
    }}

int CwnCommandFindGroups::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit, payload, nullptr, nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandFindGroups::CheckValid()
{
    return !m_qstrGroupName.isEmpty();
}
