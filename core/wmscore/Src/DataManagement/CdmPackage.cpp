// System and Qt Includes
#include <QVariant>
#include <QDebug>

// Own Includes
#include "CdmLogging.h"
#include "wmsdefines.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmPackage.h"

CdmPackage::CdmPackage(qint64 p_lSchemeId, QString p_qstrKeyname)
: CdmModelElement(p_lSchemeId, -1, p_qstrKeyname, ""),
  m_bSystemPackage(false),
  m_rParent(nullptr)
{
}

CdmPackage::CdmPackage(QVariant p_qvVariant)
: CdmModelElement(p_qvVariant),
  m_bSystemPackage(false),
  m_rParent(nullptr)
{
    QVariantMap qvMap = p_qvVariant.toMap();
    Deploy(qvMap);
}

CdmPackage::~CdmPackage()
{

}

bool CdmPackage::IsPackage() const
{
    return true;
}

void CdmPackage::Deploy(QVariantMap &p_rqvHash)
{
    CdmModelElement::SetKeyname(p_rqvHash[WMS_KEYNAME].toString());
    SetSystemPackage(p_rqvHash[WMS_SYSTEMPACKAGE].toBool());
    QVariantList qvlChildren = p_rqvHash[WMS_CHILDREN].toList();

    for (int iPos = 0; iPos < qvlChildren.count(); ++iPos)
    {
        QVariantMap qvmChild = qvlChildren[iPos].toMap();
        QString qstrName = qvmChild[WMS_KEYNAME].toString();

        CdmPackage* pPackage = FindChild(qstrName);

        if (pPackage)
        {
            pPackage->Deploy(qvmChild);
        }
        else
        {
            pPackage = new CdmPackage(qvmChild);
            pPackage->SetNew();
            pPackage->SetParent(this);
            AddChild(pPackage);
        }

        pPackage->Commit();
    }
}

QVariant CdmPackage::GetVariant()
{
    QVariantMap qvMap;

    qvMap[WMS_KEYNAME] = GetKeyname();
    qvMap[WMS_SYSTEMPACKAGE] = IsSystemPackage();
    QVariantList qvlChildren;

    for (int iPos = 0; iPos < m_qlChildren.count(); ++iPos)
    {
        CdmPackage* pPackage = m_qlChildren[iPos];

        if (CHKPTR(pPackage))
        {
            qvlChildren.append(pPackage->GetVariant());
        }
    }

    qvMap[WMS_CHILDREN] = qvlChildren;
    return qvMap;
}

CdmPackage* CdmPackage::FindChild(QString p_qstrName)
{
    CdmPackage* pPackage = nullptr;
    QString qstrPackageKeynameFirstArea;
    int iIndex = p_qstrName.indexOf(".");

    if (iIndex > 0)
    {
        qstrPackageKeynameFirstArea = p_qstrName.left(iIndex);
    }
    else
    {
        qstrPackageKeynameFirstArea = p_qstrName;
    }

    for (int iPos = 0; iPos < m_qlChildren.count(); ++iPos)
    {
        CdmPackage* pPackageTemp = m_qlChildren[iPos];

        if (CHKPTR(pPackageTemp))
        {
            if (pPackageTemp->GetKeyname() == qstrPackageKeynameFirstArea)
            {
                if (iIndex > 0)
                {
                    pPackage = pPackageTemp->FindChild(p_qstrName.mid(iIndex + 1));
                }
                else
                {
                    pPackage = pPackageTemp;
                }

                break;
            }
        }
    }

    return pPackage;
}

CdmPackage* CdmPackage::FindChildByUri(QString p_qstrName)
{
    CdmPackage* pPackage = nullptr;

    for (int iPos = 0; iPos < m_qlChildren.count(); ++iPos)
    {
        CdmPackage* pPackageTemp = m_qlChildren[iPos];

        if (CHKPTR(pPackageTemp))
        {
            if (pPackageTemp->GetUriInternal() == p_qstrName)
            {
                pPackage = pPackageTemp;
                break;
            }
            else
            {
                pPackage = pPackageTemp->FindChildByUri(p_qstrName);
                if (pPackage)
                {
                    break;
                }
            }
        }
    }

    return pPackage;
}

void CdmPackage::GetChildren(QList<CdmPackage*>& p_rqlChildren) {
    p_rqlChildren = m_qlChildren;
}

