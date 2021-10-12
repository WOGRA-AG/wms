
// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsFormObjectRefAssignment.h"
#include "ui_CwmsFormObjectRefAssignment.h"

CwmsFormObjectRefAssignment::CwmsFormObjectRefAssignment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsFormObjectRefAssignment)
{
    ui->setupUi(this);
}

CwmsFormObjectRefAssignment::~CwmsFormObjectRefAssignment()
{
    delete ui;
}

void CwmsFormObjectRefAssignment::FillDialog(CdmClass* p_pClass)
{
   qint64 lClassId = 0;

    if (p_pClass)
    {
        lClassId = p_pClass->GetId();
    }

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

        if(CHKPTR(pIdmDataAccess) && CHKPTR(pCdmManager->GetCurrentScheme()))
        {
            QMap<qint64, QString> qmObjectLists;
            pIdmDataAccess->GetContainerList(pCdmManager->GetCurrentScheme()->GetId(),
                                             lClassId,
                                             qmObjectLists);



            QMap<qint64, QString>::iterator qmIt = qmObjectLists.begin();
            QMap<qint64, QString>::iterator qmItEnd = qmObjectLists.end();

            for(; qmIt != qmItEnd; ++qmIt)
            {
                QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(ui->m_pqlvObjectLists);
                pqlviItem->setText(0, QString::number(qmIt.key()));
                pqlviItem->setText(1, qmIt.value());

                if (qmObjectLists.count() == 1)
                {
                    pqlviItem->setSelected(true);
                }
            }
        }
    }

}


void CwmsFormObjectRefAssignment::ContainerClickedSlot()
{
    ui->m_pqlvObjectLists->setEnabled(true);
    ui->m_pqgbWql->setEnabled(false);
}

void CwmsFormObjectRefAssignment::WQLClickedSlot()
{
    ui->m_pqlvObjectLists->setEnabled(false);
    ui->m_pqgbWql->setEnabled(true);
}

bool CwmsFormObjectRefAssignment::Validate()
{
    bool bRet = true;

    if (GetReference().isEmpty())
    {
        CdmMessageManager::critical(tr("Fehlende Auswahl"), tr("Es wurde entweder kein Container gewählt, oder die WQL nicht ausgewählt."));
        bRet = false;
    }


    return bRet;
}


void CwmsFormObjectRefAssignment::OKClickedSlot()
{
    if (Validate())
    {
        accept();
    }
}

QString CwmsFormObjectRefAssignment::GetReference()
{
    QString qstrRef;

    if (ui->m_pqrbWql->isChecked())
    {
        qstrRef = ui->m_pqteWql->toPlainText();
    }
    else if (ui->m_pqrbContainer->isChecked())
    {
        qstrRef = GetSelectedObjectContainer();
    }

    return qstrRef;
}

QString CwmsFormObjectRefAssignment::GetSelectedObjectContainer()
{
    QString qstrKeyname;
    CdmObjectContainer* pContainer = nullptr;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

        if(CHKPTR(pContainerManager))
        {
            QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(ui->m_pqlvObjectLists);

            if(pqlviItem)
            {
                pContainer = pContainerManager->FindContainerById(pqlviItem->text(0).toLong());
            }
        }
    }

    if (pContainer)
    {
        qstrKeyname = pContainer->GetKeyname();
    }

    return qstrKeyname;
}


QString CwmsFormObjectRefAssignment::GetObjectReferenceSelection(QWidget* p_pParent, CdmClass* p_pClass)
{
    QString qstrRef;
    CwmsFormObjectRefAssignment dialog(p_pParent);
    dialog.FillDialog(p_pClass);

    if (dialog.exec() == QDialog::Accepted)
    {
        qstrRef = dialog.GetReference();
    }

    return qstrRef;
}
