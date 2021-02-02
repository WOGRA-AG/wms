
// WMS COre Includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"

// own Includes
#include "CftlHelper.h"
#include "CftlDialect.h"
#include "CftlContainerTableAlter.h"

CftlContainerTableAlter::CftlContainerTableAlter(CdmClass* p_pClass, CftlDialect* p_ppDialect)
    : CftlContainerTableBase(p_ppDialect),
      m_rpClass(p_pClass)
{

}

CftlContainerTableAlter::~CftlContainerTableAlter()
{

}

void CftlContainerTableAlter::GenerateMemberSqls(QStringList& qstrlQueries)
{
    QMap<long, CdmMember*> qmMembers;
    m_rpClass->GetMemberMap(qmMembers);

    QMapIterator<long, CdmMember*> qmIt(qmMembers);
    QList<CdmMember*> qlNewMembers;
    QList<CdmMember*> qlModifiedMembers;
    QList<CdmMember*> qlDeletedMembers;

    while (qmIt.hasNext())
    {
        qmIt.next();
        CdmMember* pMember = qmIt.value();

        if (pMember->IsNew() &&
            !pMember->IsDeleted() &&
            pMember->IsPersistent() &&
            pMember->GetValueType() != eDmValueFormula)
        {
            qlNewMembers.append(pMember);
        }
        else if (pMember->IsModified() &&
                 !pMember->IsDeleted() &&
                 pMember->IsPersistent() &&
                 pMember->GetValueType() != eDmValueFormula)
        {
            qlModifiedMembers.append(pMember);
        }
        else if (pMember->IsDeleted() &&
                 !pMember->IsNew() &&
                 pMember->IsPersistent() &&
                 pMember->GetValueType() != eDmValueFormula)
        {
            qlDeletedMembers.append(pMember);
        }
        else
        {
            INFO("Member " + pMember->GetKeyname() + "is unmodified nothing will be done.");
        }
    }

    QString qstrTableName = m_rpClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
    QList<long> qlDerivedClasses = m_rpClass->GetDerivedClasses();
    CdmClassManager* pClassManager = m_rpClass->GetClassManager();

    if (CHKPTR(pClassManager))
    {
        if (!qlNewMembers.isEmpty())
        {
            qstrlQueries.append(AddNewMemberSql(qlNewMembers, qstrTableName));

            for (int pos = 0; pos < qlDerivedClasses.count(); ++pos)
            {
                long lId = qlDerivedClasses[pos];
                CdmClass* pClass = pClassManager->FindClassById(lId);

                if (CHKPTR(pClass) && !pClass->IsAbstract())
                {
                    QString qstrclassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                    qstrlQueries.append(AddNewMemberSql(qlNewMembers, qstrclassTableName));
                }
            }

        }

        if (!qlModifiedMembers.isEmpty())
        {
            qstrlQueries.append(UpdateMembersSql(qlModifiedMembers, qstrTableName));

            for (int pos = 0; pos < qlDerivedClasses.count(); ++pos)
            {
                long lId = qlDerivedClasses[pos];
                CdmClass* pClass = pClassManager->FindClassById(lId);

                if (CHKPTR(pClass) && !pClass->IsAbstract())
                {
                    QString qstrclassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                    qstrlQueries.append(UpdateMembersSql(qlModifiedMembers, qstrclassTableName));
                }
            }
        }

        if (!qlDeletedMembers.isEmpty())
        {
            qstrlQueries.append(DeleteMembersSql(qlDeletedMembers, qstrTableName));

            for (int pos = 0; pos < qlDerivedClasses.count(); ++pos)
            {
                long lId = qlDerivedClasses[pos];
                CdmClass* pClass = pClassManager->FindClassById(lId);

                if (CHKPTR(pClass) && !pClass->IsAbstract())
                {
                    QString qstrclassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                    qstrlQueries.append(DeleteMembersSql(qlNewMembers, qstrclassTableName));
                }
            }
        }
    }
}

void CftlContainerTableAlter::GenerateRenamingSqls(QStringList& qstrlQueries)
{
    QString qstrTableName = CftlHelper::GenerateClassContainerTableName(m_rpClass, GetDialect());
    QString qstrOriginalName = m_rpClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();

    if (qstrTableName != qstrOriginalName)
    {
        QString qstrTemplate = GetDialect()->GetRenameTableTemplate();
        qstrTemplate.replace(FTL_TABLE_NAME_PLACEHOLDER, qstrOriginalName);
        qstrTemplate.replace(FTL_NEW_NAME_PLACEHOLDER, qstrTableName);
        qstrlQueries.append(qstrTemplate);
        m_rpClass->SetConfigItem(FTL_CLASS_TABLE_NAME, qstrTableName);
    }
}

