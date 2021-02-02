/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwObjectRef.h,v 1.8 2006/01/24 23:18:39 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWOBJECTREF_H
#define COEDTWOBJECTREF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QPushButton;
class CdmObjectContainer;
class CwmsObjectChoiceComboBox;
class CdmEnhancedQueryProxy;
class CwmsObjectEditor;


class CoedtwObjectRef : public CoeValueWidget
{
   Q_OBJECT

   private:

    CwmsObjectChoiceComboBox* m_pqcbObjectChoice;
    QPushButton* m_pqpbSelect;
    QPushButton* m_pqpbEdit;
    QPushButton* m_pqpbClear;
    bool m_bProxyCreatedByThis;
    QLineEdit* m_pqleObject;
    bool m_bShowEditButton;
    CdmEnhancedQueryProxy* m_pCwmsProxy;
    CwmsObjectEditor* m_pObjectEditor;
    QString m_qstrObjectList;
    QString m_qstrVisibleKeyname;



    void GetComboBoxEdit(CdmObjectContainer* pContainer, QWidget* pqWidget, QHBoxLayout* pqLayout);

public:
   /** +-=---------------------------------------------------------Mi 22. Aug 10:59:51 2012-------*
    * @method  CoedtwObjectRef::CoedtwObjectRef              // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Destructor of Class CoedtwObjectRef                                            *
    *----------------last changed: -----------------------------Mi 22. Aug 10:59:51 2012----------*/
    CoedtwObjectRef( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwObjectRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:48:21 2003--------*
    * @method  CoedtwObjectRef::~CoedtwObjectRef             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Mon Dec 8 16:48:21 2003-------*/
   public:
      virtual ~CoedtwObjectRef(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:38:48 2012-------*
    * @method  CoedtwObjectRef::GetEditWidget                // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:38:48 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Wed Dec 10 16:50:38 2003-------*
    * @method  CoedtwObjectRef::SetValue                     // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:50:38 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Wed Dec 10 16:52:40 2003-------*
    * @method  CoedtwObjectRef::ValueChangedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:52:40 2003------*/
    void setEventClassValue();
private slots:
void ValueChangedSlotByUser(  );
    private slots:
   /** +-=---------------------------------------------------------Do 19. Jan 20:19:21 2006*
    * @method  CoedtwObjectRef::EditClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to view the obejctlist.                 *
    *----------------last changed: Wolfgang Graßhof-------------Do 19. Jan 20:19:21 2006----------*/
void EditClickedSlot(  );

   /** +-=---------------------------------------------------------Fri Dec 12 10:36:10 2003-------*
    * @method  CoedtwObjectRef::SetReadOnly                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:36:10 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Do 19. Jan 20:43:13 2006*
    * @method  CoedtwObjectRef::SetObjectList                // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrObjectList                      //                                   *
    * @param   QString p_qstrVisibleKeyname                  //                                   *
    * @comment This method sets the objectlist source, in which the user can choose the object for the objectreferenece.*
    *----------------last changed: Wolfgang Graßhof-------------Do 19. Jan 20:43:13 2006----------*/
void SetObjectList(  QString p_qstrObjectList, QString p_qstrVisibleKeyname );

    private slots:
   /** +-=---------------------------------------------------------Mo 23. Jan 22:10:22 2006*
    * @method  CoedtwObjectRef::ChooseClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the choose button was clicked.                         *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 22:10:22 2006----------*/
void ChooseClickedSlot(  );

void ClearClickedSlot();
public:
   /** +-=---------------------------------------------------------Di 24. Jan 21:18:25 2006*
    * @method  CoedtwObjectRef::GetSingleObjectList          // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Di 24. Jan 21:18:25 2006----------*/
CdmObjectContainer* GetSingleObjectList(  );

   public:
   /** +-=---------------------------------------------------------Di 10. Jun 12:40:30 2008-------*
    * @method  CoedtwObjectRef::HideEditButton               // public                            *
    * @return  void                                          //                                   *
    * @comment This method hides the edit button of the objectref.                                *
    *----------------last changed: -----------------------------Di 10. Jun 12:40:30 2008----------*/
    void HideEditButton();

   public:
   /** +-=---------------------------------------------------------Mi 3. Okt 11:58:15 2012--------*
    * @method  CoedtwObjectRef::SetProxy                     // public                            *
    * @return  void                                          //                                   *
    * @param   CdmEnhancedQueryProxy* p_pCwmsProxy           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 3. Okt 11:58:15 2012-----------*/
    void SetProxy(CdmEnhancedQueryProxy* p_pCwmsProxy);

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:46:54 2012--------*
    * @method  CoedtwObjectRef::GetTabEditWidget             // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:46:54 2012-----------*/
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);
    void SetProxy(QString p_qstrWql);
    void GetSelectionEdit(QHBoxLayout* pqLayout, QWidget* pqWidget);
    void GetComboBoxEdit(QWidget *pqWidget, QHBoxLayout *pqLayout);
    void SetEventValueInTab(CdmValue *pCdmValue, CdmObject *pEventObject);
};

#endif //
