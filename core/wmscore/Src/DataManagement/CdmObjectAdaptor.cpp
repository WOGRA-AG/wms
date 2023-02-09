// System and QT Includes
#include <QFileInfo>


// own Includes
#include "CdmClassMethod.h"
#include "CdmClass.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CumUser.h"
#include "CdmUriTemplate.h"
#include "CdmLogging.h"
#include "CdmValueObjectRef.h"
#include "CdmValueContainerRef.h"
#include "CdmValue.h"
#include "CdmValueBinaryDocument.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmValueListString.h"
#include "CdmValueListDouble.h"
#include "CdmValueListInt.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueListObjects.h"
#include "CdmObjectAdaptor.h"
#include "wmsdefines.h"

CdmObjectAdaptor::CdmObjectAdaptor(qint64 p_lDbId,qint64 p_lObjectId,qint64 p_lObjectListId )
   : m_lDbId(p_lDbId),
  m_lObjectId(p_lObjectId),
  m_lObjectListId(p_lObjectListId)
{
   // nothing to do
}

CdmObjectAdaptor::CdmObjectAdaptor(  CdmObject* p_pCdmObject )
   : m_lDbId(0),
  m_lObjectId(0),
  m_lObjectListId(0)
{
   if(p_pCdmObject)
   {
      m_lDbId = p_pCdmObject->GetSchemeId();
      m_lObjectId = p_pCdmObject->GetId();
      m_lObjectListId = p_pCdmObject->GetObjectContainerId();
   }
}

CdmObjectAdaptor::CdmObjectAdaptor()
   : m_lDbId(0),
  m_lObjectId(0),
  m_lObjectListId(0)
{
}

CdmObjectAdaptor::CdmObjectAdaptor(const CdmObjectAdaptor& p_rCdmObjectAdaptor)
: CdmLocatedElement(p_rCdmObjectAdaptor),
  m_lDbId(p_rCdmObjectAdaptor.m_lDbId),
  m_lObjectId(p_rCdmObjectAdaptor.m_lObjectId),
  m_lObjectListId(p_rCdmObjectAdaptor.m_lObjectListId)
{
}

CdmObjectAdaptor::~CdmObjectAdaptor(  )
{
   // nothing to do here :-)
}

void CdmObjectAdaptor::SetObject(CdmObject* p_pCdmObject)
{
   if (p_pCdmObject)
   {
      m_lDbId = p_pCdmObject->GetSchemeId();
      m_lObjectId = p_pCdmObject->GetId();
      m_lObjectListId = p_pCdmObject->GetObjectContainerId();
   }
   else
   {
      m_lDbId = 0;
      m_lObjectId = 0;
      m_lObjectListId = 0;
   }
}

bool CdmObjectAdaptor::ValidateObjectData()
{
   // Override this function to check if a object to be stored ist valid
   return true;
}

void CdmObjectAdaptor::BeforeCommit()
{
    // Does nothing must be overriden by implementationclass.
}

void CdmObjectAdaptor::AfterCommit()
{
    // Does nothing must be overriden by implementationclass.
}

int CdmObjectAdaptor::CommitObject()
{
   int iRet = 0;

   CdmObject* pCdmObject = GetDataObject();

   if (pCdmObject)
   {
       BeforeCommit();
      iRet = pCdmObject->Commit();
      AfterCommit();
   }
   else
   {
      CdmObjectContainer* pCdmList = GetObjectContainer();

      if(CHKPTR(pCdmList))
      {
          BeforeCommit();
         iRet = pCdmList->Commit();
         AfterCommit();
      }
   }

   return iRet;
}

QString CdmObjectAdaptor::GetUri()
{
   QString qstrUri;
   CdmObject* pObject = GetDataObject();

   if (pObject)
   {
       qstrUri = pObject->GetUri();
   }

   return qstrUri;
}

QString CdmObjectAdaptor::GetUriInternal() const
{
    QString qstrUri;
    const CdmObject* pObject = GetConstDataObjectConst();

    if (pObject)
    {
        qstrUri = pObject->GetUriInternal();
    }

    return qstrUri;
}

bool CdmObjectAdaptor::DeleteObject()
{
   bool bRet = false;
   CdmObject* pCdmObject = GetDataObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetDeleted();
      if(SUCCESSFULL(pCdmObject->Commit()))
      {
         bRet = true;
      }
   }

   return bRet;
}

CdmObjectContainer* CdmObjectAdaptor::GetObjectContainer()
{
   CdmObjectContainer* pContainer = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (m_lObjectId > 0 && m_lObjectListId > 0 && m_lDbId > 0)
   {
      if(CHKPTR(pCdmManager))
      {
         CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(m_lDbId);

         if(CHKPTR(pContainerManager) && m_lObjectListId > 0)
         {
            pContainer = pContainerManager->FindEmptyContainerById(m_lObjectListId);
         }
      }
   }

   return pContainer;
}