void CftlContainerTableAlter::GenerateBaseClassChangesSqls(QStringList& qstrlQueries)
{
    if (m_rpClass->HasBaseClassChanges())
    {
        QList<long> qlChangedBaseClasses = m_rpClass->GetBaseClassChanges();
        QMap<long,long> qmBaseClasses = m_rpClass->GetBaseClasses();

        for (int iPos = 0; iPos < qlChangedBaseClasses.count(); ++iPos)
        {
            long lClassId = qlChangedBaseClasses[iPos];
            CdmClassManager* pClassManager = m_rpClass->GetClassManager();

            if (CHKPTR(pClassManager))
            {
                CdmClass* pClass = pClassManager->FindClassById(lClassId);

                if (CHKPTR(pClass))
                {
                    QMap<long, CdmMember*> qmMembers;
                    pClass->GetMemberMap(qmMembers);

                    QMapIterator<long, CdmMember*> qmIt(qmMembers);
                    QList<CdmMember*> qlMembers;

                    while (qmIt.hasNext())
                    {
                        qmIt.next();
                        CdmMember* pMember = qmIt.value();
                        if (pMember->IsPersistent() &&
                        pMember->GetValueType() != eDmValueFormula)
                        {
                            if (!qlMembers.contains(pMember))
                            {
                                qlMembers.append(pMember);
                            }
                        }
                    }

                    QList<long> qlBaseClasses = qmBaseClasses.values();
                    QString qstrTableName = m_rpClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                    QList<long> qlDerivedClasses = m_rpClass->GetDerivedClasses();
                    CdmClassManager* pClassManager = m_rpClass->GetClassManager();

                    if (CHKPTR(pClassManager))
                    {
                        if (qlBaseClasses.contains(lClassId)) // Base class added must be added
                        {
                            qstrlQueries.append(AddNewMemberSql(qlMembers, qstrTableName));
                            for (int pos = 0; pos < qlDerivedClasses.count(); ++pos)
                            {
                                long lId = qlDerivedClasses[pos];
                                CdmClass* pClass = pClassManager->FindClassById(lId);

                                if (CHKPTR(pClass) && !pClass->IsAbstract())
                                {
                                    QString qstrclassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                                    qstrlQueries.append(AddNewMemberSql(qlMembers, qstrclassTableName));
                                }
                            }
                        }
                        else // Base class was removed must be deleted
                        {
                            qstrlQueries.append(DeleteMembersSql(qlMembers, qstrTableName));

                            for (int pos = 0; pos < qlDerivedClasses.count(); ++pos)
                            {
                                long lId = qlDerivedClasses[pos];
                                CdmClass* pClass = pClassManager->FindClassById(lId);

                                if (CHKPTR(pClass) && !pClass->IsAbstract())
                                {
                                    QString qstrclassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                                    qstrlQueries.append(DeleteMembersSql(qlMembers, qstrclassTableName));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

QStringList CftlContainerTableAlter::GenerateSqls()
{
    QStringList qstrlQueries;
    GenerateMemberSqls(qstrlQueries);
    GenerateBaseClassChangesSqls(qstrlQueries);
    GenerateRenamingSqls(qstrlQueries);


    return qstrlQueries;
}

QString CftlContainerTableAlter::AddNewMemberSqlString(CdmMember* pMember)
{
    QString qstrSql;

    if (CHKPTR(pMember))
    {
        QString qstrFieldName = CftlHelper::GenerateMemberFieldName(pMember, GetDialect());
        qstrSql = AddNewMemberSqlString(pMember, qstrFieldName);
        pMember->SetConfigItem(FTL_MEMBER_FIELD_NAME, qstrFieldName);
    }

    return qstrSql;
}

QString CftlContainerTableAlter::AddNewMemberSqlString(CdmMember* pMember, QString& p_qstrFieldName)
{
    QString qstrSql;

    if (CHKPTR(pMember))
    {
        EdmValueType eType = pMember->GetValueType();
        QString qstrType = GetDialect()->getType(eType);

        switch (eType) {
        case eDmValueBinaryDocument:
        {
            QString qstrNameField = p_qstrFieldName + FTL_BIN_DOC_FILENAME_SUFFIX;
            qstrSql += qstrNameField + " " + GetDialect()->getType(eDmValueString);
            QString qstrDataField = p_qstrFieldName + FTL_BIN_DOC_CONTENT_SUFFIX;
            qstrSql += ", " + qstrDataField + " " + qstrType;
            break;
        }
        case eDmValueObjectRef:
        {
            QString qstrContainerRefField = p_qstrFieldName + FTL_OBJECT_REF_CONTAINER_SUFFIX;
            qstrSql += qstrContainerRefField + " " + GetDialect()->getType(eType);
            QString qstrObjectRefField = p_qstrFieldName + FTL_OBJECT_REF_OBJECT_SUFFIX;
            qstrSql += ", " + qstrObjectRefField + " " + qstrType;
            break;
        }
        default:
            qstrSql += p_qstrFieldName + " " + GetDialect()->getType(eType);
            break;
        }
    }

    return qstrSql;
}


QString CftlContainerTableAlter::AddNewMemberSql(QList<CdmMember*>& p_qlMembers, QString& qstrTableName)
{
    QString qstrSql;

    if (!qstrTableName.isEmpty() && p_qlMembers.count() > 0)
    {
        bool bFirst = true;
        qstrSql = QString("alter table %1 %2 (")
                .arg(qstrTableName)
                .arg(GetDialect()->GetAddColumnString());

        for (int iPos = 0; iPos < p_qlMembers.count(); ++iPos)
        {
            if (!bFirst)
            {
                qstrSql += ", ";
            }
            else
            {
                bFirst = false;
            }

            CdmMember* pMember = p_qlMembers[iPos];
            qstrSql += AddNewMemberSqlString(pMember);
        }

        qstrSql += ")";
    }

    return qstrSql;
}

QStringList CftlContainerTableAlter::UpdateMembersSql(QList<CdmMember*>& p_qlMembers, QString& qstrTableName)
{
    QStringList qstrlQueries;


    if (!qstrTableName.isEmpty())
    {
        for (int iPos = 0; iPos < p_qlMembers.count(); ++iPos)
        {
            CdmMember* pMember = p_qlMembers[iPos];
            qstrlQueries.append(GenerateUpdateQueries(pMember));
        }
    }
    else
    {
        ERR("Tablename for class " + m_rpClass->GetFullQualifiedName() + " not found!");
    }

    return qstrlQueries;
}

QStringList CftlContainerTableAlter::GenerateUpdateQueries(CdmMember* p_pMember)
{
    QStringList qstrlSqls;

    if (CHKPTR(p_pMember))
    {
        QString qstrTableName = m_rpClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
        QString qstrFieldName = CftlHelper::GenerateMemberFieldName(p_pMember, GetDialect());
        QString qstrOriginalFieldName = p_pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();
        EdmValueType eOriginalType = static_cast<EdmValueType> (p_pMember->GetTemporaryData(WMS_MEMBER_ORIGINAL_VALUE_TYPE).toInt());

        if (qstrFieldName != qstrOriginalFieldName && p_pMember->GetValueType() == eOriginalType)
        {

            QString qstrTemplate = GetDialect()->GetRenameFieldTemplate();
            qstrTemplate.replace(FTL_TABLE_NAME_PLACEHOLDER, qstrTableName);
            qstrTemplate.replace(FTL_ORIGINAL_NAME_PLACEHOLDER, qstrOriginalFieldName);
            qstrTemplate.replace(FTL_NEW_NAME_PLACEHOLDER, qstrFieldName);
            qstrTemplate.replace(FTL_TYPE_PLACEHOLDER, GetDialect()->getType(p_pMember->GetValueType()));
            qstrlSqls.append(qstrTemplate);
        }

        if (p_pMember->HasTemporaryData(WMS_MEMBER_ORIGINAL_VALUE_TYPE))
        {
            if (p_pMember->GetValueType() != eOriginalType)
            {
                // first drop the column
                QString qstrSql = QString("alter table %1 %2 %3")
                        .arg(qstrTableName)
                        .arg(GetDialect()->GetDropColumnString())
                        .arg(qstrOriginalFieldName);
                qstrlSqls.append(qstrSql);

                // second create the column

                qstrSql = QString("alter table %1 %2 (")
                        .arg(qstrTableName)
                        .arg(GetDialect()->GetAddColumnString());
                qstrSql += AddNewMemberSqlString(p_pMember, qstrFieldName);
                qstrSql += ")";
                qstrlSqls.append(qstrSql);
            }
        }

        if (qstrlSqls.count() > 0)
        {
            p_pMember->SetConfigItem(FTL_MEMBER_FIELD_NAME, qstrFieldName);
        }
    }

    return qstrlSqls;
}

QStringList CftlContainerTableAlter::DeleteMembersSql(QList<CdmMember*>& p_qlMembers, QString& qstrTableName)
{
    QStringList qstrlQueries;

    if (!qstrTableName.isEmpty())
    {
        for (int iPos = 0; iPos < p_qlMembers.count(); ++iPos)
        {
            CdmMember* pMember = p_qlMembers[iPos];

            if (CHKPTR(pMember))
            {
                QString qstrFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();

                if (!qstrFieldName.isEmpty())
                {
                    QString qstrSql = QString("alter table %1 %2 %3")
                            .arg(qstrTableName)
                            .arg(GetDialect()->GetDropColumnString())
                            .arg(qstrFieldName);

                    qstrlQueries.append(qstrSql);
                }
                else
                {
                    ERR("Member " + pMember->GetKeyname() + " has no field name don't know what to delete.");
                }

            }
        }
    }
    else
    {
        ERR("Tablename for class " + m_rpClass->GetFullQualifiedName() + " not found!");
    }

    return qstrlQueries;
}


bool CftlContainerTableAlter::IsValid()
{
    return (m_rpClass != nullptr);
}
