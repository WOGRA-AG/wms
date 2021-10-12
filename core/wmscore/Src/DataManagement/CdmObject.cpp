/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qmap.h>
#include <qdom.h>
#include <QUuid>
#include <qtimer.h>
#include <QList>

// WMS Commons Includes
#include "CwmsJson.h"

// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmJournalItem.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueUser.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValue.h"
#include "CdmSettings.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"

CdmObject::CdmObject(qint64 p_lDatbaseId,
                    qint64 p_lId,
                     QString p_qstrKeyname,
                     const CdmClass* p_pCdmClass,
                     CdmObjectContainer* p_pContainer)
    : CdmModelElement(p_lDatbaseId, p_lId, p_qstrKeyname),
      m_iValueIdCounter(0),
      m_lClassId(0),
      m_rpContainer(p_pContainer),
      m_lContainerId(0),
      m_bIsInitialized(false),
      m_lParentId(0),
      m_bIsImmutable(false),
      m_bCommitRunning(false)
{

    if(CHKPTR(p_pCdmClass))
    {
        m_lClassId = p_pCdmClass->GetId();
    }
    else
    {
        ERR("Class Pointer is nullptr. This Object is invalid.");
        SetInvalid();
    }

    if(CHKPTR(m_rpContainer))
    {
        m_lContainerId = m_rpContainer->GetId();
    }
    else
    {
        ERR("ObjectList Pointer is nullptr. This Object is invalid.");
        SetInvalid();
    }


    InitObject();
}

CdmObject::CdmObject(qint64 p_lDatbaseId,
                    qint64 p_lId,
                     QString p_qstrKeyname,
                    qint64 p_lClassId,
                     CdmObjectContainer* p_pContainer )
    : CdmModelElement(p_lDatbaseId, p_lId, p_qstrKeyname),
      m_iValueIdCounter(0),
      m_lClassId(p_lClassId),
      m_rpContainer(p_pContainer),
      m_lContainerId(0),
      m_bIsInitialized(false),
      m_lParentId(0),
      m_bIsImmutable(false),
      m_bCommitRunning(false)
{
    m_rpContainer = p_pContainer;

    if(CHKPTR(m_rpContainer))
    {
        m_lContainerId = m_rpContainer->GetId();
    }
    else
    {
        ERR("Container Pointer is nullptr. This Object is invalid." );
        SetInvalid();
    }

    InitObject();
}

CdmObject::CdmObject(qint64 p_lDatbaseId,qint64 p_lId,qint64 p_lClassId,qint64 p_lObjectListId)
    : CdmModelElement(p_lDatbaseId, p_lId, ""),
      m_iValueIdCounter(0),
      m_lClassId(p_lClassId),
      m_rpContainer(nullptr),
      m_lContainerId(p_lObjectListId),
      m_bIsInitialized(false),
      m_lParentId(0),
      m_bIsImmutable(false),
      m_bCommitRunning(false)
{
}

CdmObject::CdmObject(const CdmObject& p_rCdmObject,qint64 p_lId)
    : CdmModelElement( p_rCdmObject.GetSchemeId(), p_lId, "" ),
      m_iValueIdCounter(0),
      m_lClassId(0),
      m_rpContainer(nullptr),
      m_lContainerId(0),
      m_bIsInitialized(false),
      m_lParentId(0),
      m_bIsImmutable(false),
      m_bCommitRunning(false)
{
    if (p_rCdmObject.IsValid())
    {
        SetInvalid();
    }

    m_rpContainer = p_rCdmObject.m_rpContainer;
    CopyFromSourceObject(p_rCdmObject);
}

CdmObject::CdmObject(CdmObjectContainer* p_pContainer, CdmObject* p_pCdmObject,qint64 p_lId)
    : CdmModelElement(p_pCdmObject->GetSchemeId(), p_lId, ""),
      m_iValueIdCounter(0),
      m_lClassId(0),
      m_rpContainer(nullptr),
      m_lContainerId(0),
      m_bIsInitialized(false),
      m_lParentId(0),
      m_bIsImmutable(false),
      m_bCommitRunning(false)
{
    if (!p_pCdmObject->IsValid())
    {
        SetInvalid();
    }

    if (CHKPTR(p_pContainer))
    {
        m_lContainerId = p_pContainer->GetId();
        m_lClassId = p_pContainer->GetClassId();
    }

    m_rpContainer = p_pContainer;
    CopyFromSourceObject(*p_pCdmObject);
}

CdmObject::CdmObject()
    : CdmModelElement(),
      m_iValueIdCounter(0),
      m_lClassId(0),
      m_rpContainer(nullptr),
      m_lContainerId(0),
      m_bIsInitialized(false),
      m_lParentId(0),
      m_bIsImmutable(false),
      m_bCommitRunning(false)
{
    FATAL("DO NOT CALL THIS. This method is for providing QML support!!!");
}

CdmObject::CdmObject(QVariantMap& p_rqvHash)
    : CdmModelElement(p_rqvHash),
      m_rpContainer(nullptr)
{
    SetVariant(p_rqvHash);
}

CdmObject::~CdmObject()
{
    ClearValuesFromObject();
}

void CdmObject::SetVariant(QVariantMap& p_rqvHash)
{
    CdmModelElement::SetVariant(p_rqvHash);
    m_lClassId = p_rqvHash[WMS_CLASSID].toInt();
    m_lContainerId = p_rqvHash[WMS_CONTAINERID].toInt();
    m_lParentId = p_rqvHash[WMS_PARENTID].toInt();
    m_bIsImmutable  = p_rqvHash[WMS_IMMUTABLE].toBool();

    QVariantMap qhValues = p_rqvHash[WMS_VALUES].toMap();
    SetValues(qhValues);
    m_bIsInitialized = true;

    SetObjectContainer(m_lContainerId);
}

void CdmObject::Deploy(QVariantMap& p_rqvHash)
{
    CdmModelElement::Deploy(p_rqvHash);
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pManager))
    {
        QString qstrClassUri = p_rqvHash[WMS_CLASSURI].toString();
        QString qstrObjectListUri = p_rqvHash[WMS_CONTAINERURI].toString();
        QString qstrParentUri = p_rqvHash[WMS_PARENTURI].toString();
        m_bIsImmutable  = p_rqvHash[WMS_IMMUTABLE].toBool();

        CdmModelElement* pElement = dynamic_cast<CdmModelElement*>(pManager->GetUriObject(qstrClassUri));

        if (pElement)
        {
            if (pElement->IsClass())
            {
                m_lClassId = pElement->GetId();
            }
            else
            {
                ERR("Wrong Type");
            }
        }

        pElement = dynamic_cast<CdmModelElement*>(pManager->GetUriObject(qstrObjectListUri));

        if (pElement)
        {
            if (pElement->IsContainer())
            {
                m_lContainerId = pElement->GetId();
            }
            else
            {
                ERR("Wrong Type");
            }
        }

        pElement = (CdmModelElement*)pManager->GetUriObject(qstrParentUri);

        if (pElement)
        {
            if (pElement->IsObject())
            {
                m_lParentId = pElement->GetId();
            }
            else
            {
                ERR("Wrong Type");
            }
        }
    }

    QVariantMap qhValues = p_rqvHash[WMS_VALUES].toMap();
    DeployValues(qhValues);
    SetModified();
    ObjectModifiedSlot();
    Commit();
}

void CdmObject::SetValues(QVariantMap& p_rqvHash)
{
    QVariantMap::iterator qhIt = p_rqvHash.begin();
    QVariantMap::iterator qhItEnd = p_rqvHash.end();

    for (; qhIt != qhItEnd; ++qhIt)
    {
        QVariantMap qvHash = qhIt.value().toMap();

        CdmValue* pCdmValue = nullptr;
        if(qvHash.contains(WMS_KEYNAME))
        {
            QString pKeyname = qvHash[WMS_KEYNAME].toString();
            pCdmValue = FindValueOverMember(pKeyname);
        }
        else
        {
            ERR("No id or keyname for value found");
        }

        if (!pCdmValue)
        {
            pCdmValue = CdmValue::CreateValue(qvHash, this);

            if (CHKPTR(pCdmValue))
            {
                m_qmValues.insert(qhIt.key(), pCdmValue);
                ++m_iValueIdCounter;
                connect(pCdmValue,
                        SIGNAL(ValueChanged(CdmValue*)),
                        this,
                        SLOT(ValueChangedSlot(CdmValue*)));
                pCdmValue->SetNew();
            }

            SetModified();
        }
        else
        {
            pCdmValue->SetVariant(qvHash);
        }
    }
}

