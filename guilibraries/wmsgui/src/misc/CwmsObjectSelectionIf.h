/******************************************************************************
 ** WOGRA Middleware Server GUI Tools Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSOBJECTSELECTIONIF_H
#define CWMSOBJECTSELECTIONIF_H


// System and QT Includes
#include <QDialog>


// WMS Includes
#include "CdmQueryModel.h"

// own Includes

#include "wmsgui.h"
#include "ui_CwmsObjectSelection.h"


// forwards
class CdmEnhancedQueryProxy;



class WMSGUI_API CwmsObjectSelectionIf : public QDialog, public Ui::CwmsObjectSelection
{
   Q_OBJECT

   private:
      QString m_qstrDisplayMember;
      CdmQueryModel m_cModel;

   private:
   /** +-=---------------------------------------------------------So 23. Mai 10:55:30 2010-------*
    * @method  CwmsObjectSelectionIf::CwmsObjectSelectionIf  // private                           *
    * @return  void                                          //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 10:55:30 2010----------*/
    CwmsObjectSelectionIf( QWidget* parent = NULL);

    CdmMember *getReferencedClassMemberForEvent(long lReferencedClassId, CdmClassManager *pClassManager);
public:
   /** +-=---------------------------------------------------------Mo 23. Jan 22:31:53 2006*
    * @method  CwmsObjectSelectionIf::~CwmsObjectSelectionIf // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectSelectionIf                                      *
    *                                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 22:31:53 2006----------*/
virtual ~CwmsObjectSelectionIf(  );

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 22:32:28 2006*
    * @method  CwmsObjectSelectionIf::GetSelectedObject      // public                            *
    * @return  CdmObject*                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 22:32:28 2006----------*/
CdmObject* GetSelectedObject(  );

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 22:33:13 2006*
    * @method  CwmsObjectSelectionIf::SetObjectList          // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 22:33:13 2006----------*/
void SetObjectList(  CdmObjectContainer* p_pContainer );

   public:
   /** +-=---------------------------------------------------------Mi 3. Okt 11:34:31 2012--------*
    * @method  CwmsObjectSelectionIf::GetObject              // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   CdmEnhancedQueryProxy* p_pCwmsProxy           //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @param   QString p_qstrDisplayMember = ""              //                                   *
    * @comment the static implementation for returning an object.                                 *
    *----------------last changed: -----------------------------Mi 3. Okt 11:34:31 2012-----------*/
    static CdmObject* GetObject(CdmObjectContainer* p_pContainer,
                                CdmEnhancedQueryProxy* p_pCwmsProxy,
                                QWidget* p_pqwParent,
                                QString p_qstrDisplayMember = "");

   public:
   /** +-=---------------------------------------------------------Mi 3. Okt 11:28:42 2012--------*
    * @method  CwmsObjectSelectionIf::SetProxy               // public                            *
    * @return  void                                          //                                   *
    * @param   CdmEnhancedQueryProxy* p_pCwmsProxy           //                                   *
    * @comment This method sets the proxy for the dialog.                                         *
    *----------------last changed: -----------------------------Mi 3. Okt 11:28:42 2012-----------*/
    void SetProxy(CdmEnhancedQueryProxy* p_pCwmsProxy);

   public:
   /** +-=---------------------------------------------------------Fr 1. Jun 10:53:38 2012--------*
    * @method  CwmsObjectSelectionIf::GetSelectedObjectId    // public                            *
    * @return  long                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 1. Jun 10:53:38 2012-----------*/
    long GetSelectedObjectId();

   public:
   /** +-=---------------------------------------------------------Mi 3. Okt 11:34:49 2012--------*
    * @method  CwmsObjectSelectionIf::GetObjectId            // public, static                    *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   CdmEnhancedQueryProxy* p_pCwmsProxy           //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment the static implementation for returning an object.                                 *
    *----------------last changed: -----------------------------Mi 3. Okt 11:34:49 2012-----------*/
    static long GetObjectId(CdmObjectContainer* p_pContainer,
                            CdmEnhancedQueryProxy* p_pCwmsProxy,
                            QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 15:32:40 2012--------*
    * @method  CwmsObjectSelectionIf::SetDisplayMember       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 15:32:40 2012-----------*/
    void SetDisplayMember(QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Fr 21. Dez 11:30:40 2012-------*
    * @method  CwmsObjectSelectionIf::SetWql                 // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrWql                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Dez 11:30:40 2012----------*/
    bool SetWql(QString p_qstrWql);

   public:
   /** +-=---------------------------------------------------------Fr 21. Dez 11:33:30 2012-------*
    * @method  CwmsObjectSelectionIf::GetObject              // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   QString p_qstrWql                             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment the static implementation for returning an object.                                 *
    *----------------last changed: -----------------------------Fr 21. Dez 11:33:30 2012----------*/
    static CdmObject* GetObject(QString p_qstrWql, QWidget* p_pqwParent);
};


#endif //
