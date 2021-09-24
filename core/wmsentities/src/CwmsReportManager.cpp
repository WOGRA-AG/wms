/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsReportManager.cpp
 ** Started Implementation: 2012/08/27
 ** Description:
 **
 ** Implements the manager for reports and printing templates
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QCoreApplication>
#include <QList>
#include <QDir>
#include <QDebug>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmScheme.h"
#include "CdmClassManager.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"
#include "CdmMessageManager.h"

// own Includes
#include "CwmsContext.h"
#include "CwmsReportManager.h"
#include "IwmsPrinting.h"
#include "IwmsPrintingPlugin.h"
#include "CwmsApplicationServices.h"
#include "CwmsReportManager.h"

/** +-=---------------------------------------------------------Mo 27. Aug 14:07:50 2012----------*
 * @method  CwmsReportManager::CwmsReportManager             // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:07:50 2012----------*/
CwmsReportManager::CwmsReportManager()
{
    CheckReportDataStructure();
}

/** +-=---------------------------------------------------------Mo 27. Aug 14:07:57 2012----------*
 * @method  CwmsReportManager::~CwmsReportManager            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsReportManager                                             *
 *----------------last changed: --------------------------------Mo 27. Aug 14:07:57 2012----------*/
CwmsReportManager::~CwmsReportManager()
{
}


/** +-=---------------------------------------------------------Mo 27. Aug 14:08:49 2012----------*
 * @method  CwmsReportManager::CheckReportDataStructure      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:08:49 2012----------*/
