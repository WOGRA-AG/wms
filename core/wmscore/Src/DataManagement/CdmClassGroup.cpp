// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"

CdmClassGroup::CdmClassGroup(CdmClass* p_pCdmClass,
                             QString p_qstrName,
                             int p_iPosition,
                             int p_iVersion,
                             int p_iParentId)
    : m_iId(0),
      m_rpCdmClass(p_pCdmClass),
      m_qstrName(p_qstrName),
      m_iVersion(p_iVersion),
      m_iParentId(p_iParentId),
      m_iPosition(p_iPosition)
{
}

CdmClassGroup::CdmClassGroup(QVariantMap& p_rqvHash,
                             CdmClass* p_pCdmClass,
                             CdmClassGroup* p_pCdmClassGroup)
    : m_iId(0),
      m_rpCdmClass(p_pCdmClass),
      m_iVersion(0),
      m_iParentId(0),
      m_iPosition(0)
{
    SetVariant(p_rqvHash);

    if (p_pCdmClassGroup)
    {
        m_iParentId = p_pCdmClassGroup->GetId();
    }
}

CdmClassGroup::~CdmClassGroup()
{
   ClearChildren();
}

int CdmClassGroup::GetId() const
{
   return m_iId.load();
}

void CdmClassGroup::SetId(int p_iId)
{
   m_iId = p_iId;
}

void CdmClassGroup::ClearChildren()
{
   SYNCHRONIZED_WRITE;
   QMap<int, CdmClassGroup*>::iterator qmIt = m_qmChilds.begin();
   QMap<int, CdmClassGroup*>::iterator qmItEnd = m_qmChilds.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClassGroup* pCdmClassGroup = qmIt.value();
      DELPTR(pCdmClassGroup)
   }

   m_qmChilds.clear();
}

void CdmClassGroup::SetVariant(QVariantMap& p_rqvHash)
{
   SYNCHRONIZED_WRITE;
   m_qstrName = p_rqvHash[WMS_NAME].toString();
   m_iPosition = p_rqvHash[WMS_POSITION].toInt();
   m_iVersion = p_rqvHash[WMS_VERSION].toInt();
   m_iId = p_rqvHash[WMS_ID].toInt();

   ClearChildren();
   QVariantMap qvChildren = p_rqvHash[WMS_CHILDREN].toMap();
   QVariantMap qvRights = p_rqvHash[WMS_RIGHTS].toMap();
   m_cCdmRights.SetVariant(qvRights);

   QVariantMap::iterator qmIt = qvChildren.begin();
   QVariantMap::iterator qmItEnd = qvChildren.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QVariantMap qvChild = qmIt.value().toMap();
      CdmClassGroup* pCdmChild = new CdmClassGroup(qvChild, m_rpCdmClass, this);
      m_qmChilds.insert(qmIt.key().toInt(), pCdmChild);
   }

   QVariantMap qvTranslations = p_rqvHash[WMS_TRANSLATIONS].toMap();
   QVariantMap::iterator qvIt = qvTranslations.begin();
   QVariantMap::iterator qvItEnd = qvTranslations.end();

   for (; qvIt != qvItEnd; ++qvIt)
   {
      QString iId = qvIt.key();
      QString qstrText = qvIt.value().toString();
      m_qmTranslations.insert(iId, qstrText);
   }
}

CdmClassGroup* CdmClassGroup::GetParent() const
{
   SYNCHRONIZED_READ;
   CdmClassGroup* pParent = nullptr;

   if (CHKPTR(m_rpCdmClass))
   {
      pParent = m_rpCdmClass->FindGroupById(m_iParentId.load());
   }

   return pParent;
}

void CdmClassGroup::SetParentId(int p_iParentId)
{
   m_iParentId = p_iParentId;
}

QString CdmClassGroup::GetName() const
{
   SYNCHRONIZED_READ;
   return m_qstrName;
}

void CdmClassGroup::SetName(QString p_qstrName)
{
   SYNCHRONIZED_WRITE;
   m_qstrName = p_qstrName;
}

int CdmClassGroup::GetPosition() const
{
   return m_iPosition.load();
}

void CdmClassGroup::SetPosition(int p_iPos)
{
   m_iPosition = p_iPos;
}

int CdmClassGroup::GetVersion() const
{
   return m_iVersion.load();
}

void CdmClassGroup::SetVersion(int p_iVersion)
{
   m_iVersion = p_iVersion;
}

void CdmClassGroup::AppendChild(CdmClassGroup* p_pCdmChild)
{
   SYNCHRONIZED_WRITE;
   // put it to the end
   m_qmChilds.insert(m_qmChilds.count() +1, p_pCdmChild);
}

void CdmClassGroup::MoveChildUp(CdmClassGroup* p_pCdmGroup)
{
   SYNCHRONIZED_WRITE;
   if (CHKPTR(p_pCdmGroup))
   {
      int iPos = GetChildPosition(p_pCdmGroup);

      if (iPos > 1)
      {
         CdmClassGroup* pCdmOld = m_qmChilds[iPos+1];
         m_qmChilds.insert(iPos - 1, p_pCdmGroup);
         m_qmChilds.insert(iPos, pCdmOld);
      }
   }
}

void CdmClassGroup::MoveChildDown(CdmClassGroup* p_pCdmGroup)
{
   SYNCHRONIZED_WRITE;
   if (CHKPTR(p_pCdmGroup))
   {
      int iPos = GetChildPosition(p_pCdmGroup);

      if (iPos < m_qmChilds.count() && iPos > 0)
      {
         CdmClassGroup* pCdmOld = m_qmChilds[iPos+1];
         m_qmChilds.insert(iPos + 1, p_pCdmGroup);
         m_qmChilds.insert(iPos, pCdmOld);
      }
   }
}

