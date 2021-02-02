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

/** +-=---------------------------------------------------------Mi 29. Aug 11:03:28 2012----------*
 * @method  CdmJournalItem::CdmJournalItem                   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:03:28 2012----------*/
CdmJournalItem::CdmJournalItem()
: m_iUserId(0),
  m_iSessionId(0),
  m_eChangeMode(eDmChangeModeModified),
  m_iObjectId(0),
  m_iObjectListId(0),
  m_iMemberId(0)
{
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:03:44 2012----------*
 * @method  CdmJournalItem::CdmJournalItem                   // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:03:44 2012----------*/
CdmJournalItem::CdmJournalItem(QVariantMap& p_rqvHash)
{
   m_iUserId = p_rqvHash["UserId"].toInt();
   m_iMemberId = p_rqvHash["MemberId"].toInt();
   m_iSessionId = p_rqvHash["SessionId"].toInt();
   m_qdtModified = p_rqvHash["Modified"].toDateTime();
   m_eChangeMode = (EdmChangeMode)p_rqvHash["ChangeMode"].toInt();
   m_iObjectId = p_rqvHash["ObjectId"].toInt();
   m_iObjectListId = p_rqvHash["ObjectListId"].toInt();
   m_qstrChanges = p_rqvHash["Changes"].toString();
   m_qstrDisplayString = p_rqvHash["DisplayString"].toString();
}


/** +-=---------------------------------------------------------So 10. Feb 09:14:29 2013----------*
 * @method  CdmJournalItem::GetVariant                       // public, const                     *
 * @return  QVariantMap                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:14:29 2013----------*/
QVariantMap CdmJournalItem::GetVariant() const
{
   QVariantMap qvHash;

   qvHash["UserId"] = m_iUserId;
   qvHash["MemberId"] = m_iMemberId;
   qvHash["SessionId"] = m_iSessionId;
   qvHash["Modified"] = m_qdtModified;
   qvHash["ChangeMode"] = m_eChangeMode;
   qvHash["ObjectId"] = m_iObjectId;
   qvHash["ObjectListId"] = m_iObjectListId;
   qvHash["Changes"] = m_qstrChanges;
   qvHash["DisplayString"] = m_qstrDisplayString;

   return qvHash;
}



/** +-=---------------------------------------------------------Mi 29. Aug 11:05:31 2012----------*
 * @method  CdmJournalItem::SetUserId                        // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iUserId                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:05:31 2012----------*/
void CdmJournalItem::SetUserId(int p_iUserId)
{
   m_iUserId = p_iUserId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:14:39 2013----------*
 * @method  CdmJournalItem::GetUserId                        // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:14:39 2013----------*/
int CdmJournalItem::GetUserId() const
{
   return m_iUserId;
}



/** +-=---------------------------------------------------------Mi 29. Aug 11:06:36 2012----------*
 * @method  CdmJournalItem::SetSessionId                     // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iSessionId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:06:36 2012----------*/
void CdmJournalItem::SetSessionId(int p_iSessionId)
{
   m_iSessionId = p_iSessionId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:14:48 2013----------*
 * @method  CdmJournalItem::GetSessionId                     // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:14:48 2013----------*/
int CdmJournalItem::GetSessionId() const
{
   return m_iSessionId;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:07:45 2012----------*
 * @method  CdmJournalItem::SetModified                      // public                            *
 * @return  void                                             //                                   *
 * @param   QDateTime p_qdModified                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:07:45 2012----------*/
void CdmJournalItem::SetModified(QDateTime p_qdModified)
{
   m_qdtModified = p_qdModified;
}

/** +-=---------------------------------------------------------So 10. Feb 09:15:07 2013----------*
 * @method  CdmJournalItem::GetModified                      // public, const, slots              *
 * @return  QDateTime                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:15:07 2013----------*/
QDateTime CdmJournalItem::GetModified() const
{
   return m_qdtModified;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:09:38 2012----------*
 * @method  CdmJournalItem::SetChangeMode                    // public                            *
 * @return  void                                             //                                   *
 * @param   EdmChangeMode p_eMode                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:09:38 2012----------*/
void CdmJournalItem::SetChangeMode(EdmChangeMode p_eMode)
{
   m_eChangeMode = p_eMode;
}

/** +-=---------------------------------------------------------So 10. Feb 09:15:17 2013----------*
 * @method  CdmJournalItem::GetChangeMode                    // public, const, slots              *
 * @return  EdmChangeMode                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:15:17 2013----------*/
EdmChangeMode CdmJournalItem::GetChangeMode() const
{
   return m_eChangeMode;
}

/** +-=---------------------------------------------------------So 10. Feb 09:15:28 2013----------*
 * @method  CdmJournalItem::GetChangeModeAsString            // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:15:28 2013----------*/
QString CdmJournalItem::GetChangeModeAsString() const
{
   QString qstrRet;

   switch (m_eChangeMode)
   {
   case eDmChangeModeNew:
      qstrRet = tr("Neu");
      break;
   case eDmChangeModeModified:
      qstrRet = tr("Änderung");
      break;
   case eDmChangeModeDeleted:
      qstrRet = tr("Löschung");
      break;
   default:
      qstrRet = tr("Unbekannt");
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:11:52 2012----------*
 * @method  CdmJournalItem::SetObjectId                      // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:11:52 2012----------*/
void CdmJournalItem::SetObjectId(int p_iId)
{
   m_iObjectId = p_iId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:15:38 2013----------*
 * @method  CdmJournalItem::GetObjectId                      // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:15:38 2013----------*/
int CdmJournalItem::GetObjectId() const
{
   return m_iObjectId;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:12:37 2012----------*
 * @method  CdmJournalItem::SetObjectListId                  // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:12:37 2012----------*/
void CdmJournalItem::SetObjectListId(int p_iId)
{
   m_iObjectListId = p_iId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:15:48 2013----------*
 * @method  CdmJournalItem::GetObjectListId                  // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:15:48 2013----------*/
int CdmJournalItem::GetObjectListId() const
{
   return m_iObjectListId;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:13:58 2012----------*
 * @method  CdmJournalItem::SetMemberId                      // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:13:58 2012----------*/
void CdmJournalItem::SetMemberId(int p_iId)
{
   m_iMemberId = p_iId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:16:10 2013----------*
 * @method  CdmJournalItem::GetMemberId                      // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:16:10 2013----------*/
int CdmJournalItem::GetMemberId() const
{
   return m_iMemberId;
}

/** +-=---------------------------------------------------------Mi 29. Aug 11:14:36 2012----------*
 * @method  CdmJournalItem::SetChanges                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrChanges                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 11:14:36 2012----------*/
void CdmJournalItem::SetChanges(QString p_qstrChanges)
{
   m_qstrChanges = p_qstrChanges;
}

/** +-=---------------------------------------------------------So 10. Feb 09:16:20 2013----------*
 * @method  CdmJournalItem::GetChanges                       // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:16:20 2013----------*/
QString CdmJournalItem::GetChanges() const
{
   return m_qstrChanges;
}

/** +-=---------------------------------------------------------Mi 29. Aug 13:33:11 2012----------*
 * @method  CdmJournalItem::SetDisplayString                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 13:33:11 2012----------*/
void CdmJournalItem::SetDisplayString(QString p_qstrValue)
{
   m_qstrDisplayString = p_qstrValue;
}

/** +-=---------------------------------------------------------So 10. Feb 09:16:28 2013----------*
 * @method  CdmJournalItem::GetDisplayString                 // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:16:28 2013----------*/
QString CdmJournalItem::GetDisplayString() const
{
   return m_qstrDisplayString;
}

/** +-=---------------------------------------------------------So 10. Feb 09:16:37 2013----------*
 * @method  CdmJournalItem::GetUserString                    // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:16:37 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:17:28 2013----------*
 * @method  CdmJournalItem::GetMemberAsString                // public, const, slots              *
 * @return  QString                                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:17:28 2013----------*/
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