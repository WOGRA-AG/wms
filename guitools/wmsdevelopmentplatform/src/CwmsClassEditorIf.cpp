/******************************************************************************
 ** WOGRA Middleware Tools WMS Enterprise Manager Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA Solutions All rights reserved
 ******************************************************************************/




// System and QT Includes
#include <QPushButton>
#include <QLineEdit>
#include <QUuid>
#include <QMessageBox>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmClassMethod.h"
#include "CdmClassValidator.h"
#include "CdmExecutor.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmExecutorFunction.h"
#include "CdmMember.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmPackage.h"
#include "CdmClassGroup.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsAdminMainWindowIf.h"
#include "CwmsScriptingEnvironment.h"
#include "CwmsClassValidationEditor.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsFunctionEditor.h"
#include "CwmsMemberSequenceEditor.h"
#include "CwmsAddMemberIf.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsGroupEditorDlg.h"
#include "CwmsClassEditorIf.h"



/** +-=---------------------------------------------------------Mo 20. Aug 15:36:48 2012----------*
 * @method  CwmsClassEditorIf::CwmsClassEditorIf             // public                            *
 * @return                                                   //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment The constructor of the classeditor. it fills the classeditor with data.               *
 *----------------last changed: --------------------------------Mo 20. Aug 15:36:48 2012----------*/
CwmsClassEditorIf::CwmsClassEditorIf(CdmClass* p_pCdmClass, QWidget* parent)
    : QWidget(parent),
      m_rpCdmClass(p_pCdmClass),
      m_rpMainWindow(nullptr),
      m_bEditMode(false)
{
    setupUi(this);
    m_pqpbCancel->hide();
    m_pqpbUpdate->hide();
    m_pqpbCancelEvent->hide();
    m_pqpbUpdateEvent->hide();

    FillDialog();
}

/** +-=---------------------------------------------------------Do 17. Mai 09:55:49 2007----------*
 * @method  CwmsClassEditorIf::~CwmsClassEditorIf            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsClassEditorIf                                             *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 17. Mai 09:55:49 2007----------*/
CwmsClassEditorIf::~CwmsClassEditorIf()
{
}

/** +-=---------------------------------------------------------Do 17. Mai 10:19:07 2007----------*
 * @method  CwmsClassEditorIf::FillDialog                    // private                           *
 * @return  void                                             //                                   *
 * @comment fills the widget with relevant data.                                                  *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 17. Mai 10:19:07 2007----------*/
void CwmsClassEditorIf::FillDialog()
{
    if (CHKPTR(m_rpCdmClass))
    {
        FillPackageData();
        FillBaseData();
        FillBaseClasses();
        FillMembers();
        FillGroups();
        FillFunctions();
        FillValidations();
        FillCUDEvents();
    }
}

void CwmsClassEditorIf::FillPackageData()
{
    m_pqcbPackage->setEnabled(false);
    m_pqcbPackage->addItem("");

    if (CHKPTR(m_rpCdmClass))
    {
        CdmClassManager* pClassManager = m_rpCdmClass->GetClassManager();

        if(CHKPTR(pClassManager))
        {
            QList<CdmPackage*> qlPackages = pClassManager->GetPackageList();

            for (int iPos = 0; iPos < qlPackages.count(); ++iPos)
            {
                FillPackageComboBox(qlPackages[iPos]);
            }
        }
    }
}


void CwmsClassEditorIf::FillPackageComboBox(CdmPackage* p_pPackage)
{
    if (CHKPTR(p_pPackage))
    {
        m_pqcbPackage->addItem(p_pPackage->GetPackageString(), p_pPackage->GetUriInternal());

        if (m_rpCdmClass->GetPackage() == p_pPackage)
        {
            m_pqcbPackage->setCurrentText(p_pPackage->GetPackageString());
        }

        QList<CdmPackage*> qlPackages;
        p_pPackage->GetChildren(qlPackages);

        for (int iPos = 0; iPos < qlPackages.count(); ++iPos)
        {
            FillPackageComboBox(qlPackages[iPos]);
        }
    }
}

void CwmsClassEditorIf::FillCUDEvents()
{
    m_pqrbDefault->setEnabled(false);
    m_pqrbEventClass->setEnabled(false);
    m_pqrbEventSourcing->setEnabled(false);

    if(m_rpCdmClass->IsEventClass())
    {
        m_pqrbDefault->setChecked(false);
        m_pqrbEventClass->setChecked(true);
        m_pqrbEventSourcing->hide();
        m_pqgbShowEvents->hide();
        m_pqgbChooseEvents->hide();
    }
    else if(m_rpCdmClass->IsEventSourcingActive())
    {
        m_pqrbDefault->setChecked(false);
        m_pqrbEventClass->hide();
        m_pqrbEventSourcing->setChecked(true);
        m_pqgbChooseEvents->show();
        FillCreateEvent();
        FillDeleteEvent();
        FillUpdateEvent();
    }
}

void CwmsClassEditorIf::FillCreateEvent()
{
    int iIndex = m_pqswWCreateEvent->currentIndex();

    QStringList qstrlCreateEvent = m_rpCdmClass->getCreateEventClassStringList();

    if(qstrlCreateEvent.isEmpty())
    {
        m_pqswWCreateEvent->hide();
        m_pqlCreateEvents->hide();
    }
    else if(qstrlCreateEvent.count() == 1)
    {
        m_pqleCreateEventClass->setText(qstrlCreateEvent.at(0));
        m_pqleCreateEventClass->setEnabled(true);
        m_pqswWCreateEvent->setCurrentIndex(iIndex);
    }
    else if(qstrlCreateEvent.count() > 1)
    {
        m_pqleCreateEventClass->setEnabled(false);
        m_pqcbCreateEventClass->clear();

        for(int i = 0; i < qstrlCreateEvent.count(); ++i)
        {
            QString qstr_ClassTemp = qstrlCreateEvent.at(i);
            m_pqcbCreateEventClass->insertItem(i, qstr_ClassTemp);
        }
        m_pqcbCreateEventClass->setEnabled(false);
        m_pqswWCreateEvent->setCurrentIndex(iIndex+1);
    }    
    else
    {
        m_pqswWCreateEvent->hide();
        m_pqlCreateEvents->hide();
    }
}

