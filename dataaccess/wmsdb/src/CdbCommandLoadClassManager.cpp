
// WMS Includes
#include "CdmClassManager.h"

// Own Includes
#include "CdbCommandLoadClassManager.h"
#include "CdbCommandGetClass.h"
#include "CdbCommandLoadPackages.h"

CdbCommandLoadClassManager::CdbCommandLoadClassManager(long p_lSchemeId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_pClassManager(nullptr)
{
}

CdbCommandLoadClassManager::~CdbCommandLoadClassManager()
{

}

int CdbCommandLoadClassManager::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    m_pClassManager = CdmDataAccessHelper::CreateClassManager(m_lSchemeId);
    CdbCommandLoadPackages commandLoadPackages(m_pClassManager, GetDataAccess());
    commandLoadPackages.Run();


    // first step load all classes with DataBaseId == p_lDataBaseId
    qstrQuery = QString("select ClassId from WMS_CLASS where DataBaseId = %1")
                        .arg(m_lSchemeId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       // second step call for each class getclass
       cQSqlQuery.first();
       if(cQSqlQuery.isValid())
       {
          QList<int> qlClasses;

          do // loading each class
          {
             long lClassId = cQSqlQuery.value(0).toInt();
             qlClasses.append(lClassId);
          }
          while(cQSqlQuery.next());

          for (int iCounter = 0; iCounter < qlClasses.count(); ++iCounter)
          {
             long lClassId = qlClasses[iCounter];
             if (!m_pClassManager->FindClassById(lClassId))
             {
                INFO("Load class with ID '" + QString::number(lClassId) + "'");
                CdmClass* pCdmClass = nullptr;

				CdbCommandGetClass commandGetClass(m_pClassManager, lClassId, GetDataAccess());
                iRet = commandGetClass.Run();
                pCdmClass = commandGetClass.GetResult();

                if(CHKPTR(pCdmClass) && iRet > 0)
                {
                   INFO("Adding class with ID '" + QString::number(lClassId) + "'");
                }
                else
                {
                   ERR("Could not load class with ID: " + QString::number(lClassId));
                   break;
                }
             }
          }
       }
       else
       {
          iRet = EC(eDmOk);
       }
    }
    else
    {
       iRet = EC(eDmInvalidSelectStatement);
       ERR("Base Class Query pronounced an error!!!");
    }


    return iRet;
}

CdmClassManager *CdbCommandLoadClassManager::GetResult()
{
    return m_pClassManager;
}

bool CdbCommandLoadClassManager::CheckValid()
{
    return (m_lSchemeId > 0);
}
