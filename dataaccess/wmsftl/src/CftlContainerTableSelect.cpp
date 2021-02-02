// WMSCORE Includes
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"

// Own Includes
#include "CftlHelper.h"
#include "CftlDialect.h"
#include "CftlContainerTableSelect.h"

CftlContainerTableSelect::CftlContainerTableSelect(CdmObjectContainer* p_pContainer, CftlDialect* p_ppDialect)
    : CftlContainerTableBase(p_ppDialect),
      m_rpContainer(p_pContainer),
      m_iValueStartPos(0)
{
}

CftlContainerTableSelect::~CftlContainerTableSelect()
{

}

void CftlContainerTableSelect::SetObjectList(QLinkedList<long> &p_qlObjectIds)
{
    m_qlObjectIds = p_qlObjectIds;
}

void CftlContainerTableSelect::SetObjectList(QLinkedList<QString> &p_qlObjectKeynames)
{
    m_qlObjectKeynames = p_qlObjectKeynames;
}

int CftlContainerTableSelect::GetValueStartPos()
{
    return m_iValueStartPos;
}

QStringList CftlContainerTableSelect::GenerateSqls()
{
    QStringList qstrlQueries;
    const CdmClass* pClass = m_rpContainer->GetClass();

    if (CHKPTR(pClass))
    {
        QString qstrTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
        QString qstrSql = QString ("select %1 from %2 %3 where " FTL_CONTAINER_ID_FIELD_NAME " = %4")
                .arg(GenerateFields(pClass))
                .arg(qstrTableName)
                .arg(m_qstrlLeftJoins.join(" "))
                .arg(m_rpContainer->GetId());

        if (m_qlObjectIds.count() > 0)
        {
            qstrSql += QString(" and %1 in %2")
                    .arg(FTL_OBJECT_ID_FIELD_NAME)
                    .arg(GenerateInStringIds());
        }
        else if(m_qlObjectKeynames.count() > 0)
        {
            qstrSql += QString(" and %1 in %2")
                                .arg(FTL_OBJECT_KEYNAME_FIELD_NAME)
                                .arg(GenerateInStringKeynames());
        }

        qstrlQueries.append(qstrSql);
    }

    return qstrlQueries;
}

QMap<long, CdmMember*>& CftlContainerTableSelect::GetMemberMap()
{
    return m_qmMembers;
}

