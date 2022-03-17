// System and QT Includes

// WMS Commons Includes
#include "wmsdefines.h"

// own Includes
#include "CdmValue.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CdmObjectContainer.h"
#include "CdmValueEnum.h"
#include "CdmValueUser.h"
#include "CwmsJson.h"
#include "CdmValueUserGroup.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueBool.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueTime.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueListString.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmObject.h"
#include "CdmValueListObjects.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringString.h"
#include "CdmMember.h"
#include "CsaMember.h"
#include "CsaObjectContainer.h"
#include "CsaObject.h"
#include "CsaFactory.h"
#include "CsaValue.h"

CsaValue::CsaValue(CdmValue *p_pValue, QObject* parent)
   : CsaModelElement(p_pValue, parent)
{
}

CsaValue::~CsaValue()
{
}

QString CsaValue::toString()
{
   return getInternals()->GetValueAsString();
}

QVariant CsaValue::getValueReference()
{
    QVariant qvValue;

    CdmValue* pCdmValue = getInternals();

    if (CHKPTR(pCdmValue))
    {
       // ToDo dependent on valuetype doing the right
       if (pCdmValue->GetValueType() == eDmValueObjectRef)
       {
          CdmObject* pObject = static_cast<CdmValueObjectRef*>(pCdmValue)->GetObject();

          if (pObject)
          {
              qvValue.setValue(dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pObject));
          }
       }
       else if (pCdmValue->GetValueType() == eDmValueContainerRef)
       {
          CdmObjectContainer* pContainer = static_cast<CdmValueContainerRef*>(pCdmValue)->GetContainer();

          if (pContainer)
          {
              qvValue.setValue(dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pContainer));
          }
       }
    }

    return qvValue;
}

void CsaValue::setValueReference(QObject* p_pObject)
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueObjectRef)
      {
         CsaObject* pObject = dynamic_cast<CsaObject*>(p_pObject);

         if (pObject)
         {
            ((CdmValueObjectRef*)pValue)->SetValue(static_cast<CdmObject*>(pObject->getInternals()));
         }
         else
         {
            ((CdmValueObjectRef*)pValue)->SetValue(static_cast<CdmObject*>(nullptr));
         }

      }
      else if (pValue->GetValueType() == eDmValueContainerRef)
      {
         CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*>(p_pObject);

         if (pContainer)
         {
            ((CdmValueContainerRef*)pValue)->SetValue(static_cast<CdmObjectContainer*>(pContainer->getInternals()));
         }
         else
         {
            ((CdmValueContainerRef*)pValue)->SetValue(static_cast<CdmObjectContainer*>(nullptr));
         }
      }
   }
}

QVariant CsaValue::getValue()
{

   QVariant qvValue;
   CdmValue* pCdmValue = getInternals();

   if (CHKPTR(pCdmValue))
   {
      // ToDo dependent on valuetype doing the right
      if (pCdmValue->GetValueType() == eDmValueObjectRef ||
          pCdmValue->GetValueType() == eDmValueContainerRef)
      {
         qvValue.setValue(this);
      }
      else
      {
         qvValue = pCdmValue->GetValueVariant();
      }
   }

   return qvValue;
}

EdmValueType CsaValue::getType()
{
   EdmValueType eType = eDmValueNone;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      eType = pValue->GetValueType();
   }

   return eType;
}

bool CsaValue::getValueAsBool()
{
   return getValue().toBool();
}

void CsaValue::setValueBool(bool p_bValue)
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBool)
   {
      (static_cast<CdmValueBool*>(pValue))->SetValue(p_bValue);
   }
}

void CsaValue::setValue(QVariant p_qvValue)
{
   if (CHKPTR(getInternals()))
   {
      getInternals()->SetValueVariant(p_qvValue);
   }
}

bool CsaValue::isDate()
{
   bool bRet = false;

   if (CHKPTR(getInternals()))
   {
      bRet = (getInternals()->GetValueType() == eDmValueDate);
   }

   return bRet;
}

bool CsaValue::isTime()
{
   bool bRet = false;

   if (CHKPTR(getInternals()))
   {
      bRet = (getInternals()->GetValueType() == eDmValueTime);
   }

   return bRet;
}

bool CsaValue::isDateTime()
{
   bool bRet = false;

   if (CHKPTR(getInternals()))
   {
      bRet = (getInternals()->GetValueType() == eDmValueDateTime);
   }

   return bRet;
}

