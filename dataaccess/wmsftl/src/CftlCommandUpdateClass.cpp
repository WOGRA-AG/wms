//System and Qt Includes
#include <QStringBuilder>

// WMS Includes
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmScheme.h"
#include "CdmPackage.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClassMethod.h"
#include "CdmClassValidator.h"
#include "CdmClass.h"

// Own Includes
#include "CftlContainerTableAlter.h"
#include "CftlContainerTableCreate.h"
#include "CftlCommandUpdateClass.h"




CftlCommandUpdateClass::CftlCommandUpdateClass(CdmClass* p_pClass, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpClass(p_pClass)
{
}

CftlCommandUpdateClass::~CftlCommandUpdateClass()
{
}

int CftlCommandUpdateClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    if (m_rpClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString().isEmpty())
    {
        CftlContainerTableCreate createTable(m_rpClass, GetDialect());
        iRet = createTable.Execute(GetInterface());
    }
    else
    {
        CftlContainerTableAlter alterTable(m_rpClass, GetDialect());
        iRet = alterTable.Execute(GetInterface());
    }

    if (SUCCESSFULL(iRet))
    {

        // First of save the groups for correct ID assignments of members.
        iRet = SaveGroups(m_rpClass);
        // Updating class Data
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
                    if (DeleteMember(pCdmMember->GetId()) > 0)
                    {
                        CdmDataAccessHelper::RemoveMemberFromClass(m_rpClass, pCdmMember);
                    }
                    else
                    {
                        ERR("Coulds not delete member!!")
                    }
                }
                else if (pCdmMember->IsNew() || pCdmMember->IsModified())
                {
                    InsertOrUpdateMember(pCdmMember, m_rpClass);
                }
            }
        }

        QSqlQuery cQSqlQuery(GetSqlDatabase());
        QString qstrPackage;
        CdmPackage* pPackage = m_rpClass->GetPackage();

        if (pPackage)
        {
            qstrPackage = pPackage->GetUriInternal();
        }

        // Query for creating new entry
        cQSqlQuery.prepare("update WMS_CLASS set Keyname = ?, LastChange = ?, SchemeId = ?, "
                           "CreatorId = ?, ModifierId = ?, Caption = ?, Comment = ?, "
                           "Abstract = ?, PositionSequence = ?, Version = ?, CaptionMember = ?, "
                           "Package_URI = ?, config = ? where ClassId = ?");
        cQSqlQuery.addBindValue(m_rpClass->GetKeyname());
        cQSqlQuery.addBindValue(QDateTime::currentDateTime());
        cQSqlQuery.addBindValue(m_rpClass->GetSchemeId());
        cQSqlQuery.addBindValue(m_rpClass->GetCreatorId());
        cQSqlQuery.addBindValue(m_rpClass->GetModifierId());
        cQSqlQuery.addBindValue(m_rpClass->GetCaption());
        cQSqlQuery.addBindValue(m_rpClass->GetComment());
        cQSqlQuery.addBindValue(m_rpClass->IsAbstract());
        cQSqlQuery.addBindValue(m_rpClass->GetMemberSequenceString());
        cQSqlQuery.addBindValue(m_rpClass->GetVersion());
        cQSqlQuery.addBindValue(m_rpClass->GetCaptionMemberId());
        cQSqlQuery.addBindValue(qstrPackage);
        cQSqlQuery.addBindValue(m_rpClass->GetConfig());
        cQSqlQuery.addBindValue(m_rpClass->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            iRet = InsertOrUpdateBaseClasses(m_rpClass);

            if (iRet == 0) // 0 means no baseclasses found!!!
            {
                iRet = EC(eDmOk);
            }

            m_rpClass->ResetNewModified();
            SaveMethods(m_rpClass);
            SaveValidators(m_rpClass);
        }
        else
        {
            iRet = EC(eDmInvalidUpdateStatement);
        }
    }

    return iRet;
}

bool CftlCommandUpdateClass::CheckValid()
{
    return (CHKPTR(m_rpClass));
}

