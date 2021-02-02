#include "CwnCommandGetSchemeList.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetSchemeList::CwnCommandGetSchemeList(CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess)
{
    // Start Transaction
}

CwnCommandGetSchemeList::~CwnCommandGetSchemeList()
{

}

QLinkedList<QString> CwnCommandGetSchemeList::GetSchemes() const
{
    return m_qllSchemes;
}


QString CwnCommandGetSchemeList::createQuery()
{
    QString query = QString("MATCH(n:Scheme) RETURN id(n),n.schemename;");
    return query;
}

void CwnCommandGetSchemeList::interpretAnswer(QVariant &Ret)
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

               QString qstrDatabaseName = row->at(1).toString();
               m_qllSchemes.append(qstrDatabaseName);
            }
            Ret = EC(eDmTrue);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("There are no Schemes in the Database.");
        }
    }
}

int CwnCommandGetSchemeList::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandGetSchemeList::CheckValid()
{
    return true;
}
