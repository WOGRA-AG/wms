#include "CwmsEventClassEditor.h"
#include "ui_CwmsEventClassEditor.h"
#include "CdmLogging.h"

CwmsEventClassEditor::CwmsEventClassEditor(const CdmClass *pObjectClass, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CwmsEventClassEditor),
    m_pObjectClass(const_cast<CdmClass*>(pObjectClass)),
    m_pSelectedEventClass(nullptr)
{
    ui->setupUi(this);
}

CwmsEventClassEditor::~CwmsEventClassEditor()
{
    delete ui;
}

void CwmsEventClassEditor::FillCreateEventEditor()
{
    QStringList qstrlCreateEvents;
    qstrlCreateEvents.append(m_pObjectClass->getCreateEventClassStringList());
    if(!qstrlCreateEvents.isEmpty())
    {
        ui->m_pqcbClassEvents->addItems(qstrlCreateEvents);
    }
}

void CwmsEventClassEditor::FillDeleteEventEditor()
{
    QStringList qstrlDeleteEvents;
    qstrlDeleteEvents.append(m_pObjectClass->getDeleteEventClassStringList());
    if(!qstrlDeleteEvents.isEmpty())
    {
        ui->m_pqcbClassEvents->addItems(qstrlDeleteEvents);
    }
}

void CwmsEventClassEditor::FillUpdateEventEditor()
{
    QStringList qstrlUpdateEvents;
    qstrlUpdateEvents.append(m_pObjectClass->getUpdateEventClassStringList());
    if(!qstrlUpdateEvents.isEmpty())
    {
        ui->m_pqcbClassEvents->addItems(qstrlUpdateEvents);
    }
}

void CwmsEventClassEditor::OKClickedSlot()
{
    QString qstr_SelectedEvent = ui->m_pqcbClassEvents->currentText();
    CdmClassManager *pClassManager = m_pObjectClass->GetClassManager();
    CdmClass *pEventClass = pClassManager->findEventClassByKeyname(qstr_SelectedEvent);
    if(CHKPTR(pEventClass))
    {
        setSelectedEventClass(pEventClass);
        m_pObjectClass->setSelectedEventClass(getSelectedEventClass());
    }
    this->close();
}

void CwmsEventClassEditor::CancelClickedSlot()
{
    this->close();
}

void CwmsEventClassEditor::setSelectedEventClass(CdmClass *pSelEventClass)
{
    m_pSelectedEventClass = pSelEventClass;
}

CdmClass *CwmsEventClassEditor::getSelectedEventClass() const
{
    return m_pSelectedEventClass;
}