qint64 CftlCommandUpdateClass::SaveGroups(CdmClass*& p_rCdmClass)
{
   qint64 lRet = CdmLogging::eDmUnknownDbError;

    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("delete from WMS_CLASS_GROUP where classid = ?");
    cQuery.addBindValue(p_rCdmClass->GetId());

    lRet = ExecuteQuery(cQuery);

    if (SUCCESSFULL(lRet))
    {
        const QMap<int, CdmClassGroup*>& qmGrooups = p_rCdmClass->GetClassGroups();

        QMap<int, CdmClassGroup*>::const_iterator qmIt = qmGrooups.begin();
        QMap<int, CdmClassGroup*>::const_iterator qmItEnd = qmGrooups.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            int iParentId = 0;
            CdmClassGroup* pCdmGroup = qmIt.value();

            if (CHKPTR(pCdmGroup))
            {
                int iId = pCdmGroup->GetId();

                if (iId == 0)
                {
                    iId = GetNewIdForClassMembers(p_rCdmClass->GetId(), pCdmGroup->GetName(), "WMS_CLASS_GROUP");

                    if (iId > 0)
                    {
                        cQuery.prepare("update WMS_CLASS_GROUP set ClassId = ?,  Name = ?, Version = ?, Position = ?, Parent = ? where Id = ?");
                        cQuery.addBindValue(p_rCdmClass->GetId());
                        cQuery.addBindValue(pCdmGroup->GetName());
                        cQuery.addBindValue(pCdmGroup->GetVersion());
                        cQuery.addBindValue(pCdmGroup->GetPosition());
                        cQuery.addBindValue(iParentId);
                        cQuery.addBindValue(iId);

                        pCdmGroup->SetId(iId);
                    }
                    else
                    {
                        ERR("Could not acquire new ID.");
                        lRet = CdmLogging::eDmInternalDbError;
                    }
                }
                else
                {
                    cQuery.prepare("insert into WMS_CLASS_GROUP (ClassId, Id, Name, Version, Position, Parent)"
                                   " values (?, ?, ?, ?, ?, ?)");
                    cQuery.addBindValue(p_rCdmClass->GetId());
                    cQuery.addBindValue(iId);
                    cQuery.addBindValue(pCdmGroup->GetName());
                    cQuery.addBindValue(pCdmGroup->GetVersion());
                    cQuery.addBindValue(pCdmGroup->GetPosition());
                    cQuery.addBindValue(iParentId);
                }


                if (SUCCESSFULL( ExecuteQuery(cQuery)))
                {
                    GetDataAccess()->SaveRights(pCdmGroup->GetRights(),
                                                pCdmGroup->GetId(),
                                                "WMS_CLASS_GROUP_RIGHTS",
                                                "GroupId");

                    SaveGroupTranslations(pCdmGroup);
                }

            }
        }
    }

    return lRet;
}

void CftlCommandUpdateClass::SaveMethods(CdmClass*& p_rCdmClass)
{
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("delete from WMS_CLASS_METHOD where classid = ?");
    cQuery.addBindValue(p_rCdmClass->GetId());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        QMap<QString, CdmClassMethod*> qmGrooups = p_rCdmClass->GetMethods();

        QMap<QString, CdmClassMethod*>::iterator qmIt = qmGrooups.begin();
        QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmGrooups.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmClassMethod* pCdmMethod = qmIt.value();

            if (CHKPTR(pCdmMethod))
            {
                int iId = pCdmMethod->GetId();
                QString qstrSql;
                QByteArray qbIcon = pCdmMethod->GetIconAsByteArray();
                QString qstrBase64(qbIcon.toBase64());

                if (iId <= 0)
                {
                    iId = GetNewIdForClassMembers(p_rCdmClass->GetId(), pCdmMethod->GetMethodName(), "WMS_CLASS_METHOD");

                    if (iId > 0)
                    {
                        cQuery.prepare("update WMS_CLASS_METHOD set ClassId = ?, MethodType = ?, Name = ?, Code = ?, Version = ?, AccessMode = ?, Parameters = ?, Comment = ?, Static = ?, "
                                       "Caption = ?, Icon = ? where Id = ?");
                        cQuery.addBindValue(p_rCdmClass->GetId());
                        cQuery.addBindValue(pCdmMethod->GetReturnType());
                        cQuery.addBindValue(pCdmMethod->GetMethodName());
                        cQuery.addBindValue(pCdmMethod->GetSourceCode());
                        cQuery.addBindValue(pCdmMethod->GetVersion());
                        cQuery.addBindValue(pCdmMethod->GetAccess());
                        cQuery.addBindValue(pCdmMethod->GetParametersAsString());
                        cQuery.addBindValue(pCdmMethod->GetComment());
                        cQuery.addBindValue(pCdmMethod->IsStatic());
                        cQuery.addBindValue(pCdmMethod->GetCaption());
                        cQuery.addBindValue(qstrBase64);
                        cQuery.addBindValue(iId);
                    }
                }
                else
                {
                    cQuery.prepare("insert into WMS_CLASS_METHOD (ClassId, MethodType, Name, Code, Version, AccessMode, Parameters, Id, Static, Comment, Caption, Icon)"
                                   " values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
                    cQuery.addBindValue(p_rCdmClass->GetId());
                    cQuery.addBindValue(pCdmMethod->GetReturnType());
                    cQuery.addBindValue(pCdmMethod->GetMethodName());
                    cQuery.addBindValue(pCdmMethod->GetSourceCode());
                    cQuery.addBindValue(pCdmMethod->GetVersion());
                    cQuery.addBindValue(pCdmMethod->GetAccess());
                    cQuery.addBindValue(pCdmMethod->GetParametersAsString());
                    cQuery.addBindValue(iId);
                    cQuery.addBindValue(pCdmMethod->IsStatic());
                    cQuery.addBindValue(pCdmMethod->GetComment());
                    cQuery.addBindValue(pCdmMethod->GetCaption());
                    cQuery.addBindValue(qstrBase64);
                }

                if(SUCCESSFULL(ExecuteQuery(cQuery)))
                {
                    pCdmMethod->SetId(iId);
                    GetDataAccess()->SaveRights(pCdmMethod->GetRights(),
                                                iId,
                                                "WMS_CLASS_METHOD_RIGHTS",
                                                "MethodId");
                }
            }
        }
    }
}