void CwmsReportManager::CheckReportDataStructure()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

        if (CHKPTR(pCdmClassManager))
        {
            CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname("Technical_Report");

            if (!pCdmClass)
            {
                CreateReportClass(pCdmClassManager);
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 14:18:47 2012----------*
 * @method  CwmsReportManager::CreateReportClass             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:18:47 2012----------*/
void CwmsReportManager::CreateReportClass(CdmClassManager* p_pCdmClassManager)
{
    if (CHKPTR(p_pCdmClassManager))
    {
        CdmClass* pCdmClass = p_pCdmClassManager->CreateClass("Technical_Report");

        if (CHKPTR(pCdmClass))
        {
            pCdmClass->SetCaption(tr("Bericht und Druckvorlage"));
            pCdmClass->SetComment(tr("Speichert Berichts- und Druckvorlagen in der Datenbank."));

            CdmClassGroup* pCdmClassGroupInfo = pCdmClass->CreateGroup(tr("Information"), 1, nullptr);
            CdmClassGroup* pCdmClassGroupDetails = pCdmClass->CreateGroup(tr("Details"), 1, nullptr);
            pCdmClass->Commit();

            CdmMember* pCdmMember = nullptr;
            pCdmMember = pCdmClass->CreateMember("Name", eDmValueString, true, 200);

            if (CHKPTR(pCdmMember))
            {
                pCdmMember->SetCaption(tr("Name"));
                pCdmMember->SetComment(tr("Name der Vorlage"));
                pCdmMember->SetGroup(pCdmClassGroupInfo);
            }

            pCdmMember = pCdmClass->CreateMember("Template", eDmValueCharacterDocument, false, 0);

            if (CHKPTR(pCdmMember))
            {
                pCdmMember->SetCaption(tr("Vorlage"));
                pCdmMember->SetComment(tr("Die Vorlage als XML DOkument"));
                pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
                pCdmMember->SetGroup(pCdmClassGroupDetails);
            }

            pCdmMember = pCdmClass->CreateMember("Class", eDmValueString, false, 0);

            if (CHKPTR(pCdmMember))
            {
                pCdmMember->SetCaption(tr("Klasse"));
                pCdmMember->SetComment(tr("Die Klasse zu der die Vorlage gehört (Keyname)"));
                pCdmMember->SetGroup(pCdmClassGroupInfo);
            }

            pCdmMember = pCdmClass->CreateMember("Language", eDmValueString, false, 0);

            if (CHKPTR(pCdmMember))
            {
                pCdmMember->SetCaption(tr("Sprache"));
                pCdmMember->SetComment(tr("Die Sprache der Vorlage"));
                pCdmMember->SetGroup(pCdmClassGroupInfo);
            }

            pCdmMember = pCdmClass->CreateMember("Type", eDmValueInt, false, 0);

            if (CHKPTR(pCdmMember))
            {
                pCdmMember->SetCaption(tr("Art"));
                pCdmMember->SetComment(tr("Die Art der Vorlage"));
                pCdmMember->SetGroup(pCdmClassGroupInfo);
            }

            pCdmMember = pCdmClass->CreateMember("Default", eDmValueBool, false, 0);

            if (CHKPTR(pCdmMember))
            {
                pCdmMember->SetCaption(tr("Standard"));
                pCdmMember->SetComment(tr("Kennzeichen ob diese Vorlage die Standardvorlage ist."));
                pCdmMember->SetGroup(pCdmClassGroupInfo);
            }

            pCdmClass->UpdateVersion();
            pCdmClass->Commit();

            CdmContainerManager* pCdmOLManager = pCdmClass->GetContainerManager();

            if (CHKPTR(pCdmOLManager))
            {
                QString qstrOLName = "TechnicalReports";
                pCdmOLManager->CreateContainer(pCdmClass, qstrOLName);
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 14:40:21 2012----------*
 * @method  CwmsReportManager::GetObjectList                 // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:40:21 2012----------*/
CdmObjectContainer* CwmsReportManager::GetObjectList()
{
    return CdmDataProvider::GetObjectContainer("TechnicalReports");
}

/** +-=---------------------------------------------------------Mo 27. Aug 14:40:50 2012----------*
 * @method  CwmsReportManager::GetReportList                 // public                            *
 * @return  void                                             //                                   *
 * @param   QList<CdmObject*>& p_rqlViews              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:40:50 2012----------*/
void CwmsReportManager::GetReportList(QList<CdmObject*>& p_rqlViews)
{
    CdmObjectContainer* pContainer = GetObjectList();

    if (CHKPTR(pContainer))
    {
        pContainer->GetObjectList(p_rqlViews);
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 14:43:22 2012----------*
 * @method  CwmsReportManager::GetReport                     // public                            *
 * @return  CwmsPrintingTemplate                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:43:22 2012----------*/
CwmsPrintingTemplate CwmsReportManager::GetReport(long p_lObjectId)
{
    CwmsPrintingTemplate cPrintingTemplate;
    CdmObjectContainer* pContainer = GetObjectList();

    if (CHKPTR(pContainer))
    {
        CdmObject* pCdmObject = pContainer->FindObjectById(p_lObjectId);
        cPrintingTemplate.SetObject(pCdmObject);
    }

    return cPrintingTemplate;
}

/** +-=---------------------------------------------------------Mo 27. Aug 14:41:50 2012----------*
 * @method  CwmsReportManager::GetReport                     // public                            *
 * @return  CwmsPrintingTemplate                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 14:41:50 2012----------*/
CwmsPrintingTemplate CwmsReportManager::GetReport(QString p_qstrName)
{
    CwmsPrintingTemplate cPrintingTemplate;
    QString qstrQuery = "select from TechnicalReports where Name = \"" + p_qstrName +"\"";

    CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrQuery);

    if (pQuery)
    {
        QList<long> qllResults = pQuery->GetResultList();

        if (qllResults.count() > 0)
        {
            cPrintingTemplate = GetReport(*(qllResults.begin()));
        }

        DELPTR(pQuery);
    }

    return cPrintingTemplate;
}

/** +-=---------------------------------------------------------Mi 20. Feb 16:20:42 2013----------*
 * @method  CwmsReportManager::GetClassesWithReports         // public                            *
 * @return  void                                             //                                   *
 * @param   QStringList& p_rqlClasses                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Feb 16:20:42 2013----------*/
void CwmsReportManager::GetClassesWithReports(QStringList& p_rqlClasses)
{
    CwmsPrintingTemplate cPrintingTemplate;
    QString qstrQuery = "select Class from TechnicalReports";
    CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrQuery);

    if (pQuery)
    {
        int iCount = pQuery->GetResultCount();

        for( int iCounter = 0; iCounter < iCount; ++iCounter)
        {
            QString qstrKeyname = pQuery->GetResultAt(0, iCounter).toString();

            if (!p_rqlClasses.contains(qstrKeyname))
            {
                p_rqlClasses.append(qstrKeyname);
            }
        }

        DELPTR(pQuery);
    }
}

/** +-=---------------------------------------------------------Mi 20. Feb 16:21:19 2013----------*
 * @method  CwmsReportManager::GetReportsByClassKeyname      // public                            *
 * @return  CdmQueryEnhanced*                                //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Feb 16:21:19 2013----------*/
CdmQueryEnhanced* CwmsReportManager::GetReportsByClassKeyname(QString p_qstrKeyname)
{
    QString qstrQuery = "select Name, Language, Type, Default from TechnicalReports where Class = \"" + p_qstrKeyname + "\"";
    CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrQuery);
    return pQuery;
}

/** +-=---------------------------------------------------------Mi 20. Feb 16:22:09 2013----------*
 * @method  CwmsReportManager::GetReportsByClassKeyname      // public                            *
 * @return  CdmQueryEnhanced*                                //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EwmsTemplateType p_eType                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Feb 16:22:09 2013----------*/
CdmQueryEnhanced* CwmsReportManager::GetReportsByClassKeyname(QString p_qstrKeyname,
                                                              EwmsTemplateType p_eType)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CdmQueryEnhanced* pQuery = nullptr;

    if (pCdmManager)
    {
        QString qstrLanguage = pCdmManager->GetCurrentLanguage();
        QString qstrQuery;

        if (!qstrLanguage.isEmpty())
        {
            qstrQuery = QString("select Name, Default from TechnicalReports where and(Class = \"%1\", Type = %2, Language = \"%3\")")
                    .arg(p_qstrKeyname)
                    .arg(p_eType)
                    .arg(pCdmManager->GetCurrentLanguage());
        }
        else
        {
            qstrQuery = QString("select Name, Default from TechnicalReports where and(Class = \"%1\", Type = %2)")
                    .arg(p_qstrKeyname)
                    .arg(p_eType);
        }

        pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrQuery);
    }

    return pQuery;
}

CdmQueryEnhanced* CwmsReportManager::GetReportsByClassKeynameAndLanguage(QString p_qstrKeyname,
                                                                         EwmsTemplateType p_eType,
                                                                         QString p_qstrLanguage)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CdmQueryEnhanced* pQuery = nullptr;

    if (pCdmManager)
    {

        QString qstrQuery = QString("select Name, Default from TechnicalReports where and(Class = \"%1\", Type = %2, Language = \"%3\")")
                .arg(p_qstrKeyname)
                .arg(p_eType)
                .arg(p_qstrLanguage);

        pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrQuery);
    }

    return pQuery;
}

/** +-=---------------------------------------------------------Mi 27. Feb 09:24:24 2013----------*
 * @method  CwmsReportManager::GetDefaultReportByClassKeyname // public                           *
 * @return  CwmsPrintingTemplate                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EwmsTemplateType p_eType                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Feb 09:24:24 2013----------*/
CwmsPrintingTemplate CwmsReportManager::GetDefaultReportByClassKeyname(QString p_qstrKeyname,
                                                                       EwmsTemplateType p_eType)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmsPrintingTemplate cTemplate;

    if (pCdmManager)
    {
        QString qstrLanguage = pCdmManager->GetCurrentLanguage();
        QString qstrQuery;

        if (!qstrLanguage.isEmpty())
        {
            qstrQuery = QString("select from TechnicalReports where and(Class = \"%1\", Type = %2, Language = \"%3\", Default = true)")
                    .arg(p_qstrKeyname)
                    .arg(p_eType)
                    .arg(pCdmManager->GetCurrentLanguage());
        }
        else
        {
            qstrQuery = QString("select from TechnicalReports where and(Class = \"%1\", Type = %2, Default = true)")
                    .arg(p_qstrKeyname)
                    .arg(p_eType);
        }

        CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrQuery);

        if (CHKPTR(pQuery) && pQuery->GetResultCount() > 0)
        {
            const QList<long>& qllResults = pQuery->GetResultList();
            long lObjectId = (*qllResults.begin());
            CdmObjectContainer* pList = GetObjectList();

            if (CHKPTR(pList))
            {
                CdmObject* pObject = pList->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    cTemplate.SetObject(pObject);
                }
            }
        }
    }

    return cTemplate;
}

