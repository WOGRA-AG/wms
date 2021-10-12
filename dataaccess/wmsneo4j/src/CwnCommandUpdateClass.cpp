#include "CwnCommandUpdateClass.h"
#include "CwnCommandLoadGroupTranslations.h"
#include "CwnCommandLoadTranslation.h"
#include "CwnHelper.h"

#include <qiterator.h>

#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmPackage.h"
#include "CdmClassGroup.h"
#include "CdmClassValidator.h"
#include "CdmClassMethod.h"

#include "CumAccessor.h"

#include <QCryptographicHash>

#include "CwnCommandStdHeader.h"

CwnCommandUpdateClass::CwnCommandUpdateClass(CdmClass *p_pClass, CwnDataAccess *p_pDataAccess):
    CwnCommandBase(p_pDataAccess),
    m_rpClass(p_pClass)
{

}

CwnCommandUpdateClass::~CwnCommandUpdateClass()
{

}


void CwnCommandUpdateClass::createQueryForUpdateAttributesOfClass(){

    // keyname already checked, if unique
    // Query for creating/alter new entries

    QString qstrCypher = QString("MATCH (c:Class) WHERE id(c)=%1 OPTIONAL MATCH (c)<-[d:ClassModifier]-() OPTIONAL MATCH (c)<-[e:ClassCreator]-() OPTIONAL MATCH (c)<-[h:Pkg_Contains_Class]-() DELETE d,e,h RETURN id(c);")
            .arg(m_rpClass->GetId());
    payload += startJsonWCommand(qstrCypher);

    QString qstrQuery;
    QDateTime now = QDateTime::currentDateTime();
    QString str_now = now.date().toString(Qt::ISODate)+" "+now.time().toString(Qt::ISODate);

    CdmPackage* pPackage = m_rpClass->GetPackage();
    QString pkgMatch;
    bool isInPkg=true;

    if(pPackage != nullptr){
        QString pkgStringNotSplitted = CwnHelper::MaskStringForChanges(pPackage->GetPackageString());
        QStringList pkgList = pkgStringNotSplitted.split(".");

        pkgMatch = QString("MATCH (s:Scheme) WHERE id(s) = %1 MATCH (s)-[:pkglevel]->").arg(m_rpClass->GetScheme()->GetId());

        int i=0;
        while(i<pkgList.size()-1)
        {
            pkgMatch += QString("(:Package {URIname:\'%1\'})-[:pkglevel]->").arg(pkgList.at(i));
            i++;
        }
        pkgMatch += QString("(p:Package {URIname:'%1'}) WITH c,p ").arg(pkgList.at(i));
    }
    else
        isInPkg =false;

    qstrQuery = QString("MATCH (c:Class) WHERE id(c) = %1 SET c.Keyname = \'%3\', c.LastChange = \'%4\', c.Caption = \'%5\', c.Comment = \'%6\', c.Abstract = \'%7\', c.Version=\'%8\', c.CaptionMember=\'%9\', c.Config=\'%10\' WITH c %2")
            .arg(m_rpClass->GetId())
            .arg(pkgMatch)
            .arg(CwnHelper::MaskStringForChanges(m_rpClass->GetKeyname()))
            .arg(str_now)
            .arg(CwnHelper::MaskStringForChanges(m_rpClass->GetCaption()))
            .arg(CwnHelper::MaskStringForChanges(m_rpClass->GetComment()))
            .arg(m_rpClass->IsAbstract())
            .arg(m_rpClass->GetVersion())
            .arg(m_rpClass->GetCaptionMemberId())
            .arg(CwnHelper::base64_encode(m_rpClass->GetConfig()));

    if(isInPkg)
    {
        qstrQuery += "CREATE (c)<-[:Pkg_Contains_Class]-(p) WITH c ";
    }

    if(m_rpClass->GetCreatorId()!=0)
        qstrQuery += QString("OPTIONAL MATCH (u:User) WHERE id(u)=%1 CREATE (c)<-[:ClassCreator]-(u) WITH c ").arg(m_rpClass->GetCreatorId());
    if(m_rpClass->GetModifierId()!=0)
        qstrQuery += QString("OPTIONAL MATCH (v:User) WHERE id(v)=%1 CREATE (c)<-[:ClassModifier]-(v) WITH c ").arg(m_rpClass->GetModifierId());

    qstrQuery += QString("RETURN id(c);");

    //qDebug()<< qstrQuery;
    payload += addJsonCommand(qstrQuery);
}


