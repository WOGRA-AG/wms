/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmExecutorFunction.cpp
 ** Started Implementation: 2012/09/19
 ** Description:
 **
 ** Implements the executor for functions and validations in Objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QCoreApplication>
#include <QObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// own Includes
#include "CwmsJson.h"
#include "CsaFactory.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CsaUser.h"
#include "CsaUserGroup.h"
#include "IwmsPluginInterface.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"
#include "CdmValue.h"
#include "CdmValueBool.h"
#include "CdmValueInt.h"
#include "CdmValueFloat.h"
#include "CdmValueDouble.h"
#include "CdmValueString.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueDateTime.h"
#include "CdmValueDate.h"
#include "CdmValueTime.h"
#include "CdmObjectContainer.h"
#include "CdmMember.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmValueObjectRef.h"
#include "CdmClassValidator.h"
#include "CdmValue.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmExecutorRuntime.h"
#include "CdmExecutorRuntimeManager.h"
#include "CdmExecutorFunction.h"

CdmExecutorFunction::CdmExecutorFunction(CdmExecutor* p_pExecutor)
: m_rpExecutor(p_pExecutor)
{
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012----------*
 * @method  CdmExecutorFunction::~CdmExecutorFunction                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmExecutorFunction                                                   *
 *----------------last changed: --------------------------------Mi 19. Sep 14:18:59 2012----------*/
CdmExecutorFunction::~CdmExecutorFunction()
{
}

///
/// \brief CdmExecutorFunction::CallConstructor
/// \param p_pObject
///
void CdmExecutorFunction::CallConstructor(CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        CdmClass* pCdmClass = p_pObject->GetClass();
        CallConstructor(p_pObject, pCdmClass);
    }
}

///
/// \brief CdmExecutorFunction::CallConstructor
/// \param p_pObject
/// \param p_pClass
///
void CdmExecutorFunction::CallConstructor(CdmObject* p_pObject, CdmClass* p_pClass)
{
    if (CHKPTR(p_pObject) && CHKPTR(p_pObject))
    {
        CdmClassManager* pClassManager = p_pClass->GetClassManager();
        const QMap<long,long> qmBaseClasses = p_pClass->GetBaseClasses();

        QMap<long,long>::const_iterator qmIt = qmBaseClasses.begin();
        QMap<long,long>::const_iterator qmItEnd = qmBaseClasses.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmClass* pBaseClass = pClassManager->FindClassById(qmIt.value());

            if (CHKPTR(pBaseClass))
            {
                CallConstructor(p_pObject, pBaseClass);
            }
            else
            {
               ERR("Baseclass with ID " + QString::number(qmIt.value()) + " not found.");
            }
        }
    }

    CallClassConstructor(p_pObject, p_pClass);

}

void CdmExecutorFunction::CallClassConstructor(CdmObject* p_pObject, CdmClass* p_pClass)
{
    const QMap<QString, CdmClassMethod*> qmMethods = p_pClass->GetMethods();

    if (qmMethods.contains(SCRIPT_CONSTRUCTOR))
    {
        CdmClassMethod* pMethod = qmMethods[SCRIPT_CONSTRUCTOR];

        if (CHKPTR(pMethod))
        {
            Execute(pMethod, p_pObject);
        }
    }
}

///
/// \brief CdmExecutorFunction::CallDestructor
/// \param p_pObject
///
void CdmExecutorFunction::CallDestructor(CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        CdmClass* pCdmClass = p_pObject->GetClass();
        CallDestructor(p_pObject, pCdmClass);
    }
}

void CdmExecutorFunction::CallDestructor(CdmObject* p_pObject, CdmClass* p_pClass)
{
    CallClassDestructor(p_pObject, p_pClass);

    if (CHKPTR(p_pObject) && CHKPTR(p_pClass))
    {
        CdmClassManager* pClassManager = p_pClass->GetClassManager();
        const QMap<long,long> qmBaseClasses = p_pClass->GetBaseClasses();

        QMap<long,long>::const_iterator qmIt = qmBaseClasses.begin();
        QMap<long,long>::const_iterator qmItEnd = qmBaseClasses.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmClass* pBaseClass = pClassManager->FindClassById(qmIt.value());

            if (CHKPTR(pBaseClass))
            {
                CallDestructor(p_pObject, pBaseClass);
            }
        }
    }
}

