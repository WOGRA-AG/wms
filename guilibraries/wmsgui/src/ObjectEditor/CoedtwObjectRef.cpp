// System and QT Includes
#include <qlineedit.h>
#include <qlayout.h>
#include <qpushbutton.h>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmMember.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmValueObjectRef.h"
#include "CdmClass.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsguiObjectEditorIf.h"
#include "CoedtwObjectRef.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "cwmsobjectchoicecombobox.h"


CoedtwObjectRef::CoedtwObjectRef(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmValue, p_pqwParent),
      m_pqcbObjectChoice(nullptr),
      m_pqpbSelect(nullptr),
      m_pqpbEdit(nullptr),
      m_pqpbClear(nullptr),
      m_bProxyCreatedByThis(false),
      m_pqleObject(nullptr),
      m_bShowEditButton(true),
      m_pCwmsProxy(nullptr),
      m_pObjectEditor(nullptr),
      m_lObjectId(0)
{
    // nothing todo
}

CoedtwObjectRef::CoedtwObjectRef(const CdmMember *p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
      m_pqcbObjectChoice(nullptr),
      m_pqpbSelect(nullptr),
      m_pqpbEdit(nullptr),
      m_pqpbClear(nullptr),
      m_bProxyCreatedByThis(false),
      m_pqleObject(nullptr),
      m_bShowEditButton(true),
      m_pCwmsProxy(nullptr),
      m_pObjectEditor(nullptr),
      m_lObjectId(0)
{
}

CoedtwObjectRef::CoedtwObjectRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_pqcbObjectChoice(nullptr),
      m_pqpbSelect(nullptr),
      m_pqpbEdit(nullptr),
      m_pqpbClear(nullptr),
      m_bProxyCreatedByThis(false),
      m_pqleObject(nullptr),
      m_bShowEditButton(true),
      m_pCwmsProxy(nullptr),
      m_pObjectEditor(nullptr),
      m_lObjectId(0)
{

}

CoedtwObjectRef::~CoedtwObjectRef()
{
    if (m_bProxyCreatedByThis)
    {
        DELPTR(m_pCwmsProxy);
    }
}

void CoedtwObjectRef::SetProxy(CdmQueryModel* p_pCwmsProxy)
{
    m_pCwmsProxy = p_pCwmsProxy;
}

void CoedtwObjectRef::SetProxy(QString p_qstrWql)
{
    m_pCwmsProxy = new CdmQueryModel();
    m_pCwmsProxy->Execute(p_qstrWql);

    if (m_pqcbObjectChoice)
    {
        m_pqcbObjectChoice->SetContainer(m_pCwmsProxy->GetContainer());
    }

    m_bProxyCreatedByThis = true;
}

QWidget* CoedtwObjectRef::GetTabEditWidget(QWidget* p_pqwParent)
{
    if (!m_pObjectEditor)
    {
        m_pObjectEditor = new CwmsObjectEditor(p_pqwParent);
    }

    return m_pObjectEditor;
}

void CoedtwObjectRef::GetComboBoxEdit(QWidget* pqWidget, QHBoxLayout* pqLayout)
{
    m_pqcbObjectChoice = new CwmsObjectChoiceComboBox(pqWidget);

    if (m_pCwmsProxy)
    {
        m_pqcbObjectChoice->SetProxy(m_pCwmsProxy);
        m_pqcbObjectChoice->FillProxyData();
    }

    pqLayout->addWidget(m_pqcbObjectChoice);

    connect(m_pqcbObjectChoice,
            SIGNAL(activated(int)),
            this,
            SLOT(ValueChangedSlotByUser()));
}


void CoedtwObjectRef::GetComboBoxEdit(CdmObjectContainer* pContainer, QWidget* pqWidget, QHBoxLayout* pqLayout)
{
    if (m_qstrVisibleKeyname.isEmpty())
    {
        const CdmClass* pClass = pContainer->GetClass();

        if (CHKPTR(pClass))
        {
            const CdmMember* pMember = pClass->GetCaptionMember();

            if (pMember)
            {
                m_qstrVisibleKeyname = pMember->GetKeyname();
            }
        }
    }

    m_pqcbObjectChoice = new CwmsObjectChoiceComboBox(pqWidget);
    m_pqcbObjectChoice->SetContainerAndDisplayValue(pContainer,
                                                    m_qstrVisibleKeyname);

    if (m_pCwmsProxy)
    {
        m_pqcbObjectChoice->SetProxy(m_pCwmsProxy);
    }

    pqLayout->addWidget(m_pqcbObjectChoice);

    connect(m_pqcbObjectChoice,
            SIGNAL(activated(int)),
            this,
            SLOT(ValueChangedSlotByUser()));
}

void CoedtwObjectRef::GetSelectionEdit(QHBoxLayout* pqLayout, QWidget* pqWidget)
{
    if (!m_bShowEditButton)
    {
        pqLayout->addItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    }

    m_pqleObject = new QLineEdit(pqWidget);
    m_pqleObject->setReadOnly(true);
    pqLayout->addWidget(m_pqleObject);

    if (m_bShowEditButton)
    {
        m_pqpbEdit = new QPushButton(pqWidget);
        m_pqpbEdit->setToolTip(tr("Details"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/edit24.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pqpbEdit->setIcon(icon9);

        connect(m_pqpbEdit, SIGNAL(clicked()), this, SLOT(EditClickedSlot()));
        pqLayout->addWidget(m_pqpbEdit);
    }

    m_pqpbClear = new QPushButton(pqWidget);
    m_pqpbClear->setToolTip(tr("Auswahl entfernen"));
    QIcon icon9;
    icon9.addFile(QString::fromUtf8(":/icons/cancel24.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_pqpbClear->setIcon(icon9);
    connect(m_pqpbClear, SIGNAL(clicked()), this, SLOT(ClearClickedSlot()));
    pqLayout->addWidget(m_pqpbClear);

    m_pqpbSelect = new QPushButton(pqWidget);
    m_pqpbSelect->setToolTip(tr("Auswählen"));
    QIcon icon8;
    icon8.addFile(QString::fromUtf8(":/icons/search24.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_pqpbSelect->setIcon(icon8);
    connect(m_pqpbSelect, SIGNAL(clicked()),
            this, SLOT(ChooseClickedSlot()));
    pqLayout->addWidget(m_pqpbSelect);
}

QWidget* CoedtwObjectRef::GetEditWidget(QWidget* p_pqwParent)
{
    QWidget* pqWidget = new QWidget(p_pqwParent);
    QHBoxLayout* pqLayout = new QHBoxLayout(pqWidget);

    if(m_rpCdmValue)
    {
        CdmContainerManager* pCdmOLManager = m_rpCdmValue->GetContainerManager();

        if(CHKPTR(pCdmOLManager))
        {
            CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(m_qstrObjectList);

            if(pContainer && pContainer->CountObjectsOnDb() < 50)
            {
                GetComboBoxEdit(pContainer, pqWidget, pqLayout);
            }
            else if (m_pCwmsProxy)
            {
                GetComboBoxEdit(pqWidget, pqLayout);
            }
            else
            {
                pContainer = GetSingleObjectList();

                if(pContainer && pContainer->CountObjectsOnDb() < 50)
                {
                    GetComboBoxEdit(pContainer, pqWidget, pqLayout);
                }
                else
                {
                    GetSelectionEdit(pqLayout, pqWidget);
                }
            }
        }
    }
    else if (m_rpCdmMember)
    {
        GetSelectionEdit(pqLayout, pqWidget);
    }

    pqLayout->setMargin(0);
    return pqWidget;
}

void CoedtwObjectRef::SetValue(CdmValue* p_pCdmValue)
{
    if(p_pCdmValue)
    {
        if(m_pqleObject)
        {
            m_pqleObject->setText(p_pCdmValue->GetDisplayString());
        }
        else if (m_pqcbObjectChoice)
        {
            ((CdmValueObjectRef*)p_pCdmValue)->GetObject();
            m_pqcbObjectChoice->SetCurrentObjectId(((CdmValueObjectRef*)p_pCdmValue)->GetValue());
        }
        else if (m_pObjectEditor)
        {
            CdmObject* pCdmObject = ((CdmValueObjectRef*)p_pCdmValue)->GetObject();

            if (CHKPTR(pCdmObject))
            {
                m_pObjectEditor->SetObject(pCdmObject);
                m_pObjectEditor->FillObjectEditor();
            }
        }
    }
}

void CoedtwObjectRef::setEventClassValue()
{
    //not needed here
}

void CoedtwObjectRef::ValueChangedSlotByUser()
{
    if(CHKPTR(m_rpCdmValue))
    {
        CdmObject* pCdmObject = m_pqcbObjectChoice->GetSelectedObject();
        ((CdmValueObjectRef*)m_rpCdmValue)->SetValue(pCdmObject);
    }
}

void CoedtwObjectRef::EditClickedSlot()
{
    if(CHKPTR(m_rpCdmValue))
    {
        CdmObject* pCdmObject = ((CdmValueObjectRef*)m_rpCdmValue)->GetObject();

        if(pCdmObject)
        {
            CwmsguiObjectEditorIf* pCwmsObjectEditorIf = new CwmsguiObjectEditorIf(pCdmObject, nullptr);
            pCwmsObjectEditorIf->FillDialog();
            pCwmsObjectEditorIf->setWindowTitle(m_rpCdmValue->GetCaption());
            pCwmsObjectEditorIf->exec();
            delete pCwmsObjectEditorIf;
        }
        else
        {
            MSG_INFO(("Kein Object ausgewählt"),
                     ("Sie können kein Feld bearbeiten in dem kein Wert ausgewählt ist."));
        }
    }
}

void CoedtwObjectRef::ChooseClickedSlot()
{
    const CdmMember* pCdmMember = nullptr;

    if (m_rpCdmValue)
    {
        pCdmMember = m_rpCdmValue->GetMember();
    }
    else
    {
        pCdmMember= m_rpCdmMember;
    }

    if (CHKPTR(pCdmMember))
    {
        qint64 lClassId = pCdmMember->GetClassReference();
        CdmObjectContainer* pContainer = CwmsContainerSelectionIf::GetObjectContainer(pCdmMember->GetSchemeId(),
                                                                                      lClassId,
                                                                                      nullptr);

        if (pContainer) // can be nullptr if the user cancels the process
        {

            CdmObject* pCdmObject = nullptr;

            pCdmObject = CwmsObjectSelectionIf::GetObject(pContainer, nullptr, nullptr);

            if(pCdmObject)
            {
                if (m_rpCdmValue)
                {
                    ((CdmValueObjectRef*)m_rpCdmValue)->SetValue(pCdmObject);
                }
                else
                {
                    m_lObjectId = pCdmObject->GetId();
                }

                m_pqleObject->setText(pCdmObject->GetCaption());
            }
        }
    }
}

void CoedtwObjectRef::ClearClickedSlot()
{
    if(m_rpCdmValue)
    {
        const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

        if(CHKPTR(pCdmMember))
        {
            ((CdmValueObjectRef*)m_rpCdmValue)->SetValue(nullptr);

        }
    }
    else
    {
        m_lObjectId = 0;
    }

    m_pqleObject->setText("");
}

CdmObjectContainer* CoedtwObjectRef::GetSingleObjectList()
{
    CdmObjectContainer* pContainer = nullptr;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
            QMap<qint64, QString> qmObjectLists;
            const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

            if (CHKPTR(pCdmMember))
            {
                qint64 lClassId = pCdmMember->GetClassReference();

                if (lClassId > 0)
                {

                    pIdmDataAccess->GetContainerList(pCdmMember->GetSchemeId(),
                                                     lClassId,
                                                     qmObjectLists);


                    if(qmObjectLists.count() == 1)
                    {
                        QMap<qint64, QString>::iterator qmIt = qmObjectLists.begin();
                        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(pCdmMember->GetSchemeId());

                        if(CHKPTR(pContainerManager))
                        {
                            pContainer = pContainerManager->FindEmptyContainerById(qmIt.key());
                        }
                    }
                }
            }
        }
    }

    return pContainer;
}

void CoedtwObjectRef::SetReadOnly()
{
    if (m_pqleObject)
    {
        m_pqleObject->show();
    }

    if (m_pqcbObjectChoice)
    {
        m_pqcbObjectChoice->setEnabled(false);
    }

    if (m_pObjectEditor)
    {
        m_pObjectEditor->SetReadOnly(true);
    }

    if(m_pqpbSelect)
    {
        m_pqpbSelect->hide();
    }

    if (m_pqpbEdit)
    {
        m_pqpbEdit->hide();
    }

    if (m_pqpbClear)
    {
        m_pqpbClear->hide();
    }
}

void CoedtwObjectRef::SetEditable()
{
    if (m_pqleObject)
    {
        m_pqleObject->hide();
    }

    if (m_pqcbObjectChoice)
    {
        m_pqcbObjectChoice->setEnabled(true);
    }

    if (m_pObjectEditor)
    {
        m_pObjectEditor->SetReadOnly(false);
    }

    if(m_pqpbSelect)
    {
        m_pqpbSelect->show();
    }

    if (m_pqpbEdit)
    {
        m_pqpbEdit->show();
    }

    if (m_pqpbClear)
    {
        m_pqpbClear->show();
    }
}

void CoedtwObjectRef::HideEditButton()
{
    m_bShowEditButton = false;
}

void CoedtwObjectRef::SetContainer(QString p_qstrObjectList, QString p_qstrVisibleKeyname)
{
    m_qstrObjectList = p_qstrObjectList;
    m_qstrVisibleKeyname = p_qstrVisibleKeyname;
}


QWidget* CoedtwObjectRef::GetSearchWidget(QWidget* p_pqwParent)
{
    m_bShowEditButton = false;
    auto pWidget = GetEditWidget(p_pqwParent);
    return pWidget;
}

void CoedtwObjectRef::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
    if (CHKPTR(p_pCdmQueryElementParent))
    {
        if (m_lObjectId > 0)
        {
            CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                    eDmQueryElementTypeCompare,
                                                                    eDmQueryCompareTypeEqual);

            pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_lObjectId);
            p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
        }
    }
}

void CoedtwObjectRef::SetSearchDeaultValue(QString p_qstrDefault)
{
    m_pqleObject->setText(p_qstrDefault);
}
