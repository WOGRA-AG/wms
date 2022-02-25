#ifndef CWMSCLASSEDITORIF_H
#define CWMSCLASSEDITORIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>
#include <QStringList>

// own Includes
#include "ui_CwmsClassEditor.h"


// forwards
class CdmClassMethod;
class CdmClass;
class CwmsAdminMainWindowIf;
class QListWidgetItem;
class QTreeWidgetItem;
class CdmClassValidator;
class CdmPackage;


class CwmsClassEditorIf : public QWidget, public Ui::CwmsClassEditor
{
    Q_OBJECT

private:
    CdmClass* m_rpCdmClass;
    CwmsAdminMainWindowIf* m_rpMainWindow;
    bool m_bEditMode;
    QList<CdmClass *> m_qlCreateEventClasses;
    QList<CdmClass *> m_qlDeleteEventClasses;
    QList<CdmClass *> m_qlUpdateEventClasses;

public:
    CwmsClassEditorIf( CdmClass* p_pCdmClass, QWidget* parent = NULL);
    virtual ~CwmsClassEditorIf( );
    void FillMembers();
    QTreeWidgetItem* GetSelectedGroupItem();
    void SetMainWindow(CwmsAdminMainWindowIf *p_pMainWindow);
    void FillFunctions();

private:
    void FillDialog();
    void FillBaseClasses();
    void FillBaseData();
    void ExecuteFunction(bool p_bDebugger);
    void FillPackageData();
    void FillPackageComboBox(CdmPackage *p_pPackage);
    void prepareEventClassLists();
    void setEventClassLists();
    void FillCUDEvents();
    QList<CdmClass*> getEventClasses();
    QList<CdmClass*> getCreateEventClasses();
    QList<CdmClass*> getDeleteEventClasses();
    QList<CdmClass*> getUpdateEventClasses();
    void FillCreateEvent();
    void FillDeleteEvent();
    void FillUpdateEvent();
    void extractAndSaveEventClassesFromTextEdits();
    void copyCreateEventListToCB(QStringList qstrlCreateEvents);
    void copyDeleteEventListToCB(QStringList qstrlDeleteEvents);
    void copyUpdateEventListToCB(QStringList qstrlUpdateEvents);
    void saveEventsInClass(QStringList qstrlCreateEvents, QStringList qstrlDeleteEvents, QStringList qstrlUpdateEvents);
    QList<CdmClass*> findCreateEventClasses(QStringList qstrlCreateEvents, QList<CdmClass*> qlEventClasses);
    QList<CdmClass*> findDeleteEventClasses(QStringList qstrlDeleteEvents, QList<CdmClass*> qlEventClasses);
    QList<CdmClass*> findUpdateEventClasses(QStringList qstrlUpdateEvents, QList<CdmClass*> qlEventClasses);
    void copyCreateEventToLE(QString qstrCreateEvent);
    void copyDeleteEventToLE(QString qstrDeleteEvent);
    void copyUpdateEventToLE(QString qstrUpdateEvent);
    QTreeWidgetItem* GetSelectedMemberItem();
    void FillGroups(int p_iSelectedId = -1);
    void FillValidations();
    QTreeWidgetItem* GetSelectedFunction();
    QTreeWidgetItem* GetSelectedValidation();
    void FillFunctionDataToItem(QTreeWidgetItem* p_pItem, CdmClassMethod* p_pMethod);
    void FillValidationDataToTree(QTreeWidgetItem* p_pItem, CdmClassValidator* p_pValidation);

private slots:
    void CancelClickedSlot( );
    void EditClickedSlot( );
    void UpdateClickedSlot( );
    void UpdatePackage();
    void AddBaseClassClickedSlot( );
    void RemoveBaseClassClickedSlot( );
    void AddMemberClickedSlot( );
    void EditMemberClickedSlot( );
    void DeleteMemberClickedSlot( );
    QListWidgetItem* GetSelectedBaseClassItem();
    void NewGroupClickedSlot( );
    void EditGroupClickedSlot( );
    void DeleteGroupClickedSlot( );
    void MoveGroupUpClickedSlot( );
    void MoveGroupDownClickedSlot( );
    void SequenceClickedSlot( );
    void NewValidationClickedSlot( );
    void EditValidationClickedSlot( );
    void DeleteValidationClickedSlot( );
    void NewFunctionClickedSlot( );
    void EditFunctionClickedSlot( );
    void DeleteFunctionClickedSlot( );
    void ExecuteFunctionClickedSlot( );
    void DebugClickedSlot( );
    void CurrentTabChangedSlot(int p_iPos);
    void CancelEventClickedSlot();
    void UpdateEventClickedSlot();
    void EditEventClickedSlot();

    void OpenBaseClassClickedSlot();
signals:
    void ClassModifiedSignal();
};

#endif