void CdmExecutorFunction::CallClassDestructor(CdmObject* p_pObject, CdmClass* p_pClass)
{
    const QMap<QString, CdmClassMethod*> qmMethods = p_pClass->GetMethods();

    if (qmMethods.contains("onDelete"))
    {
        CdmClassMethod* pMethod = qmMethods["onDelete"];

        if (CHKPTR(pMethod))
        {
            Execute(pMethod, p_pObject);
        }
    }
}


/** +-=---------------------------------------------------------So 25. Nov 12:22:10 2012----------*
 * @method  CdmExecutorFunction::ExecuteObject                       // public, slots                     *
 * @return  QVariant                                         //                                   *
 * @param   QString p_qstrFunction                           //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QVariantList p_qlParameters                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 25. Nov 12:22:10 2012----------*/
QVariant CdmExecutorFunction::ExecuteObject(QString p_qstrFunction,
                                    CdmObject* p_pCdmObject,
                                    QVariantList p_qlParameters)
{
   QVariant qvValue;

   if (CHKPTR(p_pCdmObject))
   {
      CdmClass* pCdmClass = p_pCdmObject->GetClass();

      if (CHKPTR(pCdmClass))
      {
         CdmClassMethod* pMethod = pCdmClass->GetMethod(p_qstrFunction);

         if (pMethod) // nullptr when constructor or destructor was not found
         {
            if (pMethod->GetParameterCount() == 0)
            {
               qvValue = Execute(pMethod, p_pCdmObject);
            }
            else
            {
               if (p_qlParameters.isEmpty() && IsAskForParametersAllowed())
               {
                  p_qlParameters = GetPreProcessor()->AskForParameters(pMethod);
               }
               
               if (p_qlParameters.count() == pMethod->GetParameterCount())
               {
                  qvValue = Execute(pMethod, p_pCdmObject, p_qlParameters);
               }
               else
               {
                   ERR("Argumentlist incomplete");
               }
            }
         }
      }
   }

   return qvValue;
}

/** +-=---------------------------------------------------------So 25. Nov 12:23:19 2012----------*
 * @method  CdmExecutorFunction::ExecuteStatic                       // public, slots                     *
 * @return  QVariant                                         //                                   *
 * @param   CdmClassMethod* p_pMethod                        //                                   *
 * @param   QVariantList p_qlParameters                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 25. Nov 12:23:19 2012----------*/
QVariant CdmExecutorFunction::ExecuteStatic(CdmClassMethod* p_pMethod, QVariantList p_qlParameters)
{
   QVariant qvValue;

   if (CHKPTR(p_pMethod))
   {
      if (p_pMethod->GetParameterCount() == 0)
      {
         qvValue = Execute(p_pMethod, nullptr);
         QString qstrRetValue = qvValue.toString();
         INFO("Result of Function \"" + p_pMethod->GetMethodName() + "\" call: \"" + qstrRetValue + "\"");
      }
      else
      {
         if (p_qlParameters.isEmpty() && IsAskForParametersAllowed())
         {
            p_qlParameters = GetPreProcessor()->AskForParameters(p_pMethod);
         }
         
         if (p_qlParameters.count() == p_pMethod->GetParameterCount())
         {
            qvValue = Execute(p_pMethod, nullptr, p_qlParameters);
         }
         else
         {
             ERR("Invalid argument count.");
             qvValue = EC(eDmRequiredValueIsMissing);
         }
      }
   }

   return qvValue;
}


/** +-=---------------------------------------------------------So 25. Nov 11:20:17 2012----------*
 * @method  CdmExecutorFunction::Execute                             // private                           *
 * @return  QVariant                                         //                                   *
 * @param   CdmClassMethod* p_pMethod                        //                                   *
 * @param   CdmModelElement* p_pCdmBase                      // Object / ObjectList               *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 25. Nov 11:20:17 2012----------*/
QVariant CdmExecutorFunction::Execute(CdmClassMethod* p_pMethod, CdmModelElement* p_pCdmBase)
{
   QVariantList qlEmpty;
   return Execute(p_pMethod, p_pCdmBase, qlEmpty);
}

