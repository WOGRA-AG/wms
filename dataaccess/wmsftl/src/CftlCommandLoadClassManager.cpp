
// WMS Includes
#include "CdmClassManager.h"

// Own Includes
#include "CftlCommandLoadClassManager.h"
#include "CftlCommandGetClass.h"
#include "CftlCommandLoadPackages.h"

CftlCommandLoadClassManager::CftlCommandLoadClassManager(long p_lSchemeId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_pClassManager(nullptr)
{
}

CftlCommandLoadClassManager::~CftlCommandLoadClassManager()
{

}

int CftlCommandLoadClassManager::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    m_pClassManager = CdmDataAccessHelper::CreateClassManager(m_lSchemeId);
    CftlCommandLoadPackages commandLoadPackages(m_pClassManager, GetDataAccess());
    commandLoadPackages.Run();

    cQSqlQuery.prepare("select ClassId from WMS_CLASS where SchemeId = ?");
    cQSqlQuery.addBindValue((int)m_lSchemeId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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

				CftlCommandGetClass commandGetClass(m_pClassManager, lClassId, GetDataAccess());
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

CdmClassManager *CftlCommandLoadClassManager::GetResult()
{
    return m_pClassManager;
}

bool CftlCommandLoadClassManager::CheckValid()
{
    return (m_lSchemeId > 0);
}