void CsaValue::setValueDate(QDate p_qdDate)
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueDate)
   {
      (static_cast<CdmValueDate*>(pValue))->SetValue(p_qdDate);
   }
}

void CsaValue::setValueDateTime(QDateTime p_qdtDateTime)
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueDateTime)
   {
      (static_cast<CdmValueDateTime*>(pValue))->SetValue(p_qdtDateTime);
   }
}

void CsaValue::setValueTime(QTime p_qtTime)
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueTime)
   {
      (static_cast<CdmValueTime*>(pValue))->SetValue(p_qtTime);
   }
}

QTime CsaValue::getValueTime()
{
   QTime qtTime;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueTime)
   {
      qtTime = (static_cast<CdmValueTime*>(pValue))->GetValue();
   }

   return qtTime;
}

QDate CsaValue::getValueDate()
{
   QDate qdDate;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueDate)
   {
      qdDate = (static_cast<CdmValueDate*>(pValue))->GetValue();
   }

   return qdDate;
}

QDateTime CsaValue::getValueDateTime()
{
   QDateTime qdDateTime;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueDateTime)
   {
      qdDateTime = (static_cast<CdmValueDateTime*>(pValue))->GetValue();
   }

   return qdDateTime;
}


void CsaValue::setValueObject(CsaValue* p_pValue)
{
   setElement(p_pValue->getInternals());
}

QString CsaValue::getBinDocFileName()
{
   QString qstrFilename;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBinaryDocument)
   {
      qstrFilename = (static_cast<CdmValueBinaryDocument*>(pValue))->GetValueAsString();
   }

   return qstrFilename;
}

void CsaValue::openBinDoc()
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBinaryDocument)
   {
      (static_cast<CdmValueBinaryDocument*>(pValue))->ExecuteFile();
   }
}

QObject *CsaValue::getMember()
{
   return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(const_cast<CdmMember*>(getInternals()->GetMember()));
}

bool CsaValue::isReadOnly()
{
   bool bRet = false;
   const CdmMember* pMember = getInternals()->GetMember();

   if (CHKPTR(pMember))
   {
      if (pMember->GetAccessMode() == eDmMemberAccessProtected)
      {
         bRet = true;
      }
      else
      {
         CdmRights& cCdmRights = (const_cast<CdmMember*>(pMember))->GetRights();

         if (!cCdmRights.HasCurrentUserWriteAccess())
         {
            bRet = true;
         }
      }
   }

   return bRet;
}

QString CsaValue::getSelectionModel()
{
   QString qstrModel = "import QtQuick 2.0; ListModel { id: selectionModel; ";

   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueUser)
      {
         qstrModel += getUserList();
      }
      else if (pValue->GetValueType() == eDmValueUserGroup)
      {
         qstrModel += getUserGroupList();
      }
      else if (pValue->GetValueType() == eDmValueEnum)
      {
         qstrModel += getEnumList();
      }
      else if (pValue->GetValueType() == eDmValueListString)
      {
         qstrModel += getListStringsQml();
      }
      else if (pValue->GetValueType() == eDmValueListInt)
      {
         qstrModel += getListIntsQml();
      }
      else if (pValue->GetValueType() == eDmValueListDouble)
      {
         qstrModel += getListDoublesQml();
      }
      else if (pValue->GetValueType() == eDmValueListObjects)
      {
         qstrModel += getListObjectsEntries();
      }
   }

   qstrModel += "}";

   return qstrModel;
}

void CsaValue::setSelectionValue(int p_iId)
{
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueUser)
      {
         static_cast<CdmValueUser*>(pValue)->SetValue(p_iId);
      }
      else if (pValue->GetValueType() == eDmValueUserGroup)
      {
         static_cast<CdmValueUserGroup*>(pValue)->SetValue(p_iId);
      }
      else if (pValue->GetValueType() == eDmValueEnum)
      {
         static_cast<CdmValueEnum*>(pValue)->SetValue(p_iId);
      }
   }
}

int CsaValue::getSelectionValueIndex()
{
   int iIndex = 0;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueUser)
      {
         int iId = static_cast<CdmValueUser*>(pValue)->GetValue();
         iIndex = getUserListIndex(iId);
      }
      else if (pValue->GetValueType() == eDmValueUserGroup)
      {
         int iId = static_cast<CdmValueUserGroup*>(pValue)->GetValue();
         iIndex = getUserGroupListIndex(iId);

      }
      else if (pValue->GetValueType() == eDmValueEnum)
      {
         int iId = static_cast<CdmValueEnum*>(pValue)->GetValue();
         iIndex = getEnumListIndex(iId);
      }
   }

   return iIndex;
}

