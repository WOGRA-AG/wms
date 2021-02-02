#include "CwnCommandLoadGroupTranslations.h"
#include "CdmSessionManager.h"
#include "CdmClassGroup.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"

#include "CwnCommandStdHeader.h"

CwnCommandLoadGroupTranslations::CwnCommandLoadGroupTranslations(CwnDataAccess* m_rpDataAccess, CdmClassGroup* group)
: CwnCommandBase(m_rpDataAccess),
  g(group)

{

}

CwnCommandLoadGroupTranslations::~CwnCommandLoadGroupTranslations()
{

}

QString CwnCommandLoadGroupTranslations::createQuery()
{
    QString query = QString("MATCH (w:WMS_CLASS_GROUP)-[r:WMS_ClassGroup_Translation]->(t:WMS_LANGUAGES) WHERE id(w)=%1 RETURN r.caption,t.language")
                    .arg(g->GetId());
    return query;
}

void CwnCommandLoadGroupTranslations::interpretAnswer(QVariant &Ret)
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
                const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                QString qstrCaption = list->at(0).toString();
                QString qstrLanguage = list->at(1).toString();

                CdmScheme* pScheme = CdmSessionManager::GetDataProvider()->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    g->SetTranslation(qstrLanguage, qstrCaption);
                }
            }

            Ret = EC(eDmTrue);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("No GroupTranslations found.");
        }
    }
}

int CwnCommandLoadGroupTranslations::Execute()
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

bool CwnCommandLoadGroupTranslations::CheckValid()
{
    bool bRet = true;

    if (true)
    {
        bRet = false;
    }

    return bRet;
}
