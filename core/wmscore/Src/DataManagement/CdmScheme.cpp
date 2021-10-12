/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <QString>
#include <QTextCodec>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <qdom.h>

// WMS COMMONS Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"
#include "CwmsJson.h"

// own Includes
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdmClass.h"
#include "CdmPackage.h"
#include "CdmScheme.h"
#include "CumUserManager.h"
#include "CdmObject.h"
#include "CdmMember.h"
#include "CdmObjectContainer.h"
#include "CdmValue.h"
#include "CdmGlobalContext.h"
#include "CdmModelElement.h"
#include "CdmMessageManager.h"
#include "CdmJournalItem.h"
#include "CdmClassMethod.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmContainerManager.h"
#include "CdmClassManager.h"
#include "CdmScheme.h"


CdmScheme::CdmScheme(qint64 p_lId, QString p_qstrDatabaseName, int p_iVersion)
    : m_rpCdmManager(nullptr),
      m_lId(p_lId),
      m_qstrSchemeName(p_qstrDatabaseName),
      m_iVersion(p_iVersion),
      m_pCumSchemeUserManager(nullptr),
      m_bDeploymentMode(false)
{
    m_rpCdmManager = CdmSessionManager::GetDataProvider();
}


CdmScheme::CdmScheme(QVariantMap& p_rqvHash)
    : m_rpCdmManager(nullptr),
      m_lId(-1),
      m_iVersion(-1),
      m_pCumSchemeUserManager(nullptr),
      m_bDeploymentMode(false)
{
    m_qstrSchemeName = p_rqvHash[WMS_NAME].toString();
    m_lId = p_rqvHash[WMS_ID].toInt();
    m_iVersion = p_rqvHash[WMS_VERSION].toInt();
    m_rpCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(m_rpCdmManager))
    {
        m_pCumSchemeUserManager = new CumUserManager(m_rpCdmManager->GetDataAccess(), GetUri());
    }
}

CdmScheme::~CdmScheme()
{
    DELPTR(m_pCumSchemeUserManager);
    ResetContainerManager();
}

void CdmScheme::ResetContainerManager()
{
    m_pCdmContainerManager.setLocalData(nullptr);
}

QVariant CdmScheme::GetVariant() const
{
    SYNCHRONIZED_READ;
    QVariantMap qvHash;

    qvHash.insert(WMS_ID, m_lId.load());
    qvHash.insert(WMS_NAME, m_qstrSchemeName);
    qvHash.insert(WMS_VERSION, m_iVersion.load());

    return qvHash;
}

QVariant CdmScheme::GetVariantCompleteDatabase() const
{
    SYNCHRONIZED_READ;
    QVariantMap qvHash = GetVariant().toMap();
    CdmClassManager* pClassManager = const_cast<CdmScheme*>(this)->GetClassManager();
    qvHash.insert(WMS_CLASSMANAGER, pClassManager->GetVariant());
    qvHash.insert(WMS_CONTAINERMANAGER, GetContainerManager()->GetVariant());
    qvHash.insert(WMS_USERMANAGER, GetSchemeUserManager()->GetVariant());
    return qvHash;
}

qint64 CdmScheme::GetId() const
{
    return m_lId.load();
}

QString CdmScheme::GetSchemeName() const
{
    SYNCHRONIZED_READ;
    return m_qstrSchemeName;
}

CdmClassManager* CdmScheme::GetClassManager()
{
    return CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetClassManager(m_lId);
}

CdmContainerManager* CdmScheme::GetContainerManager() const
{
    CdmContainerManager* pContainerManager = nullptr;

    if (!m_pCdmContainerManager.hasLocalData() ||
        m_pCdmContainerManager.localData() == nullptr)
    {
        pContainerManager = new CdmContainerManager(m_lId);
        const_cast<CdmScheme*>(this)->m_pCdmContainerManager.setLocalData(pContainerManager);
    }
    else
    {
        pContainerManager = m_pCdmContainerManager.localData();
    }

    return pContainerManager;
}

IdmDataAccess* CdmScheme::GetDataAccess()
{
    SYNCHRONIZED_READ;
    IdmDataAccess* pIdmDataAccess = nullptr;

    if(CHKPTR(m_rpCdmManager))
    {
        pIdmDataAccess = m_rpCdmManager->GetDataAccess();
    }

    return pIdmDataAccess;
}

