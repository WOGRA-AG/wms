// System and QT Includes
#include <qlabel.h>
#include <qlineedit.h>
#include <QGroupBox>
#include <QList>
#include <QLayout>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <QSpacerItem>
#include <QMargins>
#include <QComboBox>
#include <CdmSessionManager.h>


// WMS Includes
#include "CdmClassMethod.h"
#include "CdmClass.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmMessageManager.h"
#include <CdmLogging.h>
#include <CdmObject.h>
#include <CdmClass.h>
#include "CdmClassGroup.h"
#include <CdmValue.h>
#include "CdmDataProvider.h"
#include <CdmMember.h>
#include <CdmContainerManager.h>
#include <CdmObjectContainer.h>
#include "CdmPackage.h"

// own Includes
#include "CwmsListWidgetHelper.h"
#include "CwmsFormObject.h"
#include "CwmsRuntime.h"
#include "CwmsHelp.h"
#include "IwmsPrinting.h"
#include "CwmsReportManager.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsJournalViewer.h"
#include "CoeDataTypeWidget.h"
#include "CoedtwObjectRef.h"
#include "CwmsObjectEditor.h"

CwmsObjectEditor::CwmsObjectEditor(CdmObject* p_pCdmObject, QWidget* p_pqwParent)
    : QWidget(p_pqwParent),
      m_pqwContainter(nullptr),
      m_cCdmObjectAdaptor(p_pCdmObject),
      m_bReadOnly(false),
      m_bShowEditButton(true),
      m_bHideSystemMembers(false),
      m_rpCdmPrintingTemplate(nullptr),
      m_bOwnerMode(true),
      m_pToolBar(nullptr),
      m_pMenu(nullptr),
      m_bIsObjEventEditor(false),
      m_bCheckEventMode(false),
      m_pCoeValueWidget(nullptr),
      m_bIsUpdateEvent(false)
{
    setupUi(this);

    if (!CdmSessionManager::GetDataProvider()->IsLoggedInUserAdmin())
    {
        m_pqpbMetaData->hide();
    }

}

CwmsObjectEditor::CwmsObjectEditor(QWidget* p_pqwParent)
    : QWidget(p_pqwParent),
      m_pqwContainter(nullptr),
      m_cCdmObjectAdaptor(),
      m_bReadOnly(false),
      m_bShowEditButton(true),
      m_bHideSystemMembers(false),
      m_rpCdmPrintingTemplate(nullptr),
      m_bOwnerMode(true),
      m_pToolBar(nullptr),
      m_pMenu(nullptr),
      m_bIsObjEventEditor(false)
{
    setupUi(this);

    if (!CdmSessionManager::GetDataProvider()->IsLoggedInUserAdmin())
    {
        m_pqpbMetaData->hide();
    }
}

CwmsObjectEditor::~CwmsObjectEditor(  )
{
}

void CwmsObjectEditor::SetObject(CdmObject* p_pCdmObject)
{
    m_cCdmObjectAdaptor.SetObject(p_pCdmObject);

    if (p_pCdmObject)
    {
        m_bReadOnly = p_pCdmObject->IsReadOnly();
        m_pqpbPrint->hide();

        if (CwmsReportManager::HasDefaultPrintingTemplate(p_pCdmObject) || m_rpCdmPrintingTemplate)
        {
            m_pqpbPrint->show();
        }
    }
}

CdmObject* CwmsObjectEditor::GetObject()
{
    return m_cCdmObjectAdaptor.GetObject();
}

void CwmsObjectEditor::SetReadOnly(bool p_bReadOnly)
{
    m_bReadOnly = p_bReadOnly;
}

void CwmsObjectEditor::SetSystemMembersHidden(bool p_bHidden)
{
    m_bHideSystemMembers = p_bHidden;
}

bool CwmsObjectEditor::IsSystemMembersHidden()
{
    return m_bHideSystemMembers;
}

bool CwmsObjectEditor::IsReadOnly(  )
{
    return m_bReadOnly;
}

void CwmsObjectEditor::SetShowEditButton(bool p_bShow)
{
    m_bShowEditButton = p_bShow;
}

bool CwmsObjectEditor::ShowEditButton()
{
    return m_bShowEditButton;
}

void CwmsObjectEditor::AddHiddenValue(  QString p_qstrKeyname )
{
    m_qstrlHiddenValues.append(p_qstrKeyname);
}

void CwmsObjectEditor::AddReadOnlyValue(  QString p_qstrKeyname )
{
    m_qstrlReadOnlyValues.append(p_qstrKeyname);
}

void CwmsObjectEditor::DeactivateOwnerMode()
{
    m_bOwnerMode = false;
}

void CwmsObjectEditor::AddObjectRefData(QString p_qstrValue,
                                        QString p_qstrObjectListKeyname,
                                        QString p_qstrObjectValue )
{
    TStringPair tStringPair(p_qstrObjectListKeyname, p_qstrObjectValue);
    m_qmObjectRefs.insert(p_qstrValue, tStringPair);
}