bool CwmsReportManager::HasDefaultPrintingTemplate(CdmObject* p_pObject)
{
    CwmsReportManager cReportManager;
    CwmsPrintingTemplate cTemplate;
    const CdmClass* pClass = p_pObject->GetClass();

    if (CHKPTR(pClass))
    {
        cTemplate = cReportManager.GetDefaultReportByClassKeyname(pClass->GetFullQualifiedName(), eWmsTemplateTypeObject);
    }

    return cTemplate.IsValid();
}

bool CwmsReportManager::HasDefaultPrintingTemplate(CdmObjectContainer* p_pContainer)
{
    CwmsReportManager cReportManager;
    CwmsPrintingTemplate cTemplate;
    const CdmClass* pClass = p_pContainer->GetClass();

    if (CHKPTR(pClass))
    {
        cTemplate = cReportManager.GetDefaultReportByClassKeyname(pClass->GetFullQualifiedName(), eWmsTemplateTypeList);
    }

    return cTemplate.IsValid();
}


/** +-=---------------------------------------------------------Di 26. Feb 15:57:00 2013----------*
 * @method  CwmsReportManager::GetPdf                        // public                            *
 * @return  QByteArray                                       //                                   *
 * @param   long p_ObjectListId                              //                                   *
 * @param   QString p_qstrTemplate                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 26. Feb 15:57:00 2013----------*/