void CwnCommandUpdateClass::interpretAnswer(QVariant &Ret)
{
    //qDebug() << location;
    //qDebug() << answer;
    //optimistic
    bool bRet = true;

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
        Ret=EC(eDmInvalidSelectStatement);
        ConnectAndExecute(rollbackTransaction,nullptr,this->location,nullptr);
        ERR("Something did go wrong with updateing a class");
    }
    else
    {
        const QVariantList* results = static_cast<const QVariantList*>(this->qResult->find("results")->data());
        QVariantList::ConstIterator it;

        for (it=results->begin(); it!=results->end(); ++it)
        {
            const QVariantMap* data = static_cast<const QVariantMap*>(it->data());
            const QVariantList* dataList = static_cast<const QVariantList*>(data->find("data")->data());

            // Wurde überhaupt etwas zurückgegeben?
            if(dataList->count() >0)
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
                const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                if(list->at(0).toInt()>0)
                {
                    bRet = bRet && true;
                    //INSERT MEMBER RETURNS id(w) AND a
                    //FLAG=1 INSERT MEMBER
                    //FLAG=2 UPDATE MEMBER
                    //FLAG=3 INSERT METHOD
                    //FLAG=4 INSERT/UPDATE GROUP
                    //FLAG=5 VALIDATORS ROLLBACK DOES NOT RESET THE CONTAINERS

                    if(list->count()<=1)
                        continue;

                    QPair<CdmMember*,CdmClass*> temp;
                    CdmClassMethod* pMethod;
                    CdmClassGroup* pGroup;

                    switch(list->at(1).toInt())
                    {
                    case 1:
                        temp = forInsertMember.takeFirst();
                        CdmDataAccessHelper::SetId(temp.first, list->at(0).toInt());
                        CdmDataAccessHelper::UpdateMemberId(temp.second, temp.first);
                        //GetDataAccess()->SaveRights(temp.first->GetRights(), temp.first->GetId(), "WMS_CLASS_MEMBER_RIGHTS", "MemberId");
                        m_rpClass->ResetNewModified();
                        break;
                    case 2:
                        break;
                    case 3:
                        pMethod = m_rpClass->FindMethod(list->at(2).toString());
                        pMethod->SetId(list->at(0).toInt());
                        m_rpClass->RemoveMethod(list->at(2).toString());
                        m_rpClass->AddMethod(pMethod);
                        break;
                    case 4:
                        pGroup = m_rpClass->FindGroupByName(list->at(2).toString());
                        pGroup->SetId(list->at(0).toInt());
                        break;
                    case 5:
                        break;
                    }
                }
                else
                    bRet = bRet && false;
            }
            else
                bRet = bRet && false;

            //GetDataAccess()->SaveRights(pCdmMethod->GetRights(),iId,"WMS_CLASS_METHOD_RIGHTS","MethodId");

            if(!bRet)
            {
                Ret=-1;
                ConnectAndExecute(rollbackTransaction,nullptr,this->location,nullptr);
                ERR("Something did go wrong with updateing a class");
                break;
            }
        }
        if(bRet)
        {
            ConnectAndExecute(commitTransaction,nullptr,this->location,nullptr);
            Ret = 1;
        }

    }
}

int CwnCommandUpdateClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    //qDebug() << createQuery();

    // Save the groups for correct ID assignments of members.
    SaveGroups(m_rpClass); //DELETE AND SAVE GROUPS (AGAIN) WITH EVERY CALL OF UPDATECLASS

    QVariant Ret;
    this->payload="";
    this->location="";
    this->answer="";

    // Updating class Data

    // First Update Attributs of a Class
    createQueryForUpdateAttributesOfClass();

    QMap<qint64, CdmMember*> qmMembers;
    m_rpClass->GetClassMemberMap(qmMembers);

    QMap<qint64,CdmMember*>::iterator iIt    = qmMembers.begin();
    QMap<qint64,CdmMember*>::iterator iItEnd = qmMembers.end();

    for(; iIt != iItEnd; ++iIt)
    {
        CdmMember* pCdmMember = iIt.value();

        if(pCdmMember)
        {
            if (pCdmMember->IsDeleted())
            {
                DeleteMember(pCdmMember);
            }
            else if (pCdmMember->IsNew() || pCdmMember->IsModified())
            {
                InsertOrUpdateMember(pCdmMember, m_rpClass);
            }
        }
    }

    CaptionMemberid();
    InsertOrUpdateBaseClasses(m_rpClass);

    SaveMethods(m_rpClass);
    SaveValidators(m_rpClass);

    payload += endJsonCommand();

    //qDebug() << payload;
    queryCausedError = payload;
    ConnectAndExecute(openTransaction,payload,nullptr,nullptr);
    interpretAnswer(Ret);
    //ERR(payload);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandUpdateClass::CheckValid()
{
    return (CHKPTR(m_rpClass));
}

void CwnCommandUpdateClass::SaveGroupTranslations(CdmClassGroup *p_pCdmGroup)
{
    if(CHKPTR(p_pCdmGroup))
    {
        QMap<QString,QString> qmTranlsations = p_pCdmGroup->GetTranslations();

        if(qmTranlsations.count() > 0)
        {
            QMap<QString, QString>::iterator qmIt = qmTranlsations.begin();
            QMap<QString, QString>::iterator qmItEnd = qmTranlsations.end();

            CdmScheme* pScheme = m_rpClass->GetScheme();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                if (CHKPTR(pScheme))
                {
                    QString qstrLanguage = qmIt.key();
                    int languageId = pScheme->GetLanguageId(qstrLanguage);

                    QString qstrCypher = QString("MATCH (l:WMS_LANGUAGES),(g:WMS_CLASS_GROUP) WHERE id(l)=%1 AND id(g)=%2 MERGE (g)-[r:WMS_ClassGroup_Translation]->(l) ON MATCH SET r.caption=\'%3\' ON CREATE SET r.caption=\'%3\' RETURN id(l);")
                            .arg(languageId)
                            .arg(p_pCdmGroup->GetId())
                            .arg(qmIt.value());

                    payload += addJsonCommand(qstrCypher);
                }
            }
        }

    }
}

void CwnCommandUpdateClass::SaveTranslations(QString& qstrQuery, CdmMember* p_pCdmMember)
{
    if (CHKPTR(p_pCdmMember))
    {
        QMap<QString, StringPair>& qmTranslations = p_pCdmMember->GetTranslations();

        if (qmTranslations.count() > 0)
        {
            QMap<QString, StringPair>::iterator qmIt = qmTranslations.begin();
            QMap<QString, StringPair>::iterator qmItEnd = qmTranslations.end();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                StringPair qPair = qmIt.value();

                CdmScheme* pScheme = CdmSessionManager::GetDataProvider()->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    QString qstrLanguage = qmIt.key();
                    int Language = pScheme->GetLanguageId(qstrLanguage);
                    if(Language>0){
                        qstrQuery += QString("MATCH (x:WMS_LANGUAGES) WHERE id(x)=%1 MERGE (w)-[:WMS_ClassMember_Translation {Caption:\'%2\', Comment:\'%3\'}]->(x) WITH w ")
                                .arg(Language)
                                .arg(qPair.first)
                                .arg(qPair.second);
                    }
                }
            }
        }
    }
}

