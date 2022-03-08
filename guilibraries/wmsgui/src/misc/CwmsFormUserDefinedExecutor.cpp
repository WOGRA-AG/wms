
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"
#include <CdmExecutor.h>
#include <CdmExecutorFunction.h>
#include <CdmSessionManager.h>
#include "CsaFactory.h"


#include "CwmsFormUserDefinedExecutor.h"

#include <QtUiTools/quiloader.h>

#include <IdmExecutorEngine.h>
#include <QBuffer>

#define WMS_FORM "form"
#define WMS_CURRENT_OBJECT "myObject"
#define WMS_CURRENT_CONTAINER "myContainer"

CwmsFormUserDefinedExecutor::CwmsFormUserDefinedExecutor()
    : m_qwContainer(nullptr)
{

}

CwmsFormUserDefinedExecutor::~CwmsFormUserDefinedExecutor()
{

}

QWidget* CwmsFormUserDefinedExecutor::GenerateUi(CwmsFormUserDefined &p_Form, QWidget* parent)
{
    QString qstrUIDefintion = p_Form.GetXml();

    if (!qstrUIDefintion.isEmpty())
    {
        QUiLoader loader;
        QByteArray qba = qstrUIDefintion.toUtf8();
        QBuffer qBuffer(&qba);
        qBuffer.open(QIODevice::ReadOnly);
        QWidget* pWidget = loader.load(&qBuffer, parent);
        QString qstrErr = loader.errorString();

        if (!qstrErr.isEmpty())
        {
            ERR(qstrErr);
        }

        if (CHKPTR(pWidget))
        {
            pWidget->setAttribute(Qt::WA_DeleteOnClose, true); // automatic deletes the ui if the ui will be closed.
        }

        return pWidget;
    }

    return nullptr;
}

void CwmsFormUserDefinedExecutor::ShowUi(CwmsFormUserDefined &p_Form, QWidget* p_pWidget)
{
    if (CHKPTR(p_pWidget))
    {
        if (p_Form.GetFormType() == eWmsFormTypeDialog)
        {
            auto pDialog = dynamic_cast<QDialog*>(p_pWidget);

            if (CHKPTR(pDialog))
            {
                pDialog->show();

                if (p_Form.IsModal())
                {
                    pDialog->exec();
                }
                else
                {
                    pDialog->show();
                }
            }
            else
            {
                ERR("UI declared as Dialog, but cannot cast to Dialog!");
            }
        }
        else if (p_Form.GetFormType() == eWmsFormTypeMainWindow)
        {
            auto pMainWindow = dynamic_cast<QMainWindow*>(p_pWidget);

            if (CHKPTR(pMainWindow))
            {
                pMainWindow->show();
            }
            else
            {
                ERR("UI declared as MainWindow, but cannot cast to MainWindow!");
            }
        }
        else
        {
            m_qwContainer->show();
        }
    }
}

IdmExecutorEngine* CwmsFormUserDefinedExecutor::GetEngine()
{
    auto pDataProvider = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pDataProvider))
    {
        auto pExecutor = pDataProvider->GetExecutor();

        if (CHKPTR(pExecutor))
        {
            auto pExecutorFunction = pExecutor->GetFunction();

            if (CHKPTR(pExecutorFunction))
            {
                return pExecutorFunction->GetOrCreateEngine();
            }
        }
    }

    return nullptr;
}

CsaFactory* CwmsFormUserDefinedExecutor::GetFactory()
{
    auto pDataProvider = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pDataProvider))
    {
        auto pExecutor = pDataProvider->GetExecutor();

        if (CHKPTR(pExecutor))
        {
            auto pExecutorFunction = pExecutor->GetFunction();

            if (CHKPTR(pExecutorFunction))
            {
                return pExecutorFunction->GetFactory();
            }
        }
    }

    return nullptr;
}


