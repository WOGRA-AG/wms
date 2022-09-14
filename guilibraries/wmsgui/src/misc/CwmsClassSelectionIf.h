#ifndef CWMSCLASSSELECTIONIF_H
#define CWMSCLASSSELECTIONIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>


// Own Includes
#include "wmsgui.h"
#include "ui_cwmsclassselectiondlg.h"


// Forwards
class CdmClassManager;
class CdmClass;
class CdmPackage;

// Enumerations

/* 
 * This class implements the gui of the class selection
 */
class WMSGUI_API CwmsClassSelectionIf : public QDialog, public Ui::CwmsClassSelectionDlg
{
   Q_OBJECT

   private:
   bool m_bShowAbstractClasses;
   bool IsTechnicalClass(CdmClass *p_pClass);
   bool IsTechnicalPackage(CdmPackage *p_pPackage);

public:
    CwmsClassSelectionIf( QWidget* parent = NULL);
    virtual ~CwmsClassSelectionIf( );
    void FillDialog(bool p_bShowAbstractClasses);
   qint64 GetSelectedClass();
   static CdmClass* GetClass(QWidget* p_pqwParent, bool p_bShowAbstractClasses = true);

private slots:
   void ShowTechnicalClassesClickedSlot( );
   void FilterClassesSlot();
};

#endif //