QString CdmExecutorFunction::GenerateArguments(QVariantList p_qlParams, CdmClassMethod* p_pMethod)
{
    QString qstrArguments;

    if (CHKPTR(p_pMethod))
    {
       for (int iCounter = 0; iCounter < p_qlParams.count(); ++iCounter)
       {
          QVariant qValue = p_qlParams[iCounter];
          CdmClassMethodParameter cParameter = p_pMethod->GetParameterByPos(iCounter);

          QString qstrValue = p_qlParams[iCounter].toString();
          QJsonArray array;
          QJsonValue qJsonValue(qstrValue);
          array.append(qJsonValue);
          QJsonDocument qJsonDoc(array);
          QString qstrJsonArrDoc = qJsonDoc.toJson(QJsonDocument::Compact);
          QString qstrEscapedValue = qstrJsonArrDoc.mid(1,qstrJsonArrDoc.length()-2);

          if (cParameter.m_eType <= eDmValueDouble)
          {
              qstrArguments += qstrValue;
          }
          else if (cParameter.m_eType == eDmValueString)
          {
              qstrArguments += qstrEscapedValue;
          }
          else if (cParameter.m_eType == eDmValueDate)
          {
              QDate qDate;
              // if the qVariant is of type QDateTime, remove the timezone offset
              if(p_qlParams[iCounter].type() == QVariant::DateTime) {
                  qDate = p_qlParams[iCounter].toDateTime().toUTC().date();
              } else {
                  qDate = p_qlParams[iCounter].toDate();
              }

              qstrArguments += ConvertToJsDateConstructor(qDate.year(), qDate.month(), qDate.day(), 0, 0, 0);
          }
          else if (cParameter.m_eType == eDmValueDateTime)
          {
              QDateTime qDate;
              // if the qVariant is of type QDateTime, remove the timezone offset
              if(p_qlParams[iCounter].type() == QVariant::DateTime) {
                  qDate = p_qlParams[iCounter].toDateTime().toUTC();
              } else {
                  qDate = p_qlParams[iCounter].toDateTime();
                  qDate.setTimeSpec(Qt::UTC);
              }

              qstrArguments += ConvertToJsDateConstructor(qDate.date().year(), qDate.date().month(), qDate.date().day(), qDate.time().hour(), qDate.time().minute(), qDate.time().second());
          }
          else if (cParameter.m_eType == eDmValueTime)
          {
              QTime qDate;
              // if the qVariant is of type QDateTime, remove the timezone offset
              if(p_qlParams[iCounter].type() == QVariant::DateTime) {
                  qDate = p_qlParams[iCounter].toDateTime().toUTC().time();
              } else {
                  qDate = p_qlParams[iCounter].toTime();
              }

              qstrArguments += ConvertToJsDateConstructor(1900 ,1, 1, qDate.hour(), qDate.minute(), qDate.second());
          }
          else if (cParameter.m_eType == eDmValueContainerRef)
          {
              QString olId = "-1";
              if (qValue.canConvert<QObject*>())
              {
                QObject* qObject = qValue.value<QObject*>();
                CsaObjectContainer* qCont = static_cast<CsaObjectContainer*>(qObject);
                if(CHKPTR(qCont))
                {
                    olId = QString::number(qCont->getId());
                }
              }
              else
              {
                  QString rawJson = p_qlParams[iCounter].toString();
                  CwmsJson cwmsJson;
                  QVariantMap qMap = cwmsJson.parse(rawJson).toMap();
                  olId = qMap["ObjectListId"].toString();
              }
              qstrArguments += "wmsFactory.getContainerManager().findEmptyContainerById("+olId+")";
          }
          else if (cParameter.m_eType == eDmValueObjectRef)
          {
              QString olId = "-1";
              QString oId = "-1";
              if (qValue.canConvert<QObject*>())
              {
                QObject* qObject = qValue.value<QObject*>();
                CsaObject* qCsaObject = static_cast<CsaObject*>(qObject);
                if(CHKPTR(qCsaObject)){
                    oId = QString::number(qCsaObject->getId());
                    QObject* qContainer = qCsaObject->getContainer();
                    if(CHKPTR(qContainer))
                    {
                        CsaObjectContainer* qCsaContainer = static_cast<CsaObjectContainer*>(qContainer);
                        olId = QString::number(qCsaContainer->getId());
                    }
                }
              }
              else
              {
                  QString rawJson = p_qlParams[iCounter].toString();
                  CwmsJson cwmsJson;
                  QVariantMap qMap = cwmsJson.parse(rawJson).toMap();
                  olId = qMap["ObjectListId"].toString();
                  oId = qMap["ObjectId"].toString();
              }
              qstrArguments += "wmsFactory.findObjectById("+olId+", "+oId+")";
          }
          else if (cParameter.m_eType == eDmValueUser)
          {
              QString qstrUserLogin = "-1";
              if (qValue.canConvert<QObject*>())
              {
                QObject* qObject = qValue.value<QObject*>();
                CsaUser* pUser = static_cast<CsaUser*>(qObject);
                if(CHKPTR(pUser))
                {
                    qstrUserLogin = pUser->getLogin();
                }
              }
              else
              {
                qstrUserLogin = p_qlParams[iCounter].toString();
              }
              qstrArguments += "wmsFactory.getManager().getUserByLogin(\""+qstrUserLogin+"\")";
          }
          else if (cParameter.m_eType == eDmValueUserGroup)
          {
              QString pUserGroupLogin = "-1";
              if (qValue.canConvert<QObject*>())
              {
                QObject* qObject = qValue.value<QObject*>();
                CsaUserGroup* qUserGroup = static_cast<CsaUserGroup*>(qObject);
                if(CHKPTR(qUserGroup))
                {
                    pUserGroupLogin = qUserGroup->getName();
                }
              }
              else
              {
                pUserGroupLogin = p_qlParams[iCounter].toString();
              }
              qstrArguments += "wmsFactory.getManager().getUsergroupByName(\""+pUserGroupLogin+"\")";
          }
          else if (cParameter.m_eType == eDmValueArray)
          {
              QString pJsonArray = "";
              if (qValue.canConvert<QString>())
              {
                  pJsonArray = qstrValue;
              }
              else
              {
                  QJsonDocument qJsonDoc = QJsonDocument::fromVariant(p_qlParams[iCounter]);
                  pJsonArray = qJsonDoc.toJson(QJsonDocument::Compact);
              }
              qstrArguments += pJsonArray;
          }
          else
          {
              qstrArguments += qstrEscapedValue;
          }

          if (iCounter < p_qlParams.count() -1)
          {
              qstrArguments += ", ";
          }

       }
    }
    return qstrArguments;
}