int CdmScheme::GetVersion() const
{
    return m_iVersion.load();
}

void CdmScheme::SetVersion(  int p_iVersion )
{
    m_iVersion = p_iVersion;
}

qint64 CdmScheme::GetUserId() const
{
    SYNCHRONIZED_READ;
   qint64 lRet = CdmLogging::eDmUnknownDbError;

    if(CHKPTR(m_rpCdmManager))
    {
        lRet = m_rpCdmManager->GetUserId();
    }

    return lRet;
}

bool CdmScheme::CheckWriteAccess() const
{
    SYNCHRONIZED_READ;
    return m_cCdmRights.HasCurrentUserWriteAccess();
}

bool CdmScheme::CheckReadAccess() const
{
    SYNCHRONIZED_READ;
    return m_cCdmRights.HasCurrentUserReadAccess();
}

CdmRights& CdmScheme::GetRights()
{
    return m_cCdmRights;
}

void CdmScheme::SetCurrentLanguage(QString &p_qstrLanguage)
{
    SYNCHRONIZED_WRITE;
    m_qstrCurrentLanguage = p_qstrLanguage;
}

int CdmScheme::GetLanguageId(QString &p_qstrLanguage) const
{
    SYNCHRONIZED_READ;
    int iRet = 0;

    QMap<int, QString>::const_iterator qmIt = m_qmLanguages.begin();
    QMap<int, QString>::const_iterator qmItEnd = m_qmLanguages.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        if (qmIt.value() == p_qstrLanguage)
        {
            iRet = qmIt.key();
            break;
        }
    }

    return iRet;
}

QString CdmScheme::GetCurrentLanguageName() const
{
    SYNCHRONIZED_READ;
    return m_qstrCurrentLanguage;
}

QMap<int, QString> CdmScheme::GetLanguageMap()
{
    SYNCHRONIZED_READ;
    return m_qmLanguages;
}

QString CdmScheme::GetLanguage(int p_iId) const
{
    SYNCHRONIZED_READ;
    return m_qmLanguages[p_iId];
}

void CdmScheme::AddLanguage(QString &p_qstrName)
{
    SYNCHRONIZED_WRITE;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        IdmDataAccess* pCdmAccess = pCdmManager->GetDataAccess();

        if (CHKPTR(pCdmAccess))
        {
            int iLanguageId = pCdmAccess->AddLanguage(GetId(),
                                                      p_qstrName);

            if (iLanguageId > 0)
            {
                m_qmLanguages.insert(iLanguageId, p_qstrName);
            }
        }
    }
}

void CdmScheme::AddLanguage(int p_iId, QString &p_qstrName)
{
    SYNCHRONIZED_WRITE;
    m_qmLanguages.insert(p_iId, p_qstrName);
}

void CdmScheme::RemoveLanguage(int p_iId)
{
    SYNCHRONIZED_WRITE;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        IdmDataAccess* pCdmAccess = pCdmManager->GetDataAccess();

        if (CHKPTR(pCdmAccess))
        {
            if (pCdmAccess->DeleteLanguage(GetId(),
                                           p_iId))
            {
                m_qmLanguages.remove(p_iId);
            }
        }
    }
}

void CdmScheme::GetChanges(QList<CdmJournalItem*>& p_rqllChanges)
{
    QDate qdTo = QDate::currentDate();
    QDate qdFrom = QDate(2012,1,1);
    GetChanges(qdFrom, qdTo, p_rqllChanges);
}

void CdmScheme::GetChanges(QDate& p_qdFrom, QDate& p_qdTo, QList<CdmJournalItem*>& p_rqllChanges)
{
    SYNCHRONIZED_READ;
    IdmDataAccess* pCdmAccess = GetDataAccess();

    if (CHKPTR(pCdmAccess))
    {
       qint64 lId = GetId();
        pCdmAccess->GetSchemeModifications(lId,
                                             p_qdFrom,
                                             p_qdTo,
                                             p_rqllChanges);
    }
}

