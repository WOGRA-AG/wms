/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectContainerDataFiller.h
 ** Started Implementation: 2013/09/18
 ** Description:
 ** 
 ** implements the ui for creating new objectlists
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCREATEOBJECTCONTAINERDLG_H
#define CWMSCREATEOBJECTCONTAINERDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <qdialog.h>

// Own Includes
#include "ui_cwmscreatobjectlistdlg.h"

// Forwards
class QWidget;
class CdmClass;
class CdmObjectContainer;

// TypeDefs


class CwmsCreateObjectContainerDlg : public QDialog, public Ui::CwmsCreatObjectListDlgClass
{
   Q_OBJECT

   private:
      CdmClass* m_rpClass;

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 19:34:02 2013-------*
    * @method  CwmsCreateObjectContainerDlg::CreateObjectContainer // public, static              *
    * @return  CdmObjectContainer*                           //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 19:34:02 2013----------*/
    static CdmObjectContainer* CreateObjectContainer(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 19:39:38 2013-------*
    * @method  CwmsCreateObjectContainerDlg::CwmsCreateObjectContainerDlg // public               *
    * @return                                                //                                   *
    * @param   QWidget* p_pParent                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 19:39:38 2013----------*/
    CwmsCreateObjectContainerDlg( QWidget* p_pParent);

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 19:39:57 2013-------*
    * @method  CwmsCreateObjectContainerDlg::~CwmsCreateObjectContainerDlg // public, virtual     *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCreateObjectContainerDlg                               *
    *----------------last changed: -----------------------------Mo 23. Sep 19:39:57 2013----------*/
    virtual ~CwmsCreateObjectContainerDlg( );

public slots:
    void OKClickedSlot();
private slots:
   /** +-=---------------------------------------------------------Mo 23. Sep 19:40:19 2013-------*
    * @method  CwmsCreateObjectContainerDlg::SelectClassClickedSlot // private, slots             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 19:40:19 2013----------*/
void SelectClassClickedSlot( );
};

#endif //
