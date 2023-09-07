/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsSearchWindow.h
 ** Started Implementation: 2012/09/06
 ** Description:
 ** 
 ** implements the dlg for generic search
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSEARCHWINDOWDLG_H
#define CWMSSEARCHWINDOWDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryModel.h"

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsSearchWindowDlg.h"

// Forwards
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the user for generic search
 */
class WMSGUI_API CwmsSearchWindowDlg : public QDialog, public Ui::CwmsSearchWindowDlgClass
{
   Q_OBJECT


   public:
    CwmsSearchWindowDlg( QWidget* p_pqwParent);
    virtual ~CwmsSearchWindowDlg( );
    void AddSearchMember(QString p_qstrSearchMember);
    void FillDialog(CdmObjectContainer* p_pContainer);
    void AddResultMembers(QString p_qstrMember);
    void SetPrintVisibility(bool p_bVisible);
    void SetExportVisibility(bool p_bVisible);
    void SetImportVisibility(bool p_bVisible);
    void SetDeleteVisibility(bool p_bVisible);
    void SetEditVisibility(bool p_bVisible);

    static QList<CdmObject *> FindObjects(CdmObjectContainer *p_pContainer, QWidget *parent);
    static CdmObject *FindObject(CdmClass *p_pClass, QWidget *parent);
    static CdmObject* FindObject(CdmObjectContainer* p_pContainer, QWidget *parent);
    void FillDialog(CdmClass *p_pClass);
};

#endif // CWMSSEARCHWINDOW_H