void CwnCommandUpdateClass::InsertOrUpdateBaseClasses(CdmClass *p_pCdmClass)
{
    if(CHKPTR(p_pCdmClass))
    {
        QString qstrCypher = QString("MATCH (c:Class) WHERE id(c)=%1 OPTIONAL MATCH (c)-[a:BaseClassIs]->() DELETE a RETURN id(c)")
                .arg(p_pCdmClass->GetId());
        payload += addJsonCommand(qstrCypher);

        QString qstrQuery;

        QMap<qint64,qint64> qmBaseClasses = p_pCdmClass->GetBaseClasses();

        QMap<qint64,qint64>::iterator qmIt    = qmBaseClasses.begin();
        QMap<qint64,qint64>::iterator qmItEnd = qmBaseClasses.end();

        for(; qmIt != qmItEnd; ++qmIt)
        {
            qstrQuery = QString("MATCH (c:Class),(k:Class) WHERE id(c)=%1 AND id(k)=%2 CREATE (c)-[a:BaseClassIs]->(k) RETURN id(c)")
                    .arg(p_pCdmClass->GetId())
                    .arg(qmIt.value());
            payload += addJsonCommand(qstrQuery);
        }
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateClass::DeleteMember(CdmMember* p_lMember)
{
    if(p_lMember->GetId()!=0)
    {
        QString qstrCypher = QString("MATCH (m:WMS_CLASS_MEMBER) WHERE id(m)=%1 OPTIONAL MATCH (m)-[:member_to_value]->(wv) DETACH DELETE wv,m RETURN 1")
                .arg(p_lMember->GetId());
        payload += addJsonCommand(qstrCypher);
        CdmDataAccessHelper::RemoveMemberFromClass(m_rpClass, p_lMember);
    }
}

void CwnCommandUpdateClass::UpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass)
{
    if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
    {
        int i=0;
        QString qstrCypher = QString("MATCH (w:WMS_CLASS_MEMBER) WHERE id(w)=%1 OPTIONAL MATCH (w)-[t:WMS_ClassMember_Translation]->(k:WMS_CLASS_MEMBER_TRANSLATION)-[i:inLanguage]->() OPTIONAL MATCH ()-[mm:ModifiedMember]->(w) OPTIONAL MATCH (w)<-[cm:CreatedMember]-() OPTIONAL MATCH ()<-[cr:ClassRef]-(w) OPTIONAL MATCH ()-[g:group_has_member]->(w) OPTIONAL MATCH ()<-[r:rights]-(w) DELETE t,i,k,cm,mm,cr,g,r RETURN 1")
                .arg(p_pCdmMember->GetId());
        payload += addJsonCommand(qstrCypher);
        //qDebug()<< qstrCypher;

        QString qstrQuery;

        QString qstrMust = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsMust());
        QString qstrOwner = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsOwner());
        QString qstrExplicit = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsUnique());
        QString qstrSystem = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsSystemMember());
        QString qstrNonPersistent = GetDataAccess()->GetBoolAsString(!p_pCdmMember->IsPersistent());
        QString qstrTree = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsTree());
        QString qstrDefaultValue = p_pCdmMember->GetDefaultValue().toString();

        int iGroupId = 0;
        if (p_pCdmMember->GetGroup())
        {
            iGroupId = p_pCdmMember->GetGroup()->GetId();
        }

        qstrQuery = QString("MATCH (w:WMS_CLASS_MEMBER) WHERE id(w)=%1 ")
                .arg(p_pCdmMember->GetId());

        qstrQuery += QString("SET w.Keyname=\'%1\', w.Datatype=\'%2\', w.Must=\'%3\', w.Size=\'%4\', w.CounterStart=\'%5\', w.DefaultValue=\'%6\', w.Caption=\'%7\',")
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetKeyname()))
                .arg(p_pCdmMember->GetValueType())
                .arg(qstrMust)
                .arg(p_pCdmMember->GetSize())
                .arg(p_pCdmMember->GetCounterStart())
                .arg(qstrDefaultValue)
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetCaption()));

        qstrQuery += QString("w.Comment=\'%1\', w.Owner=\'%2\', w.Explicit=\'%3\', w.System=\'%4\', w.Access=\'%5\', w.Version=\'%6\', w.Validation=\'%7\', w.Non_Persistent=\'%8\', w.Is_Tree=\'%9\', w.Config=\'%10\' WITH w ")
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetComment()))
                .arg(qstrOwner)
                .arg(qstrExplicit)
                .arg(qstrSystem)
                .arg(p_pCdmMember->GetAccessMode())
                .arg(p_pCdmMember->GetVersion())
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetValidationCodeBase64()))
                .arg(qstrNonPersistent)
                .arg(qstrTree)
                .arg(CwnHelper::base64_encode(p_pCdmMember->GetConfig()));

        if(p_pCdmMember->GetClassReference()!=0)
        {
            if(p_pCdmMember->GetValueType() == 10 || p_pCdmMember->GetValueType() == 11)
            {
                qstrQuery += QString("OPTIONAL MATCH (z:Class) WHERE id(z)=%1 CREATE (w)-[:ClassRef]->(z) REMOVE z.ClassRef WITH w ").arg(p_pCdmMember->GetClassReference());
            }
            else
            {
                qstrQuery += QString("REMOVE w.ClassRef=%1  WITH w ").arg(p_pCdmMember->GetClassReference());
            }
        }
        if(p_pCdmMember->GetCreatorId()!=0)
            qstrQuery += QString("OPTIONAL MATCH (u:User) WHERE id(u)=%1 CREATE (w)<-[:CreatedMember]-(u) WITH w ").arg(p_pCdmMember->GetCreatorId());
        if(p_pCdmMember->GetModifierId()!=0)
            qstrQuery += QString("OPTIONAL MATCH (v:User) WHERE id(v)=%1 CREATE (w)<-[:ModifiedMember]-(v) WITH w ").arg(p_pCdmMember->GetModifierId());
        if(iGroupId!=0)
            qstrQuery += QString("OPTIONAL MATCH (g:WMS_CLASS_GROUP) WHERE id(g)=%1 CREATE (w)<-[:group_has_member]-(g) WITH w ").arg(iGroupId);

        qstrQuery += QString("OPTIONAL MATCH (w {Datatype:\'%1\'})-[:member_to_value]->(v:WMS_VALUE) WHERE v.type <> %2 DETACH DELETE v ")
                .arg(p_pCdmMember->GetValueType())
                .arg(p_pCdmMember->GetValueType());

        addRights(p_pCdmMember->GetRights().GetVariant().toMap(),i,qstrQuery,"WMS_CLASS_MEMBER","w");
        SaveTranslations(qstrQuery, p_pCdmMember);
        qstrQuery += QString("RETURN DISTINCT id(w),2;");

        //qDebug()<< qstrQuery;
        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateClass::InsertMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass)
{
    if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
    {
        QString qstrQuery;

        QString qstrMust = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsMust());
        QString qstrOwner = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsOwner());
        QString qstrExplicit = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsUnique());
        QString qstrSystem = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsSystemMember());
        QString qstrNonPersistent = GetDataAccess()->GetBoolAsString(!p_pCdmMember->IsPersistent());
        QString qstrTree = GetDataAccess()->GetBoolAsString(p_pCdmMember->IsTree());
        QString qstrDefaultValue = p_pCdmMember->GetDefaultValue().toString();

        int iGroupId = 0;
        if (p_pCdmMember->GetGroup())
        {
            iGroupId = p_pCdmMember->GetGroup()->GetId();
        }

        qstrQuery = QString("MATCH (c:Class) WHERE id(c)=%1 ")
                .arg(p_pCdmMember->GetClassId());

        qstrQuery += QString("CREATE (c)-[:WMS_Member]->(w:WMS_CLASS_MEMBER {Keyname:\'%1\', Datatype:\'%2\', Must:\'%3\', Size:\'%4\', CounterStart:\'%5\',DefaultValue:\'%6\', Caption:\'%7\',")
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetKeyname()))
                .arg(p_pCdmMember->GetValueType())
                .arg(qstrMust)
                .arg(p_pCdmMember->GetSize())
                .arg(p_pCdmMember->GetCounterStart())
                .arg(qstrDefaultValue)
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetCaption()));

        qstrQuery += QString("Comment:\'%1\', Owner:\'%2\', Explicit:\'%3\', System:\'%4\', Access:\'%5\', Version:\'%6\', Validation:\'%7\', Non_Persistent:\'%8\', Is_Tree:\'%9\'}) WITH w ")
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetComment()))
                .arg(qstrOwner)
                .arg(qstrExplicit)
                .arg(qstrSystem)
                .arg(p_pCdmMember->GetAccessMode())
                .arg(p_pCdmMember->GetVersion())
                .arg(CwnHelper::MaskStringForChanges(p_pCdmMember->GetValidationCodeBase64()))
                .arg(qstrNonPersistent)
                .arg(qstrTree);

        if(p_pCdmMember->GetClassReference()!=0)
        {
            if(p_pCdmMember->GetValueType() == 10 || p_pCdmMember->GetValueType() == 11)
            {
                qstrQuery += QString("OPTIONAL MATCH (z:Class) WHERE id(z)=%1 CREATE (w)-[:ClassRef]->(z) WITH w ").arg(p_pCdmMember->GetClassReference());
            }
            else
            {
                qstrQuery += QString("SET w.ClassRef=%1  WITH w ").arg(p_pCdmMember->GetClassReference());
            }

        }
        if(p_pCdmMember->GetCreatorId()!=0)
            qstrQuery += QString("OPTIONAL MATCH (u:User) WHERE id(u)=%1 CREATE (w)<-[:CreatedMember]-(u) WITH w ").arg(p_pCdmMember->GetCreatorId());
        if(p_pCdmMember->GetModifierId()!=0)
            qstrQuery += QString("OPTIONAL MATCH (v:User) WHERE id(v)=%1 CREATE (w)<-[:ModifiedMember]-(v) WITH w ").arg(p_pCdmMember->GetModifierId());
        if(iGroupId!=0)
            qstrQuery += QString("OPTIONAL MATCH (g:WMS_CLASS_GROUP) WHERE id(g)=%1 CREATE (w)<-[:group_has_member]-(g) WITH w ").arg(iGroupId);

        QPair<CdmMember*, CdmClass*> mp;
        mp.first = p_pCdmMember;
        mp.second = p_pCdmClass;
        forInsertMember.enqueue(mp);

        SaveTranslations(qstrQuery, p_pCdmMember);
        qstrQuery += QString("RETURN id(w),1;");

        insertedClasses.append(p_pCdmMember->GetKeyname());

        //qDebug() << qstrQuery;
        payload += addJsonCommand(qstrQuery);
    }

}

