/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CbgMandatorSelectionIf.h
 ** Started Implementation: 14.7.2005
 ** Description:
 ** Implements the selection dlg for databases
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/

#ifndef CWMSUSERSCHEMESELECTION_H
#define CWMSUSERSCHEMESELECTION_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes
#include <QDialog>


// WMS Includes


// own Includes
#include "ui_CwmsUserSchemeSelection.h"


class CwmsUserSchemeSelection : public QDialog, public Ui::CwmsUserSchemeSelectionClass
{
    Q_OBJECT

private:
    QString m_qstrScheme;

    QListWidgetItem* GetSelectedItem();

public:
    CwmsUserSchemeSelection( QWidget* parent = NULL);
    virtual ~CwmsUserSchemeSelection( );
    void FillDialog(QLinkedList<QString>& p_rqllDatabases);

    static QString SelectScheme(QLinkedList<QString> &qllSchemes, QWidget *p_pParent);
private slots:
    void ListBoxDoubleClickedSlot( );
    void CancelClickedSlot( );
    void OKClickedSlot( );

};

#endif
