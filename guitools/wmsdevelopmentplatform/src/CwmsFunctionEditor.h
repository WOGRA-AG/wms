#ifndef CWMSFUNCTIONEDITOR_H
#define CWMSFUNCTIONEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>

// WMS GUI Incldues
#include "IwmsSciprtEditor.h"

// Own Includes
#include "ui_CwmsFunctionEditor.h"


// Forwards
class CdmClassMethod;
class CdmClass;
class QTreeWidgetItem;

// TypeDefs


/* 
 * This class implements the function editor
 */
class CwmsFunctionEditor : public QWidget, public Ui::CwmsFunctionEditorClass, public IwmsScriptEditor
{
    Q_OBJECT

private:
    CdmClassMethod* m_rpCdmFunction;
    CdmClass* m_rpCdmClass;
    QByteArray m_qbaIcon;
    QTreeWidgetItem* m_rpItem;
    bool m_bModified;

public:
    CwmsFunctionEditor( QWidget* p_pqwParent);
    virtual ~CwmsFunctionEditor( );
    void FillDialog(CdmClassMethod* p_pMethod);
    void FillDialog(CdmClassMethod* p_pMethod, CdmClass* p_pCdmClass, bool p_bNew);
    virtual bool Save();
    virtual void Revert();
    virtual void SetItem(QTreeWidgetItem*);
    virtual bool IsModified();
    virtual void Debug();
    virtual void Execute();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    void FillParameters();
    void AddTypesToTypeBox();
    bool Validate();
    bool SaveData();
    void AddClassesToComboBox();
    void AddTypesToTypeBox(QComboBox *p_pComboBox);
    void ExecuteFunction(bool p_bDebugger);
    bool Find(QTextDocument::FindFlags flag);
    void SetParameterSelected(QString p_qstrName);

private slots:
    void DeleteParameterClickedSlot();
    void MoveParameterDownClickedSlot();
    void MoveParameterUpClickedSlot();
    void EnlargeCodeViewClickedSlot();
    void RightsClickedSlot();
    void SelectIconClickedSlot();
    void SyntaxCheckClickedSlot();
    void AddParameterClickedSlot();
    void TypeIndexChangedSlot();
    void ReplaceAllClickedSlot();
    void ReplaceClickedSlot();
    void FindPreviousClickedSlot();
    void FindNextClickedSlot();
    void SaveClickedSlot();
    void ExecuteClickedSlot();
    void DebugClickedSlot();
};

#endif // CWMSFUNCTIONEDITOR_H
