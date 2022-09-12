/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmMemberRights.cpp
 ** Started Implementation: 2012/06/18
 ** Description:
 **
 ** Implements the rights configuration for members
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// own Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CumUser.h"
#include "CdmRights.h"

CdmRights::CdmRights()
    : CdmLocatedElement(),
      m_rpElement(nullptr)
{
}


CdmRights::CdmRights(CdmModelElement* p_pElement)
    : CdmLocatedElement(),
      m_rpElement(p_pElement)
{
}

CdmRights::CdmRights(CdmModelElement* p_pElement, QVariantMap& p_rqvHash)
    : CdmLocatedElement(),
      m_rpElement(p_pElement)
{
   SetVariant(p_rqvHash);
}

CdmRights::CdmRights(const CdmRights&)
    :CdmLocatedElement()
{
   // does nothing
}

CdmRights::~CdmRights()
{
}

void CdmRights::SetVariant(QVariantMap& p_rqvHash)
{
   QVariantMap::iterator qvhIt = p_rqvHash.begin();
   QVariantMap::iterator qvhItEnd = p_rqvHash.end();

   m_qmRights.clear();

   for (; qvhIt != qvhItEnd; ++qvhIt)
   {
      QString qstrUri = qvhIt.key();
      CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pManager))
      {
          CdmLocatedElement* pElement = pManager->GetUriObject(qstrUri);

          if (pElement)
          {
              EdmRight eDmRight = (EdmRight)qvhIt.value().toInt();

              if (pElement->IsUser())
              {
                m_qmRights.insert(((CumUser*)pElement)->GetId(), eDmRight);
              }
              else if (pElement->IsUserGroup())
              {
                  m_qmRights.insert(((CumUserGroup*)pElement)->GetId(), eDmRight);
              }
          }
      }
   }
}

void CdmRights::AddRight(int p_iUserBaseId, EdmRight p_eRight)
{
    if (!m_qmRights.contains(p_iUserBaseId) || m_qmRights[p_iUserBaseId] != p_eRight)
    {
        m_qmRights.insert(p_iUserBaseId, p_eRight);

        if (m_rpElement)
        {
            m_rpElement->SetModified();
        }
    }
}

void CdmRights::AddRight(CumAccessor* p_pAccessor, EdmRight p_eRight)
{
    if (CHKPTR(p_pAccessor))
    {
        AddRight(p_pAccessor->GetId(), p_eRight);
    }
}

void CdmRights::DeleteRight(int p_iUserBaseId)
{
    if (m_qmRights.contains(p_iUserBaseId))
    {
        m_qmRights.remove(p_iUserBaseId);

        if (m_rpElement)
        {
            m_rpElement->SetModified();
        }
    }
}

bool CdmRights::HasRightConfigured(CumAccessor* p_pCumAccessor) const
{
   bool bRet = false;

   if (CHKPTR(p_pCumAccessor))
   {
      bRet = HasRightConfigured(p_pCumAccessor->GetId());
   }

   return bRet;
}

bool CdmRights::HasRightConfigured(int p_lUserBaseId) const
{
   bool bRet = false;

   if (m_qmRights.contains(p_lUserBaseId))
   {
      if (m_qmRights[p_lUserBaseId] != eDmRightNone)
      {
         bRet = true;
      }
   }
  
   return bRet;
}

bool CdmRights::HasRight(CumAccessor* p_pCumAccessor) const
{
   bool bRet = false;

   if (CHKPTR(p_pCumAccessor))
   {
      bRet = HasRight(p_pCumAccessor->GetId());
   }

   return bRet;
}

bool CdmRights::HasRight(int p_lUserBaseId) const
{
   return HasReadAccess(p_lUserBaseId) || HasWriteAccess(p_lUserBaseId);
}

bool CdmRights::HasReadAccess(int p_iUserBaseId) const
{
   bool bRet = false;

   if (m_qmRights.isEmpty())
   {
      bRet = true;
   }
   else
   {
      if (m_qmRights.contains(p_iUserBaseId))
      {
         if (m_qmRights[p_iUserBaseId] != eDmRightNone)
         {
            bRet = true;
         }
      }
   }

   return bRet;
}

