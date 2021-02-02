
// WMS Commons Includes
#include "CwmsJson.h"
#include "CwsHttpRequest.h"
#include "CwtHelper.h"
#include "wmsdefines.h"

// WMS Core Includes
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CdmValueObjectRef.h"
#include "CdmValueContainerRef.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CdmSessionManager.h"

// WMS Entities Includes
#include "CwmsPluginManager.h"
#include "CwmsContext.h"
#include "CwmsServerSettings.h"

// WMS REQUESTMANAGER Includes
#include "CwmscomHandler.h"

// Own Includes
#include "CwtServiceTest.h"

#include <CdmJsonToObjectMapper.h>

CwtServiceTest::CwtServiceTest()
: CwtTestBase(eBmsTestModeDB),
  m_lObjectId(0),
  m_bTimeMeassurementActive(false)
{

}

CwtServiceTest::~CwtServiceTest()
{

}

void CwtServiceTest::LoadFunctionPlugins()
{
    CwmsContext::GetContext()->ServerLogin();
    CwmsPluginManager* pPluginManager = CwmsContext::GetContext()->GetPluginManager();
    pPluginManager->LoadServerPlugins();
    CwmsContext::GetContext()->ServerLogout();
}

void CwtServiceTest::initTestCase()
{
    CdmSessionManager::CreateSessionManager(eDmSettingsModeServer);
    CwmsContext::CreateContext(eWmsApplicationContextServer);
    LoadFunctionPlugins();
    m_pHandler = CwmscomHandler::CreateOrGetCommandHandler();
    QVERIFY(m_pHandler != nullptr);
    m_pHandler->Init();
    m_pHandler->SetSystemUserLogin("admin");
    m_pHandler->SetSystemUserPassword("admin");
    m_pHandler->SetParser(new CwmsJson());
    m_pHandler->SetSerializer(new CwmsJson());
}

void CwtServiceTest::cleanupTestCase()
{
    DELPTR(m_pHandler);
}

void CwtServiceTest::init()
{
    InitWithLogin();
    m_lObjectId = 0;
    m_qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(m_qstrSchemeName);
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    CreateTestClass();
    CreateTestContainers();
    StartPureTest();
}

void CwtServiceTest::cleanup()
{
    EndPureTest();
    CwtHelper::DeleteScheme(m_qstrSchemeName);
    CleanupWithLogout();
}

void CwtServiceTest::ExcecuteRequest(QString& p_qstrRequest, CwsHttpResponse& p_rResponse, CwmsTimeMeassurement& p_rTime)
{
    CwsHttpRequest cRequest;
    QByteArray qbaRequest(p_qstrRequest.toUtf8());
    cRequest.CopyContent(qbaRequest);
    cRequest.ParseContent();
    p_rTime.finishedTask("Finished Parsing");
    m_pHandler->HandleRequest(&cRequest, &p_rResponse);
    p_rTime.finishedTask("Finished Request");
}