void CftlCommandUpdateClass::SaveValidators(CdmClass*& p_rCdmClass)
{
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("delete from WMS_CLASS_VALIDATION where classid = ?");
    cQuery.addBindValue(p_rCdmClass->GetId());

    if (ExecuteQuery(cQuery) > 0)
    {
        QMap<QString, CdmClassValidator*>& qmValidations = p_rCdmClass->GetValidators();

        QMap<QString, CdmClassValidator*>::iterator qmIt = qmValidations.begin();
        QMap<QString, CdmClassValidator*>::iterator qmItEnd = qmValidations.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmClassValidator* pCdmValidator = qmIt.value();

            if (CHKPTR(pCdmValidator))
            {
                int iId = pCdmValidator->GetId();
                QString qstrSql;

                if (iId == 0)
                {
                    iId = GetNewIdForClassMembers(p_rCdmClass->GetId(), pCdmValidator->GetName(), "WMS_CLASS_VALIDATION");

                    if (iId > 0)
                    {
                        cQuery.prepare("update WMS_CLASS_VALIDATION set ClassId = ?, Name = ?, Code = ?, Version = ?, ValidationType = ?, Message = ? where Id = ?");
                        cQuery.addBindValue(p_rCdmClass->GetId());
                        cQuery.addBindValue(pCdmValidator->GetName());
                        cQuery.addBindValue(pCdmValidator->GetCode());
                        cQuery.addBindValue(pCdmValidator->GetVersion());
                        cQuery.addBindValue(pCdmValidator->GetValidationType());
                        cQuery.addBindValue(pCdmValidator->GetErrorMessage());
                        cQuery.addBindValue(iId);
                    }
                }
                else
                {
                    cQuery.prepare("insert into WMS_CLASS_VALIDATION (ClassId, Name, Code, Version, ValidationType, Message, Id)"
                                   " values (?, ?, ?, ?, ?, ?, ?)");
                    cQuery.addBindValue(p_rCdmClass->GetId());
                    cQuery.addBindValue(pCdmValidator->GetName());
                    cQuery.addBindValue(pCdmValidator->GetCode());
                    cQuery.addBindValue(pCdmValidator->GetVersion());
                    cQuery.addBindValue(pCdmValidator->GetValidationType());
                    cQuery.addBindValue(pCdmValidator->GetErrorMessage());
                    cQuery.addBindValue(iId);
                }

                if (!qstrSql.isEmpty())
                {
                    ExecuteQuery(qstrSql, cQuery);
                }
            }
        }
    }
}

