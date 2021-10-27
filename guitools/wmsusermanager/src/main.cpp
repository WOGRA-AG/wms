/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: main.cpp
 ** Started Implementation: 2008/05/01
 ** Description:
 ** 
 ** The main method for starting usermanager
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <qapplication.h>
#include <qstring.h>
#include <qdir.h>

// own Includes
#include "CwmsMessenger.h"
#include "CwmsErrorMessenger.h"
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CdmLogging.h"
#include "CdmLogfileWriter.h"
#include "CwmsGuiLoginIf.h"
#include "CwmsUserManagerIf.h"

QString qstrVersion = "1.2.0";
QString qstrBuild   = "5";


int main( int argc, char ** argv )
{
   int iRet = 0;
   QApplication qApplication(argc, argv);   
   new CwmsMessenger(nullptr, nullptr);
   
   QString qstrLoginApplication;

   if(argc > 1)
   {
      qstrLoginApplication = argv[1];
   }

   INITERRORMANAGER();
   CwmsErrorMessenger* pLogger = new CwmsErrorMessenger();
   CdmLogging::AddAdaptor(pLogger);

   QString qstrPath = QDir::homePath() +"/Documents/usermanager.log";
   CdmLogfileWriter* pLogWriter
           = new CdmLogfileWriter(qstrPath, qstrLoginApplication, qstrVersion);
   CdmLogging::AddAdaptor(pLogWriter);

   SETSEVERITY(0);

   if (CwmsGuiLoginIf::Login("UserManager", nullptr))
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if(pCdmManager)
      {
         pCdmManager->SetApplicationVersion("-1");
         QString qstrCaption = qApplication.translate("","WMS User Manager V") + " " + qstrVersion;
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

        if(pCumUserManager)
        {
           const CumUser* pCumUser = CdmSessionManager::GetSessionManager()->GetCurrentUser();

           if(pCumUser && pCumUser->IsAdministrator())
           {
              CwmsUserManagerIf* pCwmsUserManagerIf = new CwmsUserManagerIf();
              pCwmsUserManagerIf->show();

              qApplication.connect( &qApplication, SIGNAL(lastWindowClosed()), &qApplication, SLOT(quit()) );
              qApplication.exec();

              CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

              if(pCdmManager)
              {
                 CdmSessionManager::GetSessionManager()->Logout();
              }
           }
           else
           {
              MSG_INFO(("Keine Administratorenrechte"),
                        ("Sie haben keine Administratorenrechte.\n"
                         "Die Anwendung wird beendet."));
           }
        }
      }
      else
      {
         INFO("No application start, login not successfull or canceled.");
         iRet = 1;
      }
   }

   return iRet;
}