void CwmsClassEditorIf::FillDeleteEvent()
{
    int iIndex = m_pqswWDeleteEvent->currentIndex();

    QStringList qstrlDeleteEvent = m_rpCdmClass->getDeleteEventClassStringList();

    if(qstrlDeleteEvent.isEmpty())
    {
        m_pqswWDeleteEvent->hide();
        m_pqlDeleteEvents->hide();
    }
    else if(qstrlDeleteEvent.count() == 1)
    {
        m_pqleDeleteEventClass->setText(qstrlDeleteEvent.at(0));
        m_pqleDeleteEventClass->setEnabled(true);
        m_pqswWDeleteEvent->setCurrentIndex(iIndex);
    }
    else if(qstrlDeleteEvent.count() > 1)
    {
        m_pqleDeleteEventClass->setEnabled(false);
        m_pqcbDeleteEventClass->clear();

        for(int i = 0; i < qstrlDeleteEvent.count(); ++i)
        {
            QString qstr_ClassTemp = qstrlDeleteEvent.at(i);
            m_pqcbDeleteEventClass->insertItem(i, qstr_ClassTemp);
        }
        m_pqcbDeleteEventClass->setEnabled(false);
        m_pqswWDeleteEvent->setCurrentIndex(iIndex+1);
    }
    else
    {
        m_pqswWDeleteEvent->hide();
        m_pqlDeleteEvents->hide();
    }
}

void CwmsClassEditorIf::FillUpdateEvent()
{
    int iIndex = m_pqswWUpdateEvent->currentIndex();

    QStringList qstrlUpdateEvent = m_rpCdmClass->getUpdateEventClassStringList();

    if(qstrlUpdateEvent.isEmpty())
    {
        m_pqswWUpdateEvent->hide();
        m_pqlUpdateEvents->hide();
    }
    else if(qstrlUpdateEvent.count() == 1)
    {
        m_pqleUpdateEventClass->setText(qstrlUpdateEvent.at(0));
        m_pqleUpdateEventClass->setEnabled(true);
        m_pqswWUpdateEvent->setCurrentIndex(iIndex);
    }
    else if(qstrlUpdateEvent.count() > 1)
    {
        m_pqleUpdateEventClass->setEnabled(false);
        m_pqcbUpdateEventClass->clear();

        for(int i = 0; i < qstrlUpdateEvent.count(); ++i)
        {
            QString qstr_ClassTemp = qstrlUpdateEvent.at(i);
            m_pqcbUpdateEventClass->insertItem(i, qstr_ClassTemp);
        }
        m_pqcbUpdateEventClass->setEnabled(false);
        m_pqswWUpdateEvent->setCurrentIndex(iIndex+1);
    }
    else
    {
        m_pqswWUpdateEvent->hide();
        m_pqlUpdateEvents->hide();
    }
}

/** +-=---------------------------------------------------------Do 17. Mai 10:18:54 2007----------*
 * @method  CwmsClassEditorIf::FillBaseData                  // private                           *
 * @return  void                                             //                                   *
 * @comment fills the class basedata to the deitfields.                                           *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 17. Mai 10:18:54 2007----------*/
void CwmsClassEditorIf::FillBaseData()
{
    if (CHKPTR(m_rpCdmClass))
    {
        m_pqleCaption->setText(m_rpCdmClass->GetCaption());
        m_pqleCreator->setText(QString::number(m_rpCdmClass->GetCreatorId()));
        m_pqleId->setText(QString::number(m_rpCdmClass->GetId()));
        m_pqleKeyname->setText(m_rpCdmClass->GetKeyname());
        m_pqleKeyname->setReadOnly(true);
        m_pqchbImmutable->setChecked(m_rpCdmClass->IsImmutable());
        m_pqchbSingleton->setChecked(m_rpCdmClass->IsSingleton());
        m_pqrbEventClass->setChecked(m_rpCdmClass->IsEventClass());
        m_pqrbEventSourcing->setChecked(m_rpCdmClass->IsEventSourcingActive());

        if(!m_pqrbEventClass->isChecked() || !m_pqrbEventSourcing->isChecked())
        {
            m_pqrbDefault->setChecked(true);
        }
        m_pqleLastChangeDate->setText(m_rpCdmClass->GetLastChange().toString());
        m_pqleLastChanger->setText(QString::number(m_rpCdmClass->GetModifierId()));
        m_pqteComment->setPlainText(m_rpCdmClass->GetComment());
        m_pqchbAbstract->setChecked(m_rpCdmClass->IsAbstract());

        QMap<long,CdmMember*> qmMembers;
        m_rpCdmClass->GetMemberMap(qmMembers);

        QMap<long,CdmMember*>::iterator qmIt = qmMembers.begin();
        QMap<long,CdmMember*>::iterator qmItEnd = qmMembers.end();

        m_pqcbCaptionMember->addItem("-");

        for (; qmIt != qmItEnd; ++qmIt)
        {
            m_pqcbCaptionMember->addItem(qmIt.value()->GetCaption() + " (" + qmIt.value()->GetKeyname() + ")", qmIt.value()->GetKeyname());
        }

        m_pqcbCaptionMember->setCurrentIndex(m_pqcbCaptionMember->findData(m_rpCdmClass->GetCaptionMemberKeyname()));
    }
}

/** +-=---------------------------------------------------------Do 17. Mai 10:18:39 2007----------*
 * @method  CwmsClassEditorIf::FillBaseClasses               // private                           *
 * @return  void                                             //                                   *
 * @comment fills the baseclasses to the listbox                                                  *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 17. Mai 10:18:39 2007----------*/
void CwmsClassEditorIf::FillBaseClasses()
{
    if (CHKPTR(m_rpCdmClass))
    {
        // filling Baseclasses
        m_pqlbBaseClasses->clear();
        CdmClassManager* pCdmClassManager = m_rpCdmClass->GetClassManager();
        QMap<long,long> qmBaseClasses = m_rpCdmClass->GetBaseClasses();
        QMap<long,long>::iterator qmItBaseClasses = qmBaseClasses.begin();
        QMap<long,long>::iterator qmItBaseClassesEnd = qmBaseClasses.end();

        if (qmBaseClasses.count() > 0)
        {
            for (; qmItBaseClasses != qmItBaseClassesEnd; ++qmItBaseClasses)
            {
                long lId = qmItBaseClasses.value();

                CdmClass* pCdmBaseClass = pCdmClassManager->FindClassById(lId);

                if (CHKPTR(pCdmBaseClass))
                {
                   m_pqlbBaseClasses->addItem(pCdmBaseClass->GetFullQualifiedName());
                }
            }
        }
    }
}

