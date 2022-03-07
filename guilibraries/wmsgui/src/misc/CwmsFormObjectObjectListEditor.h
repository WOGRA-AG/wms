/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFormObjectObjectListEditor.h
 ** Started Implementation: 2012/09/11
 ** Description:
 ** 
 ** implements the editor for object objectlist forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSFORMOBJECTOBJECTLISTEDITOR_H
#define CWMSFORMOBJECTOBJECTLISTEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CwmsFormObjectObjectList.h"
#include "CwmsFormStandardObjectListEditor.h"
#include "wmsgui.h"

// Forwards


// TypeDefs


/* 
 * This class implements the editor for object objectlist forms
 */
class WMSGUI_API CwmsFormObjectContainerEditor : public CwmsFormStandardContainerEditor
{
   Q_OBJECT

   private:
      CwmsFormObjectContainer m_cForm;


   public:
   /** +-=---------------------------------------------------------Di 11. Sep 15:47:43 2012-------*
    * @method  CwmsFormObjectObjectListEditor::CwmsFormObjectObjectListEditor // public           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 15:47:43 2012----------*/
    CwmsFormObjectContainerEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 11. Sep 15:47:51 2012-------*
    * @method  CwmsFormObjectObjectListEditor::~CwmsFormObjectObjectListEditor // public, virtual *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFormObjectObjectListEditor                             *
    *----------------last changed: -----------------------------Di 11. Sep 15:47:51 2012----------*/
    virtual ~CwmsFormObjectContainerEditor( );

   private:
   /** +-=---------------------------------------------------------Di 11. Sep 15:49:27 2012-------*
    * @method  CwmsFormObjectObjectListEditor::FillDialog    // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsFormObjectObjectList p_cForm              //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 15:49:27 2012----------*/
    void FillDialog(CwmsFormObjectContainer p_cForm, bool p_bNew);



   protected:
   /** +-=---------------------------------------------------------Di 11. Sep 16:01:09 2012-------*
    * @method  CwmsFormObjectObjectListEditor::Validate      // protected                         *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 16:01:09 2012----------*/
    bool Validate();

   protected:
   /** +-=---------------------------------------------------------Di 11. Sep 16:01:26 2012-------*
    * @method  CwmsFormObjectObjectListEditor::SaveData      // protected                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 16:01:26 2012----------*/
    void SaveData();

   public:
   /** +-=---------------------------------------------------------Di 11. Sep 16:03:53 2012-------*
    * @method  CwmsFormObjectObjectListEditor::EditForm      // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsFormObjectObjectList p_cForm              //                                   *
    * @param   bool p_bNew                                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 16:03:53 2012----------*/
    static void EditForm(CwmsFormObjectContainer p_cForm, bool p_bNew, QWidget* p_pqwParent);





   private:
   /** +-=---------------------------------------------------------Di 11. Sep 16:53:39 2012-------*
    * @method  CwmsFormObjectObjectListEditor::FillSelectionMembers // private                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 16:53:39 2012----------*/
    void FillSelectionMembers();
};

#endif // CWMSFORMOBJECTOBJECTLISTEDITOR_H
