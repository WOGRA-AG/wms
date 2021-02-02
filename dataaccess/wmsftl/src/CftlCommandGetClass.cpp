
// WMS Includes
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmClassGroup.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmClassValidator.h"
#include "CdmMember.h"

// own Includes
#include "CftlCommandGetClass.h"

CftlCommandGetClass::CftlCommandGetClass(CdmClassManager* p_ppClassManager, long p_lClassId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_lClassId(p_lClassId),
      m_rpClass(nullptr),
      m_rpClassManager(p_ppClassManager)
{
}

CftlCommandGetClass::~CftlCommandGetClass()
{
}

int CftlCommandGetClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

    // query for reading new id
    cQSqlQuery.prepare("select ClassId, Keyname, LastChange, SchemeId, Caption, Comment, PositionSequence, Abstract, CaptionMember, Version, Package_URI, config"
                       " from WMS_CLASS where ClassId = ?");
    cQSqlQuery.addBindValue((int)m_lClassId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        cQSqlQuery.first();
        if(cQSqlQuery.isValid())
        {
            // first step reading the WMS_Class data
            long lClassId        = cQSqlQuery.value(0).toInt();
            QString qstrKeyname  = cQSqlQuery.value(1).toString();
            QDateTime qdLastChange = cQSqlQuery.value(2).toDateTime();
            long    lSchemeId  = cQSqlQuery.value(3).toInt();
            QString qstrCaption  = cQSqlQuery.value(4).toString();
            QString qstrComment  = cQSqlQuery.value(5).toString();
            QString qstrPositionSequence = cQSqlQuery.value(6).toString();
            bool bAbstract = cQSqlQuery.value(7).toBool();
            long lCaptionMember = cQSqlQuery.value(8).toInt();
            int iVersion = cQSqlQuery.value(9).toInt();
            QString qstrPackage = cQSqlQuery.value(10).toString();
            QString qstrConfig = cQSqlQuery.value(11).toString();

            // second step creating class object
            m_rpClass = CdmDataAccessHelper::CreateClass(lSchemeId, lClassId, qstrKeyname);
            m_rpClass->SetComment(qstrComment);
            m_rpClass->SetCaption(qstrCaption);
            m_rpClass->SetAbstract(bAbstract);
            m_rpClass->SetVersion(iVersion);
            m_rpClass->SetMemberSequenceString(qstrPositionSequence);
            m_rpClass->SetConfig(qstrConfig);

            if (m_rpClassManager)
            {
                CdmDataAccessHelper::AddPackageToClass(m_rpClassManager, m_rpClass, qstrPackage);
            }

            INFO ("Loading Baseclasses from class '" + qstrKeyname + "'");
            // third step loading base classes data
            LoadBaseClasses(m_rpClass);

            INFO ("Loading Members from class '" + qstrKeyname + "'");
            // fourth step loading Value
            LoadGroups(m_rpClass);
            LoadMembers(m_rpClass);
            LoadMethods(m_rpClass);
            LoadValidators(m_rpClass);

            m_rpClass->SetCaptionMember(lCaptionMember);
            // fifth step reset flags
            m_rpClass->ResetNewModified();
            m_rpClass->SetLastChange(qdLastChange);
            INFO ("Reset Flags '" + qstrKeyname + "'");

            if (m_rpClassManager)
            {
                CdmDataAccessHelper::AddClass(m_rpClassManager, m_rpClass);
            }

            iRet = EC(eDmOk);
        }
        else
        {
            iRet = EC(eDmKeynameAlreadyExists);
            ERR("More than one class with the same Keyname!!!");
        }
    }
    else
    {
        iRet = EC(eDmInvalidSelectStatement);
        ERR("Class Select pronounced an error.");
    }


    return iRet;
}

long CftlCommandGetClass::LoadBaseClasses(CdmClass* p_pCdmClass)
{
    long lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(p_pCdmClass))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());
        cQSqlQuery.prepare("select BaseClassID from WMS_CLASS_BASECLASS where ClassId = ?");
        cQSqlQuery.addBindValue((int)p_pCdmClass->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            cQSqlQuery.first();

            if(cQSqlQuery.isValid())
            {
                do // loading each class
                {
                    long lBaseClassId = cQSqlQuery.value(0).toInt();
                    CdmDataAccessHelper::AddBaseClassToClass(p_pCdmClass, lBaseClassId);
                }
                while(cQSqlQuery.next());

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
    }

    return lRet;
}

