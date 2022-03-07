/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: CwmsClassSelectionIf.h
 ** Started Implementation: 2008/05/19
 ** Description:
 ** 
 ** the gui of the class selection
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

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
   /** +-=---------------------------------------------------------Mi 5. Sep 15:22:49 2012--------*
    * @method  CwmsClassSelectionIf::CwmsClassSelectionIf    // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 15:22:49 2012-----------*/
    CwmsClassSelectionIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Mo 19. Mai 20:25:09 2008-------*
    * @method  CwmsClassSelectionIf::~CwmsClassSelectionIf   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsClassSelectionIf                                       *
    *----------------last changed: -----------------------------Mo 19. Mai 20:25:09 2008----------*/
    virtual ~CwmsClassSelectionIf( );

   public:
   /** +-=---------------------------------------------------------So 30. Dez 11:31:21 2012-------*
    * @method  CwmsClassSelectionIf::FillDialog              // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 11:31:21 2012----------*/
    void FillDialog(bool p_bShowAbstractClasses);

   public:
   /** +-=---------------------------------------------------------Mo 19. Mai 20:30:46 2008-------*
    * @method  CwmsClassSelectionIf::GetSelectedClass        // public                            *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 20:30:46 2008----------*/
   qint64 GetSelectedClass();

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 18:25:35 2012--------*
    * @method  CwmsClassSelectionIf::GetClass                // public, static                    *
    * @return  CdmClass*                                     //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 18:25:35 2012-----------*/
   static CdmClass* GetClass(QWidget* p_pqwParent, bool p_bShowAbstractClasses = true);


private slots:
   /** +-=---------------------------------------------------------So 30. Dez 11:41:16 2012-------*
    * @method  CwmsClassSelectionIf::ShowTechnicalClassesClickedSlot // private, slots            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 11:41:16 2012----------*/
   void ShowTechnicalClassesClickedSlot( );
};

#endif //
