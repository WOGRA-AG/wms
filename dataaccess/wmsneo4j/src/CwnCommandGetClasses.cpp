#include <qiterator.h>
#include <QListIterator>
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
#include "CwnCommandGetClasses.h"
#include "CwnCommandLoadGroupTranslations.h"
#include "CwnCommandLoadTranslation.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetClasses::CwnCommandGetClasses(CdmClassManager *p_ppClassManager, QLinkedList<long> &p_lClassIds, CwnDataAccess *p_pDataAccess):
    CwnCommandBase(p_pDataAccess),
    m_rpClass(nullptr),
    m_rpClassManager(p_ppClassManager)

{
    m_qstrClassIds = GetDataAccess()->GenerateInString(p_lClassIds);
}

CwnCommandGetClasses::~CwnCommandGetClasses()
{
}

long CwnCommandGetClasses::interpretAnswerForLoadMembers(const QVariantList* dataList,long &ldatabaseid, long &lclassid)
{

    long lRet = -1;
    QMap<long,QString> ForPosAndMembers;

    if(CHKPTR(m_rpClass))
    {
        QVariantList::ConstIterator itc;
        for(itc=dataList->begin();itc!=dataList->end();++itc)
        {
            const QVariantMap* map = static_cast<const QVariantMap*>(itc->data());

            if(!map->value("id").isValid()){
                lRet = EC(eDmOk);
                INFO("No class members found for this class!");
                return true;//no Members
            }

            long lId = map->value("id").toInt();
            const QVariantMap* props= static_cast<const QVariantMap*>(map->find("props")->data());

            QVariantMap::ConstIterator it = props->begin();

            int iAccess = 0;
            if (props->contains("Access"))
                iAccess = it++->toInt();

            QString  qstrCaption        = it++->toString();

            int      propClassRef       = 0;
            if(props->contains("ClassRef"))
                propClassRef = it++->toInt();

            QString  qstrComment        = it++->toString();

            QString qstrConfig;
            if(props->contains("Config"))
                qstrConfig = CwnHelper::base64_decode(it++->toString());

            long     lCounterSize       = 0;
            if(props->contains("CounterStart"))
                lCounterSize = it++->toInt();

            int      iValue             = it++->toInt();
            QVariant qvDefaultValue     = it++.value();
            bool bExplicit              = it++->toBool();
            bool bTree                  = it++->toBool();
            QString  qstrKeyname        = it++->toString();
            bool     bMust              = it++->toBool();
            bool bNonPersistent         = it++->toBool();
            bool     bOwner             = it++->toBool();
            long     lSize              = it++->toInt();

            bool     bSystem            = true;
            bool     bUnique            = false;
            if(props->contains("System"))
                bSystem = it++->toBool();

            if(props->contains("Unique")){
                bUnique= it++->toBool();bSystem=false;
            }

            QString  qstrValidation;
            if (props->contains("Validation"))
                qstrValidation = CwnHelper::base64_decode(it++->toString());

            int iVersion = 0;
            if (props->contains("Version"))
                iVersion = it++->toInt();

            ForPosAndMembers.insert(map->find("pos")->toLongLong(),qstrKeyname);

            const QVariant* VGroupId = static_cast<const QVariant*>(map->find("groupId")->data());
            int lGroupId=0;
            if (!VGroupId->isNull())
                lGroupId = VGroupId->toInt();

            const QVariant* VRefClassId = static_cast<const QVariant*>(map->find("refClassId")->data());
            long lRefClassId = 0;
            if (!VRefClassId->isNull())
                lRefClassId = VRefClassId->toInt();
            else if(propClassRef != 0)
                lRefClassId = propClassRef;

            long lCreatorId = map->value("creator").toLongLong();
            long lModifierId = map->value("modifier").toLongLong();

            CdmMember* pCdmMember = nullptr;

            INFO ("Creating Member '" + qstrKeyname + "'");
            pCdmMember = CdmDataAccessHelper::CreateMember(ldatabaseid,
                                                            lId,
                                                            qstrKeyname,
                                                            iValue,
                                                            bMust,
                                                            static_cast<int>(lSize));

            pCdmMember->SetCaption(qstrCaption);
            CdmDataAccessHelper::SetCreatorId(pCdmMember, lCreatorId);
            CdmDataAccessHelper::SetModifierId(pCdmMember, lModifierId);
            CdmDataAccessHelper::SetMemberClassId(pCdmMember, lclassid);
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

            const QVariantList* langlist = static_cast<const QVariantList*>(map->find("langs")->data());
            for(int i=0;i<langlist->count();i++)
            {
                const QVariantList* langlistparams = static_cast<const QVariantList*>(langlist->at(i).data());
                if(langlistparams->at(0).isValid())
                {
                    QString qstrComment = langlistparams->at(0).toString();
                    QString qstrCaption  = langlistparams->at(1).toString();
                    QString qstrLanguage = langlistparams->at(2).toString();
                    pCdmMember->SetTranslation(qstrLanguage, qstrCaption, qstrComment);
                }
                else
                   break;//no Languages
            }

            const QVariantList* rightslist = static_cast<const QVariantList*>(map->find("rights")->data());
            for(int i=0;i<rightslist->count();i++)
            {
                const QVariantList* rightslistparams = static_cast<const QVariantList*>(rightslist->at(i).data());
                if(rightslistparams->at(0).isValid())
                {
                    pCdmMember->GetRights().AddRight(rightslistparams->at(0).toInt(),static_cast<EdmRight>(rightslistparams->at(1).toInt()));
                }
                else
                   break;//no rights
            }


            INFO ("Adding Member '" + pCdmMember->GetKeyname() + "' to class '" + m_rpClass->GetKeyname() + "'");
            CdmDataAccessHelper::AddMemberToClass(m_rpClass, pCdmMember);
            pCdmMember->ResetNewModified();

            lRet = EC(eDmOk);

        }

        m_rpClass->SetMemberSequenceString(ForPosAndMembers);
    }
    return lRet;
}