void CwmsObjectEditor::AddObjectRefData(QString p_qstrValue,
                                        QString p_qstrWql)
{
    TStringPair tStringPair(p_qstrWql, "");
    m_qmObjectRefs.insert(p_qstrValue, tStringPair);
}


void CwmsObjectEditor::SetDisplayType(QString p_qstrValue, EdmStringDisplayType p_EoeDisplayType)
{
    m_qmDisplayType.insert(p_qstrValue, p_EoeDisplayType);
}

void CwmsObjectEditor::AddProxy(QString p_qstrKeyname, CdmQueryModel* p_pCwmsProxy)
{
    if (CHKPTR(p_pCwmsProxy))
    {
        m_qmProxies[p_qstrKeyname] = p_pCwmsProxy;
    }
}

void CwmsObjectEditor::FillObjectEditor(  )
{
    if (GetObject())
    {
        if (!GetObject()->IsDeleted())
        {
            BuildWidget();
            AddFunctions();
        }
        else
        {
            ERR("Not possible to edit an deleted object.")
        }
    }
    else
    {
        BuildWidget();
    }
}

void CwmsObjectEditor::BuildWidget()
{
    m_qlAddedMembers.clear();

    if (GetObject())
    {
        FillGroups();
    }
    else
    {
        m_pqwContainter = nullptr;
    }
}

void CwmsObjectEditor::FillGroups()
{
    CdmObject* pCdmObject = GetObject();
    CdmClass* pCdmClass = pCdmObject->GetClass();

    if (CHKPTR(pCdmClass))
    {
        if (pCdmClass->HasGroups())
        {
            AddGroupsToListWidget();

            if (m_pqlwGroups->count() <= 1)
            {
                if (m_pqlwGroups->count() == 1)
                {
                    QListWidgetItem* pItem = m_pqlwGroups->item(0);
                    pItem->setSelected(true);
                }

                m_pqgbGroups->hide();
            }
        }
        else
        {
            m_pqgbGroups->hide();
        }
    }

    GroupChangedSlot();
}

void CwmsObjectEditor::AddGroupsToListWidget()
{
    CdmObject* pCdmObject = GetObject();
    if (false == CHKPTR(pCdmObject)) return;

    CdmClass* pCdmClass = pCdmObject->GetClass();
    if (false == CHKPTR(pCdmClass)) return;

    QMap<int, CdmClassGroup*> qmGroups;
    pCdmClass->GetGroups(qmGroups);

    QMap<int, CdmClassGroup*>::iterator qmIt    = qmGroups.begin();
    QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

    bool bFirst = true;
    m_pqlwGroups->clear();
    QMap<QString, QListWidgetItem*> qmGroupMapping;

    for ( ; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pCdmGroup = qmIt.value();

        if (CHKPTR(pCdmGroup))
        {
            CdmRights& cCdmRight = pCdmGroup->GetRights();

            if (cCdmRight.HasCurrentUserReadAccess() || cCdmRight.HasCurrentUserWriteAccess())
            {
                QListWidgetItem* pItem = nullptr;

                if (!qmGroupMapping.contains(pCdmGroup->GetCaption()))
                {
                    pItem = new QListWidgetItem(m_pqlwGroups);
                    qmGroupMapping.insert(pCdmGroup->GetCaption(), pItem);
                }
                else
                {
                    pItem = qmGroupMapping[pCdmGroup->GetCaption()];
                }

                if (CHKPTR(pItem))
                {
                    pItem->setText(pCdmGroup->GetCaption());
                    QVariantList qvlIds = pItem->data(Qt::UserRole).toList();
                    qvlIds.append(pCdmGroup->GetId());
                    pItem->setData(Qt::UserRole, qvlIds);

                    if (bFirst)
                    {
                        pItem->setSelected(true);
                        bFirst = false;
                    }
                }
            }
        }
    }

    if (HasMembersWithoutGroup())
    {
        QListWidgetItem* pItem = new QListWidgetItem(m_pqlwGroups);
        pItem->setText(tr("Weitere Daten"));
        pItem->setData(Qt::UserRole, -1);
    }
}

void CwmsObjectEditor::BuildContainerWidget()
{
    DELPTR(m_pqwContainter)
            m_pqwContainter = new QWidget(m_pqfData);
    m_pqfData->setWidget(m_pqwContainter);
}

void CwmsObjectEditor::GetClassMembers(QMap<qint64, CdmMember*>& p_rqmMembers)
{
    CdmObject* pCdmObject = GetObject();
    CdmClass* pCdmClass = pCdmObject->GetClass();

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->GetMemberMap(p_rqmMembers);
    }
}

void CwmsObjectEditor::GetClassMembers(QMap<qint64, CdmMember *> &p_rqmMembers, CdmClass *pClass)
{
    if (CHKPTR(pClass))
    {
        pClass->GetMemberMap(p_rqmMembers);
    }
}

