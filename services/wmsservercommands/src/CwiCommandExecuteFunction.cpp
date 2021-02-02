#include "CwiCommandExecuteFunction.h"
#include "CdmDataProvider.h"
#include "CdmObject.h"
#include "CsaResultObject.h"
#include "CdmClassMethod.h"
#include "CdmClass.h"
#include "CdmExecutor.h"
#include "CdmExecutorRuntime.h"
#include "CdmExecutorRuntimeManager.h"
#include "IdmExecutorEngine.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmExecutorFunction.h"



CwiCommandExecuteFunction::CwiCommandExecuteFunction(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandExecuteFunction::~CwiCommandExecuteFunction()
{

}

void CwiCommandExecuteFunction::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    QVariant qvResult;

    if (pCdmManager)
    {
       long iDbId = m_rpData->GetValue("DatabaseId").toInt();
       CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(iDbId);
       CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(iDbId);

       if (pCdmClassManager && pContainerManager)
       {
           if (m_rpData->HasValue("ObjectId") && m_rpData->HasValue("ObjectListId"))
           {
              qvResult = ExecuteFunction(pContainerManager);
           }
           else if (m_rpData->HasValue("ClassId"))
           {
              qvResult = ExecuteStaticFunction(pCdmClassManager);
              pResult = GetResultContainer(m_rpData,
                                           1,
                                           "Static Function executed",
                                           eWmscomMessageServerityInfo);

           }
           else if (m_rpData->HasValue("Function"))
           {
              qvResult = ExecuteStaticFunction(pCdmClassManager);
              pResult = GetResultContainer(m_rpData,
                                           1,
                                           "Static Function executed",
                                           eWmscomMessageServerityInfo);
           }
           else
           {
               ERR("Data for function executing are missing we need the classid for static functions or container and object id for member functins.");
           }

           if (qvResult.isValid())
           {
               pResult = GetResultContainer(m_rpData,
                                            1,
                                            "Member Function executed",
                                            eWmscomMessageServerityInfo);
               pResult->AddValue("Result", qvResult);
           }
           else
           {
               pResult = GetResultContainer(m_rpData,
                                            -5000,
                                            "Error occured while execute function.",
                                            eWmscomMessageServerityError);
           }
       }
    }
}



QVariant CwiCommandExecuteFunction::ExecuteStaticFunction(CdmClassManager* pCdmClassManager)
{
    QVariant qvResult;
    CdmClass* pCdmClass = nullptr;
    QString qstrFunction;
    int iId = 0;

    if (m_rpData->HasValue("ClassId"))
    {
        iId = m_rpData->GetValue("ClassId").toInt();
        pCdmClass = pCdmClassManager->FindClassById(iId);
    }
    else
    {
        QString qstrFullQualifiedName = m_rpData->GetValue("Function").toString();
        int pos = qstrFullQualifiedName.lastIndexOf(".");

        QString qstrClass = qstrFullQualifiedName.left(pos);
        qstrFunction = qstrFullQualifiedName.mid(pos + 1, qstrFunction.length() - pos - 1);
        pCdmClass = pCdmClassManager->FindClassByKeyname(qstrClass);
    }

    if (pCdmClass)
    {
        CdmClassMethod* pMethod = nullptr;

        if (m_rpData->HasValue("ClassId"))
        {
            pMethod = pCdmClass->GetMethod(m_rpData->GetValue("Function").toString());
        }
        else
        {
            pMethod = pCdmClass->GetMethod(qstrFunction);
        }

        QVariantList qvParameters;

        if (m_rpData->HasValue("Parameters"))
        {
            qvParameters = m_rpData->GetValue("Parameters").toList();
        }

        if (pMethod)
        {
            qvResult = Execute(pMethod, nullptr, qvParameters);
        }
        else
        {
            ERR("Function with Name ) " + m_rpData->GetValue("Function").toString() + " not found in Class with Id " + QString::number(iId)+ ".");
        }
    }
    else
    {
        ERR("Class not found. Id " + QString::number(iId)+ ".");
    }

    return qvResult;
}

QVariant CwiCommandExecuteFunction::ExecuteFunction(CdmContainerManager* pContainerManager)
{
    QVariant qvResult;
    long iObjectListId = m_rpData->GetValue("ObjectListId").toInt();
    long iObjectId = m_rpData->GetValue("ObjectId").toInt();

    CdmObjectContainer* pContainer = pContainerManager->FindContainerById(iObjectListId);

    if (pContainer)
    {
        CdmObject* pObject = pContainer->FindObjectById(iObjectId);

        if (pObject)
        {
            CdmClass* pClass = pObject->GetClass();

             if (pClass)
             {
                 CdmClassMethod* pMethod = pClass->GetMethod(m_rpData->GetValue("Function").toString());
                 QVariantList qvParameters;

                 if (m_rpData->HasValue("Parameters"))
                 {
                     qvParameters = m_rpData->GetValue("Parameters").toList();
                 }

                 if (pMethod)
                 {
                     qvResult = Execute(pMethod, pObject, qvParameters);
                 }
                 else
                 {
                     ERR("Function with Name ) " + m_rpData->GetValue("Function").toString() + " not found in Class " + pClass->GetKeyname() + ".");
                 }
             }
        }
        else
        {
            ERR("Object with Id " + QString::number(iObjectId) + " not found in Container " + pContainer->GetKeyname() + ".");
        }
    }
    else
    {
        ERR("Container with Id " + QString::number(iObjectListId) + " not found.");
    }

    return qvResult;
}

QVariant CwiCommandExecuteFunction::Execute(CdmClassMethod* p_pMethod, CdmObject* p_pObject, QVariantList& p_rqvParameters)
{
    QVariant qvResult;

    if (p_pMethod)
    {
        CdmExecutorFunction* pFunction = CdmExecutor::GetExecutor()->GetFunction();

        if (CHKPTR(pFunction))
        {
            pFunction->Execute(p_pMethod, p_pObject, p_rqvParameters);
            IdmExecutorEngine* pEngine = CdmExecutor::GetExecutor()->GetFunction()->GetEngine();

            if (CHKPTR(pEngine))
            {
                if (!pEngine->HasUncaughtExceptions())
                {
                   CdmExecutorRuntime* pRuntime = CdmExecutor::GetExecutor()->GetRuntimeManager()->CreateOrGetRuntime(pEngine);
                   if (CHKPTR(pRuntime))
                   {
                       if (!pRuntime->ExceptionOccured())
                       {
                           qvResult = pRuntime->GetResultObject();
                       }
                       else
                       {
                            ERR("Exceptions occured.");
                       }
                   }
                   else
                   {
                        ERR("No valid Execution Runtime!");
                   }
                }
                else
                {
                    ERR("Exceptions occured.");
                }
            }
            else
            {
                ERR("No valid execution engine!");
            }
       }
       else
       {
            ERR("No valid Function executor.");
       }
   }
   else
   {
     ERR("Invalid Method.");
   }

    return qvResult;
}

