// WMS Core Includes
#include "CdmClass.h"


// own Includes
#include "CftlDialect.h"
#include "CftlHelper.h"
#include "CftlContainerTableDrop.h"

CftlContainerTableDrop::CftlContainerTableDrop(CdmClass* p_pClass, CftlDialect* p_ppDialect)
: CftlContainerTableBase(p_ppDialect),
  m_rpClass(p_pClass)
{
}

CftlContainerTableDrop::~CftlContainerTableDrop()
{

}

QStringList CftlContainerTableDrop::GenerateSqls()
{
    QStringList qstrlQueries;

    if (!m_rpClass->IsAbstract())
    {
        QString qstrTableName = m_rpClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();

        if (!qstrTableName.isEmpty())
        {
            QString qstrQuery = QString("drop table %1").arg(qstrTableName);
            qstrlQueries.append(qstrQuery);
        }
    }

    return qstrlQueries;
}

bool CftlContainerTableDrop::IsValid()
{
    return (m_rpClass != nullptr);
}
