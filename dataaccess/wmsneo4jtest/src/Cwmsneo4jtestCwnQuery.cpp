#include "Cwmsneo4jtestCwnQuery.h"

#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"

#include "CdmQuery.h"
#include "CdmQueryElement.h"
#include "CdmQueryBuilder.h"

#include "CdmLogging.h"

#include <QDebug>
#include <QLinkedList>

#include "CwnQuery.h"
#include "CwnCommandCreateUser.h"
#include "CwnDataAccess.h"

Cwmsneo4jtestCwnQuery::Cwmsneo4jtestCwnQuery(QObject *parent) : QObject(parent)
{
    CwnCommandCreateUser create(NULL,"");
    create.setActive(true);
    create.setAdmin(true);
    create.setEmail("admin9@wogra.com");
    create.setFirstname("admin");
    create.setLastname("admin");
    create.setLogin("admin");
    create.setPass("admin");
    create.Run();

    CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);

    if (SUCCESSFULL(pFactory->Login("admin","admin")))
    {
         m_pCdmManager = CdmSessionManager::GetDataProvider();
         m_pCumManager = m_pCdmManager->GetUserManager();
    }

    if(m_pCdmManager==0)
    {
        QVERIFY(true==false);
    }
}

void Cwmsneo4jtestCwnQuery::initTestCase()
{

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    pCdmManager->LoadScheme("fahrtenbuch");
    CwnDataAccess* data = (CwnDataAccess*)pCdmManager->GetDataAccess();

    //CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery("SELECT Kommentar,Fahrzeug.Kennzeichen,Fahrzeug FROM Fahrzeugkosten.class WHERE OR(Fahrzeug.Kennzeichen=\"A-MK 1234\", Fahrzeug.Fabrikat=\"Diablo\") ORDER BY Fahrzeug.Kennzeichen DESC");
    CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery("SELECT Zielort, COUNT(Fahrzeug) FROM Fahrtenbuch.Fahrtenbuch.class GROUP BY Zielort");

    pQuery->SetScheme("fahrtenbuch");
    pQuery->SetSchemeSearch();

    CwnQuery* pCwnQuery = new CwnQuery(data,pQuery);
    pCwnQuery->Run();
    Q_UNUSED(pCwnQuery);

}

void Cwmsneo4jtestCwnQuery::cleanupTestCase()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pCdmManager))
    {
        CdmSessionManager::Logout();
    }
}
