/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSGUIOBJECTLISTOVERVIEWIF_H
#define CWMSGUIOBJECTLISTOVERVIEWIF_H


// System and QT Includes
#include <QDialog>

// own Includes
#include "wmsgui.h"
#include "CdmModelElement.h"
#include "ui_cwmsguiobjecteditor.h"
#include "IdmEventStoreManager.h"

// defines
#ifndef NEW
#define NEW "new"
#endif

#ifndef DELETE
#define DELETE "delete"
#endif

#ifndef UPDATE
#define UPDATE "update"
#endif

// forwards
class CdmObject;
class CwmsguiValidator;

class WMSGUI_API CwmsguiObjectEditorIf : public QDialog, public Ui::CwmsguiObjectEditor
{
   Q_OBJECT

   private:
      CwmsguiValidator* m_rpCwmsValidator;
      CdmObject* m_rpCdmObject;
      QString m_qstrObjectEventMode;

      int workOffEvents();
      void IterateOverSubscribersAndExecuteFunction(QList<CdmClassMethod *> ql_Subscribers, QVariantList qvlParameters);
      QVariantList saveEventAndReturnJSFunctionParameters(IdmEventStoreManager *p_EventStoreManager, CdmObject *p_EventObject);
      CdmObjectContainer *findValueObjectContainer();
      CdmObjectContainer *getValueObjectContainer();
public:
   /** +-=---------------------------------------------------------Di 28. Sep 08:14:33 2010-------*
    * @method  CwmsguiObjectEditorIf::CwmsguiObjectEditorIf  // public                            *
    * @return                                                //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 08:14:33 2010----------*/
    CwmsguiObjectEditorIf( CdmObject* p_pCdmObject, QWidget* parent = NULL);

   /** +-=---------------------------------------------------------Tue Dec 16 10:43:15 2003-------*
    * @method  CwmsguiObjectEditorIf::~CwmsguiObjectEditorIf // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsguiObjectEditorIf                                      *
    *                                                                                             *
    *---------------------------------------------------------------Tue Dec 16 10:43:15 2003------*/
   public:
      virtual ~CwmsguiObjectEditorIf(  );
   public:
   /** +-=---------------------------------------------------------Di 17. Jan 21:53:23 2006*
    * @method  CwmsguiObjectEditorIf::FillDialog             // public                            *
    * @return  void                                          //                                   *
    * @comment Shows the Dialog.                                                                  *
    *----------------last changed: Wolfgang Graßhof-------------Di 17. Jan 21:53:23 2006----------*/
void FillDialog(  );
void FillEventDialog();
    protected slots:
   /** +-=---------------------------------------------------------Di 16. Mrz 08:24:18 2010-------*
    * @method  CwmsguiObjectEditorIf::OKClickedSlot          // protected, slots                  *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the close button was clicked. it closes the            *
    *          ObjectEditor Dialog.                                                               *
    *----------------last changed: -----------------------------Di 16. Mrz 08:24:18 2010----------*/
void OKClickedSlot( );

public:
   /** +-=---------------------------------------------------------Do 19. Jan 20:12:02 2006*
    * @method  CwmsguiObjectEditorIf::AddHiddenValue         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method adds an hidden value to the objecteditor.                              *
    *----------------last changed: Wolfgang Graßhof-------------Do 19. Jan 20:12:02 2006----------*/
void AddHiddenValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Do 19. Jan 20:12:36 2006*
    * @method  CwmsguiObjectEditorIf::AddReadOnlyValue       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method adds an readonly value to the obejcteditor.                            *
    *----------------last changed: Wolfgang Graßhof-------------Do 19. Jan 20:12:36 2006----------*/
void AddReadOnlyValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Fr 20. Jan 23:41:48 2006*
    * @method  CwmsguiObjectEditorIf::AddObjectRefData       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrObjectList                      //                                   *
    * @param   QString p_qstrDisplayValue                    //                                   *
    * @comment Adds the object reference data.                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 20. Jan 23:41:48 2006----------*/
void AddObjectRefData(  QString p_qstrValue, QString p_qstrObjectList, QString p_qstrDisplayValue );

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 16:26:44 2012--------*
    * @method  CwmsguiObjectEditorIf::SetDisplayType         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   EdmStringDisplayType p_eOeDisplayType         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 16:26:44 2012-----------*/
    void SetDisplayType(QString p_qstrValue, EdmStringDisplayType p_eOeDisplayType);


   public:
   /** +-=---------------------------------------------------------Do 23. Feb 13:41:41 2006-------*
    * @method  CwmsguiObjectEditorIf::SetValidator           // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsguiValidator* p_pCwmsguiValidator         //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Do 23. Feb 13:41:41 2006----------*/
    void SetValidator(CwmsguiValidator* p_pCwmsguiValidator);

   public:
   /** +-=---------------------------------------------------------So 25. Jun 14:40:02 2006-------*
    * @method  CwmsguiObjectEditorIf::SetSortedList          // public                            *
    * @return  void                                          //                                   *
    * @param   QStringList p_qstrlSorting                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 25. Jun 14:40:02 2006----------*/
    void SetSortedList(QStringList p_qstrlSorting);

   public:
   /** +-=---------------------------------------------------------Di 8. Mai 21:02:24 2007--------*
    * @method  CwmsguiObjectEditorIf::SetCaptionValue        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment Over this method you can set, from which value the objectcaption will be           *
    *          autmatically copied.                                                               *
    *----------------last changed: Wolfgang Graßhof-------------Di 8. Mai 21:02:24 2007-----------*/
    void SetCaptionValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Do 4. Okt 08:40:12 2012--------*
    * @method  CwmsguiObjectEditorIf::AddProxy               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmEnhancedQueryProxy* p_pCwmsProxy           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 4. Okt 08:40:12 2012-----------*/
    void AddProxy(QString p_qstrKeyname, CdmEnhancedQueryProxy* p_pCwmsProxy);

   public:
   /** +-=---------------------------------------------------------Do 14. Jul 14:16:39 2011-------*
    * @method  CwmsguiObjectEditorIf::SetReadOnly            // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Jul 14:16:39 2011----------*/
    void SetReadOnly();

   public:
   /** +-=---------------------------------------------------------Fr 14. Dez 14:50:43 2012-------*
    * @method  CwmsguiObjectEditorIf::SetFormConfiguration   // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pObject                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 14:50:43 2012----------*/
    void SetFormConfiguration(CdmObject* p_pObject);
    void SetObjectEventMode(QString qstr_EventMode);
    QString GetObjectEventMode() const;
};

#endif //
