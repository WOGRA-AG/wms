/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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
#include "CdmQueryEnhanced.h"
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

/** +-=---------------------------------------------------------Mi 22. Aug 10:05:51 2012----------*
 * @method  CwmsObjectEditor::CwmsObjectEditor                 // public                            *
 * @return                                                   //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Object Editor constructor.                                                        *
 *----------------last changed: --------------------------------Mi 22. Aug 10:05:51 2012----------*/
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

/** +-=---------------------------------------------------------Mi 22. Aug 10:06:04 2012----------*
 * @method  CwmsObjectEditor::CwmsObjectEditor                 // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Object Editor constructor.                                                        *
 *----------------last changed: --------------------------------Mi 22. Aug 10:06:04 2012----------*/
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

/** +-=---------------------------------------------------------Fri Dec 5 14:36:55 2003-----------*
* @method  CwmsObjectEditor::~CwmsObjectEditor                // public, virtual                   *
* @return  void                                             //                                   *
* @comment The Destructor of Class CwmsObjectEditor                                               *
*---------------------------------------------------------------Fri Dec 5 14:36:55 2003----------*/
CwmsObjectEditor::~CwmsObjectEditor(  )
{
}

/** +-=---------------------------------------------------------Di 12. Aug 20:11:42 2008----------*
 * @method  CwmsObjectEditor::SetObject                       // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment This method sets the object for this editor                                           *
 *----------------last changed: --------------------------------Di 12. Aug 20:11:42 2008----------*/
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

/** +-=---------------------------------------------------------Di 12. Aug 20:12:29 2008----------*
 * @method  CwmsObjectEditor::GetObject                       // public                            *
 * @return  CdmObject*                                       //                                   *
 * @comment returns the object.                                                                   *
 *----------------last changed: --------------------------------Di 12. Aug 20:12:29 2008----------*/
CdmObject* CwmsObjectEditor::GetObject()
{
    return m_cCdmObjectAdaptor.GetObject();
}

/** +-=---------------------------------------------------------Fr 6. Jan 14:07:53 2006-----------*
 * @method  CwmsObjectEditor::SetReadOnly                     // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bReadOnly                                 //                                   *
 * @comment This emthod sets the objecteditor in readonly mode or in edit mode.                   *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 6. Jan 14:07:53 2006-----------*/
void CwmsObjectEditor::SetReadOnly(bool p_bReadOnly)
{
    m_bReadOnly = p_bReadOnly;
}

/** +-=---------------------------------------------------------So 10. Aug 21:44:51 2008----------*
 * @method  CwmsObjectEditor::SetSystemMembersHidden          // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bHidden                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Aug 21:44:51 2008----------*/
void CwmsObjectEditor::SetSystemMembersHidden(bool p_bHidden)
{
    m_bHideSystemMembers = p_bHidden;
}

/** +-=---------------------------------------------------------So 10. Aug 21:45:20 2008----------*
 * @method  CwmsObjectEditor::IsSystemMembersHidden           // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Aug 21:45:20 2008----------*/
bool CwmsObjectEditor::IsSystemMembersHidden()
{
    return m_bHideSystemMembers;
}

/** +-=---------------------------------------------------------Fr 6. Jan 14:08:20 2006-----------*
 * @method  CwmsObjectEditor::IsReadOnly                      // private                           *
 * @return  bool                                             //                                   *
 * @comment returns if the object editor is readonly or not.                                      *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 6. Jan 14:08:20 2006-----------*/
bool CwmsObjectEditor::IsReadOnly(  )
{
    return m_bReadOnly;
}

/** +-=---------------------------------------------------------Di 10. Jun 12:31:10 2008----------*
 * @method  CwmsObjectEditor::SetShowEditButton               // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bShow                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 10. Jun 12:31:10 2008----------*/
void CwmsObjectEditor::SetShowEditButton(bool p_bShow)
{
    m_bShowEditButton = p_bShow;
}

/** +-=---------------------------------------------------------Di 10. Jun 16:46:58 2008----------*
 * @method  CwmsObjectEditor::ShowEditButton                  // public                            *
 * @return  bool                                             //                                   *
 * @comment returns if the editbutton should be shown on objectreference.                         *
 *----------------last changed: --------------------------------Di 10. Jun 16:46:58 2008----------*/
bool CwmsObjectEditor::ShowEditButton()
{
    return m_bShowEditButton;
}

/** +-=---------------------------------------------------------Fri Dec 5 14:40:42 2003-----------*
 * @method  CwmsObjectEditor::AddHiddenValue               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method adds an Value which should be hidden in this editor.                   *
 *---------------------------------------------------------------Fri Dec 5 14:40:42 2003----------*/
void CwmsObjectEditor::AddHiddenValue(  QString p_qstrKeyname )
{
    m_qstrlHiddenValues.append(p_qstrKeyname);
}

