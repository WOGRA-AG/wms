// System and QT Includes
#include <qstring.h>


// own Includes
#include "CdmScheme.h"
#include "CdmModelElement.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmSettings.h"
#include "CdmModelElementBase.h"


CdmModelElementBase::CdmModelElementBase(qint64 p_lDbId)
: CdmLocatedElement(),
  m_lSchemeId(p_lDbId)
{
   m_lSchemeId = p_lDbId;
}


CdmModelElementBase::~CdmModelElementBase(  )
{
   // nothing to do :-)
}

qint64 CdmModelElementBase::GetSchemeId() const
{
   return m_lSchemeId.load();
}

void CdmModelElementBase::SetSchemeId(qint64 p_lDbId)
{
   m_lSchemeId = p_lDbId;
}

QString CdmModelElementBase::GetSchemeName() const
{
   QString qstrDbName;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      const CdmScheme* pDb = pManager->FindSchemeById(m_lSchemeId.load());

      if (CHKPTR(pDb))
      {
         qstrDbName = pDb->GetSchemeName();
      }
   }

   return qstrDbName;
}

CdmScheme* CdmModelElementBase::GetScheme() const
{
   CdmScheme* pCdmDatabase = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager)
   {
      pCdmDatabase = pCdmManager->FindSchemeById(m_lSchemeId.load());
   }

   return pCdmDatabase;
}

bool CdmModelElementBase::IsInDeploymentMode() const
{
   bool bRet = false;
   CdmScheme* pDatabase = GetScheme();

   if (CHKPTR(pDatabase))
   {
      bRet = true;
   }

   return bRet;
}

CdmDataProvider* CdmModelElementBase::GetDataProvider() const
{
   return CdmSessionManager::GetDataProvider();
}

CdmSettings* CdmModelElementBase::GetSettings() const
{
   CdmSettings* pCdmSettings = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pCdmSettings = pManager->GetSettings();
   }

   return pCdmSettings;
}

CdmClassManager* CdmModelElementBase::GetClassManager() const
{
   CdmClassManager* pCdmClassManager = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pCdmClassManager = pManager->GetClassManager(m_lSchemeId.load());
   }

   return pCdmClassManager;
}

CdmContainerManager* CdmModelElementBase::GetContainerManager() const
{
   CdmContainerManager* pContainerManager = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pContainerManager = pManager->GetContainerManager();
   }

   return pContainerManager;
}

IdmDataAccess* CdmModelElementBase::GetDataAccess() const
{
   IdmDataAccess* pIdmDataAccess = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pIdmDataAccess = pManager->GetDataAccess();
   }

   return pIdmDataAccess;
}

qint64 CdmModelElementBase::GetSessionId() const
{
   return CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
}

qint64 CdmModelElementBase::GetUserId(  ) const
{
   return CdmSessionManager::GetSessionManager()->GetCurrentUserId();
}

QString CdmModelElementBase::CreateUri(QString p_qstrType,
                                       QString p_qstrKeyname,
                                       QString p_qstrKeyname2,
                                       QString p_qstrKeyname3) const
{
   return CdmLocatedElement::CreateUri(p_qstrType, p_qstrKeyname, p_qstrKeyname2, p_qstrKeyname3);
}
