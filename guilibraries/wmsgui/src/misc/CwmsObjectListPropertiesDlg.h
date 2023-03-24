#ifndef CWMSOBJECTLISTPROPERTIESDLG_H
#define CWMSOBJECTLISTPROPERTIESDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "ui_CwmsObjectListPropertiesDlg.h"


// Forwards
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the Objectlistproperties editor
 */
class WMSGUI_API CwmsContainerPropertiesDlg : public QDialog, public Ui::CwmsObjectListPropertiesDlgClass
{
    Q_OBJECT

private:
    CdmObjectContainer* m_rpList;

public:
    CwmsContainerPropertiesDlg( QWidget* p_pqwParent);
    virtual ~CwmsContainerPropertiesDlg( );
    void FillDialog(CdmObjectContainer* p_pList);

private:
    bool Validate();
    bool Save();

private slots:
    void OKClickedSlot( );
    void RightsClickedSlot( );
};

#endif // CWMSOBJECTLISTPROPERTIESDLG_H