void CwtServiceTest::TestGetClassByKeyname()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");
    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CLASS)
            .arg(m_qstrSchemeName)
            .arg(m_pClassNoRef->GetKeyname());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   QVERIFY(qstrBody.contains(m_pClassNoRef->GetKeyname()));
   QVERIFY(qstrBody.contains(MEMBER_STRING_KEYNAME));
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestGetClassById()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");
    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CLASS)
            .arg(m_qstrSchemeName)
            .arg(m_pClassNoRef->GetId());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   QVERIFY(qstrBody.contains(m_pClassNoRef->GetKeyname()));
   QVERIFY(qstrBody.contains(MEMBER_STRING_KEYNAME));
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestContainerRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");
    // Class Request
    // "GET /Rest/Api/class/AdressDb/Address/ HTTP/1.1\r\nHost: localhost:8383\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\nCache-Control: no-cache\r\nAuthorization: Basic YWRtaW46YWRtaW4=\r\nPostman-Token: f19a545e-1af6-40dc-4c3a-227d46217a4a\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n"

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestContainerListRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/List/?from=0&to=50 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestClassManagerRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CLASS_MANAGER)
            .arg(m_qstrSchemeName);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestSchemeRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_SCHEME)
            .arg(m_qstrSchemeName);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestDataProviderRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_DATAPROVIDER)
            .arg(m_qstrSchemeName);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestContainerManagerRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER_MANAGER)
            .arg(m_qstrSchemeName);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestFindUserRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/?name=%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_DATAPROVIDER)
            .arg(m_qstrSchemeName)
            .arg("findUser")
            .arg("admin");
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestGetUserData()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n\r\n")
            .arg(WMS_URI_USER)
            .arg(m_qstrSchemeName)
            .arg("admin");
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::TestGetSchemeListRequest()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_DATAPROVIDER)
            .arg(m_qstrSchemeName)
            .arg("getSchemeList");
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
//   QString qstrVerificationString = QString("\"rel\": \"%1\"").arg(m_qstrSchemeName);
//   QVERIFY(qstrBody.contains(qstrVerificationString));
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::FindContainerByKeyname()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::FindContainerById()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);

    QVERIFY(pContainer != nullptr);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(pContainer->GetId());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::CreateContainer()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3?Keyname=\"%4\"&classkeyname=\"%5\" HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER_MANAGER)
            .arg(m_qstrSchemeName)
            .arg(WMS_URI_CREATE)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS "_neu")
            .arg(TEST_CLASS_NAME_NO_REF);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   QVERIFY(GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS "_neu") != nullptr);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::GetContainerListByClassKeyname()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");
    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3?classkeyname=\"%4\" HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER_MANAGER)
            .arg(m_qstrSchemeName)
            .arg(WMS_GET_LIST_BY_CLASS_KEYNAME)
            .arg(TEST_CLASS_NAME_NO_REF);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::GetContainerListByClassId()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3?Id=\"%4\" HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER_MANAGER)
            .arg(m_qstrSchemeName)
            .arg(WMS_GET_LIST_BY_CLASS_ID)
            .arg(m_pClassNoRef->GetId());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::DeleteContainerByKeyname()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    QString qstrRequest = QString("DELETE /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QVERIFY(GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS) == nullptr);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::DeleteContainerById()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);

    QVERIFY(pContainer != nullptr);

    QString qstrRequest = QString("DELETE /Rest/Api/%1/%2/%3/ HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(pContainer->GetId());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QVERIFY(GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS) == nullptr);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::ListAllContainerObjects()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->CountObjectsOnDb() == 2);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(WMS_LIST);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::ListOneContainerObjects()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->CountObjectsOnDb() == 2);

    QString qstrRequest = GenerateListRequest(0,0);

   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   QString qstrBody = response.GetBody();
   QVERIFY(qstrBody.toLower().contains("list next"));
   QVERIFY(!qstrBody.toLower().contains("list previous"));

   cTime.finishedTask("Finished Verification");
}

QString CwtServiceTest::GenerateListRequest(int p_iFrom, int p_iTo)
{
    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4?%5=%6&%7=%8 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(WMS_LIST)
            .arg("from")
            .arg(p_iFrom)
            .arg("to")
            .arg(p_iTo);

    return qstrRequest;
}

void CwtServiceTest::DeleteAllContainerObjects()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->CountObjectsOnDb() == 2);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(WMS_URI_DELETE_ALL_OBJECTS);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
   QVERIFY(pContainer != nullptr);
   QVERIFY(pContainer->CountObjectsOnDb() == 0);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::GetObjectGraphNoRefObjects()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_OBJECT)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(pObject->GetKeyname());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::GetObjectGraphRefObjects()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    QVERIFY(pObject->Commit() > 0);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_OBJECT)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(pObject->GetKeyname());
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::CreateNoRefObjectOverRestRequest(CwsHttpResponse& response)
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(WMS_URI_CREATE);
   cTime.finishedTask("Finished Building Request");
   ExcecuteRequest(qstrRequest, response, cTime);
}