long CftlCommandGetClass::LoadMembers(CdmClass* p_pCdmClass)
{
    long lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(p_pCdmClass))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());


        // query for reading new id
        cQSqlQuery.prepare("select me.MemberId, me.DataType, me.Must, me.Size, me.ObjectRefClassId, "
                           "me.CounterStart, me.ClassId, me.DefaultValue, me.Keyname, me.Caption, "
                           "me.CreatorId, me.ModifierId, me.Comment, cl.SchemeId, me.Owner, me.Explicit, "
                           "me.System, me.Access, me.groupId, me.version, me.validation, me.non_persistent, me.Is_Tree, me.config "
                           "from WMS_CLASS_MEMBER me, WMS_SCHEME db, WMS_CLASS cl "
                           "where me.ClassId = ? and cl.ClassId = me.ClassId and "
                           "db.schemeid = cl.schemeid");
        cQSqlQuery.addBindValue((int)p_pCdmClass->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            QList<CdmMember*> qlMembers;
            cQSqlQuery.first();
            if(cQSqlQuery.isValid())
            {
                do // loading each member
                {
                    long     lId                = cQSqlQuery.value(0).toInt();
                    int      iValue             = cQSqlQuery.value(1).toInt();
                    bool     bMust              = cQSqlQuery.value(2).toBool();
                    long     lSize              = cQSqlQuery.value(3).toInt();
                    long     lRefClassId        = cQSqlQuery.value(4).toInt();
                    long     lCounterSize       = cQSqlQuery.value(5).toInt();
                    long     lClassId           = cQSqlQuery.value(6).toInt();
                    QVariant qvDefaultValue     = cQSqlQuery.value(7);
                    QString  qstrKeyname        = cQSqlQuery.value(8).toString();
                    QString  qstrCaption        = cQSqlQuery.value(9).toString();
                    long     lCreatorId         = cQSqlQuery.value(10).toInt();
                    long     lModifierId        = cQSqlQuery.value(11).toInt();
                    QString  qstrComment        = cQSqlQuery.value(12).toString();
                    long     lDatabaseId        = cQSqlQuery.value(13).toInt();
                    bool     bOwner             = cQSqlQuery.value(14).toBool();
                    bool     bUnique            = cQSqlQuery.value(15).toBool();

                    bool     bSystem            =  false;

                    if (cQSqlQuery.value(16).isNull())
                    {
                        bSystem = true;
                    }
                    else
                    {
                        bSystem = cQSqlQuery.value(16).toBool();
                    }


                    int iAccess = 0;

                    if (!cQSqlQuery.value(17).isNull())
                    {
                        iAccess = cQSqlQuery.value(17).toInt();
                    }

                    long lGroupId = 0;

                    if (!cQSqlQuery.isNull(18))
                    {
                        lGroupId = cQSqlQuery.value(18).toInt();
                    }

                    int iVersion = 0;

                    if (!cQSqlQuery.isNull(19))
                    {
                        iVersion = cQSqlQuery.value(19).toInt();
                    }

                    QString  qstrValidation;

                    if (!cQSqlQuery.isNull(20))
                    {
                        qstrValidation = cQSqlQuery.value(20).toString();
                    }

                    bool bNonPersistent = cQSqlQuery.value(21).toBool();
                    bool bTree = cQSqlQuery.value(22).toBool();
                    QString qstrConfig = cQSqlQuery.value(23).toString();

                    CdmMember* pCdmMember = nullptr;

                    INFO ("Creating Member '" + qstrKeyname + "'");
                    pCdmMember = CdmDataAccessHelper::CreateMember(lDatabaseId,
                                                                   lId,
                                                                   qstrKeyname,
                                                                   iValue,
                                                                   bMust,
                                                                   lSize);

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
                    pCdmMember->SetMemberAccess((EdmMemberAccess)iAccess);
                    pCdmMember->SetGroup(p_pCdmClass->FindGroupById(lGroupId));
                    pCdmMember->SetVersion(iVersion);
                    pCdmMember->SetValidationCode(qstrValidation);
                    pCdmMember->SetPersistent(!bNonPersistent);
                    pCdmMember->SetTree(bTree);
                    pCdmMember->SetConfig(qstrConfig);
                    qlMembers.append(pCdmMember);
                }
                while(cQSqlQuery.next());

                for (int iCounter = 0; iCounter < qlMembers.count(); ++iCounter)
                {
                    CdmMember* pCdmMember = qlMembers[iCounter];
                    GetDataAccess()->LoadRights(pCdmMember->GetRights(), pCdmMember->GetId(), "WMS_CLASS_MEMBER_RIGHTS", "MemberId");
                    INFO ("Adding Member '" + pCdmMember->GetKeyname() + "' to class '" + p_pCdmClass->GetKeyname() + "'");
                    CdmDataAccessHelper::AddMemberToClass(p_pCdmClass, pCdmMember);
                    LoadTranslations(pCdmMember);
                    pCdmMember->ResetNewModified();
                }

                lRet = EC(eDmOk);
            }
            else
            {
                cQSqlQuery.first();
                if(cQSqlQuery.isValid())
                {
                    lRet = EC(eDmOk);
                    INFO("No class members found for this class!!!");
                }
                else
                {
                    lRet = EC(eDmInvalidSqlResult);
                }
            }
        }
        else
        {
            lRet = EC(eDmInvalidSelectStatement);
            ERR("Base Class Query pronounced an error!!!");
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

void CftlCommandGetClass::LoadTranslations(CdmMember* p_pCdmMember)
{
    if (CHKPTR(p_pCdmMember))
    {
        QSqlQuery cQuery(GetSqlDatabase());
        cQuery.prepare("select Language, Caption, Comment from WMS_CLASS_MEMBER_TRANSLATION where MemberId = ?");
        cQuery.addBindValue((int)p_pCdmMember->GetId());

        if (SUCCESSFULL(ExecuteQuery(cQuery)))
        {
            cQuery.first();
            while(cQuery.isValid())
            {
                QString qstrLanguage = cQuery.value(0).toString();
                QString qstrCaption = cQuery.value(1).toString();
                QString qstrComment = cQuery.value(2).toString();
                p_pCdmMember->SetTranslation(qstrLanguage, qstrCaption, qstrComment);
                cQuery.next();
            }
        }
        else
        {
            ERR("Select failed!");
        }
    }
}

void CftlCommandGetClass::LoadGroups(CdmClass* p_pCdmClass)
{
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("select Id, Name, Version, Position, Parent from WMS_CLASS_GROUP where classid = ?");
    cQuery.addBindValue((int)p_pCdmClass->GetId());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        cQuery.first();
        QList<CdmClassGroup*> qlGroups;
        while(cQuery.isValid())
        {
            long lGroupId = cQuery.value(0).toInt();
            QString qstrName = cQuery.value(1).toString();
            int iVersion = cQuery.value(2).toInt();
            int iPosition = cQuery.value(3).toInt();
            int iParent = cQuery.value(4).toInt();

            CdmClassGroup* pCdmGroup = p_pCdmClass->CreateGroup(qstrName, iVersion, iPosition, nullptr);

            if (CHKPTR(pCdmGroup))
            {
                qlGroups.append(pCdmGroup);
                pCdmGroup->SetId(lGroupId);
                pCdmGroup->SetPosition(iPosition);
                pCdmGroup->SetParentId(iParent);
            }

            cQuery.next();
        }

        for (int iCounter = 0; iCounter < qlGroups.count(); ++iCounter)
        {
            CdmClassGroup* pCdmGroup = qlGroups[iCounter];
            GetDataAccess()->LoadRights(pCdmGroup->GetRights(),
                                        pCdmGroup->GetId(),
                                        "WMS_CLASS_GROUP_RIGHTS",
                                        "GroupId");

            LoadGroupTranslations(pCdmGroup);
        }
    }
}

