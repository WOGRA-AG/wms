/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmJournalItem.cpp
 ** Started Implementation: 2012/08/29
 ** Description:
 **
 ** implements the item of a change on a dataobject
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QVariantMap>

// own Includes
#include "CdmDataProvider.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmJournalItem.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

CdmJournalItem::CdmJournalItem()
: m_iUserId(0),
  m_iSessionId(0),
  m_eChangeMode(eDmChangeModeModified),
  m_iObjectId(0),
  m_iContainerId(0),
  m_iMemberId(0)
{
}

CdmJournalItem::CdmJournalItem(QVariantMap& p_rqvHash)
{
   m_iUserId = p_rqvHash["UserId"].toInt();
   m_iMemberId = p_rqvHash["MemberId"].toInt();
   m_iSessionId = p_rqvHash["SessionId"].toInt();
   m_qdtModified = p_rqvHash["Modified"].toDateTime();
   m_eChangeMode = (EdmChangeMode)p_rqvHash["ChangeMode"].toInt();
   m_iObjectId = p_rqvHash["ObjectId"].toInt();
   m_iContainerId = p_rqvHash["ObjectListId"].toInt();
   m_qstrChanges = p_rqvHash["Changes"].toString();
   m_qstrDisplayString = p_rqvHash["DisplayString"].toString();
}

QVariantMap CdmJournalItem::GetVariant() const
{
   QVariantMap qvHash;

   qvHash["UserId"] = m_iUserId;
   qvHash["MemberId"] = m_iMemberId;
   qvHash["SessionId"] = m_iSessionId;
   qvHash["Modified"] = m_qdtModified;
   qvHash["ChangeMode"] = m_eChangeMode;
   qvHash["ObjectId"] = m_iObjectId;
   qvHash["ObjectListId"] = m_iContainerId;
   qvHash["Changes"] = m_qstrChanges;
   qvHash["DisplayString"] = m_qstrDisplayString;

   return qvHash;
}

void CdmJournalItem::SetUserId(int p_iUserId)
{
   m_iUserId = p_iUserId;
}

int CdmJournalItem::GetUserId() const
{
   return m_iUserId;
}

void CdmJournalItem::SetSessionId(int p_iSessionId)
{
   m_iSessionId = p_iSessionId;
}

int CdmJournalItem::GetSessionId() const
{
   return m_iSessionId;
}

void CdmJournalItem::SetModified(QDateTime p_qdModified)
{
   m_qdtModified = p_qdModified;
}

QDateTime CdmJournalItem::GetModified() const
{
   return m_qdtModified;
}

void CdmJournalItem::SetChangeMode(EdmChangeMode p_eMode)
{
   m_eChangeMode = p_eMode;
}

EdmChangeMode CdmJournalItem::GetChangeMode() const
{
   return m_eChangeMode;
}

QString CdmJournalItem::GetChangeModeAsString() const
{
   QString qstrRet;

   switch (m_eChangeMode)
   {
   case eDmChangeModeNew:
      qstrRet = tr("Neu");
      break;
   case eDmChangeModeModified:
      qstrRet = QStringLiteral("Änderung");
      break;
   case eDmChangeModeDeleted:
      qstrRet = tr("Löschung");
      break;
   default:
      qstrRet = tr("Unbekannt");
   }

   return qstrRet;
}

void CdmJournalItem::SetObjectId(int p_iId)
{
   m_iObjectId = p_iId;
}

int CdmJournalItem::GetObjectId() const
{
   return m_iObjectId;
}

void CdmJournalItem::SetObjectListId(int p_iId)
{
   m_iContainerId = p_iId;
}

int CdmJournalItem::GetObjectListId() const
{
   return m_iContainerId;
}

void CdmJournalItem::SetMemberId(int p_iId)
{
   m_iMemberId = p_iId;
}

int CdmJournalItem::GetMemberId() const
{
   return m_iMemberId;
}

void CdmJournalItem::SetChanges(QString p_qstrChanges)
{
   m_qstrChanges = p_qstrChanges;
}

QString CdmJournalItem::GetChanges() const
{
   return m_qstrChanges;
}

void CdmJournalItem::SetDisplayString(QString p_qstrValue)
{
   m_qstrDisplayString = p_qstrValue;
}

QString CdmJournalItem::GetDisplayString() const
{
   return m_qstrDisplayString;
}

QString CdmJournalItem::GetUserString() const
{
   QString qstrRet;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      CumUser* pCumUser = pCumUserManager->FindUserById(m_iUserId);

      if (pCumUser)
      {
         qstrRet = pCumUser->GetFirstName() + " " + pCumUser->GetLastName() + " (" + QString::number(m_iUserId) + ")";
      }
      else
      {
         qstrRet = tr("Unbekannt");
      }
   }

   return qstrRet;
}

QString CdmJournalItem::GetMemberAsString(CdmObject* p_pCdmObject) const
{
   QString qstrRet;

   if (CHKPTR(p_pCdmObject))
   {
      CdmClass* pCdmClass = p_pCdmObject->GetClass();

      if (CHKPTR(pCdmClass))
      {
         const CdmMember* pCdmMember = pCdmClass->FindMember(m_iMemberId);

         if (pCdmMember)
         {
            qstrRet = pCdmMember->GetCaption() + " (" + pCdmMember->GetKeyname() + ")";
         }
         else
         {
            qstrRet = QString::number(m_iMemberId);
         }
      }
   }

   return qstrRet;
}

void CdmJournalItem::RestoreValue()
{
    if (m_iContainerId > 0 && m_iObjectId > 0 && m_iMemberId > 0)
    {
        CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pDataProvider))
        {
            auto pContainerManager = pDataProvider->GetContainerManager();

            if (CHKPTR(pContainerManager))
            {
                auto pContainer = pContainerManager->FindContainerById(m_iContainerId);

                if (pContainer)
                {
                    auto pObject = pContainer->FindObjectById(m_iObjectId);

                    if (pObject)
                    {
                        pObject->RestoreValue(m_iMemberId, m_qstrChanges);
                    }
                    else
                    {
                        ERR("Object on which the values has to be restored not found")
                    }
                }
                else
                {
                    ERR("Container of the object not found")
                }
            }
        }
    }
    else
    {
        ERR("This is not a value which can be restored");
    }

}
