#include "CwmsPlatformServices.h"

#include "CdmClassMethod.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmMessageManager.h"
#include "CsaFactory.h"
#include "CwmsJson.h"

#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"


void CwmsPlatformServices::ExecuteFunction(CdmClassMethod* p_pFunction, bool p_bDebugger, QWidget* parent)
{
    QVariant qvResult;

    if (CHKPTR(p_pFunction))
    {
        if (p_pFunction->IsStatic())
        {
            qvResult = p_pFunction->ExecuteStaticFunction(p_bDebugger);
        }
        else
        {
            auto pClass = p_pFunction->GetClass();

            if (CHKPTR(pClass))
            {
                CdmObjectContainer* pList = CwmsContainerSelectionIf::GetObjectContainer(pClass->GetSchemeId(), pClass->GetId(),parent );

                if (pList)
                {
                    CdmObject* pObject = CwmsObjectSelectionIf::GetObject(pList, nullptr, parent);

                    if (pObject)
                    {
                        qvResult = p_pFunction->ExecuteFunction(p_bDebugger, pObject);
                    }
                    else
                    {
                        MSG_INFO("Funktion wird nicht ausgeführt",
                                 "Die Funktion kann nicht ausgeführt werden, da kein Objekt gewählt wurde und die Funktion nicht statisch ist.");

                    }
                }
            }
        }
    }

    QVariant qConvertedValue = CsaFactory::convertToResultVariant(qvResult);
    CwmsJson CwmsJson;
    QString qstrResult = CwmsJson.serialize(qConvertedValue);

    if (qstrResult.isEmpty() || qstrResult == "NULL")
    {
        qstrResult = QString::fromUtf8("Kein Rückgabewert");
    }

    QString qstrMessage = QString::fromUtf8("Funktion beendet. Rückgabewert: %1").arg(qstrResult);
    MSG_INFO(("Ergebnis"), qstrMessage.toUtf8());
}