void CwnCommandUpdateClass::InsertOrUpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass)
{
    if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
    {
        if(p_pCdmMember->IsNew() && !p_pCdmMember->IsDeleted())
        {
            InsertMember(p_pCdmMember, p_pCdmClass);
        }
        else if(p_pCdmMember->IsModified() && !p_pCdmMember->IsDeleted())
        {
            UpdateMember(p_pCdmMember, p_pCdmClass);
        }
        else if(p_pCdmMember->IsDeleted())
        {
            DeleteMember(p_pCdmMember);
        }
    }
}

void CwnCommandUpdateClass::CaptionMemberid()
{
    QVector<QString> posList = m_rpClass->GetMemberSequence();

    for(int i=0; i<posList.count();i++)
    {
        if(!insertedClasses.contains(posList.at(i)))
                    continue;

        QString qstrQuery = QString("MATCH (c)-[r:WMS_Member]->(:WMS_CLASS_MEMBER {Keyname:\'%2\'}) WHERE id(c)=%3 SET r.pos=\'%1\' RETURN id(c)")
                .arg(i+1)
                .arg(posList.at(i))
                .arg(m_rpClass->GetId());
        payload += addJsonCommand(qstrQuery);
    }
}

void CwnCommandUpdateClass::SaveValidators(CdmClass *&p_rCdmClass)
{
    QString qstrCypherDelete = QString("MATCH (c:Class) WHERE id(c)=%1 OPTIONAL MATCH (c)-[v:Class_Validator]->(b) DELETE v,b RETURN id(c)")
            .arg(p_rCdmClass->GetId());

    payload += addJsonCommand(qstrCypherDelete);

    QMap<QString, CdmClassValidator*>& qmValidations = p_rCdmClass->GetValidators();
    QMap<QString, CdmClassValidator*>::iterator qmIt = qmValidations.begin();
    QMap<QString, CdmClassValidator*>::iterator qmItEnd = qmValidations.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassValidator* pCdmValidator = qmIt.value();

        if (CHKPTR(pCdmValidator))
        {
            QString nQuery;

            nQuery = QString("MATCH (c:Class) WHERE id(c)=%1 ")
                    .arg(p_rCdmClass->GetId());
            nQuery += QString("CREATE (c)-[:Class_Validator]->(w:WMS_CLASS_VALIDATION {Name:\'%2\', Code:\'%3\', Version:\'%4\', edmType:\'%5\', Message:\'%6\'}) "
                              "RETURN id(w),5,'%7'")
                    .arg(CwnHelper::MaskStringForChanges(pCdmValidator->GetName()))
                    .arg(CwnHelper::MaskStringForChanges(pCdmValidator->GetCodeBase64()))
                    .arg(pCdmValidator->GetVersion())
                    .arg(pCdmValidator->GetValidationType())
                    .arg(CwnHelper::MaskStringForChanges(pCdmValidator->GetErrorMessage()))
                    .arg(qmIt.key());
            payload += addJsonCommand(nQuery);
        }
    }
}

