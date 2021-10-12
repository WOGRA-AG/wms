// WMS Includes
#include "CdmClassManager.h"

// Own Includes
#include "CwnCommandLoadClassManager.h"
#include "CwnCommandGetClass.h"
#include "CwnCommandGetClasses.h"
#include "CwnCommandLoadPackages.h"

#include "CumUser.h"
#include "CdmScheme.h"

#include <QList>

#include "CwnCommandStdHeader.h"

CwnCommandLoadClassManager::CwnCommandLoadClassManager(qint64 p_lSchemeId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_pClassManager(nullptr)
{
}

CwnCommandLoadClassManager::~CwnCommandLoadClassManager()
{

}

QString CwnCommandLoadClassManager::createQuery()
{
    QString query = QString("MATCH(s:Scheme)-[r:hasClass]->(c:Class) WHERE id(s)=%1 RETURN id(c);")
            .arg(m_lSchemeId);
    return query;
}

void CwnCommandLoadClassManager::interpretAnswer(QVariant &Ret)
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
        m_pClassManager = CdmDataAccessHelper::CreateClassManager(m_lSchemeId);
        Ret = CdmLogging::eDmUnknownClassAccessError;

        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();
        if(dataListCon->count()>0)
        {
            CwnCommandLoadPackages commandLoadPackages(m_pClassManager, GetDataAccess(), m_pClassManager->GetScheme()->GetSchemeName());
            commandLoadPackages.Run();

            QList<qint64> notLoadedClasses;

            QList<QVariant>::ConstIterator it;
            for(it=dataListCon->begin();it!=dataListCon->end();it++) // loading each class
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
                const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

               qint64 lClassId = row->at(0).toInt();

                if (!m_pClassManager->FindClassById(lClassId))
                {
                   notLoadedClasses.append(lClassId);
                }
            }

            if(notLoadedClasses.count()>0)
            {
                CwnCommandGetClasses commandGetClasses(m_pClassManager, notLoadedClasses, GetDataAccess());
               qint64 lRet = commandGetClasses.Run();

                if(lRet > 0)
                {
                   INFO("Added classes to ClassManager.");
                }
                else
                {
                   ERR("Could not load classes.");
                }
            }

            Ret = 1;
        }
        else
        {
            Ret = EC(eDmOk);
            INFO("There are no Classes in this Scheme.");
        }
    }
}

int CwnCommandLoadClassManager::Execute()
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

CdmClassManager *CwnCommandLoadClassManager::GetResult()
{
    return m_pClassManager;
}

bool CwnCommandLoadClassManager::CheckValid()
{
    return (m_lSchemeId > 0);
}