CdmMember* CwmsObjectEditor::GetMemberById(qint64 p_lId)
{
    CdmMember* pCdmMember = nullptr;
    QMap<qint64,CdmMember*> qmMemberMap;
    GetClassMembers(qmMemberMap);

    if (qmMemberMap.contains(p_lId))
    {
        pCdmMember = qmMemberMap[p_lId];
    }

    return pCdmMember;
}

CdmMember *CwmsObjectEditor::GetMemberById(qint64 p_lId, CdmClass *pClass)
{
    CdmMember *pCdmMember = nullptr;
    QMap<qint64, CdmMember*> qmMemberMap;
    GetClassMembers(qmMemberMap, pClass);

    if (qmMemberMap.contains(p_lId))
    {
        pCdmMember = qmMemberMap[p_lId];
    }

    return pCdmMember;
}

void CwmsObjectEditor::GetParentWidgetAndLayout(CdmClassGroup* p_pGroup,
                                                QWidget*& p_rpWidget,
                                                QFormLayout*& p_rpLayout,
                                                QTabWidget*& p_rpTab)
{
    BuildContainerWidget();
    int iTabs = 0;

    if (p_pGroup)
    {
        iTabs = CountAdditionalTabs(p_pGroup);
    }
    else
    {
        iTabs = CountAditionalTabsforNoneGroupMembers();
    }

    if (iTabs == 0)
    {
        p_rpWidget = m_pqwContainter;
        p_rpLayout = new QFormLayout(p_rpWidget);
        p_rpLayout->setSpacing(3);
        p_rpLayout->setContentsMargins(3,3,3,3);
    }
    else
    {
        p_rpTab = new QTabWidget(m_pqwContainter);
        QVBoxLayout* pqLayout = new QVBoxLayout(m_pqwContainter);
        pqLayout->setContentsMargins(3,3,3,3);
        pqLayout->addWidget(p_rpTab);
        p_rpWidget = new QWidget(nullptr);
        p_rpTab->addTab(p_rpWidget, tr("Stammdaten"));
        p_rpLayout = new QFormLayout(p_rpWidget);
        p_rpLayout->setSpacing(3);
    }
}

void CwmsObjectEditor::FillMembers(QList<CdmClassGroup*>& p_qlGroups)
{
    if (p_qlGroups.count() > 0)
    {
        QWidget* pParentWidget = nullptr;
        QTabWidget* pqTab = nullptr;
        QFormLayout* pLayout = nullptr;

        for (int iPos = 0; iPos < p_qlGroups.count(); ++iPos)
        {
            CdmClassGroup* pGroup = p_qlGroups[iPos];

            if (iPos == 0)
            {
                GetParentWidgetAndLayout(pGroup, pParentWidget, pLayout, pqTab);
            }

            QList<CdmMember*> qlMembers;
            pGroup->GetMembers(qlMembers);

            for (int iCounter = 0; iCounter < qlMembers.count(); ++iCounter)
            {
                CdmMember* pCdmMember = qlMembers[iCounter];

                if (pCdmMember &&
                        pCdmMember->GetAccessMode() != eDmMemberAccessPrivate)
                {
                    AddMember(pCdmMember, pParentWidget, pLayout, pqTab);
                }
            }

            if (pLayout->count() == 0 && pqTab)
            {
                pqTab->removeTab(0);
            }
        }
    }
}

void CwmsObjectEditor::AddMember(CdmMember* p_pCdmMember,
                                 QWidget* p_pqMain,
                                 QFormLayout* p_pLayout,
                                 QTabWidget* p_pqTab)
{
    if (!m_qlAddedMembers.contains(p_pCdmMember->GetKeyname()))
    {
        CdmRights& cCdmRights = p_pCdmMember->GetRights();

        if (cCdmRights.HasCurrentUserReadAccess() || cCdmRights.HasCurrentUserWriteAccess())
        {
            if (NeedsMemberTab(p_pCdmMember))
            {
                AddMemberInTab(p_pCdmMember->GetKeyname(), p_pqTab);
            }
            else
            {
                AddMemberInFormLayout(p_pCdmMember->GetKeyname(), p_pqMain, p_pLayout);
            }
        }
    }
}

void CwmsObjectEditor::FillMembers()
{
    QWidget* pParentWidget = nullptr;
    QTabWidget* pqTab = nullptr;
    QFormLayout* pLayout = nullptr;
    GetParentWidgetAndLayout(nullptr, pParentWidget, pLayout, pqTab);

    QList<qint64> qvlMembers         = GetSortMemberList();
    QList<qint64>::iterator qvlIt    = qvlMembers.begin();
    QList<qint64>::iterator qvlItEnd = qvlMembers.end();

    for (; qvlIt != qvlItEnd; ++qvlIt)
    {
        int iMemberId = *qvlIt;
        CdmMember* pCdmMember = GetMemberById(iMemberId);

        if (pCdmMember &&
                pCdmMember->GetAccessMode() != eDmMemberAccessPrivate &&
                !pCdmMember->GetGroup())
        {
            AddMember(pCdmMember, pParentWidget, pLayout, pqTab);
        }
    }

    if (pLayout->count() == 0 && pqTab)
    {
        pqTab->removeTab(0);
    }
}