QByteArray CwmsReportManager::GetPdf(long p_ObjectListId, QString p_qstrTemplate)
{
    QByteArray qArray;
    CdmObjectContainer* pList = FindObjectListForPDFCreation(p_ObjectListId);

    if (CHKPTR(pList))
    {
        CwmsPrintingTemplate cTemplate = GetReport(p_qstrTemplate);

        if (cTemplate.IsValid())
        {
            IwmsPrinting* pPrinting = GetPrintingObject();

            if (CHKPTR(pPrinting))
            {
                pPrinting->AddObjectContainer("ObjectContainer", pList);
                pPrinting->SetTemplate(cTemplate);
                qArray = pPrinting->PrintPdfToByteArray();
                DELPTR(pPrinting);
            }
        }
    }

    return qArray;
}

/** +-=---------------------------------------------------------Di 26. Feb 15:57:38 2013----------*
 * @method  CwmsReportManager::GetPdf                        // public                            *
 * @return  QByteArray                                       //                                   *
 * @param   long p_ObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 26. Feb 15:57:38 2013----------*/
QByteArray CwmsReportManager::GetPdf(long p_ObjectListId)
{
    QByteArray qArray;
    CdmObjectContainer* pList = FindObjectListForPDFCreation(p_ObjectListId);

    if (CHKPTR(pList))
    {
        const CdmClass* pClass = pList->GetClass();

        if (CHKPTR(pClass))
        {
            CwmsPrintingTemplate cTemplate = GetDefaultReportByClassKeyname(pClass->GetKeyname(), eWmsTemplateTypeList);

            if (cTemplate.IsValid())
            {
                IwmsPrinting* pPrinting = GetPrintingObject();

                if (CHKPTR(pPrinting))
                {
                    pPrinting->AddObjectContainer("ObjectContainer", pList);
                    pPrinting->SetTemplate(cTemplate);
                    qArray = pPrinting->PrintPdfToByteArray();
                    DELPTR(pPrinting);
                }
            }
        }
    }

    return qArray;
}

/** +-=---------------------------------------------------------Di 26. Feb 15:57:19 2013----------*
 * @method  CwmsReportManager::GetPdf                        // public                            *
 * @return  QByteArray                                       //                                   *
 * @param   long p_ObjectListId                              //                                   *
 * @param   long p_ObjectId                                  //                                   *
 * @param   QString p_qstrTemplate                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 26. Feb 15:57:19 2013----------*/
