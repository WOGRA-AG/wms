/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsWorkflowManager.cpp
 ** Started Implementation: 2012/08/24
 ** Description:
 **
 ** implements the manager for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QList>

// WMS Includes
#include "CdmMessageManager.h"
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
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"

// own Includes
#include "CwmsWorkflowManager.h"


/** +-=---------------------------------------------------------Fr 24. Aug 10:08:34 2012----------*
 * @method  CwmsWorkflowManager::CwmsWorkflowManager                 // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:08:34 2012----------*/
CwmsWorkflowManager::CwmsWorkflowManager()
{
    CheckWorkflowDataStructure();
}

/** +-=---------------------------------------------------------Fr 24. Aug 10:08:44 2012----------*
 * @method  CwmsWorkflowManager::~CwmsWorkflowManager                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsWorkflowManager                                               *
 *----------------last changed: --------------------------------Fr 24. Aug 10:08:44 2012----------*/
CwmsWorkflowManager::~CwmsWorkflowManager()
{
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:29:10 2012----------*
 * @method  CwmsWorkflowManager::CheckWorkflowDataStructure  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:29:10 2012----------*/
void CwmsWorkflowManager::CheckWorkflowDataStructure()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

        if (CHKPTR(pCdmClassManager))
        {
            CdmClass* pClass = pCdmClassManager->FindClassByKeyname("Workflow_Base");
            CdmPackage* pPackage = pCdmClassManager->FindPackageByName("Technical.Workflow");

            if (pClass && !pPackage)
            {
                RefactorClasses();
            }
            else if (!pPackage)
            {
               CreateClasses();
            }
        }
    }
}

/** +-=---------------------------------------------------------Fr 24. Aug 10:10:31 2012----------*
 * @method  CwmsWorkflowManager::GetObjectList                   // public                        *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:10:31 2012----------*/
CdmObjectContainer* CwmsWorkflowManager::GetObjectList()
{
    return CdmDataProvider::GetObjectContainer("WorkflowDefinitions");
}

/** +-=---------------------------------------------------------Mo 31. Dez 10:37:49 2012----------*
 * @method  CwmsWorkflowManager::GetWorkflowStepsObjectList  // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 10:37:49 2012----------*/
CdmObjectContainer* CwmsWorkflowManager::GetWorkflowStepsObjectList()
{
    return CdmDataProvider::GetObjectContainer("WorkflowSteps");
}


/** +-=---------------------------------------------------------Mo 22. Okt 15:30:59 2012----------*
 * @method  CwmsWorkflowManager::GetWorkflowList             // public                            *
 * @return  void                                             //                                   *
 * @param   QList<CdmObject*>& p_rqlViews              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:30:59 2012----------*/
void CwmsWorkflowManager::GetWorkflowList(QList<CdmObject*>& p_rqlViews)
{
    CdmObjectContainer* pContainer = GetObjectList();

    if (pContainer)
    {
        pContainer->GetObjectList(p_rqlViews);
    }
    else
    {
        ERR("Workflow Container not found.");
    }
}

/** +-=---------------------------------------------------------Fr 21. Dez 11:09:11 2012----------*
 * @method  CwmsWorkflowManager::FindWorkflowById            // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Dez 11:09:11 2012----------*/
CdmObject* CwmsWorkflowManager::FindWorkflowById(qint64 p_lObjectId)
{
    CdmObject* pObject = nullptr;
    CdmObjectContainer* pContainer = GetObjectList();

    if (CHKPTR(pContainer))
    {
        pObject = pContainer->FindObjectById(p_lObjectId);
    }

    return pObject;
}

/** +-=---------------------------------------------------------Fr 21. Dez 11:09:06 2012----------*
 * @method  CwmsWorkflowManager::FindWorkflowByName          // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Dez 11:09:06 2012----------*/
CdmObject* CwmsWorkflowManager::FindWorkflowByName(QString p_qstrName)
{
    CdmObject* pObject = nullptr;
    QString qstrWql = "select from WorkflowDefinitions where Name = \"" + p_qstrName +"\"";
    CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

    if (pQuery)
    {
        QList<qint64> qllResults = pQuery->GetResultList();

        if (qllResults.count() > 0)
        {
            pObject = FindWorkflowById(*(qllResults.begin()));
        }

        DELPTR(pQuery);
    }

    return pObject;
}

