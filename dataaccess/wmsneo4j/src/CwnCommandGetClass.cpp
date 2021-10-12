#include <qiterator.h>
#include <QByteArray>

// WMS Includes
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmClassGroup.h"
#include "CdmScheme.h"
#include "CdmClassValidator.h"
#include "CdmMember.h"
#include "CdmPackage.h"

// own Includes
#include "CwnCommandGetClass.h"
#include "CwnCommandLoadGroupTranslations.h"
#include "CwnCommandLoadTranslation.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetClass::CwnCommandGetClass(CdmClassManager* p_ppClassManager,qint64 p_lClassId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lClassId(p_lClassId),
  m_rpClass(nullptr),
  m_rpClassManager(p_ppClassManager)
{
}

CwnCommandGetClass::~CwnCommandGetClass()
{
}

qint64 CwnCommandGetClass::interpretAnswerForLoadMembers(QVariantList& dataList)
{

   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(m_rpClass))
    {
        QList<CdmMember*> qlMembers;

        if(dataList.count()>0)
        {
            for(int i=0;i<dataList.count();i++) // loading each class
            {
                QVariantMap rowTemp = dataList[i].toMap();
                QVariantList list = rowTemp["row"].toList();

               qint64     lCreatorId         = (list[2]!=0)?list[2].toInt():0;
               qint64     lModifierId        = (list[3]!=0)?list[3].toInt():0;
               qint64     lId                = list[4].toInt();
               qint64     lDatabaseId        = list[5].toInt();
                QVariantMap props           = list[6].toMap();
                int      iValue             = props["Datatype"].toInt();
                bool     bMust              = props["Must"].toBool();
               qint64     lSize              = props["Size"].toInt();
               qint64     lCounterSize       = props["CounterSize"].toInt();
               qint64     lClassId           = m_lClassId;
                QVariant qvDefaultValue     = props["DefaultValue"];
                QString  qstrKeyname        = props["Keyname"].toString();
                QString  qstrCaption        = props["Caption"].toString();
                QString  qstrComment        = props["Comment"].toString();
                bool     bOwner             = props["Owner"].toBool();
                bool     bUnique            = props["Unique"].toBool();
                bool     bSystem            = true;
                int      propClassRef       = props["ClassRef"].toInt();


               qint64 lGroupId = 0;
                if (!list[0].isNull())
                {
                    lGroupId = list[0].toInt();
                }

               qint64 lRefClassId = 0;
                if (!list[1].isNull())
                {
                    lRefClassId = list[1].toInt();
                }
                else if(propClassRef != 0)
                {
                    lRefClassId = propClassRef;
                }

                if(!props["System"].isNull())
                {
                    bSystem = bUnique;
                }

                int iAccess = 0;
                if (!props["Access"].isNull())
                {
                    iAccess = props["Access"].toInt();
                }

                int iVersion = 0;
                if (!props["Version"].isNull())
                {
                    iVersion = props["Version"].toInt();
                }

                QString  qstrValidation;
                if (!props["Validation"].isNull())
                {
                    qstrValidation = CwnHelper::base64_decode(props["Validation"].toString());
                }

                QString qstrConfig;
                if(!props["Config"].isNull())
                {
                    qstrConfig = CwnHelper::base64_decode(props["Config"].toString());
                }

                bool bNonPersistent = props["NonPersistent"].toBool();
                bool bTree = props["Tree"].toBool();

                CdmMember* pCdmMember = nullptr;

                INFO ("Creating Member '" + qstrKeyname + "'");
                pCdmMember = CdmDataAccessHelper::CreateMember(lDatabaseId,
                                                                lId,
                                                                qstrKeyname,
                                                                iValue,
                                                                bMust,
                                                                static_cast<int>(lSize));

                pCdmMember->SetCaption(qstrCaption);
                CdmDataAccessHelper::SetCreatorId(pCdmMember, lCreatorId);
                CdmDataAccessHelper::SetModifierId(pCdmMember, lModifierId);
                CdmDataAccessHelper::SetMemberClassId(pCdmMember, lClassId);
                pCdmMember->SetClassReference(lRefClassId);
                pCdmMember->SetCounterStart(lCounterSize);
                pCdmMember->SetDefaultValue(qvDefaultValue);
                pCdmMember->SetComment(qstrComment);
                pCdmMember->SetOwner(bOwner);
                pCdmMember->SetSystemFlag(bSystem);
                pCdmMember->SetUnique(bUnique);
                pCdmMember->SetMemberAccess(static_cast<EdmMemberAccess>(iAccess));
                pCdmMember->SetGroup(m_rpClass->FindGroupById(lGroupId));
                pCdmMember->SetVersion(iVersion);
                pCdmMember->SetValidationCode(qstrValidation);
                pCdmMember->SetPersistent(!bNonPersistent);
                pCdmMember->SetTree(bTree);
                pCdmMember->SetConfig(qstrConfig);

                qlMembers.append(pCdmMember);
            }

            for (int iCounter = 0; iCounter < qlMembers.count(); ++iCounter)
            {
                CdmMember* pCdmMember = qlMembers[iCounter];
                GetDataAccess()->LoadRights(pCdmMember->GetRights(), pCdmMember->GetId(), "WMS_CLASS_MEMBER", "MemberId");
                INFO ("Adding Member '" + pCdmMember->GetKeyname() + "' to class '" + m_rpClass->GetKeyname() + "'");
                CdmDataAccessHelper::AddMemberToClass(m_rpClass, pCdmMember);
                CwnDataAccess* temp = nullptr;
                CwnCommandLoadTranslation t(temp,pCdmMember);
                t.Run();
                pCdmMember->ResetNewModified();
            }

            lRet = EC(eDmOk);
        }
        else
        {
            lRet = EC(eDmOk);
            INFO("No class members found for this class!");
        }
    }
    return lRet;
}

