/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsQueryEditor.cpp
 ** Started Implementation: 2012/07/26
 ** Description:
 **
 ** Implements the ui of the queryeditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QFileDialog>
#include <QTextStream>

//#include <QAbstractItemModel>

// WMS Includes
#include <CdmSystemVariables.h>
#include <CdmSessionManager.h>
#include <CdmContainerManager.h>
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmQueryBuilder.h"
#include "CdmQueryElement.h"
#include "CdmQueryEnhanced.h"
#include "CdmObject.h"

// Basetools includes
#include <CwmsTimeMeassurement.h>
#include "CwmsErrorCollector.h"

// own Includes
#include <CwmsQueryModelExportCsv.h>
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsTreeWidgetHelper.h"
#include "jshighlighter.h"
#include "CwmsView.h"
#include "CwmsViewEditor.h"
#include "CwmsQueryEditor.h"

CwmsQueryEditor::CwmsQueryEditor(QWidget* p_pqwParent)
    : QWidget(p_pqwParent),
      m_pCdmQuery(nullptr)
{
    setupUi(this);

    m_pqtvResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pqtvResult->setSelectionMode(QAbstractItemView::ContiguousSelection);
    m_pqteEditor->setTextWrapEnabled(false);
    m_pqteEditor->setCodeFoldingEnabled(true);
    m_pqteEditor->setLineNumbersVisible(true);

    QStringList qstrlSystemVariables = CdmSystemVariables::GetSystemVariables();
    m_pqcbSystemVariables->addItems(qstrlSystemVariables);
    m_pqteEditor->clear();
}

CwmsQueryEditor::~CwmsQueryEditor()
{
}

void CwmsQueryEditor::ExecuteClickedSlot()
{
    m_pqleState->setText(tr("Läuft..."));
    m_pqleResultCount->setText("-");
    m_pqleDuration->setText("");
    CdmMessageManager::StartAsyncMessageCollection();
    CwmsTimeMeassurement cTimeMeassure(false,"Wql");
    QString qstrQuery = m_pqteEditor->toPlainText();
    qstrQuery = qstrQuery.replace("\n", " ");
    CwmsErrorCollector cErrorCollector;
    CdmLogging::AddAdaptor(&cErrorCollector);

    if (m_pqsbMaxResults->isEnabled() && m_pqsbMaxResults->value() > 0)
    {
        m_cCdmModel.Execute(qstrQuery, m_pqsbMaxResults->value());
    }
    else
    {
        m_cCdmModel.Execute(qstrQuery);
    }

    CdmLogging::RemoveAdaptor(&cErrorCollector);

    if (cErrorCollector.HasEntries())
    {
        m_pqtwQueryAnalyzer->clear();
        m_pqtvResult->setModel(nullptr);
    }
    else
    {
        FillQueryAnalyzer(m_pqtwQueryAnalyzer, m_cCdmModel.GetQuery());
        m_pqtvResult->setModel(&m_cCdmModel);
    }

    QLocale loc;
    cTimeMeassure.finished();
    m_pqleDuration->setText(loc.toString(cTimeMeassure.GetCompleteDuration()) + " " + tr("msecs"));

    if (m_cCdmModel.GetQuery() && m_cCdmModel.GetQuery()->IsValid())
    {
        m_pqleState->setText(tr("OK"));
        m_pqleResultCount->setText(QString::number(m_cCdmModel.GetQuery()->GetResultCount()));
    }
    else
    {
        m_pqleState->setText(tr("Invalid Query"));
        m_pqleResultCount->setText("0");
    }

    CdmMessageManager::EndAndShowAsyncMessageCollection();
}

void CwmsQueryEditor::FillQueryAnalyzer(QTreeWidget* p_pqTreeWidget, CdmQuery* p_pQuery)
{
    p_pqTreeWidget->clear();

    if (CHKPTR(p_pQuery) && CHKPTR(p_pqTreeWidget))
    {
        QVector<QString> qvElements = p_pQuery->GetResultElements();

        QTreeWidgetItem* pqFields = new QTreeWidgetItem(p_pqTreeWidget);
        pqFields->setText(0, tr("Felder"));

        for (int iCounter = 0; iCounter < qvElements.count(); ++iCounter)
        {
            QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqFields);
            pqItem->setText(0, qvElements[iCounter]);
        }

        QTreeWidgetItem* pqConditions = new QTreeWidgetItem(p_pqTreeWidget);
        pqConditions->setText(0, tr("Bedingungen"));

        CdmQueryElement*  pCdmRoot = p_pQuery->GetQueryElement();

        if (pCdmRoot)
        {
            AddQueryElement(pCdmRoot, pqConditions);
        }

        if (pqConditions->childCount() == 0)
        {
            DELPTR(pqConditions)
        }

        CdmObjectContainer* pContainer = p_pQuery->GetContainer();

        if (pContainer)
        {
            QTreeWidgetItem* pqObjectList = new QTreeWidgetItem(p_pqTreeWidget);
            pqObjectList->setText(0, tr("Objektcontainer"));

            QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqObjectList);
            pqItem->setText(0, pContainer->GetKeyname());
        }
        else if(p_pQuery->GetClass())
        {
            const CdmClass* pClass = p_pQuery->GetClass();
            QTreeWidgetItem* pqObjectList = new QTreeWidgetItem(p_pqTreeWidget);
            pqObjectList->setText(0, tr("Klasse"));

            QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqObjectList);
            pqItem->setText(0, pClass->GetKeyname());
        }

        QString qstrSorting = p_pQuery->GetOrderBy().join(", ");

        if (!qstrSorting.isEmpty())
        {
            QTreeWidgetItem* pqSorting = new QTreeWidgetItem(p_pqTreeWidget);
            pqSorting->setText(0, tr("Sortierung"));

            QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqSorting);
            pqItem->setText(0, qstrSorting);
        }
    }
}