/** +-=---------------------------------------------------------Mo 31. Dez 10:10:38 2012----------*
 * @method  CwmsWorkflowManager::FindMajorWorkflowByClassUri // public                            *
 * @return  CwmsWorkflowDefinition                           //                                   *
 * @param   QString p_qstrClassUri                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 10:10:38 2012----------*/
CwmsWorkflowDefinition CwmsWorkflowManager::FindMajorWorkflowByClassUri(QString p_qstrClassUri)
{
    CwmsWorkflowDefinition cDef;
    QString qstrWql = "select from \"WorkflowDefinitions\" where and(Type = 0, Class = \"" + p_qstrClassUri + "\")";

    CdmQuery* pCdmQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

    if (CHKPTR(pCdmQuery))
    {
        int iResultCount = pCdmQuery->GetResultCount();

        if (iResultCount > 1)
        {
            MSG_WARN(("Mehrere Hauptprozesse vorhanden"),
                                       ("Zu dieser Klasse existieren mehrere Hauptprozesse. Der erst Gefundene wird verwendet!"));
        }


        CdmObject* pObject = pCdmQuery->GetFirstResultObject();

        if (pObject)
        {
            cDef.SetObject(pObject);
        }
        else
        {
            INFO("No Workflow found for the class " + p_qstrClassUri);
        }
    }

    return cDef;
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:50:29 2012----------*
 * @method  CwmsWorkflowManager::GetClassManager             // private                           *
 * @return  CdmClassManager*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:50:29 2012----------*/
CdmClassManager* CwmsWorkflowManager::GetClassManager()
{
    CdmClassManager* pCdmClassManager = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
    {
        pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());
    }

    return pCdmClassManager;
}

void CwmsWorkflowManager::RefactorClasses()
{
    CdmClassManager* pCdmClassManager = GetClassManager();
    CdmPackage* pPackage = pCdmClassManager->FindPackageByName("Technical");

    if (!pPackage)
    {
        pPackage = pCdmClassManager->CreatePackage("Technical");
    }

    pPackage = pCdmClassManager->CreatePackage("Workflow", pPackage);

    CdmClass* pClass = nullptr;
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Object");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Object");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Definition");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Definition");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Step_Definition");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Step_Definition");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Step_Successor");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Step_Successor");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Step_Execution");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Step_Execution");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Base");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Base");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Team");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Team");
    pClass->Commit();
    pClass = pCdmClassManager->FindClassByKeyname("Workflow_Escalation");
    pClass->SetPackage(pPackage);
    pClass->SetKeyname("Escalation");
    pClass->Commit();
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:36:23 2012----------*
 * @method  CwmsWorkflowManager::CreateClasses               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:36:23 2012----------*/
void CwmsWorkflowManager::CreateClasses()
{
    CdmClassManager* pCdmClassManager = GetClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        CdmPackage* pPackage = pCdmClassManager->FindPackageByName("Technical");

        if (!pPackage)
        {
            pPackage = pCdmClassManager->CreatePackage("Technical");
        }

        pPackage = pCdmClassManager->CreatePackage("Workflow", pPackage);


        CdmClass* pClass = nullptr;
        pClass = pCdmClassManager->CreateClass("Object");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Definition");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Step_Definition");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Step_Successor");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Step_Execution");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Base");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Team");
        pClass->SetPackage(pPackage);
        pClass = pCdmClassManager->CreateClass("Escalation");
        pClass->SetPackage(pPackage);

        CreateTeamClass(pCdmClassManager);
        CreateWorkflowBaseClass(pCdmClassManager);
        CreateWorkflowObjectClass(pCdmClassManager);
        CreateEscalationClass(pCdmClassManager);
        CreateWorkflowStepExecutionClass(pCdmClassManager);
        CreateWorkflowStepDefinitionClass(pCdmClassManager);
        CreateWorkflowDefinitionClass(pCdmClassManager);
        CreateWorkflowStepSuccessorClass(pCdmClassManager);

        CdmContainerManager* pCdmOLManager = pCdmClassManager->GetContainerManager();

        if (CHKPTR(pCdmOLManager))
        {
            CreateObjectLists(pCdmOLManager);
        }
    }
}

