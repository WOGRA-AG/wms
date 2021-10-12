// WMS Includes
#include "CdmScheme.h"
#include "CdmRights.h"

// Own Includes
#include "CwnCommandFindScheme.h"

#include <QCryptographicHash>

#include "CwnCommandStdHeader.h"

CwnCommandFindScheme::CwnCommandFindScheme(QString p_qstrSchemeName, CwnDataAccess* p_pDataAccess)
  :CwnCommandBase(p_pDataAccess),
  m_qstrSchemeName(p_qstrSchemeName),
  m_pScheme(nullptr)
{
}

CwnCommandFindScheme::CwnCommandFindScheme(qint64 p_lId, CwnDataAccess *p_pDataAccess)
:CwnCommandBase(p_pDataAccess),
  m_lSchemeId(p_lId),
  m_pScheme(nullptr)
{
}

CwnCommandFindScheme::~CwnCommandFindScheme()
{

}

bool CwnCommandFindScheme::CheckValid()
{
    return !m_qstrSchemeName.isEmpty();
}

QString CwnCommandFindScheme::createQuery()
{
    QString query;

    if (!m_qstrSchemeName.isEmpty())
    {
        query = QString("MATCH (s:Scheme) WHERE s.schemename = \'%1\' OPTIONAL MATCH (p:WMS_LANGUAGES)<-[:languages]-(s) RETURN id(s),s,id(p),p.language;")
            .arg(m_qstrSchemeName);

    }
    else
    {
        query = QString("MATCH (s:Scheme) WHERE id(s)=%1 OPTIONAL MATCH (p:WMS_LANGUAGES)<-[:languages]-(s) RETURN id(s),s,id(p),p.language;")
                .arg(m_lSchemeId);
    }

    return query;
}

int CwnCommandFindScheme::Execute()
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

void CwnCommandFindScheme::interpretAnswer(QVariant &Ret)
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
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            // Value in col 0 is DataBaseId
            // Value in col 1 is DataBaseName
            // Value in col 2 is Version


           qint64 lDBId = list->at(0).toInt();

            const QVariantMap* rowMap = static_cast<const QVariantMap*>(list->at(1).data());

            // this is just for test if the correct one was found
            QString qstrKeyname = rowMap->find("schemename")->toString();
            int iVersion = rowMap->find("version")->toInt();

            m_pScheme = new CdmScheme(lDBId, qstrKeyname, iVersion);

            QVariantList::const_iterator it;

            for(it=dataList->begin();it!=dataList->end();++it)
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
                const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());
                if(row->at(2).toInt() != 0)
                {
                    int iLanguageId = row->at(2).toInt();
                    QString qstrName = row->at(3).toString();
                    m_pScheme->AddLanguage(iLanguageId, qstrName);
                }
            }

            if(!CHKPTR(m_pScheme))
            {
                Ret = EC(eDmMemoryAllocationError);
                ERR("Memory Allocation Error (could not initialize new object)");
            }
            else
            {
                Ret = GetDataAccess()->LoadRights(m_pScheme->GetRights(),
                                                  m_pScheme->GetId(),
                                                  "Scheme",
                                                  "DatabaseId");
            }
        }
        else
        {
            Ret = EC(eDmFalse);
            ERR("No Scheme found by keyname.");
            ERR(createQuery());
        }
    }
}

CdmScheme* CwnCommandFindScheme::GetResult()
{
    return m_pScheme;
}
