#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QDateTime>

// WMS Includes
#include "CwmsJson.h"
#include "CdmJournalItem.h"
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmLogging.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwnHelper.h"
#include "CwnDataAccess.h"
#include "CwnJournal.h"


CwnJournal::CwnJournal(CwnDataAccess *m_rpDataAccess):CwnCommandBase(m_rpDataAccess)
{

}

CwnJournal::~CwnJournal()
{

}

qint64 CwnJournal::ValueModified(CdmValue* p_pCdmValue){

   qint64 lRet = CdmLogging::eDmObjectAccessError;
    if (CHKPTR(p_pCdmValue) && p_pCdmValue->GetValueType() != eDmValueBinaryDocument)
    {
        this->qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 CREATE (s)-[:scheme_journal]->(j:ObjectModified:WMSJournal) WITH j ")
                            .arg(p_pCdmValue->GetSchemeId());

        this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=%3, j.mode=\'%4\', j.objectId=%5, j.objectCon=%6, j.memberId=%7, j.displayvalue=\'%8\' RETURN 1;")
                .arg(p_pCdmValue->GetUserId())
                .arg(p_pCdmValue->GetSessionId())
                .arg(QDateTime::currentDateTime().toTime_t())
                .arg(eDmChangeModeModified)
                .arg(p_pCdmValue->GetObject()->GetId())
                .arg(p_pCdmValue->GetObject()->GetObjectContainerId())
                .arg(p_pCdmValue->GetMemberId())
                .arg(p_pCdmValue->GetDisplayString());

       lRet = this->Execute();
       this->qstrQuery ="";
    }
    else if (CHKPTR(p_pCdmValue) && p_pCdmValue->GetValueType() == eDmValueBinaryDocument)
    {
       lRet = CdmLogging::eDmOk;
    }

    return lRet;
}

qint64 CwnJournal::ObjectDeleted(int p_iObjectId)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    if (p_iObjectId > 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
        {
            this->qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 CREATE (s)-[:scheme_journal]->(j:ObjectDeleted:WMSJournal) WITH j ").arg(pCdmManager->GetCurrentScheme()->GetId());

            this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=toInt(%3), j.mode=\'%4\', j.objectId=%5 RETURN 1;")
                    .arg(pCdmManager->GetUserId())
                    .arg(pCdmManager->GetSessionId())
                    .arg(QDateTime::currentDateTime().toTime_t())
                    .arg(eDmChangeModeDeleted)
                    .arg(p_iObjectId);

            lRet = Execute();
            this->qstrQuery="";
        }
    }
    return lRet;
}


qint64 CwnJournal::ObjectModified(CdmObject* p_pCdmObject)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   if (CHKPTR(p_pCdmObject))
   {
      this->qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 CREATE (s)-[:scheme_journal]->(j:ObjectModified:WMSJournal) WITH j ").arg(p_pCdmObject->GetSchemeId());
      if (p_pCdmObject->IsNew())
      {
          this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=toInt(%3), j.mode=\'%4\', j.objectId=%6, j.objectCon=%5, j.displayvalue=\'%7\' RETURN 1;")
                  .arg(p_pCdmObject->GetUserId())
                  .arg(p_pCdmObject->GetSessionId())
                  .arg(QDateTime::currentDateTime().toTime_t())
                  .arg(eDmChangeModeNew)
                  .arg(p_pCdmObject->GetObjectContainerId())
                  .arg(p_pCdmObject->GetId())
                  .arg(p_pCdmObject->GetKeyname());
           lRet = Execute();
      }
      else if (p_pCdmObject->IsDeleted())
      {
          this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=toInt(%3), j.mode=\'%4\', j.objectId=%6, j.objectCon=%5, j.displayvalue=\'%7\' RETURN 1;")
                  .arg(p_pCdmObject->GetUserId())
                  .arg(p_pCdmObject->GetSessionId())
                  .arg(QDateTime::currentDateTime().toTime_t())
                  .arg(eDmChangeModeDeleted)
                  .arg(p_pCdmObject->GetObjectContainerId())
                  .arg(p_pCdmObject->GetId())
                  .arg(p_pCdmObject->GetKeyname());
          lRet = Execute();
      }

      this->qstrQuery="";
   }

   return lRet;
}

