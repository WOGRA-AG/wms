// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmClassMethod.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"

// own Includes
#include "CwmsScriptableStatic.h"

CwmsScriptableStatic::CwmsScriptableStatic()
{
}

CwmsScriptableStatic::~CwmsScriptableStatic()
{

}

QVariant CwmsScriptableStatic::call(QString p_qstrClass, QString p_qstrMethod, QScriptValue p_qArg1, QScriptValue p_qArg2, QScriptValue p_qArg3, QScriptValue p_qArg4, QScriptValue p_qArg5, QScriptValue p_qArg6, QScriptValue p_qArg7, QScriptValue p_qArg8, QScriptValue p_qArg9, QScriptValue p_qArg10, QScriptValue p_qArg11, QScriptValue p_qArg12, QScriptValue p_qArg13, QScriptValue p_qArg14, QScriptValue p_qArg15)
{
    QVariant qsvResult;

    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
    {
        CdmClassMethod* pMethod = nullptr;
        CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(p_qstrClass);

            if (pClass)
            {
                pMethod = pClass->FindMethod(p_qstrMethod);
            }
            else
            {
                ERR("Class " + p_qstrClass + " not found for calling static function " + p_qstrMethod + ".");
            }
        }


        if (pMethod && pMethod->IsStatic())
        {
           QVariantList qlArguments;

           if (p_qArg1.isValid())
           {
               qlArguments.append(p_qArg1.toVariant());
           }

           if (p_qArg2.isValid())
           {
               qlArguments.append(p_qArg2.toVariant());
           }

           if (p_qArg3.isValid())
           {
               qlArguments.append(p_qArg3.toVariant());
           }

           if (p_qArg4.isValid())
           {
               qlArguments.append(p_qArg4.toVariant());
           }

           if (p_qArg5.isValid())
           {
               qlArguments.append(p_qArg5.toVariant());
           }

           if (p_qArg6.isValid())
           {
               qlArguments.append(p_qArg6.toVariant());
           }

           if (p_qArg7.isValid())
           {
               qlArguments.append(p_qArg7.toVariant());
           }

           if (p_qArg8.isValid())
           {
               qlArguments.append(p_qArg8.toVariant());
           }

           if (p_qArg9.isValid())
           {
               qlArguments.append(p_qArg9.toVariant());
           }

           if (p_qArg10.isValid())
           {
               qlArguments.append(p_qArg10.toVariant());
           }

           if (p_qArg11.isValid())
           {
               qlArguments.append(p_qArg11.toVariant());
           }

           if (p_qArg12.isValid())
           {
               qlArguments.append(p_qArg12.toVariant());
           }

           if (p_qArg13.isValid())
           {
               qlArguments.append(p_qArg13.toVariant());
           }

           if (p_qArg14.isValid())
           {
               qlArguments.append(p_qArg14.toVariant());
           }

           if (p_qArg15.isValid())
           {
               qlArguments.append(p_qArg15.toVariant());
           }

           qsvResult = pExecutor->GetFunction()->ExecuteFunctionStatic(pMethod, qlArguments);
        }
        else if (pMethod)
        {
            ERR("Method " + p_qstrMethod + " in class " + p_qstrClass + " is not static.");
        }
        else
        {
            ERR("Method " + p_qstrMethod + " in class " + p_qstrClass + " not found.");
        }
    }

    return qsvResult;
}

QVariant CwmsScriptableStatic::call(QString p_qstrClass, QString p_qstrFunction, QJSValue p_qlArguments)
{
    QVariant qsvResult;

    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
    {
        CdmClassMethod* pMethod = nullptr;
        CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(p_qstrClass);

            if (pClass)
            {
                pMethod = pClass->FindMethod(p_qstrFunction);
            }
            else
            {
                ERR("Class " + p_qstrClass + " not found for calling static function " + p_qstrFunction + ".");
            }
        }


        if (pMethod && pMethod->IsStatic())
        {
            QVariantList qlArguments;
            if (p_qlArguments.isArray())
            {
               int size = p_qlArguments.property("length").toInt();

               for (int pos = 0; pos < size; ++pos)
               {
                  QJSValue qsvArgument = p_qlArguments.property(pos);
                  qlArguments.append(qsvArgument.toVariant());
               }
            }
            else if (!p_qlArguments.isNull())
            {
                qlArguments.append(p_qlArguments.toVariant());
            }

           qsvResult = pExecutor->GetFunction()->ExecuteFunctionStatic(pMethod, qlArguments);
        }
        else if (pMethod)
        {
            ERR("Method " + p_qstrFunction + " in class " + p_qstrClass + " is not static.");
        }
        else
        {
            ERR("Method " + p_qstrFunction + " in class " + p_qstrClass + " not found.");
        }
    }

    return qsvResult;
}