void CftlCommandGetClass::LoadGroupTranslations(CdmClassGroup* p_pCdmGroup)
{

    if (CHKPTR(p_pCdmGroup))
    {
        QSqlQuery cQuery(GetSqlDatabase());
        cQuery.prepare("select Language, Caption from WMS_CLASS_GROUP_TRANSLATION where GroupId = ?");
        cQuery.addBindValue(p_pCdmGroup->GetId());

        if (SUCCESSFULL(ExecuteQuery(cQuery)))
        {
            cQuery.first();
            while(cQuery.isValid())
            {
                QString qstrLanguage = cQuery.value(0).toString();
                QString qstrCaption = cQuery.value(1).toString();
                p_pCdmGroup->SetTranslation(qstrLanguage, qstrCaption);
                cQuery.next();
            }
        }
        else
        {
            ERR("Select failed!");
        }
    }
}


void CftlCommandGetClass::LoadValidators(CdmClass* p_pCdmClass)
{
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("select Id, Name, Version, Code, ValidationType, Message from WMS_CLASS_VALIDATION where classid = ?");
    cQuery.addBindValue((int)p_pCdmClass->GetId());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        cQuery.first();
        while(cQuery.isValid())
        {
            long lValidationId = cQuery.value(0).toInt();
            QString qstrName = cQuery.value(1).toString();
            int iVersion = cQuery.value(2).toInt();
            QString qstrCode = cQuery.value(3).toString();
            EdmValidationType eDmType = (EdmValidationType)cQuery.value(4).toInt();
            QString qstrMessage = cQuery.value(5).toString();

            CdmClassValidator* pCdmValidator = p_pCdmClass->CreateValidator(qstrName);
            pCdmValidator->SetId(lValidationId);
            pCdmValidator->SetVersion(iVersion);
            pCdmValidator->SetCode(qstrCode);
            pCdmValidator->SetValidationType(eDmType);
            pCdmValidator->SetMessage(qstrMessage);

            cQuery.next();
        }
    }
}