bool CwnCommandGetClasses::interpretAnswerForLoadMethods(const QVariantList* dataList)
{
    QVariantList::ConstIterator itc;
    for(itc=dataList->begin();itc!=dataList->end();++itc)
    {
        const QVariantMap* map = static_cast<const QVariantMap*>(itc->data());

        if(!map->value("id").isValid())
        {
            return true;//no METHODS
        }

        long lMethodId = map->find("id")->toInt();
        const QVariantMap* props= static_cast<const QVariantMap*>(map->find("props")->data());
        QVariantMap::ConstIterator it = props->begin();

        QString qstrCaption = it++->toString();
        QString qstrCode = it++->toString();
        QString qstrComment = it++->toString();
        EdmMemberAccess eDmAccess = static_cast<EdmMemberAccess>(it++->toInt());
        EdmValueType eDmType = static_cast<EdmValueType>(it++->toInt());
        QString qstrIcon = QString(it++->toString().data());
        QString qstrName = it++->toString();
        QString qstrParameters = it++->toString();
        bool bStatic = it++->toBool();
        int iVersion = it++->toInt();


        CdmClassMethod* pCdmMethod = m_rpClass->CreateMethod(static_cast<int>(lMethodId), qstrName, eDmType, eDmAccess, qstrCode, iVersion);
        pCdmMethod->SetParameters(qstrParameters);
        pCdmMethod->SetComment(qstrComment);
        pCdmMethod->SetStatic(bStatic);
        pCdmMethod->SetCaption(qstrCaption);
        QByteArray qbaIcon = QByteArray::fromBase64(qstrIcon.toLocal8Bit());
        pCdmMethod->SetIcon(qbaIcon);

        const QVariantList* rightslist = static_cast<const QVariantList*>(map->find("rights")->data());
        for(int i=0;i<rightslist->count();i++)
        {
            const QVariantList* rightslistparams = static_cast<const QVariantList*>(rightslist->at(i).data());
            if(rightslistparams->at(0).isValid())
            {
                pCdmMethod->GetRights().AddRight(rightslistparams->at(0).toInt(),static_cast<EdmRight>(rightslistparams->at(1).toInt()));
            }
            else
               break;//no rights
        }
    }

    return true;
}
bool CwnCommandGetClasses::interpretAnswerForLoadValidators(const QVariantList* dataList)
{
    if(dataList->count()>0)
    {
        QVariantList::ConstIterator itc;
        for(itc=dataList->begin();itc!=dataList->end();++itc)
        {
            const QVariantList* list = static_cast<const QVariantList*>(itc->data());

            if(!list->at(0).isValid())
                return true;

            long lValidationId = list->at(0).toInt();
            const QVariantMap* props= static_cast<const QVariantMap*>(list->at(1).data());
            QVariantMap::ConstIterator it = props->begin();

            QString qstrCode = it++->toString();
            EdmValidationType eDmType = static_cast<EdmValidationType>(it++->toInt());
            QString qstrMessage = it++->toString();
            QString qstrName = it++->toString();
            int iVersion = it++->toInt();

            CdmClassValidator* pCdmValidator = m_rpClass->CreateValidator(qstrName);
            pCdmValidator->SetId(static_cast<int>(lValidationId));
            pCdmValidator->SetVersion(iVersion);
            pCdmValidator->SetCode(CwnHelper::base64_decode(qstrCode));

            pCdmValidator->SetValidationType(eDmType);
            pCdmValidator->SetMessage(qstrMessage);
            m_rpClass->AddValidator(pCdmValidator);
       }
    }
    else
    {
        INFO("No Validators found for this class!");
    }
    return true;
}
bool CwnCommandGetClasses::interpretAnswerForLoadGroups(const QVariantList* dataList)
{
    //Id, Name, Version, Position, Parent
    //qDebug() << dataList;

    QVariantList::ConstIterator itc;
    for(itc=dataList->begin();itc!=dataList->end();++itc)
    {
        const QVariantMap* map = static_cast<const QVariantMap*>(itc->data());

        if(!map->value("id").isValid())
            return true;//no GROUPS

        long lGroupId = map->value("id").toInt();

        const QVariantMap* props= static_cast<const QVariantMap*>(map->value("props").data());

        QVariantMap::ConstIterator it = props->begin();

        QString qstrName = it++->toString();

        int iParent=0;
        if (props->contains("Parent"))
            iParent = it++->toInt();

        int iPosition = it++->toInt();
        int iVersion = it++->toInt();

        CdmClassGroup* pCdmGroup = m_rpClass->CreateGroup(qstrName, iVersion, iPosition, nullptr);

        if (CHKPTR(pCdmGroup))
        {
            pCdmGroup->SetId(static_cast<int>(lGroupId));
            pCdmGroup->SetPosition(iPosition);
            pCdmGroup->SetParentId(iParent);
        }

        const QVariantList* langlist = static_cast<const QVariantList*>(map->find("langs")->data());
        for(int i=0;i<langlist->count();i++)
        {
            const QVariantList* langlistparams = static_cast<const QVariantList*>(langlist->at(i).data());
            if(langlistparams->at(0).isValid())
            {
                QString qstrCaption = langlistparams->at(0).toString();
                QString qstrLanguage = langlistparams->at(1).toString();
                pCdmGroup->SetTranslation(qstrLanguage,qstrCaption);
            }
            else
               break;//no Languages
        }

        const QVariantList* rightslist = static_cast<const QVariantList*>(map->find("rights")->data());
        for(int i=0;i<rightslist->count();i++)
        {
            const QVariantList* rightslistparams = static_cast<const QVariantList*>(rightslist->at(i).data());
            if(rightslistparams->at(0).isValid())
            {
                pCdmGroup->GetRights().AddRight(rightslistparams->at(0).toInt(),static_cast<EdmRight>(rightslistparams->at(1).toInt()));
            }
            else
               break;//no rights
        }
    }

    return true;
}