int CwmsObjectEditor::CountAdditionalTabs(CdmClassGroup* p_pCdmGroup)
{
    int iRet = 0;

    if (p_pCdmGroup)
    {
        QList<CdmMember*> qlMembers;
        p_pCdmGroup->GetMembers(qlMembers);

        for (int iCounter = 0; iCounter < qlMembers.count(); ++iCounter)
        {
            if (NeedsMemberTab(qlMembers[iCounter]))
            {
                ++iRet;
            }
        }
    }
    else
    {
        iRet = CountAditionalTabsforNoneGroupMembers();
    }

    return iRet;
}

int CwmsObjectEditor::CountAditionalTabsforNoneGroupMembers()
{
    int iRet = 0;
    QMap<qint64,CdmMember*> qmMemberMap;
    GetClassMembers(qmMemberMap);

    QMap<qint64,CdmMember*>::iterator qmIt = qmMemberMap.begin();
    QMap<qint64,CdmMember*>::iterator qmItEnd = qmMemberMap.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmMember* pCdmMember = qmIt.value();

        if (CHKPTR(pCdmMember))
        {
            if (NeedsMemberTab(pCdmMember))
            {
                ++iRet;
            }
        }
    }

    return iRet;
}

bool CwmsObjectEditor::NeedsMemberTab(CdmMember* p_pCdmMember)
{
    bool bRet = false;

    if (CHKPTR(p_pCdmMember))
    {
        EdmValueType eValue = p_pCdmMember->GetValueType();

        switch(eValue)
        {
        case eDmValueDictIntDouble:
        case eDmValueDictIntInt:
        case eDmValueDictIntString:
        case eDmValueDictStringDouble:
        case eDmValueDictStringInt:
        case eDmValueDictStringString:
        case eDmValueListDouble:
        case eDmValueListInt:
        case eDmValueListObjects:
        case eDmValueListString:
        case eDmValueCharacterDocument:
            bRet = true;
            break;
        case eDmValueContainerRef:

            if (p_pCdmMember->IsOwner())
            {
                bRet = true;
            }

            break;
        case eDmValueObjectRef:

            if (p_pCdmMember->IsOwner() && m_bOwnerMode)
            {
                bRet = true;
            }

            break;
        default:
            bRet = false;
        }
    }

    return bRet;
}

void CwmsObjectEditor::GroupChangedSlot()
{
    m_qlAddedMembers.clear();
    QListWidgetItem* pItem = CwmsListWidgetHelper::GetSelectedItem(m_pqlwGroups);

    if (pItem)
    {
        QList<CdmClassGroup*> qlGroups;
        GetGroupList(pItem,qlGroups);

        if (qlGroups.count() > 0)
        {
            FillMembers(qlGroups);
        }
        else
        {
            FillMembers();
        }

    }
    else
    {
        FillMembers();
    }
}

void CwmsObjectEditor::GetGroupList(QListWidgetItem* pItem, QList<CdmClassGroup*>& p_rqlGroups)
{
    if (CHKPTR(pItem))
    {
        CdmObject* pCdmObject = GetObject();
        CdmClass* pCdmClass = pCdmObject->GetClass();

        if (CHKPTR(pCdmClass))
        {
            QVariantList qvlGroups = pItem->data(Qt::UserRole).toList();

            if (qvlGroups.count() > 0)
            {
                QList<CdmClassGroup*> qlGroups;

                for (int iPos = 0; iPos < qvlGroups.count(); ++iPos)
                {
                    int iGroupId = qvlGroups[iPos].toInt();

                    if (iGroupId >= 0)
                    {
                        CdmClassGroup* pGroup = pCdmClass->FindGroupById(iGroupId);

                        if (pGroup)
                        {
                            p_rqlGroups.append(pGroup);
                        }
                    }
                }
            }
        }
    }
}

void CwmsObjectEditor::AddMemberInFormLayout(QString p_qstrKeyname,
                                             QWidget* p_qwParent,
                                             QFormLayout* p_qLayout)
{
    CdmValue* pCdmValue = m_cCdmObjectAdaptor.GetValue(p_qstrKeyname);

    if (CHKPTR(pCdmValue))
    {
        CreateMemberUi(pCdmValue, p_qwParent, p_qLayout);
    }

    m_qlAddedMembers.append(p_qstrKeyname);
}

