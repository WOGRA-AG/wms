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
#include "CdbCommandUpdateClass.h"

CdbCommandUpdateClass::CdbCommandUpdateClass(CdmClass* p_pClass, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_rpClass(p_pClass)
{
}

CdbCommandUpdateClass::~CdbCommandUpdateClass()
{
}

int CdbCommandUpdateClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    // First of save the groups for correct ID assignments of members.
    SaveGroups(m_rpClass);
    // Updating class Data
    QMap<long, CdmMember*> qmMembers;
    m_rpClass->GetClassMemberMap(qmMembers);

    QMap<long,CdmMember*>::iterator iIt    = qmMembers.begin();
    QMap<long,CdmMember*>::iterator iItEnd = qmMembers.end();

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
                ERR("Could not delete member!!")
             }
          }
          else if (pCdmMember->IsNew() || pCdmMember->IsModified())
          {
             InsertOrUpdateMember(pCdmMember, m_rpClass);
          }
       }
    }

    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    // Query for creating new entry
    qstrQuery = QString("update WMS_CLASS set Keyname = '%1', LastChange = %2, DataBaseId = %3, "
                      "CreatorId = %4, ModifierId = %5, Caption = '%6', Comment = '%7', ")
                      .arg(CwmsUtilities::MaskStringForChanges(m_rpClass->GetKeyname()))
                      .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                      .arg(m_rpClass->GetSchemeId())
                      .arg(m_rpClass->GetCreatorId())
                      .arg(m_rpClass->GetModifierId())
                      .arg(CwmsUtilities::MaskStringForChanges(m_rpClass->GetCaption()))
                      .arg(CwmsUtilities::MaskStringForChanges(m_rpClass->GetComment()));

	QString qstrPackage;
	CdmPackage* pPackage = m_rpClass->GetPackage();

	if (pPackage)
	{
        qstrPackage = pPackage->GetUriInternal();
	}

    qstrQuery += QString("Abstract = %1, PositionSequence = '%2', Version = %3, CaptionMember = %4, Package_URI = '%5', config = '%6' where ClassId = %7")
       .arg(m_rpClass->IsAbstract())
       .arg(CwmsUtilities::MaskStringForChanges(m_rpClass->GetMemberSequenceString()))
       .arg(m_rpClass->GetVersion())
       .arg(m_rpClass->GetCaptionMemberId())
       .arg(CwmsUtilities::MaskStringForChanges(qstrPackage))
       .arg(CwmsUtilities::MaskStringForChanges(m_rpClass->GetConfig()))
       .arg(m_rpClass->GetId());

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {

       iRet = InsertOrUpdateBaseClasses(m_rpClass);

       if (iRet == 0) // 0 means no baseclasses found!!!
       {
          iRet = EC(eDmOk);
       }

       SaveMethods(m_rpClass);
       SaveValidators(m_rpClass);
       m_rpClass->ResetNewModified();
    }
    else
    {
       iRet = EC(eDmInvalidUpdateStatement);
    }

    return iRet;
}

bool CdbCommandUpdateClass::CheckValid()
{
    return (CHKPTR(m_rpClass));
}

void CdbCommandUpdateClass::SaveGroups(CdmClass*& p_rCdmClass)
{
   QSqlQuery cQuery;
   QString qstrDeleteGroups = QString("delete from WMS_CLASS_GROUP where classid = %1"). arg(p_rCdmClass->GetId());

   if (ExecuteQuery(qstrDeleteGroups, cQuery) > 0)
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
            QString qstrSql;

            if (iId == 0)
            {
               iId = GetNewIdForClassMembers(p_rCdmClass->GetId(), pCdmGroup->GetName(), "WMS_CLASS_GROUP");

               if (iId > 0)
               {
                  qstrSql = QString("update WMS_CLASS_GROUP set ClassId = %1,  Name = '%2', Version = %3, Position = %4, Parent = %5 where Id = %6")
                     .arg(p_rCdmClass->GetId())
                     .arg(CwmsUtilities::MaskStringForChanges(pCdmGroup->GetName()))
                     .arg(pCdmGroup->GetVersion())
                     .arg(pCdmGroup->GetPosition())
                     .arg(iParentId)
                     .arg(iId);

                  pCdmGroup->SetId(iId);
               }
            }
            else
            {
               qstrSql = QString("insert into WMS_CLASS_GROUP (ClassId, Id, Name, Version, Position, Parent)"
                                            " values (%1, %2, '%3', %4, %5, %6)")
                                            .arg(p_rCdmClass->GetId())
                                            .arg(pCdmGroup->GetId())
                                            .arg(CwmsUtilities::MaskStringForChanges(pCdmGroup->GetName()))
                                            .arg(pCdmGroup->GetVersion())
                                            .arg(pCdmGroup->GetPosition())
                                            .arg(iParentId);
            }

            if (!qstrSql.isEmpty())
            {
               ExecuteQuery(qstrSql, cQuery);

               GetDataAccess()->SaveRights(pCdmGroup->GetRights(),
                                               pCdmGroup->GetId(),
                                               "WMS_CLASS_GROUP_RIGHTS",
                                               "GroupId");

               SaveGroupTranslations(pCdmGroup);
            }
         }
      }
   }
}