qint64 CwnJournal::ObjectListModified(CdmObjectContainer* p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    if(CHKPTR(p_pContainer))
    {
        this->qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 CREATE (s)-[:scheme_journal]->(j:ObjectListModified:WMSJournal) WITH j ").arg(p_pContainer->GetSchemeId());

        if(CHKPTR(p_pContainer->GetClass()))
        {
            if (p_pContainer->IsNew())
            {
                this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=toInt(%3), j.mode=\'%4\', j.objectCon=%5, j.displayvalue=\'%6\' RETURN 1;")
                        .arg(p_pContainer->GetUserId())
                        .arg(p_pContainer->GetSessionId())
                        .arg(QDateTime::currentDateTime().toTime_t())
                        .arg(eDmChangeModeNew)
                        .arg(p_pContainer->GetId())
                        .arg(p_pContainer->GetClass()->GetKeyname());
                lRet = Execute();
            }
            else if (p_pContainer->IsDeleted())
            {
                this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=toInt(%3), j.mode=\'%4\', j.objectCon=%5, j.displayvalue=\'%6\' RETURN 1")
                        .arg(p_pContainer->GetUserId())
                        .arg(p_pContainer->GetSessionId())
                        .arg(QDateTime::currentDateTime().toTime_t())
                        .arg(eDmChangeModeDeleted)
                        .arg(p_pContainer->GetId())
                        .arg(p_pContainer->GetClass()->GetKeyname());
                lRet = Execute();
            }
            this->qstrQuery="";
        }
        else
        {
            lRet = EC(eDmOk);
        }
    }

    return lRet;
 }

qint64 CwnJournal::ObjectListDeleted(int p_iObjectListId)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    if (p_iObjectListId > 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
        {
            this->qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 CREATE (s)-[:scheme_journal]->(j:ObjectListDeleted:WMSJournal) WITH j ").arg(pCdmManager->GetCurrentScheme()->GetId());

            this->qstrQuery += QString("SET j.user=%1, j.session=%2, j.date=toInt(%3), j.mode=\'%4\', j.objectId=%5 RETURN 1;")
                    .arg(pCdmManager->GetUserId())
                    .arg(pCdmManager->GetSessionId())
                    .arg(QDateTime::currentDateTime().toTime_t())
                    .arg(eDmChangeModeDeleted)
                    .arg(p_iObjectListId);

            lRet = Execute();
            this->qstrQuery="";
        }
    }
    return lRet;

}

qint64 CwnJournal::GetObjectModifications(int p_iObjectId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem *> &p_rqlItems)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    QDateTime qdFrom;
    qdFrom.setDate(p_qdFrom);

    QDateTime qdTo;
    qdTo.setDate(p_qdTo);
    qdTo.setTime(QTime(24,59,59,99));

    if (p_iObjectId > 0)
    {
        this->qstrQuery = QString("MATCH (oj) WHERE oj:WMSJournal AND (oj:ObjectModified OR oj:ObjectDeleted) AND oj.objectId=%1 AND oj.date>=toInt(%2) AND oj.date<=toInt(%3) RETURN 2, oj.user, oj.session, oj.date, oj.mode, oj.displayvalue, oj.memberId")
                .arg(p_iObjectId)
                .arg(qdFrom.toTime_t())
                .arg(qdTo.toTime_t());
        lRet = Execute(p_rqlItems);
        this->qstrQuery="";
    }

    return lRet;
}

qint64 CwnJournal::GetObjectListModifications(int p_iObjectListId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem *> &p_rqlItems)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    QDateTime qdFrom;
    qdFrom.setDate(p_qdFrom);

    QDateTime qdTo;
    qdTo.setDate(p_qdTo);
    qdTo.setTime(QTime(24,59,59,99));

    if (p_iObjectListId > 0)
    {
        this->qstrQuery = QString("MATCH (oj) WHERE oj:WMSJournal AND (oj:ObjectListModified OR oj:ObjectListDeleted) AND oj.objectListId=%1 AND oj.date>=toInt(%2) AND oj.date<=toInt(%3) RETURN 3, oj.user, oj.session, oj.date, oj.mode, oj.objectId, oj.displayvalue")
                .arg(p_iObjectListId)
                .arg(qdFrom.toTime_t())
                .arg(qdTo.toTime_t());
        lRet = Execute(p_rqlItems);
        this->qstrQuery="";
    }

    return lRet;

}

