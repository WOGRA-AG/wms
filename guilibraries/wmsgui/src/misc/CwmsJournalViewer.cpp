// System and QT Includes
#include <QClipboard>
#include <QDate>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmScheme.h"
#include "CdmJournalItem.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsJournalViewer.h"

CwmsJournalViewer::CwmsJournalViewer(QWidget* p_pqwParent)
    : QDialog(p_pqwParent),
      m_rpCdmDatabase(nullptr),
      m_rpContainer(nullptr),
      m_rpCdmObject(nullptr)
{
    setupUi(this);
    SetFromToDefaultData();
}

CwmsJournalViewer::~CwmsJournalViewer()
{
}

void CwmsJournalViewer::FillDialog(CdmScheme* p_pCdmDtabase)
{
    ClearItems();
    if (!m_rpCdmDatabase)
    {
        AddDbHeader();
    }

    m_rpCdmDatabase = p_pCdmDtabase;

    if (CHKPTR(m_rpCdmDatabase))
    {
        m_pqtwJournal->clear();
        QList<CdmJournalItem*> qlItems;
        QDate qdFrom = m_pqdeFrom->date();
        QDate qdTo = m_pqdeTo->date();
        m_rpCdmDatabase->GetChanges(qdFrom, qdTo, qlItems);

        for (int iCounter = 0; iCounter < qlItems.count(); ++iCounter)
        {
            CdmJournalItem* pItem = qlItems[iCounter];

            if (CHKPTR(pItem))
            {
                QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwJournal);
                m_qmItems.insert(pqItem, pItem);
                pqItem->setText(0, pItem->GetUserString());
                pqItem->setText(1, pItem->GetModified().toString(Qt::SystemLocaleShortDate));
                pqItem->setText(2, pItem->GetChangeModeAsString());

                int iObjectListId = pItem->GetObjectListId();

                CdmObjectContainer* pContainer = m_rpCdmDatabase->GetContainerManager()->FindEmptyContainerById(iObjectListId);

                if (pContainer)
                {
                    pqItem->setText(3, pContainer->GetCaption());
                    int iObjectId = pItem->GetObjectId();

                    if (iObjectId > 0)
                    {
                        CdmObject* pCdmObject = pContainer->FindObjectById(iObjectId);

                        if (pCdmObject)
                        {
                            pqItem->setText(4, pCdmObject->GetCaption());
                            pqItem->setText(5, pItem->GetMemberAsString(pCdmObject));
                            pqItem->setText(6, pItem->GetDisplayString());
                        }
                    }
                }
            }
        }
    }
}

void CwmsJournalViewer::ClearItems()
{
    m_qmItems.clear();
}

void CwmsJournalViewer::FillDialog(CdmObjectContainer* p_pContainer)
{
    ClearItems();
    if (!m_rpContainer)
    {
        AddContainerHeader();
    }

    m_rpContainer = p_pContainer;


    if (CHKPTR(m_rpContainer))
    {
        m_pqtwJournal->clear();
        QList<CdmJournalItem*> qlItems;
        m_rpContainer->GetChanges(m_pqdeFrom->date(), m_pqdeTo->date(), qlItems);

        for (int iCounter = 0; iCounter < qlItems.count(); ++iCounter)
        {
            CdmJournalItem* pItem = qlItems[iCounter];

            if (CHKPTR(pItem))
            {
                QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwJournal);
                m_qmItems.insert(pqItem, pItem);
                pqItem->setText(0, pItem->GetUserString());
                pqItem->setText(1, pItem->GetModified().toString(Qt::SystemLocaleShortDate));
                pqItem->setText(2, pItem->GetChangeModeAsString());

                int iObjectId = pItem->GetObjectId();

                if (iObjectId > 0)
                {
                    CdmObject* pCdmObject = m_rpContainer->FindObjectById(iObjectId);

                    if (pCdmObject)
                    {
                        pqItem->setText(3, pCdmObject->GetCaption());
                        pqItem->setText(4, pItem->GetMemberAsString(pCdmObject));
                        pqItem->setText(5, pItem->GetDisplayString());
                    }
                }
            }
        }

    }
}

