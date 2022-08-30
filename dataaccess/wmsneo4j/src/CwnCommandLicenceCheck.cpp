#include "CwnCommandLicenceCheck.h"

CwnCommandLicenceCheck::CwnCommandLicenceCheck(QString p_qstrApplication,
                                               QString p_qstrVersion,
                                               CwnDataAccess* p_ppDataAccess)
: CwnCommandBase(p_ppDataAccess),
  m_qstrApplication(p_qstrApplication),
  m_bDemo(false),
  m_iModules(0),
  m_qstrVersion(p_qstrVersion)
{
}

CwnCommandLicenceCheck::~CwnCommandLicenceCheck()
{

}

int CwnCommandLicenceCheck::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    // OLD CODE LOOK HERE FOR REACTIVATING LICENCE MECHANISMN
    /*
    p_iModules = 0;
    int iMaxLicences = CountMaxLicences(p_qstrApplication, p_bDemo, p_iModules, p_qstrVersion);

    if (iMaxLicences == 0)
    {
       p_bDemo = true;
       bRet = true;
    }
    else if(ActiveSessionCount(p_qstrApplication) < iMaxLicences)
    {
       bRet = true;
    }

    if (!bRet)
    {
       CdmManager* pCdmManager = m_rpCdbDataAccess->GetManager();

       if (CHKPTR(pCdmManager))
       {
          CdmSettings* pCdmSettings = pCdmManager->GetSettings();

          if (pCdmSettings->GetAccessMode() == eDmFile)
          {
             bRet = true;
          }
       }
    }
    */

    // disabled licencecheck
    m_iModules = INT_MAX;
    iRet = EC(eDmOk);


    return iRet;
}

bool CwnCommandLicenceCheck::CheckValid()
{
    return (!m_qstrApplication.isEmpty());
}

void CwnCommandLicenceCheck::interpretAnswer(QVariant& Ret){
    Q_UNUSED(Ret);
}

QString CwnCommandLicenceCheck::createQueryForActiveSessionCount(){
    return "hi";
}

QString CwnCommandLicenceCheck::createQueryForCountMaxLicences(){
    return "hi";
}

int CwnCommandLicenceCheck::ActiveSessionCount( QString p_qstrApplication)
{
   int iRet = 0;

   QString qstrQuery = QString("select SessionId from WMS_UM_SESSION "
                       "where state = true and Application = '%1'")
                       .arg(p_qstrApplication);
   return iRet;
}


int CwnCommandLicenceCheck::CountMaxLicences(QString p_qstrApplication,
                                        bool& p_bDemo,
                                        int& p_iModules,
                                        QString p_qstrVersion)
{
    Q_UNUSED(p_bDemo)
    Q_UNUSED(p_iModules)
    Q_UNUSED(p_qstrVersion)
   int iRet = 0;

   QString qstrQuery = QString("select Licensee, LicenseKey from WMS_UM_LICENSEKEY "
                               "where Application = '%1'")
                                  .arg(p_qstrApplication);
   return iRet;
}


int CwnCommandLicenceCheck::GetModules()
{
    return m_iModules;
}

bool CwnCommandLicenceCheck::IsDemo()
{
    return m_bDemo;
}