int CsaValue::getUserListIndex(int p_iId)
{
   int iIndex = 0;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (CHKPTR(pCumUserManager))
      {
         QList<CumUser*> qllUsers;
         pCumUserManager->GetUserListUnmanaged(qllUsers);

         QList<CumUser*>::iterator qllIt = qllUsers.begin();
         QList<CumUser*>::iterator qllItEnd = qllUsers.end();
         int iCounter = 0;

         for (; qllIt != qllItEnd; ++qllIt)
         {
            ++iCounter; // must be added before access because the first element is a "nullptr"nothing selected" element in combobox;
            CumUser* pCumUser = *qllIt;

            if (CHKPTR(pCumUser) && pCumUser->GetId() == p_iId)
            {
               iIndex = iCounter;
               break;
            }
         }
      }
   }

   return iIndex;
}

int CsaValue::getUserGroupListIndex(int p_iId)
{
   int iIndex = 0;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (CHKPTR(pCumUserManager))
      {
         QList<CumUserGroup*> qllUserGroups;
         pCumUserManager->GetUserGroupList(qllUserGroups);

         QList<CumUserGroup*>::iterator qllIt = qllUserGroups.begin();
         QList<CumUserGroup*>::iterator qllItEnd = qllUserGroups.end();
         int iCounter = 0;

         for (; qllIt != qllItEnd; ++qllIt)
         {
            ++iCounter; // must be added before access because the first element is a "nullptr"nothing selected" element in combobox;
            CumUserGroup* pCumUserGroup = *qllIt;

            if (CHKPTR(pCumUserGroup) && pCumUserGroup->GetId() == p_iId)
            {
               iIndex = iCounter;
               break;
            }
         }
      }
   }

   return iIndex;
}

int CsaValue::getEnumListIndex(int p_iId)
{
   return p_iId + 1;
}

QString CsaValue::getUserList()
{
   QString qstrModel;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (CHKPTR(pCumUserManager))
      {
         QString qstrElementTemplate = getListElementTemplate();
         qstrModel += QString(qstrElementTemplate).arg("-").arg(-1);

         QList<CumUser*> qllUsers;
         pCumUserManager->GetUserListUnmanaged(qllUsers);

         QList<CumUser*>::iterator qllIt = qllUsers.begin();
         QList<CumUser*>::iterator qllItEnd = qllUsers.end();

         for (; qllIt != qllItEnd; ++qllIt)
         {
            CumUser* pCumUser = *qllIt;

            if (CHKPTR(pCumUser))
            {
               qstrModel += QString(qstrElementTemplate).arg(pCumUser->GetFirstName() + " " + pCumUser->GetLastName()).arg(pCumUser->GetId());
            }
         }
      }
   }

   return qstrModel;
}

QString CsaValue::getListElementTemplate()
{
   return "ListElement {name: \"%1\";  idValue:%2;}";
}

QString CsaValue::getUserGroupList()
{
   QString qstrModel;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (CHKPTR(pCumUserManager))
      {
         QString qstrElementTemplate = getListElementTemplate();
         qstrModel += QString(qstrElementTemplate).arg("-").arg(-1);

         QList<CumUserGroup*> qllUserGroups;
         pCumUserManager->GetUserGroupList(qllUserGroups);

         QList<CumUserGroup*>::iterator qllIt = qllUserGroups.begin();
         QList<CumUserGroup*>::iterator qllItEnd = qllUserGroups.end();

         for (; qllIt != qllItEnd; ++qllIt)
         {
            CumUserGroup* pCumUserGroup = *qllIt;

            if (CHKPTR(pCumUserGroup))
            {
               qstrModel += QString(qstrElementTemplate).arg(pCumUserGroup->GetGroupName()).arg(pCumUserGroup->GetId());
            }
         }
      }
   }

   return qstrModel;
}

QString CsaValue::getListStringsQml()
{
   QString qstrModel;
   QString qstrElementTemplate = getListElementTemplate();
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListString)
   {
      QList<QString> qllValues = static_cast<CdmValueListString*>(pValue)->GetList();
      QList<QString>::iterator qllIt = qllValues.begin();
      QList<QString>::iterator qllItEnd = qllValues.end();
      int iCounter = 0;

      for (; qllIt != qllItEnd; ++qllIt)
      {
         qstrModel += QString(qstrElementTemplate).arg(*qllIt).arg(iCounter);
         ++iCounter;
      }
   }

   return qstrModel;
}

