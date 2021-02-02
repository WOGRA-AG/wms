/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsUtilities.cpp
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QSqlQuery>

// WMS COMMONS Includes
#include "CwmsUtilities.h"

// WMSCORE Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmValue.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListString.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueListObjects.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"
#include "CdmValueEnum.h"
#include "CdmQueryElement.h"

// own Includes
#include "CftlDialect.h"
#include "CftlInterface.h"
#include "CftlHelper.h"


QString CftlHelper::GenerateClassContainerTableName(CdmClass *p_pClass, CftlDialect* p_pDialect)
{
    QString qstrTableName;

    if (CHKPTR(p_pClass))
    {
        QString qstrScheme = QString("_%1").arg(p_pClass->GetSchemeId());
        QString qstrFullQualifiedName = p_pClass->GetFullQualifiedName() + qstrScheme;
        int iMaxTableNameLength = FTL_MAX_TABLE_NAME_LENGTH_VALUE;

        if (CHKPTR(p_pDialect))
        {
            iMaxTableNameLength = p_pDialect->GetMaxTableNameLength();
        }


        if (qstrFullQualifiedName.length() > iMaxTableNameLength)
        {
            QStringList qstrlSplit = qstrFullQualifiedName.split(".", QString::SkipEmptyParts);
            int iListSize = qstrlSplit.count();

            if (iListSize == 1) // the keyname itself is too long
            {
                qstrTableName = qstrFullQualifiedName.left(iMaxTableNameLength) + QString::number(p_pClass->GetId());

            }
            else
            {
                for (int iPos = iListSize - 1; iPos > 0; iPos--)
                {
                    QString qstrPart = qstrlSplit[iPos];

                    if (qstrPart.length() > iMaxTableNameLength)
                    {
                        if (qstrTableName.isEmpty())
                        {
                            qstrTableName = qstrPart.left(iMaxTableNameLength) + QString::number(p_pClass->GetId());
                            break;
                        }
                        else
                        {
                            qstrTableName += QString::number(p_pClass->GetId());
                            break;
                        }
                    }
                    else
                    {
                        qstrTableName = qstrPart + QString::number(p_pClass->GetId());
                    }
                }
            }
        }
        else
        {
            qstrFullQualifiedName = qstrFullQualifiedName.remove(".");
            qstrTableName += qstrFullQualifiedName + QString::number(p_pClass->GetId());
        }
    }

    if (CwmsUtilities::IsKeynameSqlKeyword(qstrTableName))
    {
        qstrTableName += "1";
    }

    return qstrTableName;
}

QString CftlHelper::GenerateClassContainerSequenceName(CdmClass *p_pClass)
{
    QString qstrSequenceName;

    if (CHKPTR(p_pClass))
    {
        QString qstrKeyname = p_pClass->GetKeyname();

        if (qstrKeyname.length() > FTL_MAX_SEQUENCE_NAME_LENGTH_VALUE)
        {
            qstrSequenceName = qstrKeyname.left(FTL_MAX_SEQUENCE_NAME_LENGTH_VALUE) + QString::number(p_pClass->GetId()) + FTL_SEQUENCE_NAME_SUFFIX;
        }
        else
        {
            qstrSequenceName = qstrKeyname + QString::number(p_pClass->GetId()) + FTL_SEQUENCE_NAME_SUFFIX;
        }
    }

    if (CwmsUtilities::IsKeynameSqlKeyword(qstrSequenceName))
    {
        qstrSequenceName += "1";
    }

    return qstrSequenceName;

}


QString CftlHelper::GenerateClassContainerSequenceTriggerName(CdmClass *p_pClass)
{
    QString qstrSequenceName;

    if (CHKPTR(p_pClass))
    {
        QString qstrKeyname = p_pClass->GetKeyname();

        if (qstrKeyname.length() > FTL_MAX_TRIGGER_NAME_LENGTH_VALUE)
        {
            qstrSequenceName = qstrKeyname.left(FTL_MAX_TRIGGER_NAME_LENGTH_VALUE) + QString::number(p_pClass->GetId()) + FTL_TRIGGER_NAME_SUFFIX;
        }
        else
        {
            qstrSequenceName = qstrKeyname + QString::number(p_pClass->GetId()) + FTL_TRIGGER_NAME_SUFFIX;
        }
    }

    if (CwmsUtilities::IsKeynameSqlKeyword(qstrSequenceName))
    {
        qstrSequenceName += "1";
    }

    return qstrSequenceName;
}