void CwmsQueryEditor::AddQueryElement(CdmQueryElement* p_pCdmElement, QTreeWidgetItem* p_pqParent)
{
    if (CHKPTR(p_pCdmElement) && CHKPTR(p_pqParent))
    {
        QTreeWidgetItem* pqItem = new QTreeWidgetItem(p_pqParent);

        if (p_pCdmElement->GetQueryElementType() == eDmQueryElementTypeAnd)
        {
            pqItem->setText(0, tr("UND"));
        }
        else if (p_pCdmElement->GetQueryElementType() == eDmQueryElementTypeOr)
        {
            pqItem->setText(0, tr("ODER"));
        }
        else
        {
            pqItem->setText(0, p_pCdmElement->GetConditionAsString());
        }

        if (p_pCdmElement->GetQueryElementType() != eDmQueryElementTypeCompare)
        {
            QList<CdmQueryElement*> qlChilds;
            p_pCdmElement->GetChildList(qlChilds);

            QList<CdmQueryElement*>::iterator qllIt = qlChilds.begin();
            QList<CdmQueryElement*>::iterator qllItEnd = qlChilds.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                AddQueryElement(*qllIt, pqItem);
            }
        }
    }
}

void CwmsQueryEditor::SaveClickedSlot()
{
    QMenu* pqMenu = new QMenu(this);
    pqMenu->addAction(tr("Datei"));
    pqMenu->addAction(tr("Sicht"));
    QAction* pqAction = pqMenu->exec(QCursor::pos());

    if (pqAction)
    {
        if (pqAction->text() == tr("Datei"))
        {
            QString qstrFilename = CwmsQueryModelExportCsv::AskForFilename(".wql");

            if (!qstrFilename.isEmpty())
            {
                CwmsQueryModelExportCsv::SaveContent(qstrFilename, m_pqteEditor->toPlainText());
            }
        }
        else
        {
            CwmsView cView = CwmsView::Create();

            if (cView.IsValid())
            {
                cView.SetViewCommand(m_pqteEditor->toPlainText());
                CwmsViewEditor::Edit(cView, true, this);
            }
        }
    }
}

void CwmsQueryEditor::EditClickedSlot()
{
    CdmObject* pObject = m_cCdmModel.GetObject(m_pqtvResult);

    if (pObject)
    {
        CwmsguiObjectEditorSelector::Edit(pObject, this);
    }
}

void CwmsQueryEditor::DeleteClickedSlot()
{
    QList<CdmObject*> qlObjects = m_cCdmModel.GetObjects(m_pqtvResult);
    CdmObjectContainer* pContainer = nullptr;

    for (int iPos = 0; iPos < qlObjects.count(); ++iPos)
    {
        CdmObject* pObject = qlObjects[iPos];
        if (pObject)
        {
            pObject->SetDeleted();

            if (!pContainer)
            {
                pContainer = pObject->GetObjectContainer();
            }
        }
    }

    if (pContainer)
    {
        pContainer->Commit();
    }

    ExecuteClickedSlot();
}


void CwmsQueryEditor::SaveResultClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(m_cCdmModel);
}

void CwmsQueryEditor::ClearResultClickedSlot()
{
    m_cCdmModel.Clear();
}


void CwmsQueryEditor::SystemVariablesChangedSlot(QString p_qstrText)
{
    m_pqteEditor->insertPlainText("${" + p_qstrText + "}");
}


void CwmsQueryEditor::QueryChangedSlot()
{
    QTextCursor cur = m_pqteEditor->textCursor();
    cur.movePosition(QTextCursor::PreviousCharacter,QTextCursor::KeepAnchor);
    QString qstrLastInsertedChar = cur.selectedText();

    if(qstrLastInsertedChar == " ")
    {
        QString qstrQuery = m_pqteEditor->toPlainText();
        QString qstrFromValue = qstrQuery.section("from",1,1);
        qstrFromValue = qstrFromValue.section(" ",1,1);
        const CdmClass* pClass = nullptr;

        if (!qstrFromValue.isEmpty())
        {
            if (qstrFromValue.contains(".class"))
            {
                QString qstrClassKeyname = qstrFromValue.section(".class",-1);
                CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

                if (CHKPTR(pClassManager))
                {
                    pClass = pClassManager->FindClassByKeyname(qstrClassKeyname);
                }
            }
            else
            {
                QString qstrContainerKeyname = qstrFromValue;
                CdmContainerManager* pContainerManager = CdmSessionManager::GetDataProvider()->GetContainerManager();

                if (CHKPTR(pContainerManager))
                {
                    CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerByKeyname(qstrContainerKeyname);

                    if (pContainer)
                    {
                        pClass = pContainer->GetClass();
                    }
                }
            }
        }

        if (pClass)
        {
            m_pqteEditor->SetClass(pClass);
        }
    }
}