qint64 CdmScheme::Commit()
{
   qint64 lRet = CdmLogging::eDmUnknownDbError;
    SYNCHRONIZED_WRITE;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        IdmDataAccess* pCdmAccess = pCdmManager->GetDataAccess();

        if (CHKPTR(pCdmAccess))
        {
            lRet =pCdmAccess->UpdateScheme(this);
        }
    }

    return lRet;
}

CdmLocatedElement* CdmScheme::GetBaseObject(QString& p_qstrType,
                                            QString& p_qstrMajorKeyname,
                                            QString& p_qstrMinorKeyname,
                                            QString p_qstrValueKeyname = "")
{
    SYNCHRONIZED_READ;
    CdmLocatedElement* pCdmBase = nullptr;
    CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();
    CdmContainerManager* pContainerManager = GetContainerManager();

    if (CHKPTR(pCdmDataProvider))
    {
        if (p_qstrType.toLower() == WMS_URI_CLASS && CHKPTR(GetClassManager()))
        {
            if (CwmsUtilities::IsNumber(p_qstrMajorKeyname))
            {
                pCdmBase = GetClassManager()->FindClassById(p_qstrMajorKeyname.toInt());
            }
            else
            {
                pCdmBase = GetClassManager()->FindClassByKeyname(p_qstrMajorKeyname);
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_PACKAGE && CHKPTR(GetClassManager()))
        {
            pCdmBase = GetClassManager()->FindPackageByName(p_qstrMajorKeyname);
        }
        else if (p_qstrType.toLower() == WMS_URI_CLASS_MANAGER)
        {
            pCdmBase = GetClassManager();
        }
        else if (p_qstrType.toLower() == WMS_URI_CONTAINER_MANAGER && CHKPTR(GetContainerManager()))
        {
            pCdmBase = GetContainerManager();
        }
        else if (p_qstrType.toLower() == WMS_URI_MEMBER && CHKPTR(GetClassManager()))
        {
            CdmClass* pCdmClass = GetClassManager()->FindClassByKeyname(p_qstrMajorKeyname);

            if (CHKPTR(pCdmClass))
            {
                pCdmBase = const_cast<CdmMember*>(pCdmClass->FindMember(p_qstrMinorKeyname));
            }
            else
            {
                ERR(tr("The class by keyname in the uri is invalid"));
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_METHOD && CHKPTR(GetClassManager()))
        {
            CdmClass* pCdmClass = GetClassManager()->FindClassByKeyname(p_qstrMajorKeyname);

            if (CHKPTR(pCdmClass))
            {
                pCdmBase = pCdmClass->FindMethod(p_qstrMinorKeyname);
            }
            else
            {
                ERR(tr("The class id in the uri is invalid"));
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_CONTAINER && CHKPTR(pContainerManager))
        {
            if (CwmsUtilities::IsNumber(p_qstrMajorKeyname))
            {
                pCdmBase = pContainerManager->FindEmptyContainerById(p_qstrMajorKeyname.toLong());
            }
            else
            {
                pCdmBase = pContainerManager->FindEmptyContainerByKeyname(p_qstrMajorKeyname);
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_OBJECT && CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pList = nullptr;

            if (CwmsUtilities::IsNumber(p_qstrMajorKeyname))
            {
                pList = pContainerManager->FindEmptyContainerById(p_qstrMajorKeyname.toLong());
            }
            else
            {
                pList = pContainerManager->FindEmptyContainerByKeyname(p_qstrMajorKeyname);
            }

            if (pList) // can be nullptr by importing a deploymentfile
            {
                if (CwmsUtilities::IsNumber(p_qstrMinorKeyname))
                {
                    pCdmBase = pList->FindObjectById(p_qstrMinorKeyname.toLong());
                }
                else
                {
                    pCdmBase = pList->FindObjectByKeyname(p_qstrMinorKeyname);
                }
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_VALUE && CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pList = pContainerManager->FindEmptyContainerByKeyname(p_qstrMajorKeyname);

            if (CHKPTR(pList))
            {
                CdmObject* pObject = pList->FindObjectByKeyname(p_qstrMinorKeyname);

                if (CHKPTR(pObject))
                {
                    pCdmBase = pObject->GetValue(p_qstrValueKeyname);
                }
                else
                {
                    ERR(tr("The object keyname in the uri is invalid. Keyname: ") + p_qstrMinorKeyname);
                }
            }
            else
            {
                ERR(tr("The objectlist id in the uri is invalid. Keyname: ") + p_qstrMajorKeyname);
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_USER)
        {
            CumUserManager* pCumManager = GetSchemeUserManager();

            if (pCumManager)
            {
                if (CwmsUtilities::IsNumber(p_qstrMajorKeyname))
                {
                    pCdmBase = pCumManager->FindUserById(p_qstrMajorKeyname.toInt());
                } else {
                    pCdmBase = pCumManager->FindUserByLogin(p_qstrMajorKeyname);
                }
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_USERGROUP)
        {
            CumUserManager* pCumManager = GetSchemeUserManager();

            if (pCumManager)
            {
                pCdmBase = pCumManager->FindUserGroupByName(p_qstrMajorKeyname);
            }
        }
        else if (p_qstrType.toLower() == WMS_URI_SCHEME || p_qstrType.toLower() == WMS_URI_DATABASE)
        {
            pCdmBase = this;
        }
        else if (p_qstrType.toLower() == WMS_URI_DATAPROVIDER)
        {
            pCdmBase = pCdmDataProvider;
        }
    }

    return pCdmBase;
}

bool CdmScheme::GenerateDeploymentFile(QString& p_qstrFilename)
{
    SYNCHRONIZED_READ;
    bool bRet = false;
    m_bDeploymentMode = true;
    m_qlDeploymentRelevantEelements.clear();
    m_qlDeployedContainerIds.clear();
    QVariantMap qvHash;
    CwmsJson cJson;
    QVariant qvClass = GetClassManager()->GetVariant();
    QVariantList qvObjectLists;
    QList<CdmClass*> qllClasses;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    GetClassManager()->GetClassList(qllClasses);
    CdmContainerManager* pContainerManager = GetContainerManager();
    QList<CdmClass*>::iterator qllIt = qllClasses.begin();
    QList<CdmClass*>::iterator qllItEnd = qllClasses.end();

    if (CHKPTR(pContainerManager))
    {
        for(; qllIt != qllItEnd; ++qllIt)
        {
            CdmClass* pClass = *qllIt;

            if (pClass && !pClass->IsAbstract())
            {
                pContainerManager->GetDeploymentVariant(pClass, qvObjectLists);
            }
        }

        for (int iPos = 0; iPos < m_qlDeploymentRelevantEelements.count(); ++iPos)
        {
            CdmLocatedElement* pElement = pManager->GetUriObject(m_qlDeploymentRelevantEelements[iPos]);

            if (CHKPTR(pElement))
            {
                CdmObjectContainer* pContainer = nullptr;

                if (pElement->IsObject())
                {
                    CdmObject* pObject = static_cast<CdmObject*>(pElement);
                    pContainer = pObject->GetObjectContainer();
                }

                if (CHKPTR(pContainer) && !IsDeployedContainerId(pContainer->GetId()))
                {
                    pContainerManager->ReloadContainerComplete(pContainer);
                    qvObjectLists.append(pContainer->GetVariant());
                    m_qlDeployedContainerIds.append(pContainer->GetId());
                }
            }
        }

        QMap<int, QString>::iterator qmIt = m_qmLanguages.begin();
        QMap<int, QString>::iterator qmItEnd = m_qmLanguages.end();
        QVariantMap qvLanguages;

        for (; qmIt != qmItEnd; ++qmIt)
        {
            qvLanguages.insert(QString::number(qmIt.key()), qmIt.value());
        }

        qvHash.insert(WMS_LANGUAGES, qvLanguages);
        qvHash.insert(WMS_CLASSMANAGER, qvClass);
        qvHash.insert(WMS_CONTAINERMANAGER, qvObjectLists);

        CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pDataProvider))
        {
            CumUserManager* pUserManager = GetSchemeUserManager();

            if (CHKPTR(pUserManager))
            {
                qvHash.insert(WMS_USERGROUP, pUserManager->GetGroupVariant());
            }
        }
        QByteArray qbDeployment = cJson.serialize(qvHash, bRet);

        if(bRet)
        {
            QFile qfFile(p_qstrFilename);

            if (qfFile.open(QIODevice::WriteOnly))
            {
                QTextStream qStream(&qfFile);
                qStream.setCodec(QTextCodec::codecForName("UTF-8"));
                qStream << qbDeployment;
                qfFile.close();
            }
            else
            {
                ERR("Could not open file for writing data. Filename: " + p_qstrFilename);
                bRet = false;
            }
        }
        else
        {
            ERR("Could not serialize JSON");
        }
    }


    m_bDeploymentMode = false;
    qvHash.clear();
    m_qlDeploymentRelevantEelements.clear();
    m_qlDeployedContainerIds.clear();
    return bRet;
}

bool CdmScheme::IsDeployedContainerId(qint64 p_Id)
{
    SYNCHRONIZED_READ;
    return m_qlDeployedContainerIds.contains(p_Id);
}

void CdmScheme::AddDeployedContainerId(qint64 p_Id)
{
    SYNCHRONIZED_WRITE;
    if (!m_qlDeployedContainerIds.contains(p_Id))
    {
        m_qlDeployedContainerIds.append(p_Id);
    }
}

void CdmScheme::AddDeploymentRelevantElement(QString& p_qstrUri)
{
    SYNCHRONIZED_WRITE;
    if (!m_qlDeploymentRelevantEelements.contains(p_qstrUri))
    {
        m_qlDeploymentRelevantEelements.append(p_qstrUri);
    }
}

bool CdmScheme::Deploy(QString& p_qstrFilename)
{
    SYNCHRONIZED_WRITE;
    bool bRet = false;
    QString qstrContent;
    QFile qfFile(p_qstrFilename);

    if (qfFile.open(QIODevice::ReadOnly))
    {
        QTextStream qStream(&qfFile);
        qStream.setCodec(QTextCodec::codecForName("UTF-8"));
        qstrContent = qStream.readAll();
        bRet = DeployJsonContent(qstrContent);
    }
    else
    {
        ERR("File not found for deployment. File: " + p_qstrFilename);
    }

    return bRet;
}

bool CdmScheme::DeployJsonContent(QString& p_rqstrJson)
{
    SYNCHRONIZED_WRITE;
    bool bRet = false;
    CwmsJson cJson;
    QVariantMap qvHash = cJson.parse(p_rqstrJson, bRet).toMap();

    if (bRet)
    {
        QList<QString> qstrlKeys = qvHash.keys();
        QVariantMap qvClassManager = qvHash[WMS_CLASSMANAGER].toMap();
        qstrlKeys = qvClassManager.keys();
        GetClassManager()->Deploy(qvClassManager);
        QVariantList qvOLManager = qvHash[WMS_CONTAINERMANAGER].toList();
        CdmContainerManager* pContainerManager = GetContainerManager();
        if (CHKPTR(pContainerManager))
        {
            pContainerManager->Deploy(qvOLManager);
        }

        QVariantMap qvLanguages = qvHash[WMS_LANGUAGES].toMap();

        QVariantMap::iterator qIt = qvLanguages.begin();
        QVariantMap::iterator qItEnd = qvLanguages.end();

        for (; qIt != qItEnd; ++qIt)
        {
            QString qstrLanguage = qIt.value().toString();
            AddLanguage(qstrLanguage);
        }
    }

    return bRet;
}

bool CdmScheme::IsInDeploymentMode() const
{
    return m_bDeploymentMode.load();
}

bool CdmScheme::IsScheme() const
{
    return true;
}


QString CdmScheme::GetUri() const
{
    return CreateUri(WMS_URI_SCHEME, "");
}

QString CdmScheme::GetUriInternal() const
{
    return CreateUriPath(WMS_URI_SCHEME, GetSchemeName(), "", "");
}

CumUserManager* CdmScheme::GetSchemeUserManager() const
{
    if (!m_pCumSchemeUserManager && CHKPTR(m_rpCdmManager))
    {
        CdmSettings* pSettings = m_rpCdmManager->GetSettings();

        if (CHKPTR(pSettings))
        {
            if (pSettings->IsSchemeBasedUserManagementAcive())
            {
                const_cast<CdmScheme*> (this)->m_pCumSchemeUserManager = new CumUserManager(m_rpCdmManager->GetDataAccess(), GetUriInternal());
            }
            else
            {
                return m_rpCdmManager->GetUserManager();
            }
        }
    }

    return m_pCumSchemeUserManager;
}