void CwmsObjectEditor::AddMemberInTab(QString p_qstrKeyname, QTabWidget* p_qwParent)
{
    CdmValue* pCdmValue = m_cCdmObjectAdaptor.GetValue(p_qstrKeyname);

    if (CHKPTR(pCdmValue))
    {
        QWidget* pqwWidget = new QWidget(nullptr);
        p_qwParent->addTab(pqwWidget, pCdmValue->GetCaption());
        QVBoxLayout* pqLayout = new QVBoxLayout(pqwWidget);

        if (!CreateTabMemberUi(pCdmValue, pqwWidget, pqLayout))
        {
            DELPTR(pqwWidget)
        }
    }

    m_qlAddedMembers.append(p_qstrKeyname);
}

bool CwmsObjectEditor::HasMembersWithoutGroup()
{
    bool bRet = false;

    CdmObject* pCdmObject = GetObject();
    CdmClass* pCdmClass = pCdmObject->GetClass();

    if (CHKPTR(pCdmClass))
    {
        QMap<qint64,CdmMember*> qmMemberMap;
        pCdmClass->GetMemberMap(qmMemberMap);

        QMap<qint64,CdmMember*>::iterator qmIt = qmMemberMap.begin();
        QMap<qint64,CdmMember*>::iterator qmItEnd = qmMemberMap.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmMember* pMember = qmIt.value();

            if (CHKPTR(pMember))
            {
                if (!pMember->GetGroup())
                {
                    bRet = true;
                    break;
                }
            }
        }
    }

    return bRet;
}

bool CwmsObjectEditor::CreateTabMemberUi(CdmValue* p_pCdmValue,
                                         QWidget* p_pqfParent,
                                         QVBoxLayout* p_qLayout)
{
    bool bRet = false;

    if (CHKPTR(p_pCdmValue))
    {
        const CdmMember* pCdmMember = p_pCdmValue->GetMember();


        if (!FindInHiddenList(p_pCdmValue))
        {
            CoeValueWidget* pCoeValueWidget = CoeValueWidget::CreateValueWidget(p_pCdmValue, p_pqfParent);
            m_pCoeValueWidget = pCoeValueWidget;

            if(m_pCoeValueWidget)
            {
                m_pCoeValueWidget->CreateTabWidget(p_pqfParent, p_qLayout);
                CheckReadOnly(pCdmMember, m_pCoeValueWidget);
                m_pCoeValueWidget->SetValue(p_pCdmValue);
                bRet = true;
            }
        }
    }

    return bRet;
}

void CwmsObjectEditor::CheckReadOnly(const CdmMember* p_pCdmMeber, CoeValueWidget* p_pWidget)
{
    if (CHKPTR(p_pWidget) && CHKPTR(p_pCdmMeber))
    {
        if (IsReadOnly(p_pCdmMeber))
        {
            INFO("Member in ReadOnlyList will be set ReadOnly: " + p_pCdmMeber->GetKeyname())
                    p_pWidget->SetReadOnly();
        }
    }
}

void CwmsObjectEditor::CheckEditable(const CdmMember* p_pCdmMeber, CoeValueWidget* p_pWidget)
{
    if(CHKPTR(p_pWidget) && CHKPTR(p_pCdmMeber))
    {
        if(IsReadOnly(p_pCdmMeber))
        {
            INFO("Member in ReadOnlyList will be set Editable: " + p_pCdmMeber->GetKeyname())
                    p_pWidget->SetEditable();
        }
    }
}

void CwmsObjectEditor::CreateMemberUi(CdmValue* p_pCdmValue,
                                      QWidget* p_pqfParent,
                                      QFormLayout* p_qLayout)
{

    if (CHKPTR(p_pCdmValue))
    {
        const CdmMember* pCdmMember = p_pCdmValue->GetMember();

        if (!FindInHiddenList(p_pCdmValue))
        {
            CoeValueWidget* pCoeValueWidget = CoeValueWidget::CreateValueWidget(p_pCdmValue, p_pqfParent);
            m_pCoeValueWidget = pCoeValueWidget;

            if(CHKPTR(m_pCoeValueWidget))
            {
                // set the displaytype if needed
                if(m_qmDisplayType.contains(p_pCdmValue->GetKeyname()))
                {
                    m_pCoeValueWidget->SetDisplayType(m_qmDisplayType[p_pCdmValue->GetKeyname()]);
                }

                // set the objectlist in case of object ref and combobox displayvalue
                if(p_pCdmValue->GetValueType() == eDmValueObjectRef)
                {
                    if(m_qmObjectRefs.contains(p_pCdmValue->GetKeyname()))
                    {
                        TStringPair tStringPair = m_qmObjectRefs[p_pCdmValue->GetKeyname()];
                        QString qstrKey = tStringPair.first;
                        qstrKey = qstrKey.simplified();

                        if (!qstrKey.startsWith("select "))
                        {
                            ((CoedtwObjectRef*)m_pCoeValueWidget)->SetContainer(tStringPair.first, tStringPair.second);
                        }
                        else
                        {
                            ((CoedtwObjectRef*)m_pCoeValueWidget)->SetProxy(tStringPair.first);
                        }

                        if (m_qmProxies.contains(p_pCdmValue->GetKeyname()))
                        {
                            ((CoedtwObjectRef*)m_pCoeValueWidget)->SetProxy(m_qmProxies[p_pCdmValue->GetKeyname()]);
                        }
                    }

                    if (!m_bShowEditButton)
                    {
                        ((CoedtwObjectRef*)m_pCoeValueWidget)->HideEditButton();
                    }
                }

                // creating the widget
                m_pCoeValueWidget->CreateWidget(p_qLayout, p_pqfParent);
                CheckReadOnly(pCdmMember, m_pCoeValueWidget);
            }
        }
        else
        {
            INFO("Member in HiddenList will not be shown: " + p_pCdmValue->GetKeyname())
        }
    }
}