QString CftlHelper::GenerateMemberFieldName(CdmMember *p_pMember, CftlDialect* p_pDialect)
{
    QString qstrMemberFieldName;

    if (CHKPTR(p_pMember))
    {
        QString qstrKeyname = p_pMember->GetKeyname();
        int iMaxFieldNameLength = FTL_MAX_FIELD_NAME_LENGTH_VALUE;

        if (CHKPTR(p_pDialect))
        {
            iMaxFieldNameLength = p_pDialect->GetMaxFieldNameLength();
        }


        if (p_pMember->GetValueType() == eDmValueBinaryDocument ||
                p_pMember->GetValueType() == eDmValueObjectRef)
        {
            iMaxFieldNameLength -= 5; // because more than one column for this field we have to add additional infos in fieldname
        }

        if (qstrKeyname.length() > iMaxFieldNameLength)
        {
            qstrMemberFieldName = qstrKeyname.left(iMaxFieldNameLength) + QString::number(p_pMember->GetId());
        }
        else
        {
            qstrMemberFieldName = qstrKeyname;
        }
    }

    if (CwmsUtilities::IsKeynameSqlKeyword(qstrMemberFieldName))
    {
        qstrMemberFieldName += "1";
    }

    return qstrMemberFieldName;
}

void CftlHelper::FillFieldValues(QString p_qstrPlaceholder,
                                 const CdmMember* p_pMember,
                                 CdmObject* p_pObject,
                                 QVariantMap& p_rMap,
                                 CftlInterface *p_pInterface)
{

    if (CHKPTR(p_pMember) && !p_qstrPlaceholder.isEmpty())
    {
        CdmValue* pValue = p_pObject->GetValue(p_pMember->GetKeyname());

        if (CHKPTR(pValue))
        {
            switch (p_pMember->GetValueType())
            {
            case eDmValueBool:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueBool*> (pValue)->GetValue());
                break;
            case eDmValueInt:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueInt*> (pValue)->GetValue());
                break;
            case eDmValueLong:
                p_rMap.insert(p_qstrPlaceholder, (int)dynamic_cast<CdmValueLong*> (pValue)->GetValue());
                break;
            case eDmValueFloat:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueFloat*> (pValue)->GetValue());
                break;
            case eDmValueDouble:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueDouble*> (pValue)->GetValue());
                break;
            case eDmValueString:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueString*> (pValue)->GetValue());
                break;
            case eDmValueDate:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueDate*> (pValue)->GetValue());
                break;
            case eDmValueTime:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueTime*> (pValue)->GetValue());
                break;
            case eDmValueDateTime:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueDateTime*> (pValue)->GetValue());
                break;
            case eDmValueObjectRef:
                p_rMap.insert(p_qstrPlaceholder + FTL_OBJECT_REF_OBJECT_SUFFIX, (int)dynamic_cast<CdmValueObjectRef*> (pValue)->GetValue());
                p_rMap.insert(p_qstrPlaceholder + FTL_OBJECT_REF_CONTAINER_SUFFIX, (int)dynamic_cast<CdmValueObjectRef*> (pValue)->GetObjectListId());
                break;
            case eDmValueContainerRef:
                p_rMap.insert(p_qstrPlaceholder, (int)dynamic_cast<CdmValueContainerRef*> (pValue)->GetValue());
                break;
            case eDmValueCounter:
            {
                CdmValueCounter* pCounter = dynamic_cast<CdmValueCounter*> (pValue);
                int iValue = pCounter->GetValue();
                if (iValue == 0)
                {
                    GetCounterValue(dynamic_cast<CdmValueCounter*> (pValue), p_pInterface);
                    p_rMap.insert(p_qstrPlaceholder, (int) dynamic_cast<CdmValueCounter*> (pValue)->GetValue());
                }

                break;
            }
            case eDmValueBinaryDocument:
            {
                CdmValueBinaryDocument* pBinDoc = dynamic_cast<CdmValueBinaryDocument*> (pValue);
                p_rMap.insert(p_qstrPlaceholder + FTL_BIN_DOC_FILENAME_SUFFIX, pBinDoc->GetFilename());
                p_rMap.insert(p_qstrPlaceholder + FTL_BIN_DOC_CONTENT_SUFFIX,  pBinDoc->GetBase64());
                break;
            }
                // Chardocs and derived documents from chardoc as xml
            case eDmValueCharacterDocument:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueListInt:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueListDouble:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueListString:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueDictStringInt:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueDictStringString:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueDictStringDouble:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());
                break;
            case eDmValueDictIntInt:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());

                break;
            case eDmValueDictIntString:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());

                break;
            case eDmValueDictIntDouble:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());

                break;
            case eDmValueListObjects:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueCharacterDocument*> (pValue)->GetValue());

                break;
            case eDmValueUser:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueInt*> (pValue)->GetValue());
                break;
            case eDmValueUserGroup:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueInt*> (pValue)->GetValue());
                break;
            case eDmValueEnum:
                p_rMap.insert(p_qstrPlaceholder, dynamic_cast<CdmValueInt*> (pValue)->GetValue());
                break;
            case eDmValueFormula:
                break;
            default:
                ERR("Invalid Value for writing to object list!!!");
                break;
            }
        }
    }
}


