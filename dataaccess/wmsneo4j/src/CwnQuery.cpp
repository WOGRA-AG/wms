#include "CwnQuery.h"
#include "CwnQueryElement.h"

#include "CdmQuery.h"
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmMember.h"

#include "CdmQueryResultElement.h"

#include "CdmLogging.h"
#include <QDebug>

CwnQuery::CwnQuery(CwnDataAccess* p_pCwnDataAccess, CdmQuery* p_pCdmQuery) :
    CwnCommandBase(p_pCwnDataAccess),
    m_rpCwnDataAccess(p_pCwnDataAccess),
    m_rpCdmQuery(p_pCdmQuery)
{
    CwnQueryVariables::s_value=1;
    CwnQueryVariables::or_value=1;
    CwnQueryVariables::olr_value=1;
    CwnQueryVariables::u_value=1;
    CwnQueryVariables::ug_value=1;
    CwnQueryVariables::e_value=1;
    CwnQueryVariables::rm_value=0;
    CwnQueryVariables::rv_value=0;
}

CwnQuery::~CwnQuery()
{
    // CANT DELETE new CwnQueryElement
}

QString CwnQuery::MakeKeynameSave(QString p_qstrKeyname)
{
   return CwnHelper::MakeKeynameSave(p_qstrKeyname, m_qmKeynames, m_iKeynameCount);
}