void CwmsObjectEditor::CaptionChangedSlot(const QString & p_qstrCaption)
{
    GetObject()->SetCaption(p_qstrCaption);
}

QList<qint64> CwmsObjectEditor::GetSortMemberList()
{
    QList<qint64> qvlMembers;

    if(m_qstrlSortedMembers.isEmpty())
    {
        CdmClass* pCdmClass = GetObject()->GetClass();

        if (CHKPTR(pCdmClass))
        {
            QVector<QString> qvSequence = pCdmClass->GetMemberSequence();

            if (qvSequence.isEmpty())
            {
                QMap<qint64,CdmMember*> qmMembers;
                pCdmClass->GetMemberMap(qmMembers);

                QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
                QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    CdmMember* pCdmMember = qmIt.value();

                    if (pCdmMember)
                    {
                        qint64 lMemberId = pCdmMember->GetId();
                        qvlMembers.append(lMemberId);
                    }
                }
            }
            else
            {
                for (int iCounter = 0; iCounter < qvSequence.count(); ++iCounter)
                {
                    const CdmMember* pCdmMember = pCdmClass->FindMember(qvSequence[iCounter]);

                    if (pCdmMember)
                    {
                        qvlMembers.append(pCdmMember->GetId());
                    }
                }
            }
        }
    }
    else
    {
        qvlMembers = GetSortedMemberListFromStringList();
    }

    return qvlMembers;
}

QList<qint64> CwmsObjectEditor::GetSortedMemberListFromStringList(  )
{
    QList<qint64> qvlMembers;

    QStringList::Iterator  qstrIt    = m_qstrlSortedMembers.begin();
    QStringList::Iterator  qstrItEnd = m_qstrlSortedMembers.end();

    for(; qstrIt != qstrItEnd; ++qstrIt)
    {
        CdmValue* pCdmValue = GetObject()->GetValue(*qstrIt);

        if(CHKPTR(pCdmValue))
        {
            qint64 lMemberId = pCdmValue->GetMemberId();
            qvlMembers.append(lMemberId);
        }
    }

    return qvlMembers;
}

CdmValue* CwmsObjectEditor::FindValueByMemberId(qint64 p_lMemberId)
{
    CdmValue* pCdmValueRet = nullptr;
    QMap<QString, CdmValue*> qmValues;

    GetObject()->GetValueMap(qmValues);

    QMap<QString, CdmValue*>::iterator qmIt    = qmValues.begin();
    QMap<QString, CdmValue*>::iterator qmItEnd = qmValues.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmValue* pCdmValue = qmIt.value();
        if (pCdmValue)
        {
            if(pCdmValue->GetMemberId() == p_lMemberId)
            {
                pCdmValueRet = pCdmValue;
                break;
            }
        }
    }

    return pCdmValueRet;
}

bool CwmsObjectEditor::FindInHiddenList(CdmValue* p_pCdmValue)
{
    bool bRet = false;

    if (CHKPTR(p_pCdmValue))
    {
        QString qstrKeyname = p_pCdmValue->GetKeyname();

        QStringList::Iterator qstrlIt = m_qstrlHiddenValues.begin();
        QStringList::Iterator qstrlItEnd = m_qstrlHiddenValues.end();

        for (; qstrlIt != qstrlItEnd; ++qstrlIt)
        {
            if (qstrKeyname == (*qstrlIt))
            {
                bRet = true;
                break;
            }
        }
    }

    if (!bRet)
    {
        const CdmMember* pCdmMember = p_pCdmValue->GetMember();

        if (pCdmMember)
        {
            if (pCdmMember->GetAccessMode() == eDmMemberAccessPrivate)
            {
                bRet = true;
            }

            if (!bRet)
            {
                if (m_bHideSystemMembers && pCdmMember->IsSystemMember())
                {
                    bRet = true;
                }
            }
        }
    }



    return bRet;
}

