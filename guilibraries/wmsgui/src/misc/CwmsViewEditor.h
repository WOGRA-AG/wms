#ifndef CWMSVIEWEDITOR_H
#define CWMSVIEWEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CwmsView.h"
#include "ui_CwmsViewEditor.h"
#include "wmsgui.h"

#include <CwmsPrintingTemplate.h>

// Forwards


// TypeDefs


/* 
 * This class implements the editor for views
 */
class WMSGUI_API CwmsViewEditor : public QDialog, public Ui::CwmsViewEditorClass
{
    Q_OBJECT

private:
    CwmsView m_cView;
    CwmsPrintingTemplate m_cTemplate;

public:
    CwmsViewEditor(QWidget* p_pqwParent);
    virtual ~CwmsViewEditor();
    void FillDialog(CwmsView p_cCwmsView);
    static void Edit(CwmsView p_cView, bool p_bNew, QWidget* p_pqwParent);
public slots:
    void SelectPrintingTemplateClickedSlot();

private:
    bool Validate();
    void SaveData();
    void FillReport(CdmObject *p_pCdmObject);


private slots:
    void OKClickedSlot();
    void ShowResultClickedSlot();
    void CurrentTabChangedSlot();
    void CheckClickedSlot();

};

#endif // CWMSVIEWEDITOR_H