void CwmsFormUserDefinedExecutor::InitForm(CwmsFormUserDefined &p_Form, QWidget* p_pWidget, CdmObject *p_pObject)
{
    QString qstrCode = p_Form.GetUICode();


    if (!qstrCode.isEmpty())
    {
        BuildFunctionCode(qstrCode, p_Form);
        IdmExecutorEngine* pEngine = GetEngine();
        CsaFactory* pFactory = GetFactory();

        if (CHKPTR(pEngine) && CHKPTR(pFactory))
        {
            pEngine->PushContext();
            pEngine->SetProperty(p_Form.GetName(), p_pWidget);
            pEngine->SetProperty(WMS_CURRENT_OBJECT, pFactory->createScriptObject(p_pObject));
            pEngine->Evaluate(qstrCode, p_Form.GetName());
            pEngine->PopContext();
        }
    }
}

void CwmsFormUserDefinedExecutor::BuildFunctionCode(QString& p_rqstrCode, CwmsFormUserDefined &p_Form)
{
    QString qstrName = p_Form.GetName();

    if (!qstrName.isEmpty())
    {
      //  QString qstrHeader = QString (" %1()\n{").arg(qstrName);
    }
}

void CwmsFormUserDefinedExecutor::InitForm(CwmsFormUserDefined &p_Form, QWidget* p_pWidget, CdmObjectContainer *p_pContainer)
{
    QString qstrCode = p_Form.GetUICode();

    if (!qstrCode.isEmpty())
    {
        IdmExecutorEngine* pEngine = GetEngine();
        CsaFactory* pFactory = GetFactory();

        if (CHKPTR(pEngine) && CHKPTR(pFactory))
        {
            pEngine->PushContext();
            pEngine->SetProperty(p_Form.GetName(), p_pWidget);
            pEngine->SetProperty(WMS_CURRENT_CONTAINER, pFactory->createScriptObject(p_pContainer));
            pEngine->Evaluate(qstrCode, p_Form.GetName());
            pEngine->PopContext();
        }
    }

}

void CwmsFormUserDefinedExecutor::InitForm(CwmsFormUserDefined &p_Form, QWidget* p_pWidget)
{
    QString qstrCode = p_Form.GetUICode();

    if (!qstrCode.isEmpty())
    {
        IdmExecutorEngine* pEngine = GetEngine();

        if (CHKPTR(pEngine))
        {
            pEngine->PushContext();
            pEngine->SetProperty(p_Form.GetName(), p_pWidget);
            pEngine->Evaluate(qstrCode, p_Form.GetName());
            pEngine->PopContext();
        }
    }
}

void CwmsFormUserDefinedExecutor::ExecuteUserDefinedFormObject(CwmsFormUserDefined &p_Form, CdmObject *p_pObject, QWidget* parent)
{
    if (CHKPTR(p_pObject))
    {
        QWidget* pWidget = GenerateUi(p_Form, parent);

        if (CHKPTR(pWidget))
        {
            InitForm(p_Form, pWidget, p_pObject);
            ShowUi(p_Form, pWidget);
        }
    }
}

void CwmsFormUserDefinedExecutor::ExecuteUserDefinedFormContainer(CwmsFormUserDefined &p_Form, CdmObjectContainer *p_pContainer, QWidget* parent)
{
    if (CHKPTR(p_pContainer))
    {
        QWidget* pWidget = GenerateUi(p_Form, parent);

        if (CHKPTR(pWidget))
        {
            InitForm(p_Form, pWidget, p_pContainer);
            ShowUi(p_Form, pWidget);
        }
    }
}

void CwmsFormUserDefinedExecutor::ExecuteUserDefinedFormMisc(CwmsFormUserDefined &p_Form, QWidget* parent)
{
    QWidget* pWidget = GenerateUi(p_Form, parent);

    if (CHKPTR(pWidget))
    {
        InitForm(p_Form, pWidget);
        ShowUi(p_Form, pWidget);
    }
}
