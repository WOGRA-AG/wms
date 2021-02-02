/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWOBJECTLISTREF_H
#define COEDTWOBJECTLISTREF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QPushButton;
class CwmsObjectListEditorWidgetIf;


class CoedtwContainerRef : public CoeValueWidget
{
   Q_OBJECT

   private:
      QLineEdit* m_pqleEdit;
      QPushButton* m_pqpbChange;
      QPushButton* m_pqpbClear;
      QPushButton* m_pqpbView;
      CwmsObjectListEditorWidgetIf* m_pObjectListEditor;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:00:02 2012-------*
    * @method  CoedtwContainerRef::CoedtwContainerRef      // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:00:02 2012----------*/
    CoedtwContainerRef( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwContainerRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:47:52 2003--------*
    * @method  CoedtwContainerRef::~CoedtwContainerRef     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Mon Dec 8 16:47:52 2003-------*/
   public:
      virtual ~CoedtwContainerRef(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:37:10 2012-------*
    * @method  CoedtwContainerRef::GetEditWidget            // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:37:10 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);
   protected slots:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:46:29 2012--------*
    * @method  CoedtwContainerRef::SetValue                 // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Mo 5. Nov 11:46:29 2012-----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);

   /** +-=---------------------------------------------------------Wed Dec 10 16:52:30 2003-------*
    * @method  CoedtwContainerRef::ValueChangedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:52:30 2003------*/
    void setEventClassValue();
private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Thu Dec 11 13:14:43 2003-------*
    * @method  CoedtwContainerRef::ChangeClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wan to change the objectlistref.              *
    *---------------------------------------------------------------Thu Dec 11 13:14:43 2003------*/
    private slots:
void ChangeClickedSlot(  );
    private slots:
   /** +-=---------------------------------------------------------So 8. Jan 12:36:35 2006*
    * @method  CoedtwContainerRef::EditClickedSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to view the obejctlist.                 *
    *----------------last changed: Wolfgang Graßhof-------------So 8. Jan 12:36:35 2006-----------*/
void EditClickedSlot(  );

   /** +-=---------------------------------------------------------Fri Dec 12 10:35:57 2003-------*
    * @method  CoedtwContainerRef::SetReadOnly              // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:35:57 2003------*/
void ClearClickedSlot();
public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();
   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:36:28 2012--------*
    * @method  CoedtwContainerRef::GetTabEditWidget         // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:36:28 2012-----------*/
virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);

};

#endif //