void CwmsClassEditorIf::FillMembers()
{
    if (CHKPTR(m_rpCdmClass))
    {
        m_pqlvMembers->clear();
        CdmClassManager* pCdmClassManager = m_rpCdmClass->GetClassManager();
        QMap<long, CdmMember*> qmMembers;
        qmMembers = m_rpCdmClass->GetClassMemberMap();


        QMap<long, CdmMember*>::iterator qmItMember = qmMembers.begin();
        QMap<long, CdmMember*>::iterator qmItMemberEnd = qmMembers.end();

        for (; qmItMember != qmItMemberEnd; ++qmItMember)
        {
            CdmMember* pCdmMember = qmItMember.value();

            if (CHKPTR(pCdmMember))
            {
                QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvMembers);
                pqlviItem->setText(0, QString::number(pCdmMember->GetId()));
                pqlviItem->setText(1, pCdmMember->GetCaption());
                pqlviItem->setText(2, pCdmMember->GetKeyname());
                pqlviItem->setText(3, pCdmMember->GetValueTypeAsString());

                switch (pCdmMember->GetAccessMode())
                {
                case eDmMemberAccessPublic:
                    pqlviItem->setText(4, tr("Öffentlich"));
                    break;
                case eDmMemberAccessProtected:
                    pqlviItem->setText(4, tr("Geschützt"));
                    break;
                case eDmMemberAccessPrivate:
                    pqlviItem->setText(4, tr("Privat"));
                    break;
                }

                if (pCdmMember->IsSystemMember())
                {
                    pqlviItem->setText(5, tr("Ja"));
                }
                else
                {
                    pqlviItem->setText(5, tr("Nein"));
                }

                QString qstrDefault = pCdmMember->GetDefaultValue().toString();
                pqlviItem->setText(6, qstrDefault);

                if (pCdmMember->IsOwner())
                {
                    pqlviItem->setText(7, tr("Ja"));
                }
                else
                {
                    pqlviItem->setText(7, tr("Nein"));
                }

                if (pCdmMember->IsUnique())
                {
                    pqlviItem->setText(8, tr("Ja"));
                }
                else
                {
                    pqlviItem->setText(8, tr("Nein"));
                }

                if(pCdmMember->GetValueType() == eDmValueObjectRef ||
                        pCdmMember->GetValueType() == eDmValueContainerRef ||
                        pCdmMember->GetValueType() == eDmValueListObjects)
                {
                    long lRefId = pCdmMember->GetClassReference();

                    if (lRefId > 0)
                    {
                        CdmClass* pCdmRefClass = pCdmClassManager->FindClassById(lRefId);

                        if (pCdmRefClass)
                        {
                            pqlviItem->setText(9, pCdmRefClass->GetKeyname());
                        }
                    }
                }

                pqlviItem->setText(10, pCdmMember->GetComment());
                const CdmClassGroup* pCdmGroup = pCdmMember->GetGroup();

                if (pCdmGroup)
                {
                    pqlviItem->setText(11, pCdmGroup->GetName());
                }
                else
                {
                    pqlviItem->setText(11, tr("keine Zuordnung"));
                }
            }
        }

        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvMembers);
    }
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:45:12 2008----------*
 * @method  CwmsClassEditorIf::CancelClickedSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:45:12 2008----------*/