void CdbCommandUpdateClass::SaveMethods(CdmClass*& p_rCdmClass)
{
   QSqlQuery cQuery;
   QString qstrDeleteGroups = QString("delete from WMS_CLASS_METHOD where classid = %1"). arg(p_rCdmClass->GetId());

   if (SUCCESSFULL(ExecuteQuery(qstrDeleteGroups, cQuery)))
   {
      QMap<QString, CdmClassMethod*>& qmMethods = p_rCdmClass->GetMethods();

      QMap<QString, CdmClassMethod*>::iterator qmIt = qmMethods.begin();
      QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmMethods.end();
      QList<QString> qlNameChanged;

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmClassMethod* pCdmMethod = qmIt.value();

         if (CHKPTR(pCdmMethod))
         {
             if (pCdmMethod->GetMethodName() != qmIt.key())
             {
                 qlNameChanged.append(qmIt.key());
             }

            int iId = pCdmMethod->GetId();
            QByteArray qbIcon = pCdmMethod->GetIconAsByteArray();
            QString qstrBase64(qbIcon.toBase64());
            QSqlQuery cQSqlQuery(GetSqlDatabase());


            if (iId <= 0)
            {
               iId = GetNewIdForClassMembers(p_rCdmClass->GetId(), pCdmMethod->GetMethodName(), "WMS_CLASS_METHOD");


               if (iId > 0)
               {
                   cQSqlQuery.prepare("update WMS_CLASS_METHOD set ClassId = :classid, MethodType = :methodtype, Name = :name, Code = :code, Version = :version, "
                                      "AccessMode = :accessmode, Parameters = :parameters, Comment = :comment, Static = :static, Caption = :caption, Icon = :icon "
                                      "where Id = :id");
                   cQSqlQuery.bindValue(":classid", (int)p_rCdmClass->GetId());
                   cQSqlQuery.bindValue(":methodtype", pCdmMethod->GetReturnType());
                   cQSqlQuery.bindValue(":name", pCdmMethod->GetMethodName());
                   cQSqlQuery.bindValue(":code", pCdmMethod->GetSourceCode());
                   cQSqlQuery.bindValue(":version", pCdmMethod->GetVersion());
                   cQSqlQuery.bindValue(":accessmode", pCdmMethod->GetAccess());
                   cQSqlQuery.bindValue(":parameters", pCdmMethod->GetParametersAsString());
                   cQSqlQuery.bindValue(":comment", pCdmMethod->GetComment());
                   cQSqlQuery.bindValue(":static", pCdmMethod->IsStatic());
                   cQSqlQuery.bindValue(":caption", pCdmMethod->GetCaption());
                   cQSqlQuery.bindValue(":icon", qstrBase64);
                   cQSqlQuery.bindValue(":id", iId);
               }
            }
            else
            {

                cQSqlQuery.prepare("insert into WMS_CLASS_METHOD (ClassId, MethodType, Name, Code, Version, AccessMode, Parameters, Id, Static, Comment, Caption, Icon)"
                                    " values (:classid, :methodtype, :name, :code, :version, :accessmode, :parameters, :id, :static, :comment, :caption, :icon)");
                cQSqlQuery.bindValue(":classid", (int)p_rCdmClass->GetId());
                cQSqlQuery.bindValue(":methodtype", pCdmMethod->GetReturnType());
                cQSqlQuery.bindValue(":name", pCdmMethod->GetMethodName());
                cQSqlQuery.bindValue(":code", pCdmMethod->GetSourceCode());
                cQSqlQuery.bindValue(":version", pCdmMethod->GetVersion());
                cQSqlQuery.bindValue(":accessmode", pCdmMethod->GetAccess());
                cQSqlQuery.bindValue(":parameters", pCdmMethod->GetParametersAsString());
                cQSqlQuery.bindValue(":comment", pCdmMethod->GetComment());
                cQSqlQuery.bindValue(":static", pCdmMethod->IsStatic());
                cQSqlQuery.bindValue(":caption", pCdmMethod->GetCaption());
                cQSqlQuery.bindValue(":icon", qstrBase64);
                cQSqlQuery.bindValue(":id", iId);
            }

            if (SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
            {
               pCdmMethod->SetId(iId);
               GetDataAccess()->SaveRights(pCdmMethod->GetRights(),
										   iId,
                                           "WMS_CLASS_METHOD_RIGHTS",
                                           "MethodId");
            }

         }
      }

      for (int iCounter = 0; iCounter < qlNameChanged.count(); ++iCounter)
      {
          CdmClassMethod* pMethod = p_rCdmClass->FindMethod(qlNameChanged[iCounter]);
          p_rCdmClass->RemoveMethod(qlNameChanged[iCounter]);
          p_rCdmClass->AddMethod(pMethod);
      }
   }
}