CdmObject* CdmObjectAdaptor::GetObject()
{
   // TODO move code to new method GetDataObject and then delete this method ;-)
   CdmObject* pCdmObject = nullptr;

   if ((m_lObjectId > 0) && (m_lObjectListId > 0) && (m_lDbId > 0))
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(m_lDbId);

         if (CHKPTR(pContainerManager))
         {
            CdmObjectContainer* pContainer = pContainerManager->FindContainerById(m_lObjectListId);

            if (CHKPTR(pContainer))
            {
               pCdmObject = pContainer->FindObjectById(m_lObjectId);
            }
         }
      }

      if (!pCdmObject)
      {
         INFO("Object not found!!! DbId: " + QString::number(m_lDbId) + " ObjectListId: " + QString::number(m_lObjectListId) +
             " ObjectId = " + QString::number(m_lObjectId))
      }
   }
   else
   {
      INFO("Invalid Object!!!")
   }

   return pCdmObject;
}

CdmObject* CdmObjectAdaptor::GetDataObject()
{
    return GetObject();
}

const CdmObject* CdmObjectAdaptor::GetConstDataObjectConst() const
{
    return const_cast<CdmObject*>(const_cast<CdmObjectAdaptor*>(this)->GetDataObject());
}

CdmObject* CdmObjectAdaptor::GetDataObjectConst() const
{
    return const_cast<CdmObjectAdaptor*>(this)->GetDataObject();
}

void CdmObjectAdaptor::Refresh()
{
    BODY_TRY
    CdmObject* pCdmObject = GetDataObject();

    if (CHKPTR(pCdmObject))
    {
        pCdmObject->Refresh();
    }
    BODY_CATCH
}

bool CdmObjectAdaptor::IsValid() const
{
    bool bRet = false;

    BODY_TRY
    const CdmObject* pCdmObject = GetConstDataObjectConst();

    if (pCdmObject && pCdmObject->IsValid())
    {
        bRet = true;
    }
    BODY_CATCH

   return bRet;
}

QString CdmObjectAdaptor::GetKeyname() const
{
    QString qstrKeyname;

    BODY_TRY
    const CdmObject* pCdmObject = GetConstDataObjectConst();

    if (CHKPTR(pCdmObject))
    {
        qstrKeyname = pCdmObject->GetKeyname();
    }
    BODY_CATCH

    return qstrKeyname;
}

QString CdmObjectAdaptor::GetCaption() const
{
   QString qstrCaption;
   BODY_TRY
   const CdmObject* pCdmObject = GetConstDataObjectConst();

   if (CHKPTR(pCdmObject))
   {
      qstrCaption = pCdmObject->GetCaption();
   }
   BODY_CATCH

   return qstrCaption;
}

qint64 CdmObjectAdaptor::GetObjectId() const
{
   return m_lObjectId;
}

QString CdmObjectAdaptor::GetString(QString p_qstrKeyname) const
{
   QString qstrString;

   BODY_TRY
   CdmObject* pCdmObject = GetDataObjectConst();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, qstrString);
   }
   BODY_CATCH

   return qstrString;
}

CumUser* CdmObjectAdaptor::GetUser(QString p_qstrKeyname) const
{
   CumUser* pCumUser = nullptr;

   BODY_TRY
   CdmObject* pCdmObject = GetDataObjectConst();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, pCumUser);
   }
   BODY_CATCH

   return pCumUser;
}

QTime CdmObjectAdaptor::GetTime(QString p_qstrKeyname) const
{
   QTime qtTime;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, qtTime);
   }

   return qtTime;
}

QDate CdmObjectAdaptor::GetDate(QString p_qstrKeyname) const
{
   QDate qdDate;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, qdDate);
   }

   return qdDate;
}

QDateTime CdmObjectAdaptor::GetDateTime(QString p_qstrKeyname) const
{
   QDateTime qdDateTime;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, qdDateTime);
   }

   return qdDateTime;
}

float CdmObjectAdaptor::GetFloat(QString p_qstrKeyname) const
{
   float fRet = 0.0f;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, fRet);
   }

   return fRet;
}

bool CdmObjectAdaptor::GetBool(QString p_qstrKeyname) const
{
   bool bRet = false;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, bRet);
   }

   return bRet;
}

int CdmObjectAdaptor::GetInt(QString p_qstrKeyname) const
{
   int iRet = 0;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetDataObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, iRet);
   }
   return iRet;
}

CdmValue* CdmObjectAdaptor::GetValue(QString p_qstrKeyname)
{
   CdmValue* pCdmValue = nullptr;
   CdmObject* pCdmObject = GetDataObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmValue = pCdmObject->GetValue(p_qstrKeyname);
   }

   return pCdmValue;
}

qint64 CdmObjectAdaptor::GetLong(QString p_qstrKeyname) const
{
  qint64 lRet = 0;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if (CHKPTR(pCdmValue))
      {
         EdmValueType eValueType = pCdmValue->GetValueType();

         if ((eValueType == eDmValueLong) || (eValueType == eDmValueCounter))
         {
            lRet = (dynamic_cast<CdmValueLong*>(pCdmValue))->GetValue();
         }
      }
   }

   return lRet;
}

double CdmObjectAdaptor::GetDouble(QString p_qstrKeyname) const
{
   double dRet = 0.0;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->GetValue(p_qstrKeyname, dRet);
   }

   return dRet;
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, QString p_qstrValue)
{
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_qstrValue);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, CumUser* p_pCumUser)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      if (p_pCumUser)
      {
         pCdmObject->SetValue(p_qstrKeyname, p_pCumUser->GetId());
      }
      else
      {
         pCdmObject->SetValue(p_qstrKeyname, 0);
      }
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, QDate p_qdDate)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_qdDate);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, QDateTime p_qdtDateTime)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_qdtDateTime);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qqstrkeyname, QTime p_qtTime)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qqstrkeyname, p_qtTime);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, float p_fValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_fValue);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, double p_dValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_dValue);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, int p_iValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_iValue);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname,qint64 p_lValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_lValue);
   }
}

