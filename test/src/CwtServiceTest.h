#ifndef CWTSERVICETEST_H
#define CWTSERVICETEST_H

#include "CwsHttpResponse.h"
#include "CwmsTimeMeassurement.h"

// Own Includes
#include "CwtTestBase.h"

class CwmscomHandler;

class CwtServiceTest : public CwtTestBase
{
    Q_OBJECT

private:
    CwmscomHandler* m_pHandler;
    CdmClass* m_pClassDerived1;
    CdmClass* m_pClassDerived2;
    long m_lObjectId;
    bool m_bTimeMeassurementActive;

    void LoadFunctionPlugins();
    void ExcecuteRequest(QString &p_qstrRequest, CwsHttpResponse &p_rResponse, CwmsTimeMeassurement &p_rTime);
    void TestContainerListRequest();
    QString GenerateListRequest(int p_iFrom, int p_iTo);
    void CreateNoRefObjects(CdmObjectContainer *pContainer, int p_iCount);
    CdmObject *CreateSingleNoRefObject(CdmObjectContainer *pContainer);
    QString ChangeObjectValue(QString &qstrBody);
    void ChangeObjectValue(QString p_qstrKeyname, QString p_qstrValue);
    QString ChangeObjectReferencesValue(QString &qstrBody);
    QString ChangeObjectValueForReferences(QString &qstrBody, QString p_qstrContainerKeyname);
    CdmObject *CreateSingleObject(CdmObjectContainer *pContainer);
    void CreateNoRefObjectOverRestRequest(CwsHttpResponse &response);
    
public:
    CwtServiceTest();
    virtual  ~CwtServiceTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void TestGetClassByKeyname();
    void TestContainerRequest();
    void TestClassManagerRequest();
    void TestSchemeRequest();
    void TestContainerManagerRequest();
    void TestDataProviderRequest();
    void TestFindUserRequest();
    void TestGetSchemeListRequest();
    void TestGetUserData();
    void FindContainerByKeyname();
    void FindContainerById();
    void CreateContainer();
    void GetContainerListByClassKeyname();
    void GetContainerListByClassId();
    void DeleteContainerByKeyname();
    void DeleteContainerById();
    void ListAllContainerObjects();
    void ListOneContainerObjects();
    void DeleteAllContainerObjects();
    void TestGetClassById();
    void GetObjectGraphNoRefObjects();
    void GetObjectGraphRefObjects();
    void CreateNoRefObject();
    void CreateRefObject();
    void ListManyContainerObjects();
    void ChangeObjectStringValue();
    void ChangeObjectIntValue();
    void ChangeObjectLongValue();
    void ChangeObjectFloatValue();
    void ChangeObjectDoubleValue();
    void ChangeObjectCharDocValue();
    void ChangeObjectEnumValue();
    void ChangeObjectDateTimeValue();
    void ChangeObjectTimeValue();
    void ChangeObjectDateValue();
    void ChangeObjectBoolValue();
    void ChangeObjectUserGroupValue();
    void ChangeObjectUserValue();
    void ChangeObjectCounterValue();
    void ChangeObjectListStringValue();
    void ChangeObjectListIntValue();
    void ChangeObjectListDoubleValue();
    void ChangeObjectMapIntIntValue();
    void ChangeObjectMapIntDoubleValue();
    void ChangeObjectMapIntStringValue();
    void ChangeObjectMapStringIntValue();
    void ChangeObjectMapStringDoubleValue();
    void ChangeObjectMapStringStringValue();
    void ChangeBinDocValue();
    void ChangeObjectRefValue();
    void ChangeContainerRefValue();
};

#endif // CWTSERVICETEST_H