bool CwnCommandGetClasses::interpretAnswerForBaseClasses(const QVariantList* dataList)
{
    long lRet = -1;

    if(CHKPTR(m_rpClass))
    {
        if(dataList->count()>0)
        {
            QVariantList::ConstIterator it;
            for(it=dataList->begin();it!=dataList->end();++it)
            {
                long lBaseClassId = it->toLongLong();
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

bool CwnCommandGetClasses::interpretAnswerForClassLoad(long &ldatabaseid, long &lclassid, const QVariantList *dataList)
{
    // first step reading the WMS_Class data

    const QVariantList* list = static_cast<const QVariantList*>(dataList->at(0).data());

    const QVariantMap* listMap= static_cast<const QVariantMap*>(list->at(0).data());

    QVariantMap::ConstIterator it = listMap->begin();

    bool bAbstract=false;
    QString qstrCaption;
    long lCaptionMember = 0;
    QString qstrComment="";
    QString qstrConfig;
    QString qstrKeyname;
    QDateTime qdLastChange;
    int iVersion = 0;

    // first step reading the WMS_Class data
    if (listMap->contains("Abstract"))
        bAbstract = it++->toBool();

    qstrCaption  = it++->toString();

    if (listMap->contains("CaptionMember"))
        lCaptionMember = it++->toInt();

    if (listMap->contains("Comment"))
        qstrComment  = it++->toString();

    if (listMap->contains("Config"))
        qstrConfig = CwnHelper::base64_decode(it++->toString());

    qstrKeyname = it++->toString();
    qdLastChange = it++->toDateTime();

    if (listMap->contains("Version"))
        iVersion =  it++->toInt();

    long modifier = 0;
    long creator = 0;

    creator = (list->at(1).isValid())?list->at(1).toLongLong():0;
    modifier = (list->at(2).isValid())?list->at(2).toLongLong():0;

    // second step creating class object
    m_rpClass = CdmDataAccessHelper::CreateClass(ldatabaseid, lclassid, qstrKeyname);
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

bool CwnCommandGetClasses::interpretAnswerForPackageLoad(const QVariantList* dataList){

    if(dataList == nullptr)
        return true;

    if(dataList->count()>0)
    {
        QString pkgString;
        QVariantList::ConstIterator it;

        for(it=dataList->begin();it!=dataList->end()-1;++it)
        {
            pkgString += QString(it->toString());
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

QString CwnCommandGetClasses::createQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class) WHERE id(c) IN %1 "
    "OPTIONAL MATCH (c)<-[:ClassModifier]-(cm:User) "
    "WITH s,c "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)<-[:ClassModifier]-(cm:User) "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)<-[:ClassCreator]-(cc:User) "
    "WITH s,c,collect([properties(c),id(cm),id(cc)]) AS classProps "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:BaseClassIs]->(cbc:Class) "
    "WITH s,c,classProps,collect(id(cbc)) AS classbaseProps "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:class_group]->(cg:WMS_CLASS_GROUP) OPTIONAL MATCH (cg)-[trans:WMS_ClassGroup_Translation]->(l:WMS_LANGUAGES) OPTIONAL MATCH (cg)-[r:rights]->(u) "
    "WITH s,c,classProps,classbaseProps,{id:id(cg),props:properties(cg),langs:collect(DISTINCT [trans.caption,l.language]),rights:collect(DISTINCT [id(u),r.rightId])} AS groupList "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:Class_Validator]->(cv:WMS_CLASS_VALIDATION) "
    "WITH s,c,classProps,classbaseProps,groupList,collect([id(cv),properties(cv)]) AS classvalProps "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:Class_Method]->(cmet:WMS_CLASS_METHOD) OPTIONAL MATCH (cmet)-[b:rights]->(u) "
    "WITH s,c,classProps,classbaseProps,groupList,classvalProps,{id:id(cmet),props:properties(cmet),rights:collect(DISTINCT [id(u),b.rightId])} AS classMethods "
    "OPTIONAL MATCH k=(s)-[:pkglevel *]->(:Package)-[:Pkg_Contains_Class]->(c) "
    "WITH s,c,classProps,classbaseProps,groupList,classvalProps,classMethods,tail(extract(n IN nodes(k)| n.URIname)) AS classPackages "
    "OPTIONAL MATCH (s)-[:hasClass]->(c)-[r:WMS_Member]->(i) "
    "WITH s,c,classProps,classbaseProps,groupList,classvalProps,classMethods,classPackages,r,i "
    "OPTIONAL MATCH (i)<-[:group_has_member]-(ig:WMS_CLASS_GROUP) "
    "OPTIONAL MATCH (i)-[:ClassRef]->(irc:Class) "
    "OPTIONAL MATCH (i)<-[:CreatedMember]-(icm:User) OPTIONAL MATCH (i)<-[:ModifiedMember]-(imm:User) OPTIONAL MATCH (i)-[trans:WMS_ClassMember_Translation]->(l:WMS_LANGUAGES) OPTIONAL MATCH (i)-[k:rights]->(u) "
    "WITH s,c,classProps,classbaseProps,groupList,classvalProps,classMethods,classPackages,{id:id(i),pos:r.pos,props:properties(i),groupId:id(ig),refClassId:id(irc),creator:id(icm),modifier:id(imm),langs:collect(DISTINCT [ trans.Comment,trans.Caption,l.language]),rights:collect(DISTINCT [id(u),k.rightId])} AS memberProps "
    "RETURN DISTINCT id(s),id(c),classProps,classbaseProps,collect(DISTINCT groupList),classvalProps,collect(DISTINCT classMethods),classPackages,collect(DISTINCT memberProps);")
    .arg(m_qstrClassIds);

    return qstrQuery;
}

