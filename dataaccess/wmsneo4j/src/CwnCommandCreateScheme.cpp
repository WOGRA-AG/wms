#include "CdmScheme.h"
#include "CwnCommandCreateScheme.h"

#include "CwnCommandStdHeader.h"


CwnCommandCreateScheme::CwnCommandCreateScheme(QString p_qstrSchemeName, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName),
      m_pScheme(nullptr)
{
}


CwnCommandCreateScheme::~CwnCommandCreateScheme()
{

}

QString CwnCommandCreateScheme::createQuery()
{
    QString query = QString("MERGE (s:Scheme { schemename : \'%1\'}) ON CREATE SET s={schemename : \'%1\', version: \'%2\'}, s.onCreate = true WITH s, EXISTS(s.onCreate) as onCreate REMOVE s.onCreate RETURN id(s),s.schemename,s.version,onCreate;")
                 .arg(m_qstrSchemeName)
                 .arg(1);
    return query;
}

bool CwnCommandCreateScheme::CheckValid()
{
    return (!m_qstrSchemeName.isEmpty());
}

int CwnCommandCreateScheme::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

void CwnCommandCreateScheme::interpretAnswer(QVariant &Ret)
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
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();

        const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
        const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());
        //qDebug() << rowList[1].toBool();
        if(list->at(3).toBool())
        {
            Ret = list->at(0);
            m_pScheme = new CdmScheme(list->at(0).toLongLong(), list->at(1).toString(), list->at(2).toInt());
            //qDebug() << rowList[0].toInt();
        }
        else
        {
            Ret = 0;
            ERR("The schemename is already in use.");
        }
    }
}

CdmScheme* CwnCommandCreateScheme::GetResult()
{
    return m_pScheme;
}
