/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CbgPrintingTemplateProperties.h
 ** Started Implementation: 2010/11/09
 ** Description:
 ** 
 ** This class implements the ui for editing the template properties
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSPRINTINGTEMPLATEPROPERTIES_H
#define CWMSPRINTINGTEMPLATEPROPERTIES_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// WMS Includes
#include "CdmObject.h"

// Own Includes
#include "wmsgui.h"
#include "CwmsPrintingTemplate.h"
#include "ui_CwmsPrintingTemplateProperties.h"


// Forwards
class CdmClass;

// Enumerations

/* 
 * This class implements the ui for editing the template properties
 */
class WMSGUI_API CwmsPrintingTemplateProperties : public QDialog, public Ui::CwmsPrintingTemplatePropertiesClass
{
   Q_OBJECT

   private:
      CwmsPrintingTemplate m_cCwmsTemplate;
      CdmClass* m_rpCdmClass;


   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 13:50:48 2012-------*
    * @method  CwmsPrintingTemplateProperties::CwmsPrintingTemplateProperties // public           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 13:50:48 2012----------*/
    CwmsPrintingTemplateProperties( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 13:50:58 2012-------*
    * @method  CwmsPrintingTemplateProperties::~CwmsPrintingTemplateProperties // public, virtual *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbgPrintingTemplateProperties                              *
    *----------------last changed: -----------------------------Mo 27. Aug 13:50:58 2012----------*/
    virtual ~CwmsPrintingTemplateProperties( );

   private:
   /** +-=---------------------------------------------------------Mo 27. Aug 13:51:32 2012-------*
    * @method  CwmsPrintingTemplateProperties::FillDialog    // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsPrintingTemplate p_cCwmsTemplate          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 13:51:32 2012----------*/
    void FillDialog(CwmsPrintingTemplate p_cCwmsTemplate);

   private:
   /** +-=---------------------------------------------------------Mo 27. Aug 13:52:54 2012-------*
    * @method  CwmsPrintingTemplateProperties::FillLanguages // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 13:52:54 2012----------*/
    void FillLanguages();

   private:
   /** +-=---------------------------------------------------------Mo 27. Aug 13:52:59 2012-------*
    * @method  CwmsPrintingTemplateProperties::SaveData      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 13:52:59 2012----------*/
    void SaveData();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 13:53:04 2012-------*
    * @method  CwmsPrintingTemplateProperties::EditProperties // public, static                   *
    * @return  void                                          //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 13:53:04 2012----------*/
    static void EditProperties(QWidget* p_pqwParent, CdmObject* p_pCdmObject, bool p_bNew);

    private slots:
   /** +-=---------------------------------------------------------Mo 27. Aug 16:33:09 2012-------*
    * @method  CwmsPrintingTemplateProperties::OKClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 16:33:09 2012----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 27. Aug 16:34:17 2012-------*
    * @method  CwmsPrintingTemplateProperties::Validate      // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 16:34:17 2012----------*/
    bool Validate();

    private slots:
   /** +-=---------------------------------------------------------Mo 27. Aug 16:38:39 2012-------*
    * @method  CwmsPrintingTemplateProperties::SelectClassClickedSlot // private, slots           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 16:38:39 2012----------*/
void SelectClassClickedSlot( );
};

#endif //