void CwtServiceTest::CreateNoRefObject()
{
    CwsHttpResponse response;
    CreateNoRefObjectOverRestRequest(response);
    QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    QVERIFY(pContainer->CountObjectsOnDb() == 1);
}

void CwtServiceTest::CreateRefObject()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);

    QString qstrRequest = QString("GET /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n")
            .arg(WMS_URI_CONTAINER)
            .arg(m_qstrSchemeName)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(WMS_URI_CREATE);
   cTime.finishedTask("Finished Building Request");
   CwsHttpResponse response;
   ExcecuteRequest(qstrRequest, response, cTime);
   QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
   pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
   QVERIFY(pContainer != nullptr);
   QVERIFY(pContainer->CountObjectsOnDb() == 1);
   cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::CreateNoRefObjects(CdmObjectContainer* pContainer, int p_iCount)
{
    for (int i = 0; i < p_iCount; ++i)
    {
       CdmObject* pObject =CreateSingleNoRefObject(pContainer);
       QVERIFY(pObject != nullptr);
       FillObjectData(pObject);
       QVERIFY(pObject->Commit() > 0);
    }

    QVERIFY(pContainer->CountObjectsOnDb() == p_iCount);
}

CdmObject* CwtServiceTest::CreateSingleNoRefObject(CdmObjectContainer* pContainer)
{
    CdmObject* pObject = CreateSingleObject(pContainer);
    if (CHKPTR(pObject))
    {
        FillObjectData(pObject);
        pObject->Commit();
    }

    return pObject;
}

CdmObject* CwtServiceTest::CreateSingleObject(CdmObjectContainer* pContainer)
{
    CdmObject* pObject = pContainer->CreateNewObject();
    if (CHKPTR(pObject))
    {
        pObject->Commit();
    }

    return pObject;
}

void CwtServiceTest::ListManyContainerObjects()
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);

     CreateNoRefObjects(pContainer, 150);

    QString qstrRequest = GenerateListRequest(50,99);

    cTime.finishedTask("Finished Building Request");
    CwsHttpResponse response;
    ExcecuteRequest(qstrRequest, response, cTime);
    QVERIFY(response.GetStatusCode() == eWmsHttpStatusCodeOk);
    QString qstrBody = response.GetBody();
    QVERIFY(qstrBody.toLower().contains("list next"));
    QVERIFY(qstrBody.toLower().contains("list previous"));
    cTime.finishedTask("Finished Verification");
}

void CwtServiceTest::ChangeObjectStringValue()
{
    ChangeObjectValue(MEMBER_STRING_KEYNAME, "Test");
}

void CwtServiceTest::ChangeObjectIntValue()
{
    ChangeObjectValue(MEMBER_INT_KEYNAME, "8765");
}

void CwtServiceTest::ChangeObjectLongValue()
{
    ChangeObjectValue(MEMBER_LONG_KEYNAME, "12984567");
}

void CwtServiceTest::ChangeObjectCounterValue()
{
    ChangeObjectValue(MEMBER_COUNTER_KEYNAME, "12984567");
}

void CwtServiceTest::ChangeObjectFloatValue()
{
    ChangeObjectValue(MEMBER_FLOAT_KEYNAME, "3");
}

void CwtServiceTest::ChangeObjectDoubleValue()
{
    ChangeObjectValue(MEMBER_DOUBLE_KEYNAME, "1.2984567");
}

void CwtServiceTest::ChangeObjectCharDocValue()
{
    ChangeObjectValue(MEMBER_CHARDOC_KEYNAME, "Das ist ein Test mit ÄÖÜöäüß\nund neuer Zeile mit \tTab.");
}

void CwtServiceTest::ChangeObjectEnumValue()
{
    ChangeObjectValue(MEMBER_ENUM_KEYNAME, "second");
}

