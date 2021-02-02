/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectListPropertiesDlg.h
 ** Started Implementation: 2012/12/13
 ** Description:
 ** 
 ** Implements the editor for objectlistproperties
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

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
   /** +-=---------------------------------------------------------Do 13. Dez 15:02:40 2012-------*
    * @method  CwmsObjectListPropertiesDlg::CwmsObjectListPropertiesDlg // public                 *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:02:40 2012----------*/
    CwmsContainerPropertiesDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 13. Dez 15:07:14 2012-------*
    * @method  CwmsObjectListPropertiesDlg::~CwmsObjectListPropertiesDlg // public, virtual       *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectListPropertiesDlg                                *
    *----------------last changed: -----------------------------Do 13. Dez 15:07:14 2012----------*/
    virtual ~CwmsContainerPropertiesDlg( );

   public:
   /** +-=---------------------------------------------------------Do 13. Dez 15:07:54 2012-------*
    * @method  CwmsObjectListPropertiesDlg::FillDialog       // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:07:54 2012----------*/
    void FillDialog(CdmObjectContainer* p_pList);

    private slots:
   /** +-=---------------------------------------------------------Do 13. Dez 15:08:03 2012-------*
    * @method  CwmsObjectListPropertiesDlg::OKClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:08:03 2012----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 13. Dez 15:08:15 2012-------*
    * @method  CwmsObjectListPropertiesDlg::Validate         // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:08:15 2012----------*/
    bool Validate();

   private:
   /** +-=---------------------------------------------------------Do 13. Dez 15:08:34 2012-------*
    * @method  CwmsObjectListPropertiesDlg::Save             // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:08:34 2012----------*/
    bool Save();

    private slots:
   /** +-=---------------------------------------------------------Do 13. Dez 15:33:59 2012-------*
    * @method  CwmsObjectListPropertiesDlg::RightsClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:33:59 2012----------*/
void RightsClickedSlot( );
};

#endif // CWMSOBJECTLISTPROPERTIESDLG_H