void CdmObject::DeployValues(QVariantMap& p_rqvHash)
{
    QVariantMap::iterator qhIt = p_rqvHash.begin();
    QVariantMap::iterator qhItEnd = p_rqvHash.end();

    for (; qhIt != qhItEnd; ++qhIt)
    {
        QVariantMap qvHash = qhIt.value().toMap();
        QString qstrKeyname = qvHash[WMS_KEYNAME].toString();
        CdmValue* pCdmValue = GetValue(qstrKeyname);

        if (!pCdmValue)
        {
            pCdmValue = CdmValue::CreateDeployValue(qvHash, this);

            if (pCdmValue)
            {
                m_qmValues.insert(qhIt.key(), pCdmValue);
                ++m_iValueIdCounter;
                connect(pCdmValue,
                        SIGNAL(ValueChanged(CdmValue*)),
                        this,
                        SLOT(ValueChangedSlot(CdmValue*)));

                pCdmValue->SetNew();
                CdmClass* pClass = GetClass();

                if (CHKPTR(pClass))
                {
                    QString qstrKeyname = qvHash[WMS_KEYNAME].toString();
                    const CdmMember* pMember = pClass->FindMember(qstrKeyname);

                    if (CHKPTR(pMember))
                    {
                        pCdmValue->SetMemberId(pMember->GetId());
                    }
                }
            }
        }

        if (pCdmValue) // can be nullptr if value is a formula
        {
            pCdmValue->Deploy(qvHash);
            pCdmValue->SetModified();
        }
    }
}

void CdmObject::ClearValuesFromObject()
{
    QMap<QString,CdmValue*>::iterator qmIt    = m_qmValues.begin();
    QMap<QString,CdmValue*>::iterator qmItEnd = m_qmValues.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue* pCdmValue = qmIt.value();
        DELPTR(pCdmValue);
    }

    m_qmValues.clear();
    m_iValueIdCounter = 0;
}

void CdmObject::ClearPersistentValuesFromObject()
{
    QMap<QString,CdmValue*>::iterator qmIt    = m_qmValues.begin();
    QMap<QString,CdmValue*>::iterator qmItEnd = m_qmValues.end();
    QList<QString> qlValuesToRemove;

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue* pCdmValue = qmIt.value();

        if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() != eDmValueFormula)
        {
            const CdmMember* pMember = pCdmValue->GetMember();
            if (pMember && pMember->IsPersistent())
            {
                qlValuesToRemove.append(pCdmValue->GetKeyname());
                DELPTR(pCdmValue);
            }
        }
    }

    for (int iCOunter = 0; iCOunter < qlValuesToRemove.count(); ++iCOunter)
    {
        m_qmValues.remove(qlValuesToRemove[iCOunter]);
    }

    m_iValueIdCounter = m_qmValues.count() + 1;
}


void CdmObject::CopyFromSourceObject(const CdmObject& p_rCdmObject)
{
    m_iValueIdCounter = p_rCdmObject.m_iValueIdCounter;
    m_lClassId        = p_rCdmObject.m_lClassId;

    const CdmClass* pClass = p_rCdmObject.GetClass();
    QString qstrKeyname = pClass->GetKeyname();
    qstrKeyname += "_" + QUuid::createUuid().toString();
    SetKeyname(qstrKeyname);
    CopyValuesFromObject(p_rCdmObject);
}

void CdmObject::CopyValuesFromObject(const CdmObject& p_rCdmObject)
{
    QMap<QString,CdmValue*>::const_iterator qmIt    = p_rCdmObject.m_qmValues.begin();
    QMap<QString,CdmValue*>::const_iterator qmItEnd = p_rCdmObject.m_qmValues.end();


    int iCount = p_rCdmObject.m_qmValues.count();
    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue* pCdmSourceValue = qmIt.value();
        if(CHKPTR(pCdmSourceValue))
        {
            CdmValue* pCdmValue = CdmValue::CopyValue(pCdmSourceValue, this);

            if (CHKPTR(pCdmValue))
            {
                QString qstrKeyname = pCdmValue->GetKeyname();
                m_qmValues.insert(qstrKeyname, pCdmValue);


                connect(pCdmValue,
                        SIGNAL(ValueChanged(CdmValue*)),
                        this,
                        SLOT(ValueChangedSlot(CdmValue*)));
            }
            else
            {
                QString qstrMessage = "Could not copy value " + pCdmSourceValue->GetKeyname();
                ERR(qstrMessage);
            }
        }
    }

    int iCompareCount = m_qmValues.count();

    if (iCompareCount != iCount)
    {
        ERR("The valuecount from source and target objects are different!!!");
    }

    SetValid();

    if (!IsModified())
    {
        SetModified();
    }
}

//void CdmObject::CopyValuesFromObject(CdmObjectContainer *p_rCdmObjectContainer)
//{
//    CdmObject *pObjectSource = p_rCdmObjectContainer->FindObjectByIndex(0);

//    QMap<QString,CdmValue*>::iterator qmIt    = pObjectSource->m_qmValues.begin();
//    QMap<QString,CdmValue*>::iterator qmItEnd = pObjectSource->m_qmValues.end();


//    int iCount = pObjectSource->m_qmValues.count();
//    for (; qmIt != qmItEnd; ++qmIt)
//    {
//        CdmValue* pCdmSourceValue = qmIt.value();
//        if(CHKPTR(pCdmSourceValue))
//        {
//            CdmValue* pCdmValue = CdmValue::CopyValue(pCdmSourceValue, this);

//            if (CHKPTR(pCdmValue))
//            {
//                QString qstrKeyname = pCdmValue->GetKeyname();
//                m_qmValues.insert(qstrKeyname, pCdmValue);


//                connect(pCdmValue,
//                        SIGNAL(ValueChanged(CdmValue*)),
//                        this,
//                        SLOT(ValueChangedSlot(CdmValue*)));
//            }
//            else
//            {
//                QString qstrMessage = "Could not copy value " + pCdmSourceValue->GetKeyname();
//                ERR(qstrMessage);
//            }
//        }
//    }

//    int iCompareCount = m_qmValues.count();



//    if (iCompareCount == iCount)
//    {
//        SetValid();
//        if (!IsModified())
//        {
//            SetModified();
//        }
//    }
//    else
//    {
//        ERR("The valuecount from source and target objects are different!!!");
//    }

//}

int CdmObject::InitObject()
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    CdmClassManager* pClassManager = GetClassManager();
    if(m_lClassId > 0 &&
            !m_bIsInitialized && CHKPTR(pClassManager))
    {

        CdmClass* pClass = pClassManager->FindClassById(m_lClassId);
        QMap<qint64,CdmMember*> qvlMembers;
        pClass->GetMemberMap(qvlMembers);

        if(qvlMembers.count() > 0)
        {
            QMap<qint64,CdmMember*>::iterator qvlIt    = qvlMembers.begin();
            QMap<qint64,CdmMember*>::iterator qvlItEnd = qvlMembers.end();

            for ( ; qvlIt != qvlItEnd; ++ qvlIt )
            {
                CreateObjectValue(qvlIt.value());
            }

            m_bIsInitialized = true;
            SetValid();
            iRet = EC(eDmOk);
        }
        else
        {
            iRet = EC(eDmInitObjectWithoutMembers);
            ERR("Values Creation for this object failed.");
            SetInvalid();
        }
    }

    return iRet;
}

int CdmObject::InitObject(const CdmClass* p_pCdmClass)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    m_lClassId = p_pCdmClass->GetId();

    if(m_lClassId > 0)
    {
        iRet = InitObject();
        m_bIsInitialized = true;
    }
    else
    {
        iRet = EC(eDmInvalidClassPtr);
        ERR("nullptr Pointer in class!!!");
        SetInvalid();
    }

    return iRet;
}

bool CdmObject::IsObjectInitialized() const
{
    return m_bIsInitialized;
}

CdmClass* CdmObject::GetClass() const
{
    if (!m_rpClass)
    {
        CdmClassManager* pCdmClassManager = GetClassManager();

        if (CHKPTR(pCdmClassManager))
        {
            m_rpClass = pCdmClassManager->FindClassById(m_lClassId);
        }
    }

    return m_rpClass;
}