bool CwmsObjectEditor::IsReadOnly(const CdmMember* p_pCdmMember)
{
    bool bRet = false;

    if(m_bReadOnly)
    {
        bRet = true;
    }
    else
    {
        if (CHKPTR(p_pCdmMember))
        {
            QString qstrKeyname = p_pCdmMember->GetKeyname();

            if (m_qstrlReadOnlyValues.contains(qstrKeyname))
            {
                bRet = true;
            }
        }
    }

    if (!bRet)
    {
        if (CHKPTR(p_pCdmMember) && p_pCdmMember->GetAccessMode() == eDmMemberAccessProtected)
        {
            bRet = true;
        }

        CdmRights& cCdmRights = (const_cast<CdmMember*>(p_pCdmMember))->GetRights();

        if (!cCdmRights.HasCurrentUserWriteAccess())
        {
            bRet = true;
        }
    }

    return bRet;
}

void CwmsObjectEditor::SetSortedList(  QStringList p_qstrlistSortedMembers )
{
    m_qstrlSortedMembers = p_qstrlistSortedMembers;
}

void CwmsObjectEditor::SetCaptionValue(QString p_qstrValue)
{
    m_qstrCaptionValue = p_qstrValue;
}

void CwmsObjectEditor::setObjectName(QString p_qstrName)
{
    setWindowTitle(p_qstrName);
}