QByteArray CwmsReportManager::GetPdf(long p_ObjectListId, long p_ObjectId, QString p_qstrTemplate)
{
    QByteArray qArray;
    CdmObjectContainer* pList = FindObjectListForPDFCreation(p_ObjectListId);

    if (CHKPTR(pList))
    {
        const CdmClass* pClass = pList->GetClass();

        if (CHKPTR(pClass))
        {
            CwmsPrintingTemplate cTemplate = GetReport(p_qstrTemplate);

            if (cTemplate.IsValid())
            {
                CdmObject* pObject = pList->FindObjectById(p_ObjectId);

                if (CHKPTR(pObject))
                {
                    IwmsPrinting* pPrinting = GetPrintingObject();

                    if (CHKPTR(pPrinting))
                    {
                        pPrinting->AddObject("Object", pObject);
                        pPrinting->SetTemplate(cTemplate);
                        qArray = CreatePDFOutput(*pPrinting);
                        DELPTR(pPrinting);
                    }
                }
            }
        }
    }

    return qArray;
}

/** +-=---------------------------------------------------------Di 26. Feb 15:57:52 2013----------*
 * @method  CwmsReportManager::GetPdf                        // public                            *
 * @return  QByteArray                                       //                                   *
 * @param   long p_ObjectListId                              //                                   *
 * @param   long p_ObjectId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 26. Feb 15:57:52 2013----------*/
QByteArray CwmsReportManager::GetPdf(long p_ObjectListId, long p_ObjectId)
{

    QByteArray qArray;
    CdmObjectContainer* pList = FindObjectListForPDFCreation(p_ObjectListId);

    if (CHKPTR(pList))
    {
        const CdmClass* pClass = pList->GetClass();

        if (CHKPTR(pClass))
        {
            CwmsPrintingTemplate cTemplate = GetDefaultReportByClassKeyname(pClass->GetKeyname(), eWmsTemplateTypeObject);

            if (cTemplate.IsValid())
            {
                CdmObject* pObject = pList->FindObjectById(p_ObjectId);

                if (CHKPTR(pObject))
                {
                    IwmsPrinting* pPrinting = GetPrintingObject();
                    pPrinting->AddObject("Object", pObject);
                    pPrinting->SetTemplate(cTemplate);
                    qArray = CreatePDFOutput(*pPrinting);
                    DELPTR(pPrinting);
                }
            }
        }
    }

    return qArray;
}

/** +-=---------------------------------------------------------Di 26. Feb 15:59:55 2013----------*
 * @method  CwmsReportManager::FindObjectListForPDFCreation  // private                           *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 26. Feb 15:59:55 2013----------*/
CdmObjectContainer* CwmsReportManager::FindObjectListForPDFCreation(long p_lObjectListId)
{
    CdmObjectContainer* pList = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager) && CHKPTR(pManager->GetCurrentScheme()))
    {
        CdmContainerManager* pOLManager = pManager->GetContainerManager(pManager->GetCurrentScheme()->GetId());

        if (CHKPTR(pOLManager))
        {
            pList = pOLManager->FindEmptyContainerById(p_lObjectListId);
        }
    }
    
    return pList;
}

/** +-=---------------------------------------------------------Mi 27. Feb 09:37:16 2013----------*
 * @method  CwmsReportManager::CreatePDFOutput               // private                           *
 * @return  QByteArray                                       //                                   *
 * @param   CwmsPrinting& p_rPrinting                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Feb 09:37:16 2013----------*/
QByteArray CwmsReportManager::CreatePDFOutput(IwmsPrinting& p_rPrinting)
{
    //QByteArray qbaPdf;
    return p_rPrinting.PrintPdfToByteArray();
    /*CdmManager* pManager = CdmSessionManager::GetManager();

   if (CHKPTR(pManager))
   {
      QString qstrFilename = QDir::tempPath() + "/" + QString::number(pManager->GetSessionId()) + "_" + QDateTime::currentDateTime().toString() + ".pdf";
      qstrFilename = qstrFilename.replace("-", "_");
      qstrFilename = qstrFilename.replace(":", "_");
      qstrFilename = qstrFilename.replace(" ", "_");
      p_rPrinting.PrintPdf(qstrFilename);

      QFile qFile(qstrFilename);

      if (qFile.open(QIODevice::ReadOnly))
      {
         qbaPdf = qFile.readAll();
      }
   }

   return qbaPdf;
           */
}