void CftlHelper::GetCounterValue(CdmValueCounter* p_pCdmCounter, CftlInterface *p_pInterface)
{
   if (CHKPTR(p_pCdmCounter))
   {
      const CdmObject* pCdmObject = p_pCdmCounter->GetObject();

      if (CHKPTR(pCdmObject))
      {
         long lObjectListId = pCdmObject->GetObjectContainerId();
         CdmClass* pClass = pCdmObject->GetClass();
         const CdmMember* pMember = p_pCdmCounter->GetMember();
         if (CHKPTR(pClass) && CHKPTR(pMember))
         {
             QString qstrClassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
             QString qstrMemberFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();

             int iValue = GetCounterValue(lObjectListId,
                                          qstrClassTableName,
                                          qstrMemberFieldName,
                                          p_pInterface);

             dynamic_cast<CdmValueLong*>(p_pCdmCounter)->SetValue(iValue);
         }
      }
   }
}

long CftlHelper::GetCounterValue(long p_lObjectListId,
                                 QString& p_qstrTableName,
                                 QString& p_qstrMemberFieldName,
                                 CftlInterface *p_pInterface)
{
   long lRet = CdmLogging::eDmObjectAccessError;
   QString qstrQuery;
   QSqlQuery querySelect(p_pInterface->GetSqlDatabase());

   qstrQuery = QString("select MAX(%1) from %2 where %3 = ?")
           .arg(p_qstrMemberFieldName)
           .arg(p_qstrTableName)
           .arg(FTL_CONTAINER_ID_FIELD_NAME);

   querySelect.prepare(qstrQuery);
   querySelect.bindValue(0, static_cast<int>(p_lObjectListId));

   lRet = p_pInterface->ExecuteQuery(querySelect);

   if(lRet > 0)
   {
      long lValue = 0;
      querySelect.first();

      if(querySelect.isValid())
      {
         lValue = querySelect.value(0).toInt() + 1;
      }

      lRet = lValue;
   }

   return lRet;
}

QString CftlHelper::GenerateClassContainerIndexNameFromTableName(QString p_qstrTableName, int p_iIndexCounter, CftlDialect* p_pDialect)
{
   QString qstrIndexName;

   int iMaxTableNameLength = FTL_MAX_TABLE_NAME_LENGTH_VALUE;

   if (CHKPTR(p_pDialect))
   {
       iMaxTableNameLength = p_pDialect->GetMaxTableNameLength();
   }

   if (p_qstrTableName.length() > iMaxTableNameLength)
   {
       p_qstrTableName = p_qstrTableName.right(iMaxTableNameLength);
   }

   qstrIndexName = "idx_" + p_qstrTableName + QString::number(p_iIndexCounter);


   return qstrIndexName;
}