void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, bool p_bValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_bValue);
   }
}

CdmObject* CdmObjectAdaptor::GetObjectRefValue(QString p_qstrKeyname)
{
   const CdmObject* pCdmObjectReturn = nullptr;
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if(CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueObjectRef)
      {
         pCdmObjectReturn = ((CdmValueObjectRef*)pCdmValue)->GetObject();
      }
      else
      {
         ERR("Value '" + p_qstrKeyname + "' in Object not found.\n ObjectInfo:\n"+pCdmObject->GetInfo());
      }
   }
  else
   {
      ERR("nullptr Pointer while asking for Value with Keyname: " + p_qstrKeyname);
   }

   return const_cast<CdmObject*>(pCdmObjectReturn);
}

void CdmObjectAdaptor::SetObjectRefValue(QString p_qstrKeyname, QString qstrSelfLink)
{
    CdmObject* p_cdmObj = FindObjectBySelfLink(qstrSelfLink);
    SetObjectRefValue(p_qstrKeyname, p_cdmObj);
}

CdmObject* CdmObjectAdaptor::FindObjectBySelfLink(QString qstrSelfLink)
{
    CdmObject *pObject = nullptr;
    CdmUriTemplate m_uriTemplate("http://{host}/Rest/Api//object/{schema}/{containerId}/{objectId}/");
    QMap<QString,QString> qmMatches = m_uriTemplate.match(qstrSelfLink);

    if(!qstrSelfLink.isEmpty())
    {
            QString qstrObjId = qmMatches["objectId"];
            QString qstrObjListId = qmMatches["containerId"];
            QLocale loc;
            bool isObjId;
            bool isObjListId;
            int iObjId = loc.toInt(qstrObjId, &isObjId);
            int iObjListId = loc.toInt(qstrObjListId, &isObjListId);
            CdmDataProvider *pProvider = CdmSessionManager::GetDataProvider();
            CdmContainerManager *pManager = pProvider->GetContainerManager();
            if(isObjId && isObjListId)
            {
                CdmObjectContainer *pContainer = pManager->FindEmptyContainerById(iObjListId);
                pObject = pContainer->FindObjectById(iObjId);
            } else {
                CdmObjectContainer *pContainer = pManager->FindEmptyContainerByKeyname(qstrObjListId);
                pObject = pContainer->FindObjectByKeyname(qstrObjId);
            }
    }
    return pObject;
}

qint64 CdmObjectAdaptor::GetObjectRef(QString p_qstrKeyname)
{
  qint64 lObjectRef = 0;
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if(CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueObjectRef)
      {
         lObjectRef = ((CdmValueObjectRef*)pCdmValue)->GetValue();
      }
      else
      {
         WARNING("pCdmValue is nullptr or not of type objectref");
      }
   }

   return lObjectRef;
}

qint64 CdmObjectAdaptor::GetContainerRef(QString p_qstrKeyname)
{
  qint64 lRet = 0;
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if(CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueContainerRef)
      {
         lRet = ((CdmValueContainerRef*)pCdmValue)->GetValue();
      }
   }

   return lRet;
}

void CdmObjectAdaptor::SetContainerRefValue(QString p_qstrKeyname,qint64 p_lObjectListId)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if(CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueContainerRef)
      {
         ((CdmValueContainerRef*)pCdmValue)->SetValue(p_lObjectListId);
      }
   }
}

void CdmObjectAdaptor::SetContainerRefValue(QString p_qstrKeyname, CdmObjectContainer* p_pContainer)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if(CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueContainerRef)
      {
         if (p_pContainer)
         {
            ((CdmValueContainerRef*)pCdmValue)->SetValue(p_pContainer->GetId());
         }
         else
         {
            ((CdmValueContainerRef*)pCdmValue)->SetValue((qint64)0);
         }
      }
   }
}

void CdmObjectAdaptor::ReloadContainerComplete(CdmObjectContainer *&p_pContainer)
{
    if (CHKPTR(p_pContainer))
    {
        CdmContainerManager* pContainerManager = p_pContainer->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainerManager->ReloadContainerComplete(p_pContainer);
        }
    }
}

void CdmObjectAdaptor::SetObjectRefValue(QString p_qstrKeyname, CdmObject* p_pCdmObject)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if(CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueObjectRef)
      {
         if (p_pCdmObject)
         {
            ((CdmValueObjectRef*)pCdmValue)->SetValue(p_pCdmObject);
         }
         else
         {
            ((CdmValueObjectRef*)pCdmValue)->SetValue(nullptr);
         }
      }
   }
}

CdmObjectContainer* CdmObjectAdaptor::GetContainerRefValue(QString p_qstrKeyname)
{
   CdmObjectContainer* pContainer = nullptr;

    BODY_TRY
    CdmObject* pCdmObject = GetDataObject();

    if (CHKPTR(pCdmObject))
    {
        CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueContainerRef)
        {
            pContainer = static_cast<CdmValueContainerRef*>(pCdmValue)->GetContainer();
        }
    }
    BODY_CATCH

    return pContainer;
}