void CdbCommandUpdateClass::SaveValidators(CdmClass*& p_rCdmClass)
{
   QSqlQuery cQuery;
   QString qstrDeleteGroups = QString("delete from WMS_CLASS_VALIDATION where classid = %1"). arg(p_rCdmClass->GetId());

   if (ExecuteQuery(qstrDeleteGroups, cQuery) > 0)
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
                 qstrSql = QString("update WMS_CLASS_VALIDATION set ClassId = %1, Name = '%2', Code = '%3', Version = %4, ValidationType = %5, Message = '%6' where Id = %7")
                    .arg(p_rCdmClass->GetId())
                    .arg(CwmsUtilities::MaskStringForChanges(pCdmValidator->GetName()))
                    .arg(CwmsUtilities::MaskStringForChanges(pCdmValidator->GetCode()))
                    .arg(pCdmValidator->GetVersion())
                    .arg(pCdmValidator->GetValidationType())
                    .arg(pCdmValidator->GetErrorMessage())
                    .arg(iId);
              }
            }
            else
            {
               qstrSql = QString("insert into WMS_CLASS_VALIDATION (ClassId, Name, Code, Version, ValidationType, Message, Id)"
                  " values (%1, '%2', '%3', %4, %5, '%6', %7)")
                  .arg(p_rCdmClass->GetId())
                  .arg(CwmsUtilities::MaskStringForChanges(pCdmValidator->GetName()))
                  .arg(CwmsUtilities::MaskStringForChanges(pCdmValidator->GetCode()))
                  .arg(pCdmValidator->GetVersion())
                  .arg(pCdmValidator->GetValidationType())
                  .arg(CwmsUtilities::MaskStringForChanges(pCdmValidator->GetErrorMessage()))
                  .arg(iId);
            }

            if (!qstrSql.isEmpty())
            {
               ExecuteQuery(qstrSql, cQuery);
            }
         }
      }
   }
}

long CdbCommandUpdateClass::InsertOrUpdateMember(CdmMember* p_pCdmMember, CdmClass* p_pCdmClass)
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

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