const CdmClass* CftlHelper::GetClassFromQuery(CdmQuery* p_pQuery)
{
    if (CHKPTR(p_pQuery))
    {
        if (p_pQuery->GetContainerId() > 0)
        {
            CdmObjectContainer* pContainer = p_pQuery->GetContainer();

            if (CHKPTR(pContainer))
            {
                return pContainer->GetClass();
            }
        }
        else if (p_pQuery->GetClassId() > 0)
        {
            return p_pQuery->GetClass();
        }
    }

    return nullptr;
}

QString CftlHelper::GetClassTableName(CdmQuery* p_pQuery)
{
    if (CHKPTR(p_pQuery))
    {
        const CdmClass* pClass = GetClassFromQuery(p_pQuery);
        if (CHKPTR(pClass))
        {
            return pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
        }
    }

    return "";
}

QString CftlHelper::GetClassTableName(const CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        return p_pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
    }

    return "";
}

QString CftlHelper::GetClassMemberFieldNameFromQueryElement(CdmQueryElement* p_pElement)
{
    if (CHKPTR(p_pElement))
    {
        const CdmMember* pMember = GetLastMemberOfQueryElementReference(p_pElement);

        if (CHKPTR(pMember))
        {
            return pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();
        }
    }

    return "";
}

const CdmMember* CftlHelper::GetMemberOfQueryElement(CdmQueryElement* p_pElement)
{
    if (CHKPTR(p_pElement))
    {
        CdmQuery* pQuery = p_pElement->GetQuery();

        if (CHKPTR(pQuery))
        {
            const CdmClass* pClass = GetClassFromQuery(pQuery);

            if (CHKPTR(pClass))
            {
                QString qstrCompareKeyname = p_pElement->GetCompareKeyname();

                if (qstrCompareKeyname.contains("."))
                {
                    qstrCompareKeyname = qstrCompareKeyname.split(".")[0];
                }

                return pClass->FindMember(qstrCompareKeyname);
            }
        }
    }

    return nullptr;
}

const CdmMember* CftlHelper::GetMemberOfReferenceList(const CdmClass* pClass, QString& p_qstrSelectMember)
{
    if (CHKPTR(pClass))
    {
        if (p_qstrSelectMember.contains("."))
        {
            p_qstrSelectMember = p_qstrSelectMember.split(".")[0];
        }

        return pClass->FindMember(p_qstrSelectMember);
    }

    return nullptr;
}

CdmQueryElement* CftlHelper::GetNextQueryElementReference(CdmQueryElement* p_pElement)
{
    CdmQueryElement* pElement = nullptr;

    if (CHKPTR(p_pElement) && p_pElement->HasSubQuery())
    {
        CdmQuery* pQuery = p_pElement->GetSubQuery();

        if (CHKPTR(pQuery))
        {
            pElement = pQuery->GetQueryElement();
        }
    }

    return pElement;
}

CdmQueryElement* CftlHelper::GetLastQueryElementReference(CdmQueryElement* p_pElement)
{
    CdmQueryElement* pElement = nullptr;

    if (CHKPTR(p_pElement))
    {
        pElement = p_pElement;

        while (pElement && pElement->HasSubQuery())
        {
            pElement = GetNextQueryElementReference(pElement);
        }

        if (pElement == p_pElement)
        {
            pElement = nullptr;
        }
    }

    return pElement;
}

const CdmMember* CftlHelper::GetLastMemberOfQueryElementReference(CdmQueryElement* p_pElement)
{
    const CdmMember* pMember = nullptr;

    if (CHKPTR(p_pElement))
    {
        if (HasMultipleReferences(p_pElement))
        {
            CdmQuery* pQuery = p_pElement->GetQuery();

            if (CHKPTR(pQuery))
            {
                const CdmClass* pClass = GetClassFromQuery(pQuery);

                if (CHKPTR(pClass))
                {
                    QString qstrCompareKeyname = p_pElement->GetCompareKeyname();
                    pMember = pClass->FindMember(qstrCompareKeyname);
                }
            }
        }
        else if (p_pElement->HasSubQuery())
        {
            CdmQueryElement* pLastElement = GetLastQueryElementReference(p_pElement);
            pMember = GetMemberOfQueryElement(pLastElement);
        }
        else
        {
            pMember = GetMemberOfQueryElement(p_pElement);
        }
    }

    return pMember;
}