CdmObjectContainer* CdmObjectAdaptor::GetEmptyContainerRefValue(QString p_qstrKeyname)
{
   CdmObjectContainer* pContainer = nullptr;

    BODY_TRY
    CdmObject* pCdmObject = GetObject();

    if (CHKPTR(pCdmObject))
    {
        // TODO SB develop a smarter cast for values
        CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueContainerRef)
        {
            pContainer = static_cast<CdmValueContainerRef*>(pCdmValue)->GetEmptyContainer();
        }
    }
    BODY_CATCH

    return pContainer;
}

QString CdmObjectAdaptor::GetDisplayString(QString p_qstrKeyname) const
{
    QString qstrRet;

    BODY_TRY
    const CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

    if (CHKPTR(pCdmObject))
    {
        qstrRet = pCdmObject->GetDisplayString(p_qstrKeyname);
    }
    BODY_CATCH

    return qstrRet;
}

void CdmObjectAdaptor::SetBinDocNewFilename(QString p_qstrKeyname, QString p_qstrFilename)
{
    BODY_TRY
    CdmObject* pCdmObject = GetObject();

    if (CHKPTR(pCdmObject))
    {
       CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

       if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueBinaryDocument)
       {
           CdmValueBinaryDocument* pCdmValueBinDoc = static_cast<CdmValueBinaryDocument*>(pCdmValue);

           if (CHKPTR(pCdmValueBinDoc))
           {
               QFileInfo qfInfo(p_qstrFilename);
               QString qstrSuffix = qfInfo.completeSuffix();

               if (qstrSuffix.isEmpty())
               {
                   qstrSuffix = qfInfo.suffix();
               }

               pCdmValueBinDoc->SetValue(p_qstrFilename, qstrSuffix);
               IdmDataAccess* pDataAccess = pCdmValueBinDoc->GetDataAccess();

               if (CHKPTR(pDataAccess))
               {
                   pDataAccess->UpdateBinaryDocument(pCdmValueBinDoc->GetSchemeId(), pCdmValueBinDoc);
               }
           }
       }
   }
   BODY_CATCH
}

QString CdmObjectAdaptor::GetBinDocCurrentFilename(QString p_qstrKeyname)
{
   QString qstrRet;
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueBinaryDocument)
      {
         CdmValueBinaryDocument* pCdmValueBinDoc = ((CdmValueBinaryDocument*)pCdmValue);
         qstrRet = pCdmValueBinDoc->GetFilename();
      }
   }
 
   return qstrRet;
}

QString CdmObjectAdaptor::GetBinDocCurrentCompletePath(QString p_qstrKeyname)
{
    QString qstrRet;
    CdmObject* pCdmObject = GetObject();

    if (CHKPTR(pCdmObject))
    {
       CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

       if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueBinaryDocument)
       {
          CdmValueBinaryDocument* pCdmValueBinDoc = ((CdmValueBinaryDocument*)pCdmValue);
          qstrRet = pCdmValueBinDoc->GetCurrentDirectory() + "/" +pCdmValueBinDoc->GetFilename();
       }
    }

    return qstrRet;
}

void CdmObjectAdaptor::OpenBinDoc(QString p_qstrKeyname)
{
   QString qstrRet;
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueBinaryDocument)
      {
         CdmValueBinaryDocument* pCdmValueBinDoc = ((CdmValueBinaryDocument*)pCdmValue);
         pCdmValueBinDoc->ExecuteFile();
      }
   }
}

QByteArray CdmObjectAdaptor::LoadBinDoc(QString p_qstrKeyname)
{
   QByteArray qByteArray;
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueBinaryDocument)
      {
         CdmValueBinaryDocument* pCdmValueBinDoc = ((CdmValueBinaryDocument*)pCdmValue);
         qByteArray = pCdmValueBinDoc->GetByteArray();
      }
   }

   return qByteArray;
}

void CdmObjectAdaptor::SaveBinDocTo(QString p_qstrKeyname, QString p_qstrPath)
{
   QString qstrRet;
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

      if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueBinaryDocument)
      {
         CdmValueBinaryDocument* pCdmValueBinDoc = ((CdmValueBinaryDocument*)pCdmValue);
         pCdmValueBinDoc->SaveFileTo(p_qstrPath);
      }
   }
}

QList<QString> CdmObjectAdaptor::GetStringList(QString p_qstrMember) const
{
   QList<QString> qllRet;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      qllRet = pCdmValueList->GetList();
   }

   return qllRet;
}

QList<double> CdmObjectAdaptor::GetDoubleList(QString p_qstrMember) const
{
   QList<double> qllRet;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      qllRet = pCdmValueList->GetList();
   }

   return qllRet;
}

QList<int> CdmObjectAdaptor::GetIntList(QString p_qstrMember) const
{
   QList<int> qllRet;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      qllRet = pCdmValueList->GetList();
   }

   return qllRet;
}

QList<CdmObject*> CdmObjectAdaptor::GetListObjects(QString p_qstrMember)
{
   QList<CdmObject*> qllRet;
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListObjects)
   {
      CdmValueListObjects* pCdmValueList = (CdmValueListObjects*)pCdmValue;
      pCdmValueList->GetList(qllRet);
   }

   return qllRet;
}

