#ifndef CWMSUIEDITOR_H
#define CWMSUIEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QWidget>
#include <QFileSystemWatcher>
#include <QProcess>

// WMS Includes
#include "CwmsFormUserDefined.h"

// own Includes
#include "IwmsSciprtEditor.h"
#include "ui_CwmsUIEditor.h"
#include "wmsgui.h"

// Forwards
class QQuickView;
class CdmObject;
class CdmObjectContainer;
class QTreeWidgetItem;

// TypeDefs

// enums

class WMSGUI_API CwmsUIEditor : public QWidget, public Ui::CwmsUIEditor, public IwmsScriptEditor
{
    Q_OBJECT

private:
    CwmsFormUserDefined m_Form;
    QFileSystemWatcher m_FileWatcher;
    QString m_qstrOriginalCode;
    QTreeWidgetItem * m_rpItem;
    QString m_qstrXml;
    QString m_qstrFilename;
    QProcess m_Process;


public:
    CwmsUIEditor(QWidget* p_pParent);
    virtual ~CwmsUIEditor();
    void FillDialog(CwmsFormUserDefined p_Form);
    virtual bool Save();
    virtual void Revert();
    virtual void SetItem(QTreeWidgetItem*);
    virtual bool IsModified();

    virtual void Debug();
    virtual void Execute();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    bool Validate();

    QString GenerateEmptyTemplate(QString qstrName);
    CdmObjectContainer *GetFormContainer();
    CdmObject *GetFormObject();
private slots:
    void SelectClassClickedSlot();
    void OpenInExternalEditorSlot();
    void FileChangedSlot(QString p_qstrFile);
    void PreviewClickedSlot();
    void SaveClickedSlot();
    void RemoveClassClickedSlot();
    void ProcessFinishedSlot();
};

#endif //