void CwmsClassEditorIf::CancelClickedSlot()
{
    m_pqleCaption->setReadOnly(true);
    m_pqteComment->setReadOnly(true);
    m_pqchbAbstract->setEnabled(false);
    m_pqcbCaptionMember->setEnabled(false);
    m_pqcbPackage->setEnabled(false);
    m_pqchbImmutable->setEnabled(false);
    m_pqchbSingleton->setEnabled(false);

    m_pqpbEdit->show();
    m_pqpbCancel->hide();
    m_pqpbUpdate->hide();
    FillBaseData();
    m_bEditMode =false;
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:45:20 2008----------*
 * @method  CwmsClassEditorIf::EditClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:45:20 2008----------*/
void CwmsClassEditorIf::EditClickedSlot()
{
    m_bEditMode = true;
    m_pqleCaption->setReadOnly(false);
    m_pqteComment->setReadOnly(false);

    if (m_rpCdmClass->IsInUse())
    {
        m_pqleKeyname->setReadOnly(true);
        m_pqleKeyname->setToolTip(tr("Die Schlüsselbezeichnung kann nicht mehr geändert werden, da die Klasse im Datenmodell aktiv verwendet wird."));
    }
    else
    {
        m_pqleKeyname->setReadOnly(false);
    }
    m_pqchbAbstract->setEnabled(true);
    m_pqchbImmutable->setEnabled(true);
    m_pqchbSingleton->setEnabled(true);
    m_pqcbCaptionMember->setEnabled(true);
    m_pqcbPackage->setEnabled(true);

    m_pqpbEdit->hide();
    m_pqpbCancel->show();
    m_pqpbUpdate->show();
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:45:28 2008----------*
 * @method  CwmsClassEditorIf::UpdateClickedSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:45:28 2008----------*/
void CwmsClassEditorIf::UpdateClickedSlot()
{
    m_rpCdmClass->SetCaption(m_pqleCaption->text());
    m_rpCdmClass->SetComment(m_pqteComment->toPlainText());
    m_rpCdmClass->SetAbstract(m_pqchbAbstract->isChecked());
    m_rpCdmClass->SetCaptionMember(m_pqcbCaptionMember->currentData().toString());
    m_rpCdmClass->SetKeyname(m_pqleKeyname->text());
    m_rpCdmClass->SetImmutable(m_pqchbImmutable->isChecked());
    m_rpCdmClass->SetSingleton(m_pqchbSingleton->isChecked());

    UpdatePackage();
    m_rpCdmClass->Commit();
    CancelClickedSlot();
    m_rpMainWindow->CloseClassRelatedContainerUis(m_rpCdmClass);
    emit ClassModifiedSignal();
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:45:36 2008----------*
 * @method  CwmsClassEditorIf::AddBaseClassClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:45:36 2008----------*/
void CwmsClassEditorIf::AddBaseClassClickedSlot()
{
    CdmClass* pBaseClass = CwmsClassSelectionIf::GetClass(this);

    if (pBaseClass)
    {
        if (!pBaseClass->IsInherited(m_rpCdmClass->GetId()) &&
                pBaseClass != m_rpCdmClass)
        {
            m_rpCdmClass->AddBaseClass(pBaseClass);
            m_rpCdmClass->Commit();
        }
        else
        {
            CdmMessageManager::critical(tr("Basisklasse kann nicht hinzugefügt werden."),
                                        tr("Die selektierte Klasse hat diese Klasse bereits als Basisklasse.\n"
                                           "Dies ist nicht erlaubt!"));
        }
    }

    FillBaseClasses();
    emit ClassModifiedSignal();
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:45:45 2008----------*
 * @method  CwmsClassEditorIf::RemoveBaseClassClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:45:45 2008----------*/
void CwmsClassEditorIf::RemoveBaseClassClickedSlot()
{
    if (!m_rpCdmClass->IsInUse())
    {
        QListWidgetItem* pqlbItem = GetSelectedBaseClassItem();

        if (pqlbItem)
        {
            QString qstrBaseClass = pqlbItem->text();
            int iSuccess = m_rpCdmClass->RemoveBaseClass(qstrBaseClass);

            if (iSuccess > 0)
            {
                m_rpCdmClass->Commit();
                delete pqlbItem;
            }
            else
            {
                CdmMessageManager::critical(tr("Basisklasse kann nicht gelöscht werden!"),
                                            tr("Das System meldet einen Fehler Fehlercode:") + QString::number(iSuccess));
            }
        }
        else
        {
            CdmMessageManager::critical(tr("Basisklasse kann nicht gelöscht werden!"),
                                        tr("Es wurde keine Basisklasse ausgewÃ¤hlt."));
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Basisklasse kann nicht gelöscht werden!"),
                                    tr("Da diese Klasse bereits verwendet wird, kann eine Basisklasse nicht mehr gelöscht werden."));
    }

    emit ClassModifiedSignal();
}

/** +-=---------------------------------------------------------Di 14. Aug 14:58:29 2012----------*
 * @method  CwmsClassEditorIf::GetSelectedBaseClassItem      // private                           *
 * @return  QListWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 14:58:29 2012----------*/
QListWidgetItem* CwmsClassEditorIf::GetSelectedBaseClassItem()
{
    QListWidgetItem* pItem = nullptr;
    QList<QListWidgetItem*> qlItems = m_pqlbBaseClasses->selectedItems();

    if (qlItems.count() > 0)
    {
        pItem = qlItems[0];
    }

    return pItem;
}

/** +-=---------------------------------------------------------Di 14. Aug 14:59:59 2012----------*
 * @method  CwmsClassEditorIf::GetSelectedMemberItem         // private                           *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 14:59:59 2012----------*/
QTreeWidgetItem* CwmsClassEditorIf::GetSelectedMemberItem()
{
    QTreeWidgetItem* pItem = nullptr;
    QList<QTreeWidgetItem*> qlItems = m_pqlvMembers->selectedItems();

    if (qlItems.count() > 0)
    {
        pItem = qlItems[0];
    }

    return pItem;
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:45:54 2008----------*
 * @method  CwmsClassEditorIf::AddMemberClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:45:54 2008----------*/
void CwmsClassEditorIf::AddMemberClickedSlot()
{
    CwmsAddMemberIf pCwmsAddMemberIf(m_rpCdmClass, this);
    pCwmsAddMemberIf.Init();
    pCwmsAddMemberIf.exec();
    m_rpCdmClass->Commit();
    FillMembers();
    emit ClassModifiedSignal();
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:46:04 2008----------*
 * @method  CwmsClassEditorIf::EditMemberClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:46:04 2008----------*/
void CwmsClassEditorIf::EditMemberClickedSlot()
{
    QTreeWidgetItem* pqlviItem = GetSelectedMemberItem();

    if (pqlviItem)
    {
        QString qstrMemberKey = pqlviItem->text(2);
        CdmMember* pCdmMember = const_cast<CdmMember*>(m_rpCdmClass->FindMember(qstrMemberKey));

        if (CHKPTR(pCdmMember))
        {
            CwmsAddMemberIf pCwmsAddMemberIf(m_rpCdmClass, this);
            pCwmsAddMemberIf.SetMember(pCdmMember);

            if (pCwmsAddMemberIf.exec())
            {
                FillMembers();
                m_rpCdmClass->Commit();
                emit ClassModifiedSignal();
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:46:12 2008----------*
 * @method  CwmsClassEditorIf::DeleteMemberClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Mai 19:46:12 2008----------*/
void CwmsClassEditorIf::DeleteMemberClickedSlot()
{
    if (!m_rpCdmClass->IsInUse())
    {
        QTreeWidgetItem* pqlviItem = GetSelectedMemberItem();

        if (pqlviItem)
        {
            if (CdmMessageManager::Ask(tr("Member löschen"),
                                       tr("Der Member wird unwiderruflich gelöscht."
                                          "Wollen Sie das wirklich?")))
            {
                QString qstrMemberKey = pqlviItem->text(2);
                int iSuccess = m_rpCdmClass->DeleteMember(qstrMemberKey);

                if (iSuccess > 0)
                {
                    m_rpCdmClass->Commit();
                    delete pqlviItem;
                    emit ClassModifiedSignal();
                }
                else
                {
                    CdmMessageManager::critical(tr("Member kann nicht gelöscht werden!"),
                                                tr("Das System meldet einen Fehler. Fehlercode:") + QString::number(iSuccess));
                }
            }
        }
        else
        {
            CdmMessageManager::critical(tr("Member kann nicht gelöscht werden!"),
                                        tr("Es wurde kein Member ausgewählt."));
        }
    }
    else
    {
        CdmMessageManager::critical(tr("Member kann nicht gelöscht werden!"),
                                    tr("Da diese Klasse bereits verwendet wird, kann ein Member nicht mehr gelöscht werden."));
    }
}


/** +-=---------------------------------------------------------Fr 17. Aug 13:58:18 2012----------*
 * @method  CwmsClassEditorIf::NewGroupClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 13:58:18 2012----------*/
void CwmsClassEditorIf::NewGroupClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        CdmClassGroup* pCdmGroup = m_rpCdmClass->CreateGroup("", 1, nullptr);
        CwmsGroupEditorDlg pEditCwmsGroupEditorDlg(this);
        pEditCwmsGroupEditorDlg.FillDialog(pCdmGroup);

        if (pEditCwmsGroupEditorDlg.exec() == QDialog::Accepted)
        {
            m_rpCdmClass->SetModified();
            m_rpCdmClass->Commit();
            FillGroups();
            emit ClassModifiedSignal();
        }
    }
}

/** +-=---------------------------------------------------------Fr 17. Aug 13:58:29 2012----------*
 * @method  CwmsClassEditorIf::EditGroupClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 13:58:29 2012----------*/
void CwmsClassEditorIf::EditGroupClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        QTreeWidgetItem* pqtwItem = GetSelectedGroupItem();

        if (pqtwItem)
        {
            int iId = pqtwItem->data(0, Qt::UserRole).toInt();
            CdmClassGroup* pCdmGroup = m_rpCdmClass->FindGroupById(iId);

            if(pCdmGroup)
            {
                CwmsGroupEditorDlg pEdit(this);
                pEdit.FillDialog(pCdmGroup);

                if (pEdit.exec() == QDialog::Accepted)
                {
                    m_rpCdmClass->SetModified();
                    m_rpCdmClass->Commit();
                    FillGroups();
                    emit ClassModifiedSignal();
                }
            }
        }
    }
}

/** +-=---------------------------------------------------------Fr 17. Aug 13:58:40 2012----------*
 * @method  CwmsClassEditorIf::DeleteGroupClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 13:58:40 2012----------*/
void CwmsClassEditorIf::DeleteGroupClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        QTreeWidgetItem* pqtwItem = GetSelectedGroupItem();

        if (pqtwItem)
        {
            int iId = pqtwItem->text(0).toInt();
            m_rpCdmClass->DeleteGroup(iId);
            m_rpCdmClass->Commit();
            FillGroups();
            FillMembers();
            emit ClassModifiedSignal();
        }
    }
}

/** +-=---------------------------------------------------------Fr 17. Aug 13:58:52 2012----------*
 * @method  CwmsClassEditorIf::MoveGroupUpClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 13:58:52 2012----------*/
void CwmsClassEditorIf::MoveGroupUpClickedSlot()
{
    QTreeWidgetItem* pqtwItem = GetSelectedGroupItem();

    if (pqtwItem)
    {
        int iId = pqtwItem->data(0, Qt::UserRole).toInt();
        CdmClassGroup* pCdmGroup = m_rpCdmClass->FindGroupById(iId);

        if(pCdmGroup)
        {
            m_rpCdmClass->MoveGroupUp(iId);
            m_rpCdmClass->Commit();
            FillGroups(iId);
        }
    }
}

/** +-=---------------------------------------------------------Fr 17. Aug 13:59:07 2012----------*
 * @method  CwmsClassEditorIf::MoveGroupDownClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 13:59:07 2012----------*/
void CwmsClassEditorIf::MoveGroupDownClickedSlot()
{
    QTreeWidgetItem* pqtwItem = GetSelectedGroupItem();

    if (pqtwItem)
    {
        int iId = pqtwItem->data(0, Qt::UserRole).toInt();
        CdmClassGroup* pCdmGroup = m_rpCdmClass->FindGroupById(iId);

        if(pCdmGroup)
        {
            m_rpCdmClass->MoveGroupDown(iId);
            m_rpCdmClass->SetModified();
            m_rpCdmClass->Commit();
            FillGroups(iId);
        }
    }
}

/** +-=---------------------------------------------------------So 4. Nov 10:48:44 2012-----------*
 * @method  CwmsClassEditorIf::FillGroups                    // private                           *
 * @return  void                                             //                                   *
 * @param   int p_iSelectedId = -1                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 10:48:44 2012-----------*/
void CwmsClassEditorIf::FillGroups(int p_iSelectedId)
{
    if (CHKPTR(m_rpCdmClass))
    {
        QMap<int, CdmClassGroup*> qmGroups = m_rpCdmClass->GetClassGroups();
        m_pqtwGroups->clear();

        QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
        QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            int iId = qmIt.key();
            CdmClassGroup* pCdmGroup = qmIt.value();

            if (CHKPTR(pCdmGroup))
            {
                QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwGroups);
                pqtwItem->setText(0, QString::number(iId));
                pqtwItem->setText(1, pCdmGroup->GetName());
                pqtwItem->setData(0, Qt::UserRole, pCdmGroup->GetId());

                if (p_iSelectedId == pCdmGroup->GetId())
                {
                    pqtwItem->setSelected(true);
                }
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 20. Aug 15:45:48 2012----------*
 * @method  CwmsClassEditorIf::GetSelectedGroupItem          // public                            *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 15:45:48 2012----------*/
QTreeWidgetItem* CwmsClassEditorIf::GetSelectedGroupItem()
{
    QTreeWidgetItem* pItem = nullptr;
    QList<QTreeWidgetItem*> qlItems = m_pqtwGroups->selectedItems();

    if (qlItems.count() > 0)
    {
        pItem = qlItems[0];
    }

    return pItem;
}

/** +-=---------------------------------------------------------Do 23. Aug 09:45:12 2012----------*
 * @method  CwmsClassEditorIf::SequenceClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 09:45:12 2012----------*/
void CwmsClassEditorIf::SequenceClickedSlot()
{
    CwmsMemberSequenceEditor pEditor(this);
    pEditor.FillDialog(m_rpCdmClass);

    if (pEditor.exec() == QDialog::Accepted)
    {
        QVector<QString> qvSequence = pEditor.GetSequence();
        m_rpCdmClass->SetMemberSequence(qvSequence);
        m_rpCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:50:57 2012----------*
 * @method  CwmsClassEditorIf::FillValidations               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:50:57 2012----------*/
void CwmsClassEditorIf::FillValidations()
{
    QMap<QString, CdmClassValidator*>& qmValidators = m_rpCdmClass->GetValidators();

    QMap<QString, CdmClassValidator*>::iterator qmIt = qmValidators.begin();
    QMap<QString, CdmClassValidator*>::iterator qmItEnd = qmValidators.end();
    m_pqtwValidations->clear();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassValidator* pValidator = qmIt.value();

        if (pValidator)
        {
            QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwValidations);
            FillValidationDataToTree(pqtwItem, pValidator);
        }
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:51:12 2012----------*
 * @method  CwmsClassEditorIf::NewValidationClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:51:12 2012----------*/
void CwmsClassEditorIf::NewValidationClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        CdmClassValidator* pValidator = m_rpCdmClass->CreateValidator(QUuid::createUuid().toString());

        if (CwmsClassValidationEditor::EditValidation(m_rpCdmClass, pValidator, true, this))
        {
            QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwValidations);
            FillValidationDataToTree(pqtwItem, pValidator);
        }
    }
}

/** +-=---------------------------------------------------------Mo 26. Nov 12:57:22 2012----------*
 * @method  CwmsClassEditorIf::FillValidationDataToTree      // private                           *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @param   CdmClassValidator* p_pValidation                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 12:57:22 2012----------*/
void CwmsClassEditorIf::FillValidationDataToTree(QTreeWidgetItem* p_pItem,
                                                 CdmClassValidator* p_pValidation)
{
    if (CHKPTR(p_pItem) && CHKPTR(p_pValidation))
    {
        p_pItem->setText(0, p_pValidation->GetName());
        p_pItem->setText(1, p_pValidation->GetErrorMessage());

        if (p_pValidation->GetValidationType() == eDmValidationTypeObject)
        {
            p_pItem->setText(2, tr("Objekt"));
        }
        else
        {
            p_pItem->setText(2, tr("Container"));
        }
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:51:22 2012----------*
 * @method  CwmsClassEditorIf::EditValidationClickedSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:51:22 2012----------*/
void CwmsClassEditorIf::EditValidationClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        QTreeWidgetItem* pqtwItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwValidations);

        if (pqtwItem)
        {
            QString qstrName = pqtwItem->text(0);

            CdmClassValidator* pValidator = m_rpCdmClass->FindValidation(qstrName);

            if (CHKPTR(pValidator))
            {
                CwmsClassValidationEditor::EditValidation(m_rpCdmClass, pValidator, false, this);
                FillValidationDataToTree(pqtwItem, pValidator);
            }
        }
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:51:34 2012----------*
 * @method  CwmsClassEditorIf::DeleteValidationClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:51:34 2012----------*/
void CwmsClassEditorIf::DeleteValidationClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        QTreeWidgetItem* pqtwItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwValidations);

        if (pqtwItem)
        {
            QString qstrName = pqtwItem->text(0);
            m_rpCdmClass->DeleteValidator(qstrName);
            m_rpCdmClass->Commit();
            DELPTR(pqtwItem);
        }
    }
}

void CwmsClassEditorIf::FillFunctions()
{
    m_pqtwMethods->clear();
   QMap<QString, CdmClassMethod*> qmMethods = m_rpCdmClass->GetMethods();

    QMap<QString, CdmClassMethod*>::iterator qmIt = qmMethods.begin();
    QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmMethods.end();
    m_pqtwMethods->clear();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassMethod* pMethod = qmIt.value();

        if (pMethod)
        {
            QTreeWidgetItem* pqtwItem = new QTreeWidgetItem(m_pqtwMethods);
            FillFunctionDataToItem(pqtwItem, pMethod);
        }
    }

    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwMethods);
}

/** +-=---------------------------------------------------------Fr 23. Nov 11:46:09 2012----------*
 * @method  CwmsClassEditorIf::FillFunctionDataToItem        // private                           *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @param   CdmClassMethod* p_pMethod                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 23. Nov 11:46:09 2012----------*/
void CwmsClassEditorIf::FillFunctionDataToItem(QTreeWidgetItem* p_pItem, CdmClassMethod* p_pMethod)
{
    if (CHKPTR(p_pItem) && CHKPTR(p_pMethod))
    {
        p_pItem->setText(0, p_pMethod->GetMethodName());
        p_pItem->setData(0, Qt::UserRole, p_pMethod->GetMethodName());
        p_pItem->setText(1, p_pMethod->GetCallInterface());

        QString qstrAccessText;

        if (p_pMethod->GetAccess() == eDmMemberAccessPrivate)
        {
            qstrAccessText = tr("Privat");
        }
        else if (p_pMethod->GetAccess() == eDmMemberAccessProtected)
        {
            qstrAccessText = tr("Geschützt");
        }
        else
        {
            qstrAccessText = tr("Öffentlich");
        }

        if (p_pMethod->IsStatic())
        {
            qstrAccessText += " " + tr("Statisch");
        }

        p_pItem->setText(2, qstrAccessText);
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:51:59 2012----------*
 * @method  CwmsClassEditorIf::NewFunctionClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:51:59 2012----------*/
void CwmsClassEditorIf::NewFunctionClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        if (m_rpMainWindow)
        {
            m_rpMainWindow->ScriptEnvironmentSlot();
            CwmsScriptingEnvironment* pEnvironment = m_rpMainWindow->GetScriptingEnvironment();

            if (pEnvironment)
            {
                pEnvironment->NewFunction(m_rpCdmClass);
            }

        }
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:52:09 2012----------*
 * @method  CwmsClassEditorIf::EditFunctionClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:52:09 2012----------*/
void CwmsClassEditorIf::EditFunctionClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        QTreeWidgetItem* pqtwItem = GetSelectedFunction();

        if (pqtwItem)
        {
            QString qstrName = pqtwItem->data(0, Qt::UserRole).toString();
            CdmClassMethod* pMethod = m_rpCdmClass->FindMethod(qstrName);

            if (CHKPTR(pMethod))
            {
                if (m_rpMainWindow)
                {
                    m_rpMainWindow->ScriptEnvironmentSlot();
                    CwmsScriptingEnvironment* pEnvironment = m_rpMainWindow->GetScriptingEnvironment();

                    if (pEnvironment)
                    {
                        pEnvironment->OpenObject(pMethod);
                    }

                }
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 12. Nov 14:21:37 2012----------*
 * @method  CwmsClassEditorIf::ExecuteFunctionClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 12. Nov 14:21:37 2012----------*/
void CwmsClassEditorIf::ExecuteFunctionClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        ExecuteFunction(false);
    }
}

/** +-=---------------------------------------------------------Fr 30. Nov 15:05:52 2012----------*
 * @method  CwmsClassEditorIf::DebugClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 15:05:52 2012----------*/
void CwmsClassEditorIf::DebugClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        ExecuteFunction(true);
    }
}

/** +-=---------------------------------------------------------So 2. Dez 11:52:22 2012-----------*
 * @method  CwmsClassEditorIf::ExecuteFunction               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 2. Dez 11:52:22 2012-----------*/
void CwmsClassEditorIf::ExecuteFunction(bool p_bDebugger)
{
    if (CHKPTR(m_rpCdmClass))
    {
        QVariant qvResult;
        QTreeWidgetItem* pqtwItem = GetSelectedFunction();

        if (pqtwItem)
        {
            QString qstrName = pqtwItem->data(0, Qt::UserRole).toString();
            CdmClassMethod* pMethod = m_rpCdmClass->FindMethod(qstrName);

            if (CHKPTR(pMethod))
            {
                if (pMethod->IsStatic())
                {
                    QVariantList qlParameters;

                    if (p_bDebugger)
                    {
                        qvResult = CdmExecutor::DebugFunction(pMethod, nullptr, qlParameters, true, true);
                    }
                    else
                    {
                        qvResult = CdmExecutor::ExecuteFunction(pMethod, nullptr, qlParameters, true, true, false, false);
                    }
                }
                else
                {
                    CdmObjectContainer* pList = CwmsContainerSelectionIf::GetObjectContainer(m_rpCdmClass->GetSchemeId(), m_rpCdmClass->GetId(), this);

                    if (pList)
                    {
                        CdmObject* pObject = CwmsObjectSelectionIf::GetObject(pList, nullptr, this);

                        if (pObject)
                        {
                            QVariantList qlParameters;
                            if (p_bDebugger)
                            {
                                qvResult = CdmExecutor::DebugFunction(pMethod, pObject, qlParameters, true, true);
                            }
                            else
                            {
                                qvResult = CdmExecutor::ExecuteFunction(pMethod, pObject, qlParameters, true, true, false, false);
                            }
                        }
                        else
                        {
                            CdmMessageManager::information(tr("Funktion wird nicht ausgeführt"), tr("Die Funktion kann nicht ausgeführt werden, da kein Objekt gewählt wurde."));
                        }
                    }
                }
            }
        }

        QString qstrResult = qvResult.toString();

        if (qstrResult.isEmpty())
        {
            qstrResult = tr("Kein Ergebnis");
        }

        CdmMessageManager::information(tr("Ergebnis"), tr("Funktion endete mit dem Ergebnis %1").arg(qstrResult));
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 13:52:20 2012----------*
 * @method  CwmsClassEditorIf::DeleteFunctionClickedSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 13:52:20 2012----------*/
void CwmsClassEditorIf::DeleteFunctionClickedSlot()
{
    if (CHKPTR(m_rpCdmClass))
    {
        QTreeWidgetItem* pqtwItem = GetSelectedFunction();

        if (pqtwItem)
        {
            QString qstrName = pqtwItem->data(0, Qt::UserRole).toString();
            m_rpCdmClass->DeleteMethod(qstrName);
            m_rpCdmClass->Commit();
            DELPTR(pqtwItem);
            emit ClassModifiedSignal();
        }
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 14:10:30 2012----------*
 * @method  CwmsClassEditorIf::GetSelectedFunction           // private                           *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 14:10:30 2012----------*/
QTreeWidgetItem* CwmsClassEditorIf::GetSelectedFunction()
{
    QTreeWidgetItem* pItem = nullptr;
    QList<QTreeWidgetItem*> qlItems = m_pqtwMethods->selectedItems();

    if (qlItems.count() > 0)
    {
        pItem = qlItems[0];
    }

    return pItem;
}

void CwmsClassEditorIf::UpdateEventClickedSlot()
{
    m_rpCdmClass->SetIsEventClass(m_pqrbEventClass->isChecked());
    m_rpCdmClass->SetEventSourcingActive(m_pqrbEventSourcing->isChecked());

    if(!m_rpCdmClass->IsEventClass() && m_rpCdmClass->IsEventSourcingActive())
    {
        extractAndSaveEventClassesFromTextEdits();

        m_rpCdmClass->Commit();
        CancelEventClickedSlot();
        m_rpMainWindow->CloseClassRelatedContainerUis(m_rpCdmClass);
        emit ClassModifiedSignal();
    }
    else
    {
        m_rpCdmClass->Commit();
        CancelEventClickedSlot();
        m_rpMainWindow->CloseClassRelatedContainerUis(m_rpCdmClass);
        emit ClassModifiedSignal();
    }
    m_pqteCreateEvents->clear();
    m_pqteDeleteEvents->clear();
    m_pqteUpdateEvents->clear();
}

void CwmsClassEditorIf::CancelEventClickedSlot()
{
    m_pqleCreateEventClass->setEnabled(false);
    m_pqcbCreateEventClass->setEnabled(false);
    m_pqleDeleteEventClass->setEnabled(false);
    m_pqcbDeleteEventClass->setEnabled(false);
    m_pqcbUpdateEventClass->setEnabled(false);
    m_pqleUpdateEventClass->setEnabled(false);

    m_pqteCreateEvents->setReadOnly(true);
    m_pqteDeleteEvents->setReadOnly(true);
    m_pqteUpdateEvents->setReadOnly(true);

    m_pqrbDefault->setEnabled(false);
    m_pqrbEventClass->setEnabled(false);
    m_pqrbEventSourcing->setEnabled(false);

    m_pqpbEditEvent->show();
    m_pqpbCancelEvent->hide();
    m_pqpbUpdateEvent->hide();
    m_bEditMode = false;
}

void CwmsClassEditorIf::EditEventClickedSlot()
{
    m_bEditMode = true;

    m_pqteCreateEvents->setReadOnly(false);
    m_pqteDeleteEvents->setReadOnly(false);
    m_pqteUpdateEvents->setReadOnly(false);

    if(m_rpCdmClass->IsEventSourcingActive())
    {
        m_pqrbDefault->setEnabled(true);
        m_pqrbEventSourcing->setEnabled(true);
        m_pqgbChooseEvents->show();
        prepareEventClassLists();
    }
    else if(m_rpCdmClass->IsEventClass())
    {
        m_pqrbDefault->setEnabled(true);
        m_pqrbEventClass->setEnabled(true);
    }
    else
    {
        m_pqrbDefault->setEnabled(true);
        m_pqrbEventClass->setEnabled(true);
        m_pqrbEventSourcing->setEnabled(true);
    }

    m_pqpbEditEvent->hide();
    m_pqpbCancelEvent->show();
    m_pqpbUpdateEvent->show();
}

void CwmsClassEditorIf::extractAndSaveEventClassesFromTextEdits()
{
    QString qstrCreateEvents = m_pqteCreateEvents->toPlainText();
    QString qstrDeleteEvents = m_pqteDeleteEvents->toPlainText();
    QString qstrUpdateEvents = m_pqteUpdateEvents->toPlainText();

    QStringList qstrlCreateEvents = qstrCreateEvents.split(",");
    QStringList qstrlDeleteEvents = qstrDeleteEvents.split(",");
    QStringList qstrlUpdateEvents = qstrUpdateEvents.split(",");
    qstrlCreateEvents.removeAll(" ");
    qstrlDeleteEvents.removeAll(" ");
    qstrlUpdateEvents.removeAll(" ");
    saveEventsInClass(qstrlCreateEvents, qstrlDeleteEvents, qstrlUpdateEvents);

    QStringList qstrlClassCreateEvent = m_rpCdmClass->getCreateEventClassStringList();
    QStringList qstrlClassDeleteEvent = m_rpCdmClass->getDeleteEventClassStringList();
    QStringList qstrlClassUpdateEvent = m_rpCdmClass->getUpdateEventClassStringList();

    if(qstrlClassCreateEvent.count() > 1)
    {
        copyCreateEventListToCB(qstrlClassCreateEvent);
    }
    else if(qstrlClassCreateEvent.count() == 1)
    {
        copyCreateEventToLE(qstrlClassCreateEvent.at(0));
    }

    if(qstrlClassDeleteEvent.count() > 1)
    {
        copyDeleteEventListToCB(qstrlClassDeleteEvent);
    }
    else if(qstrlClassDeleteEvent.count() == 1)
    {
        copyDeleteEventToLE(qstrlClassDeleteEvent.at(0));
    }

    if(qstrlClassUpdateEvent.count() > 1)
    {
        copyUpdateEventListToCB(qstrlClassUpdateEvent);
    }
    else if(qstrlClassUpdateEvent.count() == 1)
    {
        copyUpdateEventToLE(qstrlClassUpdateEvent.at(0));
    }

}

void CwmsClassEditorIf::saveEventsInClass(QStringList qstrlCreateEvents, QStringList qstrlDeleteEvents, QStringList qstrlUpdateEvents)
{
    QList<CdmClass*> qlTempClass;
    CdmClassManager *pClassManager = m_rpCdmClass->GetClassManager();
    qlTempClass = pClassManager->getEventClassList();
    m_qlCreateEventClasses.append(findCreateEventClasses(qstrlCreateEvents, qlTempClass));
    m_qlDeleteEventClasses.append(findDeleteEventClasses(qstrlDeleteEvents, qlTempClass));
    m_qlUpdateEventClasses.append(findUpdateEventClasses(qstrlUpdateEvents, qlTempClass));

    m_rpCdmClass->SetCreateEventClassList(m_qlCreateEventClasses);
    m_rpCdmClass->SetDeleteEventClassList(m_qlDeleteEventClasses);
    m_rpCdmClass->SetUpdateEventClassList(m_qlUpdateEventClasses);
}

QList<CdmClass*> CwmsClassEditorIf::findCreateEventClasses(QStringList qstrlCreateEvents, QList<CdmClass*> qlEventClasses)
{
    QList<CdmClass*> qlCreateEvents;
    for(int i = 0; i < qlEventClasses.count(); ++i)
    {
        CdmClass *pClass = qlEventClasses.at(i);
        for(int j = 0; j < qstrlCreateEvents.count(); ++j)
        {
            if(qstrlCreateEvents.at(j) == pClass->GetKeyname())
            {
                qlCreateEvents.append(pClass);
            }
        }
    }
    return qlCreateEvents;
}

QList<CdmClass*> CwmsClassEditorIf::findDeleteEventClasses(QStringList qstrlDeleteEvents, QList<CdmClass*> qlEventClasses)
{
    QList<CdmClass*> qlDeleteEvents;
    for(int i = 0; i < qlEventClasses.count(); ++i)
    {
        CdmClass *pClass = qlEventClasses.at(i);
        for(int j = 0; j < qstrlDeleteEvents.count(); ++j)
        {
            if(qstrlDeleteEvents.at(j) == pClass->GetKeyname())
            {
                qlDeleteEvents.append(pClass);
            }
        }
    }
    return qlDeleteEvents;
}

QList<CdmClass*> CwmsClassEditorIf::findUpdateEventClasses(QStringList qstrlUpdateEvents, QList<CdmClass*> qlEventClasses)
{
    QList<CdmClass*> qlUpdateEvents;
    for(int i = 0; i < qlEventClasses.count(); ++i)
    {
        CdmClass *pClass = qlEventClasses.at(i);
        for(int j = 0; j < qstrlUpdateEvents.count(); ++j)
        {
            if(qstrlUpdateEvents.at(j) == pClass->GetKeyname())
            {
                qlUpdateEvents.append(pClass);
            }
        }
    }
    return qlUpdateEvents;
}

void CwmsClassEditorIf::copyCreateEventListToCB(QStringList qstrlCreateEvents)
{
    m_pqcbCreateEventClass->clear();
    if(!qstrlCreateEvents.isEmpty())
    {
        for(int i = 0; i < qstrlCreateEvents.count(); ++i)
        {
            m_pqcbCreateEventClass->insertItem(i, qstrlCreateEvents.at(i));
        }
    }
    else
    {
        ERR("No Create Events to Add.");
    }
    m_pqleCreateEventClass->hide();
    m_pqswWCreateEvent->setCurrentIndex(m_pqswWCreateEvent->currentIndex()+1);
}

void CwmsClassEditorIf::copyDeleteEventListToCB(QStringList qstrlDeleteEvents)
{
    m_pqcbDeleteEventClass->clear();
    if(!qstrlDeleteEvents.isEmpty())
    {
        for(int i = 0; i < qstrlDeleteEvents.count(); ++i)
        {
            m_pqcbDeleteEventClass->insertItem(i, qstrlDeleteEvents.at(i));
        }
    }
    else
    {
        ERR("No Delete Events to Add.");
    }
    m_pqleDeleteEventClass->hide();
    m_pqswWDeleteEvent->setCurrentIndex(m_pqswWDeleteEvent->currentIndex()+1);
}

void CwmsClassEditorIf::copyUpdateEventListToCB(QStringList qstrlUpdateEvents)
{
    m_pqcbUpdateEventClass->clear();
    if(!qstrlUpdateEvents.isEmpty())
    {
        for(int i = 0; i < qstrlUpdateEvents.count(); ++i)
        {
            m_pqcbUpdateEventClass->insertItem(i, qstrlUpdateEvents.at(i));
        }
    }
    else
    {
        ERR("No Update Events to Add.");
    }
    m_pqleUpdateEventClass->hide();
    m_pqswWUpdateEvent->setCurrentIndex(m_pqswWUpdateEvent->currentIndex()+1);
}

void CwmsClassEditorIf::copyCreateEventToLE(QString qstrCreateEvent)
{
    m_pqcbCreateEventClass->hide();
    m_pqleCreateEventClass->setText(qstrCreateEvent);
    m_pqswWCreateEvent->setCurrentIndex(0);
}

void CwmsClassEditorIf::copyDeleteEventToLE(QString qstrlDeleteEvent)
{
    m_pqcbDeleteEventClass->hide();
    m_pqleDeleteEventClass->setText(qstrlDeleteEvent);
    m_pqswWDeleteEvent->setCurrentIndex(0);
}

void CwmsClassEditorIf::copyUpdateEventToLE(QString qstrUpdateEvent)
{
    m_pqcbUpdateEventClass->hide();
    m_pqleUpdateEventClass->setText(qstrUpdateEvent);
    m_pqswWUpdateEvent->setCurrentIndex(0);
}

void CwmsClassEditorIf::prepareEventClassLists()
{
    if(m_rpCdmClass->getCreateEventClassStringList().count() > 1)
    {
        m_pqcbCreateEventClass->setEnabled(true);
    }
    if(m_rpCdmClass->getDeleteEventClassStringList().count() > 1)
    {
        m_pqcbDeleteEventClass->setEnabled(true);
    }
    if(m_rpCdmClass->getUpdateEventClassStringList().count() > 1)
    {
        m_pqcbUpdateEventClass->setEnabled(true);
    }
}

/** +-=---------------------------------------------------------Do 23. Aug 14:10:52 2012----------*
 * @method  CwmsClassEditorIf::GetSelectedValidation         // private                           *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 14:10:52 2012----------*/
QTreeWidgetItem* CwmsClassEditorIf::GetSelectedValidation()
{
    QTreeWidgetItem* pItem = nullptr;
    QList<QTreeWidgetItem*> qlItems = m_pqtwValidations->selectedItems();

    if (qlItems.count() > 0)
    {
        pItem = qlItems[0];
    }

    return pItem;
}

void CwmsClassEditorIf::UpdatePackage()
{
    CdmDataProvider* pManager = m_rpCdmClass->GetDataProvider();

    if (CHKPTR(pManager))
    {
        QString qstrPackage = m_pqcbPackage->currentData().toString();
        CdmLocatedElement* pElement = pManager->GetUriObject(qstrPackage);
        CdmClassManager* pClassManager = m_rpCdmClass->GetClassManager();

        if (CHKPTR(pClassManager))
        {

            if (pElement && pElement->IsPackage())
            {
                pClassManager->MoveClassToPackage(m_rpCdmClass, (CdmPackage*)pElement);
                m_rpCdmClass->SetPackage((CdmPackage*)pElement);
            }
            else
            {
                pClassManager->MoveClassToPackage(m_rpCdmClass, nullptr);
            }
        }
    }
}

void CwmsClassEditorIf::SetMainWindow(CwmsAdminMainWindowIf* p_pMainWindow)
{
    m_rpMainWindow = p_pMainWindow;
}

void CwmsClassEditorIf::CurrentTabChangedSlot(int p_iPos)
{
    if (p_iPos != 0)
    {
        if (m_bEditMode)
        {
            UpdateClickedSlot();
        }
    }
}