void CwtServiceTest::ChangeObjectDateValue()
{
    QDate qdDate(1978,8,21);

    ChangeObjectValue(MEMBER_DATE_KEYNAME, qdDate.toString(Qt::ISODate));
}

void CwtServiceTest::ChangeObjectDateTimeValue()
{
    QDate qdDate(1978,8,21);
    QTime qtTime(5,55);
    QDateTime qdt(qdDate, qtTime);

    ChangeObjectValue(MEMBER_DATE_TIME_KEYNAME, qdt.toString(Qt::ISODate));
}

void CwtServiceTest::ChangeObjectTimeValue()
{
    QTime qtTime(5,55);
    ChangeObjectValue(MEMBER_TIME_KEYNAME, qtTime.toString(Qt::ISODate));
}

void CwtServiceTest::ChangeObjectBoolValue()
{
    ChangeObjectValue(MEMBER_BOOL_KEYNAME, "false");
}

void CwtServiceTest::ChangeObjectUserValue()
{
    ChangeObjectBoolValue(); // Just a hack to become valid session data for uri --> pSession->SetServerRequestPath("Rest/Api");
    DeleteTestUser();
    CumUser* pUser = CreateTestUser();
    QVERIFY(pUser != nullptr);

    ChangeObjectValue(MEMBER_USER_KEYNAME, pUser->GetUri());
}

void CwtServiceTest::ChangeObjectUserGroupValue()
{
    ChangeObjectBoolValue(); // Just a hack to become valid session data for uri --> pSession->SetServerRequestPath("Rest/Api");
    CumUserGroup* pUserGroup = CreateTestUserGroup();
    QVERIFY(pUserGroup != nullptr);
    ChangeObjectValue(MEMBER_USER_GROUP_KEYNAME, pUserGroup->GetUri());
    CumUserManager* pUserManager = GetUserManager();

    if (pUserManager != nullptr)
    {
        pUserManager->DeleteUserGroup(pUserGroup->GetId());
    }
}

void CwtServiceTest::ChangeObjectListStringValue()
{
    QVariantList qvl;
    qvl.append("One - eins");
    qvl.append("Two - zwei");
    qvl.append("Three - drei");

    QVariantMap qvm;
    qvm.insert(MEMBER_LIST_STRING_KEYNAME, qvl);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_LIST_STRING_KEYNAME));
    qstrBodyResult.contains(qstrBody);
}

void CwtServiceTest::ChangeObjectListIntValue()
{
    QVariantList qvl;
    qvl.append(400);
    qvl.append(500);
    qvl.append(600);

    QVariantMap qvm;
    qvm.insert(MEMBER_LIST_INT_KEYNAME, qvl);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_LIST_INT_KEYNAME));
    qstrBodyResult.contains(qstrBody);
}

void CwtServiceTest::ChangeObjectListDoubleValue()
{
    QVariantList qvl;
    qvl.append(3.14);
    qvl.append(54.45);
    qvl.append(99.10);

    QVariantMap qvm;
    qvm.insert(MEMBER_LIST_DOUBLE_KEYNAME, qvl);
    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_LIST_DOUBLE_KEYNAME));
    QVariantList qvlResult = qvmData[MEMBER_LIST_DOUBLE_KEYNAME].toList();
    QVERIFY(qvlResult.contains(3.14));
    QVERIFY(qvlResult.contains(54.45));
    QVERIFY(qvlResult.contains(99.10));
}

void CwtServiceTest::ChangeObjectMapIntIntValue()
{
    QVariantMap qvmContent;
    qvmContent.insert("50",10);
    qvmContent.insert("150",20);
    qvmContent.insert("300",30);

    QVariantMap qvm;
    qvm.insert(MEMBER_MAP_INT_INT_KEYNAME, qvmContent);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_MAP_INT_INT_KEYNAME));
    QVariantMap qvmResultMap = qvmData[MEMBER_MAP_INT_INT_KEYNAME].toMap();
    QVERIFY(qvmResultMap.contains("50"));
    QVERIFY(qvmResultMap.contains("150"));
    QVERIFY(qvmResultMap.contains("300"));
}