long CdbCommandUpdateClass::InsertMember(CdmMember* p_pCdmMember, CdmClass* p_pCdmClass)
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
   {
      QString qstrQuery;

      int iGroupId = 0;

      if (p_pCdmMember->GetGroup())
      {
         iGroupId = p_pCdmMember->GetGroup()->GetId();
      }

      QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());
      cQSqlQuery.prepare("insert into WMS_CLASS_MEMBER (Keyname, Datatype, Must, Size, ObjectRefClassId, "
                         "CounterStart, ClassId, DefaultValue, Caption, CreatorId, ModifierId, Comment, "
                         "Owner, Explicit, `System`, Access, Version, GroupId, Validation, Non_Persistent, Is_Tree, config) "
                         "values(:keyname, :datatype, :must, :size, :objrefclassid, :counterstart, :classid, "
                         ":defaultValue, :caption, :creatorId, :modifierId, :comment, :owner, :explicit, :system, "
                         ":access, :version, :groupId, :validation, :nonPersistent, :isTree, :config)");

      cQSqlQuery.bindValue(":keyname", p_pCdmMember->GetKeyname());
      cQSqlQuery.bindValue(":datatype", p_pCdmMember->GetValueType());
      cQSqlQuery.bindValue(":must", p_pCdmMember->IsMust());
      cQSqlQuery.bindValue(":size", (int)p_pCdmMember->GetSize());
      cQSqlQuery.bindValue(":objrefclassid",(int) p_pCdmMember->GetClassReference());
      cQSqlQuery.bindValue(":counterstart",(int) p_pCdmMember->GetCounterStart());
      cQSqlQuery.bindValue(":classid", (int)p_pCdmMember->GetClassId());
      cQSqlQuery.bindValue(":defaultValue", p_pCdmMember->GetDefaultValue().toString());
      cQSqlQuery.bindValue(":caption", p_pCdmMember->GetCaption());
      cQSqlQuery.bindValue(":creatorId", (int)p_pCdmMember->GetCreatorId());
      cQSqlQuery.bindValue(":modifierId", (int)p_pCdmMember->GetModifierId());
      cQSqlQuery.bindValue(":comment", p_pCdmMember->GetComment());
      cQSqlQuery.bindValue(":owner", p_pCdmMember->IsOwner());
      cQSqlQuery.bindValue(":explicit", p_pCdmMember->IsUnique());
      cQSqlQuery.bindValue(":system", p_pCdmMember->IsSystemMember());
      cQSqlQuery.bindValue(":access", p_pCdmMember->GetAccessMode());
      cQSqlQuery.bindValue(":groupId", iGroupId);
      cQSqlQuery.bindValue(":validation", p_pCdmMember->GetValidationCode());
      cQSqlQuery.bindValue(":version", p_pCdmMember->GetVersion());
      cQSqlQuery.bindValue(":nonPersistent", !p_pCdmMember->IsPersistent());
      cQSqlQuery.bindValue(":isTree", p_pCdmMember->IsTree());
      cQSqlQuery.bindValue(":config", p_pCdmMember->GetConfig());


      if(SUCCESSFULL(GetDataAccess()->ExecuteQuery(cQSqlQuery)))
      {
         QString qstrKeyname =  p_pCdmMember->GetKeyname();
         qstrQuery = QString("select MemberId from WMS_CLASS_MEMBER where Keyname = '%1' and ClassId = %2")
                            .arg(CwmsUtilities::MaskString(qstrKeyname))
                            .arg(p_pCdmMember->GetClassId());

         if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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


long CdbCommandUpdateClass::UpdateMember(CdmMember* p_pCdmMember, CdmClass* p_pCdmClass )
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   if(CHKPTR(p_pCdmMember) && CHKPTR(p_pCdmClass))
   {
      int iGroupId = 0;

      if (p_pCdmMember->GetGroup())
      {
         iGroupId = p_pCdmMember->GetGroup()->GetId();
      }

      QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());
      cQSqlQuery.prepare("update WMS_CLASS_MEMBER set Keyname = :keyname, Datatype = :datatype, Must= :must, Size = :size, ObjectRefClassId = :objrefclassid, "
                         "CounterStart = :counterstart, ClassId = :classid, DefaultValue = :defaultValue, Caption = :caption, CreatorId = :creatorId, ModifierId = :modifierId, "
                         "Comment = :comment, Owner = :owner, Explicit = :explicit, `System` = :system, Access = :access, GroupId = :groupId, validation = :validation, "
                         "version = :version, non_persistent = :nonPersistent, is_Tree = :isTree, config = :config where MemberId = :memberId");

      cQSqlQuery.bindValue(":keyname", p_pCdmMember->GetKeyname());
      cQSqlQuery.bindValue(":datatype", p_pCdmMember->GetValueType());
      cQSqlQuery.bindValue(":must", p_pCdmMember->IsMust());
      cQSqlQuery.bindValue(":size", (int)p_pCdmMember->GetSize());
      cQSqlQuery.bindValue(":objrefclassid",(int) p_pCdmMember->GetClassReference());
      cQSqlQuery.bindValue(":counterstart",(int) p_pCdmMember->GetCounterStart());
      cQSqlQuery.bindValue(":classid", (int)p_pCdmMember->GetClassId());
      cQSqlQuery.bindValue(":defaultValue", p_pCdmMember->GetDefaultValue().toString());
      cQSqlQuery.bindValue(":caption", p_pCdmMember->GetCaption());
      cQSqlQuery.bindValue(":creatorId", (int)p_pCdmMember->GetCreatorId());
      cQSqlQuery.bindValue(":modifierId", (int)p_pCdmMember->GetModifierId());
      cQSqlQuery.bindValue(":comment", p_pCdmMember->GetComment());
      cQSqlQuery.bindValue(":owner", p_pCdmMember->IsOwner());
      cQSqlQuery.bindValue(":explicit", p_pCdmMember->IsUnique());
      cQSqlQuery.bindValue(":system", p_pCdmMember->IsSystemMember());
      cQSqlQuery.bindValue(":access", p_pCdmMember->GetAccessMode());
      cQSqlQuery.bindValue(":groupId", iGroupId);
      cQSqlQuery.bindValue(":validation", p_pCdmMember->GetValidationCode());
      cQSqlQuery.bindValue(":version", p_pCdmMember->GetVersion());
      cQSqlQuery.bindValue(":nonPersistent", !p_pCdmMember->IsPersistent());
      cQSqlQuery.bindValue(":isTree", p_pCdmMember->IsTree());
      cQSqlQuery.bindValue(":config", p_pCdmMember->GetConfig());
      cQSqlQuery.bindValue(":memberId", (int)p_pCdmMember->GetId());


      if(SUCCESSFULL(GetDataAccess()->ExecuteQuery(cQSqlQuery)))
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

long CdbCommandUpdateClass::DeleteMember(long p_lMemberId)
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;


      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // first step load all classes with DataBaseId == p_lDataBaseId
      qstrQuery = QString("delete from WMS_CLASS_MEMBER where MemberId = %1")
                         .arg(p_lMemberId);

      lRet = ExecuteQuery(qstrQuery, cQSqlQuery);

   return lRet;
}