void CdmObjectAdaptor::SetListObjects(QString p_qstrMember, QList<CdmObject*> p_qlObjects)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListObjects)
   {
      CdmValueListObjects* pCdmValueList = (CdmValueListObjects*)pCdmValue;
      pCdmValueList->SetList(p_qlObjects);
   }
}

void CdmObjectAdaptor::AddStringListValue(QString p_qstrMember, QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      pCdmValueList->AddValue(p_qstrValue);
   }
}

void CdmObjectAdaptor::SetStringList(QString p_qstrMember, QList<QString> p_rqstrlList)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      pCdmValueList->SetList(p_rqstrlList);
   }
}

void CdmObjectAdaptor::SetIntList(QString p_qstrMember, QList<int> p_rqstrlList)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      pCdmValueList->SetList(p_rqstrlList);
   }
}

void CdmObjectAdaptor::SetDoubleList(QString p_qstrMember, QList<double> p_rqstrlList)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      pCdmValueList->SetList(p_rqstrlList);
   }
}

void CdmObjectAdaptor::AddDoubleListValue(QString p_qstrMember, double p_dValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      pCdmValueList->AddValue(p_dValue);
   }
}

void CdmObjectAdaptor::AddIntListValue(QString p_qstrMember, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      pCdmValueList->AddValue(p_iValue);
   }
}

void CdmObjectAdaptor::AddListObjectsValue(QString p_qstrMember, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListObjects)
   {
      CdmValueListObjects* pCdmValueList = (CdmValueListObjects*)pCdmValue;
      pCdmValueList->AddValue(p_pCdmObject);
   }
}

void CdmObjectAdaptor::SetListObjectsValues(QString p_qstrMember, QVariantList selfLinks)
{
    QList<CdmObject*> qll_cdmObjects;
    for(auto selfLink : selfLinks)
    {
        CdmObject* p_cdmObj = FindObjectBySelfLink(selfLink.toString());
        if(CHKPTR(p_cdmObj))
        {
            qll_cdmObjects.append(p_cdmObj);
        }
    }
    SetListObjects(p_qstrMember, qll_cdmObjects);
}

void CdmObjectAdaptor::RemoveStringListValue(QString p_qstrMember, QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      pCdmValueList->RemoveValue(p_qstrValue);
   }
}

void CdmObjectAdaptor::RemoveDoubleListValue(QString p_qstrMember, double p_dValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      pCdmValueList->RemoveValue(p_dValue);
   }
}

void CdmObjectAdaptor::RemoveIntListValue(QString p_qstrMember, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      pCdmValueList->RemoveValue(p_iValue);
   }
}

void CdmObjectAdaptor::RemoveListObjectsValue(QString p_qstrMember, CdmObject* p_pCdmObject)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListObjects)
   {
      CdmValueListObjects* pCdmValueList = (CdmValueListObjects*)pCdmValue;
      pCdmValueList->RemoveValue(p_pCdmObject);
   }
}

void CdmObjectAdaptor::RemoveListObjectsComplete(QString p_qstrMember)
{
    CdmValue* pCdmValue = GetValue(p_qstrMember);

    if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListObjects)
    {
       CdmValueListObjects* pCdmValueList = (CdmValueListObjects*)pCdmValue;
       pCdmValueList->ClearList();
       CommitObject();
    }
}

QMap<QString, QString> CdmObjectAdaptor::GetStringStringDict(QString p_qstrValue) const
{
   QMap<QString, QString> qmResult;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
   {
      CdmValueDictStringString* pCdmValueDict = (CdmValueDictStringString*)pCdmValue;
      qmResult = pCdmValueDict->GetDict();
   }

   return qmResult;
}