void CwnCommandUpdateClass::SaveMethods(CdmClass *&p_rCdmClass)
{
    QString nQuery;
    QMap<QString, CdmClassMethod*> qmGroups = p_rCdmClass->GetMethods();

    QString qstrCypher = QString("MATCH (c:Class) WHERE id(c)=%1 OPTIONAL MATCH (c)-[r:Class_Method]->(m) DETACH DELETE m RETURN id(c)")
            .arg(m_rpClass->GetId());
    payload += addJsonCommand(qstrCypher);

    QMap<QString, CdmClassMethod*>::iterator qmIt = qmGroups.begin();
    QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmGroups.end();

    int i=0;
    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassMethod* pCdmMethod = qmIt.value();

        if (CHKPTR(pCdmMethod))
        {

            QString qstrStatic = CwnHelper::ConvertBoolToString(pCdmMethod->IsStatic());
            QByteArray qbIcon = pCdmMethod->GetIconAsByteArray();
            QString qstrBase64(qbIcon.toBase64());

            nQuery = QString("MATCH (c:Class) WHERE id(c)=%1 "
                             "CREATE (c)-[:Class_Method]->(m:WMS_CLASS_METHOD {Name:\'%2\', MethodType:\'%3\', Code:\'%4\', Version:\'%5\', AccessMode:\'%6\', Parameters:\'%7\', Static:\'%8\', Comment:\'%9\', Caption:\'%10\', Icon:\'%11\'}) "
                             )
                    .arg(p_rCdmClass->GetId())
                    .arg(CwnHelper::MaskStringForChanges(pCdmMethod->GetMethodName()))
                    .arg(pCdmMethod->GetReturnType())
                    .arg(CwnHelper::MaskStringForChanges(pCdmMethod->GetSourceCodeBase64()))
                    .arg(pCdmMethod->GetVersion())
                    .arg(pCdmMethod->GetAccess())
                    .arg(pCdmMethod->GetParametersAsString())
                    .arg(qstrStatic)
                    .arg(CwnHelper::MaskStringForChanges(pCdmMethod->GetComment()))
                    .arg(CwnHelper::MaskStringForChanges(pCdmMethod->GetCaption()))
                    .arg(qstrBase64);

            addRights(pCdmMethod->GetRights().GetVariant().toMap(),i,nQuery,"WMS_CLASS_METHOD","m");

            nQuery += QString("RETURN id(m),3,'%12' ").arg(qmIt.key());

            //qDebug() << nQuery;
            payload += addJsonCommand(nQuery);

        }
    }
}

