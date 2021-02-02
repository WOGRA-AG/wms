
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include <CdmObject.h>
#include <CdmObjectContainer.h>
#include <CwmsContainerEditorDlg.h>
#include "CdmContainerManager.h"
#include "CdmMessageManager.h"


#include "CwmsguiObjectEditorSelector.h"
#include "CwmsDataSearchDlg.h"
#include "ui_CwmsDataSearchDlg.h"


CwmsDataSearchDlg::CwmsDataSearchDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsDataSearchDlgClass)
{
    ui->setupUi(this);
    SearchTypeChangedSlot();
}

CwmsDataSearchDlg::~CwmsDataSearchDlg()
{
    delete ui;
}

void CwmsDataSearchDlg::SearchTypeChangedSlot()
{
    if (ui->m_pqrbContainer->isChecked())
    {
        ui->m_pqlObject->hide();
        ui->m_pqleObject->hide();
    }
    else
    {
        ui->m_pqlObject->show();
        ui->m_pqleObject->show();
    }
}

void CwmsDataSearchDlg::SearchModeChangedSlot()
{
    if (ui->m_pqrbObject->isChecked())
    {
        if (ui->m_pqrbUri->isChecked())
        {
            ui->m_pqleContainer->hide();
            ui->m_pqlContainer->hide();
        }
        else
        {
            ui->m_pqleContainer->show();
            ui->m_pqlContainer->show();
        }
    }
    else
    {
        ui->m_pqleContainer->show();
        ui->m_pqlContainer->show();
        ui->m_pqleObject->hide();
        ui->m_pqlObject->hide();
        ui->m_pqleObject->hide();
    }
}

void CwmsDataSearchDlg::SearchClickedSlot()
{
    if (ui->m_pqrbContainer->isChecked())
    {
        SearchContainer();
    }
    else
    {
        SearchObject();
    }
}

void CwmsDataSearchDlg::SearchContainer()
{
    if (ui->m_pqrbId->isChecked())
    {
        SearchContainerById();
    }
    else if (ui->m_pqrbKeyname->isChecked())
    {
        SearchContainerByKeyname();
    }
    else
    {
        SearchContainerByUri();
    }
}

void CwmsDataSearchDlg::SearchContainerById()
{
    long lContainerId = ui->m_pqleContainer->text().toInt();

    if (lContainerId > 0)
    {
        CdmContainerManager* pContainerManager = GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(lContainerId);

            if (pContainer)
            {
                OpenContainer(pContainer);
            }
            else
            {
                CdmMessageManager::critical(tr("Container nicht gefunden"), tr("Der Container wurde nicht gefunden"));
            }
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Falsche Eingaben"), tr("Es wird eine ID rößer 0 erwartet."));
    }
}

void CwmsDataSearchDlg::SearchContainerByKeyname()
{
    QString qstrContainer = ui->m_pqleContainer->text();

    if (!qstrContainer.isEmpty())
    {
        CdmContainerManager* pContainerManager = GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerByKeyname(qstrContainer);

            if (pContainer)
            {
                OpenContainer(pContainer);
            }
            else
            {
                CdmMessageManager::critical(tr("Container nicht gefunden"), tr("Der Container wurde nicht gefunden"));
            }
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Falsche Eingaben"), tr("Es ein Keyname für den Container erwartet."));
    }
}

void CwmsDataSearchDlg::SearchContainerByUri()
{
    QString qstrUri = ui->m_pqleContainer->text();

    if (!qstrUri.isEmpty())
    {
        CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pProvider))
        {
            CdmLocatedElement* pElement = pProvider->GetUriObject(qstrUri);

            if (CHKPTR(pElement))
            {
                CdmObjectContainer* pContainer = dynamic_cast<CdmObjectContainer*>(pElement);

                if (pContainer)
                {
                    OpenContainer(pContainer);
                }
                else
                {
                    CdmMessageManager::critical(tr("Uri ist kein Objekt"), tr("Die eingegebene Uri ist kein Objekt."));
                }
            }
            else
            {
                CdmMessageManager::critical(tr("Uri nicht gefunden"), tr("Die eingegebene Uri konnte nicht aufgelöst werden."));
            }
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Falsche Eingaben"), tr("Die Uri darf nicht leer sein."));
    }
}