bool CwnCommandGetClass::interpretAnswerForLoadMethods(QVariantList& dataList)
{
    if(dataList.count()>0)
    {
        QList<CdmClassMethod*> qlMethods;
        for(int i=0;i<dataList.count();i++)
        {
            QVariantMap rowTemp = dataList[i].toMap();
            QVariantList list = rowTemp["row"].toList();

           qint64 lMethodId = list[0].toInt();
            QVariantMap props = list[1].toMap();
            QString qstrName = props["Name"].toString();
            int iVersion = props["Version"].toInt();
            QString qstrCode = props["Code"].toString();
            EdmValueType eDmType = static_cast<EdmValueType>(props["eDmType"].toInt());
            EdmMemberAccess eDmAccess = static_cast<EdmMemberAccess>(props["eDmAccess"].toInt());
            QString qstrParameters = props["Parameters"].toString();
            QString qstrComment = props["Comment"].toString();
            QString qstrIcon = QString(props["Icon"].toString().data());
            QString qstrCaption = props["Caption"].toString();
            bool bStatic = props["Static"].toBool();

            CdmClassMethod* pCdmMethod = m_rpClass->CreateMethod(static_cast<int>(lMethodId), qstrName, eDmType, eDmAccess, qstrCode, iVersion);
            qlMethods.append(pCdmMethod);
            pCdmMethod->SetParameters(qstrParameters);
            pCdmMethod->SetComment(qstrComment);
            pCdmMethod->SetStatic(bStatic);

            pCdmMethod->SetCaption(qstrCaption);
            QByteArray qbaIcon = QByteArray::fromBase64(qstrIcon.toLocal8Bit());
            pCdmMethod->SetIcon(qbaIcon);
        }

        for (int iCOunter = 0; iCOunter < qlMethods.count(); ++iCOunter)
        {
            CdmClassMethod* pCdmMethod = qlMethods[iCOunter];

            GetDataAccess()->LoadRights(pCdmMethod->GetRights(),
                                        pCdmMethod->GetId(),
                                        "CLASS_METHOD",
                                        "MethodId");
        }
    }
    else
    {
        INFO("No Methods found for this class!");
   }
    return true;
}
bool CwnCommandGetClass::interpretAnswerForLoadValidators(QVariantList& dataList)
{
    if(dataList.count()>0)
    {
        for(int i=0;i<dataList.count();i++) // loading each class
        {
            QVariantMap rowTemp = dataList[i].toMap();
            QVariantList list = rowTemp["row"].toList();

           qint64 lValidationId = list[0].toInt();
            QVariantMap props = list[1].toMap();
            QString qstrName = props["Name"].toString();
            int iVersion = props["Version"].toInt();
            QString qstrCode = props["Code"].toString();
            EdmValidationType eDmType = static_cast<EdmValidationType>(props["edmType"].toInt());
            QString qstrMessage = props["Message"].toString();

            CdmClassValidator* pCdmValidator = m_rpClass->CreateValidator(qstrName);
            pCdmValidator->SetId(static_cast<int>(lValidationId));
            pCdmValidator->SetVersion(iVersion);
            pCdmValidator->SetCode(CwnHelper::base64_decode(qstrCode));

            pCdmValidator->SetValidationType(eDmType);
            pCdmValidator->SetMessage(qstrMessage);

       }
    }
    else
    {
        INFO("No Validators found for this class!");
    }
    return true;
}
bool CwnCommandGetClass::interpretAnswerForLoadGroups(QVariantList& dataList)
{
    //Id, Name, Version, Position, Parent
    //qDebug() << dataList;

    QList<CdmClassGroup*> qlGroups;

    for(int i=0;i<dataList.count();i++)
    {
        QVariantMap rowTemp = dataList[i].toMap();
        QVariantList list = rowTemp["row"].toList();

       qint64 lGroupId = list[0].toInt();
        QVariantMap props = list[1].toMap();

        QString qstrName = props["Name"].toString();
        int iVersion = props["Version"].toInt();
        int iPosition = props["Position"].toInt();
        int iParent;
        if (props.contains("Parent"))
            iParent = props["Parent"].toInt();
        else
            iParent = 0;
        //qDebug() << qstrName;

        CdmClassGroup* pCdmGroup = m_rpClass->CreateGroup(qstrName, iVersion, iPosition, nullptr);

        if (CHKPTR(pCdmGroup))
        {
            qlGroups.append(pCdmGroup);
            pCdmGroup->SetId(static_cast<int>(lGroupId));
            pCdmGroup->SetPosition(iPosition);
            pCdmGroup->SetParentId(iParent);
        }
    }

    for (int iCounter = 0; iCounter < qlGroups.count(); ++iCounter)
    {
         CdmClassGroup* pCdmGroup = qlGroups[iCounter];
         GetDataAccess()->LoadRights(pCdmGroup->GetRights(),
                                        pCdmGroup->GetId(),
                                        "CLASS_GROUP",
                                        "GroupId");
         //qDebug() << pCdmGroup->GetId();

         CwnDataAccess* temp = nullptr;
         CwnCommandLoadGroupTranslations t(temp,pCdmGroup);
         t.Run();
    }

    return true;
}

