/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwBool.h,v 1.6 2006/01/06 20:19:23 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWBOOL_H
#define COEDTWBOOL_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QCheckBox;


class CoedtwBool : public CoeValueWidget
{
   Q_OBJECT

   private:
      QCheckBox* m_pqchbCheckbox;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:02:22 2012-------*
    * @method  CoedtwBool::CoedtwBool                        // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:02:22 2012----------*/
    CoedtwBool( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwBool(const CdmObject *pEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:31:59 2003--------*
    * @method  CoedtwBool::~CoedtwBool                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *                                                                                             *
    *                                                                                             *
    *---------------------------------------------------------------Mon Dec 8 16:31:59 2003-------*/
   public:
      virtual ~CoedtwBool(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 13:57:06 2012-------*
    * @method  CoedtwBool::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 13:57:06 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);


   /** +-=---------------------------------------------------------Wed Dec 10 16:51:12 2003-------*
    * @method  CoedtwBool::SetValue                          // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:51:12 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Wed Dec 10 16:55:48 2003-------*
    * @method  CoedtwBool::ValueChangedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:55:48 2003------*/
    void setEventClassValue();
private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Fri Dec 12 10:34:57 2003-------*
    * @method  CoedtwBool::SetReadOnly                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:34:57 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:20:39 2008--------*
    * @method  CoedtwBool::CoedtwBool                        // public                            *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 19:20:39 2008-----------*/
    CoedtwBool( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 13:57:27 2012-------*
    * @method  CoedtwBool::GetSearchWidget                   // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 13:57:27 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 14:03:19 2008--------*
    * @method  CoedtwBool::AddQueryElement                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 14:03:19 2008-----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 20:25:14 2008-------*
    * @method  CoedtwBool::SetSearchDeaultValue              // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 20:25:14 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
};

#endif //
