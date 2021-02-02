#include "CwnCommandLoadTranslation.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmMember.h"
#include "CdmScheme.h"

#include "CwnCommandStdHeader.h"




CwnCommandLoadTranslation::CwnCommandLoadTranslation(CwnDataAccess* m_rpDataAccess, CdmMember* member)
: CwnCommandBase(m_rpDataAccess),
  m(member)

{

}

CwnCommandLoadTranslation::~CwnCommandLoadTranslation()
{

}

QString CwnCommandLoadTranslation::createQuery()
{
    //Language, Caption, Comment
    QString query = QString("MATCH (w:WMS_CLASS_MEMBER)-[r:WMS_ClassMember_Translation]->(l:WMS_LANGUAGES) WHERE id(w)=%1 RETURN r.Comment,r.Caption,l.language")
                    .arg(m->GetId());
    return query;
}

void CwnCommandLoadTranslation::interpretAnswer(QVariant &Ret)
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

                QString qstrCaption = list->at(1).toString();
                QString qstrLanguage = list->at(2).toString();
                QString qstrComment = list->at(0).toString();

                CdmScheme* pScheme = CdmSessionManager::GetDataProvider()->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    m->SetTranslation(qstrLanguage, qstrCaption, qstrComment);
                }
            }

            Ret = EC(eDmTrue);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("No Translation found.");
        }
    }
}

int CwnCommandLoadTranslation::Execute()
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

bool CwnCommandLoadTranslation::CheckValid()
{
    return true;
}