/** +-=---------------------------------------------------------Fri Dec 5 14:41:38 2003-----------*
 * @method  CwmsObjectEditor::AddReadOnlyValue             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method adds an read only Value to the editor. Which means the dataype will    *
 *          be shown, but it will not be editable.                                                *
 *---------------------------------------------------------------Fri Dec 5 14:41:38 2003----------*/
void CwmsObjectEditor::AddReadOnlyValue(  QString p_qstrKeyname )
{
    m_qstrlReadOnlyValues.append(p_qstrKeyname);
}

/** +-=---------------------------------------------------------Mo 5. Nov 15:07:10 2012-----------*
 * @method  CwmsObjectEditor::DeactivateOwnerMode            // public                            *
 * @return  void                                             //                                   *
 * @comment The owner mode is used to display in an objecteditor an objecteditor of an owned      *
 *          object. if you deactivate this mode, objectreferences which are owned will only       *
 *          be displayed as an edit button and not as a child tab.                                *
 *----------------last changed: --------------------------------Mo 5. Nov 15:07:10 2012-----------*/
void CwmsObjectEditor::DeactivateOwnerMode()
{
    m_bOwnerMode = false;
}

/** +-=---------------------------------------------------------Fr 20. Jan 23:32:41 2006----------*
 * @method  CwmsObjectEditor::AddObjectRefData                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrObjectListKeyname                  //                                   *
 * @param   QString p_qstrObjectValue                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 20. Jan 23:32:41 2006----------*/
void CwmsObjectEditor::AddObjectRefData(QString p_qstrValue,
                                        QString p_qstrObjectListKeyname,
                                        QString p_qstrObjectValue )
{
    TStringPair tStringPair(p_qstrObjectListKeyname, p_qstrObjectValue);
    m_qmObjectRefs.insert(p_qstrValue, tStringPair);
}

/** +-=---------------------------------------------------------Mo 3. Sep 15:43:51 2012-----------*
 * @method  CwmsObjectEditor::SetDisplayType                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   EdmStringDisplayType p_EoeDisplayType            //                                   *
 * @comment This method sets the displaytype for a value.                                         *
 *----------------last changed: --------------------------------Mo 3. Sep 15:43:51 2012-----------*/
void CwmsObjectEditor::SetDisplayType(QString p_qstrValue, EdmStringDisplayType p_EoeDisplayType)
{
    m_qmDisplayType.insert(p_qstrValue, p_EoeDisplayType);
}

/** +-=---------------------------------------------------------Do 4. Okt 08:37:20 2012-----------*
 * @method  CwmsObjectEditor::AddProxy                        // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCwmsProxy              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 4. Okt 08:37:20 2012-----------*/
void CwmsObjectEditor::AddProxy(QString p_qstrKeyname, CdmEnhancedQueryProxy* p_pCwmsProxy)
{
    if (CHKPTR(p_pCwmsProxy))
    {
        m_qmProxies[p_qstrKeyname] = p_pCwmsProxy;
    }
}

/** +-=---------------------------------------------------------Fr 6. Jan 14:08:54 2006-----------*
 * @method  CwmsObjectEditor::FillObjectEditor                // public                            *
 * @return  void                                             //                                   *
 * @comment Overwritten virtual method which shows the dialog.                                    *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 6. Jan 14:08:54 2006-----------*/
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

void CwmsObjectEditor::FillObjectEventEditor(CdmClass *pEventClass, QString eventType)
{
    if(eventType == UPDATE)
    {
        m_bIsUpdateEvent = true;
    }
    else
    {
        m_bIsUpdateEvent = false;
    }
    CdmClassManager *pClassManager = GetObject()->GetClassManager();

    if(CHKPTR(pClassManager))
    {
        if(GetObject())
        {
            if(!GetObject()->IsDeleted())
            {
                BuildWidget(pEventClass);
            }
        }
    }
}

/** +-=---------------------------------------------------------Fri Dec 5 15:19:55 2003-----------*
 * @method  CwmsObjectEditor::BuildWidget                     // private                           *
 * @return  void                                             //                                   *
 * @comment This method builds the widget for all Values.                                      *
 *---------------------------------------------------------------Fri Dec 5 15:19:55 2003----------*/