bool CwnCommandGetClass::interpretAnswerForBaseClasses(QVariantList& dataList)
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(m_rpClass))
    {
        if(dataList.count()>0)
        {
            for(int i=0;i<dataList.count();i++)
            {
                QVariantMap rowTemp = dataList[i].toMap();
                QVariantList list = rowTemp["row"].toList();

               qint64 lBaseClassId = list[i].toLongLong();
                if(lBaseClassId>0)
                    CdmDataAccessHelper::AddBaseClassToClass(m_rpClass, lBaseClassId);
            }
            lRet = EC(eDmOk);
         }
         else
         {
            lRet = EC(eDmOk);
            INFO("No Base class found to this class.");
         }
     }
     else
     {
         lRet = EC(eDmInvalidSelectStatement);
         ERR("Base Class Query pronounced an error!!!");
     }

     return lRet;
}


bool CwnCommandGetClass::interpretAnswerForPosAndMembers(QVariantList& dataList){

    //qDebug() << dataList;

    QMap<qint64,QString> ForPosAndMembers;

    for(int i=0;i<dataList.count();i++)
    {
        QVariantMap listMapPosAndName = dataList[i].toMap();
        QVariantList list = listMapPosAndName["row"].toList();
        ForPosAndMembers.insert(list[0].toLongLong(),list[1].toString());

    }

    // second step creating class object
    m_rpClass->SetMemberSequenceString(ForPosAndMembers);

    return true;
}
bool CwnCommandGetClass::interpretAnswerForClassLoad(QVariantList& dataList)
{
    // first step reading the WMS_Class data

    //qint64 lCaptionMember = cQSqlQuery.value(8).toInt();

    QVariantMap rowMap = dataList[0].toMap();
    QVariantList list = rowMap["row"].toList();

    //qDebug() << dataList;
   qint64 lClassId   = list[0].toLongLong();
    QVariantMap listMap = list[1].toMap();
    //qDebug() << listMap;

    // first step reading the WMS_Class data
    QString qstrCaption  = listMap["Caption"].toString();
    QString qstrKeyname  = listMap["Keyname"].toString();
    QDateTime qdLastChange = listMap["LastChange"].toDateTime();

    QString qstrConfig;
    QString qstrComment;
    bool bAbstract;
    int iVersion;
   qint64 lCaptionMember;

    if (listMap.contains("Comment"))
        qstrComment  = listMap["Comment"].toString();
    else
        qstrComment = "";

    if (listMap.contains("Abstract"))
        bAbstract = listMap["Abstract"].toBool();
    else
        bAbstract = false;

    if (listMap.contains("Version") && !listMap["Version"].isNull())
        iVersion = listMap["Version"].toInt();
    else
        iVersion = 0;

    if (listMap.contains("CaptionMember") && !listMap["CaptionMember"].isNull())
        lCaptionMember = listMap["CaptionMember"].toInt();
    else
        lCaptionMember = 0;

    if (listMap.contains("Config"))
        qstrConfig = CwnHelper::base64_decode(listMap["Config"].toString());

   qint64 lDatabaseId = list[2].toLongLong();
   qint64 modifier = 0;
   qint64 creator = 0;

    if(list.length()>3){
        creator = list[4].toLongLong();
        modifier = list[3].toLongLong();
    }

    // second step creating class object
    m_rpClass = CdmDataAccessHelper::CreateClass(lDatabaseId, lClassId, qstrKeyname);
    m_rpClass->SetComment(qstrComment);
    m_rpClass->SetCaption(qstrCaption);
    m_rpClass->SetAbstract(bAbstract);
    m_rpClass->SetVersion(iVersion);
    m_rpClass->SetLastChange(qdLastChange);
    m_rpClass->SetCaptionMember(lCaptionMember);
    m_rpClass->SetCreatorId(creator);
    m_rpClass->SetModifierId(modifier);
    m_rpClass->SetConfig(qstrConfig);

    return true;
}