bool CdmObject::IsTypeOf(QString p_qstrClassName) const
{
    bool bRet = false;

    CdmClass* pCdmClass = GetClass();

    if (CHKPTR(pCdmClass))
    {
        if (pCdmClass->IsInherited(p_qstrClassName) > 0)
        {
            bRet = true;
        }
    }

    return bRet;
}

bool CdmObject::IsExactTypeOf(QString p_qstrClassName) const
{
    bool bRet = false;

    const CdmClass* pCdmClass = GetClass();

    if (CHKPTR(pCdmClass))
    {
        if (pCdmClass->GetFullQualifiedName() == p_qstrClassName)
        {
            bRet = true;
        }
    }

    return bRet;
}

bool CdmObject::IsTypeOf(CdmClass* p_pClass) const
{
    bool bRet = false;

    if (CHKPTR(p_pClass))
    {
        CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            if (pCdmClass->IsInherited(p_pClass) > 0)
            {
                bRet = true;
            }
        }
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

bool CdmObject::IsExactTypeOf(CdmClass* p_pClass) const
{
    bool bRet = false;

    if (p_pClass)
    {
        const CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            if (pCdmClass->GetId() == p_pClass->GetId())
            {
                bRet = true;
            }
        }
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

qint64 CdmObject::GetClassId() const
{
    return m_lClassId;
}

CdmValue* CdmObject::CreateObjectValue(CdmMember* p_pCdmMember)
{
    CdmValue* pCdmValue = nullptr;

    if(CHKPTR(p_pCdmMember))
    {
        QMap<QString, CdmValue*>::iterator qmIt = m_qmValues.find(p_pCdmMember->GetKeyname());

        if(qmIt == m_qmValues.end())
        {

            pCdmValue = CdmValue::CreateValue(p_pCdmMember, this);

            // if the member is owner of an objectlist it must be created
            if(p_pCdmMember->IsOwner() && pCdmValue->GetValueType() == eDmValueContainerRef)
            {
                CdmValueContainerRef* pCdmObjRef = dynamic_cast<CdmValueContainerRef*>(pCdmValue);
               qint64 lClassId = pCdmObjRef->GetClassId();
                CdmClassManager* pCdmClassManager = GetClassManager();

                if(CHKPTR(pCdmClassManager))
                {
                    CdmClass* pCdmClass = pCdmClassManager->FindClassById(lClassId);

                    if(CHKPTR(pCdmClass))
                    {
                        CdmContainerManager* pContainerManager = GetContainerManager();

                        if(CHKPTR(pContainerManager))
                        {
                            QString qstrKeyname = GetKeyname() + "_" + pCdmValue->GetKeyname();
                            pContainerManager->CreateContainer(pCdmClass, qstrKeyname);
                            CdmObjectContainer* pContainer = pContainerManager->FindContainerByKeyname(qstrKeyname);

                            if(CHKPTR(pContainer))
                            {
                                pCdmObjRef->SetValue(pContainer);
                                pCdmObjRef->SetNew();
                                pContainer->SetTree(p_pCdmMember->IsTree());
                            }
                        }
                    }
                }
            }

            if(CHKPTR(pCdmValue))
            {
                connect(pCdmValue,
                        SIGNAL(ValueChanged(CdmValue*)),
                        this,
                        SLOT(ValueChangedSlot(CdmValue*)));

                QString qstrKeyname = pCdmValue->GetKeyname();
                m_qmValues.insert(qstrKeyname, pCdmValue);
                m_iValueIdCounter++;
                ObjectModifiedSlot();
            }
            else
            {
                ERR("Value Creation for this object failed.");
                SetInvalid();
            }
        }
        else
        {
            INFO("Keyname found in value map no creation neccessary!!!");
        }
    }

    return pCdmValue;
}

int CdmObject::RemoveValue(QString p_qstrKeyname)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    QMap<QString, CdmValue*>::iterator qmIt = m_qmValues.find(p_qstrKeyname);

    if(qmIt != m_qmValues.end())
    {
        CdmValue* pCdmValue = qmIt.value();

        if(CHKPTR(pCdmValue))
        {
            m_qmValues.remove(p_qstrKeyname);
            delete pCdmValue;
            pCdmValue = nullptr;
        }
        else
        {
            iRet = EC(eDmInvalidPtr);
        }
    }
    else
    {
        iRet = EC(eDmObjectValueNotFound);
    }

    return iRet;
}

int CdmObject::AddObjectValue(CdmValue* p_pCdmValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if(CHKPTR(p_pCdmValue))
    {
        connect(p_pCdmValue, SIGNAL(ValueChanged(CdmValue*)), this, SLOT(ValueChangedSlot(CdmValue*)));
        QString qstrKeyname = p_pCdmValue->GetKeyname();
        m_qmValues.insert(qstrKeyname, p_pCdmValue);
        m_iValueIdCounter++;
        iRet = EC(eDmOk);
        SetValid();

        if (p_pCdmValue->GetValueType() == eDmValueObjectRef)
        {
            connect(dynamic_cast<CdmValueObjectRef*>(p_pCdmValue), SIGNAL(ObjectRefModifiedSignal(CdmObject*, CdmValue*)),
                    this, SLOT(ObjectRefModifiedSlot(CdmObject*, CdmValue*)));
        }

    }
    else
    {
        ERR("Value Creation for this object failed.");
        iRet = EC(eDmInvalidPtr);
        SetInvalid();
    }

    return iRet;
}

CdmValue* CdmObject::GetValue(int p_iMemberId)
{
    QMapIterator<QString,CdmValue*> qmIt(m_qmValues);

    while (qmIt.hasNext())
    {
        qmIt.next();

        if (qmIt.value()->GetMemberId() == p_iMemberId)
        {
            return qmIt.value();
        }
    }

    return nullptr;
}

CdmValue* CdmObject::GetValue(const QString& p_qstrKeyname)
{
    CdmValue* pCdmValue = nullptr;

    if(IsValid())
    {
        if (!p_qstrKeyname.contains("."))
        {
            if(m_qmValues.contains(p_qstrKeyname))
            {
                pCdmValue = m_qmValues[p_qstrKeyname];
            }

            if(!pCdmValue)
            {
                INFO("Value not found. Checking out if this is a new class member");
                pCdmValue = FindValueOverMember(p_qstrKeyname);
            }
        }
        else
        {
            pCdmValue = FindValueOverReference(p_qstrKeyname);
        }
    }
    else
    {
        ERR("GetValue called on a invalid object!!!\n Keyname '" + p_qstrKeyname + "'\n Object Info:\n" + GetInfo());
    }

    return pCdmValue;
}

CdmValue* CdmObject::FindValueOverReference(QString p_qstrKeyname)
{
    CdmValue* pCdmValue = nullptr;

    INFO("Value must be searched over references")
            int iPointPos = p_qstrKeyname.indexOf('.');

    if (iPointPos > 0)
    {
        QString qstrKeyname = p_qstrKeyname.mid(0, iPointPos);
        pCdmValue = GetValue(qstrKeyname);

        if (CHKPTR(pCdmValue))
        {
            if (pCdmValue->GetValueType() == eDmValueObjectRef)
            {
                CdmObject* pCdmObject = dynamic_cast<CdmValueObjectRef*> (pCdmValue)->GetObject();

                if (pCdmObject)
                {
                    qstrKeyname = p_qstrKeyname.mid(iPointPos+1, p_qstrKeyname.length() - iPointPos -1);
                    pCdmValue = pCdmObject->GetValue(qstrKeyname);

                    if (!pCdmValue)
                    {
                        INFO("VALUE \"" + qstrKeyname +"\" not found!!");
                    }
                }
                else
                {
                    INFO("The Object in the reference is nullptr");
                    pCdmValue = nullptr;
                }
            }
            else
            {
                ERR("Value " + qstrKeyname + " is not a objectreference");
                pCdmValue = nullptr;
            }
        }
    }
    else
    {
        ERR("There exist no member with the keyname '" + p_qstrKeyname + "' in the object class!!!\n"
                                                                         "Object Info:\n" + GetInfo());
    }

    return pCdmValue;
}

CdmValue* CdmObject::FindValueOverMember(QString p_qstrKeyname)
{
    CdmValue* pCdmValue = nullptr;
    CdmClass* pCdmClass = GetClass();

    if(CHKPTR(pCdmClass))
    {
        if (!m_qmValues.contains(p_qstrKeyname))
        {
            const CdmMember* pCdmMember = pCdmClass->FindMember(p_qstrKeyname);

            if(pCdmMember)
            {
                pCdmValue = CreateObjectValue(const_cast<CdmMember*>(pCdmMember));
                pCdmValue->SetNew();
                SetModified();
            }
            else
            {
                INFO("Member not found checking if there is a point operator");
            }
        }
        else
        {
            pCdmValue = m_qmValues[p_qstrKeyname];
        }
    }

    return pCdmValue;
}

void CdmObject::GetValueMap(QMap<QString, CdmValue*>& p_qmValues) const
{
    p_qmValues =  m_qmValues;
}

void CdmObject::CheckAllValuesCreated()
{
    CdmClass* pClass = GetClass();
    QMap<qint64,CdmMember*> qvlMembers;
    pClass->GetMemberMap(qvlMembers);

    if(qvlMembers.count() > 0)
    {
        QMap<qint64,CdmMember*>::iterator qvlIt    = qvlMembers.begin();
        QMap<qint64,CdmMember*>::iterator qvlItEnd = qvlMembers.end();

        for ( ; qvlIt != qvlItEnd; ++ qvlIt )
        {
            CdmMember* pMember = qvlIt.value();

            if (CHKPTR(pMember))
            {
                GetValue(pMember->GetKeyname());
            }
        }
    }
}

QMap<QString, CdmValue*>& CdmObject::GetValueMap()
{
    return m_qmValues;
}

int CdmObject::GetValue(const QString& p_qstrKeyname, QString& p_qstrValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if(eDmValue == eDmValueString)
            {
                p_qstrValue = dynamic_cast<CdmValueString*>(pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else if(eDmValue == eDmValueCharacterDocument)
            {
                p_qstrValue = dynamic_cast<CdmValueCharacterDocument*>(pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR(QString("Wrong Type for this Value. Value: %1 Type %2").arg(p_qstrKeyname).arg(eDmValue));
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_qstrKeyname, CumUser*& p_pCumUser)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if(eDmValue == eDmValueUser)
            {
                p_pCumUser = dynamic_cast<CdmValueUser*>(pCdmValue)->GetUser();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR("Wrong Value for this Value.");
                iRet = EC(eDmWrongValueType);
            }
        }

    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const QString p_qstrValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();
        if (eDmValue == eDmValueString)
        {
            dynamic_cast<CdmValueString*> (pCdmValue)->SetValue(p_qstrValue);
            iRet = EC(eDmOk);
        }
        else if (eDmValue == eDmValueCharacterDocument)
        {
            dynamic_cast<CdmValueCharacterDocument*> (pCdmValue)->SetValue(p_qstrValue);
            iRet = EC(eDmOk);
        }
        else
        {
            iRet = EC(eDmWrongValueType);
            ERR("Wrong Value for this Value. Keyname: " + p_qstrKeyname + " Value: " + p_qstrValue);
        }
    }
    else
    {
        ERR("Value \"" + p_qstrKeyname + "\" not found. No update possible.");
    }

    return iRet;
}

int CdmObject::SetValue(QString p_pKeyname, const char* p_pValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if(CHKPTR(p_pValue))
    {
        iRet = SetValue(p_pKeyname, QString(p_pValue));
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_qstrKeyname, bool& p_bValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue))
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if(eDmValue == eDmValueBool)
            {
                p_bValue = dynamic_cast<CdmValueBool*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                iRet = EC(eDmWrongValueType);
                ERR("Wrong Value for this Value.");
            }
        }
        else
        {
            ERR("Value " + p_qstrKeyname + " not found in Object " + GetUri());
        }
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, bool p_bValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();

        if(eDmValue == eDmValueBool)
        {
            dynamic_cast<CdmValueBool*> (pCdmValue)->SetValue(p_bValue);
            iRet = EC(eDmOk);
        }
        else
        {
            iRet = EC(eDmWrongValueType);
            ERR("Wrong Value for this Value.");
        }
    }



    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const QDate& p_rqdValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();

        if(eDmValue == eDmValueDate)
        {
            dynamic_cast<CdmValueDate*> (pCdmValue)->SetValue(p_rqdValue);
            iRet = EC(eDmOk);
        }
        else
        {
            iRet = EC(eDmWrongValueType);
            ERR("Wrong Value for this Value.");
        }
    }



    return iRet;
}

