#include <QVariant>

#include "wmsdefines.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmScheme.h"
#include "CdmObject.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueDictStringString.h"

// Own includes
#include "CwmsServerSchemeManager.h"
#include "CwmsAppStoreData.h"

// Defines

#define WMS_APP_NAME "Name"
#define WMS_APP_DESCRIPTION "Description"
#define WMS_APP_DEVELOPER "Developer"
#define WMS_APP_EMAIL "Email"
#define WMS_APP_LOGO "Logo"
#define WMS_APP_APPLICATIONS "ApplicationVersionMap"
#define WMS_APP_ID "Id"
#define WMS_APP_WDF "Wdf"


CwmsAppStoreData::CwmsAppStoreData()
    : m_rpCurrentScheme(nullptr)
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    QString qstrScheme = WMS_TECHNICAL_SERVER;

    if (CHKPTR(pManager))
    {
       m_rpCurrentScheme = pManager->GetCurrentScheme();

       if (!m_rpCurrentScheme ||
           m_rpCurrentScheme->GetSchemeName() != qstrScheme) {
            pManager->FindSchemeByName(qstrScheme);
       }
    }
}

CwmsAppStoreData::~CwmsAppStoreData()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    QString qstrScheme = WMS_TECHNICAL_SERVER;

    if (CHKPTR(pManager) && m_rpCurrentScheme)
    {
        if (m_rpCurrentScheme == nullptr ||
            m_rpCurrentScheme->GetSchemeName() != qstrScheme)
        {
            pManager->RemoveLocalScheme(qstrScheme);
        }

        pManager->SetCurrentScheme(m_rpCurrentScheme);
    }
}

void CwmsAppStoreData::GetAppStoreData(QVariantList& p_rList)
{
    CdmObjectContainer* pContainer = LoadData();

    if (CHKPTR(pContainer))
    {
        QList<CdmObject*> qllObjects;
        pContainer->GetObjectList(qllObjects);
        ReadData(p_rList, qllObjects);
    }
}

qint64 CwmsAppStoreData::AddAppScheme(QVariantMap &p_rMap)
{
   qint64 lRet = 0;
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(APP_STORE_CONTAINER_NAME);

            if (CHKPTR(pContainer))
            {
                lRet = AddAppScheme(pContainer, p_rMap);
            }
        }
    }

    return lRet;
}

qint64 CwmsAppStoreData::AddAppScheme(CdmObjectContainer* p_pContainer, QVariantMap &p_rMap)
{
   qint64 lRet = 0;

    if (CHKPTR(p_pContainer))
    {
        CdmObject* pObject = p_pContainer->CreateNewObject();

        if (CHKPTR(pObject))
        {
            p_rMap[WMS_APP_APPLICATIONS];

            pObject->SetValue("Name", p_rMap[WMS_APP_NAME]);
            pObject->SetValue("Description", p_rMap[WMS_APP_DESCRIPTION]);
            pObject->SetValue("Manufacturer", p_rMap[WMS_APP_DEVELOPER]);
            pObject->SetValue("E-Mail", p_rMap[WMS_APP_EMAIL]);
            pObject->SetValue("WDF", p_rMap[WMS_APP_WDF]);

            CdmValue* pValue = pObject->GetValue("Sign");


            if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBinaryDocument)
            {
                CdmValueBinaryDocument* pBinDoc = static_cast<CdmValueBinaryDocument*>(pValue);
                QString qstrSign = p_rMap[WMS_APP_LOGO].toString();
                pBinDoc->SetBase64(p_rMap[WMS_APP_NAME].toString(), "IMG", qstrSign);
            }


            pValue = pObject->GetValue("Applications");

            if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueDictStringString)
            {
                CdmValueDictStringString* pDict = static_cast<CdmValueDictStringString*>(pValue);

                QVariantMap dictValue = p_rMap[WMS_APP_APPLICATIONS].toMap();

                QVariantMap::iterator qIt = dictValue.begin();
                QVariantMap::iterator qItEnd = dictValue.end();

                for (; qIt != qItEnd; ++qIt)
                {
                    pDict->SetValue(qIt.key(), qIt.value().toString());
                }
            }

            if (SUCCESSFULL(pObject->Commit()))
            {
                lRet = pObject->GetId();
            }
        }
    }

    return lRet;
}


bool CwmsAppStoreData::DeleteAppScheme(qint64 p_lAppSchemeId)
{
    bool bRet = false;
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(APP_STORE_CONTAINER_NAME);

            if (CHKPTR(pContainer))
            {
                bRet = DeleteAppScheme(pContainer, p_lAppSchemeId);
            }
        }
    }

    return bRet;
}

bool CwmsAppStoreData::DeleteAppScheme(CdmObjectContainer* p_pContainer,qint64 p_lAppSchemeId)
{
    bool bRet = false;

    if (CHKPTR(p_pContainer) && p_lAppSchemeId > 0)
    {
        if (SUCCESSFULL(p_pContainer->DeleteObject(p_lAppSchemeId)))
        {
            p_pContainer->Commit();
            bRet = true;
        }
    }

    return bRet;
}


CdmObjectContainer* CwmsAppStoreData::LoadData()
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(APP_STORE_CONTAINER_NAME);

            if (CHKPTR(pContainer))
            {
                pContainerManager->ReloadContainerComplete(pContainer);
            }
        }
    }

    return pContainer;
}


void CwmsAppStoreData::ReadData(QVariantList& p_rqvlApps, QList<CdmObject*>& p_rqllObjects)
{
    QList<CdmObject*>::iterator qllIt =  p_rqllObjects.begin();
    QList<CdmObject*>::iterator qllItEnd =  p_rqllObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        AddDataToVariant(p_rqvlApps, *qllIt);
    }
}

void CwmsAppStoreData::AddDataToVariant(QVariantList& p_rqvlApps, CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        QVariantMap entry;

        entry.insert(WMS_APP_NAME, p_pObject->GetDisplayString("Name"));
        entry.insert(WMS_APP_DESCRIPTION,p_pObject->GetDisplayString("Description"));
        entry.insert(WMS_APP_DEVELOPER, p_pObject->GetDisplayString("Manufacturer"));
        entry.insert(WMS_APP_EMAIL, p_pObject->GetDisplayString("E-Mail") );
        entry.insert(WMS_APP_ID, p_pObject->GetId());
        entry.insert(WMS_APP_WDF, p_pObject->GetDisplayString("WDF"));

        CdmValue* pValue = p_pObject->GetValue("Sign");

        if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBinaryDocument)
        {
            CdmValueBinaryDocument* pBinDoc = static_cast<CdmValueBinaryDocument*>(pValue);
            entry.insert(WMS_APP_LOGO, pBinDoc->GetBase64());
        }

        pValue = p_pObject->GetValue("Applications");

        if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueDictStringString)
        {
            CdmValueDictStringString* pDict = static_cast<CdmValueDictStringString*>(pValue);

            QMap<QString, QString> qmDict = pDict->GetDict();
            QVariantMap qvmVersionMap;

            QMap<QString, QString>::iterator qmIt = qmDict.begin();
            QMap<QString, QString>::iterator qmItEnd = qmDict.end();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                qvmVersionMap.insert(qmIt.key(), qmIt.value());
            }

            entry.insert(WMS_APP_APPLICATIONS, qvmVersionMap);

        }

        p_rqvlApps.append(entry);
    }
}