void CwmsObjectEditor::BuildWidget(CdmClass *pClass)
{
    m_qlAddedMembers.clear();

    if (GetObject())
    {
        FillGroups(pClass);
    }
    else
    {
        m_pqwContainter = nullptr;
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

/** +-=---------------------------------------------------------So 4. Nov 11:20:29 2012-----------*
 * @method  CwmsObjectEditor::FillGroups                     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 11:20:29 2012-----------*/
void CwmsObjectEditor::FillGroups(CdmClass *pClass)
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

    GroupChangedSlot(pClass);
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

/** +-=---------------------------------------------------------So 4. Nov 11:44:23 2012-----------*
 * @method  CwmsObjectEditor::AddGroupsToListWidget          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 11:44:23 2012-----------*/
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

    for ( ; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pCdmGroup = qmIt.value();

        if (CHKPTR(pCdmGroup))
        {
            CdmRights& cCdmRight = pCdmGroup->GetRights();

            if (cCdmRight.HasCurrentUserReadAccess() || cCdmRight.HasCurrentUserWriteAccess())
            {
                QListWidgetItem* pItem = new QListWidgetItem(m_pqlwGroups);
                pItem->setText(pCdmGroup->GetCaption());
                pItem->setData(Qt::UserRole, pCdmGroup->GetId());

                if (bFirst)
                {
                    pItem->setSelected(true);
                    bFirst = false;
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

/** +-=---------------------------------------------------------So 4. Nov 11:58:51 2012-----------*
 * @method  CwmsObjectEditor::BuildContainerWidget           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 11:58:51 2012-----------*/
void CwmsObjectEditor::BuildContainerWidget()
{
    DELPTR(m_pqwContainter)
    m_pqwContainter = new QWidget(m_pqfData);
    m_pqfData->setWidget(m_pqwContainter);
}

/** +-=---------------------------------------------------------Mo 5. Nov 09:19:48 2012-----------*
 * @method  CwmsObjectEditor::GetClassMembers                // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<long, CdmMember*>& p_rqmMembers             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 09:19:48 2012-----------*/
void CwmsObjectEditor::GetClassMembers(QMap<long, CdmMember*>& p_rqmMembers)
{
    CdmObject* pCdmObject = GetObject();
    CdmClass* pCdmClass = pCdmObject->GetClass();

    if (CHKPTR(pCdmClass))
    {
        pCdmClass->GetMemberMap(p_rqmMembers);
    }
}

void CwmsObjectEditor::GetClassMembers(QMap<long, CdmMember *> &p_rqmMembers, CdmClass *pClass)
{
    if (CHKPTR(pClass))
    {
        pClass->GetMemberMap(p_rqmMembers);
    }
}

/** +-=---------------------------------------------------------Mo 5. Nov 09:19:39 2012-----------*
 * @method  CwmsObjectEditor::GetMemberById                  // private                           *
 * @return  CdmMember*                                       //                                   *
 * @param   long p_lId                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 09:19:39 2012-----------*/
CdmMember* CwmsObjectEditor::GetMemberById(long p_lId)
{
    CdmMember* pCdmMember = nullptr;
    QMap<long,CdmMember*> qmMemberMap;
    GetClassMembers(qmMemberMap);

    if (qmMemberMap.contains(p_lId))
    {
        pCdmMember = qmMemberMap[p_lId];
    }

    return pCdmMember;
}

CdmMember *CwmsObjectEditor::GetMemberById(long p_lId, CdmClass *pClass)
{
    CdmMember *pCdmMember = nullptr;
    QMap<long, CdmMember*> qmMemberMap;
    GetClassMembers(qmMemberMap, pClass);

    if (qmMemberMap.contains(p_lId))
    {
        pCdmMember = qmMemberMap[p_lId];
    }

    return pCdmMember;
}

/** +-=---------------------------------------------------------Mo 5. Nov 14:31:46 2012-----------*
 * @method  CwmsObjectEditor::GetParentWidgetAndLayout       // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClassGroup* p_pGroup                          //                                   *
 * @param   QWidget*& p_rpWidget                             //                                   *
 * @param   QFormLayout*& p_rpLayout                         //                                   *
 * @param   QTabWidget*& p_rpTab                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 14:31:46 2012-----------*/
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

void CwmsObjectEditor::GetParentWidgetAndEventLayout(CdmClassGroup* p_pGroup,
                                                     QWidget*& p_rpWidget,
                                                     QFormLayout*& p_rpLayout,
                                                     QTabWidget*& p_rpTab,
                                                     CdmClass *pEventClass)
{
    BuildContainerWidget();
    int iTabs = 0;
    if (p_pGroup)
    {
        iTabs = CountAdditionalTabs(p_pGroup);
    }
    else
    {
        iTabs = CountAditionalTabsforNoneGroupMembers(pEventClass);
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

/** +-=---------------------------------------------------------Mo 5. Nov 14:14:27 2012-----------*
 * @method  CwmsObjectEditor::FillMembers                    // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassGroup* p_pGroup                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 14:14:27 2012-----------*/
void CwmsObjectEditor::FillMembers(CdmClassGroup* p_pGroup)
{
    if (p_pGroup)
    {
        QWidget* pParentWidget = nullptr;
        QTabWidget* pqTab = nullptr;
        QFormLayout* pLayout = nullptr;
        GetParentWidgetAndLayout(p_pGroup, pParentWidget, pLayout, pqTab);

        QList<CdmMember*> qlMembers;
        p_pGroup->GetMembers(qlMembers);

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

/** +-=---------------------------------------------------------Mo 5. Nov 14:26:45 2012-----------*
 * @method  CwmsObjectEditor::AddMember                      // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QWidget* p_pqMain                                //                                   *
 * @param   QFormLayout* p_pLayout                           //                                   *
 * @param   QTabWidget* p_pqTab                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 14:26:45 2012-----------*/
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

void CwmsObjectEditor::AddEventClassMember(CdmMember* p_pCdmMember,
                                           QWidget* p_pqMain,
                                           QFormLayout* p_pLayout,
                                           QTabWidget* p_pqTab, CdmObject *pCdmEventObject)
{
    if (!m_qlAddedMembers.contains(p_pCdmMember->GetKeyname()))
    {
        CdmRights& cCdmRights = p_pCdmMember->GetRights();

        if (cCdmRights.HasCurrentUserReadAccess() || cCdmRights.HasCurrentUserWriteAccess())
        {
            if (NeedsMemberTab(p_pCdmMember))
            {
                AddEventClassMemberInTab(p_pCdmMember->GetKeyname(), p_pqTab, pCdmEventObject);
            }
            else
            {
                AddEventClassMemberInFormLayout(p_pCdmMember->GetKeyname(), p_pqMain,
                                                                   p_pLayout, pCdmEventObject);
            }
        }
    }
}

/** +-=---------------------------------------------------------So 4. Nov 12:00:58 2012-----------*
 * @method  CwmsObjectEditor::FillMembers                    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 12:00:58 2012-----------*/
void CwmsObjectEditor::FillMembers()
{
    QWidget* pParentWidget = nullptr;
    QTabWidget* pqTab = nullptr;
    QFormLayout* pLayout = nullptr;
    GetParentWidgetAndLayout(nullptr, pParentWidget, pLayout, pqTab);

    QList<long> qvlMembers         = GetSortMemberList();
    QList<long>::iterator qvlIt    = qvlMembers.begin();
    QList<long>::iterator qvlItEnd = qvlMembers.end();

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

void CwmsObjectEditor::FillMembers(CdmClass *pEventClass)
{
    QWidget *pParentWidget = nullptr;
    QTabWidget* pqTab = nullptr;
    QFormLayout* pLayout = nullptr;
    GetParentWidgetAndEventLayout(nullptr, pParentWidget, pLayout, pqTab, pEventClass);

    QList<long> qvlMembers         = getEventClassMemberList(pEventClass);
    QList<long>::iterator qvlIt    = qvlMembers.begin();
    QList<long>::iterator qvlItEnd = qvlMembers.end();

    if(!qvlMembers.isEmpty())
    {
        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
            int iMemberId = *qvlIt;
            CdmMember* pCdmMember = GetMemberById(iMemberId, pEventClass);

            if (pCdmMember &&
                    pCdmMember->GetAccessMode() != eDmMemberAccessPrivate &&
                    !pCdmMember->GetGroup())
            {
                    AddEventClassMember(pCdmMember, pParentWidget, pLayout, pqTab, GetObject());
            }
        }
    }

    if (pLayout->count() == 0 && pqTab)
    {
        pqTab->removeTab(0);
    }
}

/** +-=---------------------------------------------------------So 4. Nov 12:02:39 2012-----------*
 * @method  CwmsObjectEditor::CountAdditionalTabs            // private                           *
 * @return  int                                              //                                   *
 * @param   CdmClassGroup* p_pCdmGroup                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 12:02:39 2012-----------*/
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

/** +-=---------------------------------------------------------Mo 5. Nov 11:12:33 2012-----------*
 * @method  CwmsObjectEditor::CountAditionalTabsforNoneGroupMembers // private                    *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:12:33 2012-----------*/
int CwmsObjectEditor::CountAditionalTabsforNoneGroupMembers()
{
    int iRet = 0;
    QMap<long,CdmMember*> qmMemberMap;
    GetClassMembers(qmMemberMap);

    QMap<long,CdmMember*>::iterator qmIt = qmMemberMap.begin();
    QMap<long,CdmMember*>::iterator qmItEnd = qmMemberMap.end();

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
//Build Tabs for References --> Eventview
int CwmsObjectEditor::CountAditionalTabsforNoneGroupMembers(CdmClass *pEventClass)
{
    int iRet = 0;
    QMap<long, CdmMember*> qmMemberMap;
    pEventClass->GetMemberMap(qmMemberMap);

    QMap<long,CdmMember*>::iterator qmIt = qmMemberMap.begin();
    QMap<long,CdmMember*>::iterator qmItEnd = qmMemberMap.end();
    for(; qmIt != qmItEnd; ++qmIt)
    {
        CdmMember *pCdmEventMember = qmIt.value();
        if(CHKPTR(pCdmEventMember))
        {
            if(NeedsMemberTab(pCdmEventMember))
            {
                ++iRet;
            }
        }
    }
    return iRet;
}

/** +-=---------------------------------------------------------So 4. Nov 12:04:13 2012-----------*
 * @method  CwmsObjectEditor::NeedsMemberTab                 // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 12:04:13 2012-----------*/
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


/** +-=---------------------------------------------------------So 4. Nov 11:40:11 2012-----------*
 * @method  CwmsObjectEditor::GroupChangedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 11:40:11 2012-----------*/
void CwmsObjectEditor::GroupChangedSlot()
{
    m_qlAddedMembers.clear();
    QListWidgetItem* pItem = CwmsListWidgetHelper::GetSelectedItem(m_pqlwGroups);

    if (pItem)
    {
        CdmObject* pCdmObject = GetObject();
        CdmClass* pCdmClass = pCdmObject->GetClass();

        if (CHKPTR(pCdmClass))
        {
            int iGroupId = pItem->data(Qt::UserRole).toInt();

            if (iGroupId >= 0)
            {
                CdmClassGroup* pGroup = pCdmClass->FindGroupById(iGroupId);
                FillMembers(pGroup);
            }
            else
            {
                FillMembers();
            }
        }
    }
    else
    {
        FillMembers();
    }
}

void CwmsObjectEditor::GroupChangedSlot(CdmClass *pClass)
{
    m_qlAddedMembers.clear();
    QListWidgetItem* pItem = CwmsListWidgetHelper::GetSelectedItem(m_pqlwGroups);

    if (pItem)
    {
        if (CHKPTR(pClass))
        {
            int iGroupId = pItem->data(Qt::UserRole).toInt();

            if (iGroupId >= 0)
            {
                CdmClassGroup* pGroup = pClass->FindGroupById(iGroupId);
                FillMembers(pGroup);
            }
            else
            {
                if(m_bCheckEventMode)
                {
                    FillMembers(pClass);
                }
                FillMembers();
            }
        }
    }
    else
    {
        if(CHKPTR(pClass))
        {
            if(m_bCheckEventMode)
            {
                FillMembers(pClass);
            }
        }
        else
        {
            FillMembers();
        }
    }
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:09:07 2012-----------*
 * @method  CwmsObjectEditor::AddMemberInFormLayout          // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_qwParent                              //                                   *
 * @param   QFormLayout* p_qLayout                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:09:07 2012-----------*/
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

void CwmsObjectEditor::AddEventClassMemberInFormLayout(QString p_qstrKeyname,
                                                       QWidget* p_qwParent,
                                                       QFormLayout* p_qLayout,
                                                       CdmObject *pCdmEventObject)
{
    CdmValue* pCdmValue = m_cCdmObjectAdaptor.GetEventValue(p_qstrKeyname, pCdmEventObject);

    if (CHKPTR(pCdmValue))
    {
        CreateEventMemberUi(pCdmValue, p_qwParent, p_qLayout, pCdmEventObject);
    }

    m_qlAddedMembers.append(p_qstrKeyname);
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:16:02 2012-----------*
 * @method  CwmsObjectEditor::AddMemberInTab                 // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QTabWidget* p_qwParent                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:16:02 2012-----------*/
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

void CwmsObjectEditor::AddEventClassMemberInTab(QString p_qstrKeyname, QTabWidget* p_qwParent, CdmObject *pCdmEventObject)
{
    CdmValue* pCdmValue = m_cCdmObjectAdaptor.GetEventValue(p_qstrKeyname, pCdmEventObject);

    if (CHKPTR(pCdmValue))
    {
        QWidget* pqwWidget = new QWidget(nullptr);
        int iTabIndex = p_qwParent->addTab(pqwWidget, p_qstrKeyname);
        p_qwParent->setTabText(iTabIndex, p_qstrKeyname);
        QVBoxLayout* pqLayout = new QVBoxLayout(pqwWidget);

        if(!CreateEventTabMemberUi(pCdmValue, pqwWidget, pqLayout, pCdmEventObject))
        {
            DELPTR(pqwWidget)
        }
    }

    m_qlAddedMembers.append(p_qstrKeyname);
}

/** +-=---------------------------------------------------------So 4. Nov 11:34:58 2012-----------*
 * @method  CwmsObjectEditor::HasMembersWithoutGroup         // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 11:34:58 2012-----------*/
bool CwmsObjectEditor::HasMembersWithoutGroup()
{
    bool bRet = false;

    CdmObject* pCdmObject = GetObject();
    CdmClass* pCdmClass = pCdmObject->GetClass();

    if (CHKPTR(pCdmClass))
    {
        QMap<long,CdmMember*> qmMemberMap;
        pCdmClass->GetMemberMap(qmMemberMap);

        QMap<long,CdmMember*>::iterator qmIt = qmMemberMap.begin();
        QMap<long,CdmMember*>::iterator qmItEnd = qmMemberMap.end();

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

/** +-=---------------------------------------------------------Mo 5. Nov 11:28:07 2012-----------*
 * @method  CwmsObjectEditor::CreateTabMemberUi              // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqfParent                             //                                   *
 * @param   QVBoxLayout* p_qLayout                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:28:07 2012-----------*/
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

bool CwmsObjectEditor::CreateEventTabMemberUi(CdmValue* p_pCdmValue,
                                              QWidget* p_pqfParent,
                                              QVBoxLayout* p_qLayout,
                                              CdmObject *pEventObject)
{
    bool bRet = false;

    if(CHKPTR(p_pCdmValue))
    {
        const CdmMember *pCdmMember = p_pCdmValue->GetEventMember(pEventObject);
        if(!FindInHiddenList(p_pCdmValue))
        {
            CoeValueWidget* pCoeValueWidget = CoeValueWidget::CreateEventValueWidget(p_pCdmValue, p_pqfParent, pEventObject);
            m_pCoeValueWidget = pCoeValueWidget;

            if(m_pCoeValueWidget)
            {

                EdmValueType edmValueType = p_pCdmValue->GetEvenValueType(pEventObject);
                if(edmValueType == eDmValueObjectRef)
                {
                    m_pCoeValueWidget->CreateTabWidget(p_pqfParent, p_qLayout);
                    CheckEditable(pCdmMember, m_pCoeValueWidget);
                    m_pCoeValueWidget->SetEventValueInTab(p_pCdmValue, pEventObject);
                }
                else
                {
                    m_pCoeValueWidget->CreateTabWidget(p_pqfParent, p_qLayout);
                    CheckEditable(pCdmMember, m_pCoeValueWidget);
                    m_pCoeValueWidget->SetValue(p_pCdmValue);
                }
                bRet = true;
            }
        }
    }
    return bRet;
}

/** +-=---------------------------------------------------------Mo 11. Feb 10:25:00 2013----------*
 * @method  CwmsObjectEditor::CheckReadOnly                  // private                           *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMeber                     //                                   *
 * @param   CoeValueWidget* p_pWidget                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 10:25:00 2013----------*/
void CwmsObjectEditor::CheckReadOnly(const CdmMember* p_pCdmMeber, CoeValueWidget* p_pWidget)
{
    if (CHKPTR(p_pWidget) && CHKPTR(p_pCdmMeber))
    {
        CdmClass *pClass = p_pCdmMeber->GetClass();

        //If EventSourcing is active, Member has to be read-only
        if(pClass->IsEventSourcingActive())
        {
            INFO("Member in ReadOnlyList will be set ReadOnly: " + p_pCdmMeber->GetKeyname())
            p_pWidget->SetReadOnly();
        }
        else
        {
            if (IsReadOnly(p_pCdmMeber))
            {
                INFO("Member in ReadOnlyList will be set ReadOnly: " + p_pCdmMeber->GetKeyname())
                p_pWidget->SetReadOnly();
            }
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


/** +-=---------------------------------------------------------Mi 22. Aug 15:15:16 2012----------*
 * @method  CwmsObjectEditor::CreateMemberUi                  // private                           *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqfParent                             //                                   *
 * @param   QFormLayout* p_qLayout                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 15:15:16 2012----------*/
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
                            ((CoedtwObjectRef*)m_pCoeValueWidget)->SetObjectList(tStringPair.first, tStringPair.second);
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

void CwmsObjectEditor::CreateEventMemberUi(CdmValue* p_pCdmValue,
                                           QWidget* p_pqfParent,
                                           QFormLayout* p_qLayout,
                                           CdmObject *pEventObject)
{

    if (CHKPTR(p_pCdmValue))
    {
        const CdmObject *pCdmEventObject = const_cast<CdmObject*>(pEventObject);
        const CdmMember* pCdmMember = p_pCdmValue->GetEventMember(pCdmEventObject);

        if (!FindInHiddenList(p_pCdmValue))
        {
            CoeValueWidget* pCoeValueWidget = CoeValueWidget::CreateEventValueWidget(p_pCdmValue, p_pqfParent, pCdmEventObject);
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
                            ((CoedtwObjectRef*)m_pCoeValueWidget)->SetObjectList(tStringPair.first, tStringPair.second);
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
                m_pCoeValueWidget->CreateEventWidget(p_qLayout, p_pqfParent);
                CheckEditable(pCdmMember, m_pCoeValueWidget);
            }
        }
        else
        {
            INFO("Member in HiddenList will not be shown: " + p_pCdmValue->GetKeyname())
        }
    }
}

/** +-=---------------------------------------------------------Di 24. Jan 22:49:24 2006----------*
 * @method  CwmsObjectEditor::CaptionChangedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @param   const QString & p_qstrCaption                    //                                   *
 * @comment This slot will be called if the user changes the caption.                             *
 *----------------last changed: Wolfgang GraÃŸhof----------------Di 24. Jan 22:49:24 2006----------*/
void CwmsObjectEditor::CaptionChangedSlot(  const QString & p_qstrCaption )
{
    GetObject()->SetCaption(p_qstrCaption);
}

/** +-=---------------------------------------------------------Fr 6. Jan 18:17:58 2006-----------*
 * @method  CwmsObjectEditor::GetSortMemberList               // public                            *
 * @return  QValueList<long>                                 // the list of members               *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 6. Jan 18:17:58 2006-----------*/
QList<long> CwmsObjectEditor::GetSortMemberList(  )
{
    QList<long> qvlMembers;

    if(m_qstrlSortedMembers.isEmpty())
    {
        CdmClass* pCdmClass = GetObject()->GetClass();

        if (CHKPTR(pCdmClass))
        {
            QVector<QString> qvSequence = pCdmClass->GetMemberSequence();

            if (qvSequence.isEmpty())
            {
                QMap<long,CdmMember*> qmMembers;
                pCdmClass->GetMemberMap(qmMembers);

                QMap<long, CdmMember*>::iterator qmIt    = qmMembers.begin();
                QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    CdmMember* pCdmMember = qmIt.value();

                    if (pCdmMember)
                    {
                        long lMemberId = pCdmMember->GetId();
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

QList<long> CwmsObjectEditor::getEventClassMemberList(CdmClass *pClass)
{
    QList<long> qvlMembers;

    if(m_qstrlEventClassMembers.isEmpty())
    {
        if(CHKPTR(pClass))
        {
            QVector<QString> qvSequence = pClass->GetMemberSequence();

            if(qvSequence.isEmpty())
            {
                QMap<long,CdmMember*> qmMembers;
                pClass->GetMemberMap(qmMembers);

                QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
                QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

                for(; qmIt != qmItEnd; ++qmIt)
                {
                    CdmMember *pMember = qmIt.value();

                    if(pMember)
                    {
                        long lMemberId = pMember->GetId();
                        qvlMembers.append(lMemberId);
                    }
                }
            }
            else
            {
                for(int iCounter = 0; iCounter < qvSequence.count(); ++iCounter)
                {
                    const CdmMember *pMember = pClass->FindMember(qvSequence[iCounter]);

                    if(pMember)
                    {
                        qvlMembers.append(pMember->GetId());
                    }
                }
            }
        }
    }
    else
    {
        qvlMembers = getEventClassMemberListFromStringList(pClass);
    }

    return qvlMembers;
}

/** +-=---------------------------------------------------------Fr 20. Jan 22:43:03 2006----------*
 * @method  CwmsObjectEditor::GetSortedMemberListFromStringList // public                          *
 * @return  QValueList<long>                                 //                                   *
 * @comment This method creates the sorted memberlist with the helb of the string list.           *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 20. Jan 22:43:03 2006----------*/
QList<long> CwmsObjectEditor::GetSortedMemberListFromStringList(  )
{
    QList<long> qvlMembers;

    QStringList::Iterator  qstrIt    = m_qstrlSortedMembers.begin();
    QStringList::Iterator  qstrItEnd = m_qstrlSortedMembers.end();

    for(; qstrIt != qstrItEnd; ++qstrIt)
    {
        CdmValue* pCdmValue = GetObject()->GetValue(*qstrIt);

        if(CHKPTR(pCdmValue))
        {
            long lMemberId = pCdmValue->GetMemberId();
            qvlMembers.append(lMemberId);
        }
        else
        {
#ifdef WOGRA_DEBUG
            CdmMessageManager::critical(tr("Datenfehler"),
                                        tr("Datum existiert nicht. Datum:") + *qstrIt);
#endif //
        }
    }

    return qvlMembers;
}

QList<long> CwmsObjectEditor::getEventClassMemberListFromStringList(CdmClass *pClass)
{
    QList<long> qvlMembers;

    QStringList::Iterator qstrIt = m_qstrlEventClassMembers.begin();
    QStringList::Iterator qstrItEnd = m_qstrlEventClassMembers.end();

    for(; qstrIt != qstrItEnd; ++qstrIt)
    {
        const CdmMember *pMember = pClass->FindMember(*qstrIt);
        if(pMember)
        {
            long lMemberId = pMember->GetId();
            qvlMembers.append(lMemberId);
        }
    }
    return qvlMembers;
}

/** +-=---------------------------------------------------------Fr 6. Jan 18:14:58 2006-----------*
 * @method  CwmsObjectEditor::FindValueByMemberId             // private                           *
 * @return  CdmValue*                                        //                                   *
 * @param   long p_lMemberId                                 //                                   *
 * @comment This method finds a value by MemberId                                                 *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 6. Jan 18:14:58 2006-----------*/
CdmValue* CwmsObjectEditor::FindValueByMemberId(  long p_lMemberId )
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

/** +-=---------------------------------------------------------Thu Dec 11 16:42:02 2003----------*
 * @method  CwmsObjectEditor::FindInHiddenList                // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method checks if a Value is in Hidden list. If found true will be returned    *
 *---------------------------------------------------------------Thu Dec 11 16:42:02 2003---------*/
bool CwmsObjectEditor::FindInHiddenList(  CdmValue* p_pCdmValue )
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

/** +-=---------------------------------------------------------Mo 11. Feb 10:52:23 2013----------*
 * @method  CwmsObjectEditor::IsReadOnly                     // private                           *
 * @return  bool                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method checks if a Value is in Hidden list. If found true will be returned       *
 *----------------last changed: --------------------------------Mo 11. Feb 10:52:23 2013----------*/
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


/** +-=---------------------------------------------------------Do 19. Jan 20:16:16 2006----------*
 * @method  CwmsObjectEditor::SetSortedList                   // public                            *
 * @return  void                                             //                                   *
 * @param   QStringList p_qstrlistSortedMembers              //                                   *
 * @comment This method sets a sorted memberlist.                                                 *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 19. Jan 20:16:16 2006----------*/
void CwmsObjectEditor::SetSortedList(  QStringList p_qstrlistSortedMembers )
{
    m_qstrlSortedMembers = p_qstrlistSortedMembers;
}

/** +-=---------------------------------------------------------Di 8. Mai 20:51:22 2007-----------*
 * @method  CwmsObjectEditor::SetCaptionValue                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment Over this method you can set, from which value the objectcaption will be              *
 *          autmatically copied.                                                                  *
 *----------------last changed: Wolfgang GraÃŸhof----------------Di 8. Mai 20:51:22 2007-----------*/
void CwmsObjectEditor::SetCaptionValue(QString p_qstrValue)
{
    m_qstrCaptionValue = p_qstrValue;
}

/** +-=---------------------------------------------------------Di 12. Aug 19:57:38 2008----------*
 * @method  CwmsObjectEditor::setObjectName                   // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 12. Aug 19:57:38 2008----------*/
void CwmsObjectEditor::setObjectName(QString p_qstrName)
{
    setWindowTitle(p_qstrName);
}

/** +-=---------------------------------------------------------Di 23. Jul 12:37:05 2013----------*
 * @method  CwmsObjectEditor::ConnectRuntime                 // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsRuntime* p_pRuntime                          //                                   *
 * @param   CwmsApplicationModule& p_cModule                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 23. Jul 12:37:05 2013----------*/
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

/** +-=---------------------------------------------------------Mo 17. Sep 16:13:00 2012----------*
 * @method  CwmsObjectEditor::SetModule                       // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 16:13:00 2012----------*/
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

/** +-=---------------------------------------------------------Fr 14. Dez 14:47:26 2012----------*
 * @method  CwmsObjectEditor::SetFormConfiguration           // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pObject                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 14:47:26 2012----------*/
void CwmsObjectEditor::SetFormConfiguration(CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        CwmsFormObject cForm(p_pObject);

        CdmClass *pCdmObjectClass = p_pObject->GetClass();
        if(CHKPTR(pCdmObjectClass))
        {
            if(pCdmObjectClass->IsEventSourcingActive())
            {
                SetReadOnly(false);
            }
            else
            {
                SetReadOnly(cForm.GetReadOnly());
            }

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

/** +-=---------------------------------------------------------Mo 17. Sep 16:12:36 2012----------*
 * @method  CwmsObjectEditor::Initialize                      // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @param   CwmsRuntime* p_pRuntime                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 16:12:36 2012----------*/
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

/** +-=---------------------------------------------------------Mo 17. Sep 16:21:08 2012----------*
 * @method  CwmsObjectEditor::JournalClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 16:21:08 2012----------*/
void CwmsObjectEditor::JournalClickedSlot()
{
    CwmsJournalViewer* pViewer = new CwmsJournalViewer(this);
    pViewer->FillDialog(GetObject());
    pViewer->exec();
    DELPTR(pViewer)
}

/** +-=---------------------------------------------------------Mo 17. Sep 16:21:38 2012----------*
 * @method  CwmsObjectEditor::PrintClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 16:21:38 2012----------*/
void CwmsObjectEditor::PrintClickedSlot()
{
    CwmsReportManager::PrintDefaultForObject(GetObject());
}

/** +-=---------------------------------------------------------Fr 14. Dez 10:42:24 2012----------*
 * @method  CwmsObjectEditor::AddFunctions                   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 10:42:24 2012----------*/
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

/** +-=---------------------------------------------------------Fr 14. Dez 10:44:49 2012----------*
 * @method  CwmsObjectEditor::FunctionClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 10:44:49 2012----------*/
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
    if(GetObject()->GetClass()->IsEventSourcingActive())
    {
    GroupChangedSlot(GetObject()->GetClass()); // updates the data in current displayed group
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
        if(pObject->GetClass()->IsEventSourcingActive())
        {
        GroupChangedSlot(GetObject()->GetClass()); // updates the data in current displayed group
        }
        GroupChangedSlot(); // updates the data in current displayed group
    }
}

void CwmsObjectEditor::setIsObjectEventEditor(bool bIsObjEEditor)
{
    m_bIsObjEventEditor = bIsObjEEditor;
}

bool CwmsObjectEditor::getIsObjectEventEditor()
{
    return m_bIsObjEventEditor;
}

bool CwmsObjectEditor::checkEventMode(QString qstr_checkEventMode)
{
    return checkForEventMode(qstr_checkEventMode);
}

bool CwmsObjectEditor::checkForEventMode(QString qstr_checkEventMode)
{
    if(qstr_checkEventMode == NEW || qstr_checkEventMode == DELETE)
    {
        m_bIsUpdateEvent = false;
    }
    else if(qstr_checkEventMode == UPDATE)
    {
        m_bIsUpdateEvent = true;
    }
    m_bCheckEventMode = true;
    return m_bCheckEventMode;
}

QList<CdmValue*> CwmsObjectEditor::getEventClassMemberValues() const
{
    return m_pCoeValueWidget->getEventClassValues();
}