QString CftlContainerTableSelect::GenerateFields(const CdmClass* p_pClass)
{
    QString qstrFields;

    if (CHKPTR(p_pClass))
    {
        AddCommonFields(qstrFields);
        p_pClass->GetMemberMap(m_qmMembers);
        QMapIterator<long, CdmMember*> qmIt(m_qmMembers);

        while (qmIt.hasNext())
        {
            qmIt.next();
            CdmMember* pMember = qmIt.value();

            if (CHKPTR(pMember) && pMember->IsPersistent() && pMember->GetValueType() != eDmValueFormula)
            {
                qstrFields += ", ";
                EdmValueType eValue = pMember->GetValueType();
                QString qstrFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();

                switch (eValue)
                {
                case eDmValueBinaryDocument:
                {
                    QString qstrNameField = qstrFieldName + FTL_BIN_DOC_FILENAME_SUFFIX;
                    qstrFields += qstrNameField;
                    QString qstrDataField = qstrFieldName + FTL_BIN_DOC_CONTENT_SUFFIX;
                    qstrFields += ", " + qstrDataField;
                    break;
                }
                case eDmValueObjectRef:
                {
                    QString qstrContainerRefField = qstrFieldName + FTL_OBJECT_REF_CONTAINER_SUFFIX;
                    qstrFields += qstrContainerRefField;
                    QString qstrObjectRefField = qstrFieldName + FTL_OBJECT_REF_OBJECT_SUFFIX;
                    QString qstrObjectRefKeyname = qstrFieldName + FTL_OBJECT_REF_OBJECT_KEYNAME_SUFFIX;
                    QString qstrObjectRefContainerKeyname = qstrFieldName + FTL_OBJECT_REF_OBJECT_CONTAINER_KEYNAME_SUFFIX;
                    qstrFields += ", " + qstrObjectRefField;

                    auto lClass = pMember->GetClassReference();

                    if (lClass > 0)
                    {
                        auto pClassManager = pMember->GetClassManager();

                        if (CHKPTR(pClassManager))
                        {
                            auto pClass = pClassManager->FindClassById(lClass);

                            if (CHKPTR(pClass))
                            {
                                // add Object Keyname to select
                                QString qstrJoinName = "refjoin" + QString::number(m_qstrlLeftJoins.count());
                                QString qstrClassTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
                                qstrFields += ", " + qstrJoinName + "." FTL_OBJECT_KEYNAME_FIELD_NAME" as " + qstrObjectRefKeyname;

                                QString qstrJoin = QString("left join %1 %2 on %3 = %2.%4")
                                        .arg(qstrClassTableName)
                                        .arg(qstrJoinName)
                                        .arg(qstrObjectRefField)
                                        .arg(FTL_OBJECT_ID_FIELD_NAME);

                                m_qstrlLeftJoins.append(qstrJoin);
                            }
                        }
                    }

                    // add Container Keyname to select
                    QString qstrJoinName = "refjoin" + QString::number(m_qstrlLeftJoins.count());
                    qstrFields += ", " + qstrJoinName + "." FTL_OBJECT_KEYNAME_FIELD_NAME " as " + qstrObjectRefContainerKeyname;

                    QString qstrJoin = QString("left join %1 %2 on %3 = %2.%4")
                            .arg("WMS_DM_CONTAINER")
                            .arg(qstrJoinName)
                            .arg(qstrContainerRefField)
                            .arg(FTL_CONTAINER_ID_FIELD_NAME);

                    m_qstrlLeftJoins.append(qstrJoin);

                    break;
                }
                case eDmValueContainerRef:
                {
                    // add Container Keyname to select
                    QString qstrObjectRefContainerKeyname = qstrFieldName + FTL_OBJECT_REF_OBJECT_CONTAINER_KEYNAME_SUFFIX;
                    QString qstrJoinName = "refjoin" + QString::number(m_qstrlLeftJoins.count());
                    qstrFields += ", " + qstrJoinName + "." FTL_OBJECT_KEYNAME_FIELD_NAME " as " + qstrObjectRefContainerKeyname;

                    QString qstrJoin = QString("left join %1 %2 on %3 = %2.%4")
                            .arg("WMS_DM_CONTAINER")
                            .arg(qstrJoinName)
                            .arg(qstrFieldName)
                            .arg(FTL_CONTAINER_ID_FIELD_NAME);

                    m_qstrlLeftJoins.append(qstrJoin);

                    break;
                }
                default:
                    qstrFields += qstrFieldName;
                    break;
                }
            }
        }
    }

    return qstrFields;
}

void CftlContainerTableSelect::AddCommonFields(QString& qstrFields)
{
    qstrFields += FTL_OBJECT_ID_FIELD_NAME;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_OBJECT_KEYNAME_FIELD_NAME;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_OBJECT_CAPTION_FIELD_NAME;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_LAST_MODIFIED;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_CREATOR_ID;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_MODIFIER_ID;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_PARENT;
    ++m_iValueStartPos;
    qstrFields += ", " FTL_CONFIG;
    ++m_iValueStartPos;
}

QString CftlContainerTableSelect::GenerateInStringIds()
{
   QString qstrRet = "(";

   QLinkedList<long>::iterator qvlIt = m_qlObjectIds.begin();
   QLinkedList<long>::iterator qvlItEnd = m_qlObjectIds.end();

   while (qvlIt != qvlItEnd)
   {
      QString qstrId = QString::number(*qvlIt);
      qstrRet += qstrId;

      ++ qvlIt;

      if (qvlIt != qvlItEnd)
      {
         qstrRet += ", ";
      }
      else
      {
         qstrRet += ")";
         break;
      }
   }

   return qstrRet;
}

QString CftlContainerTableSelect::GenerateInStringKeynames()
{
   QString qstrRet = "(";

   QLinkedList<QString>::iterator qvlIt = m_qlObjectKeynames.begin();
   QLinkedList<QString>::iterator qvlItEnd = m_qlObjectKeynames.end();

   while (qvlIt != qvlItEnd)
   {
      QString qstrId = "'" + *qvlIt + "'";
      qstrRet += qstrId;

      ++ qvlIt;

      if (qvlIt != qvlItEnd)
      {
         qstrRet += ", ";
      }
      else
      {
         qstrRet += ")";
         break;
      }
   }

   return qstrRet;
}

bool CftlContainerTableSelect::IsValid()
{
    return (m_rpContainer != nullptr);
}
