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
#include <QFileInfo>


// own Includes
#include "CdmClassMethod.h"
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CumUser.h"
#include "CdmMessageManager.h"
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:08:22 2005----------*
 * @method  CdmObjectAdaptor::CdmObjectAdaptor               // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDbId                                     //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment the cosntructor of dataccess.                                                         *
 *----------------last changed: --------------------------------Sa 20. Aug 10:08:22 2005----------*/
CdmObjectAdaptor::CdmObjectAdaptor(long p_lDbId, long p_lObjectId, long p_lObjectListId )
   : m_lDbId(p_lDbId),
  m_lObjectId(p_lObjectId),
  m_lObjectListId(p_lObjectListId)
{
   // nothing to do
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:08:34 2005----------*
 * @method  CdmObjectAdaptor::CdmObjectAdaptor               // public                            *
 * @return                                                   //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor f the object adaptor.                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 10:08:34 2005----------*/
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

/** +-=---------------------------------------------------------Mo 27. Feb 11:38:44 2006----------*
 * @method  CdmObjectAdaptor::CdmObjectAdaptor               // public                            *
 * @return                                                   //                                   *
 * @comment The default constructor. it creates an invalid objectadaptor. if you want to          *
 *          change it to a valid adaptor you have to call SetObject() with a valid                *
 *          CdmObject.                                                                            *
 *----------------last changed: Wolfgang Graßhof----------------Mo 27. Feb 11:38:44 2006----------*/
CdmObjectAdaptor::CdmObjectAdaptor()
   : m_lDbId(0),
  m_lObjectId(0),
  m_lObjectListId(0)
{
}

/** +-=---------------------------------------------------------So 19. Nov 16:11:29 2006----------*
 * @method  CdmObjectAdaptor::CdmObjectAdaptor               // public                            *
 * @return                                                   //                                   *
 * @param   const CdmObjectAdaptor& p_rCdmObjectAdaptor      //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 19. Nov 16:11:29 2006----------*/
CdmObjectAdaptor::CdmObjectAdaptor(const CdmObjectAdaptor& p_rCdmObjectAdaptor)
: CdmLocatedElement(p_rCdmObjectAdaptor),
  m_lDbId(p_rCdmObjectAdaptor.m_lDbId),
  m_lObjectId(p_rCdmObjectAdaptor.m_lObjectId),
  m_lObjectListId(p_rCdmObjectAdaptor.m_lObjectListId)
{
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:47:25 2005----------*
 * @method  CdmObjectAdaptor::~CdmObjectAdaptor              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsDataAccess                                                *
 *----------------last changed: --------------------------------Sa 20. Aug 12:47:25 2005----------*/
CdmObjectAdaptor::~CdmObjectAdaptor(  )
{
   // nothing to do here :-)
}

/** +-=---------------------------------------------------------Sa 5. Jun 14:23:41 2010-----------*
 * @method  CdmObjectAdaptor::SetObject                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment With the help of this method it is possible to set the object after creating the      *
 *          adaptor.                                                                              *
 *----------------last changed: --------------------------------Sa 5. Jun 14:23:41 2010-----------*/
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

/** +-=---------------------------------------------------------Mi 21. Sep 18:57:03 2011----------*
 * @method  CdmObjectAdaptor::ValidateObjectData             // protected, virtual                *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Sep 18:57:03 2011----------*/
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


/** +-=---------------------------------------------------------Mo 12. Okt 18:22:23 2009----------*
 * @method  CdmObjectAdaptor::DeleteObject                   // public                            *
 * @return  bool                                             //                                   *
 * @comment This method sets the deleted flag of the object.                                      *
 *----------------last changed: --------------------------------Mo 12. Okt 18:22:23 2009----------*/
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

/** +-=---------------------------------------------------------Do 13. Sep 10:21:00 2012----------*
 * @method  CdmObjectAdaptor::GetObjectContainer                  // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 10:21:00 2012----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:37:40 2013----------*
 * @method  CdmObjectAdaptor::IsValid                        // public, const                     *
 * @return  bool                                             //                                   *
 * @comment returns if this adaptor is valid or not.                                              *
 *----------------last changed: --------------------------------So 10. Feb 09:37:40 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:37:50 2013----------*
 * @method  CdmObjectAdaptor::GetKeyname                     // public, const                     *
 * @return  QString                                          //                                   *
 * @comment This method returns the caption of the object.                                        *
 *----------------last changed: --------------------------------So 10. Feb 09:37:50 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:37:59 2013----------*
 * @method  CdmObjectAdaptor::GetCaption                     // public, const                     *
 * @return  QString                                          //                                   *
 * @comment This method returns the caption of the object.                                        *
 *----------------last changed: --------------------------------So 10. Feb 09:37:59 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:38:10 2013----------*
 * @method  CdmObjectAdaptor::GetObjectId                    // public, const                     *
 * @return  long                                             //                                   *
 * @comment returns the object id of this obejct.                                                 *
 *----------------last changed: --------------------------------So 10. Feb 09:38:10 2013----------*/
long CdmObjectAdaptor::GetObjectId() const
{
   return m_lObjectId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:38:24 2013----------*
 * @method  CdmObjectAdaptor::GetString                      // public, const                     *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:38:24 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:38:41 2013----------*
 * @method  CdmObjectAdaptor::GetUser                        // public, const                     *
 * @return  CumUser*                                         //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:38:41 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:38:49 2013----------*
 * @method  CdmObjectAdaptor::GetTime                        // public, const                     *
 * @return  QTime                                            //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:38:49 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:38:57 2013----------*
 * @method  CdmObjectAdaptor::GetDate                        // public, const                     *
 * @return  QDate                                            //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:38:57 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:39:05 2013----------*
 * @method  CdmObjectAdaptor::GetDateTime                    // public, const                     *
 * @return  QDateTime                                        //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:39:05 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:39:13 2013----------*
 * @method  CdmObjectAdaptor::GetFloat                       // public, const                     *
 * @return  float                                            //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:39:13 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:39:22 2013----------*
 * @method  CdmObjectAdaptor::GetBool                        // public, const                     *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:39:22 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:39:40 2013----------*
 * @method  CdmObjectAdaptor::GetInt                         // public, const                     *
 * @return  int                                              //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:39:40 2013----------*/
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

/** +-=---------------------------------------------------------Mo 31. Dez 11:01:49 2007----------*
 * @method  CdmObjectAdaptor::GetValue                       // public                            *
 * @return  CdmValue*                                        //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment returns the valueobject.                                                              *
 *----------------last changed: Wolfgang Graßhof----------------Mo 31. Dez 11:01:49 2007----------*/
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

CdmValue* CdmObjectAdaptor::GetEventValue(QString p_qstrKeyname, CdmObject* p_pCdmEventObject)
{
    CdmValue* pCdmValue = nullptr;

    if (CHKPTR(p_pCdmEventObject))
    {
        pCdmValue = p_pCdmEventObject->GetEventValue(p_qstrKeyname, p_pCdmEventObject);
    }

    return pCdmValue;
}

/** +-=---------------------------------------------------------So 10. Feb 09:40:00 2013----------*
 * @method  CdmObjectAdaptor::GetLong                        // public, const                     *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:40:00 2013----------*/
long CdmObjectAdaptor::GetLong(QString p_qstrKeyname) const
{
   long lRet = 0;
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

/** +-=---------------------------------------------------------So 10. Feb 09:40:09 2013----------*
 * @method  CdmObjectAdaptor::GetDouble                      // public, const                     *
 * @return  double                                           //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:40:09 2013----------*/
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

/** +-=---------------------------------------------------------Di 8. Feb 16:20:28 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:20:28 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, QString p_qstrValue)
{
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_qstrValue);
   }
}

/** +-=---------------------------------------------------------Di 14. Jun 16:42:01 2011----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CumUser* p_pCumUser                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Jun 16:42:01 2011----------*/
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

/** +-=---------------------------------------------------------Di 8. Feb 16:20:34 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QDate p_qdDate                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:20:34 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, QDate p_qdDate)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_qdDate);
   }
}

/** +-=---------------------------------------------------------Di 8. Feb 16:20:40 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QDateTime p_qdtDateTime                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:20:40 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, QDateTime p_qdtDateTime)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_qdtDateTime);
   }
}


/** +-=---------------------------------------------------------Di 8. Feb 16:20:46 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qqstrkeyname                           //                                   *
 * @param   QTime p_qtTime                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:20:46 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qqstrkeyname, QTime p_qtTime)
{
   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qqstrkeyname, p_qtTime);
   }
}



/** +-=---------------------------------------------------------Di 8. Feb 16:20:51 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   float p_fValue                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:20:51 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, float p_fValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_fValue);
   }
}

/** +-=---------------------------------------------------------Di 8. Feb 16:20:57 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:20:57 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, double p_dValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_dValue);
   }
}


/** +-=---------------------------------------------------------Di 8. Feb 16:21:04 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:04 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, int p_iValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_iValue);
   }
}

/** +-=---------------------------------------------------------Di 8. Feb 16:21:15 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   long p_lValue                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:15 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, long p_lValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_lValue);
   }
}



/** +-=---------------------------------------------------------Di 8. Feb 16:21:21 2011-----------*
 * @method  CdmObjectAdaptor::SetValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool p_bValue                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:21 2011-----------*/
void CdmObjectAdaptor::SetValue(QString p_qstrKeyname, bool p_bValue)
{

   CdmObject* pCdmObject = GetObject();

   if(CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue(p_qstrKeyname, p_bValue);
   }
}

/** +-=---------------------------------------------------------Di 8. Feb 16:21:27 2011-----------*
 * @method  CdmObjectAdaptor::GetObjectRefValue              // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:27 2011-----------*/
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

/** +-=---------------------------------------------------------Di 8. Feb 16:21:35 2011-----------*
 * @method  CdmObjectAdaptor::GetObjectRef                   // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:35 2011-----------*/
long CdmObjectAdaptor::GetObjectRef(QString p_qstrKeyname)
{
   long lObjectRef = 0;
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

/** +-=---------------------------------------------------------Di 8. Feb 16:21:42 2011-----------*
 * @method  CdmObjectAdaptor::GetObjectListRef               // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:42 2011-----------*/
long CdmObjectAdaptor::GetContainerRef(QString p_qstrKeyname)
{
   long lRet = 0;
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

/** +-=---------------------------------------------------------Di 8. Feb 16:21:48 2011-----------*
 * @method  CdmObjectAdaptor::SetContainerRefValue          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:48 2011-----------*/
void CdmObjectAdaptor::SetContainerRefValue(QString p_qstrKeyname, long p_lObjectListId)
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

/** +-=---------------------------------------------------------Di 8. Feb 16:21:56 2011-----------*
 * @method  CdmObjectAdaptor::SetContainerRefValue          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:21:56 2011-----------*/
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
            ((CdmValueContainerRef*)pCdmValue)->SetValue((long)0);
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

/** +-=---------------------------------------------------------Di 8. Feb 16:22:11 2011-----------*
 * @method  CdmObjectAdaptor::SetObjectRefValue              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Feb 16:22:11 2011-----------*/
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

/** +-=---------------------------------------------------------Di 8. Feb 16:22:17 2011-----------*
 * @method  CdmObjectAdaptor::GetContainerRefValue          // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method returns the objectlistvalueref CdmObjectContainer* of a given value            *
 *----------------last changed: --------------------------------Di 8. Feb 16:22:17 2011-----------*/
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

/** +-=---------------------------------------------------------Do 25. Mai 12:56:27 2006----------*
 * @method  CdmObjectAdaptor::GetEmptyContainerRefValue     // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method returns the objectlistvalueref CdmObjectContainer* of a given value            *
 *----------------last changed: Wolfgang Graßhof----------------Do 25. Mai 12:56:27 2006----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:41:18 2013----------*
 * @method  CdmObjectAdaptor::GetDisplayString               // public, const                     *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method returns the displaystring to an value.                                    *
 *----------------last changed: --------------------------------So 10. Feb 09:41:18 2013----------*/
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

/** +-=---------------------------------------------------------Mo 18. Aug 11:59:48 2008----------*
 * @method  CdmObjectAdaptor::SetBinDocNewFilename           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Aug 11:59:48 2008----------*/
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

/** +-=---------------------------------------------------------Mo 18. Aug 12:09:50 2008----------*
 * @method  CdmObjectAdaptor::GetBinDocCurrentFilename       // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment returns the current filename of the bindoc for open the file.                         *
 *----------------last changed: --------------------------------Mo 18. Aug 12:09:50 2008----------*/
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

/** +-=---------------------------------------------------------Mo 18. Aug 12:15:20 2008----------*
 * @method  CdmObjectAdaptor::OpenBinDoc                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method opens the bindoc.                                                         *
 *----------------last changed: --------------------------------Mo 18. Aug 12:15:20 2008----------*/
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

/** +-=---------------------------------------------------------Di 28. Apr 18:28:30 2009----------*
 * @method  CdmObjectAdaptor::SaveBinDocTo                   // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrPath                               //                                   *
 * @comment savesthe specified bindoc in the specified path. It does not oberride files.          *
 *----------------last changed: --------------------------------Di 28. Apr 18:28:30 2009----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:41:46 2013----------*
 * @method  CdmObjectAdaptor::GetStringList                  // public, const                     *
 * @return  QList<QString>                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:41:46 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:41:53 2013----------*
 * @method  CdmObjectAdaptor::GetDoubleList                  // public, const                     *
 * @return  QList<double>                              //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:41:53 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:42:02 2013----------*
 * @method  CdmObjectAdaptor::GetIntList                     // public, const                     *
 * @return  QList<int>                                 //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:42:02 2013----------*/
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

/** +-=---------------------------------------------------------Do 10. Nov 16:14:22 2011----------*
 * @method  CdmObjectAdaptor::GetListObjects                 // public                            *
 * @return  QList<CdmObject*>                          //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:14:22 2011----------*/
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

/** +-=---------------------------------------------------------Do 25. Okt 13:54:43 2012----------*
 * @method  CdmObjectAdaptor::SetListObjects                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QList<CdmObject*> p_qlObjects              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 13:54:43 2012----------*/
void CdmObjectAdaptor::SetListObjects(QString p_qstrMember, QList<CdmObject*> p_qlObjects)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListObjects)
   {
      CdmValueListObjects* pCdmValueList = (CdmValueListObjects*)pCdmValue;
      pCdmValueList->SetList(p_qlObjects);
   }
}

/** +-=---------------------------------------------------------Di 14. Jun 10:02:51 2011----------*
 * @method  CdmObjectAdaptor::AddStringListValue             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Jun 10:02:51 2011----------*/
void CdmObjectAdaptor::AddStringListValue(QString p_qstrMember, QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      pCdmValueList->AddValue(p_qstrValue);
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:18:34 2012----------*
 * @method  CdmObjectAdaptor::SetStringList                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QList<QString> p_rqstrlList                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:18:34 2012----------*/
void CdmObjectAdaptor::SetStringList(QString p_qstrMember, QList<QString> p_rqstrlList)
{

   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      pCdmValueList->SetList(p_rqstrlList);
   }
}

/** +-=---------------------------------------------------------Di 28. Mai 14:35:56 2013----------*
 * @method  CdmObjectAdaptor::SetIntList                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QList<int> p_rqstrlList                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Mai 14:35:56 2013----------*/
void CdmObjectAdaptor::SetIntList(QString p_qstrMember, QList<int> p_rqstrlList)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      pCdmValueList->SetList(p_rqstrlList);
   }
}

/** +-=---------------------------------------------------------Di 28. Mai 14:36:26 2013----------*
 * @method  CdmObjectAdaptor::SetDoubleList                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QList<double> p_rqstrlList                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Mai 14:36:26 2013----------*/
void CdmObjectAdaptor::SetDoubleList(QString p_qstrMember, QList<double> p_rqstrlList)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      pCdmValueList->SetList(p_rqstrlList);
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 16:31:36 2011----------*
 * @method  CdmObjectAdaptor::AddDoubleListValue             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:31:36 2011----------*/
void CdmObjectAdaptor::AddDoubleListValue(QString p_qstrMember, double p_dValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      pCdmValueList->AddValue(p_dValue);
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 16:30:58 2011----------*
 * @method  CdmObjectAdaptor::AddIntListValue                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:30:58 2011----------*/
void CdmObjectAdaptor::AddIntListValue(QString p_qstrMember, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      pCdmValueList->AddValue(p_iValue);
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 16:32:13 2011----------*
 * @method  CdmObjectAdaptor::AddListObjectsValue            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:32:13 2011----------*/
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

/** +-=---------------------------------------------------------Di 14. Jun 10:04:56 2011----------*
 * @method  CdmObjectAdaptor::RemoveStringListValue          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Jun 10:04:56 2011----------*/
void CdmObjectAdaptor::RemoveStringListValue(QString p_qstrMember, QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListString)
   {
      CdmValueListString* pCdmValueList = (CdmValueListString*)pCdmValue;
      pCdmValueList->RemoveValue(p_qstrValue);
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 16:39:29 2011----------*
 * @method  CdmObjectAdaptor::RemoveDoubleListValue          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:39:29 2011----------*/
void CdmObjectAdaptor::RemoveDoubleListValue(QString p_qstrMember, double p_dValue)
{

   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListDouble)
   {
      CdmValueListDouble* pCdmValueList = (CdmValueListDouble*)pCdmValue;
      pCdmValueList->RemoveValue(p_dValue);
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 16:40:08 2011----------*
 * @method  CdmObjectAdaptor::RemoveIntListValue             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:40:08 2011----------*/
void CdmObjectAdaptor::RemoveIntListValue(QString p_qstrMember, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueListInt)
   {
      CdmValueListInt* pCdmValueList = (CdmValueListInt*)pCdmValue;
      pCdmValueList->RemoveValue(p_iValue);
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 16:40:51 2011----------*
 * @method  CdmObjectAdaptor::RemoveListObjectsValue         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 16:40:51 2011----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:42:51 2013----------*
 * @method  CdmObjectAdaptor::GetStringStringDict            // public, const                     *
 * @return  QMap<QString, QString>                           //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:42:51 2013----------*/
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

/** +-=---------------------------------------------------------Mi 12. Sep 11:54:42 2012----------*
 * @method  CdmObjectAdaptor::SetStringStringDict            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QMap<QString, QString> p_qmValue                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 11:54:42 2012----------*/
void CdmObjectAdaptor::SetStringStringDict(QString p_qstrValue, QMap<QString, QString> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
   {
      CdmValueDictStringString* pCdmValueDict = (CdmValueDictStringString*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

/** +-=---------------------------------------------------------So 10. Feb 09:43:11 2013----------*
 * @method  CdmObjectAdaptor::GetStringIntDict               // public, const                     *
 * @return  QMap<QString, int>                               //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:43:11 2013----------*/
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

/** +-=---------------------------------------------------------Mi 12. Sep 13:38:07 2012----------*
 * @method  CdmObjectAdaptor::SetStringIntDict               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QMap<QString, int> p_qmValue                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 13:38:07 2012----------*/
void CdmObjectAdaptor::SetStringIntDict(QString p_qstrValue, QMap<QString, int> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

/** +-=---------------------------------------------------------Di 28. Mai 14:38:57 2013----------*
 * @method  CdmObjectAdaptor::SetStringDoubleDict            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QMap<QString, double> p_qmValue                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Mai 14:38:57 2013----------*/
void CdmObjectAdaptor::SetStringDoubleDict(QString p_qstrValue, QMap<QString, double> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringDouble)
   {
      CdmValueDictStringDouble* pCdmValueDict = (CdmValueDictStringDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

/** +-=---------------------------------------------------------Di 28. Mai 14:39:28 2013----------*
 * @method  CdmObjectAdaptor::SetIntDoubleDict               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QMap<int, double> p_qmValue                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Mai 14:39:28 2013----------*/
void CdmObjectAdaptor::SetIntDoubleDict(QString p_qstrValue, QMap<int, double> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

/** +-=---------------------------------------------------------Di 28. Mai 14:39:52 2013----------*
 * @method  CdmObjectAdaptor::SetIntIntDict                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QMap<int, int> p_qmValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Mai 14:39:52 2013----------*/
void CdmObjectAdaptor::SetIntIntDict(QString p_qstrValue, QMap<int, int> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

/** +-=---------------------------------------------------------Di 28. Mai 14:41:45 2013----------*
 * @method  CdmObjectAdaptor::SetIntStringDict               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QMap<int, QString> p_qmValue                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Mai 14:41:45 2013----------*/
void CdmObjectAdaptor::SetIntStringDict(QString p_qstrValue, QMap<int, QString> p_qmValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrValue);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      pCdmValueDict->SetValue(p_qmValue);
   }
}

/** +-=---------------------------------------------------------So 10. Feb 09:43:23 2013----------*
 * @method  CdmObjectAdaptor::GetStringDoubleDict            // public, const                     *
 * @return  QMap<QString, double>                            //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:43:23 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:43:33 2013----------*
 * @method  CdmObjectAdaptor::GetIntStringDict               // public, const                     *
 * @return  QMap<int, QString>                               //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:43:33 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:43:53 2013----------*
 * @method  CdmObjectAdaptor::GetIntIntDict                  // public, const                     *
 * @return  QMap<int, int>                                   //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:43:53 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:44:01 2013----------*
 * @method  CdmObjectAdaptor::GetIntDoubleDict               // public, const                     *
 * @return  QMap<int, double>                                //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:44:01 2013----------*/
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

/** +-=---------------------------------------------------------Mo 23. Jan 14:41:12 2012----------*
 * @method  CdmObjectAdaptor::AddStringStringEntry           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:41:12 2012----------*/
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

/** +-=---------------------------------------------------------Mo 23. Jan 14:29:56 2012----------*
 * @method  CdmObjectAdaptor::AddStringIntEntry              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:29:56 2012----------*/
void CdmObjectAdaptor::AddStringIntEntry(QString p_qstrMember, QString p_qstrKey, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      pCdmValueDict->SetValue(p_qstrKey, p_iValue);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:30:39 2012----------*
 * @method  CdmObjectAdaptor::AddStringDoubleEntry           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:30:39 2012----------*/
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

/** +-=---------------------------------------------------------Mo 23. Jan 14:32:42 2012----------*
 * @method  CdmObjectAdaptor::AddIntStringEntry              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:32:42 2012----------*/
void CdmObjectAdaptor::AddIntStringEntry(QString p_qstrMember, int p_iKey, QString p_qstrValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      pCdmValueDict->SetValue(p_iKey, p_qstrValue);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:32:20 2012----------*
 * @method  CdmObjectAdaptor::AddIntIntEntry                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:32:20 2012----------*/
void CdmObjectAdaptor::AddIntIntEntry(QString p_qstrMember, int p_iKey, int p_iValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      pCdmValueDict->SetValue(p_iKey, p_iValue);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:31:59 2012----------*
 * @method  CdmObjectAdaptor::AddIntDoubleEntry              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:31:59 2012----------*/
void CdmObjectAdaptor::AddIntDoubleEntry(QString p_qstrMember, int p_iKey, double p_dValue)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      pCdmValueDict->SetValue(p_iKey, p_dValue);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:39:58 2012----------*
 * @method  CdmObjectAdaptor::RemoveStringStringEntry        // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:39:58 2012----------*/
void CdmObjectAdaptor::RemoveStringStringEntry(QString p_qstrMember, QString p_qstrKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
   {
      CdmValueDictStringString* pCdmValueDict = (CdmValueDictStringString*)pCdmValue;
      pCdmValueDict->RemoveValue(p_qstrKey);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:39:31 2012----------*
 * @method  CdmObjectAdaptor::RemoveStringIntEntry           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:39:31 2012----------*/
void CdmObjectAdaptor::RemoveStringIntEntry(QString p_qstrMember, QString p_qstrKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringInt)
   {
      CdmValueDictStringInt* pCdmValueDict = (CdmValueDictStringInt*)pCdmValue;
      pCdmValueDict->RemoveValue(p_qstrKey);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:39:02 2012----------*
 * @method  CdmObjectAdaptor::RemoveStringDoubleEntry        // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:39:02 2012----------*/
void CdmObjectAdaptor::RemoveStringDoubleEntry(QString p_qstrMember, QString p_qstrKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringDouble)
   {
      CdmValueDictStringDouble* pCdmValueDict = (CdmValueDictStringDouble*)pCdmValue;
      pCdmValueDict->RemoveValue(p_qstrKey);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:38:38 2012----------*
 * @method  CdmObjectAdaptor::RemoveIntStringEntry           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:38:38 2012----------*/
void CdmObjectAdaptor::RemoveIntStringEntry(QString p_qstrMember, int p_iKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
   {
      CdmValueDictIntString* pCdmValueDict = (CdmValueDictIntString*)pCdmValue;
      pCdmValueDict->RemoveValue(p_iKey);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:38:12 2012----------*
 * @method  CdmObjectAdaptor::RemoveIntIntEntry              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:38:12 2012----------*/
void CdmObjectAdaptor::RemoveIntIntEntry(QString p_qstrMember, int p_iKey)
{
   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntInt)
   {
      CdmValueDictIntInt* pCdmValueDict = (CdmValueDictIntInt*)pCdmValue;
      pCdmValueDict->RemoveValue(p_iKey);
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 14:37:32 2012----------*
 * @method  CdmObjectAdaptor::RemoveIntDoubleEntry           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iKey                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jan 14:37:32 2012----------*/
void CdmObjectAdaptor::RemoveIntDoubleEntry(QString p_qstrMember, int p_iKey)
{

   CdmValue* pCdmValue = GetValue(p_qstrMember);

   if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntDouble)
   {
      CdmValueDictIntDouble* pCdmValueDict = (CdmValueDictIntDouble*)pCdmValue;
      pCdmValueDict->RemoveValue(p_iKey);
   }
}

/** +-=---------------------------------------------------------So 19. Nov 16:36:24 2006----------*
 * @method  CdmObjectAdaptor::operator=                      // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmObjectAdaptor& p_rCdmObjectAdaptor      //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 19. Nov 16:36:24 2006----------*/
void CdmObjectAdaptor::operator=(const CdmObjectAdaptor& p_rCdmObjectAdaptor)
{
   m_lDbId = p_rCdmObjectAdaptor.m_lDbId;
   m_lObjectId = p_rCdmObjectAdaptor.m_lObjectId;
   m_lObjectListId = p_rCdmObjectAdaptor.m_lObjectListId;
}

/** +-=---------------------------------------------------------So 10. Feb 09:44:23 2013----------*
 * @method  CdmObjectAdaptor::IsTypeOf                       // public, const                     *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrType                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:44:23 2013----------*/
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

/** +-=---------------------------------------------------------Do 15. Dez 18:24:20 2011----------*
 * @method  CdmObjectAdaptor::SetDeleted                     // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 15. Dez 18:24:20 2011----------*/
void CdmObjectAdaptor::SetDeleted()
{
   CdmObject* pCdmObject = GetObject();

   if (pCdmObject)
   {
      pCdmObject->SetDeleted();
   }
}

/** +-=---------------------------------------------------------So 10. Feb 09:44:37 2013----------*
 * @method  CdmObjectAdaptor::GetVariant                     // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:44:37 2013----------*/
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

/** +-=---------------------------------------------------------Mo 4. Jun 16:23:07 2012-----------*
 * @method  CdmObjectAdaptor::SetVariant                     // public                            *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @param   QString p_qstrOLKeyname                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 16:23:07 2012-----------*/
void CdmObjectAdaptor::SetVariant(QVariant& p_rqVariant, QString p_qstrOLKeyname)
{
   QVariantMap qHash = p_rqVariant.toMap();
   CdmObjectContainer* pContainer = GetObjectContainer(p_qstrOLKeyname);

   if (CHKPTR(pContainer))
   {
      long lObjectId = qHash["ObjectId"].toInt();
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

/** +-=---------------------------------------------------------Mo 4. Jun 16:37:16 2012-----------*
 * @method  CdmObjectAdaptor::UpdateObject                   // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqVariant                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 16:37:16 2012-----------*/
void CdmObjectAdaptor::UpdateObject(QVariantMap& p_rqVariant)
{
   CdmObject* pCdmObject = GetObject();

   if (CHKPTR(pCdmObject))
   {
      QVariantMap qvHash = p_rqVariant["Values"].toMap();
   }
}

/** +-=---------------------------------------------------------Mo 4. Jun 16:18:23 2012-----------*
 * @method  CdmObjectAdaptor::GetObjectContainer                  // public, static                    *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 16:18:23 2012-----------*/
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

/** +-=---------------------------------------------------------So 14. Okt 09:45:03 2012----------*
 * @method  CdmObjectAdaptor::GetParentObject                // public                            *
 * @return  CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Okt 09:45:03 2012----------*/
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

/** +-=---------------------------------------------------------So 14. Okt 09:45:19 2012----------*
 * @method  CdmObjectAdaptor::GetParentObjectId              // public                            *
 * @return  long                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Okt 09:45:19 2012----------*/
long CdmObjectAdaptor::GetParentObjectId()
{
   long lRet = 0;
   CdmObject* pCdmObject = GetObject();
   
   if (pCdmObject)
   {
      lRet = pCdmObject->GetParentId();
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mo 11. Feb 16:37:43 2013----------*
 * @method  CdmObjectAdaptor::Execute                        // public                            *
 * @return  QVariant                                         //                                   *
 * @param   QString p_qstrFunction                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 16:37:43 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 09:33:36 2013----------*
 * @method  CdmObject::GetVariantGraph                       // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:33:36 2013----------*/
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
                    long lId = pObjectlist->GetId();
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

