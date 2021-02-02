#ifndef CWMSSCRIPTINGENVIRONMENT_H
#define CWMSSCRIPTINGENVIRONMENT_H

#include <QMainWindow>

namespace Ui {
class CwmsScriptingEnvironmentClass;
}

// forwards
class QTreeWidgetItem;
class QMdiSubWindow;
class CdmLocatedElement;
class CdmClass;
class CdmClassMethod;
class CdmObject;
class CwmsAdminMainWindowIf;

enum EwmsCutCopyMode
{
    eWmsNone,
    eWmsCut,
    eWmsCopy
};

class CwmsScriptingEnvironment : public QMainWindow
{
    Q_OBJECT

public:
    explicit CwmsScriptingEnvironment(QWidget *parent = 0);
    virtual ~CwmsScriptingEnvironment();

    void FillContent();
    void SetAdminMainWindow(CwmsAdminMainWindowIf *p_pMainWindow);
    void OpenObject(CdmLocatedElement *p_pElement);
    void NewFunction(CdmClass *p_pClass);
public slots:
    void ClassesExpandedSlot();
    void UisExpandedSlot();
protected:
    virtual void closeEvent(QCloseEvent *p_pqCloseEvent);
private slots:
    void SaveAllSlot();
    void SaveSlot();
    void NewSlot();
    void InsertSlot();
    void ExecuteSlot();
    void DebugSlot();
    void CutSolt();
    void CopySlot();
    void CloseSlot();
    void EditClicked();
    void EditResourceSlot(QTreeWidgetItem *p_pItem);
    void EditLibrarySlot(QTreeWidgetItem *p_pItem);
    void EditFunctionSlot(QTreeWidgetItem *p_pItem);
    void EditMemberSlot(QTreeWidgetItem *p_pItem);
    void EditFormSlot(QTreeWidgetItem *p_pItem);
    void CloseAllSlot();
    void DeleteSlot();
    void TreeViewSelectionChangedSlot();
    void CustomContextMenuSlot(const QPoint & p_Pos);
    void RefreshSlot();
    void ShowTechnicalClassesChangedSlot();
private:
    Ui::CwmsScriptingEnvironmentClass *ui;
    CdmLocatedElement* m_rpCutCopyElement;
    QTreeWidgetItem* m_rpCurrentItem;
    EwmsCutCopyMode m_eCutCopyMode;
    CwmsAdminMainWindowIf* m_pAdminMainWindow;
    QTreeWidgetItem* m_pFormItem;
    QTreeWidgetItem* m_pLibraryItem;

    void UpdateDockWidgetVisibility();
    void EditSlot(QTreeWidgetItem *p_pItem);
    QMdiSubWindow *AddMdiWindow(QWidget *p_pWidget);
    QMdiSubWindow *FindSubWindowByUri(QString p_qstrUri);
    bool FindAndSetSubWindow(QString p_qstrUri);
    void Save(QMdiSubWindow *p_pSubWindow);
    void DeleteItem(QTreeWidgetItem *p_pItem);
    void DeleteFunctionSlot(QTreeWidgetItem *pqtwMethod);
    void DeleteMemberSlot(QTreeWidgetItem *pqtwMember);
    void DeleteLibrarySlot(QTreeWidgetItem *pCurrent);
    void DeleteResourceSlot(QTreeWidgetItem *pCurrent);
    void DeleteUserDefinedFormSlot(QTreeWidgetItem *pItem);
    void NewItem(QTreeWidgetItem *p_pItem);
    void FillUi();
    void AddContextMenus();
    void NewMember(QTreeWidgetItem *p_pItem);
    void NewFunction(QTreeWidgetItem *p_pItem);
    void NewResource(QTreeWidgetItem *p_pItem);
    void NewForm(QTreeWidgetItem *p_pItem);
    void NewLibrary(QTreeWidgetItem *p_pItem);
    CdmClass *GetClassFromItem(QTreeWidgetItem *p_pItem);
    void FillClasses();
    void EditFormSlot(CdmObject *p_pObject, QTreeWidgetItem* p_pItem);
    void EditFunctionSlot(CdmClassMethod *p_pMethod, QTreeWidgetItem* p_pItem);
    void EditLibrarySlot(CdmObject *p_pObject, QTreeWidgetItem* p_pItem);
    QTreeWidgetItem *FindMethodItem(CdmClassMethod *p_pMethod);
    QTreeWidgetItem *FindFormLibraryItem(CdmObject *p_pObject);
    QTreeWidgetItem *FindFormLibraryItem(CdmObject *p_pObject, QTreeWidgetItem *p_pParent);
    QTreeWidgetItem *FindMethodItem(CdmClassMethod *p_pMethod, QTreeWidgetItem *p_pParent);
    CdmLocatedElement *GetCurrentElement();
    void ClearTreeWidgetAssignments();
    QTreeWidgetItem* CreateItemToObject(CdmObject* p_pObject);
};

#endif // CWMSSCRIPTINGENVIRONMENT_H