int CdmClassGroup::GetChildPosition(CdmClassGroup* p_pCdmGroup)
{
   SYNCHRONIZED_READ;
   int iPos = 0;

   if (CHKPTR(p_pCdmGroup))
   {
      QMap<int, CdmClassGroup*>::iterator qmIt = m_qmChilds.begin();
      QMap<int, CdmClassGroup*>::iterator qmItEnd = m_qmChilds.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         if (p_pCdmGroup == qmIt.value())
         {
            iPos = qmIt.key();
            break;
         }
      }
   }

   return iPos;
}

void CdmClassGroup::GetMembers(QList<CdmMember*>& p_rqlMembers) const
{
   SYNCHRONIZED_READ;
   p_rqlMembers.clear();

   if (CHKPTR(m_rpCdmClass))
   {
      QMap<long, CdmMember*> qmMembers;
      m_rpCdmClass->GetClassMemberMap(qmMembers);
      QVector<QString> qvSequence = m_rpCdmClass->GetMemberSequence();

      if (qvSequence.isEmpty())
      {
         QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
         QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            CdmMember* pCdmMember = qmIt.value();

            if (CHKPTR(pCdmMember))
            {
               if (pCdmMember->GetGroup() == this)
               {
                  p_rqlMembers.append(pCdmMember);
               }
            }
         }
      }
      else
      {
         for (int iCounter = 0; iCounter < qvSequence.count(); ++iCounter)
         {
            QString qstrKeyname = qvSequence[iCounter];
            CdmMember* pCdmMember = const_cast<CdmMember*>(m_rpCdmClass->FindMember(qstrKeyname));

            if (pCdmMember && pCdmMember->GetGroup() == this)
            {
               p_rqlMembers.append(pCdmMember);
            }
         }
      }
   }
}

CdmRights& CdmClassGroup::GetRights()
{
   SYNCHRONIZED_READ;
   return m_cCdmRights;
}

bool CdmClassGroup::CheckWriteAccess() const
{
   SYNCHRONIZED_READ;
   return m_cCdmRights.HasCurrentUserWriteAccess();
}

bool CdmClassGroup::CheckReadAccess() const
{
   SYNCHRONIZED_READ;
   return m_cCdmRights.HasCurrentUserReadAccess();
}

QVariant CdmClassGroup::GetVariant() const
{
   SYNCHRONIZED_READ;
   QVariantMap qvHash;

   qvHash.insert(WMS_NAME, m_qstrName);
   qvHash.insert(WMS_VERSION, m_iVersion.load());
   qvHash.insert(WMS_POSITION, m_iPosition.load());
   qvHash.insert(WMS_RIGHTS, m_cCdmRights.GetVariant());
   qvHash.insert(WMS_ID, m_iId.load());

   if (!m_qmChilds.isEmpty())
   {
      QVariantMap qvChildren;

      QMap<int, CdmClassGroup*>::const_iterator qmIt = m_qmChilds.begin();
      QMap<int, CdmClassGroup*>::const_iterator qmItEnd = m_qmChilds.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmClassGroup* pCdmClassGroup = qmIt.value();

         if (CHKPTR(pCdmClassGroup))
         {
            QVariant qvChild = pCdmClassGroup->GetVariant();
            qvChildren.insert(QString::number(qmIt.key()), qvChild);
         }
      }

      qvHash.insert(WMS_CHILDREN, qvChildren);
   }

   QMap<QString, QString>::const_iterator qmIt = m_qmTranslations.begin();
   QMap<QString, QString>::const_iterator qmItEnd = m_qmTranslations.end();
   QVariantMap qmTranslations;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString iId = qmIt.key();
      QString qstrText = qmIt.value();
      qmTranslations.insert(iId, qstrText);
   }

   qvHash.insert(WMS_TRANSLATIONS, qmTranslations);

   return qvHash;
}

QString CdmClassGroup::GetCaption() const
{
   SYNCHRONIZED_READ;
   QString qstrRet = GetName();
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
       QString iLanguageId = pCdmManager->GetCurrentLanguage();

      if (!iLanguageId.isEmpty())
      {
        qstrRet = GetTranslation(iLanguageId);
      }
   }

   return qstrRet;
}

void CdmClassGroup::DeleteTranslation(QString p_iId)
{
   SYNCHRONIZED_WRITE;
   m_qmTranslations.remove(p_iId);
   m_rpCdmClass->SetModified();
}

void CdmClassGroup::SetTranslation(QString p_qstrLanguage, QString p_qstrTranslation)
{
   SYNCHRONIZED_WRITE;
   m_qmTranslations.insert(p_qstrLanguage, p_qstrTranslation);
   m_rpCdmClass->SetModified();
}

QString CdmClassGroup::GetTranslation(QString p_iLanguageId) const
{
   SYNCHRONIZED_READ;
   QString qstrRet;

   if (m_qmTranslations.contains(p_iLanguageId))
   {
      qstrRet = m_qmTranslations[p_iLanguageId];
   }

   if (qstrRet.isEmpty())
   {
      qstrRet = m_qstrName;
   }

   return qstrRet;
}

QMap<QString, QString>& CdmClassGroup::GetTranslations()
{
   SYNCHRONIZED_READ;
   return m_qmTranslations;
}