bool CftlHelper::HasMultipleReferences(CdmQueryElement* p_pElement)
{
    bool bRet = false;

    if (CHKPTR(p_pElement))
    {
        QString qstrCompareKeyname = p_pElement->GetCompareKeyname();

        if (qstrCompareKeyname.contains("."))
        {
            bRet = true;
        }
    }

    return bRet;
}

CdmClass* CftlHelper::GetClassOfMember(CdmQueryElement* p_pElement)
{
    if (CHKPTR(p_pElement))
    {
        const CdmMember* pMember = GetMemberOfQueryElement(p_pElement);

        if (CHKPTR(pMember))
        {
            return pMember->GetClass();
        }
    }

    return nullptr;
}

QString CftlHelper::GetDefaultSelect(CdmClass* p_pClass)
{
    return GetDefaultSelect(p_pClass, nullptr);
}

QString CftlHelper::GetUnionJoinSelect(const CdmClass* p_pClass)
{
    QString qstrRet;
    if (CHKPTR(p_pClass))
    {
        QString qstrClassTable = CftlHelper::GetClassTableName(p_pClass);

        qstrRet = QString("select distinct %1, %2, " FTL_MEMBER_PLACEHOLDER " from %3")
                .arg(FTL_OBJECT_ID_FIELD_NAME)
                .arg(FTL_CONTAINER_ID_FIELD_NAME)
                .arg(qstrClassTable);
    }

    return qstrRet;
}


QString CftlHelper::GetDefaultSelect(CdmClass* p_pClass, CdmObjectContainer* p_pContainer)
{
    QString qstrRet;
    if (CHKPTR(p_pClass))
    {
        QString qstrClassTable = CftlHelper::GetClassTableName(p_pClass);

        qstrRet = QString("select %1, %2 from %3")
                .arg(FTL_OBJECT_ID_FIELD_NAME)
                .arg(FTL_CONTAINER_ID_FIELD_NAME)
                .arg(qstrClassTable);

        if (p_pContainer)
        {
            qstrRet += QString(" where %1 = %2")
                    .arg(FTL_CONTAINER_ID_FIELD_NAME)
                    .arg(p_pContainer->GetId());
        }
    }

    return qstrRet;
}

QString CftlHelper::GetUnionOfSubclasses(const CdmClass* p_pClass)
{
    QString qstrJoin = QString();

    if (CHKPTR(p_pClass))
    {
        QList<long> qllClasses = p_pClass->GetDerivedClasses();

        if (qllClasses.count() == 0)
        {
            qstrJoin += CftlHelper::GetClassTableName(p_pClass);
        }
        else
        {
            CdmClassManager* pClassManager = p_pClass->GetClassManager();

            if (CHKPTR(pClassManager))
            {
                bool bFirst = true;
                qstrJoin += "(";
                for (int iPos = 0; iPos < qllClasses.count(); ++iPos)
                {
                    CdmClass* pBaseClass = pClassManager->FindClassById(qllClasses[iPos]);

                    if (!pBaseClass->IsAbstract())
                    {
                       if (!bFirst)
                        {
                            qstrJoin += " union ";
                        }
                        else
                        {
                            bFirst = false;
                        }

                        qstrJoin += CftlHelper::GetUnionJoinSelect(pBaseClass);
                    }
                }

                if (!p_pClass->IsAbstract())
                {
                    qstrJoin += " union " + CftlHelper::GetUnionJoinSelect(p_pClass);
                }

                qstrJoin += ")";
            }
        }
    }

    return qstrJoin;
}

QString CftlHelper::GetBaseMemberFieldName(const CdmMember *p_pMember)
{
    QString qstrRet = "";

    if (CHKPTR(p_pMember))
    {
        qstrRet = p_pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();
    }

    return qstrRet;
}

QString CftlHelper::GetMemberFieldName(const CdmMember *p_pMember)
{
    QString qstrRet = GetBaseMemberFieldName(p_pMember);

    if (CHKPTR(p_pMember))
    {
        EdmValueType type = p_pMember->GetValueType();
        switch (type) {
        case eDmValueObjectRef:
            qstrRet += FTL_OBJECT_REF_OBJECT_SUFFIX;
            break;
        case eDmValueBinaryDocument:
            qstrRet += FTL_BIN_DOC_FILENAME_SUFFIX;
            break;
        default:
            break;
        }
    }

    return qstrRet;
}