QString CwnQuery::GenerateReturnStatement()
{
    QString qstrCypher;
    int valConnector=1;
    int pathCounter=1;

    if(CHKPTR(m_rpCwnDataAccess) && CHKPTR(m_rpCdmQuery))
    {
        QVector<QString> qvResultElements = m_rpCdmQuery->GetResultElements();
        QString withCypher;
        QString returnCypher;
        if(m_rpCdmQuery->ContainsGrouping())
            returnCypher="RETURN collect([id(ol),id(o)])";
        else
            returnCypher="RETURN id(ol),id(o)";

        if (m_rpCdmQuery->HasResultElements())
        {
            int iCount = qvResultElements.count();

            for (int iCounter = 0; iCounter < iCount; ++iCounter)
            {
                qstrCypher+= " OPTIONAL MATCH ";

                if (qvResultElements[iCounter].contains(".")) // iterating over all references and enhancing the objectquery
                {
                    QString qstrKeynameOrg = qvResultElements[iCounter];
                    QStringList list = qstrKeynameOrg.split('.');

                    CdmQueryResultElement* p_cqre_res = m_rpCdmQuery->GetResultElement(iCounter);

                    if(p_cqre_res->GetValueType())
                    {
                        switch(p_cqre_res->GetValueType())
                        {
                        case eDmValueContainerRef:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<-[:member_to_value]-({Keyname:'"+list[0]+"'}), p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:objectListRefValue]->()";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|n.val)) | x[1]]) AS "+list[0]+"_"+list[1]+"";
                            break;
                        case eDmValueObjectRef:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<-[:member_to_value]-({Keyname:'"+list[0]+"'}), p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:objectRefValue]->(or"+QString::number(CwnQueryVariables::referenceObjects.value(list[0]))+")<-[:hasObjects]-()";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[2]]) AS "+list[0]+"_"+list[1]+"";
                            //CONTAINER ID NOT IMPLEMENTED NOW
                            //", head([x IN COLLECT(DISTINCT EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[3]]) AS "+list[0]+"_"+list[1]+"_Container";
                            break;
                        case eDmValueUser:
                        case eDmValueUserGroup:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<-[:member_to_value]-({Keyname:'"+list[0]+"'}),  p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:objectRefValue]->(or"+QString::number(CwnQueryVariables::referenceObjects.value(list[0]))+")-->()-[:userValue|:userGroupValue]->()";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[3]]) AS "+list[0]+"_"+list[1]+"";
                            break;
                        default:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<-[:member_to_value]-({Keyname:'"+list[0]+"'}), p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:objectRefValue]->(or"+QString::number(CwnQueryVariables::referenceObjects.value(list[0]))+")-->()<--({Keyname:'"+list[1]+"'})";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|n.val)) | x[2]]) AS "+list[0]+"_"+list[1]+"";
                            break;
                        }

                        switch (p_cqre_res->GetMode())
                        {
                        case eDmQueryResultElementModeCount:
                           returnCypher += ", count("+list[0]+"_"+list[1]+")";;
                           break;
                        case eDmQueryResultElementModeSum:
                           returnCypher += ", sum("+list[0]+"_"+list[1]+")";;
                           break;
                        case eDmQueryResultElementModeAvg:
                           returnCypher += ", avg("+list[0]+"_"+list[1]+")";
                           break;
                        case eDmQueryResultElementModeMax:
                           returnCypher += ", max("+list[0]+"_"+list[1]+")";
                           break;
                        case eDmQueryResultElementModeMin:
                           returnCypher += ", min("+list[0]+"_"+list[1]+")";
                           break;
                        default: // no grouping mode
                           returnCypher += ","+list[0]+"_"+list[1]+"";
                           break;
                        }
                    }
                }
                else
                {
                    QString qstrKeynameOrg = qvResultElements[iCounter];
                    QString qstrKeyname = MakeKeynameSave(qstrKeynameOrg);

                    CdmQueryResultElement* p_cqre_res = m_rpCdmQuery->GetResultElement(iCounter);

                    if(p_cqre_res->GetValueType())
                    {
                        switch(p_cqre_res->GetValueType())
                        {
                        case eDmValueContainerRef:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<--({Keyname:'"+qstrKeynameOrg+"'}), p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:objectListRefValue]->()";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[1]]) AS "+qstrKeynameOrg+"";
                            break;
                        case eDmValueObjectRef:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<--({Keyname:'"+qstrKeynameOrg+"'}), p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:objectRefValue]->()<-[:hasObjects]-()";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[1]]) AS "+qstrKeynameOrg+"";
                            //CONTAINER_ID NOT IMPLEMENTED NOW
                            //+", head([x IN COLLECT(DISTINCT EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[2]]) AS "+qstrKeynameOrg+"_Container";
                            break;
                        case eDmValueUser:
                        case eDmValueUserGroup:
                            qstrCypher += "(o)-->(var"+QString::number(valConnector)+")<--({Keyname:'"+qstrKeynameOrg+"'}),  p"+QString::number(pathCounter)+"=(var"+QString::number(valConnector)+")-[:userValue|:userGroupValue]->()";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|id(n)))| x[1]]) AS "+qstrKeynameOrg+"";
                            break;
                        default:
                            qstrCypher += "p"+QString::number(pathCounter)+"=(o)-->()<--({Keyname:'"+qstrKeynameOrg+"'})";
                            withCypher += ", head([x IN COLLECT(EXTRACT(n IN NODES(p"+QString::number(pathCounter)+")|n.val))| x[1]]) AS "+qstrKeynameOrg+"";
                            break;
                        }

                        switch (p_cqre_res->GetMode())
                        {
                        case eDmQueryResultElementModeCount:
                           returnCypher += ", count("+qstrKeynameOrg+")";;
                           break;
                        case eDmQueryResultElementModeSum:
                           returnCypher += ", sum("+qstrKeynameOrg+")";;
                           break;
                        case eDmQueryResultElementModeAvg:
                           returnCypher += ", avg("+qstrKeynameOrg+")";
                           break;
                        case eDmQueryResultElementModeMax:
                           returnCypher += ", max("+qstrKeynameOrg+")";
                           break;
                        case eDmQueryResultElementModeMin:
                           returnCypher += ", min("+qstrKeynameOrg+")";
                           break;
                        default: // no grouping mode
                           returnCypher += ","+qstrKeynameOrg+"";
                           break;
                        }
                    }
                }
                valConnector++;
                pathCounter++;
            }
            qstrCypher +=" WITH ol,o"+withCypher+" "+returnCypher;
        }
        else
        {
            qstrCypher += "RETURN id(ol), id(o)";
        }
    }

    return qstrCypher;
}