/** +-=---------------------------------------------------------Di 23. Okt 18:30:30 2012----------*
 * @method  CwmsWorkflowManager::CreateObjectLists           // private                           *
 * @return  void                                             //                                   *
 * @param   CdmContainerManager* p_pCmOLManager             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 23. Okt 18:30:30 2012----------*/
void CwmsWorkflowManager::CreateObjectLists(CdmContainerManager* p_pCmOLManager)
{
    if (CHKPTR(p_pCmOLManager))
    {
        QString qstrOLName = "Teams";
        p_pCmOLManager->CreateContainer("Technical.Workflow.Team", qstrOLName,
                                        tr("Teams"),
                                        tr("Liste von Teams im Unternehmen."));

        qstrOLName = "WorkflowSteps";
        p_pCmOLManager->CreateContainer("Technical.Workflow.Step_Execution", qstrOLName,
                                        tr("Arbeitsschritte"),
                                        tr("Liste von durchzuführenden Arbeitsschritten"));

        qstrOLName = "WorkflowDefinitions";
        p_pCmOLManager->CreateContainer("Technical.Workflow.Definition", qstrOLName,
                                        tr("Workflows"),
                                        tr("Liste der definierten Workflows"));
    }
}

/** +-=---------------------------------------------------------Di 23. Okt 18:42:07 2012----------*
 * @method  CwmsWorkflowManager::CreateWorkflowDefinitionClass // private                         *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 23. Okt 18:42:07 2012----------*/
void CwmsWorkflowManager::CreateWorkflowDefinitionClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Definition");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Geschäftsprozess"));
        pCdmClass->SetComment(tr("Diese Klasse definiert einen Geschäftsprozess."));

        CdmMember* pCdmMember = pCdmClass->CreateMember("Workflow",
                                                        eDmValueContainerRef,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Arbeitsschritte hinter dem Geschäftsprozess"));
            pCdmMember->SetClassReference("Technical.Workflow.Step_Definition");
            pCdmMember->SetCaption(tr("Arbeitsschritte"));
            pCdmMember->SetOwner(true);
        }

        pCdmMember = pCdmClass->CreateMember("Description",
                                             eDmValueCharacterDocument,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Beschreibung des Geschäftsprozess"));
            pCdmMember->SetCaption(tr("Beschreibung"));
        }

        pCdmMember = pCdmClass->CreateMember("Name",
                                             eDmValueString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Name des Geschäftsprozesses"));
            pCdmMember->SetCaption(tr("Name"));
        }

        pCdmMember = pCdmClass->CreateMember("Type",
                                             eDmValueEnum,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Art des Geschäftsprozesses"));
            pCdmMember->SetCaption(tr("Art"));
            pCdmMember->SetValidationCode(tr("Hauptprozess, Subprozess"));
        }

        pCdmMember = pCdmClass->CreateMember("Class",
                                             eDmValueString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die URI für welche Workflow Objekte der Workflow eingesetzt werden kann"));
            pCdmMember->SetCaption(tr("Referenz"));
        }

        pCdmClass->SetCaptionMember("Name");
        pCdmClass->Commit();
    }
}


/** +-=---------------------------------------------------------Mo 22. Okt 15:43:02 2012----------*
 * @method  CwmsWorkflowManager::CreateWorkflowObjectClass   // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:43:02 2012----------*/