void CwmsJournalViewer::FillDialog(CdmObject* p_pCdmObject)
{
    ClearItems();
    if (!m_rpCdmObject)
    {
        AddObjectHeader();
    }

    m_rpCdmObject = p_pCdmObject;

    if (CHKPTR(m_rpCdmObject))
    {
        m_pqtwJournal->clear();
        QList<CdmJournalItem*> qlItems;
        m_rpCdmObject->GetChanges(m_pqdeFrom->date(), m_pqdeTo->date(), qlItems);

        for (int iCounter = 0; iCounter < qlItems.count(); ++iCounter)
        {
            CdmJournalItem* pItem = qlItems[iCounter];

            if (CHKPTR(pItem))
            {
                QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwJournal);
                m_qmItems.insert(pqItem, pItem);
                pqItem->setText(0, pItem->GetUserString());
                pqItem->setText(1, pItem->GetModified().toString(Qt::SystemLocaleShortDate));
                pqItem->setText(2, pItem->GetChangeModeAsString());
                pqItem->setText(3, pItem->GetMemberAsString(m_rpCdmObject));
                pqItem->setText(4, pItem->GetDisplayString());
            }
        }
    }
}

void CwmsJournalViewer::AddCommonHeaders(QStringList& qstrlHeader)
{
    qstrlHeader.append(tr("Anwender"));
    qstrlHeader.append(tr("Zeitpunkt"));
    qstrlHeader.append(tr("Änderungsart"));

}

void CwmsJournalViewer::AddDbHeader()
{
    QStringList qstrlHeader;
    AddCommonHeaders(qstrlHeader);
    qstrlHeader.append(tr("Container"));
    qstrlHeader.append(tr("Objekt"));
    qstrlHeader.append(tr("Variable"));
    qstrlHeader.append(tr("Wert"));
    m_pqtwJournal->setHeaderLabels(qstrlHeader);
}

void CwmsJournalViewer::AddContainerHeader()
{
    QStringList qstrlHeader;
    AddCommonHeaders(qstrlHeader);
    qstrlHeader.append(tr("Objekt"));
    qstrlHeader.append(tr("Variable"));
    qstrlHeader.append(tr("Wert"));
    m_pqtwJournal->setHeaderLabels(qstrlHeader);

}

void CwmsJournalViewer::AddObjectHeader()
{
    QStringList qstrlHeader;
    AddCommonHeaders(qstrlHeader);
    qstrlHeader.append(tr("Variable"));
    qstrlHeader.append(tr("Wert"));
    m_pqtwJournal->setHeaderLabels(qstrlHeader);
}

void CwmsJournalViewer::SetFromToDefaultData()
{
    m_pqdeTo->setDate(QDate::currentDate());
    m_pqdeFrom->setDate(QDate::currentDate().addDays(-30));
}

void CwmsJournalViewer::CopyToClipboardClickedSlot()
{
    QTreeWidgetItem* pItem = m_pqtwJournal->selectedItems().first();

    if (CHKPTR(pItem))
    {
        QString qstrText = QString("%s = %s").arg(pItem->text(3)).arg(pItem->text(4));

        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(qstrText);
    }
}

void CwmsJournalViewer::RestoreClickedSlot()
{
    QTreeWidgetItem* pqItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwJournal);

    if (pqItem)
    {
        CdmJournalItem* pJournal = m_qmItems[pqItem];

        if (CHKPTR(pJournal))
        {
            pJournal->RestoreValue();
            RefreshClickedSlot();
        }
    }
    else
    {
        ERR("No item selected.");
    }
}

void CwmsJournalViewer::RefreshClickedSlot()
{
    if (m_rpCdmDatabase)
    {
        FillDialog(m_rpCdmDatabase);
    }
    else if (m_rpCdmObject)
    {
        FillDialog(m_rpCdmObject);
    }
    else if (m_rpContainer)
    {
        FillDialog(m_rpContainer);
    }
}