QString CwnQuery::GenerateQueryCypher()
{
    QString cypher;

    if(CHKPTR(m_rpCwnDataAccess) && CHKPTR(m_rpCdmQuery))
    {
       CdmQueryElement* pCdmQueryElement = m_rpCdmQuery->GetQueryElement();

       if(pCdmQueryElement)
       {
           CwnQueryElement v_CwnQueryElement(m_rpCwnDataAccess, pCdmQueryElement);

            cypher += QString("MATCH (c:Class)-[:hasObjectContainer]->(ol:WMS_DM_OBJECTLIST)-[:hasObjects]->(o:WMS_DM_OBJECT) ");
            v_CwnQueryElement.GenerateVariablesForLaterUse(cypher);
            CwnQueryVariables::s_value=1;
            CwnQueryVariables::or_value=1;
            CwnQueryVariables::olr_value=1;
            CwnQueryVariables::u_value=1;
            CwnQueryVariables::ug_value=1;
            CwnQueryVariables::e_value=1;
            CwnQueryVariables::rm_value=0;
            CwnQueryVariables::rv_value=0;
            if (m_rpCdmQuery->GetContainerId() > 0)
            {
                cypher +=  QString("WHERE id(ol)=%1 AND %2").arg(QString::number(m_rpCdmQuery->GetContainerId()))
                                                            .arg(v_CwnQueryElement.GenerateQuery());
            }
            else if (m_rpCdmQuery->GetClassId() > 0)
            {
                cypher +=  QString("WHERE id(c)=%1 AND %2").arg(QString::number(m_rpCdmQuery->GetClassId()))
                                                          .arg(v_CwnQueryElement.GenerateQuery());
            }
            cypher += GenerateReturnStatement();
       }
       else
       {

           if (m_rpCdmQuery->GetContainerId() > 0)
           {
               cypher = QString("MATCH (ol:WMS_DM_OBJECTLIST)-[hasObjects]->(o:WMS_DM_OBJECT) WHERE id(ol)=%1 ")
                        .arg(QString::number(m_rpCdmQuery->GetContainerId()));
               cypher += GenerateReturnStatement();
           }
           else if (m_rpCdmQuery->GetClassId() > 0)
           {
               cypher = QString("MATCH (c:Class)-[:hasObjectContainer]->(ol:WMS_DM_OBJECTLIST)-[hasObjects]->(o:WMS_DM_OBJECT) WHERE id(c)=%1 ")
                        .arg(QString::number(m_rpCdmQuery->GetClassId()));
               cypher += GenerateReturnStatement();
           }
           else
           {
               ERR("Unknown Target no container and no class selected.")
           }
       }

       if(m_rpCdmQuery->GetOrderBy().isEmpty())
       {
           QString qstrSortKey = m_rpCdmQuery->GetOrderBy().join(", ");
           QString orderMode = (m_rpCdmQuery->GetOrderMode())?"ASC":"DESC";
           bool bReferenceCount = qstrSortKey.contains(".");

           if(bReferenceCount)
               qstrSortKey.replace(".","_");

           cypher += QString(" ORDER BY %1 %2").arg(qstrSortKey).arg(orderMode);

       }

       if (m_rpCdmQuery->GetResultStart() > 0)
       {
           cypher += " SKIP " + QString::number(m_rpCdmQuery->GetResultStart());
       }

       if (m_rpCdmQuery->GetLimitResultCount() > 0)
       {
           cypher += " LIMIT " + QString::number(m_rpCdmQuery->GetLimitResultCount());
       }
    }

    //ERR(cypher);
    //qDebug()<< cypher;
    return cypher;
}