void CwtServiceTest::ChangeObjectMapIntDoubleValue()
{
    QVariantMap qvmContent;
    qvmContent.insert("50",10.45);
    qvmContent.insert("150",20.32);
    qvmContent.insert("300",30.89);

    QVariantMap qvm;
    qvm.insert(MEMBER_MAP_INT_DOUBLE_KEYNAME, qvmContent);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_MAP_INT_DOUBLE_KEYNAME));
    QVariantMap qvmResultMap = qvmData[MEMBER_MAP_INT_DOUBLE_KEYNAME].toMap();
    QVERIFY(qvmResultMap.contains("50"));
    QVERIFY(qvmResultMap.contains("150"));
    QVERIFY(qvmResultMap.contains("300"));
}

void CwtServiceTest::ChangeObjectMapIntStringValue()
{
    QVariantMap qvmContent;
    qvmContent.insert("50","li");
    qvmContent.insert("150","la");
    qvmContent.insert("300","laune");

    QVariantMap qvm;
    qvm.insert(MEMBER_MAP_INT_STRING_KEYNAME, qvmContent);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_MAP_INT_STRING_KEYNAME));
    QVariantMap qvmResultMap = qvmData[MEMBER_MAP_INT_STRING_KEYNAME].toMap();
    QVERIFY(qvmResultMap.contains("50"));
    QVERIFY(qvmResultMap.contains("150"));
    QVERIFY(qvmResultMap.contains("300"));
}

void CwtServiceTest::ChangeObjectMapStringIntValue()
{
    QVariantMap qvmContent;
    qvmContent.insert("li",3);
    qvmContent.insert("la",4);
    qvmContent.insert("laune",5);

    QVariantMap qvm;
    qvm.insert(MEMBER_MAP_STRING_INT_KEYNAME, qvmContent);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_MAP_STRING_INT_KEYNAME));
    QVariantMap qvmResultMap = qvmData[MEMBER_MAP_STRING_INT_KEYNAME].toMap();
    QVERIFY(qvmResultMap.contains("li"));
    QVERIFY(qvmResultMap.contains("la"));
    QVERIFY(qvmResultMap.contains("laune"));
}

void CwtServiceTest::ChangeObjectMapStringDoubleValue()
{
    QVariantMap qvmContent;
    qvmContent.insert("li",3.1);
    qvmContent.insert("la",4.5);
    qvmContent.insert("laune",5.9);

    QVariantMap qvm;
    qvm.insert(MEMBER_MAP_STRING_DOUBLE_KEYNAME, qvmContent);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_MAP_STRING_DOUBLE_KEYNAME));
    QVariantMap qvmResultMap = qvmData[MEMBER_MAP_STRING_DOUBLE_KEYNAME].toMap();
    QVERIFY(qvmResultMap.contains("li"));
    QVERIFY(qvmResultMap.contains("la"));
    QVERIFY(qvmResultMap.contains("laune"));
}

void CwtServiceTest::ChangeObjectMapStringStringValue()
{
    QVariantMap qvmContent;
    qvmContent.insert("li","super");
    qvmContent.insert("la","klein");
    qvmContent.insert("laune","groß");

    QVariantMap qvm;
    qvm.insert(MEMBER_MAP_STRING_STRING_KEYNAME, qvmContent);

    CwmsJson cJson;
    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_MAP_STRING_STRING_KEYNAME));
    QVariantMap qvmResultMap = qvmData[MEMBER_MAP_STRING_STRING_KEYNAME].toMap();
    QVERIFY(qvmResultMap.contains("li"));
    QVERIFY(qvmResultMap.contains("la"));
    QVERIFY(qvmResultMap.contains("laune"));
}