void CdmObjectAdaptor::SetStringStringDict(QString p_qstrValue, QMap<QString, QString> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
   {
      CdmValueDictStringString* pCdmValueDict = (CdmValueDictStringString*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

QMap<QString, int> CdmObjectAdaptor::GetStringIntDict(QString p_qstrValue) const
{
   QMap<QString, int> qmResult;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      qmResult = pCdmValueDict->GetDict();
   }

   return qmResult;
}

void CdmObjectAdaptor::SetStringIntDict(QString p_qstrValue, QMap<QString, int> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

void CdmObjectAdaptor::SetStringDoubleDict(QString p_qstrValue, QMap<QString, double> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringDouble)
   {
      CdmValueDictStringDouble* pCdmValueDict = (CdmValueDictStringDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

void CdmObjectAdaptor::SetIntDoubleDict(QString p_qstrValue, QMap<int, double> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

void CdmObjectAdaptor::SetIntIntDict(QString p_qstrValue, QMap<int, int> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

void CdmObjectAdaptor::SetIntStringDict(QString p_qstrValue, QMap<int, QString> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

QMap<QString, double> CdmObjectAdaptor::GetStringDoubleDict(QString p_qstrValue) const
{
   QMap<QString, double> qmResult;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringDouble)
   {
      CdmValueDictStringDouble* pCdmValueDict = (CdmValueDictStringDouble*)pCdmValue;
      qmResult = pCdmValueDict->GetDict();
   }


   return qmResult;
}

QMap<int, QString> CdmObjectAdaptor::GetIntStringDict(QString p_qstrValue) const
{
   QMap<int, QString> qmResult;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      qmResult = pCdmValueDict->GetDict();
   }

   return qmResult;
}

QMap<int, int> CdmObjectAdaptor::GetIntIntDict(QString p_qstrValue) const
{
   QMap<int, int> qmResult;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      qmResult = pCdmValueDict->GetDict();
   }

   return qmResult;
}

QMap<int, double> CdmObjectAdaptor::GetIntDoubleDict(QString p_qstrValue) const
{
   QMap<int, double> qmResult;
   CdmValue* pCdmValue = (const_cast<CdmObjectAdaptor*>(this))->GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      qmResult = pCdmValueDict->GetDict();
   }

   return qmResult;
}

void CdmObjectAdaptor::AddStringStringEntry(QString p_qstrMember,
                                            QString p_qstrKey,
                                            QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
   {
      CdmValueDictStringString* pCdmValueDict = (CdmValueDictStringString*)pCdmValue;
      pCdmValueDict->SetValue(p_qstrKey, p_qstrValue);
   }
}

void CdmObjectAdaptor::AddStringIntEntry(QString p_qstrMember, QString p_qstrKey, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      pCdmValueDict->SetValue(p_qstrKey, p_iValue);
   }
}

void CdmObjectAdaptor::AddStringDoubleEntry(QString p_qstrMember,
                                            QString p_qstrKey,
                                            double p_dValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringDouble)
   {
      CdmValueDictStringDouble* pCdmValueDict = (CdmValueDictStringDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_qstrKey, p_dValue);
   }
}

void CdmObjectAdaptor::AddIntStringEntry(QString p_qstrMember, int p_iKey, QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      pCdmValueDict->SetValue(p_iKey, p_qstrValue);
   }
}

void CdmObjectAdaptor::AddIntIntEntry(QString p_qstrMember, int p_iKey, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      pCdmValueDict->SetValue(p_iKey, p_iValue);
   }
}

void CdmObjectAdaptor::AddIntDoubleEntry(QString p_qstrMember, int p_iKey, double p_dValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_iKey, p_dValue);
   }
}

void CdmObjectAdaptor::RemoveStringStringEntry(QString p_qstrMember, QString p_qstrKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
   {
      CdmValueDictStringString* pCdmValueDict = (CdmValueDictStringString*)pCdmValue;
      pCdmValueDict->RemoveValue(p_qstrKey);
   }
}

void CdmObjectAdaptor::RemoveStringIntEntry(QString p_qstrMember, QString p_qstrKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      pCdmValueDict->RemoveValue(p_qstrKey);
   }
}

void CdmObjectAdaptor::RemoveStringDoubleEntry(QString p_qstrMember, QString p_qstrKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringDouble)
   {
      CdmValueDictStringDouble* pCdmValueDict = (CdmValueDictStringDouble*)pCdmValue;
      pCdmValueDict->RemoveValue(p_qstrKey);
   }
}

void CdmObjectAdaptor::RemoveIntStringEntry(QString p_qstrMember, int p_iKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      pCdmValueDict->RemoveValue(p_iKey);
   }
}

void CdmObjectAdaptor::RemoveIntIntEntry(QString p_qstrMember, int p_iKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      pCdmValueDict->RemoveValue(p_iKey);
   }
}

void CdmObjectAdaptor::RemoveIntDoubleEntry(QString p_qstrMember, int p_iKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      pCdmValueDict->RemoveValue(p_iKey);
   }
}

void CdmObjectAdaptor::operator=(const CdmObjectAdaptor& p_rCdmObjectAdaptor)
{
   m_lDbId = p_rCdmObjectAdaptor.m_lDbId;
   m_lObjectId = p_rCdmObjectAdaptor.m_lObjectId;
   m_lObjectListId = p_rCdmObjectAdaptor.m_lObjectListId;
}

bool CdmObjectAdaptor::IsTypeOf(QString p_qstrType) const
{
   bool bRet = false;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (pCdmObject)
   {
      bRet = pCdmObject->IsTypeOf(p_qstrType);
   }

   return bRet;
}

void CdmObjectAdaptor::SetDeleted()
{
   CdmObject* pCdmObject = GetObject();

   if (pCdmObject)
   {
      pCdmObject->SetDeleted();
   }
}

QVariant CdmObjectAdaptor::GetVariant() const
{
   QVariant qVariant;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      qVariant = pCdmObject->GetVariant();
   }

   return qVariant;
}

QVariant CdmObjectAdaptor::GetVariant(QString& p_qstrValue) const
{
   QVariant qVariant;
   CdmObject* pCdmObject = (const_cast<CdmObjectAdaptor*>(this))->GetObject();

   if (CHKPTR(pCdmObject))
   {
      qVariant = pCdmObject->GetVariant(p_qstrValue);
   }

   return qVariant;
}

void CdmObjectAdaptor::SetVariant(QVariant& p_rqVariant, QString p_qstrOLKeyname)
{
   QVariantMap qHash = p_rqVariant.toMap();
   CdmObjectContainer* pContainer = GetObjectContainer(p_qstrOLKeyname);

   if (CHKPTR(pContainer))
   {
     qint64 lObjectId = qHash["ObjectId"].toInt();
      CdmObject* pCdmObject = nullptr;

      if (lObjectId > 0)
      {
         // Update object
         pCdmObject = pContainer->FindObjectById(lObjectId);
      }
      else
      {
         // Create Object
         pCdmObject = pContainer->CreateNewObject();
      }

      SetObject(pCdmObject);
      UpdateObject(qHash);
   }
}