long CdbCommandUpdateClass::InsertOrUpdateBaseClasses(CdmClass* p_pCdmClass)
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   if(CHKPTR(p_pCdmClass))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // first step load all classes with DataBaseId == p_lDataBaseId
      qstrQuery = QString("select BaseClassId from WMS_CLASS_BASECLASS where ClassId = %1")
                          .arg(p_pCdmClass->GetId());

      if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

         QMap<long,long> qmBaseClasses = p_pCdmClass->GetBaseClasses();

         // checking if a base class must be inserted to DB
         QMap<long,long>::iterator qmIt    = qmBaseClasses.begin();
         QMap<long,long>::iterator qmItEnd = qmBaseClasses.end();

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

bool CdbCommandUpdateClass::FindValueInMap(  long p_lValue, QMap<long, long>& p_rqmMap )
{
   bool bRet = false;

   QMap<long,long>::iterator qmIt    = p_rqmMap.begin();
   QMap<long,long>::iterator qmItEnd = p_rqmMap.end();

   for(; qmIt != qmItEnd; ++qmIt)
   {
      long lValue = qmIt.value();
      if(lValue == p_lValue)
      {
         bRet = true;
         break;
      }
   }

   return bRet;
}

bool CdbCommandUpdateClass::FindValueInList(  int p_iValue, QList<int>& p_rqvlList )
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

long CdbCommandUpdateClass::InsertBaseClass(  long p_lClassId, long p_lBaseClassId )
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;
  QSqlQuery cQSqlQuery;
  QString qstrQuery;

  // first step load all classes with DataBaseId == p_lDataBaseId
  qstrQuery = QString("insert into WMS_CLASS_BASECLASS (ClassId, BaseClassId) values(%1, %2)")
                      .arg(p_lClassId)
                      .arg(p_lBaseClassId);

  lRet = ExecuteQuery(qstrQuery, cQSqlQuery);

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

long CdbCommandUpdateClass::DeleteBaseClassFromDb(  long p_lClassId, long p_lBaseClassId )
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;
  QSqlQuery cQSqlQuery;
  QString qstrQuery;

  // first step load all classes with DataBaseId == p_lDataBaseId
  qstrQuery = QString("delete from WMS_CLASS_BASECLASS where CLassId = %1 AND BaseClassId = %2")
                      .arg(p_lClassId)
                      .arg(p_lBaseClassId);

  lRet = ExecuteQuery(qstrQuery, cQSqlQuery);

  if(lRet < 0)
  {
     lRet = EC(eDmInvalidDeleteStatement);
     ERR("Error occurred while trying to delete old baseclass.");
  }


   return lRet;
}

