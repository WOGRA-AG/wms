

// own Includes
#include "CftlDialect.h"
#include "CftlHelper.h"
#include "CftlJoinData.h"


QString CftlJoinData::JoinTemplate = "left join %1 %2 on %3.%4 = %2.%5 and %3.%6 = %2.%7";

CftlJoinData::CftlJoinData(QString p_qstrJoin, QString p_qstrJoinName, QString p_qstrReferenceMemberName)
    : m_qstrJoin(p_qstrJoin),
      m_qstrJoinName(p_qstrJoinName),
      m_qstrJoinPartner(),
      m_qstrReferenceMemberName(p_qstrReferenceMemberName)
{
}

CftlJoinData::CftlJoinData(QString p_qstrJoin, QString p_qstrJoinName, QString p_qstrReferenceMemberName, QString p_qstrJoinPartner)
    : m_qstrJoin(p_qstrJoin),
      m_qstrJoinName(p_qstrJoinName),
      m_qstrJoinPartner(p_qstrJoinPartner),
      m_qstrReferenceMemberName(p_qstrReferenceMemberName)
{
}

QString CftlJoinData::GenerateJoin() const
{
    QString qstrJoin;
    qstrJoin = GetJoinTemplate()    // left join %1 %2 on %3.%4 = %2.%5 and %3.%6 = %2.%7
            .arg(m_qstrJoin)
            .arg(m_qstrJoinName)
            .arg(GetJoinPartner())
            .arg(m_qstrReferenceMemberName + FTL_OBJECT_REF_OBJECT_SUFFIX)
            .arg(FTL_OBJECT_ID_FIELD_NAME)
            .arg(m_qstrReferenceMemberName + FTL_OBJECT_REF_CONTAINER_SUFFIX)
            .arg(FTL_CONTAINER_ID_FIELD_NAME);

    qstrJoin = qstrJoin.replace(FTL_MEMBER_PLACEHOLDER, m_qstrlSearchableMembers.join(","));

    return qstrJoin;
}

void CftlJoinData::AddJoinMember(QString p_qstrMember)
{
    if (!m_qstrlSearchableMembers.contains(p_qstrMember))
    {
        m_qstrlSearchableMembers.append(p_qstrMember);
    }
}

QString CftlJoinData::GetJoinName() const
{
    return m_qstrJoinName;
}

QString CftlJoinData::GetJoinPartner() const
{
    QString qstrRet = "o1";

    if (HasJoinPartner())
    {
        qstrRet = m_qstrJoinPartner;

    }

    return qstrRet;
}

bool CftlJoinData::HasJoinPartner() const
{
    bool bRet = false;

    if (!m_qstrJoinPartner.isEmpty() && m_qstrJoinPartner != "o1")
    {
        bRet = true;
    }

    return bRet;
}

QString CftlJoinData::GetJoinTemplate()
{
    return CftlJoinData::JoinTemplate;
}
