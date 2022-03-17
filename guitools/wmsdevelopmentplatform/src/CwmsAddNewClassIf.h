#ifndef CWMSADDNEWCLASSIF_H
#define CWMSADDNEWCLASSIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_cwmsaddnewclass.h"


// Forwards


// Enumerations

/* 
 * This class implements the class creation dlg
 */
class CwmsAddNewClassIf : public QDialog, public Ui::CwmsAddNewClass
{
    Q_OBJECT

public:
    CwmsAddNewClassIf( QWidget* parent = NULL);
    virtual ~CwmsAddNewClassIf( );

private:
    bool Validate();

private slots:
    void OKClickedSlot( );
    void CancelClickedSlot( );

};

#endif //

