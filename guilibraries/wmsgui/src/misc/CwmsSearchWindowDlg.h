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
#include "CdmQueryEnhanced.h"
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
   /** +-=---------------------------------------------------------Di 18. Sep 10:21:33 2012-------*
    * @method  CwmsSearchWindowDlg::CwmsSearchWindowDlg      // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:21:33 2012----------*/
    CwmsSearchWindowDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 18. Sep 10:21:43 2012-------*
    * @method  CwmsSearchWindowDlg::~CwmsSearchWindowDlg     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsSearchWindow                                           *
    *----------------last changed: -----------------------------Di 18. Sep 10:21:43 2012----------*/
    virtual ~CwmsSearchWindowDlg( );

   public:
   /** +-=---------------------------------------------------------Di 18. Sep 10:21:53 2012-------*
    * @method  CwmsSearchWindowDlg::AddSearchMember          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrSearchMember                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:21:53 2012----------*/
    void AddSearchMember(QString p_qstrSearchMember);

   public:
   /** +-=---------------------------------------------------------Di 18. Sep 10:22:52 2012-------*
    * @method  CwmsSearchWindowDlg::FillDialog               // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 10:22:52 2012----------*/
    void FillDialog(CdmObjectContainer* p_pContainer);

    static CdmObject* FindObject(CdmObjectContainer* p_pContainer, QWidget *parent);
    void AddResultMembers(QString p_qstrMember);
    void SetPrintVisibility(bool p_bVisible);
    void SetExportVisibility(bool p_bVisible);
    void SetImportVisibility(bool p_bVisible);
    void SetDeleteVisibility(bool p_bVisible);
    void SetEditVisibility(bool p_bVisible);
    static QList<CdmObject *> FindObjects(CdmObjectContainer *p_pContainer, QWidget *parent);
};

#endif // CWMSSEARCHWINDOW_H