void CwnCommandUpdateClass::SaveGroups(CdmClass *&p_rCdmClass)
{

    const QMap<int, CdmClassGroup*>& qmGrooups = p_rCdmClass->GetClassGroups();

    if(qmGrooups.count()<1)
        return;

    QMap<int, CdmClassGroup*>::const_iterator qmIt = qmGrooups.begin();
    QMap<int, CdmClassGroup*>::const_iterator qmItEnd = qmGrooups.end();

    QString groupIdsShouldNotBeDeleted = "[";

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pCdmGroup = qmIt.value();
        groupIdsShouldNotBeDeleted += QString("%1,").arg(pCdmGroup->GetId());
    }

    groupIdsShouldNotBeDeleted.chop(1);
    groupIdsShouldNotBeDeleted += "]";

    payload += startJsonWCommand(QString("OPTIONAL MATCH (c:Class)-[:class_group]->(g:WMS_CLASS_GROUP) WHERE id(c)=%1 AND NOT(id(g) IN %2) DETACH DELETE g RETURN DISTINCT 1")
                                 .arg(p_rCdmClass->GetId())
                                 .arg(groupIdsShouldNotBeDeleted));


    qmIt = qmGrooups.begin();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pCdmGroup = qmIt.value();

        QString qstrQuery;
        if (CHKPTR(pCdmGroup))
        {
            int i=0;
            if(pCdmGroup->GetId() == 0)
            {
                qstrQuery = QString("MATCH (c:Class) WHERE id(c)=%1 CREATE (c)-[:class_group]->(g:WMS_CLASS_GROUP)"
                                    " SET g.Name=\'%3\', g.Version=\'%4\', g.Position=\'%5\'")
                        .arg(p_rCdmClass->GetId())
                        .arg(CwnHelper::MaskStringForChanges(pCdmGroup->GetName()))
                        .arg(pCdmGroup->GetVersion())
                        .arg(pCdmGroup->GetPosition());

                qstrQuery += QString(" RETURN id(g),4,g.Name;");
            }
            else
            {
                payload += addJsonCommand(QString("OPTIONAL MATCH (g)-[r:rights]->() WHERE id(g)=%1 DETACH DELETE r RETURN 1").arg(pCdmGroup->GetId()));

                qstrQuery = QString("MATCH (c)-[:class_group]->(g) WHERE id(c)=%1 AND id(g)=%2"
                                    " SET g.Name=\'%3\', g.Version=\'%4\', g.Position=\'%5\'")
                        .arg(p_rCdmClass->GetId())
                        .arg(pCdmGroup->GetId())
                        .arg(CwnHelper::MaskStringForChanges(pCdmGroup->GetName()))
                        .arg(pCdmGroup->GetVersion())
                        .arg(pCdmGroup->GetPosition());

                addRights(pCdmGroup->GetRights().GetVariant().toMap(),i,qstrQuery,"WMS_CLASS_GROUP","g");
                qstrQuery += QString(" RETURN id(g),4,g.Name;");
            }
            payload += addJsonCommand(qstrQuery);

            SaveGroupTranslations(pCdmGroup);
        }
    }
    payload += endJsonCommand();

    ConnectAndExecute(openTransaction,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);

    //ERR(payload);
}