void CwnQuery::interpretAnswer(QVariant &Ret)
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
        Ret=-1;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()<0)
        {
            //Es wurden keine Ergebnisse mit den übergebenen kriterien gefunden.
            Ret=0;
        }
        else
        {
            Ret=1;

            const QVariantList* results = static_cast<const QVariantList*>(this->qResult->find("results")->data());
            const QVariantMap* data = static_cast<const QVariantMap*>(results->at(0).data());
            const QVariantList* columnList = static_cast<const QVariantList*>(data->find("columns")->data());

            //qDebug() << columnList[i].toString();

            QVariantList::ConstIterator it;
            int rCounter=-1;


            for(it=dataList->begin(); it!=dataList->end();++it)
            {
                const QVariantMap* row = static_cast<const QVariantMap*>(it->data());
                const QVariantList* rowList = static_cast<const QVariantList*>(row->find("row")->data());

                //DEPRICATED GROUP BY WILL REPLACE THIS IF CLAUSE
                //if(m_rpCdmQuery->ContainsGrouping())
                //{
                //    CdmQuery* pQueryEnhanced = dynamic_cast<CdmQuery*>(m_rpCdmQuery);
                //    CdmDataAccessHelper::SetQueryEnhancedResult(pQueryEnhanced, 0, rowList->at(0).toInt(), -1, -1);
                //}


                if(columnList->count()==2)
                {
                    CdmDataAccessHelper::AddQueryResult(m_rpCdmQuery, rowList->at(1).toInt(), rowList->at(0).toInt());
                }

                QVariantList::ConstIterator itc;

                int iCounter;
                if(m_rpCdmQuery->ContainsGrouping())
                {
                    itc=columnList->begin()+1;
                    iCounter=1;
                }
                else
                {
                    itc=columnList->begin()+2;
                    iCounter=2;
                }

                for (;itc!=columnList->end(); ++itc)
                {
                    QVariant qVariant;
                    //qDebug() << qVariant;

                    CdmQuery* pQueryEnhanced = dynamic_cast<CdmQuery*>(m_rpCdmQuery);

                    QString keyname;
                    if(m_rpCdmQuery->ContainsGrouping())
                        keyname = pQueryEnhanced->GetKeynameAt(iCounter-1);
                    else
                        keyname = pQueryEnhanced->GetKeynameAt(iCounter-2);

                    const CdmClass* p_tempClass = pQueryEnhanced->GetClass();
                    const CdmMember* p_member = p_tempClass->FindMember(keyname);
                    QTime n(0,0);

                    switch(p_member->GetValueType())
                    {
                    case eDmValueDate:
                        qVariant = QDate::fromJulianDay(rowList->at(iCounter).toInt());
                        break;
                    case eDmValueDateTime:
                        qVariant = QDateTime::fromTime_t((time_t)(rowList->at(iCounter).toInt()));
                        break;
                    case eDmValueTime:
                        qVariant = n.addSecs(rowList->at(iCounter).toInt());
                        break;
                    case eDmValueString:
                        qVariant = rowList->at(iCounter).toString();
                        break;
                    case eDmValueCharacterDocument:
                        qVariant = CwnHelper::base64_decode(rowList->at(iCounter).toString());
                        break;
                    default:
                        qVariant = rowList->at(iCounter).toString();
                        break;
                    }

                    if (CHKPTR(pQueryEnhanced))
                    {
                        if(m_rpCdmQuery->ContainsGrouping())
                            CdmDataAccessHelper::SetQueryEnhancedResult(pQueryEnhanced, iCounter-1, qVariant, rCounter, rCounter);
                        else
                            CdmDataAccessHelper::SetQueryEnhancedResult(pQueryEnhanced, iCounter-2, qVariant, rowList->at(1).toInt(), rowList->at(0).toInt());
                    }
                    p_tempClass = nullptr;
                    p_member = nullptr;
                    iCounter++;
                }
                rCounter--;
            }

            //int iColumnCount = columnList.count();
            //qDebug()<<iColumnCount;
        }
    }
}

bool CwnQuery::CheckValid()
{
    //Checks are done by other classes
    return true;
}

int CwnQuery::Execute(){
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(GenerateQueryCypher());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