QVariantList CsaValue::getListStrings()
{
   QVariantList qvResults;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListString)
   {
      QList<QString> qllValues = static_cast<CdmValueListString*>(pValue)->GetList();
      QList<QString>::iterator qllIt = qllValues.begin();
      QList<QString>::iterator qllItEnd = qllValues.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         qvResults.append(*qllIt);
      }
   }

   return qvResults;
}

QString CsaValue::getListIntsQml()
{
   QString qstrModel;
   QString qstrElementTemplate = getListElementTemplate();
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListInt)
   {
      QList<int> qllValues = static_cast<CdmValueListInt*>(pValue)->GetList();
      QList<int>::iterator qllIt = qllValues.begin();
      QList<int>::iterator qllItEnd = qllValues.end();
      int iCounter = 0;

      for (; qllIt != qllItEnd; ++qllIt)
      {
         qstrModel += QString(qstrElementTemplate).arg(QString::number(*qllIt)).arg(iCounter);
         ++iCounter;
      }
   }

   return qstrModel;
}

QVariantList CsaValue::getListInts()
{
   QVariantList qvResults;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListInt)
   {
      QList<int> qllValues = static_cast<CdmValueListInt*>(pValue)->GetList();
      QList<int>::iterator qllIt = qllValues.begin();
      QList<int>::iterator qllItEnd = qllValues.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         qvResults.append(*qllIt);
      }
   }

   return qvResults;
}

QString CsaValue::getListDoublesQml()
{
   QString qstrModel;
   QString qstrElementTemplate = getListElementTemplate();
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListDouble)
   {
      QList<double> qllValues = static_cast<CdmValueListDouble*>(pValue)->GetList();
      QList<double>::iterator qllIt = qllValues.begin();
      QList<double>::iterator qllItEnd = qllValues.end();
      int iCounter = 0;

      for (; qllIt != qllItEnd; ++qllIt)
      {
         qstrModel += QString(qstrElementTemplate).arg(QString::number(*qllIt)).arg(iCounter);
         ++iCounter;
      }
   }

   return qstrModel;
}

QVariantList CsaValue::getListDoubles()
{
   QVariantList qvResult;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueListDouble)
      {
         QList<double> qllValues = static_cast<CdmValueListDouble*>(pValue)->GetList();
         QList<double>::iterator qllIt = qllValues.begin();
         QList<double>::iterator qllItEnd = qllValues.end();

         for (; qllIt != qllItEnd; ++qllIt)
         {
            qvResult.append((*qllIt));
         }
      }
      else
      {
         ERR("Value is not of Type List of Doubles");
      }
   }

   return qvResult;
}

bool CsaValue::hasCurrentUserReadAccess()
{
    CdmValue* pValue = getInternals();

    if (CHKPTR(pValue))
    {
        CdmObject* pObject = const_cast<CdmObject*> (pValue->GetObject());

        if (CHKPTR(pObject))
        {
            CsaObject* pCsaObject = dynamic_cast<CsaObject*>(dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pObject));

            if (CHKPTR(pCsaObject) && pCsaObject->hasCurrentUserReadAccess())
            {
                CsaMember* pCsaMember = dynamic_cast<CsaMember*> (getMember());

                if (CHKPTR(pCsaMember))
                {
                    CdmMember* pMember = pCsaMember->getInternals();

                    if (CHKPTR(pMember))
                    {
                        CdmRights& cRights = pMember->GetRights();
                        return cRights.HasCurrentUserReadAccess();
                    }
                }
            }
        }
    }

    return false;
}

bool CsaValue::hasCurrentUserWriteAccess()
{
    CdmValue* pValue = getInternals();

    if (CHKPTR(pValue))
    {
        CdmObject* pObject = const_cast<CdmObject*> (pValue->GetObject());

        if (CHKPTR(pObject))
        {
            CsaObject* pCsaObject = dynamic_cast<CsaObject*>(dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pObject));

            if (CHKPTR(pCsaObject) && pCsaObject->hasCurrentUserWriteAccess())
            {
                CsaMember* pCsaMember = dynamic_cast<CsaMember*> (getMember());

                if (CHKPTR(pCsaMember))
                {
                    CdmMember* pMember = pCsaMember->getInternals();

                    if (CHKPTR(pMember))
                    {
                        CdmRights& cRights = pMember->GetRights();
                        return cRights.HasCurrentUserWriteAccess();
                    }
                }
            }
        }
    }

    return false;
}