void CftlCommandGetClass::LoadMethods(CdmClass* p_pCdmClass)
{
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("select Id, Name, Version, Code, MethodType, AccessMode, Parameters, Comment, Icon, Caption, Static from WMS_CLASS_METHOD where classid = ?");
    cQuery.addBindValue((int)p_pCdmClass->GetId());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        QList<CdmClassMethod*> qlMethods;
        cQuery.first();
        while(cQuery.isValid())
        {
            long lMethodId = cQuery.value(0).toInt();
            QString qstrName = cQuery.value(1).toString();
            int iVersion = cQuery.value(2).toInt();
            QString qstrCode = cQuery.value(3).toString();
            EdmValueType eDmType = (EdmValueType)cQuery.value(4).toInt();
            EdmMemberAccess eDmAccess = (EdmMemberAccess)cQuery.value(5).toInt();
            QString qstrParameters = cQuery.value(6).toString();
            QString qstrComment = cQuery.value(7).toString();
            QString qstrIcon = cQuery.value(8).toString();
            QString qstrCaption = cQuery.value(9).toString();
            bool bStatic = cQuery.value(10).toBool();

            CdmClassMethod* pCdmMethod = p_pCdmClass->CreateMethod(lMethodId, qstrName, eDmType, eDmAccess, qstrCode, iVersion);
            qlMethods.append(pCdmMethod);
            pCdmMethod->SetParameters(qstrParameters);
            pCdmMethod->SetComment(qstrComment);
            pCdmMethod->SetStatic(bStatic);
            pCdmMethod->SetCaption(qstrCaption);
            QByteArray qbaIcon = QByteArray::fromBase64(qstrIcon.toLocal8Bit());
            pCdmMethod->SetIcon(qbaIcon);
            cQuery.next();
        }

        for (int iCOunter = 0; iCOunter < qlMethods.count(); ++iCOunter)
        {
            CdmClassMethod* pCdmMethod = qlMethods[iCOunter];

            GetDataAccess()->LoadRights(pCdmMethod->GetRights(),
                                        pCdmMethod->GetId(),
                                        "WMS_CLASS_METHOD_RIGHTS",
                                        "MethodId");
        }
    }
}


CdmClass *CftlCommandGetClass::GetResult()
{
    return m_rpClass;
}

bool CftlCommandGetClass::CheckValid()
{
    return (m_lClassId > 0);
}
