#include "CwnCommandGetContainerList.h"

#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include <qiterator.h>

#include "CwnCommandStdHeader.h"

CwnCommandGetContainerList::CwnCommandGetContainerList(qint64 p_lSchemeId,qint64 p_lClassId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_lClassId(p_lClassId)
{
}

CwnCommandGetContainerList::~CwnCommandGetContainerList()
{

}

void CwnCommandGetContainerList::GetResult(QMap<qint64, QString> &p_rqmContainerList)
{
    p_rqmContainerList = m_qmContainer;
}

bool CwnCommandGetContainerList::CheckValid()
{
    // Class Id can be 0
    return (m_lSchemeId > 0 && m_lClassId >= 0 && CHKPTR(GetDataAccess()));
}

QString CwnCommandGetContainerList::GetContainerQuery()
{
    QString qstrQuery;

    if(m_lClassId == 0)
    {
       qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]->(oc:WMS_DM_OBJECTLIST) WHERE id(s)=%1 RETURN id(oc),oc.Keyname")
                           .arg(m_lSchemeId);
    }
    else
    {
       qstrQuery = QString("MATCH (c:Class)-[:hasObjectContainer]->(oc:WMS_DM_OBJECTLIST) WHERE id(c)=%1 RETURN id(oc),oc.Keyname")
                           .arg(m_lClassId);
    }

    return qstrQuery;
}

void CwnCommandGetContainerList::interpretAnswer(QVariant &Ret)
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
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            QList<QVariant>::ConstIterator it;
            for(it=dataList->begin();it!=dataList->end();it++) // loading each class
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
                const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

               qint64 lId = row->at(0).toInt();
                QString qstrKeyname = row->at(1).toString();

                if(lId !=0)
                    m_qmContainer.insert(lId, qstrKeyname);

                //qDebug() << rowList;

            }
            Ret = EC(eDmTrue);
        }
        else
        {
            Ret = EC(eDmObjectListNotFound);
            INFO("No ObjectLists found in Database!!");
        }
    }
}

int CwnCommandGetContainerList::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    m_qmContainer.clear();
    QString payload = createJson(GetContainerQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

QString CwnCommandGetContainerList::GetClassListString()
{
    QString qstrClassList;
    QList<qint64> qlClasses = GetClassList();

    if (qlClasses.count() > 0)
    {
        qstrClassList = "[";
        bool bFirst = true;

        for(int iPos = 0; iPos < qlClasses.count(); ++iPos)
        {
            if (!bFirst)
            {
                qstrClassList += ", ";
            }

            bFirst = false;

            qstrClassList += QString::number(qlClasses[iPos]);
        }

        qstrClassList += "]";
    }

    return qstrClassList;
}

QList<qint64> CwnCommandGetContainerList::GetClassList()
{
    QList<qint64> qlClasses;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pManager))
    {
        CdmClassManager* pClassManager = pManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            qlClasses.append(m_lClassId);
            CdmClass* pClass = pClassManager->FindClassById(m_lClassId);

            if (CHKPTR(pClass))
            {
                qlClasses.append(pClass->GetDerivedClasses());
            }
        }
    }

    return qlClasses;
}

