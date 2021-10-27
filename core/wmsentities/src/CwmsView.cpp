// System and QT Includes


// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmExecutor.h"

// Own Includes
#include "CwmsView.h"

#include <CwmsScriptableModel.h>

// Forwards

// Enumerations

CwmsView::CwmsView()
 : CdmObjectAdaptor()
{
}

CwmsView::CwmsView(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsView::~CwmsView()
{
}

int CwmsView::GetId()
{
   return GetInt("Id");
}

void CwmsView::SetId(int p_iValue)
{
   SetValue("Id", p_iValue);
}

QString CwmsView::GetName()
{
   return GetString("Name");
}

void CwmsView::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

QString CwmsView::GetViewCommand()
{
   return GetString("WQL");
}

void CwmsView::SetViewCommand(QString p_qstrValue)
{
   SetValue("WQL", p_qstrValue);
}

QString CwmsView::GetComment()
{
   return GetString("Comment");
}

void CwmsView::SetComment(QString p_qstrValue)
{
   SetValue("Comment", p_qstrValue);
}

int CwmsView::GetReference()
{
   return GetInt("Reference");
}

void CwmsView::SetReference(int p_iValue)
{
   SetValue("Reference", p_iValue);
}

bool CwmsView::GetValid()
{
   return GetBool("Valid");
}

void CwmsView::SetValid(bool p_bValue)
{
   SetValue("Valid", p_bValue);
}

bool CwmsView::IsWql()
{
    return CdmQuery::IsWql(GetViewCommand());
}

QStandardItemModel* CwmsView::GetModel()
{
    QStandardItemModel* pStandardItemModel = nullptr;
    CdmClassMethod* pMethod = FindModelMethod();

    if (CHKPTR(pMethod))
    {
        QVariantList qList;
        QVariant qvResult = CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, nullptr, qList);

        if (qvResult.canConvert<QObject*>())
        {
            QObject* pObject = qvResult.value<QObject*>();

            if (CHKPTR(pObject) && pObject->objectName() == "Model")
            {
                CwmsScriptableModel* pModel = dynamic_cast<CwmsScriptableModel*>(pObject);

                if (CHKPTR(pModel))
                {
                    pStandardItemModel = pModel->generateItemModel();
                    DELPTR(pModel);
                }
            }
        }
    }

    return pStandardItemModel;
}

CdmClassMethod* CwmsView::FindModelMethod()
{
    QString qstrViewCommand = GetViewCommand();
    return FindModelMethod(qstrViewCommand);
}

CdmClassMethod* CwmsView::FindModelMethod(QString& p_qstrModelMethod)
{
    int iPos = p_qstrModelMethod.lastIndexOf(".");

    if (iPos > 0)
    {
       QString qstrMethod = p_qstrModelMethod.mid(iPos + 1);
       QString qstrClass = p_qstrModelMethod.left(iPos);
       CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pProvider))
       {
           CdmClassManager* pClassManager = pProvider->GetClassManager();

           if (CHKPTR(pClassManager))
           {
              CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

              if (CHKPTR(pClass))
              {
                 CdmClassMethod* pMethod = pClass->FindMethod(qstrMethod);

                 if (CHKPTR(pMethod))
                 {
                    if (pMethod->IsStatic() /*&& pMethod->GetParameterCount() == 0*/ && pMethod->GetReturnType() == eDmValueQObject)
                    {
                         return pMethod;
                    }
                    else
                    {
                        if (!pMethod->IsStatic())
                        {
                            MSG_CRIT("Funktion ist nicht statisch", "Eine View Funktion muss statisch sein.");
                        }

//                        if (pMethod->GetParameterCount() != 0)
//                        {
//                            MSG_CRIT("Funktion hat Parameter", "Eine View Funktion darf keine Parameter haben.");
//                        }

                        if (pMethod->GetReturnType() == eDmValueQObject)
                        {
                            MSG_CRIT("Funktion hat falschen Rückgabewert", "Eine View Funktion muss QOBject als Rückgabewert haben.");
                        }
                    }
                 }
              }
           }
       }
    }

    return nullptr;
}

bool CwmsView::IsModel()
{
    return (FindModelMethod() != nullptr);
}

CwmsView CwmsView::Create()
{
   CwmsView cCwmsView;
   CdmObjectContainer* pContainer = CdmDataProvider::GetObjectContainer("TechnicalViews");

   if (CHKPTR(pContainer))
   {
      CdmObject* pCdmObject = pContainer->CreateNewObject();
      cCwmsView.SetObject(pCdmObject);
   }

   return cCwmsView;
}

CdmObject *CwmsView::GetReport()
{
    return GetObjectRefValue("Report");
}

void CwmsView::SetReport(CdmObject *p_pObject)
{
    SetObjectRefValue("Report", p_pObject);
}

bool CwmsView::Delete(CwmsView cCwmsView)
{
   bool bSuccess = false;
   if (cCwmsView.IsValid())
   {
      cCwmsView.SetDeleted();
      cCwmsView.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