qint64 CftlCommandUpdateClass::InsertOrUpdateMember(CdmMember* p_pCdmMember, CdmClass* p_pCdmClass)
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
    {
        if(p_pCdmMember->IsNew() && !p_pCdmMember->IsDeleted())
        {
            lRet = InsertMember(p_pCdmMember, p_pCdmClass);

            if(lRet <= 0)
            {
                ERR("InsertMember failed!!!");
            }
            else
            {
                SaveTranslations(p_pCdmMember);
                GetDataAccess()->SaveRights(p_pCdmMember->GetRights(), p_pCdmMember->GetId(), "WMS_CLASS_MEMBER_RIGHTS", "MemberId");
            }
        }
        else if(p_pCdmMember->IsModified() && !p_pCdmMember->IsDeleted())
        {
            lRet = UpdateMember(p_pCdmMember, p_pCdmClass);

            if(lRet < 0)
            {
                ERR("UpdateMember failed!!!");
            }
            else
            {
                SaveTranslations(p_pCdmMember);
                GetDataAccess()->SaveRights(p_pCdmMember->GetRights(), p_pCdmMember->GetId(), "WMS_CLASS_MEMBER_RIGHTS", "MemberId");
            }
        }
        else if(p_pCdmMember->IsDeleted())
        {
            lRet = DeleteMember(p_pCdmMember->GetId());

            if(lRet < 0)
            {
                ERR("Delete Member failed!!!");
            }
            else
            {
                DeleteTranslations(p_pCdmMember->GetId());
                GetDataAccess()->DeleteRights(p_pCdmMember->GetId(), "WMS_CLASS_MEMBER_RIGHTS", "MemberId");
            }
        }
    }

    return lRet;
}

qint64 CftlCommandUpdateClass::InsertMember(CdmMember* p_pCdmMember, CdmClass* p_pCdmClass)
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());
        int iGroupId = 0;

        if (p_pCdmMember->GetGroup())
        {
            iGroupId = p_pCdmMember->GetGroup()->GetId();
        }

        // first step insert into WMS_Base table
        // Query for creating new entry
        cQSqlQuery.prepare("insert into WMS_CLASS_MEMBER (Keyname, Datatype, Must, Size, ObjectRefClassId, "
                           "CounterStart, ClassId, DefaultValue, Caption, CreatorId, ModifierId, Comment, "
                           "Owner, Explicit, System, Access, Version, GroupId, Validation, Non_Persistent, Is_Tree, config) "
                           "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        cQSqlQuery.addBindValue(p_pCdmMember->GetKeyname());
        cQSqlQuery.addBindValue(p_pCdmMember->GetValueType());
        cQSqlQuery.addBindValue(p_pCdmMember->IsMust());
        cQSqlQuery.addBindValue(p_pCdmMember->GetSize());
        cQSqlQuery.addBindValue(p_pCdmMember->GetClassReference());
        cQSqlQuery.addBindValue(p_pCdmMember->GetCounterStart());
        cQSqlQuery.addBindValue(p_pCdmMember->GetClassId()); // to Identify which to which class this belongs to
        cQSqlQuery.addBindValue(p_pCdmMember->GetDefaultValue());
        cQSqlQuery.addBindValue(p_pCdmMember->GetCaption());
        cQSqlQuery.addBindValue(p_pCdmMember->GetCreatorId());
        cQSqlQuery.addBindValue(p_pCdmMember->GetModifierId());
        cQSqlQuery.addBindValue(p_pCdmMember->GetComment());
        cQSqlQuery.addBindValue(p_pCdmMember->IsOwner());
        cQSqlQuery.addBindValue(p_pCdmMember->IsUnique());
        cQSqlQuery.addBindValue(p_pCdmMember->IsSystemMember());
        cQSqlQuery.addBindValue(p_pCdmMember->GetAccessMode());
        cQSqlQuery.addBindValue(p_pCdmMember->GetVersion());
        cQSqlQuery.addBindValue(iGroupId);
        cQSqlQuery.addBindValue(p_pCdmMember->GetValidationCode());
        cQSqlQuery.addBindValue(!p_pCdmMember->IsPersistent());
        cQSqlQuery.addBindValue(p_pCdmMember->IsTree());
        cQSqlQuery.addBindValue(p_pCdmMember->GetConfig());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            QString qstrKeyname =  p_pCdmMember->GetKeyname();
            cQSqlQuery.prepare("select MemberId from WMS_CLASS_MEMBER where Keyname = ? and ClassId = ?");
            cQSqlQuery.addBindValue(qstrKeyname);
            cQSqlQuery.addBindValue(p_pCdmMember->GetClassId());

            if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
            {
                cQSqlQuery.first();
                if(cQSqlQuery.isValid())
                {
                    CdmDataAccessHelper::SetId(p_pCdmMember, cQSqlQuery.value(0).toInt());
                    CdmDataAccessHelper::UpdateMemberId(p_pCdmClass, p_pCdmMember);
                    SaveTranslations(p_pCdmMember);
                    lRet = EC(eDmOk);
                }
                else
                {
                    lRet = EC(eDmQueryResultMismatch);
                    FATAL("The Execute Query Method says it was successfull, but the dataset was not found. This is not possible!!");
                }
            }
            else
            {
                lRet = EC(eDmInvalidInsertStatement);
                ERR("Select Query failed!!!");
            }
        }
        else
        {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert in WMS_Class_Member Table failed for Member.");
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}