bool CwnCommandGetClass::interpretAnswerForPackageLoad(QVariantList &dataList){

    //qDebug() << dataList;
    if(dataList.count()>0)
    {
        QVariantMap listMapPosAndName = dataList[0].toMap();
        QVariantList list = listMapPosAndName["row"].toList();
        QVariantList erglist = list[0].toList();

        QString pkgString;
        //qDebug() << list;
        for(int i=0;i<erglist.count()-1;i++)
        {
            pkgString += QString(erglist[i].toString());
            pkgString += QString(".");
        }
        //qDebug() << pkgString;

        if (m_rpClassManager && pkgString.size()!=0)
        {
            pkgString = pkgString.left(pkgString.size()-1);
            CdmDataAccessHelper::AddPackageToClass(m_rpClassManager, m_rpClass, pkgString);
        }
    }
    else
    {
        INFO("Class is not in a package!");
    }

    //qDebug() << dataList;
    return true;
}

void CwnCommandGetClass::interpretAnswer(QVariant &Ret)
{
    //qDebug() << answer;
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
        Ret=0;
    }
    else
    {
/*
        QVariantList results= qResult["results"].toList();
        QVariantMap dataClass = results[0].toMap();
        QVariantList dataListClass = dataClass["data"].toList();
        QVariantMap dataPMembers = results[1].toMap();
        QVariantList dataListPMembers = dataPMembers["data"].toList();
        QVariantMap dataBaseClass = results[2].toMap();
        QVariantList dataListBaseClass = dataBaseClass["data"].toList();
        QVariantMap dataGroups = results[3].toMap();
        QVariantList dataListGroups = dataGroups["data"].toList();
        QVariantMap dataMembers = results[4].toMap();
        QVariantList dataListMembers = dataMembers["data"].toList();
        QVariantMap dataValid = results[5].toMap();
        QVariantList dataListValid = dataValid["data"].toList();
        QVariantMap dataMethods = results[6].toMap();
        QVariantList dataListMethods = dataMethods["data"].toList();
        QVariantMap dataPackage = results[7].toMap();
        QVariantList dataListPackage = dataPackage["data"].toList();

        bRet = bRet && interpretAnswerForClassLoad(dataListClass);
        bRet = bRet && interpretAnswerForPosAndMembers(dataListPMembers);
        bRet = bRet && interpretAnswerForBaseClasses(dataListBaseClass);
        bRet = bRet && interpretAnswerForLoadGroups(dataListGroups);
        bRet = bRet && interpretAnswerForLoadMembers(dataListMembers);
        bRet = bRet && interpretAnswerForLoadValidators(dataListValid);
        bRet = bRet && interpretAnswerForLoadMethods(dataListMethods);
        bRet = bRet && interpretAnswerForPackageLoad(dataListPackage);

        if(!bRet)
        {
            Ret=0;
        }

        if(bRet)
        {
            Ret=1;
            //Loaded Class stuff
        }
        */
    }
}