qint64 CwnJournal::GetSchemeModifications(int p_iDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem *> &p_rqlItems)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (p_iDatabaseId>0)
    {
        QDateTime qdFrom;
        qdFrom.setDate(p_qdFrom);

        QDateTime qdTo;
        qdTo.setDate(p_qdTo);
        qdTo.setTime(QTime(24,59,59,99));

        this->qstrQuery = QString("MATCH (oj)<-[:scheme_journal]-(s:Scheme) WHERE id(s)=%1 AND oj.date>=toInt(%2) AND oj.date<=toInt(%3) RETURN 4, oj.user, oj.session, oj.date, oj.mode, oj.objectListId, oj.objectId, oj.displayvalue")
                .arg(p_iDatabaseId)
                .arg(qdFrom.toTime_t())
                .arg(qdTo.toTime_t());
        lRet = Execute(p_rqlItems);
        this->qstrQuery="";

    }

    return lRet;
}

int CwnJournal::Execute(){
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(this->qstrQuery);
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

void CwnJournal::interpretAnswer(QVariant &Ret)
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
        if(CwnCommandBase::getDataListPtr()->count()>0)
        {

                Ret = EC(eDmTrue);
        }
        else
        {
            Ret = -1;
            ERR("Failed to insert WMS_JOURNAL");

        }
    }
}

int CwnJournal::Execute(QList<CdmJournalItem *> &p_rqlItems){
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(this->qstrQuery);
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret,p_rqlItems);
    iRet = Ret.toInt();
    return iRet;
}

void CwnJournal::interpretAnswer(QVariant &Ret,QList<CdmJournalItem *> &p_rqlItems)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());
    this->answer=nullptr;

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=0;
    }
    else
    {
        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();

        QVariantList::ConstIterator it;
        for(it=dataListCon->begin();it!=dataListCon->end();++it) // loading each
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            if(list->at(0).toString() == "2")
            {
                int       iUserId           = list->at(1).toInt();
                int       iSessionId        = list->at(2).toInt();
                QDateTime qdtModified(QDateTime::fromTime_t((time_t)(list->at(3).toInt())));
                int       iChangeMode       = list->at(4).toInt();
                QString   qstrDisplayValue  = list->at(5).toString();
                int       iMemberId         = (list->at(6).toInt()>0)?list->at(6).toInt():0;

                CdmJournalItem* pCdmItem = new CdmJournalItem();
                pCdmItem->SetUserId(iUserId);
                pCdmItem->SetSessionId(iSessionId);
                pCdmItem->SetModified(qdtModified);
                pCdmItem->SetChangeMode(static_cast<EdmChangeMode>(iChangeMode));
                pCdmItem->SetDisplayString(qstrDisplayValue);
                pCdmItem->SetMemberId(iMemberId);
                p_rqlItems.append(pCdmItem);

            }
            else if(list->at(0).toString() == "3")
            {
                int       iUserId           = list->at(1).toInt();
                int       iSessionId        = list->at(2).toInt();
                QDateTime qdtModified(QDateTime::fromTime_t((time_t)(list->at(3).toInt())));
                int       iChangeMode       = list->at(4).toInt();
                int       iObjectId         = list->at(5).toInt();
                QString   qstrDisplayValue  = list->at(6).toString();

                CdmJournalItem* pCdmItem = new CdmJournalItem();
                pCdmItem->SetUserId(iUserId);
                pCdmItem->SetSessionId(iSessionId);
                pCdmItem->SetModified(qdtModified);
                pCdmItem->SetChangeMode(static_cast<EdmChangeMode>(iChangeMode));
                pCdmItem->SetObjectId(iObjectId);
                pCdmItem->SetDisplayString(qstrDisplayValue);
                p_rqlItems.append(pCdmItem);


            }
            else if(list->at(0).toString() == "4")
            {
                int       iUserId           = list->at(1).toInt();
                int       iSessionId        = list->at(2).toInt();
                QDateTime qdtModified(QDateTime::fromTime_t((time_t)(list->at(3).toInt())));
                int       iChangeMode       = list->at(4).toInt();
                int       iObjectLIstId     = list->at(5).toInt();
                int       iObjectId         = list->at(6).toInt();
                QString   qstrDisplayValue  = list->at(7).toString();

                CdmJournalItem* pCdmItem = new CdmJournalItem();
                pCdmItem->SetUserId(iUserId);
                pCdmItem->SetSessionId(iSessionId);
                pCdmItem->SetModified(qdtModified);
                pCdmItem->SetChangeMode(static_cast<EdmChangeMode>(iChangeMode));
                pCdmItem->SetObjectId(iObjectId);
                pCdmItem->SetObjectListId(iObjectLIstId);
                pCdmItem->SetDisplayString(qstrDisplayValue);
                p_rqlItems.append(pCdmItem);

            }
        }

        Ret = EC(eDmTrue);
    }
}

bool CwnJournal::CheckValid()
{
    return true;
}


