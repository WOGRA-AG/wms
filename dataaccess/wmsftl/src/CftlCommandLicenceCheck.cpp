#include "CftlCommandLicenceCheck.h"

CftlCommandLicenceCheck::CftlCommandLicenceCheck(QString p_qstrApplication,
                                               QString p_qstrVersion,
                                               CftlDataAccess* p_ppDataAccess)
: CftlAbstractCommand(p_ppDataAccess),
  m_qstrApplication(p_qstrApplication),
  m_bDemo(false),
  m_iModules(0),
  m_qstrVersion(p_qstrVersion)
{
}

CftlCommandLicenceCheck::~CftlCommandLicenceCheck()
{

}

int CftlCommandLicenceCheck::Execute()
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
       CdmManager* pCdmManager = m_rpCftlDataAccess->GetManager();

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

bool CftlCommandLicenceCheck::NeedsSessionCheck()
{
    return false;
}

bool CftlCommandLicenceCheck::CheckValid()
{
    return (!m_qstrApplication.isEmpty());
}


int CftlCommandLicenceCheck::ActiveSessionCount( QString p_qstrApplication)
{
   int iRet = 0;

   QString qstrQuery;

   qstrQuery = QString("select SessionId from WMS_UM_SESSION "
                       "where state = true and Application = '%1'")
                       .arg(p_qstrApplication);

   QSqlQuery qsqlQuery;

   if(ExecuteQuery(qstrQuery, qsqlQuery) > 0)
   {
      qsqlQuery.first();

      while(qsqlQuery.isValid())
      {
         ++iRet;
         qsqlQuery.next();
      }
   }

#ifdef WOGRA_DEBUG
   iRet = 0;
#endif //

   return iRet;
}


int CftlCommandLicenceCheck::CountMaxLicences(QString p_qstrApplication,
                                        bool& p_bDemo,
                                        int& p_iModules,
                                        QString p_qstrVersion)
{
   int iRet = 0;
   QMap<QString, int> qmLicences;


   QString qstrQuery = QString("select Licensee, LicenseKey from WMS_UM_LICENSEKEY "
                               "where Application = '%1'")
                                  .arg(p_qstrApplication);

   QSqlQuery qsqlQuery;

   if(ExecuteQuery(qstrQuery, qsqlQuery) > 0)
   {
      qsqlQuery.first();


      while(qsqlQuery.isValid())
      {
         QString qstrLicencee = qsqlQuery.value(0).toString();
         QString qstrLicenceKey = qsqlQuery.value(1).toString();

         // The Licencee Demo identifies allway a demo version.
         // it plays no role how many other licences are includede
         // with one demo licence you will get a demoversion
         if (qstrLicencee.startsWith("Demo"))
         {
            iRet = 0;
            p_bDemo = true;
            break;
         }

         if(!qmLicences.contains(qstrLicencee))
         {
            int iModules = 0;
            int iLicenceCount = CdmDataAccessHelper::ValidateLicence(p_qstrApplication,
                                                               qstrLicencee,
                                                               qstrLicenceKey,
                                                               iModules,
                                                               p_qstrVersion);

            if(iLicenceCount >= 0)
            {
               p_iModules += iModules;
               iRet += iLicenceCount;
            }

            qmLicences.insert(qstrLicencee, iLicenceCount);
         }

         qsqlQuery.next();
      }
   }

   return iRet;
}


int CftlCommandLicenceCheck::GetModules()
{
    return m_iModules;
}

bool CftlCommandLicenceCheck::IsDemo()
{
    return m_bDemo;
}
