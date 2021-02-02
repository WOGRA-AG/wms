#include "CwnCommandExistContainer.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"


CwnCommandExistContainer::CwnCommandExistContainer(long p_lClassId, QString p_qstrContainer, CwnDataAccess* p_pDataAccess)
:CwnCommandBase(p_pDataAccess),
m_lClassId(p_lClassId),
m_qstrContainerKeyname(p_qstrContainer)
{

}

CwnCommandExistContainer::~CwnCommandExistContainer()
{

}

QString CwnCommandExistContainer::createQuery(){

    QString qstrQuery = QString("MATCH (w:WMS_DM_OBJECTLIST)<-[:hasObjectContainer]-(c:Class) WHERE w.Keyname=\'%1\' and id(c)=%2 RETURN id(w);")
                        .arg(CwnHelper::MaskString(m_qstrContainerKeyname))
                        .arg(m_lClassId);

    return qstrQuery;
}

void CwnCommandExistContainer::interpretAnswer(QVariant& Ret){

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
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();

        if(dataList->count()>0)
        {
            Ret = 1;
        }
        else
        {
            Ret = -1;
            ERR("No Container found.");
        }
    }
}

int CwnCommandExistContainer::Execute(){
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandExistContainer::CheckValid(){
    return (m_lClassId > 0 && !m_qstrContainerKeyname.isEmpty() && CHKPTR(GetDataAccess()));
}