qint64 CftlCommandUpdateClass::UpdateMember(CdmMember* p_pCdmMember, CdmClass* p_pCdmClass )
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());


        int iGroupId = 0;

        if (p_pCdmMember->GetGroup())
        {
            iGroupId = p_pCdmMember->GetGroup()->GetId();
        }

        cQSqlQuery.prepare("update WMS_CLASS_MEMBER set Keyname = ?, Datatype = ?, Must= ?, Size = ?, ObjectRefClassId = ?, "
                           "CounterStart = ?, ClassId = ?, DefaultValue = ?, Caption = ?, CreatorId = ?, ModifierId = ?, "
                           "Comment = ?, Owner = ?, Explicit = ?, System = ?, Access = ?, GroupId = ?, validation = ?, "
                           "version = ?, non_persistent = ?, is_Tree = ?, config = ? where MemberId = ?");
        cQSqlQuery.addBindValue(p_pCdmMember->GetKeyname());
        cQSqlQuery.addBindValue(p_pCdmMember->GetValueType());
        cQSqlQuery.addBindValue(p_pCdmMember->IsMust());
        cQSqlQuery.addBindValue(p_pCdmMember->GetSize());
        cQSqlQuery.addBindValue(p_pCdmMember->GetClassReference());
        cQSqlQuery.addBindValue(p_pCdmMember->GetCounterStart());
        cQSqlQuery.addBindValue(p_pCdmMember->GetClassId()); // to Identify which to which class this belongs to
        cQSqlQuery.addBindValue(p_pCdmMember->GetDefaultValue());
        cQSqlQuery.addBindValue(p_pCdmMember->GetCaption());
        cQSqlQuery.addBindValue(p_pCdmMember->GetCreatorId());
        cQSqlQuery.addBindValue(p_pCdmMember->GetModifierId());
        cQSqlQuery.addBindValue(p_pCdmMember->GetComment());
        cQSqlQuery.addBindValue(p_pCdmMember->IsOwner());
        cQSqlQuery.addBindValue(p_pCdmMember->IsUnique());
        cQSqlQuery.addBindValue(p_pCdmMember->IsSystemMember());
        cQSqlQuery.addBindValue(p_pCdmMember->GetAccessMode());
        cQSqlQuery.addBindValue(iGroupId);
        cQSqlQuery.addBindValue(p_pCdmMember->GetValidationCode());
        cQSqlQuery.addBindValue(p_pCdmMember->GetVersion());
        cQSqlQuery.addBindValue(!p_pCdmMember->IsPersistent());
        cQSqlQuery.addBindValue(p_pCdmMember->IsTree());
        cQSqlQuery.addBindValue(p_pCdmMember->GetConfig());
        cQSqlQuery.addBindValue(p_pCdmMember->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            lRet = EC(eDmOk);
        }
        else
        {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update of WMS_Class_Member Table not succeeded");
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;

}

qint64 CftlCommandUpdateClass::DeleteMember(qint64 p_lMemberId)
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("delete from WMS_CLASS_MEMBER where MemberId = ?");
    cQSqlQuery.addBindValue(p_lMemberId);

    lRet = ExecuteQuery(cQSqlQuery);

    return lRet;
}