QString CwnCommandGetClass::createQueryForLoadMethods()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (c:Class)-[r:Class_Method]->(w:WMS_CLASS_METHOD) WHERE id(c)=%1 RETURN id(w),w")
                        .arg(m_lClassId);
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForLoadValidators()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (c:Class)-[r:Class_Validator]->(w:WMS_CLASS_VALIDATION) WHERE id(c)=%1 RETURN id(w),w")
                        .arg(m_lClassId);
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForLoadMembers()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:WMS_Member]->(i:WMS_CLASS_MEMBER) WHERE id(c)=%1 WITH s,i OPTIONAL MATCH (i)<-[:group_has_member]-(g:WMS_CLASS_GROUP) OPTIONAL MATCH (i)-[:ClassRef]->(l:Class) OPTIONAL MATCH (i)<-[:createdMember]-(u:User) OPTIONAL MATCH (i)<-[:modifiedMember]-(v:User) RETURN id(g),id(l),id(u),id(v),id(i),id(s),i")
                        .arg(m_lClassId);
    //qDebug() << qstrQuery;
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForLoadGroups()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (c:Class)-[r:class_group]->(i:WMS_CLASS_GROUP) WHERE id(c)=%1 RETURN id(i),i")
                        .arg(m_lClassId);
    //qDebug() << qstrQuery;
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForBaseClasses()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (c:Class)-[r:BaseClassIs]->(k:Class) WHERE id(c)=%1 RETURN id(k)")
                        .arg(m_lClassId);
    //qDebug() << qstrQuery;
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForPosAndMembers()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (c:Class)-[r:WMS_Member]->(m:WMS_CLASS_MEMBER) WHERE id(c)=%1 RETURN r.pos,m.Keyname;")
                        .arg(m_lClassId);
    //qDebug() << qstrQuery;
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForClassLoad()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (c:Class)<-[h:hasClass]-(s:Scheme) WHERE id(c)=%1 OPTIONAL MATCH (c)<-[:ClassModifier]-(m:User) OPTIONAL MATCH (c)<-[:ClassCreator]-(e:User) RETURN id(c),c,id(s),id(m),id(e);")
                        .arg(m_lClassId);
    //qDebug() << qstrQuery;
    return qstrQuery;
}
QString CwnCommandGetClass::createQueryForLoadPackageString()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH k=(s:Scheme)-[:pkglevel *]->(:Package)-[:Pkg_Contains_Class]->(c:Class) WHERE id(c)=%1 AND id(s)=%2 RETURN tail(extract(n IN nodes(k)| n.URIname)) AS pkgString;")
            .arg(m_lClassId)
            .arg(m_rpClassManager->GetSchemeId());
    return qstrQuery;
}

int CwnCommandGetClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    //qDebug() << createQuery();


    payload += startJsonWCommand(createQueryForClassLoad());
    payload += addJsonCommand(createQueryForPosAndMembers());
    payload += addJsonCommand(createQueryForBaseClasses());
    payload += addJsonCommand(createQueryForLoadGroups());
    payload += addJsonCommand(createQueryForLoadMembers());
    payload += addJsonCommand(createQueryForLoadValidators());
    payload += addJsonCommand(createQueryForLoadMethods());
    payload += addJsonCommand((createQueryForLoadPackageString()));
    payload += endJsonCommand();

    //qDebug() << payload;
    queryCausedError = payload;
    //ERR(payload);

    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    m_rpClass->ResetNewModified();

    if (m_rpClassManager)
    {
        CdmDataAccessHelper::AddClass(m_rpClassManager, m_rpClass);
    }


    INFO ("Reset Flags");
    iRet = Ret.toInt();

    return iRet;
}

CdmClass *CwnCommandGetClass::GetResult()
{
    return m_rpClass;
}


bool CwnCommandGetClass::CheckValid()
{
    return (m_lClassId > 0);
}