void CwmsDataSearchDlg::SearchObject()
{
    if (ui->m_pqrbId->isChecked())
    {
        SearchObjectById();
    }
    else if (ui->m_pqrbKeyname->isChecked())
    {
        SearchObjectByKeyname();
    }
    else
    {
        SearchObjectByUri();
    }
}

void CwmsDataSearchDlg::SearchObjectById()
{
    CdmObject* pObject = nullptr;
    long lContainerId = ui->m_pqleContainer->text().toInt();
    long lObjectId = ui->m_pqleObject->text().toInt();

    if (lContainerId > 0 && lObjectId > 0)
    {
        CdmContainerManager* pContainerManager = GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(lContainerId);

            if (pContainer)
            {
                pObject = pContainer->FindObjectById(lObjectId);

                if (pObject)
                {
                    OpenObject(pObject);
                }
                else
                {
                    CdmMessageManager::critical(tr("Objekt nicht gefunden"), tr("Das Objekt wurde nicht gefunden"));
                }
            }
            else
            {
                CdmMessageManager::critical(tr("Container nicht gefunden"), tr("Der Container wurde nicht gefunden"));
            }
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Eingabefehler"), tr("Beide Eingaberfelder müssen eine ID sein. Such kann nicht durchgeführt werden."));
    }
}

CdmContainerManager* CwmsDataSearchDlg::GetContainerManager()
{
    CdmContainerManager* pContainerManager = nullptr;
    CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pProvider))
    {
        pContainerManager = pProvider->GetContainerManager();
    }

    return pContainerManager;
}

void CwmsDataSearchDlg::SearchObjectByKeyname()
{
    CdmObject* pObject = nullptr;
    QString qstrContainer = ui->m_pqleContainer->text();
    QString qstrObject = ui->m_pqleObject->text();

    if (!qstrContainer.isEmpty() && !qstrObject.isEmpty())
    {
        CdmContainerManager* pContainerManager = GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerByKeyname(qstrContainer);

            if (pContainer)
            {
                pObject = pContainer->FindObjectByKeyname(qstrObject);

                if (pObject)
                {
                    OpenObject(pObject);
                }
                else
                {
                    CdmMessageManager::critical(tr("Objekt nicht gefunden"), tr("Das Objekt wurde nicht gefunden"));
                }
            }
            else
            {
                CdmMessageManager::critical(tr("Container nicht gefunden"), tr("Der Container wurde nicht gefunden"));
            }
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Fehlende Angaben"), tr("Es muss sowohl der Container Keyname als auch der Objekt Keyname angegeben sein."));
    }
}

void CwmsDataSearchDlg::SearchObjectByUri()
{
    QString qstrUri = ui->m_pqleObject->text();

     CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pProvider))
    {
        CdmLocatedElement* pElement = pProvider->GetUriObject(qstrUri);

        if (CHKPTR(pElement))
        {
            CdmObject* pObject = dynamic_cast<CdmObject*>(pElement);

            if (pObject)
            {
                OpenObject(pObject);
            }
            else
            {
                CdmMessageManager::critical(tr("Uri ist kein Objekt"), tr("Die eingegebene Uri ist kein Objekt."));
            }
        }
        else
        {
            CdmMessageManager::critical(tr("Uri nicht gefunden"), tr("Die eingegebene Uri konnte nicht aufgelöst werden."));
        }
    }
}

void CwmsDataSearchDlg::OpenContainer(CdmObjectContainer* p_pContainer)
{
    if (CHKPTR(p_pContainer))
    {
        CwmsContainerEditorDlg cDlg(this);
        cDlg.SetContainer(p_pContainer);
        cDlg.exec();
    }
}


void CwmsDataSearchDlg::OpenObject(CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        CwmsguiObjectEditorSelector::Edit(p_pObject, this);
    }
}