int CdbCommandUpdateClass::GetNewIdForClassMembers(long p_lClassId,
                                              QString p_qstrName,
                                              QString p_qstrTable)
{
   int iId = 0;
   QSqlQuery cQuery;
   QString qstrInsert = QString("insert into %1 (ClassId, Name) values (%2, '%3')")
      .arg(p_qstrTable)
      .arg(p_lClassId)
      .arg(CwmsUtilities::MaskStringForChanges(p_qstrName));

   if (ExecuteQuery(qstrInsert, cQuery) > 0)
   {
      QString qstrSelect = QString("select Id from %1 where ClassId = %2 and Name = '%3'")
                              .arg(p_qstrTable)
                              .arg(p_lClassId)
                              .arg(CwmsUtilities::MaskStringForChanges(p_qstrName));

      if (ExecuteQuery(qstrSelect, cQuery) > 0)
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

void CdbCommandUpdateClass::SaveTranslations(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      QMap<QString, StringPair>& qmTranslations = p_pCdmMember->GetTranslations();

      if (qmTranslations.count() > 0)
      {
         QString qstrDelete = QString("delete from WMS_CLASS_MEMBER_TRANSLATION where MemberId = %1").arg(p_pCdmMember->GetId());
         QSqlQuery cQueryDelete;

         if (ExecuteQuery(qstrDelete, cQueryDelete) > 0)
         {
            QMap<QString, StringPair>::iterator qmIt = qmTranslations.begin();
            QMap<QString, StringPair>::iterator qmItEnd = qmTranslations.end();
            QString qstrInsertValue;
            bool bFirst = true;

            for (; qmIt != qmItEnd; ++qmIt)
            {
               StringPair qPair = qmIt.value();

               if (!bFirst)
               {
                  qstrInsertValue += ",";
               }
               else
               {
                  bFirst = false;
               }

			   CdmScheme* pScheme = CdmSessionManager::GetDataProvider()->GetCurrentScheme();

			   if (CHKPTR(pScheme))
			   {
				   qstrInsertValue += QString("(%1, '%2', '%3', '%4')")
					   .arg(p_pCdmMember->GetId())
                       .arg(qmIt.key())
					   .arg(qPair.first)
					   .arg(qPair.second);
			   }
            }

            QString qstrInsert = "insert into WMS_CLASS_MEMBER_TRANSLATION (MemberId, Language, Caption, Comment) values"+ qstrInsertValue;
            QSqlQuery cQuery;

            if (ExecuteQuery(qstrInsert, cQuery) > 0)
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

void CdbCommandUpdateClass::SaveGroupTranslations(CdmClassGroup* p_pCdmGroup)
{
   if (CHKPTR(p_pCdmGroup))
   {
      QMap<QString, QString>& qmTranslations = p_pCdmGroup->GetTranslations();

      if (qmTranslations.count() > 0)
      {
         QString qstrDelete = QString("delete from WMS_CLASS_GROUP_TRANSLATION where GroupId = %1").arg(p_pCdmGroup->GetId());
         QSqlQuery cQueryDelete;

         if (ExecuteQuery(qstrDelete, cQueryDelete) > 0)
         {
            QMap<QString, QString>::iterator qmIt = qmTranslations.begin();
            QMap<QString, QString>::iterator qmItEnd = qmTranslations.end();
            QString qstrInsertValue;
            bool bFirst = true;

            for (; qmIt != qmItEnd; ++qmIt)
            {
               if (!bFirst)
               {
                  qstrInsertValue += ",";
               }
               else
               {
                  bFirst = false;
               }

               qstrInsertValue += QString("(%1, '%2', '%3')")
                   .arg(p_pCdmGroup->GetId())
                   .arg(qmIt.key())
                   .arg(qmIt.value());
                       }

            QString qstrInsert = "insert into WMS_CLASS_GROUP_TRANSLATION (GroupId, Language, Caption) values"+ qstrInsertValue;
            QSqlQuery cQuery;

            if (ExecuteQuery(qstrInsert, cQuery) > 0)
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

void CdbCommandUpdateClass::DeleteTranslations(int p_iMemberId)
{
   QString qstrInsert = QString("delete from WMS_CLASS_MEMBER_TRANSLATION where MemberId = %1").arg(p_iMemberId);
   QSqlQuery cQuery;

   if (ExecuteQuery(qstrInsert, cQuery) > 0)
   {
      INFO("Delete successfull");
   }
   else
   {
      ERR("Delete failed");
   }
}