void CdmObjectAdaptor::UpdateObject(QVariantMap& p_rqVariant)
{
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      QVariantMap qvHash = p_rqVariant["Values"].toMap();
   }
}

CdmObjectContainer* CdmObjectAdaptor::GetObjectContainer(QString p_qstrKeyname)
{
   CdmObjectContainer* pContainer = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      pContainer = pCdmManager->GetObjectContainerEmpty(p_qstrKeyname);
   }

   return pContainer;
}

CdmObject* CdmObjectAdaptor::GetParentObject()
{
   CdmObject* pCdmParent = nullptr;
   CdmObject* pCdmObject = GetObject();

   if (pCdmObject)
   {
      pCdmParent = pCdmObject->GetParent();
   }

   return pCdmParent;
}

qint64 CdmObjectAdaptor::GetParentObjectId()
{
  qint64 lRet = 0;
   CdmObject* pCdmObject = GetObject();
   
   if (pCdmObject)
   {
      lRet = pCdmObject->GetParentId();
   }

   return lRet;
}

QVariant CdmObjectAdaptor::Execute(QString p_qstrFunction)
{
   QVariant qvResult;

   if (!p_qstrFunction.isEmpty())
   {
      CdmObject* pObject = GetObject();

      if (CHKPTR(pObject))
      {
          pObject->Commit();
         CdmClass* pClass = pObject->GetClass();

         if (CHKPTR(pClass))
         {
            CdmClassMethod* pMethod = pClass->GetMethod(p_qstrFunction);

            if (CHKPTR(pMethod) && 
                pMethod->GetAccess() == eDmMemberAccessPublic)
            {
               qvResult = CdmExecutor::GetExecutor()->GetFunction()->ExecuteFunction(p_qstrFunction, pObject, QVariantList());
            }
            else
            {
               ERR(tr("Funktion konnte nicht aufgelöst werden.\nDie Funktion konnte nicht aufgelöst werden.\nDie Funktion wurde nicht gefunden, ist nicht vom Typ Objekt, hat Parameter oder ist nicht Öffentlich."));
            }
         }
      }
   }

   return qvResult;
}