void CwnCommandUpdateClass::addRights(QVariantMap qvHash, int& i, QString& qstrQuery, QString NodeName, QString NodeVar)
{
    QVariantMap::Iterator qvIt = qvHash.begin();
    QVariantMap::Iterator qvItEnd = qvHash.end();


    for (; qvIt != qvItEnd; ++qvIt)
    {
        int iUserBaseId = 0;
        QString qstrUri = qvIt.key();
        if (!qstrUri.isEmpty())
        {
            CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pManager))
            {
                CdmLocatedElement* pElement = pManager->GetUriObject(qstrUri);

                if (pElement)
                {
                    if (pElement->IsUser() || pElement->IsUserGroup())
                    {
                        iUserBaseId = static_cast<CumAccessor*> (pElement)->GetId();
                    }
                    else
                    {
                        ERR("Wrong URI Type");
                    }
                }
                else
                {
                    ERR("Unknown Element:" + qstrUri);
                    continue;
                }
            }

            qstrQuery += QString(" WITH "+NodeVar+" MATCH (u"+QString::number(i)+") WHERE id(u"+QString::number(i)+")=%1 MERGE ("+NodeVar+")-[:rights {rightId:%2, type:\'%3\'}]->(u"+QString::number(i)+") WITH "+NodeVar+" ")
                    .arg(iUserBaseId)
                    .arg(qvIt.value().toInt())
                    .arg(NodeName);
            i++;
        }
    }
}