void CwtServiceTest::ChangeBinDocValue()
{
    // TODO ChangeBinDocValue
}

void CwtServiceTest::ChangeObjectRefValue()
{
    CwmsJson cJson;
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();
    QString qstrObjectKeyname = pObject->GetKeyname();
    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);

    CwsHttpResponse response;
    CreateNoRefObjectOverRestRequest(response);

    QString qstrResponse = response.GetBody();
    QVariantMap qvmContent = cJson.parse(qstrResponse).toMap();


    QVariantMap qvm;
    QString qstrUri = CdmJsonToObjectMapper::GetSelfLink(qvmContent);
    qvm.insert(MEMBER_OBJREF_KEYNAME, qstrUri);


    QString qstrBody = cJson.serialize(qvm);
    QString qstrBodyResult = ChangeObjectReferencesValue(qstrBody);

    QVariantMap qvmResult = cJson.parse(qstrBodyResult).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(MEMBER_OBJREF_KEYNAME));
    QString refMap = qvmData[MEMBER_OBJREF_KEYNAME].toString();
    QCOMPARE(refMap, qstrUri);
}

void CwtServiceTest::ChangeContainerRefValue()
{
    // TODO ChangeContainerRefValue
}


void CwtServiceTest::ChangeObjectValue(QString p_qstrKeyname, QString p_qstrValue)
{
    QVariantMap qvm;
    qvm.insert(p_qstrKeyname, p_qstrValue);
    CwmsJson cJson;
    QString qstrJson = cJson.serialize(qvm);
    QString qstrBody = ChangeObjectValue(qstrJson);

    QVariantMap qvmResult = cJson.parse(qstrBody).toMap();
    QVERIFY(qvmResult.contains(WMS_SIMPLE_REST_DATA));
    QVariantMap qvmData = qvmResult[WMS_SIMPLE_REST_DATA].toMap();
    QVERIFY(qvmData.contains(p_qstrKeyname));
    QVERIFY(qvmData[p_qstrKeyname] == p_qstrValue);
}

QString CwtServiceTest::ChangeObjectValue(QString& qstrBody)
{
    return ChangeObjectValueForReferences(qstrBody, QString(TEST_CONTAINER_NAME_ALL_MEMBERS));
}

QString CwtServiceTest::ChangeObjectValueForReferences(QString& qstrBody, QString p_qstrContainerKeyname)
{
    CwmsTimeMeassurement cTime(m_bTimeMeassurementActive, "test");

    CdmObjectContainer* pContainer = GetContainer(p_qstrContainerKeyname);
    CdmObject* pObject = nullptr;

    if (p_qstrContainerKeyname == TEST_CONTAINER_NAME_ALL_MEMBERS)
    {
        pObject = CreateSingleNoRefObject(pContainer);
    }
    else
    {
        pObject = CreateSingleObject(pContainer);
    }

    QString qstrRequest = QString("PUT /Rest/Api/%1/%2/%3/%4 HTTP/1.1\r\n"
                                  "Host: localhost:8383\r\n"
                                  "Connection: keep-alive\r\n"
                                  "User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36\r\n"
                                  "Cache-Control: no-cache\r\n"
                                  "Authorization: Basic YWRtaW46YWRtaW4=\r\n"
                                  "Accept: */*\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                  "Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n%5")
            .arg(WMS_URI_OBJECT)
            .arg(m_qstrSchemeName)
            .arg(p_qstrContainerKeyname)
            .arg(pObject->GetKeyname())
            .arg(qstrBody);

    cTime.finishedTask("Finished Building Request");
    CwsHttpResponse response;
    ExcecuteRequest(qstrRequest, response, cTime);
    qstrBody = response.GetBody();
    return qstrBody;
}

QString CwtServiceTest::ChangeObjectReferencesValue(QString& qstrBody)
{
    return ChangeObjectValueForReferences(qstrBody, TEST_CONTAINER_NAME_REF);
}