QVariantMap CdmObjectAdaptor::GetVariantGraph(bool p_bFollowNonOwnerObjectlist,
                                              bool p_bFollowNonOwnerObject,
                                              QStringList p_qstrExcludedKeynames,
                                              int p_iMaxDepth,
                                              int p_iMaxObjects) const
{
    QVariantMap qmMembers;
    int iProcessedObjects = 1;

    QMap<QString, CdmValue*> m_qmValues;
    CdmObject* pObject = const_cast<CdmObjectAdaptor*> (this)->GetObject();

    if (CHKPTR(pObject))
    {
        pObject->GetValueMap(m_qmValues);
        QMap<QString, CdmValue*>::const_iterator qmIt =  m_qmValues.begin();
        QMap<QString, CdmValue*>::const_iterator qmItEnd = m_qmValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmValue* pCdmValue = qmIt.value();

            if(p_qstrExcludedKeynames.contains(pCdmValue->GetKeyname()))
            {
                if(pCdmValue->GetValueType() == eDmValueContainerRef) {
                    CdmObjectContainer* pObjectlist = dynamic_cast<CdmValueContainerRef*> (pCdmValue)->GetContainer();
                    QString qstrUri = pObjectlist->GetUri();
                     qmMembers.insert(qmIt.key(), qstrUri);
                }
                continue;
            }

            if (CHKPTR(pCdmValue))
            {
                EdmValueType eValue = pCdmValue->GetValueType();
                if (eValue == eDmValueContainerRef &&
                    (pCdmValue->GetMember()->IsOwner() || p_bFollowNonOwnerObjectlist))
                {
                    CdmObjectContainer* pObjectlist = ((CdmValueContainerRef*)pCdmValue)->GetContainer();
                    CdmContainerManager* pManager = pObjectlist->GetContainerManager();
                   qint64 lId = pObjectlist->GetId();
                    pManager->ReloadContainerComplete(lId);
                    pObjectlist = pManager->FindContainerById(lId);

                    QList<CdmObject*> qllObjects;
                    pObjectlist->GetObjectList(qllObjects);

                    QList<CdmObject*>::iterator qllIt = qllObjects.begin();
                    QList<CdmObject*>::iterator qllItEnd = qllObjects.end();

                    QVariantList pObjectlistVariant;
                    for(; qllIt != qllItEnd; ++qllIt)
                    {
                       CdmObject* pContainerObject = *qllIt;
                       QVariantMap childVariant;
                       if(p_iMaxDepth <= 0 || iProcessedObjects >= p_iMaxObjects)
                       {
                           childVariant.insert(WMS_URI, pContainerObject->GetUri());
                       }
                       else
                       {
                           CdmObjectAdaptor cCdmObjectAdaptor(pContainerObject);
                           childVariant = cCdmObjectAdaptor.GetVariantGraph(p_bFollowNonOwnerObjectlist, p_bFollowNonOwnerObject, p_qstrExcludedKeynames, p_iMaxDepth - 1, p_iMaxObjects - iProcessedObjects);
                           int iProcessedChildObjects = childVariant[WMS_PROCESSED_OBJECTS].toInt();
                           iProcessedObjects += iProcessedChildObjects;
                           childVariant.remove(WMS_PROCESSED_OBJECTS);
                           AppendLinksToChildVariant(pContainerObject, childVariant);
                           pObjectlistVariant.append(childVariant);
                       }

                    }
                    qmMembers.insert(qmIt.key(), pObjectlistVariant);
                    continue;
                }
                else if (pCdmValue->GetValueType() == eDmValueObjectRef &&
                         (pCdmValue->GetMember()->IsOwner() || p_bFollowNonOwnerObject))
                {
                    CdmObject* pRefObject = dynamic_cast<CdmValueObjectRef*> (pCdmValue)->GetObject();

                    if(pRefObject)
                    {
                        QVariantMap childVariant;
                        if(p_iMaxDepth <= 0 || iProcessedObjects >= p_iMaxObjects)
                        {
                            childVariant.insert(WMS_URI, pRefObject->GetUri());
                        }
                        else
                        {
                            CdmObjectAdaptor cCdmObjectAdaptor(pRefObject);
                            childVariant = cCdmObjectAdaptor.GetVariantGraph(p_bFollowNonOwnerObjectlist, p_bFollowNonOwnerObject, p_qstrExcludedKeynames, p_iMaxDepth - 1, p_iMaxObjects - iProcessedObjects);
                            int iProcessedChildObjects = childVariant[WMS_PROCESSED_OBJECTS].toInt();
                            iProcessedObjects += iProcessedChildObjects;
                            AppendLinksToChildVariant(pObject, childVariant);
                            childVariant.remove(WMS_PROCESSED_OBJECTS);
                        }
                        qmMembers.insert(qmIt.key(), childVariant);
                    }
                    continue;
                }
                else if (pCdmValue->GetValueType() == eDmValueBinaryDocument)
                {
                    continue;
                }
                else if (pCdmValue->GetValueType() == eDmValueListObjects && p_bFollowNonOwnerObjectlist)
                {
                    CdmValueListObjects *pObjectList = dynamic_cast<CdmValueListObjects*>(pCdmValue);
                    QList<CdmObject*>qllObjects;
                    pObjectList->GetList(qllObjects);
                    QList<CdmObject*>::iterator qllIt = qllObjects.begin();
                    QList<CdmObject*>::iterator qllItEnd = qllObjects.end();

                    QVariantList pObjectlistVariant;
                    for (; qllIt != qllItEnd; ++qllIt)
                    {
                        CdmObject* pObject = *qllIt;
                        if(CHKPTR(pObject))
                        {
                            QVariantMap childVariant;
                            if(p_iMaxDepth <= 0 || iProcessedObjects >= p_iMaxObjects)
                            {
                                childVariant.insert(WMS_URI, pObject->GetUri());
                            }
                            else
                            {
                                CdmObjectAdaptor cCdmObjectAdaptor(pObject);
                                childVariant = cCdmObjectAdaptor.GetVariantGraph(p_bFollowNonOwnerObjectlist, p_bFollowNonOwnerObject, p_qstrExcludedKeynames, p_iMaxDepth - 1, p_iMaxObjects - iProcessedObjects);
                                int iProcessedChildObjects = childVariant[WMS_PROCESSED_OBJECTS].toInt();
                                iProcessedObjects += iProcessedChildObjects;
                                childVariant.remove(WMS_PROCESSED_OBJECTS);
                                AppendLinksToChildVariant(pObject, childVariant);
                                pObjectlistVariant.append(childVariant);
                            }
                        }
                    }
                    qmMembers.insert(qmIt.key(), pObjectlistVariant);
                    continue;
                }
                QVariant qvValue = pCdmValue->GetValueVariant();
                qmMembers.insert(qmIt.key(), qvValue);
            }
        }
    }
    qmMembers.insert(WMS_PROCESSED_OBJECTS, iProcessedObjects);
    return qmMembers;
}

void CdmObjectAdaptor::AppendLinksToChildVariant(CdmObject* pObject, QVariantMap &childVariant) const
{
    BODY_TRY
    QVariantList qvlLinks;
    QVariantMap qvmSelfLink;
    qvmSelfLink.insert(WMS_HREF, pObject->GetUri());
    qvmSelfLink.insert(WMS_REL, WMS_SELF);
    qvlLinks.append(qvmSelfLink);
    childVariant.insert(WMS_LINKS, qvlLinks);
    BODY_CATCH
}

CdmClassManager* CdmObjectAdaptor::GetClassManager()
{
    CdmClassManager* pCdmClassManager = nullptr;

    BODY_TRY
    CdmObject* pObject = GetDataObject();

    if (CHKPTR(pObject))
    {
        return pObject->GetClassManager();
    }
    BODY_CATCH

    return pCdmClassManager;
}

CdmContainerManager* CdmObjectAdaptor::GetContainerManager()
{
    CdmContainerManager* pCdmContainerManager = nullptr;

    BODY_TRY
    CdmObject* pObject = GetDataObject();

    if (CHKPTR(pObject))
    {
        pCdmContainerManager = pObject->GetContainerManager();
    }
    BODY_CATCH

    return pCdmContainerManager;
}
