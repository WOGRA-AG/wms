/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsguiObjectEditorSelector.h
 ** Started Implementation: 2011/07/14
 ** Description:
 ** 
 ** this class choses the right editor for editing a given object.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSGUIOBJECTEDITORSELECTOR_H
#define CWMSGUIOBJECTEDITORSELECTOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "wmsgui.h"

// Forwards
class IwmsObjectEditorDescriptor;
class IwmsObjectListEditorDescriptor;

// Enumerations
enum EwmsGuiDisplayMode
{
   eWmsGuiDisplayModeNew,
   eWmsGuiDisplayModeWrite,
   eWmsGuiDisplayModeRead
};

//defs
#define WMS_NEW "newObject"
#define WMS_DELETE "deleteObject"
#define WMS_UPDATE "updateObject"

// TypeDefs


/* 
 * This class implements the choices the right editor for editing a given object.
 */
class WMSGUI_API CwmsguiObjectEditorSelector
{
   private:
      static CwmsguiObjectEditorSelector* m_pSelector;
      QMap<QString, IwmsObjectEditorDescriptor*> m_qmObjectDescriptors;
      QMap<QString, IwmsObjectListEditorDescriptor*> m_qmObjectListDescriptors;

   private:
    CwmsguiObjectEditorSelector();
    virtual ~CwmsguiObjectEditorSelector();

   protected:
   /** +-=---------------------------------------------------------Do 14. Jul 10:58:15 2011-------*
    * @method  CwmsguiObjectEditorSelector::GetSelector      // protected, static                 *
    * @return  CwmsguiObjectEditorSelector*                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 10:58:15 2011----------*/
    static CwmsguiObjectEditorSelector* GetSelector();

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 15:47:57 2011-------*
    * @method  CwmsguiObjectEditorSelector::Create           // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:47:57 2011----------*/
    static bool Create(CdmObject* p_pCdmObject, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 15:49:56 2011-------*
    * @method  CwmsguiObjectEditorSelector::View             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:49:56 2011----------*/
    static bool View(CdmObject* p_pCdmObject, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 15:51:08 2011-------*
    * @method  CwmsguiObjectEditorSelector::Edit             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:51:08 2011----------*/
    static bool Edit(CdmObject* p_pCdmObject, QWidget* p_pqwParent);

   protected:
   /** +-=---------------------------------------------------------Do 14. Jul 15:51:50 2011-------*
    * @method  CwmsguiObjectEditorSelector::DisplayObjectEditor // protected, virtual             *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:51:50 2011----------*/
    virtual bool DisplayObjectEditor(CdmObject* p_pCdmObject,
                                     EwmsGuiDisplayMode p_eDisplayMode,
                                     QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 15:47:22 2011-------*
    * @method  CwmsguiObjectEditorSelector::Create           // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObjectAdaptor& p_CdmObjectAdaptor          //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:47:22 2011----------*/
    static bool Create(CdmObjectAdaptor& p_CdmObjectAdaptor, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 15:49:14 2011-------*
    * @method  CwmsguiObjectEditorSelector::View             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObjectAdaptor p_CdmObjectAdaptor           //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:49:14 2011----------*/
    static bool View(CdmObjectAdaptor p_CdmObjectAdaptor, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 15:50:25 2011-------*
    * @method  CwmsguiObjectEditorSelector::Edit             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObjectAdaptor p_CdmObjectAdaptor           //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 15:50:25 2011----------*/
    static bool Edit(CdmObjectAdaptor p_CdmObjectAdaptor, QWidget* p_pqwParent);





   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 11:19:03 2012-------*
    * @method  CwmsguiObjectEditorSelector::DisplayDefaultObjectEditor // private                 *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 11:19:03 2012----------*/
    bool DisplayDefaultObjectEditor(CdmObject* p_pCdmObject,
                                    EwmsGuiDisplayMode p_eDisplayMode,
                                    QWidget* p_pqwParent);

   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 11:24:58 2012-------*
    * @method  CwmsguiObjectEditorSelector::HasConfiguredObjectEditor // private                  *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 11:24:58 2012----------*/
    bool HasConfiguredObjectEditor(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 11:21:20 2012-------*
    * @method  CwmsguiObjectEditorSelector::DisplayConfiguredObjectEditor // private              *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 11:21:20 2012----------*/
    bool DisplayConfiguredObjectEditor(CdmObject* p_pCdmObject,
                                       EwmsGuiDisplayMode p_eDisplayMode,
                                       QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 17. Dez 10:09:31 2012-------*
    * @method  CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor // public, static       *
    * @return  void                                          //                                   *
    * @param   IwmsObjectEditorDescriptor* p_pDescriptor     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Dez 10:09:31 2012----------*/
    static void InstallObjectEditorDescriptor(IwmsObjectEditorDescriptor* p_pDescriptor);

   public:
   /** +-=---------------------------------------------------------Mo 17. Dez 10:09:02 2012-------*
    * @method  CwmsguiObjectEditorSelector::InstallObjectListEditorDescriptor // public, static   *
    * @return  void                                          //                                   *
    * @param   IwmsObjectListEditorDescriptor* p_pDescriptor//                                    *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Dez 10:09:02 2012----------*/
    static void InstallObjectListEditorDescriptor(IwmsObjectListEditorDescriptor* p_pDescriptor);

   protected:
   /** +-=---------------------------------------------------------Mo 17. Dez 10:12:04 2012-------*
    * @method  CwmsguiObjectEditorSelector::DisplayObjectListEditor // protected, virtual         *
    * @return  bool                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   EwmsGuiDisplayMode p_eDisplayMode             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Dez 10:12:04 2012----------*/
    virtual bool DisplayContainerEditor(CdmObjectContainer* p_pContainer,
                                         EwmsGuiDisplayMode p_eDisplayMode,
                                         QWidget* p_pqwParent);

    bool ExistQmlForThisPlattform(const CdmClass* p_pClass);

   public:
   /** +-=---------------------------------------------------------Mo 17. Dez 10:13:48 2012-------*
    * @method  CwmsguiObjectEditorSelector::Edit             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Dez 10:13:48 2012----------*/
    static bool Edit(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 17. Dez 10:14:51 2012-------*
    * @method  CwmsguiObjectEditorSelector::View             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Dez 10:14:51 2012----------*/
    static bool View(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent);

    static void Init();

private:
    bool ShowQmlForm(CdmObject* p_pCdmObject, long p_lObjectId, QWidget* p_pqParent);
    QString GenerateQmlQuery(const CdmClass* p_pClass);
    bool DisplayQmlForm(CdmObject* p_pCdmObject, EwmsGuiDisplayMode p_eDisplayMode, QWidget* p_pqwParent);
};

#endif // CWMSGUIOBJECTEDITORSELECTOR_H