QString CdmExecutorFunction::ConvertToJsDateConstructor(
        int pYear, int pMonth, int pDay, int pHour, int pMinute, int pSecond){
    QString qYear = QString().sprintf("%d", pYear);
    QString qMonth = QString().sprintf("%d", pMonth - 1);
    QString qDay = QString().sprintf("%d",pDay);
    QString qHour = QString().sprintf("%d",pHour);
    QString qMinute = QString().sprintf("%d",pMinute);
    QString qSecond = QString().sprintf("%d",pSecond);
    //new Date(Date.UTC(2000,1,1)).getTimezoneOffset()/60
    QString qResult = "new Date(Date.UTC("+qYear+", "+qMonth+", "+ qDay +", "+qHour+", "+qMinute+", "+qSecond+"))";

    return qResult;
}

/** +-=---------------------------------------------------------Di 13. Nov 15:39:16 2012----------*
 * @method  CdmExecutorFunction::Execute                             // public, slots                     *
 * @return  QVariant                                         //                                   *
 * @param   CdmClassMethod* p_pMethod                        //                                   *
 * @param   CdmModelElement* p_pCdmBase                              // Object / ObjectList               *
 * @param   QVariantList p_qlParams                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 15:39:16 2012----------*/
QVariant CdmExecutorFunction::Execute(CdmClassMethod* p_pMethod,
                              CdmModelElement* p_pCdmBase,
                              QVariantList p_qlParams)
{
   SYNCHRONIZED;
   QVariant qvValue;
   CdmMessageManager::StartAsyncMessageCollection();

   
   if (CHKPTR(p_pMethod))
   {
      IdmExecutorEngine* pEngine = GetOrCreateEngine();

      if (CHKPTR(pEngine))
      {
         CdmExecutorRuntime* pRuntime = CreateOrGetRuntime(pEngine);
         CdmExecutorPreProcessor* preProcessor = GetPreProcessor();
         QString qstrMethodName;

         if (CHKPTR(pRuntime) && pRuntime->IsMethodCallAllowed(p_pMethod))
         {
             qstrMethodName = preProcessor->PreProcessFunction(p_pMethod, p_pCdmBase, *pEngine);

             if (!qstrMethodName.isEmpty())
             {
                QString qstrParameters = GenerateArguments(p_qlParams, p_pMethod);
                QString qstrMethodCall = qstrMethodName + "(" + qstrParameters + ")";
                CdmObject* pObject = dynamic_cast<CdmObject*>(p_pCdmBase);

                pRuntime->MethodCallStart(p_pMethod, pObject);
                qvValue = pEngine->Evaluate(qstrMethodCall, qstrMethodName + "_Call", p_pMethod->GetReturnType());

                if (preProcessor->ExceptionCheck(*pEngine) &&
                    !pRuntime->ExceptionOccured())
                {
                   if (p_pCdmBase &&
                       p_pCdmBase->IsObject() &&
                       !p_pCdmBase->IsDeleted())
                   {
                      if(p_pMethod->GetMethodName() != SCRIPT_CONSTRUCTOR &&
                         p_pMethod->GetMethodName() != SCRIPT_COMMIT &&
                         !m_rpExecutor->GetCommitRunning(pObject->GetObjectContainer()))
                      {
                          pObject->Commit();
                      }
                   }

                   int iDepth = pRuntime->GetCallStackDepth();
                   QVariant qConvertedValue;

                   if (iDepth > 1)
                   {
                       // if the call was from a sub method csaobject and csaobjcectcontainer must not
                       // be converted to json.
                       qConvertedValue = CsaFactory::convertToResultVariantForSubMethodCalls(qvValue);
                   }
                   else
                   {
                       qConvertedValue = CsaFactory::convertToResultVariant(qvValue);
                   }

                   CwmsJson CwmsJson;
                   QString qstrRetValue = CwmsJson.serialize(qConvertedValue);
                   INFO("Result of Function \"" + p_pMethod->GetMethodName() + "\" call: \"" + qstrRetValue + "\"");
                   qvValue = qConvertedValue;
                } else {
                   QVariantMap qvValueMap = qvValue.toMap();
                   qvValueMap.insert("exitStatus", "failure");
                   qvValue = qvValueMap;
                }

                pRuntime->MethodCallFinished();
             }
          }
          else
          {
             ERR("Engine not created");
          }
      }
   }

   CdmMessageManager::EndAndShowAsyncMessageCollection();
   return qvValue;
}

