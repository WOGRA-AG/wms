/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CftlHelper.h
 ** Started Implementation: 2012/08/30
 ** Description:
 ** 
 ** Helper class with static functions
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CODBCHELPER_H
#define CODBCHELPER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QDateTime>

// Own Includes
#include "CftlDataAccess.h"

// DEFINES
#define FTL_CLASS_TABLE_NAME "classTableName"
#define FTL_MEMBER_FIELD_NAME "memberFieldName"
#define FTL_MAX_TABLE_NAME_LENGTH_VALUE 55
#define FTL_MAX_FIELD_NAME_LENGTH_VALUE 55
#define FTL_MAX_TRIGGER_NAME_LENGTH_VALUE 55
#define FTL_MAX_SEQUENCE_NAME_LENGTH_VALUE 55
#define FTL_TRIGGER_NAME_SUFFIX "_trg"
#define FTL_SEQUENCE_NAME_SUFFIX "_seq"
#define FTL_BIN_DOC_FILENAME_SUFFIX "_FILE"
#define FTL_BIN_DOC_CONTENT_SUFFIX "_DATA"
#define FTL_OBJECT_REF_CONTAINER_SUFFIX "_CONT"
#define FTL_OBJECT_REF_OBJECT_SUFFIX "_OBJ"
#define FTL_OBJECT_REF_OBJECT_KEYNAME_SUFFIX "_OBJKEYNAME"
#define FTL_OBJECT_REF_OBJECT_CONTAINER_KEYNAME_SUFFIX "_OBJCONTAINERKEYNAME"

// Forwards
class CdmQueryElement;
class CdmQuery;
class CdmValueCounter;
class CftlDialect;
// TypeDefs

/* 
 * This class is a helper class with static functions
 */
class CftlHelper
{
public:
    static QString GenerateClassContainerTableName(CdmClass* p_pClass, CftlDialect* p_pDialect);
    static QString GenerateMemberFieldName(CdmMember* p_pMember, CftlDialect* p_pDialect);
    static QString GenerateClassContainerSequenceTriggerName(CdmClass *p_pClass);
    static QString GenerateClassContainerSequenceName(CdmClass *p_pClass);
    static void FillFieldValues(QString p_qstrPlaceholder, const CdmMember *p_pMember, CdmObject *p_pObject, QVariantMap &p_rMap, CftlInterface *p_pInterface);
    static QString GenerateClassContainerIndexNameFromTableName(QString p_qstrTableName, int p_iIndexCounter, CftlDialect *p_pDialect);
    static const CdmClass *GetClassFromQuery(CdmQuery *p_pQuery);
    static QString GetClassTableName(CdmQuery *p_pQuery);
    static QString GetClassMemberFieldNameFromQueryElement(CdmQueryElement *p_pElement);
    static CdmClass *GetClassOfMember(CdmQueryElement *p_pElement);
    static QString GetClassTableName(const CdmClass *p_pClass);
    static QString GetDefaultSelect(CdmClass *p_pClass, CdmObjectContainer *p_pContainer);
    static QString GetDefaultSelect(CdmClass *p_pClass);
    static const CdmMember *GetMemberOfQueryElement(CdmQueryElement *p_pElement);
    static const CdmMember *GetLastMemberOfQueryElementReference(CdmQueryElement *p_pElement);
    static bool HasMultipleReferences(CdmQueryElement *p_pElement);
    static CdmQueryElement *GetNextQueryElementReference(CdmQueryElement *p_pElement);
    static CdmQueryElement *GetLastQueryElementReference(CdmQueryElement *p_pElement);
    static QString GetUnionJoinSelect(const CdmClass *p_pClass);
    static const CdmMember *GetMemberOfReferenceList(const CdmClass *pClass, QString &p_qstrSelectMember);
    static QString GetUnionOfSubclasses(const CdmClass* p_pClass);
    static QString GetBaseMemberFieldName(const CdmMember *p_pMember);
    static QString GetMemberFieldName(const CdmMember *p_pMember);
private:
    static void GetCounterValue(CdmValueCounter *p_pCdmCounter, CftlInterface *p_pInterface);
    static long GetCounterValue(long p_lObjectListId, QString &p_qstrTableName, QString &p_qstrMemberFieldName, CftlInterface *p_pInterface);
};

#endif // CODBCHELPER_H
