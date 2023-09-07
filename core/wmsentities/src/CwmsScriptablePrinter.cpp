// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CsaFactory.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CsaObject.h"
#include "CdmScheme.h"
#include "CsaObjectContainer.h"
#include "CdmQuery.h"

// own Includes
#include "CwmsReportManager.h"
#include "IwmsPrinting.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsScriptablePrinter.h"


CwmsScriptablePrinter::CwmsScriptablePrinter()
{
}

CwmsScriptablePrinter::~CwmsScriptablePrinter()
{
}

void CwmsScriptablePrinter::print(CsaObject* p_pCsaObject)
{
   if (CHKPTR(p_pCsaObject))
   {
      CwmsReportManager cReportManager;  
      QString qstrTemplate;
      CdmQuery* pQuery = nullptr;

      const CdmClass* pClass = p_pCsaObject->getInternals()->GetClass();

      if (CHKPTR(pClass))
      {
         pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetKeyname(), 
                                                          eWmsTemplateTypeObject);
      }

      print(pQuery, cReportManager, p_pCsaObject);
      
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CsaObject* p_pCsaObject)
{
    QString qba;
   if (CHKPTR(p_pCsaObject))
   {
      CwmsReportManager cReportManager;
      QString qstrTemplate;
      CdmQuery* pQuery = nullptr;

      const CdmClass* pClass = p_pCsaObject->getInternals()->GetClass();

      if (CHKPTR(pClass))
      {
         pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetKeyname(),
                                                          eWmsTemplateTypeObject);
      }

      qba = printPdfToBase64(pQuery, cReportManager, p_pCsaObject);

   }

   return qba;
}

void CwmsScriptablePrinter::printInLanguage(CsaObject* p_pCsaObject, QString p_qstrLanguage)
{
   if (CHKPTR(p_pCsaObject))
   {
       CdmScheme* pScheme = p_pCsaObject->getInternals()->GetScheme();

       if (CHKPTR(pScheme))
       {
            if (CHKPTR(p_pCsaObject))
            {
                   CwmsReportManager cReportManager;
                   CdmQuery* pQuery = nullptr;

                   const CdmClass* pClass = p_pCsaObject->getInternals()->GetClass();

                   if (CHKPTR(pClass))
                   {
                      pQuery = cReportManager.GetReportsByClassKeynameAndLanguage(pClass->GetKeyname(),
                                                                                  eWmsTemplateTypeObject,
                                                                                  p_qstrLanguage);
                   }

                   print(pQuery, cReportManager, p_pCsaObject);
            }
       }
   }
}

QString CwmsScriptablePrinter::printInLanguagePdfToBase64(CsaObject* p_pCsaObject, QString p_qstrLanguage)
{
    QString qba;
   if (CHKPTR(p_pCsaObject))
   {
       CdmScheme* pScheme = p_pCsaObject->getInternals()->GetScheme();

       if (CHKPTR(pScheme))
       {
           CwmsReportManager cReportManager;
           CdmQuery* pQuery = nullptr;

           const CdmClass* pClass = p_pCsaObject->getInternals()->GetClass();

           if (CHKPTR(pClass))
           {
              pQuery = cReportManager.GetReportsByClassKeynameAndLanguage(pClass->GetKeyname(),
                                                                          eWmsTemplateTypeObject,
                                                                          p_qstrLanguage);
           }

           qba = printPdfToBase64(pQuery, cReportManager, p_pCsaObject);
       }
   }

   return qba;
}