/** +-=---------------------------------------------------------Di 13. Nov 16:43:09 2012----------*
 * @method  CdmExecutorFunction::ExecuteFunction                     // public                    *
 * @return  QVariant                                         //                                   *
 * @param   QString p_qstrFunction                           //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QVariantList p_qlParameters                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 16:43:09 2012----------*/
QVariant CdmExecutorFunction::ExecuteFunction(QString p_qstrFunction,
                                      CdmObject* p_pCdmObject,
                                      QVariantList p_qlParameters)
{
   return ExecuteObject(p_qstrFunction, p_pCdmObject, p_qlParameters);
}

/** +-=---------------------------------------------------------Di 13. Nov 16:42:53 2012----------*
 * @method  CdmExecutorFunction::ExecuteFunctionStatic               // public                    *
 * @return  QVariant                                         //                                   *
 * @param   CdmClassMethod* p_pMethod                        //                                   *
 * @param   QVariantList p_qlParameters                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 16:42:53 2012----------*/
QVariant CdmExecutorFunction::ExecuteFunctionStatic(CdmClassMethod* p_pMethod,
                                            QVariantList p_qlParameters)
{
   return ExecuteStatic(p_pMethod, p_qlParameters);
}

bool CdmExecutorFunction::IsAskForParametersAllowed() const
{
    return m_bAllowAskForParameters;
}

void CdmExecutorFunction::setAskForParametersAllowed(bool bAllowAskForParameters)
{
    m_bAllowAskForParameters = bAllowAskForParameters;
}
