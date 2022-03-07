#ifndef CWMSFORMVIEWEDITOR_H
#define CWMSFORMVIEWEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "CwmsView.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsFormView.h"
#include "ui_CwmsFormViewEditor.h"

// Forwards


// TypeDefs


/* 
 * This class implements the editor for view forms
 */
class WMSGUI_API CwmsFormViewEditor : public QDialog, public Ui::CwmsFormViewEditorClass
{
    Q_OBJECT

private:
    CwmsFormView m_cForm;
    CwmsPrintingTemplate m_cTemplate;

public:
    CwmsFormViewEditor(QWidget* p_pqwParent);
    virtual ~CwmsFormViewEditor();
    static void EditForm(CwmsFormView p_cForm, bool p_bNew, QWidget* p_pqwParent);

private:
    void FillViews();
    void FillReport(CdmObject* p_pCdmObject);
    void FillDialog(CwmsFormView p_cForm, bool p_bNew);
    bool Validate();
    void SaveData();

private slots:
    void OKClickedSlot();
    void AddViewClickedSlot();
    void RemoveViewClickedSlot();
    void ViewDownClickedSlot();
    void ViewUpClickedSlot();
    void SelectPrintingTemplateClickedSlot();

};

#endif // CWMSFORMVIEWEDITOR_H