bool CdmRights::HasWriteAccess(int p_iUserBaseId) const
{
   bool bRet = false;

   if (m_qmRights.isEmpty())
   {
      bRet = true;
   }
   else
   {
      if (m_qmRights.contains(p_iUserBaseId))
      {
         if (m_qmRights[p_iUserBaseId] == eDmRightWrite)
         {
            bRet = true;
         }
      }
   }

   return bRet;
}

bool CdmRights::HasCurrentUserWriteAccess() const
{
   bool bRet = false;

   if (m_qmRights.isEmpty())
   {
      bRet = true;
   }
   else
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         const CumUser* pCumUser = pCdmManager->GetUser();

         if (CHKPTR(pCumUser))
         {
            if (pCumUser->IsAdministrator())
            {
               bRet = true;
            }
            else
            {
               EdmRight eDmRight = FindRight(pCumUser);

               if (eDmRight == eDmRightWrite)
               {
                  bRet = true;
               }
            }
         }
      }
   }

   return bRet;
}

bool CdmRights::HasCurrentUserReadAccess() const
{
   bool bRet = false;

   if (m_qmRights.isEmpty())
   {
      bRet = true;
   }
   else
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         const CumUser* pCumUser = pCdmManager->GetUser();

         if (CHKPTR(pCumUser))
         {
            if (pCumUser->IsAdministrator())
            {
               bRet = true;
            }
            else
            {
               bRet = HasUserExplicitReadAccess(pCumUser);
            }
         }
      }
   }

   return bRet;
}

bool CdmRights::HasCurrentUserExplicitReadAccess() const
{
    bool bRet = false;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
       const CumUser* pCumUser = pCdmManager->GetUser();

       if (CHKPTR(pCumUser))
       {
         bRet = HasUserExplicitReadAccess(pCumUser);
       }
    }

    return bRet;
}

bool CdmRights::HasUserExplicitReadAccess(const CumUser* pUser) const
{
    bool bRet = false;

       if (CHKPTR(pUser))
       {
         EdmRight eDmRight = FindRight(pUser);

         if (eDmRight != eDmRightNone)
         {
            bRet = true;
         }
    }

    return bRet;
}

EdmRight CdmRights::FindRight(const CumUser* p_pCumUser) const
{
   EdmRight eDmRight = eDmRightNone;

   if(m_qmRights.contains(p_pCumUser->GetId()))
   {
      eDmRight = m_qmRights[p_pCumUser->GetId()];
   }
   else // the user could be member in a usergroup
   {
      QList<CumUserGroup*> qvlUserGroupIds;
      (const_cast<CumUser*>(p_pCumUser))->GetUserGroups(qvlUserGroupIds);

      QList<CumUserGroup*>::iterator qvlIt    = qvlUserGroupIds.begin();
      QList<CumUserGroup*>::iterator qvlItEnd = qvlUserGroupIds.end();

      for(; qvlIt != qvlItEnd; ++qvlIt)
      {
         CumUserGroup* pCumUserGroup = (*qvlIt);
         if(pCumUserGroup)
         {
            if(m_qmRights.contains(pCumUserGroup->GetId()))
            {
               eDmRight = m_qmRights[pCumUserGroup->GetId()];
               break;
            }
         }
      }
   }

   return eDmRight;
}



QVariant CdmRights::GetVariant() const
{
   QVariantMap qvRights;

   QMap<int, EdmRight>::const_iterator qmIt = m_qmRights.begin();
   QMap<int, EdmRight>::const_iterator qmItEnd = m_qmRights.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
     qint64 lId = qmIt.key();
      EdmRight eDmRight = qmIt.value();
      QString qstrUri = GetUserUri(lId);
      qvRights.insert(qstrUri, QString::number(eDmRight));
   }

   return qvRights;
}

QMap<int, EdmRight> CdmRights::GetRights() const
{
   return m_qmRights;
}

QString CdmRights::GetUserUri(qint64 p_iUserId) const
{
    QString qstrUri;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CumUserManager* pUserManager = pManager->GetUserManager();

        if (CHKPTR(pUserManager))
        {
            CumUser* pUser = pUserManager->FindUserById(p_iUserId);

            if (pUser)
            {
                qstrUri = pUser->GetUri();
            }
            else
            {
                CumUserGroup* pUserGroup = pUserManager->FindUserGroupById(p_iUserId);

                if (pUserGroup)
                {
                    qstrUri = pUserGroup->GetUri();
                }
            }
        }
    }

    return qstrUri;
}