IwmsPrinting* CwmsReportManager::GetPrintingObject()
{
    IwmsPrinting* pPrinting = nullptr;
    CwmsContext* pContext = CwmsContext::GetContext();

    if (CHKPTR(pContext))
    {
        CwmsPluginManager* pPluginManager = pContext->GetPluginManager();

        if (CHKPTR(pPluginManager) && pPluginManager->HasPrintingPlugin())
        {
            pPrinting = pPluginManager->GetPrintingPlugin()->getPrinting();
        }
        else
        {
            CdmMessageManager::critical(tr("Druck Plugin nicht gefunden"),
                                        tr("Das Druck Plugin wurde nicht gefunden. Drucken nicht möglich!"));
        }
    }

    return pPrinting;
}


void CwmsReportManager::OpenReportEditor(long p_lObjectId, QWidget* p_pParent)
{
    CwmsReportManager cManager;
    OpenReportEditor(cManager.GetReport(p_lObjectId).GetObject(), p_pParent);
}

void CwmsReportManager::OpenReportEditor(CdmObject* p_pObject, QWidget* p_pParent)
{
    CwmsPluginManager* pPluginManager = CwmsContext::GetContext()->GetPluginManager();

    if (CHKPTR(pPluginManager) && pPluginManager->HasPrintingPlugin())
    {
        pPluginManager->GetPrintingPlugin()->OpenPrintingDesigner(p_pObject, p_pParent);
    }
    else
    {
        CdmMessageManager::critical(tr("Druck Plugin nicht gefunden"),
                                    tr("Der Druckausgabe Designer kann nicht geöffnet werden!"));
    }
}

void CwmsReportManager::PrintDefaultForContainer(CdmObjectContainer* p_pContainer)
{
    CwmsReportManager cReportManager;
    QString qstrTemplate;
    CdmQueryEnhanced* pQuery = nullptr;

    const CdmClass* pClass = p_pContainer->GetClass();

    if (CHKPTR(pClass))
    {
        pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetFullQualifiedName(),
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
        Print(cTemplate.GetObject(), p_pContainer);
    }
}

void CwmsReportManager::Print(CdmObject* p_pCdmTemplateObject, CdmObjectContainer* p_pContainer)
{
    CwmsPrintingTemplate cTemplate(p_pCdmTemplateObject);

    if (cTemplate.IsValid())
    {
        IwmsPrinting* pPrinting = CwmsReportManager::GetPrintingObject();

        if (CHKPTR(pPrinting))
        {
            if (p_pContainer != nullptr)
            {
                pPrinting->AddObjectContainer("ObjectContainer", p_pContainer);
                pPrinting->AddParameter("ContainerKeyname", p_pContainer->GetKeyname());
            }

            pPrinting->SetTemplate(cTemplate);
            pPrinting->Print();
            DELPTR(pPrinting);
        }
    }
}

void CwmsReportManager::PrintDefaultForObject(CdmObject* p_pObject)
{
    CwmsReportManager cReportManager;
    QString qstrTemplate;
    CdmQueryEnhanced* pQuery = nullptr;

    const CdmClass* pClass = p_pObject->GetClass();

    if (CHKPTR(pClass))
    {
        pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetFullQualifiedName(),
                                                         eWmsTemplateTypeObject);
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
        Print(cTemplate.GetObject(), p_pObject);
    }
}

void CwmsReportManager::Print(CdmObject* p_pCdmTemplateObject, CdmObject* p_pObject)
{
    CwmsReportManager cReportManager;
    CwmsPrintingTemplate cTemplate(p_pCdmTemplateObject);

    if (cTemplate.IsValid())
    {
        IwmsPrinting* pPrinting = cReportManager.GetPrintingObject();

        if (CHKPTR(pPrinting))
        {
            pPrinting->AddObject("Object", p_pObject);
            pPrinting->SetTemplate(cTemplate);
            pPrinting->PrintPreview();
            DELPTR(pPrinting);
        }
    }
}
