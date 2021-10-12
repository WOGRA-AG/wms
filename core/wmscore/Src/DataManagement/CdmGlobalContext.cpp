// System and Qt Inlcudes
#include <QMutexLocker>
#include <QThread>

// Own Includes
#include "CdmLogging.h"
#include "CdmSettings.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClassManager.h"
#include "CdmGlobalContext.h"

CdmGlobalContext::CdmGlobalContext(EdmSettingsMode p_eMode)
    : m_eDmSettingsMode(p_eMode),
      m_pCdmSettings(nullptr)
{
     m_pCdmSettings = new CdmSettings(m_eDmSettingsMode);
}

CdmGlobalContext::~CdmGlobalContext()
{
   DeleteAllClassManagers();
   DELPTR(m_pCdmSettings);
}

CdmClassManager *CdmGlobalContext::GetClassManager(qint64 p_lSchemeId)
{
    CdmClassManager* pClassManager = nullptr;
    SYNCHRONIZED;

    if (m_qlLoadingClassManagers.contains(p_lSchemeId))
    {
        return nullptr;
    }

    if (m_qmClassManagers.contains(p_lSchemeId))
    {
        pClassManager = m_qmClassManagers[p_lSchemeId];
    }
    else
    {
        m_qlLoadingClassManagers.append(p_lSchemeId);
        // toDo load class manager
        pClassManager = LoadClassManager(p_lSchemeId);

        if (!pClassManager)
        {
            FATAL("ClassManager for SchemeId " + QString::number(p_lSchemeId) + " not found.");
        }

        m_qlLoadingClassManagers.removeAll(p_lSchemeId);
    }

    return pClassManager;
}

void CdmGlobalContext::DeleteClassManager(qint64 p_lSchemeId)
{
    if (!CdmSessionManager::GetSessionManager()->GetServerMode())
    {
        CdmClassManager* pClassManager = nullptr;
        SYNCHRONIZED;

        if (m_qmClassManagers.contains(p_lSchemeId))
        {
            pClassManager = m_qmClassManagers[p_lSchemeId];
            m_qmClassManagers.remove(p_lSchemeId);
            DELPTR(pClassManager);
        }
        else
        {
            ERR("ClassManager for ID not found");
        }


    }
    else
    {
        ERR("It is not allowed to call this method in server mode!")
    }
}

CdmClassManager* CdmGlobalContext::LoadClassManager(qint64 p_lSchemeId)
{
   CdmClassManager* pClassManager = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (m_qmClassManagers.contains(p_lSchemeId))
   {
       INFO("No new class manager loaded. Was already there.");
       return m_qmClassManagers[p_lSchemeId];
   }

   if (CHKPTR(pManager))
   {
       IdmDataAccess* pIdmDataAccess = pManager->GetDataAccess();

       if(CHKPTR(pIdmDataAccess))
       {
          pClassManager = nullptr;
          int iRet = pIdmDataAccess->LoadClassManager(p_lSchemeId, pClassManager);

          if (SUCCESSFULL(iRet))
          {
              SYNCHRONIZED;
              m_qmClassManagers.insert(p_lSchemeId, pClassManager);
          }
          else
          {
             FATAL("Could not load Class Manager");
          }
       }
   }

   return pClassManager;
}

void CdmGlobalContext::UpdateClassManager(qint64 p_lSchemeId)
{
    if (!CdmSessionManager::GetSessionManager()->GetServerMode())
    {
        CdmClassManager* pClassManager = nullptr;
        SYNCHRONIZED;
        if (m_qmClassManagers.contains(p_lSchemeId))
        {
            pClassManager = m_qmClassManagers[p_lSchemeId];
            m_qmClassManagers.remove(p_lSchemeId);
            // this could lead to segfault
            DELPTR(pClassManager);
            GetClassManager(p_lSchemeId);
        }
        else
        {
            ERR("ClassManager for ID not found");
        }
    }
    else
    {
        ERR("It is not allowed to call this method in server mode!")
    }
}

void CdmGlobalContext::DeleteAllClassManagers()
{
    SYNCHRONIZED;
    QMap<qint64, CdmClassManager*>::iterator qmIt = m_qmClassManagers.begin();
    QMap<qint64, CdmClassManager*>::iterator qmItEnd = m_qmClassManagers.end();

    for (; qmIt != qmItEnd; qmIt++)
    {
       DELPTR(qmIt.value());
    }

    m_qmClassManagers.clear();
}

EdmSettingsMode CdmGlobalContext::GetMode()
{
    return m_eDmSettingsMode;
}

CdmSettings* CdmGlobalContext::GetSettings()
{
    return m_pCdmSettings;
}
