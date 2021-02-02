// System and QT Includes
#include <QGuiApplication>
#include <QDir>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmLogfileWriter.h"
#include "CdmSessionManager.h"
#include "CumUser.h"

// Basetools Includes
#include "CwmsContext.h"

// WMS GUI Includes
#include "CwmsErrorMessenger.h"
#include "CwmsGuiLoginIf.h"

// own Includes
#include "CwmsAdminMainWindowIf.h"
#include "CwmsInitAdmin.h"

CwmsInitAdmin::CwmsInitAdmin(QString p_qstrName, QString p_qstrVersion)
: CwmsInitApplication(p_qstrName, p_qstrVersion)
{
}

CwmsInitAdmin::~CwmsInitAdmin()
{
}

void CwmsInitAdmin::Logging()
{
    INITERRORMANAGER();

    QString qstrFilename = m_qstrApplicationName;
    qstrFilename = qstrFilename.replace(" ", "_") + ".log";
    QString qstrPath = QDir::homePath() + "/Documents/" + qstrFilename;
    CdmLogfileWriter* pLogger
            = new CdmLogfileWriter(qstrPath, m_qstrApplicationName, m_qstrVersion);
    CdmLogging::AddAdaptor(pLogger);

    CwmsErrorMessenger* pLoggerMessenger = new CwmsErrorMessenger();
    CdmLogging::AddAdaptor(pLoggerMessenger);

    StateFinished(true);
}

void CwmsInitAdmin::Login()
{
    if (CwmsGuiLoginIf::Login(m_qstrApplicationName, nullptr))
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager))
        {
            CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

            if(pCumUserManager)
            {
                const CumUser* pCumUser = CdmSessionManager::GetSessionManager()->GetCurrentUser();

                if(pCumUser && pCumUser->IsAdministrator())
                {
                    CdmSessionManager::GetSessionManager()->SetSessionTimeoutMinutes(120);
                    StateFinished(true);
                }
                else
                {
                    if(pCumUser)
                    {
                        ERR("User has no admin privileges.");
                    }

                    StateFinished(false);
                }
            }
            else
            {
              StateFinished(false);
            }
        }
        else
        {
          StateFinished(false);
        }
    }
    else
    {
      StateFinished(false);
    }
}

void CwmsInitAdmin::DbSelection()
{
    StateFinished(true);
}

void CwmsInitAdmin::ApplicationSelection()
{
    StateFinished(true);
}

void CwmsInitAdmin::ApplicationStart()
{
    CwmsContext::CreateContext(eWmsApplicationContextAdmin);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CwmsAdminMainWindowIf* pCwmsAdminMainWindowIf = new CwmsAdminMainWindowIf();

        if(pCwmsAdminMainWindowIf)
        {
           if (pCdmManager->IsDemo())
           {
              pCwmsAdminMainWindowIf->setWindowTitle(GetApplicationAndVersionName() + " " + QObject::tr("Demo"));
           }
           else
           {
              pCwmsAdminMainWindowIf->setWindowTitle(GetApplicationAndVersionName());
           }

           pCwmsAdminMainWindowIf->show();
        }
    }

    StateFinished(true);
}