int CdmObject::GetValue(const QString& p_qstrKeyname, QDate& p_rqdValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if (eDmValue == eDmValueDate)
            {
                p_rqdValue = dynamic_cast<CdmValueDate*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR("Wrong Value for this Value.");
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_rqstrKeyname, QDateTime& p_rqdtValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_rqstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if(eDmValue == eDmValueDateTime)
            {
                p_rqdtValue = dynamic_cast<CdmValueDateTime*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
                QString qstr = p_rqdtValue.toString();
            }
            else
            {
                ERR("Wrong Value for this Value.");
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const QDateTime& p_rqdtValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();
        if(eDmValue == eDmValueDateTime)
        {
            dynamic_cast<CdmValueDateTime*> (pCdmValue)->SetValue(p_rqdtValue);
            iRet = EC(eDmOk);
        }
        else
        {
            ERR("Wrong Value for this Value.");
            iRet = EC(eDmWrongValueType);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_rqstrKeyname, double& p_rdValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if(IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_rqstrKeyname);

        if (CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();
            if (eDmValue == eDmValueDouble)
            {
                p_rdValue = dynamic_cast<CdmValueDouble*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else if (eDmValue == eDmValueFloat)
            {
                p_rdValue = dynamic_cast<CdmValueFloat*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR("Wrong Value for this Value.");
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const double p_rdValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();

        if(eDmValue == eDmValueDouble)
        {
            dynamic_cast<CdmValueDouble*> (pCdmValue)->SetValue(p_rdValue);
            iRet = EC(eDmOk);
        }
        else if(eDmValue == eDmValueFloat)
        {
            dynamic_cast<CdmValueFloat*> (pCdmValue)->SetValue(p_rdValue);

            iRet = EC(eDmOk);
        }
        else
        {
            ERR("Wrong Value for this Value. Keyname: " +
                p_qstrKeyname + " ValueType: " + QString::number(eDmValue));
            iRet = EC(eDmWrongValueType);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_rqstrKeyname, float& p_rfValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_rqstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if(eDmValue == eDmValueFloat)
            {
                p_rfValue = dynamic_cast<CdmValueFloat*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR("Wrong Value for this Value (Float). Keyname: " +p_rqstrKeyname);
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const float p_rfValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();
        if(eDmValue == eDmValueFloat)
        {
            dynamic_cast<CdmValueFloat*> (pCdmValue)->SetValue(p_rfValue);
            iRet = EC(eDmOk);
        }
        else if(eDmValue == eDmValueDouble)
        {
            dynamic_cast<CdmValueDouble*> (pCdmValue)->SetValue(p_rfValue);
            iRet = EC(eDmOk);
        }
        else
        {
            ERR("Wrong Value for this Value.");
            iRet = EC(eDmWrongValueType);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const int p_riValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();

        if(eDmValue == eDmValueInt)
        {
            dynamic_cast<CdmValueInt*> (pCdmValue)->SetValue(p_riValue);
            iRet = EC(eDmOk);
        }
        else if(eDmValue == eDmValueLong)
        {
            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(p_riValue);
            iRet = EC(eDmOk);
        }
        else if(eDmValue == eDmValueCounter)
        {
            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(p_riValue);
            iRet = EC(eDmOk);
        }
        else if(eDmValue == eDmValueUser)
        {
            dynamic_cast<CdmValueUser*> (pCdmValue)->SetValue(p_riValue);
            iRet = EC(eDmOk);
        }
        else if(eDmValue == eDmValueEnum)
        {
            dynamic_cast<CdmValueInt*> (pCdmValue)->SetValue(p_riValue);
            iRet = EC(eDmOk);
        }
        else
        {
            ERR("Wrong Value for this Value.");
            iRet = EC(eDmWrongValueType);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_qstrKeyname, int& p_iValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if(IsValid())
    {
        SYNCHRONIZED;

        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();
            if(eDmValue == eDmValueInt || eDmValue == eDmValueUser || eDmValue == eDmValueEnum)
            {
                p_iValue = dynamic_cast<CdmValueInt*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else if (eDmValue == eDmValueCounter)
            {
                p_iValue = dynamic_cast<CdmValueCounter*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else if (eDmValue == eDmValueLong)
            {
                p_iValue = dynamic_cast<CdmValueLong*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR("Wrong Value for this Value.");
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_qstrKeyname,qint64& p_lValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if(IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();
            if(eDmValue == eDmValueLong)
            {
                p_lValue = dynamic_cast<CdmValueLong*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else if(eDmValue == eDmValueContainerRef)
            {
                p_lValue = dynamic_cast<CdmValueLong*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else if(eDmValue == eDmValueObjectRef)
            {
                p_lValue = dynamic_cast<CdmValueLong*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                ERR("Wrong Value for this Value.");
                iRet = EC(eDmWrongValueType);
            }
        }
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const qint64 p_lValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();
        if (eDmValue == eDmValueLong)
        {
            iRet = EC(eDmOk);
            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(p_lValue);
        }
        else if (eDmValue == eDmValueContainerRef)
        {
            iRet = EC(eDmOk);
            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(p_lValue);
        }
        else if (eDmValue == eDmValueObjectRef)
        {
            iRet = EC(eDmOk);
            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(p_lValue);
        }
        else if (eDmValue == eDmValueCounter)
        {
            iRet = EC(eDmOk);
            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(p_lValue);
        }
        else if (eDmValue == eDmValueUser)
        {
            iRet = EC(eDmOk);
            dynamic_cast<CdmValueUser*> (pCdmValue)->SetValue(p_lValue);
        }
        else
        {
            iRet = EC(eDmWrongValueType);
            ERR("Wrong Value for this Value.");
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

int CdmObject::GetValue(const QString& p_qstrKeyname, QTime& p_qtValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if(IsValid())
    {
        SYNCHRONIZED;
        CdmValue* pCdmValue = GetValue(p_qstrKeyname);

        if(CHKPTR(pCdmValue) && pCdmValue->HasValue())
        {
            EdmValueType eDmValue = pCdmValue->GetValueType();

            if(eDmValue == eDmValueTime)
            {
                p_qtValue = dynamic_cast<CdmValueTime*> (pCdmValue)->GetValue();
                iRet = EC(eDmOk);
            }
            else
            {
                iRet = EC(eDmWrongValueType);
                ERR("Wrong Value for this Value.");
            }
        }
    }

    return iRet;
}

int CdmObject::SetValue(const QString& p_qstrKeyname, const QTime& p_qtValue)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        EdmValueType eDmValue = pCdmValue->GetValueType();
        if(eDmValue == eDmValueTime)
        {
            dynamic_cast<CdmValueTime*> (pCdmValue)->SetValue(p_qtValue);
            iRet = EC(eDmOk);
        }
        else
        {
            iRet = EC(eDmWrongValueType);
            ERR("Wrong Value for this Value.");
        }
    }

    return iRet;
}

int CdmObject::DeleteValue(const QString& p_qstrKeyname)
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    SYNCHRONIZED;
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if(CHKPTR(pCdmValue))
    {
        iRet = pCdmValue->DeleteValue();
    }

    return iRet;
}

void CdmObject::SetDeleted() 
{
    UnlockObjectOnDb();
    CdmModelElement::SetDeleted();
    //DeleteOwnerRefs();
    SetInvalid();
    emit ObjectDeletedSignal(this);
}

void CdmObject::SetNew()
{
    CdmModelElement::SetNew();
}

void CdmObject::CommitOwnRefs()
{
    CdmClass* pCdmClass = GetClass();
    if(CHKPTR(pCdmClass))
    {
        QMap<QString,CdmValue*>::iterator qmIt    = m_qmValues.begin();
        QMap<QString,CdmValue*>::iterator qmItEnd = m_qmValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmValue* pCdmValue = qmIt.value();

            if(CHKPTR(pCdmValue))
            {
                const CdmMember* pCdmMember = pCdmClass->FindMember(pCdmValue->GetKeyname());

                if (CHKPTR(pCdmMember) &&
                    pCdmMember->IsOwner())
                {
                    if(pCdmValue->GetValueType() == eDmValueContainerRef)
                    {
                        CdmValueContainerRef* pCdmObjListRef = dynamic_cast<CdmValueContainerRef*>(pCdmValue);
                        CdmObjectContainer* pContainer = pCdmObjListRef->GetContainer();

                        if(pContainer)  // can be nullptr if it was deleted before
                        {
                            pContainer->Commit();
                        }
                    }
                    else if(pCdmValue->GetValueType() == eDmValueObjectRef)
                    {
                        CdmValueObjectRef* pCdmObjRef = dynamic_cast<CdmValueObjectRef*>(pCdmValue);
                        CdmObject* pCdmObject = pCdmObjRef->GetObject();

                        if(pCdmObject) // can be nullptr if it was deleted before
                        {
                            pCdmObject->Commit();
                        }
                    }
                }
            }
        }
    }
}

void CdmObject::DeleteOwnerRefs(  )
{
    CdmClass* pCdmClass = GetClass();
    if(CHKPTR(pCdmClass))
    {
        QMap<QString,CdmValue*>::iterator qmIt    = m_qmValues.begin();
        QMap<QString,CdmValue*>::iterator qmItEnd = m_qmValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmValue* pCdmValue = qmIt.value();

            if(CHKPTR(pCdmValue))
            {
                const CdmMember* pCdmMember = pCdmClass->FindMember(pCdmValue->GetKeyname());

                if(pCdmMember &&
                        pCdmMember->IsOwner() &&
                        pCdmValue->GetValueType() == eDmValueContainerRef)
                {
                    CdmValueContainerRef* pCdmObjListRef = dynamic_cast<CdmValueContainerRef*> (pCdmValue);

                    CdmObjectContainer* pContainer = pCdmObjListRef->GetContainer();

                    // can be nullptr if it was deleted before
                    if(pContainer)
                    {
                        pContainer->SetDeleted();
                        pContainer->Commit();
                    }
                }
                else if(pCdmMember &&
                        pCdmMember->IsOwner() &&
                        pCdmValue->GetValueType() == eDmValueObjectRef)
                {
                    CdmValueObjectRef* pCdmObjRef = dynamic_cast<CdmValueObjectRef*> (pCdmValue);

                    CdmObject* pCdmObject = pCdmObjRef->GetObject();

                    // can be nullptr if it was deleted before
                    if(pCdmObject)
                    {
                        pCdmObject->SetDeleted();
                        pCdmObject->Commit();
                    }
                }
            }
        }
    }
}

void CdmObject::ValueChangedSlot(  CdmValue* p_pCdmValue )
{
    if(CHKPTR(p_pCdmValue))
    {
        // the check is needed because the objectref value
        // emits the event when the child object has changed
        if (p_pCdmValue->IsModified())
        {
            if (!IsModified())
            {
                CdmModelElement::SetModified();
            }
        }

        ObjectModifiedSlot();
    }
}

void CdmObject::ObjectModifiedSlot(  )
{
    emit ObjectModifiedSignal(this);
}


CdmObjectContainer* CdmObject::GetObjectContainer() const
{
    return m_rpContainer;
}

void CdmObject::SetObjectContainer(  CdmObjectContainer* p_pContainer )
{
    m_rpContainer = p_pContainer;

    if (p_pContainer)
    {
        m_lClassId = p_pContainer->GetClassId();
    }
}

void CdmObject::SetObjectContainer(qint64 lObjectContainerId)
{
    if(m_rpContainer == nullptr || m_rpContainer->GetId() != lObjectContainerId)
    {
        CdmDataProvider *pProvider = CdmSessionManager::GetDataProvider();
        CdmContainerManager *pManager = pProvider->GetContainerManager();
        CdmObjectContainer *pContainer = pManager->FindEmptyContainerById(lObjectContainerId);
        if(pContainer)
        {
            SetObjectContainer(pContainer);
        }
        else
        {
            ERR("Container not found! ContainerId:" + QString::number(lObjectContainerId));
        }
    }
}

qint64 CdmObject::GetObjectContainerId() const
{
    if (m_lContainerId == 0)
    {
        WARNING("ObjectList Id is 0 Try to read the objectlist pointer for ther ID");

        if (m_rpContainer)
        {
            m_lContainerId = (const_cast<CdmObjectContainer*>(m_rpContainer))->GetId();

            if (m_lContainerId == 0)
            {
                ERR("ObjectList ID still invalid!!!");
            }
        }
        else
        {
            ERR("Coould not resolve object for Id.");
        }

    }

    return m_lContainerId;
}

void CdmObject::ResetNewModified()
{
    CdmModelElement::ResetNewModified();

    QMap<QString,CdmValue*>::iterator qmIt    = m_qmValues.begin();
    QMap<QString,CdmValue*>::iterator qmItEnd = m_qmValues.end();

    for ( ; qmIt != qmItEnd; ++qmIt )
    {
        CdmValue* pCdmValue = qmIt.value();

        if(CHKPTR(pCdmValue))
        {
            pCdmValue->ResetNewModified();
        }
    }
}

int CdmObject::GetValueCounter() const
{
    return m_iValueIdCounter;
}

void CdmObject::SetValueIdCounter(int p_lValueIdCounter)
{
    m_iValueIdCounter = p_lValueIdCounter;
}

int CdmObject::Commit()
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (!m_bCommitRunning)
    {
        m_bCommitRunning = true;
        bool bDeleted = IsDeleted();

        if (!bDeleted)
        {
            CommitOwnRefs();
        }

        if (IsNew() || IsModified() || IsDeleted())
        {
            SetModifierId(GetUserId());
            CdmObjectContainer* pContainer = GetObjectContainer();

            if(CHKPTR(pContainer))
            {
                iRet = pContainer->Commit();
            }
            else
            {
                iRet = EC(eDmInvalidPtr);
            }
        }
        else
        {
            iRet = CdmLogging::eDmOk;
        }

        m_bCommitRunning = false;
    }
    else
    {
        iRet = CdmLogging::eDmOk;
    }

    return iRet;
}

void CdmObject::GetCounterValues()
{
    if(IsNew())
    {
        QMap<QString,CdmValue*>::iterator qmIt    = m_qmValues.begin();
        QMap<QString,CdmValue*>::iterator qmItEnd = m_qmValues.end();

        for ( ; qmIt != qmItEnd; ++qmIt )
        {
            CdmValue* pCdmValue = qmIt.value();

            if(CHKPTR(pCdmValue))
            {
                if(pCdmValue->GetValueType() == eDmValueCounter)
                {
                    IdmDataAccess* pIdmDataAccess = GetDataAccess();

                    if(CHKPTR(pIdmDataAccess))
                    {
                       qint64 lValue = 0;
                        lValue = pIdmDataAccess->GetCounterValue(GetObjectContainer(), pCdmValue);

                        if(lValue >= 0)
                        {
                            // Cast to qint64 because every counter is a qint64 value
                            dynamic_cast<CdmValueLong*> (pCdmValue)->SetValue(lValue);

                        }
                        else
                        {
                            ERR("Error while trying to get the counterids!!!");
                        }
                    }
                }
            }
        }
    }
}

int CdmObject::LockObjectOnDb()
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        bool bSuccess = false;
        iRet = pIdmDataAccess->LockObject(this, bSuccess);

        if(!bSuccess)
        {
            ERR("Locking does not work!!!");
            if(iRet >= 0)
            {
                iRet = EC(eDmLockingErr);
            }
        }
    }

    return iRet;
}

int CdmObject::UnlockObjectOnDb()
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        bool bSuccess = false;
        iRet = pIdmDataAccess->UnLockObject(this, bSuccess);

        if(!bSuccess)
        {
            ERR("Unlocking does not work!!!");
            if(iRet >= 0)
            {
                iRet = EC(eDmLockingErr);
            }
        }
    }

    return iRet;
}

int CdmObject::MoveToObjectList(CdmObjectContainer* p_pContainer)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (CHKPTR(p_pContainer))
    {
        if (p_pContainer->GetClassId() == m_lClassId)
        {
            // 1. remove from old objectlist map
            m_rpContainer->RemoveObjectLocalWithoutDelete(GetId());

            // 2. set new objectlist
            m_lContainerId = p_pContainer->GetId();
            m_rpContainer = p_pContainer;

            // 3. insert in new objectlist map
            m_rpContainer->AddObject(this);

            // 4. store changes
            if (!IsModified())
            {
                SetModified();
            }

            iRet = Commit();
        }
        else
        {
            iRet = EC(eDmObjectClassIsDifferent);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }


    return iRet;
}

QString CdmObject::GetCaption() const
{
    QString qstrDisplayString;

    const CdmClass* pClass = GetClass();

    if (pClass)
    {
        qstrDisplayString = GetDisplayString(pClass->GetCaptionMemberKeyname());
    }
    else
    {
        qstrDisplayString = GetKeyname();
    }

    return qstrDisplayString;
}

QString CdmObject::GetObjectContainerKeyname() const
{
    CdmObjectContainer* pContainer = GetObjectContainer();

    if (CHKPTR(pContainer))
    {
        return pContainer->GetKeyname();
    }

    return "";
}

QString CdmObject::GetInfo() const
{
    QString qstrRet;

    qstrRet += "\n\n";
    qstrRet = CdmModelElement::GetInfo();
    qstrRet += "\n\n";

    qstrRet += "Object Informations:\n";
    qstrRet += WMS_CONTAINER + QString(": ");

    if (m_rpContainer)
    {
        qstrRet += m_rpContainer->GetKeyname() + " / " + m_rpContainer->GetCaption() + "\n";
    }
    else
    {
        qstrRet += "nullptr\n";
    }

    qstrRet += "Class Id:" + QString::number(m_lClassId) + "\n";
    qstrRet += "Class:      ";

    CdmClass* pCdmClass = GetClass();

    if (pCdmClass)
    {
        qstrRet += pCdmClass->GetKeyname() + "\n";
    }
    else
    {
        qstrRet += "nullptr\n";
    }

    qstrRet += "Values: " +QString::number(m_qmValues.count()) + "\n";

    return qstrRet;
}

bool CdmObject::IsValid() const
{
    if (m_qmValues.count() == 0)
    {
        INFO("Invalid Object: \n" + GetInfo())
        (const_cast<CdmObject*>(this))->SetInvalid();
    }

    return CdmModelElement::IsValid();
}

void CdmObject::Refresh()
{
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if (CHKPTR(pIdmDataAccess) && !IsNew())
    {
       qint64 lSuccess = pIdmDataAccess->RefreshObject(this);

        if (lSuccess == CdmLogging::eDmObjectNotFound)
        {
            SetDeleted();
        }

        ResetNewModified();
    }
}

QVariant CdmObject::GetVariant(QString p_qstrKeyname) const
{
    QVariant qVariant;
    CdmValue* pCdmValue = (const_cast<CdmObject*>(this))->GetValue(p_qstrKeyname);

    if (pCdmValue)
    {
        qVariant = pCdmValue->GetValueVariant();
    }

    return qVariant;
}

void CdmObject::SetValue(QString p_qstrKeyname, QVariant p_qvValue)
{
    CdmValue* pCdmValue = GetValue(p_qstrKeyname);

    if (pCdmValue)
    {
        pCdmValue->SetValueVariant(p_qvValue);
    }
}

QVariant CdmObject::GetVariant() const
{
    QVariantMap qmVariant;

    qmVariant = CdmModelElement::GetVariant().toMap();
    qmVariant.insert(WMS_CLASSID, static_cast<int>(m_lClassId));
    qmVariant.insert(WMS_CONTAINERID, static_cast<int>(m_lContainerId));
    qmVariant.insert(WMS_PARENTID, static_cast<int>(m_lParentId));
    qmVariant.insert(WMS_IMMUTABLE, m_bIsImmutable);

    CdmClass* pCdmClass = GetClass();

    if (CHKPTR(pCdmClass))
    {
        qmVariant.insert(WMS_CLASSURI, pCdmClass->GetUriInternal());
    }

    const CdmObjectContainer* pList = (const_cast<CdmObject*>(this))->GetObjectContainer();

    if (CHKPTR(pList))
    {
        qmVariant.insert(WMS_CONTAINERURI, pList->GetUriInternal());
    }

    const CdmObject* pObject = (const_cast<CdmObject*>(this))->GetParent();

    if (pObject)
    {
        qmVariant.insert(WMS_PARENTURI, pObject->GetUriInternal());
    }

    QVariantMap qmMembers;

    QMap<QString, CdmValue*>::const_iterator qmIt = m_qmValues.begin();
    QMap<QString, CdmValue*>::const_iterator qmItEnd = m_qmValues.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue* pCdmValue = qmIt.value();

        if (CHKPTR(pCdmValue))
        {
            if (pCdmValue->GetValueType() == eDmValueContainerRef &&
                    pCdmValue->GetMember()->IsOwner())
            {
                dynamic_cast<CdmValueContainerRef*>(pCdmValue)->GetContainer();
            }
            else if (pCdmValue->GetValueType() == eDmValueObjectRef &&
                     pCdmValue->GetMember()->IsOwner())
            {
                dynamic_cast<CdmValueObjectRef*>(pCdmValue)->GetObject();
            }

            qmMembers.insert(qmIt.key(), pCdmValue->GetVariant());
        }
    }

    qmVariant.insert(WMS_VALUES, qmMembers);
    return qmVariant;
}

QString CdmObject::GetDisplayString(QString p_qstrKeyname) const
{
    QString qstrRet;
    if (!p_qstrKeyname.contains("&&"))
    {
        CdmValue* pCdmValue = (const_cast<CdmObject*>(this))->GetValue(p_qstrKeyname);

        if (pCdmValue)
        {
            qstrRet = pCdmValue->GetDisplayString();

            if (qstrRet.isEmpty())
            {
               qstrRet = GetKeyname();
            }
        }
        else
        {
            WARNING("Value \"" + p_qstrKeyname + "\" does not exists.");
        }
    }
    else
    {
        qstrRet = BuildComplexDisplayString(p_qstrKeyname);
    }

    return qstrRet;
}

QString CdmObject::BuildComplexDisplayString(QString p_qstrComplexDisplayString) const
{
    QString qstrDisplayValue;
    bool bLast = false;
    QString qstrValueKeyname = p_qstrComplexDisplayString;
    int iPos = p_qstrComplexDisplayString.indexOf("&&");

    while (iPos > 0 || bLast)
    {
        QString qstrTemp = qstrValueKeyname.mid(0, iPos);
        qstrTemp = qstrTemp.trimmed();
        qstrValueKeyname = qstrValueKeyname.mid(iPos + 2, qstrValueKeyname.length() - iPos - 2);
        iPos = qstrValueKeyname.indexOf("&&");

        QString qstrDisplayString = GetDisplayString(qstrTemp);

        if(!qstrDisplayString.isEmpty())
        {
            qstrDisplayValue += qstrDisplayString;

            if (!bLast)
            {
                qstrDisplayValue += ", ";
            }
        }

        if (!bLast)
        {
            if (iPos == -1)
            {
                bLast = true;
            }
        }
        else
        {
            bLast = false;
        }
    }

    qstrDisplayValue = qstrDisplayValue.trimmed();

    if (qstrDisplayValue.right(1) == ",")
    {
        qstrDisplayValue = qstrDisplayValue.left(qstrDisplayValue.length() - 1);
    }

    return qstrDisplayValue;
}

void CdmObject::ObjectRefModifiedSlot(CdmObject* p_pCdmObject, CdmValue* p_pCdmValue)
{
    if (CHKPTR(p_pCdmObject) && CHKPTR(p_pCdmValue))
    {
        QString qstrKeyname = p_pCdmValue->GetKeyname();

        if (!qstrKeyname.isEmpty())
        {
            emit ObjectRefModifiedSignal(p_pCdmObject);
        }
        else
        {
            FATAL("Invalid Valuekeyname. Keyname is empty.");
        }
    }
}

void CdmObject::SetParentObject(CdmObject* p_pCdmObject)
{
    if (p_pCdmObject)
    {
        SetParent(p_pCdmObject->GetId());
    }
    else
    {
        SetParent(0);
    }
}

void CdmObject::SetParent(qint64 p_lObjectId)
{
    if( m_lParentId != p_lObjectId)
    {
        m_lParentId = p_lObjectId;
        SetModified();
    }
}

bool CdmObject::HasParent() const
{
    bool bRet = false;

    if (m_lParentId > 0)
    {
        bRet = true;
    }

    return bRet;
}

CdmObject* CdmObject::GetParent()
{
    CdmObject* pCdmObject = nullptr;
    CdmObjectContainer* pContainer = GetObjectContainer();

    if (CHKPTR(pContainer) && m_lParentId > 0)
    {
        pCdmObject = pContainer->FindObjectById(m_lParentId);

        if (!pCdmObject)
        {
            SetParent(0);
        }
    }

    return pCdmObject;
}

qint64 CdmObject::GetParentId() const
{
    return m_lParentId;
}

void CdmObject::GetChanges(QList<CdmJournalItem*>& p_rqllChanges)
{
    QDate qdTo = QDate::currentDate();
    QDate qdFrom = QDate(2012,1,1);
    GetChanges(qdFrom, qdTo, p_rqllChanges);
}

void CdmObject::GetChanges(QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqllChanges)
{

    IdmDataAccess* pCdmAccess = GetDataAccess();

    if (CHKPTR(pCdmAccess))
    {
        pCdmAccess->GetObjectModifications(this,
                                           p_qdFrom,
                                           p_qdTo,
                                           p_rqllChanges);
    }
}

CdmObject* CdmObject::GetOwner()
{
    CdmObject* pCdmObject = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        IdmDataAccess* pDataAccess = pManager->GetDataAccess();

        if (CHKPTR(pDataAccess))
        {
            pDataAccess->GetOwner(this,
                                  pCdmObject);
        }
    }

    if (pCdmObject == nullptr)
    {
        auto pContainer = GetObjectContainer();

        if (CHKPTR(pContainer))
        {
            pCdmObject = pContainer->GetOwner();
        }
    }

    return pCdmObject;
}

bool CdmObject::HasOwner() const
{
    bool bRet = false;

    if ((const_cast<CdmObject*>(this))->GetOwner())
    {
        bRet = true;
    }

    return bRet;
}

QList<CdmObject*> CdmObject::GetReferences()
{
    QList<CdmObject*> qlReferences;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        IdmDataAccess* pDataAccess = pManager->GetDataAccess();

        if (CHKPTR(pDataAccess))
        {
            pDataAccess->GetReferences(this, qlReferences);
        }
    }

    return qlReferences;
}

bool CdmObject::IsObject() const
{
    return true;
}

QString CdmObject::GetUri() const
{
    QString qstrUri;
    const CdmObjectContainer* pList = (const_cast<CdmObject*>(this))->GetObjectContainer();

    if (CHKPTR(pList))
    {
        qstrUri = CreateUri(WMS_URI_OBJECT, pList->GetKeyname(), GetKeyname());
    }
    else
    {
        qstrUri = CreateUri(WMS_URI_OBJECT, "Unkonwn_List", GetKeyname());
    }

    return qstrUri;
}

QString CdmObject::GetUriInternal() const
{
    QString qstrUri;
    const CdmObjectContainer* pList = (const_cast<CdmObject*>(this))->GetObjectContainer();

    if (CHKPTR(pList))
    {
        qstrUri = CreateUriPath(WMS_URI_OBJECT, pList->GetKeyname(), GetKeyname(), "");
    }
    else
    {
        qstrUri = CreateUriPath(WMS_URI_OBJECT, "Unkonwn_List", GetKeyname(), "");
    }

    return qstrUri;
}

QString CdmObject::GetConfig() const
{
    QVariantMap qvMap;
    qvMap.insert("Immutable", IsImmutable());

    CwmsJson json;
    return json.serialize(qvMap);
}

void CdmObject::SetConfig(QString p_qstrConfig)
{
    if (!p_qstrConfig.isEmpty())
    {
        CwmsJson json;
        QVariantMap qvMap = json.parse(p_qstrConfig).toMap();
        SetImmutable(qvMap["Immutable"].toBool());
    }
}

bool CdmObject::IsImmutable() const
{
    return m_bIsImmutable;
}

void CdmObject::SetImmutable(bool p_bImmutable)
{
    m_bIsImmutable = p_bImmutable;
    SetModified();
}

void CdmObject::RestoreValue(int p_iMemberId, QString p_qstrValueAsString)
{
    // todo
    auto pValue = GetValue(p_iMemberId);

    if (pValue)
    {
        pValue->Restore(p_qstrValueAsString);
        Commit();
        INFO("Restore successfully finished");
    }
    else
    {
        ERR("Value which should be restored not found");
    }
}

bool CdmObject::IsReadOnly() const
{
    bool bRet = false;

    if (!IsNew())
    {
        if (IsImmutable())
        {
            bRet = true;
        }
        else
        {
            CdmObjectContainer* pContainer = GetObjectContainer();

            if (CHKPTR(pContainer))
            {
                if (pContainer->IsImmutable())
                {
                    bRet = true;
                }
                else
                {
                    CdmClass* pClass = GetClass();

                    if (CHKPTR(pClass))
                    {
                        bRet = pClass->IsImmutable();
                    }
                }
            }
        }
    }

    return bRet;
}

CdmValue* CdmObject::GetEventValue(const QString& p_rqstrKeyname, CdmObject* p_pEventObject)
{
    CdmValue* pEventValue = nullptr;

    if (p_pEventObject->m_qmValues.contains(p_rqstrKeyname))
    {
        pEventValue = p_pEventObject->m_qmValues[p_rqstrKeyname];
    }

    if (!pEventValue)
    {
        ERR("Value could not be found in EventObject!")
    }

    return pEventValue;
}

void CdmObject::CopyValuesFromObjectToEventObject(CdmObject* p_pEventObject)
{
    if (CHKPTR(p_pEventObject))
    {
        int iEventObjectMembers = p_pEventObject->m_qmValues.count();
        int iObjectMembers = m_qmValues.count();

        if (iEventObjectMembers > iObjectMembers)
        {
            CopyObjectValueToEventValueWithEventObjectStarting(p_pEventObject);
        }
        else if (iEventObjectMembers == iObjectMembers)
        {
            CopyObjectValueToEventValueWithObjectStarting(p_pEventObject);
        }
        else
        {
            CopyObjectValuesToEventObjectValues(p_pEventObject);
        }
    }
}

void CdmObject::CopyObjectValueToEventValueWithEventObjectStarting(CdmObject *pEventObject)
{
    const CdmObject *pCdmEventObject = const_cast<CdmObject*>(pEventObject);
    QList<CdmValue*> qlObjectValues = m_qmValues.values();
    int iIndexCount = 0;
    QMap<QString, CdmValue*>::const_iterator qm_It = pEventObject->m_qmValues.constBegin();
    QMap<QString, CdmValue*>::const_iterator qm_ItEnd = pEventObject->m_qmValues.constEnd();

    for(;qm_It != qm_ItEnd; ++qm_It)
    {
        CdmValue *pEventObjectValue = qm_It.value();
        if(pEventObjectValue)
        {
            CdmValue *pObjectValue = nullptr;
            CdmValue *pNewEventObjectValue = nullptr;

            if(iIndexCount < qlObjectValues.count())
            {
                pObjectValue = qlObjectValues.at(iIndexCount);

                if(pObjectValue)
                {
                    if(pEventObjectValue->GetKeyname() == pObjectValue->GetKeyname())
                    {
                        pNewEventObjectValue = pObjectValue->CopyObjectValueToEventValue(pEventObjectValue, pCdmEventObject, this, pObjectValue);

                        if(pNewEventObjectValue)
                        {
                            QString qstrKeyname = pNewEventObjectValue->GetEventValueKeyname(pEventObjectValue);

                            if(pEventObject->m_qmValues.contains(qstrKeyname))
                            {
                                pEventObject->m_qmValues.remove(qstrKeyname);
                                pEventObject->m_qmValues.insert(qstrKeyname, pNewEventObjectValue);
                            }
                            else
                            {
                                pEventObject->m_qmValues.insert(qstrKeyname, pNewEventObjectValue);
                            }                             connect(pNewEventObjectValue,
                                                                  SIGNAL(ValueChanged(CdmValue*)),
                                                                  this,
                                                                  SLOT(ValueChangedSlot(CdmValue*)));
                        }
                        else
                        {
                            QString qstrMessage = "Could not copy value " + pObjectValue->GetKeyname();
                            ERR(qstrMessage);
                        }
                    }
                }
            }
        }

        ++iIndexCount;
    }
}

void CdmObject::CopyObjectValueToEventValueWithObjectStarting(CdmObject *pEventObject)
{
    const CdmObject *pCdmEventObject = const_cast<CdmObject*>(pEventObject);
    QMap<QString, CdmValue*>::const_iterator qmIt = m_qmValues.constBegin();
    QMap<QString, CdmValue*>::const_iterator qmItEnd = m_qmValues.constEnd();
    QList<CdmValue*> qlEventObjectValues = pEventObject->m_qmValues.values();
    int iIndexCount = 0;

    for(; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue *pEventObjectValue  = nullptr;
        CdmValue *pNewEventObjectValue = nullptr;
        CdmValue *pObjectValue = (*qmIt);

        if(CHKPTR(pObjectValue))
        {
            if(iIndexCount < qlEventObjectValues.count())
            {
                pEventObjectValue = qlEventObjectValues.at(iIndexCount);
            }

            if(CHKPTR(pEventObjectValue))
            {
                if(pObjectValue->GetKeyname() == pEventObjectValue->GetKeyname())
                {
                    pNewEventObjectValue = pObjectValue->CopyObjectValueToEventValue(pEventObjectValue, pCdmEventObject, this, pObjectValue);

                    if(CHKPTR(pNewEventObjectValue))
                    {
                        QString qstrKeyname = pNewEventObjectValue->GetEventValueKeyname(pEventObjectValue);

                        if(pEventObject->m_qmValues.contains(qstrKeyname))
                        {
                            pEventObject->m_qmValues.remove(qstrKeyname);
                            pEventObject->m_qmValues.insert(qstrKeyname, pNewEventObjectValue);
                        }
                        else
                        {
                            pEventObject->m_qmValues.insert(qstrKeyname, pNewEventObjectValue);
                        }

                        connect(pNewEventObjectValue,
                                SIGNAL(ValueChanged(CdmValue*)),
                                this,
                                SLOT(ValueChangedSlot(CdmValue*)));
                    }
                    else
                    {
                        QString qstrMessage = "Could not copy value " + pObjectValue->GetKeyname();
                        ERR(qstrMessage);
                    }
                }
            }
        }

        ++iIndexCount;
    }
}

void CdmObject::CopyObjectValuesToEventObjectValues(CdmObject* p_pEventObject)
{
    if (!CHKPTR(p_pEventObject))
    {
        return; // emergency exit
    }

    const CdmObject* pCdmEventObject = const_cast<CdmObject*>(p_pEventObject);
    QMap<QString, CdmValue*>::const_iterator qmIt    = m_qmValues.constBegin();
    QMap<QString, CdmValue*>::const_iterator qmItEnd = m_qmValues.constEnd();
    QList<CdmValue*> qlEventObjectValues = p_pEventObject->m_qmValues.values();
    int iEventValues = qlEventObjectValues.count();

    for( ; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue* pObjectValue = *qmIt;

        if (CHKPTR(pObjectValue))
        {
            CdmValue* pNewEventObjectValue = nullptr;
            int iIndexCount = 0;

            while (iIndexCount < iEventValues)
            {
                CdmValue* pEventObjectValue = qlEventObjectValues.at(iIndexCount);

                if (CHKPTR(pEventObjectValue))
                {
                    if (pEventObjectValue->GetKeyname() == pObjectValue->GetKeyname())
                    {
                        pNewEventObjectValue =
                                pObjectValue->CopyObjectValueToEventValue(pEventObjectValue, pCdmEventObject, this, pObjectValue);

                        if (CHKPTR(pNewEventObjectValue))
                        {
                            QString qstrKeyname = pNewEventObjectValue->GetEventValueKeyname(pEventObjectValue);

                            if (p_pEventObject->m_qmValues.contains(qstrKeyname))
                            {
                                p_pEventObject->m_qmValues.remove(qstrKeyname);
                                p_pEventObject->m_qmValues.insert(qstrKeyname, pNewEventObjectValue);
                            }
                            else
                            {
                                p_pEventObject->m_qmValues.insert(qstrKeyname, pNewEventObjectValue);
                            }

                            connect(pNewEventObjectValue, SIGNAL(ValueChanged(    CdmValue*)),
                                    this,                 SLOT(  ValueChangedSlot(CdmValue*)));
                        }
                        else
                        {
                            ERR(QString("Could not copy value ") + pObjectValue->GetKeyname())
                        }
                    }
                }

                ++iIndexCount;
            }
        }
    }
}
