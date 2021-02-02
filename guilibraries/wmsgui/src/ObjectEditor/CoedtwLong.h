/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwLong.h,v 1.6 2006/01/06 20:19:29 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWLONG_H
#define COEDTWLONG_H

// System and QT Includes


// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;


class CoedtwLong : public CoeValueWidget
{
   Q_OBJECT

   private:
      QLineEdit* m_pleEdit;


   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:00:17 2012-------*
    * @method  CoedtwLong::CoedtwLong                        // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:00:17 2012----------*/
    CoedtwLong( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwLong(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:47:23 2003--------*
    * @method  CoedtwLong::~CoedtwLong                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Mon Dec 8 16:47:23 2003-------*/
   public:
      virtual ~CoedtwLong(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:36:34 2012-------*
    * @method  CoedtwLong::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:36:34 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Wed Dec 10 16:50:47 2003-------*
    * @method  CoedtwLong::SetValue                       // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:50:47 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Wed Dec 10 16:52:23 2003-------*
    * @method  CoedtwLong::ValueChangedSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:52:23 2003------*/
    void setEventClassValue();
private slots:
void ValueChangedSlotByUser(  );
};

#endif //
