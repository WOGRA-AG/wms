#ifndef CWMSQMLLIBRARYEDITOR_H
#define CWMSQMLLIBRARYEDITOR_H

// System and Qt Includes
#include <QWidget>
#include <QFileSystemWatcher>


// Basetools Includes
#include "CwmsFormLibrary.h"

// own Includes
#include "IwmsSciprtEditor.h"
#include "ui_CwmsQmlLibraryEditor.h"
#include "wmsgui.h"


class WMSGUI_API CwmsQmlLibraryEditor : public QWidget, public IwmsScriptEditor
{
    Q_OBJECT

private:
    QFileSystemWatcher m_FileWatcher;
    CwmsFormLibrary m_cForm;
    Ui::CwmsQmlLibraryEditorClass *ui;
    QTreeWidgetItem* m_rpItem;

public:
    CwmsQmlLibraryEditor(QWidget *parent = 0);
    ~CwmsQmlLibraryEditor();
    void FillDialog(CwmsFormLibrary p_cForm);

    virtual bool Save();
    virtual void Revert();
    virtual void SetItem(QTreeWidgetItem*);
    virtual bool IsModified();
    virtual void Execute();
    virtual void Debug();
private slots:
    void PreviewClickedSlot();
    void OpenInExternalEditorClickedSlot();

    void FileChangedSlot(QString p_qstrFile);
    void CancelClickedSlot();
    void OKClickedSlot();
private:
    bool Validate();
};

#endif // CWMSQMLLIBRARYEDITOR_H