void CwmsWorkflowManager::CreateWorkflowObjectClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Object");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Geschäftsprozessobjekt"));
        pCdmClass->SetComment(tr("Auf Basis dieser Klasse werden Geschäftsprozesse ausgeführt."));
        pCdmClass->SetAbstract(true);

        CdmMember* pCdmMember = pCdmClass->CreateMember("State",
                                                        eDmValueEnum,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Status der Bearbeitung"));
            pCdmMember->SetCaption(tr("Status"));
            pCdmMember->SetValidationCode(tr("Offen, In Prüfung, In Arbeit, Erledigt, Nicht berechtigt, Geschlossen"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
        }

        pCdmMember = pCdmClass->CreateMember("Name",
                                             eDmValueString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Name des Prozesses"));
            pCdmMember->SetCaption(tr("Name"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
        }

        pCdmMember = pCdmClass->CreateMember("Creator",
                                             eDmValueUser,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Anwender, der den Prozess erstellt/gestartet hat"));
            pCdmMember->SetCaption(tr("Ersteller"));
            pCdmMember->SetDefaultValue("${USER}");
        }

        pCdmMember = pCdmClass->CreateMember("Description",
                                             eDmValueCharacterDocument,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Beschreibung des Prozesses"));
            pCdmMember->SetCaption(tr("Beschreibung"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
        }

        pCdmMember = pCdmClass->CreateMember("Done_Steps",
                                             eDmValueListObjects,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Liste aller Schritte die bereits erledigt wurden."));
            pCdmMember->SetCaption(tr("Erledigte Schritte"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
        }

        pCdmMember = pCdmClass->CreateMember("Current_Steps",
                                             eDmValueListObjects,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Liste der in Arbeit befindlichen Arbeittschritte."));
            pCdmMember->SetCaption(tr("Aktuelle Arbeitsschritte"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
        }

        pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Mi 24. Okt 15:17:15 2012----------*
 * @method  CwmsWorkflowManager::CreateWorkflowStepExecutionClass // private                      *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 15:17:15 2012----------*/
void CwmsWorkflowManager::CreateWorkflowStepExecutionClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Step_Execution");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Arbeitsschrittausführung"));
        pCdmClass->SetComment(tr("Diese Klasse definiert die Ausführung eines Arbeitsschritts"));

        CdmMember* pCdmMember = pCdmClass->CreateMember("Current_State",
                                                        eDmValueEnum,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Status des Arbeitsschritts"));
            pCdmMember->SetValidationCode(tr("Offen, In Arbeit, Erledigt"));
            pCdmMember->SetCaption(tr("Status"));
        }

        pCdmMember = pCdmClass->CreateMember("Editor",
                                             eDmValueUser,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Bearbeiter des Arbetisschritts"));
            pCdmMember->SetCaption(tr("Bearbeiter"));
        }

        pCdmMember = pCdmClass->CreateMember("Current_Escalation_Step",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die aktuelle Eskalationsstufe des Arbeitsschritts."));
            pCdmMember->SetCaption(tr("Aktuelle Eskalationsstufe"));
            pCdmMember->SetClassReference("Technical.Workflow.Escalation");
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
        }

        pCdmMember = pCdmClass->CreateMember("Next_Escalation_Date",
                                             eDmValueDate,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Das Datum wann die nächste Eskalationsstufe erreicht wird"));
            pCdmMember->SetCaption(tr("Ablaufdatum nächste Eskalation"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
        }

        pCdmMember = pCdmClass->CreateMember("Technical.Workflow.Step",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der aktuelle Arbeitsschritt"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetClassReference("Technical.Workflow.Step_Definition");
            pCdmMember->SetCaption(tr("Arbeitsschritt"));
        }

        pCdmMember = pCdmClass->CreateMember("Current_Sub_Technical.Workflow.Step",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der aktuelle Arbeitsschritt im Subprozess"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetClassReference("Technical.Workflow.Step_Execution");
            pCdmMember->SetCaption(tr("Subprozess-Arbeitsschritt"));
        }

        pCdmMember = pCdmClass->CreateMember("Technical.Workflow.Object",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Zuordnung zum Technical.Workflow.Objekt auf dessen Basis der Workflow ausgeführt wird."));
            pCdmMember->SetCaption(tr("Arbeitsschritte Objekt"));
            pCdmMember->SetClassReference("Technical.Workflow.Object");
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
        }

        pCdmMember = pCdmClass->CreateMember("Parent",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der übergeordnete Workflow Step falls ein Subworkflow aufgerufen wurde."));
            pCdmMember->SetCaption(tr("Vater-Ausführungsobjekt"));
            pCdmMember->SetClassReference("Technical.Workflow.Step_Execution");
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
        }

        pCdmClass->AddBaseClass("Technical.Workflow.Base");
        pCdmClass->SetCaptionMember("Name");
        pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Mi 24. Okt 15:16:55 2012----------*
 * @method  CwmsWorkflowManager::CreateWorkflowBaseClass     // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 15:16:55 2012----------*/
void CwmsWorkflowManager::CreateWorkflowBaseClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Base");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Arbeitsschritt Defintion Basis"));
        pCdmClass->SetComment(tr("Diese Klasse definiert die Basiseigenschaften eines Arbeitsschritts"));
        pCdmClass->SetAbstract(true);

        CdmMember* pCdmMember = pCdmClass->CreateMember("Responsibility",
                                                        eDmValueObjectRef,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Das verantwortliche Team für diesen Arbeitsschritt"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetClassReference("Technical.Workflow.Team");
            pCdmMember->SetCaption(tr("Verantwortungsbereich"));
        }

        pCdmMember = pCdmClass->CreateMember("Position",
                                             eDmValueCounter,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Nummer des Prozessschritts."));
            pCdmMember->SetCaption(tr("Nummer"));
        }

        pCdmMember = pCdmClass->CreateMember("Name",
                                             eDmValueString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Bezeichnung der Tätigkeit"));
            pCdmMember->SetCaption(tr("Tätigkeit"));
        }

        pCdmMember = pCdmClass->CreateMember("Description",
                                             eDmValueCharacterDocument,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Beschreibung der Tätigkeit"));
            pCdmMember->SetCaption(tr("Tätigkeitsbschreibung"));
        }

        pCdmMember = pCdmClass->CreateMember("State",
                                             eDmValueEnum,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Wert auf den Sich der Status ändert, sobald die Aufgabe in Arbeit ist."));
            pCdmMember->SetCaption(tr("Statusänderung"));
            pCdmMember->SetValidationCode(tr("Offen, In Prüfung, In Arbeit, Erledigt, Nicht berechtigt, Geschlossen"));
        }

        pCdmMember = pCdmClass->CreateMember("Max_Duration",
                                             eDmValueInt,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Maximale Abarbeitungsdauer in Tagen"));
            pCdmMember->SetCaption(tr("Max. Abarbeitungsdauer"));
        }

        pCdmClass->SetCaptionMember("Name");
        pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Mi 24. Okt 15:16:33 2012----------*
 * @method  CwmsWorkflowManager::CreateWorkflowStepDefinitionClass // private                     *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 15:16:33 2012----------*/
void CwmsWorkflowManager::CreateWorkflowStepDefinitionClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Step_Definition");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Arbeitsschritt Defintion"));
        pCdmClass->SetComment(tr("Diese Klasse definiert die Definition eines Arbeitsschritts"));

        CdmMember* pCdmMember = pCdmClass->CreateMember("Escalation",
                                                        eDmValueContainerRef,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Eskalationsschritte"));
            pCdmMember->SetClassReference("Technical.Workflow.Escalation");
            pCdmMember->SetCaption(tr("Eskalationsschritte"));
            pCdmMember->SetOwner(true);
        }

        pCdmMember = pCdmClass->CreateMember("Sub_Workflow",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Subgeschäftsprozess der bei diesem Schritt parallel gestartet wird."));
            pCdmMember->SetClassReference("Technical.Workflow.Definition");
            pCdmMember->SetCaption(tr("Subgeschäftsprozesse"));
        }

        pCdmMember = pCdmClass->CreateMember("Successor",
                                             eDmValueContainerRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Nachfolger auf diesen Schritt."));
            pCdmMember->SetClassReference("Technical.Workflow.Step_Successor");
            pCdmMember->SetCaption(tr("Nachfolger"));
            pCdmMember->SetOwner(true);
        }

        pCdmMember = pCdmClass->CreateMember("Hidden_Members",
                                             eDmValueListString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die versteckten Felder der Geschäftsprozess-Objekts (nicht sichtbar und nicht editierbar)"));
            pCdmMember->SetCaption(tr("Versteckte Felder"));
        }

        pCdmMember = pCdmClass->CreateMember("ReadOnly_Members",
                                             eDmValueListString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Felder des Geschäftsprozess-Objekts die nicht editierbar sind(nur sichtbar und nicht editierbar)"));
            pCdmMember->SetCaption(tr("Felder mit Lesezugriff"));
        }

        pCdmMember = pCdmClass->CreateMember("Type",
                                             eDmValueEnum,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Typ des Prozessschritts: Start, Laufend, Entscheidung oder Ende"));
            pCdmMember->SetCaption(tr("Typ"));
            pCdmMember->SetValidationCode(tr("Start, Laufend, Entscheidung, Ende"));
        }

        pCdmMember = pCdmClass->CreateMember("Changing_Values",
                                             eDmValueDictStringString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Felder die sich beim Geschäftsprozess ändern, wenn dieser Schritt beginnt."));
            pCdmMember->SetCaption(tr("Eintrittsänderungsfelder"));
        }

        pCdmClass->AddBaseClass("Technical.Workflow.Base");
        pCdmClass->SetCaptionMember("Name");
        pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Mi 24. Okt 15:21:32 2012----------*
 * @method  CwmsWorkflowManager::CreateWorkflowStepSuccessorClass // private                      *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 15:21:32 2012----------*/
void CwmsWorkflowManager::CreateWorkflowStepSuccessorClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Step_Successor");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Arbeitsschritt Nachfolger"));
        pCdmClass->SetComment(tr("Durch diese Klasse können die Nachfolger definiert werden."));

        CdmMember* pCdmMember = pCdmClass->CreateMember("ID",
                                                        eDmValueCounter,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Nummer des Nachfolgers"));
            pCdmMember->SetCaption(tr("Nummer"));
        }

        pCdmMember = pCdmClass->CreateMember("Successor",
                                             eDmValueObjectRef,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Nachfolger auf den aktuellen Prozessschritt"));
            pCdmMember->SetClassReference("Technical.Workflow.Step_Definition");
            pCdmMember->SetCaption(tr("Nachfolger"));
        }

        pCdmMember = pCdmClass->CreateMember("Condition",
                                             eDmValueCharacterDocument,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Bedingung, die erfüllt sein muss um ein gültiger Nachfolger sein zu können."));
            pCdmMember->SetCaption(tr("Bedingung"));
            pCdmMember->SetClassReference(edmStringDisplayTypeUnFormatted);
        }

        pCdmClass->SetCaptionMember("Successor");
        pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:44:42 2012----------*
 * @method  CwmsWorkflowManager::CreateEscalationClass       // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:44:42 2012----------*/
void CwmsWorkflowManager::CreateEscalationClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Escalation");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Eskalation"));
        pCdmClass->SetComment(tr("Die Definition von Eskalationsstufen für einen Prozessschritt."));

        CdmMember* pCdmMember = pCdmClass->CreateMember("Employees",
                                                        eDmValueListInt,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die zu informierenden Mitarbeiter"));
            pCdmMember->SetCaption(tr("Mitarbeiter"));
        }

        pCdmMember = pCdmClass->CreateMember("Violation_Of_Limit",
                                             eDmValueInt,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Überschreitung des max. Bearbeitungszeitraums in Tagen."));
            pCdmMember->SetCaption(tr("Überschreitung in Tage"));
        }

        pCdmMember = pCdmClass->CreateMember("Escalation_Step",
                                             eDmValueInt,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Eskalationsschrittsnummer (Reihenfolge der Eskalation)"));
            pCdmMember->SetCaption(tr("Eskalationsschritt"));
        }

        pCdmClass->SetCaptionMember("Escalation_Step");
        pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:44:51 2012----------*
 * @method  CwmsWorkflowManager::CreateTeamClass             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:44:51 2012----------*/
void CwmsWorkflowManager::CreateTeamClass(CdmClassManager* p_pCdmClassManager)
{
    CdmClass* pCdmClass = p_pCdmClassManager->FindClassByKeyname("Technical.Workflow.Team");

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->SetCaption(tr("Team"));
        pCdmClass->SetComment(tr("Die definierten Teams innerhalb des Unternehmens"));

        CdmMember* pCdmMember = pCdmClass->CreateMember("Name",
                                                        eDmValueString,
                                                        false,
                                                        0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Bezeichnung des Teams"));
            pCdmMember->SetCaption(tr("Name"));
        }

        pCdmMember = pCdmClass->CreateMember("E-Mail",
                                             eDmValueString,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Der Mailverteiler des Teams"));
            pCdmMember->SetCaption(tr("E-Mail"));
        }

        pCdmMember = pCdmClass->CreateMember("Usergroup",
                                             eDmValueUserGroup,
                                             false,
                                             0);

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->SetComment(tr("Die Benutzergruppe innerhalb der das Team zusammengestellt ist."));
            pCdmMember->SetCaption(tr("Benutzergruppe"));
        }

        pCdmClass->SetCaptionMember("Name");
        pCdmClass->Commit();
    }
}