qint64 CftlCommandUpdateClass::InsertOrUpdateBaseClasses(CdmClass* p_pCdmClass)
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

    if(CHKPTR(p_pCdmClass))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());


        // first step load all classes with DataBaseId == p_lDataBaseId
        cQSqlQuery.prepare("select BaseClassId from WMS_CLASS_BASECLASS where ClassId = ?");
        cQSqlQuery.addBindValue(p_pCdmClass->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            lRet = EC(eDmFalse);
            QList<int> qvlDbBaseClasses;

            cQSqlQuery.first();
            if(cQSqlQuery.isValid())
            {
                do
                {
                    qvlDbBaseClasses.append(cQSqlQuery.value(0).toInt());
                }
                while(cQSqlQuery.next());
            }
            else
            {
                INFO("No Baseclasses found");
            }

            QMap<qint64,qint64> qmBaseClasses = p_pCdmClass->GetBaseClasses();

            // checking if a base class must be inserted to DB
            QMap<qint64,qint64>::iterator qmIt    = qmBaseClasses.begin();
            QMap<qint64,qint64>::iterator qmItEnd = qmBaseClasses.end();

            for(; qmIt != qmItEnd; ++qmIt)
            {
                if(!FindValueInList(qmIt.value(), qvlDbBaseClasses))
                {
                    InsertBaseClass(p_pCdmClass->GetId(), qmIt.value());
                }
            }

            // checking if a base class must be removed from DB
            QList<int>::iterator qvlIt = qvlDbBaseClasses.begin();
            QList<int>::iterator qvlItEnd = qvlDbBaseClasses.end();

            for(; qvlIt != qvlItEnd; ++qvlIt)
            {
                if(!FindValueInMap((*qvlIt), qmBaseClasses))
                {
                    DeleteBaseClassFromDb(p_pCdmClass->GetId(), (*qvlIt));
                }
            }
        }
        else
        {
            lRet = EC(eDmInvalidSelectStatement);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

bool CftlCommandUpdateClass::FindValueInMap(qint64 p_lValue, QMap<qint64,qint64>& p_rqmMap)
{
    bool bRet = false;

    QMap<qint64,qint64>::iterator qmIt    = p_rqmMap.begin();
    QMap<qint64,qint64>::iterator qmItEnd = p_rqmMap.end();

    for(; qmIt != qmItEnd; ++qmIt)
    {
       qint64 lValue = qmIt.value();
        if(lValue == p_lValue)
        {
            bRet = true;
            break;
        }
    }

    return bRet;
}

bool CftlCommandUpdateClass::FindValueInList(int p_iValue, QList<int>& p_rqvlList)
{
    bool bRet = false;

    QList<int>::iterator qvlIt = p_rqvlList.begin();
    QList<int>::iterator qvlItEnd = p_rqvlList.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        int iValue = (*qvlIt);
        if(iValue == p_iValue)
        {
            bRet = true;
            break;
        }
    }

    return bRet;
}

qint64 CftlCommandUpdateClass::InsertBaseClass(qint64 p_lClassId,qint64 p_lBaseClassId)
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    // first step load all classes with DataBaseId == p_lDataBaseId
    cQSqlQuery.prepare("insert into WMS_CLASS_BASECLASS (ClassId, BaseClassId) values(?, ?)");
    cQSqlQuery.addBindValue(p_lClassId);
    cQSqlQuery.addBindValue(p_lBaseClassId);

    lRet = ExecuteQuery(cQSqlQuery);

    if(lRet < 0)
    {
        ERR("Error occurred while trying to insert a new baseclass.");
    }
    else
    {
        lRet = EC(eDmInvalidInsertStatement);
    }



    return lRet;
}

qint64 CftlCommandUpdateClass::DeleteBaseClassFromDb( qint64 p_lClassId,qint64 p_lBaseClassId )
{
   qint64 lRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    // first step load all classes with DataBaseId == p_lDataBaseId
    cQSqlQuery.prepare("delete from WMS_CLASS_BASECLASS where ClassId = ? AND BaseClassId = ?");
    cQSqlQuery.addBindValue(p_lClassId);
    cQSqlQuery.addBindValue(p_lBaseClassId);

    lRet = ExecuteQuery(cQSqlQuery);

    if(lRet < 0)
    {
        lRet = EC(eDmInvalidDeleteStatement);
        ERR("Error occurred while trying to delete old baseclass.");
    }


    return lRet;
}