bool CsaValue::addListValue(QString p_qstrValue)
{
   bool bRet = false;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueListString)
      {
         static_cast<CdmValueListString*>(pValue)->AddValue(p_qstrValue);
         bRet = true;
      }
      else if (pValue->GetValueType() == eDmValueListInt)
      {
         static_cast<CdmValueListInt*>(pValue)->AddValue(p_qstrValue.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueListDouble)
      {
         static_cast<CdmValueListDouble*>(pValue)->AddValue(p_qstrValue.toDouble(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueListObjects)
      {
         CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

         if (CHKPTR(pManager))
         {
            CdmObject* pObject = dynamic_cast<CdmObject*>(pManager->GetUriObject(p_qstrValue));
            if (CHKPTR(pObject))
            {
               static_cast<CdmValueListObjects*>(pValue)->AddValue(pObject);
               bRet = true;
            }
         }
      }
   }

   return bRet;
}

bool CsaValue::InsertDictValue(QString p_qstrKey, QString p_qstrValue)
{
   bool bRet = false;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueDictIntDouble)
      {
         static_cast<CdmValueDictIntDouble*>(pValue)->SetValue(p_qstrKey.toInt(&bRet), p_qstrValue.toDouble(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictIntInt)
      {
         static_cast<CdmValueDictIntInt*>(pValue)->SetValue(p_qstrKey.toInt(&bRet), p_qstrValue.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictIntString)
      {
         static_cast<CdmValueDictIntString*>(pValue)->SetValue(p_qstrKey.toInt(&bRet), p_qstrValue);
      }
      else if (pValue->GetValueType() == eDmValueDictStringDouble)
      {
         static_cast<CdmValueDictStringDouble*>(pValue)->SetValue(p_qstrKey, p_qstrValue.toDouble(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictStringInt)
      {
         static_cast<CdmValueDictStringInt*>(pValue)->SetValue(p_qstrKey, p_qstrValue.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictStringString)
      {
         static_cast<CdmValueDictStringString*>(pValue)->SetValue(p_qstrKey, p_qstrValue);
      }
   }

   return bRet;
}

bool CsaValue::removeListValue(QString p_qstrValue)
{
   bool bRet = false;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueListString)
      {
         static_cast<CdmValueListString*>(pValue)->RemoveValue(p_qstrValue);
         bRet = true;
      }
      else if (pValue->GetValueType() == eDmValueListInt)
      {
         static_cast<CdmValueListInt*>(pValue)->RemoveValue(p_qstrValue.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueListDouble)
      {
         static_cast<CdmValueListDouble*>(pValue)->RemoveValue(p_qstrValue.toDouble(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueListObjects)
      {
         CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

         if (CHKPTR(pManager))
         {
            CdmObject* pObject = dynamic_cast<CdmObject*>(pManager->GetUriObject(p_qstrValue));
            if (CHKPTR(pObject))
            {
               static_cast<CdmValueListObjects*>(pValue)->RemoveValue(pObject);
               bRet = true;
            }
         }
      }
   }

   return bRet;
}

bool CsaValue::removeDictValue(QString p_qstrKey)
{
   bool bRet = true;
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueDictIntDouble)
      {
         static_cast<CdmValueDictIntDouble*>(pValue)->RemoveValue(p_qstrKey.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictIntInt)
      {
         static_cast<CdmValueDictIntInt*>(pValue)->RemoveValue(p_qstrKey.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictIntString)
      {
         static_cast<CdmValueDictIntString*>(pValue)->RemoveValue(p_qstrKey.toInt(&bRet));
      }
      else if (pValue->GetValueType() == eDmValueDictStringDouble)
      {
         static_cast<CdmValueDictStringDouble*>(pValue)->RemoveValue(p_qstrKey);
      }
      else if (pValue->GetValueType() == eDmValueDictStringInt)
      {
         static_cast<CdmValueDictStringInt*>(pValue)->RemoveValue(p_qstrKey);
      }
      else if (pValue->GetValueType() == eDmValueDictStringString)
      {
         static_cast<CdmValueDictStringString*>(pValue)->RemoveValue(p_qstrKey);
      }
   }

   return bRet;
}

QVariant CsaValue::getListObjectsEntriesVariant()
{
    QString qstrModel;
    QString qstrElementTemplate = getListElementTemplate();
    CdmValue* pValue = getInternals();

    if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListObjects)
    {
        QList<CdmObject*> qllValues;
        static_cast<CdmValueListObjects*>(pValue)->GetList(qllValues);
        QList<CdmObject*>::iterator qllIt = qllValues.begin();
        QList<CdmObject*>::iterator qllItEnd = qllValues.end();
        int iCounter = 0;

        for (; qllIt != qllItEnd; ++qllIt)
        {
            CdmObject* pObject = *qllIt;

            if (pObject)
            {
                qstrModel += QString(qstrElementTemplate).arg(pObject->GetCaption()).arg("\"" + pObject->GetUri() + "\"");
                ++iCounter;
            }
        }
    }

    return QVariant::fromValue(qstrModel);
}

QString CsaValue::getListObjectsEntries()
{
   QString qstrModel;
   QString qstrElementTemplate = getListElementTemplate();
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueListObjects)
   {
      QList<CdmObject*> qllValues;
      static_cast<CdmValueListObjects*>(pValue)->GetList(qllValues);
      QList<CdmObject*>::iterator qllIt = qllValues.begin();
      QList<CdmObject*>::iterator qllItEnd = qllValues.end();
      int iCounter = 0;

      for (; qllIt != qllItEnd; ++qllIt)
      {
         CdmObject* pObject = *qllIt;

         if (pObject)
         {
            qstrModel += QString(qstrElementTemplate).arg(pObject->GetCaption()).arg("\"" + pObject->GetUri() + "\"");
            ++iCounter;
         }
      }
   }

   return qstrModel;
}

QVariantList CsaValue::getListObjects()
{
   QVariantList qvResult;
   QString qstrElementTemplate = getListElementTemplate();
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      if (pValue->GetValueType() == eDmValueListObjects)
      {
         QList<CdmObject*> qllValues;
         static_cast<CdmValueListObjects*>(pValue)->GetList(qllValues);
         QList<CdmObject*>::iterator qllIt = qllValues.begin();
         QList<CdmObject*>::iterator qllItEnd = qllValues.end();
         CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());

         if (CHKPTR(pFactory))
         {
            for (; qllIt != qllItEnd; ++qllIt)
            {
               CdmObject* pObject = *qllIt;

               if (pObject)
               {
                  CsaLocatedElement* pElement = pFactory->createScriptObject(pObject);

                  if (pElement)
                  {
                     qvResult.append(QVariant::fromValue(pElement));
                  }
               }
            }
         }
      }
      else
      {
         ERR("Wrong Type! Expected ValueListObjects");
      }
   }

   return qvResult;
}

bool CsaValue::isListOfObjects()
{
   return getType() == eDmValueListObjects;
}

QString CsaValue::getEnumList()
{
   QString qstrModel;

   QStringList qstrlSelection = static_cast<CdmValueEnum*>(getInternals())->GetSelectionList();

   QString qstrElementTemplate = getListElementTemplate();
   qstrModel += QString(qstrElementTemplate).arg("-").arg(-1);

   for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
   {
      qstrModel += QString(qstrElementTemplate).arg(qstrlSelection[iCounter]).arg(iCounter);
   }

   return qstrModel;
}

QString CsaValue::getJson()
{
   QVariant qVariant = getDetailedVariant();
   CwmsJson cJson;
   bool success = false;
   QString qstrJson = cJson.serialize(qVariant, success);
   return qstrJson;
}

QVariant CsaValue::getRoughVariant()
{
   QVariantMap qVariantMap;
   addVariantData(qVariantMap);
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      qVariantMap.insert(WMS_VALUE, pValue->GetValueVariant());
      qVariantMap.insert(WMS_DETAIL, getUri());
   }

   return qVariantMap;
}

QVariant CsaValue::getDetailedVariant()
{
   QVariantMap qVariantMap = getRoughVariant().toMap();
   CdmValue* pValue = getInternals();

   if (CHKPTR(pValue))
   {
      qVariantMap.insert(WMS_TYPE, CdmMember::GetValueTypeAsString(pValue->GetValueType()));
//      const CdmMember* pMember = pValue->GetMember();
//      if (CHKPTR(pMember))
//      {
//          qVariantMap.insert(WMS_URI_MEMBER, pMember->GetUri());
//      }
   }

   return qVariantMap;
}



CdmValue *CsaValue::getInternals()
{
   return static_cast<CdmValue*>(getElement());
}