int CdmPackage::Commit()
{
    SetModifierId(GetUserId());
    int iRet = CdmLogging::eDmUnknownClassError;
	CdmClassManager* pClassManager = GetClassManager();
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
       CdmPackage* pPackage = this;

       iRet = pIdmDataAccess->UpdatePackage(pPackage);

       if(iRet > 0)
       {
          if (CHKPTR(pClassManager))
          {
              pClassManager->UpdateModifiedClasses();
          }
       }
    }

    return iRet;
}

void CdmPackage::AddChild(CdmPackage* p_pPackage)
{
    m_qlChildren.append(p_pPackage);
    SetModified();
}

void CdmPackage::DeleteChild(CdmPackage* p_pPackage)
{
	m_qlChildren.removeAll(p_pPackage);
    p_pPackage->SetDeleted();
    SetModified();
}

void CdmPackage::RemovePackageFromClasses(CdmPackage* p_pPackage)
{
    for (int iPos = 0; iPos < p_pPackage->m_qlClasses.count(); ++iPos)
    {
        CdmClass* pClass = p_pPackage->m_qlClasses[iPos];
        pClass->SetPackage(nullptr);
    }
}

void CdmPackage::DeleteChild(QString p_qstrName)
{
    for (int iPos = 0; iPos < m_qlChildren.count(); ++iPos)
    {
        CdmPackage* pPackage = m_qlChildren[iPos];

        if (CHKPTR(pPackage) && pPackage->GetKeyname() == p_qstrName)
        {
            DeleteChild(pPackage);
            break;
        }
    }
}

void CdmPackage::AddClass(QString p_qstrKeyname)
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmClassManager* pClassManager = pManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(p_qstrKeyname);

            if (CHKPTR(pClass))
            {
                AddClass(pClass);
            }
        }
    }
}

void CdmPackage::AddClass(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        if (!m_qlClasses.contains(p_pClass))
        {
            m_qlClasses.append(p_pClass);
        }
    }
}

void CdmPackage::RemoveClass(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        m_qlClasses.removeAll(p_pClass);
    }
}

void CdmPackage::RemoveClass(QString p_qstrKeyname)
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmClassManager* pClassManager = pManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(p_qstrKeyname);

            if (CHKPTR(pClass))
            {
                RemoveClass(pClass);
            }
        }
    }
}

void CdmPackage::SetParent(CdmPackage* p_pPackage)
{
    if (m_rParent != p_pPackage)
    {
        m_qstrOriginalPackageString = GetPackageString();
        m_rParent = p_pPackage;
        SetModified();
    }
}

const CdmPackage* CdmPackage::GetParent() const
{
    return m_rParent;
}

QString CdmPackage::GetPackageString() const
{
	QString qstrPackageString = CdmModelElement::GetKeyname();

    const CdmPackage* pParent = GetParent();

    while (pParent)
    {
        qstrPackageString = pParent->GetKeyname() + "." + qstrPackageString;
        pParent = pParent->GetParent();
    }
    //qDebug()<<qstrPackageString;
    return qstrPackageString;
}

bool CdmPackage::IsSystemPackage()
{
    return m_bSystemPackage;
}

void CdmPackage::SetSystemPackage(bool p_bSystemFlag)
{
    if (m_bSystemPackage != p_bSystemFlag)
    {
        SetModified();
        m_bSystemPackage = p_bSystemFlag;
    }
}

QString CdmPackage::GetKeyname() const
{
    return CdmModelElement::GetKeyname();
}

QString CdmPackage::GetOriginalPackgeString() const
{
    return m_qstrOriginalPackageString;
}

void CdmPackage::SetKeyname(QString p_qstrKeyname)
{
    Rename(p_qstrKeyname);
}

void CdmPackage::Rename(QString p_qstrKeyname)
{
    m_qstrOriginalPackageString = GetPackageString();
    CdmModelElement::SetKeyname(p_qstrKeyname);
    SetModified();
	Commit();

    for (int iPos = 0; iPos < m_qlClasses.count(); ++iPos)
    {
        CdmClass* pClass = m_qlClasses[iPos];
        pClass->SetModified(); // Package Name has changed
		pClass->Commit();
    }
}

QList<CdmClass*> CdmPackage::GetClassList()
{
    return m_qlClasses;
}

QString CdmPackage::GetUri() const
{
   QString qstrType = GetUriType();
   return CreateUri(qstrType, GetPackageString());
}

QString CdmPackage::GetUriInternal() const
{
    QString qstrType = GetUriType();
    return CreateUriPath(qstrType, GetPackageString(), "", "");
}



void CdmPackage::ResetNewModified()
{
  CdmModelElement::ResetNewModified();
  m_qstrOriginalPackageString = "";
}