void CwnCommandGetClasses::interpretAnswer(QVariant &Ret)
{
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
               const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

               QList<QVariant>::ConstIterator itc;
               itc=row->begin();

               long schemeId=itc++->toLongLong();
               long classId=itc++->toLongLong();
               const QVariantList* classloadlist =static_cast<const QVariantList*>(itc++->data());
               const QVariantList* baseclasslist =static_cast<const QVariantList*>(itc++->data());
               const QVariantList* grouplist =static_cast<const QVariantList*>(itc++->data());
               const QVariantList* validlist =static_cast<const QVariantList*>(itc++->data());
               const QVariantList* methodslist =static_cast<const QVariantList*>(itc++->data());
               const QVariantList* packagelist = ((itc->isValid())?static_cast<const QVariantList*>(itc->data()):nullptr);
               itc++;
               const QVariantList* memberlist =((itc->isValid())?static_cast<const QVariantList*>(itc->data()):nullptr);

               bRet = bRet && interpretAnswerForClassLoad(schemeId,classId,classloadlist);
               bRet = bRet && interpretAnswerForBaseClasses(baseclasslist);
               bRet = bRet && interpretAnswerForLoadGroups(grouplist);
               bRet = bRet && interpretAnswerForLoadValidators(validlist);
               bRet = bRet && interpretAnswerForLoadMethods(methodslist);
               bRet = bRet && interpretAnswerForPackageLoad(packagelist);
               bRet = bRet && interpretAnswerForLoadMembers(memberlist,schemeId,classId);

               m_rpClass->ResetNewModified();
               if (m_rpClassManager)
               {
                    CdmDataAccessHelper::AddClass(m_rpClassManager, m_rpClass);
               }
               m_rpClass=nullptr;
           }
        }

        if(bRet)
        {
           Ret=1;
        }
        else
        {
           Ret=-1;
           ERR("Could not load a class.");
        }
    }

}

int CwnCommandGetClasses::Execute()
{
    //qDebug()<<m_qstrClassIds;

    long lRet = -1;
    //qDebug() << createQuery();
    QString payload = createJson(createQuery());

    //qDebug() << payload;
    queryCausedError = payload;
    //ERR(payload);

    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);

    INFO ("Reset Flags");
    lRet = Ret.toInt();

    return lRet;
}

bool CwnCommandGetClasses::CheckValid()
{
    return !(m_qstrClassIds.isEmpty());
}