int CftlCommandUpdateClass::GetNewIdForClassMembers(qint64 p_lClassId,
                                                    QString p_qstrName,
                                                    QString p_qstrTable)
{
    int iId = 0;
    QSqlQuery cQuery(GetSqlDatabase());
    QString qstrInsert = QString("insert into %1 (ClassId, Name) values (?, ?)")
            .arg(p_qstrTable);

    cQuery.prepare(qstrInsert);
    cQuery.addBindValue(p_lClassId);
    cQuery.addBindValue(p_qstrName);

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        QString qstrSelect = QString("select Id from %1 where ClassId = ? and Name = ?")
                .arg(p_qstrTable);

        cQuery.prepare(qstrSelect);
        cQuery.addBindValue(p_lClassId);
        cQuery.addBindValue(p_qstrName);

        if (ExecuteQuery(cQuery) > 0)
        {
            cQuery.first();
            if(cQuery.isValid())
            {
                iId = cQuery.value(0).toInt();
            }
            else
            {
                ERR("Entry not found something went wrong!");
            }
        }
        else
        {
            ERR("Select failed!");
        }
    }
    else
    {
        ERR("Error while inserting Entry in DB.");
    }

    return iId;
}

void CftlCommandUpdateClass::SaveTranslations(CdmMember* p_pCdmMember)
{
    if (CHKPTR(p_pCdmMember))
    {
        QMap<QString, StringPair>& qmTranslations = p_pCdmMember->GetTranslations();

        if (qmTranslations.count() > 0)
        {
            QSqlQuery cQueryDelete(GetSqlDatabase());
            cQueryDelete.prepare("delete from WMS_CLASS_MEMBER_TRANSLATION where MemberId = ?");
            cQueryDelete.addBindValue(p_pCdmMember->GetId());


            if (SUCCESSFULL(ExecuteQuery(cQueryDelete)))
            {
                QVariantList qvlMemberids;
                QVariantList qvlLanguage;
                QVariantList qvlCaptions;
                QVariantList qvlComments;
                QMap<QString, StringPair>::iterator qmIt = qmTranslations.begin();
                QMap<QString, StringPair>::iterator qmItEnd = qmTranslations.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    StringPair qPair = qmIt.value();
                    qvlMemberids.append(p_pCdmMember->GetId());
                    qvlLanguage.append(qmIt.key());
                    qvlCaptions.append(qPair.first);
                    qvlComments.append(qPair.second);
                }

                QSqlQuery cQuery(GetSqlDatabase());
                cQuery.prepare("insert into WMS_CLASS_MEMBER_TRANSLATION (MemberId, Language, Caption, Comment) values(?, ?, ?, ?)");
                cQuery.addBindValue(qvlMemberids);
                cQuery.addBindValue(qvlLanguage);
                cQuery.addBindValue(qvlCaptions);
                cQuery.addBindValue(qvlComments);

                if (cQuery.execBatch())
                {
                    INFO("Insert successfull");
                }
                else
                {
                    ERR("Insert failed");
                }
            }
        }
    }
}

void CftlCommandUpdateClass::SaveGroupTranslations(CdmClassGroup* p_pCdmGroup)
{
    if (CHKPTR(p_pCdmGroup))
    {
        QMap<QString, QString> qmTranslations = p_pCdmGroup->GetTranslations();

        if (qmTranslations.count() > 0)
        {
            QSqlQuery cQueryDelete;
            cQueryDelete.prepare("delete from WMS_CLASS_GROUP_TRANSLATION where GroupId = ?");
            cQueryDelete.addBindValue(p_pCdmGroup->GetId());


            if (SUCCESSFULL(ExecuteQuery(cQueryDelete)))
            {
                QMap<QString, QString>::iterator qmIt = qmTranslations.begin();
                QMap<QString, QString>::iterator qmItEnd = qmTranslations.end();
                QVariantList qvlgroups;
                QVariantList qvlLanguages;
                QVariantList qvlCaptions;

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    qvlgroups.append(p_pCdmGroup->GetId());
                    qvlLanguages.append(qmIt.key());
                    qvlCaptions.append(qmIt.value());
                }

                QSqlQuery cQuery(GetSqlDatabase());
                cQuery.prepare("insert into WMS_CLASS_GROUP_TRANSLATION (GroupId, Language, Caption) values(?,?,?)");

                if (SUCCESSFULL(ExecuteQuery(cQuery)))
                {
                    INFO("Insert successfull");
                }
                else
                {
                    ERR("Insert failed");
                }
            }
        }
    }
}

void CftlCommandUpdateClass::DeleteTranslations(int p_iMemberId)
{
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("delete from WMS_CLASS_MEMBER_TRANSLATION where MemberId = ?");
    cQuery.addBindValue(p_iMemberId);

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        INFO("Delete successfull");
    }
    else
    {
        ERR("Delete failed");
    }
}