void CwmsObjectEditor::ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule& p_cModule)
{
    if (p_pRuntime)
    {
        m_pToolBar = p_pRuntime->addToolBar(tr(p_cModule.GetName().toUtf8()));
        p_pRuntime->AddToolBar(m_pToolBar);
        QMenuBar* pMenuBar = p_pRuntime->QMainWindow::menuBar();

        if (CHKPTR(pMenuBar))
        {
            m_pMenu = pMenuBar->addMenu(tr(p_cModule.GetName().toUtf8()));
            p_pRuntime->SetCurrentModuleMenu(m_pMenu);
        }

        QAction* pAction = new QAction(tr("Save"), this);
        QIcon iconNew;
        iconNew.addFile(QStringLiteral(":/icons/ok24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pAction->setIcon(iconNew);
        m_pMenu->addAction(pAction);
        m_pToolBar->addAction(pAction);
        connect(pAction, SIGNAL(triggered()), this, SLOT(SaveClickedSlot()));


        if (m_pqpbPrint->isVisible())
        {
            QAction* pAction = new QAction(tr("Drucken"), this);
            QIcon iconPrint;
            iconPrint.addFile(QStringLiteral(":/icons/print24.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconPrint);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(PrintClickedSlot()));
            m_pqpbPrint->hide();
        }

        if (m_pqpbJournal->isVisible())
        {
            QAction* pAction = new QAction(tr("Journal"), this);
            QIcon iconJournal;
            iconJournal.addFile(QStringLiteral(":/icons/printpreview24.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconJournal);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(JournalClickedSlot()));
            m_pqpbJournal->hide();
        }
    }
}

void CwmsObjectEditor::SetModule(CwmsApplicationModule p_cModule)
{
    if (p_cModule.IsValid())
    {
        CdmObject* pCdmObject = p_cModule.GetUserInterface();

        if (CHKPTR(pCdmObject))
        {
            if (p_cModule.GetObjectModule())
            {
                SetObject(p_cModule.GetObjectModule());
            }
            else
            {
                CwmsFormObject obj(pCdmObject);
                QString qstrWql = obj.GetWql();

                if (!qstrWql.isEmpty())
                {
                    CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

                    if (CHKPTR(pQuery) && pQuery->IsValid())
                    {
                        if (pQuery->GetResultCount() == 0)
                        {
                            ERR("Wql has no result delivered.")
                        }
                        else
                        {
                            if (pQuery->GetResultCount() > 1)
                            {
                                WARNING("More than one result of query found taking first object.")
                            }

                            SetObject(pQuery->GetFirstResultObject());
                        }
                    }
                    else
                    {
                        ERR("WQL in UI Definition is invalid")
                    }
                }
            }

            SetFormConfiguration(pCdmObject);
            setObjectName(p_cModule.GetName());
        }
    }
}

void CwmsObjectEditor::SetFormConfiguration(CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        CwmsFormObject cForm(p_pObject);

        CdmClass *pCdmObjectClass = p_pObject->GetClass();
        if(CHKPTR(pCdmObjectClass))
        {
            SetReadOnly(cForm.GetReadOnly());

            SetCaptionValue(cForm.GetCaptionValue());
            //QMap<QString, QString> qmDefaults = cForm.GetDefaultValues();
            QMap<QString, int> qmDisplayTypes = cForm.GetDisplayTypes();
            QMap<QString, QString> qmObjectRefAssignments = cForm.GetObjectRefAssignment();
            QList<QString> qllVisibleMembers = cForm.GetVisibleMembers();
            QList<QString>::iterator qllIt = qllVisibleMembers.begin();
            QList<QString>::iterator qllItEnd = qllVisibleMembers.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                m_qstrlSortedMembers.append(*qllIt);
            }

            QList<QString> qllFucntions = cForm.GetFunctions();

            qllIt = qllFucntions.begin();
            qllItEnd = qllFucntions.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                m_qstrlFunctions.append(*qllIt);
            }

            QMap<QString, int>::iterator qmIt = qmDisplayTypes.begin();
            QMap<QString, int>::iterator qmItEnd = qmDisplayTypes.end();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                m_qmDisplayType.insert(qmIt.key(), (EdmStringDisplayType)qmIt.value());
            }

            QMap<QString, QString>::iterator qmItRef = qmObjectRefAssignments.begin();
            QMap<QString, QString>::iterator qmItRefEnd = qmObjectRefAssignments.end();

            for (; qmItRef != qmItRefEnd; ++qmItRef)
            {
                AddObjectRefData(qmItRef.key(), qmItRef.value(), "");
            }

            if (cForm.GetJournalEnabled())
            {
                m_pqpbJournal->show();
            }
            else
            {
                m_pqpbJournal->hide();
            }

            if (cForm.GetPrintEnabled())
            {
                m_pqpbPrint->show();
            }
            else
            {
                m_pqpbPrint->hide();
            }

            m_rpCdmPrintingTemplate = cForm.GetPrintingTemplate();
        }
    }
}

void CwmsObjectEditor::Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime)
{
    SetModule(p_cModule);
    ConnectRuntime(p_pRuntime, p_cModule);
    FillObjectEditor();
}

void CwmsObjectEditor::SaveClickedSlot()
{
    GetObject()->Commit();
}

void CwmsObjectEditor::MetaDataClickedSlot()
{
    QString qstrInfo = GetObject()->GetInfo();
    CwmsHelp::ShowTextHelp(qstrInfo, nullptr);
}

void CwmsObjectEditor::JournalClickedSlot()
{
    CwmsJournalViewer* pViewer = new CwmsJournalViewer(this);
    pViewer->FillDialog(GetObject());
    pViewer->exec();
    DELPTR(pViewer)
}

void CwmsObjectEditor::PrintClickedSlot()
{
    CwmsReportManager::PrintDefaultForObject(GetObject());
}

void CwmsObjectEditor::AddFunctions()
{
    for (int iCounter = 0; iCounter < m_qstrlFunctions.count(); ++iCounter)
    {
        CdmObject* pObject = m_cCdmObjectAdaptor.GetObject();

        if (CHKPTR(pObject))
        {
            CdmClass* pClass = pObject->GetClass();

            if (CHKPTR(pClass))
            {
                QString qstrFunction = m_qstrlFunctions[iCounter];
                CdmClassMethod* pMethod = pClass->GetMethod(qstrFunction);

                if (CHKPTR(pMethod) && pMethod->GetAccess() == eDmMemberAccessPublic)
                {
                    QPushButton* pButton = new QPushButton(this);

                    QPixmap qPixmap = pMethod->GetIcon();

                    if (!qPixmap.isNull())
                    {
                        pButton->setIcon(QIcon(qPixmap));
                        pButton->setIconSize(QSize(24,24));
                        pButton->setToolTip(pMethod->GetCaption());


                    }
                    else
                    {
                        pButton->setText(pMethod->GetCaption());
                        pButton->setToolTip(pMethod->GetCaption());
                    }

                    if (m_pMenu && m_pToolBar)
                    {
                        QAction* pAction = new QAction(pMethod->GetCaption(), this);
                        pAction->setIcon(QIcon(qPixmap));
                        m_pMenu->addAction(pAction);
                        m_pToolBar->addAction(pAction);
                        connect(pAction, SIGNAL(triggered()), this, SLOT(FunctionClickedSlot()));
                    }


                    int iWidgetCount = m_pqhbFunctions->count() - 2;
                    m_pqhbFunctions->insertWidget(iWidgetCount, pButton);
                    m_qmFunctionMapping.insert(pButton, qstrFunction);
                    connect(pButton, SIGNAL(clicked()), this, SLOT(FunctionClickedSlot()));
                }
            }
        }
    }
}

void CwmsObjectEditor::FunctionClickedSlot()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    CdmMessageManager::StartAsyncMessageCollection();
    QPushButton* pButton = (QPushButton*)sender();

    if (CHKPTR(pButton))
    {
        if (m_qmFunctionMapping.contains(pButton))
        {
            QString qstrFunction = m_qmFunctionMapping[pButton];
            m_cCdmObjectAdaptor.Execute(qstrFunction);
        }
    }

    GroupChangedSlot(); // updates the data in current displayed group
    QApplication::restoreOverrideCursor();
    CdmMessageManager::EndAndShowAsyncMessageCollection();
}


void CwmsObjectEditor::ResetClickedSlot()
{
    CdmObject* pObject = GetObject();

    if (CHKPTR(pObject))
    {
        pObject->Refresh();
        GroupChangedSlot(); // updates the data in current displayed group
    }
}