void CwmsScriptablePrinter::print(CsaObject* p_pCsaObjectToPrint, QString p_qstrTemplate)
{
   if (CHKPTR(p_pCsaObjectToPrint))
   {
      CwmsReportManager cReportManager;
      CwmsPrintingTemplate cTemplate = cReportManager.GetReport(p_qstrTemplate);

      if (cTemplate.IsValid())
      {
          CwmsReportManager cReportManager;
         IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

         if (CHKPTR(pPrinting))
         {
             pPrinting->AddObject("Object", p_pCsaObjectToPrint->getInternals());
             pPrinting->SetTemplate(cTemplate);
             pPrinting->Print();
             DELPTR(pPrinting);
         }
      }
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CsaObject* p_pCsaObjectToPrint, QString p_qstrTemplate)
{
    QString qba;
   if (CHKPTR(p_pCsaObjectToPrint))
   {
      CwmsReportManager cReportManager;
      CwmsPrintingTemplate cTemplate = cReportManager.GetReport(p_qstrTemplate);

      if (cTemplate.IsValid())
      {
          CwmsReportManager cReportManager;
         IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

         if (CHKPTR(pPrinting))
         {
             pPrinting->AddObject("Object", p_pCsaObjectToPrint->getInternals());
             pPrinting->SetTemplate(cTemplate);
             qba = pPrinting->PrintPdfToByteArray().toBase64();
             DELPTR(pPrinting);
         }
      }
   }

   return qba;
}

void CwmsScriptablePrinter::print(CsaObject* p_pCsaObjectToPrint, CsaObject* p_pCdmTemplate)
{
   if (CHKPTR(p_pCsaObjectToPrint) && CHKPTR(p_pCdmTemplate))
   {
      CwmsPrintingTemplate cTemplate(p_pCdmTemplate->getInternals());

      if (cTemplate.IsValid())
      {
         CwmsReportManager cReportManager;
         IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

         if (CHKPTR(pPrinting))
         {
             pPrinting->AddObject("Object", p_pCsaObjectToPrint->getInternals());
             pPrinting->SetTemplate(cTemplate);
             pPrinting->Print();
             DELPTR(pPrinting);
         }
      }
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CsaObject* p_pCsaObjectToPrint, CsaObject* p_pCdmTemplate)
{
    QString qba;

   if (CHKPTR(p_pCsaObjectToPrint) && CHKPTR(p_pCdmTemplate))
   {
      CwmsPrintingTemplate cTemplate(p_pCdmTemplate->getInternals());

      if (cTemplate.IsValid())
      {
         CwmsReportManager cReportManager;
         IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

         if (CHKPTR(pPrinting))
         {
             pPrinting->AddObject("Object", p_pCsaObjectToPrint->getInternals());
             pPrinting->SetTemplate(cTemplate);
             qba = pPrinting->PrintPdfToByteArray().toBase64();
             DELPTR(pPrinting);
         }
      }
   }

   return qba;
}

void CwmsScriptablePrinter::print(CsaObjectContainer* p_pList)
{
   if (CHKPTR(p_pList))
   {
      CwmsReportManager cReportManager;  
      QString qstrTemplate;
      CdmQuery* pQuery = nullptr;
      
      const CdmClass* pClass = p_pList->getInternals()->GetClass();

      if (CHKPTR(pClass))
      {
         pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetKeyname(), 
                                                          eWmsTemplateTypeList);
      }
      
      if (pQuery)
      {
         int iResultCount = pQuery->GetResultCount();

         if (iResultCount > 0)
         {
            for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
            {
               QString qstrName = pQuery->GetResultAt(0, iCounter).toString();
               bool bDefault = pQuery->GetResultAt(1, iCounter).toBool();

               if (iCounter == 0)
               {
                  qstrTemplate = qstrName;
               }

               if (bDefault)
               {
                  qstrTemplate = qstrName;
                  break;
               }
            }
         }

         DELPTR(pQuery);
      }

      if (!qstrTemplate.isEmpty())
      {
         CwmsPrintingTemplate cTemplate = cReportManager.GetReport(qstrTemplate);
         CsaFactory* pFactory = dynamic_cast<CsaFactory*> (p_pList->getFactory());
         print(p_pList, static_cast<CsaObject*>(pFactory->createScriptObject(cTemplate.GetObject())));
      }
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CsaObjectContainer* p_pList)
{
    QString qba;
   if (CHKPTR(p_pList))
   {
      CwmsReportManager cReportManager;
      QString qstrTemplate;
      CdmQuery* pQuery = nullptr;

      const CdmClass* pClass = p_pList->getInternals()->GetClass();

      if (CHKPTR(pClass))
      {
         pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetKeyname(),
                                                          eWmsTemplateTypeList);
      }

      if (pQuery)
      {
         int iResultCount = pQuery->GetResultCount();

         if (iResultCount > 0)
         {
            for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
            {
               QString qstrName = pQuery->GetResultAt(0, iCounter).toString();
               bool bDefault = pQuery->GetResultAt(1, iCounter).toBool();

               if (iCounter == 0)
               {
                  qstrTemplate = qstrName;
               }

               if (bDefault)
               {
                  qstrTemplate = qstrName;
                  break;
               }
            }
         }

         DELPTR(pQuery);
      }

      if (!qstrTemplate.isEmpty())
      {
         CwmsPrintingTemplate cTemplate = cReportManager.GetReport(qstrTemplate);
         CsaFactory* pFactory = dynamic_cast<CsaFactory*> (p_pList->getFactory());
         qba = printPdfToBase64(p_pList, static_cast<CsaObject*>(pFactory->createScriptObject(cTemplate.GetObject())));
      }
   }

   return qba;
}

void CwmsScriptablePrinter::print(CsaObjectContainer* p_pList, CsaObject* p_pCdmTemplate)
{
   if (CHKPTR(p_pList) && CHKPTR(p_pCdmTemplate))
   {
      CwmsPrintingTemplate cTemplate(p_pCdmTemplate->getInternals());

      if (cTemplate.IsValid())
      {
          CwmsReportManager cReportManager;
          IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

          if (CHKPTR(pPrinting))
          {
              pPrinting->AddObjectContainer("ObjectContainer", p_pList->getInternals());
              pPrinting->SetTemplate(cTemplate);
              pPrinting->Print();
              DELPTR(pPrinting);
          }
      }
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CsaObjectContainer* p_pList, CsaObject* p_pCdmTemplate)
{
    QByteArray qba;
   if (CHKPTR(p_pList) && CHKPTR(p_pCdmTemplate))
   {
      CwmsPrintingTemplate cTemplate(p_pCdmTemplate->getInternals());

      if (cTemplate.IsValid())
      {
          CwmsReportManager cReportManager;
          IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

          if (CHKPTR(pPrinting))
          {
              pPrinting->AddObjectContainer("ObjectContainer", p_pList->getInternals());
              pPrinting->SetTemplate(cTemplate);
              qba = pPrinting->PrintPdfToByteArray().toBase64();
              DELPTR(pPrinting);
          }
      }
   }

   return qba;
}

void CwmsScriptablePrinter::print(CsaObjectContainer* p_pList, QString p_qstrTemplate)
{
   if (CHKPTR(p_pList))
   {
      CwmsReportManager cReportManager;
      CwmsPrintingTemplate cTemplate = cReportManager.GetReport(p_qstrTemplate);

      if (cTemplate.IsValid())
      {
          CwmsReportManager cReportManager;
          IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

          if (CHKPTR(pPrinting))
          {
              pPrinting->AddObjectContainer("ObjectContainer", p_pList->getInternals());
              pPrinting->SetTemplate(cTemplate);
              pPrinting->Print();
              DELPTR(pPrinting);
          }
      }
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CsaObjectContainer* p_pList, QString p_qstrTemplate)
{
    QString qba;
   if (CHKPTR(p_pList))
   {
      CwmsReportManager cReportManager;
      CwmsPrintingTemplate cTemplate = cReportManager.GetReport(p_qstrTemplate);

      if (cTemplate.IsValid())
      {
          CwmsReportManager cReportManager;
          IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

          if (CHKPTR(pPrinting))
          {
              pPrinting->AddObjectContainer("ObjectContainer", p_pList->getInternals());
              pPrinting->SetTemplate(cTemplate);
              qba = pPrinting->PrintPdfToByteArray().toBase64();
              DELPTR(pPrinting);
          }
      }
   }

   return qba;
}

void CwmsScriptablePrinter::print(CdmQuery* pQuery, CwmsReportManager &cReportManager, CsaObject* p_pCsaObject)
{
   QString qstrTemplate;
   if (pQuery)
   {
      int iResultCount = pQuery->GetResultCount();

      if (iResultCount > 0)
      {
         for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
         {
            QString qstrName = pQuery->GetResultAt(0, iCounter).toString();
            bool bDefault = pQuery->GetResultAt(1, iCounter).toBool();

            if (iCounter == 0)
            {
               qstrTemplate = qstrName;
            }

            if (bDefault)
            {
               qstrTemplate = qstrName;
               break;
            }
         }
      }

      DELPTR(pQuery);
   }

   CwmsPrintingTemplate cTemplate = cReportManager.GetReport(qstrTemplate);
   CsaFactory* pFactory = dynamic_cast<CsaFactory*> (p_pCsaObject->getFactory());

   CdmObject* pTemplateObject = cTemplate.GetObject();

   if (pTemplateObject)
   {
        print(p_pCsaObject, static_cast<CsaObject*>(pFactory->createScriptObject(cTemplate.GetObject())));
   }
   else
   {
       ERR("No template found to print document. print canceled!\nTemplateName: " + qstrTemplate);
   }
}

QString CwmsScriptablePrinter::printPdfToBase64(CdmQuery* pQuery, CwmsReportManager &cReportManager, CsaObject* p_pCsaObject)
{
    QString qba;
   QString qstrTemplate;
   if (pQuery)
   {
      int iResultCount = pQuery->GetResultCount();

      if (iResultCount > 0)
      {
         for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
         {
            QString qstrName = pQuery->GetResultAt(0, iCounter).toString();
            bool bDefault = pQuery->GetResultAt(1, iCounter).toBool();

            if (iCounter == 0)
            {
               qstrTemplate = qstrName;
            }

            if (bDefault)
            {
               qstrTemplate = qstrName;
               break;
            }
         }
      }

      DELPTR(pQuery);
   }

   CwmsPrintingTemplate cTemplate = cReportManager.GetReport(qstrTemplate);
   if (cTemplate.IsValid())
   {
        CsaFactory* pFactory = dynamic_cast<CsaFactory*> (p_pCsaObject->getFactory());
        CsaObject* pCsaTemplateObject =
                static_cast<CsaObject*>(pFactory->createScriptObject(cTemplate.GetObject()));
        qba = printPdfToBase64(p_pCsaObject, pCsaTemplateObject);
    }
    else
    {
        ERR("Template not found.\n Templatename: " + qstrTemplate);
    }
   return qba;
}
