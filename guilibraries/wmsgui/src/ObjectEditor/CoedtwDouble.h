/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwDouble.h,v 1.6 2006/01/06 20:19:27 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWDOUBLE_H
#define COEDTWDOUBLE_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;
class QLabel;


class CoedtwDouble : public CoeValueWidget
{

   Q_OBJECT

   private:
        QLabel* m_pqlPrefix;
        QLabel* m_pqlSuffix;
      QLineEdit* m_pqleEdit;
      // following member are needed for the search
      QComboBox* m_pqcbComboBox;


   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:01:27 2012-------*
    * @method  CoedtwDouble::CoedtwDouble                    // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:01:27 2012----------*/
    CoedtwDouble( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwDouble(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:45:24 2003--------*
    * @method  CoedtwDouble::~CoedtwDouble                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Mon Dec 8 16:45:24 2003-------*/
   public:
      virtual ~CoedtwDouble(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:54:40 2012-------*
    * @method  CoedtwDouble::GetEditWidget                   // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:54:40 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Wed Dec 10 16:50:52 2003-------*
    * @method  CoedtwDouble::SetValue                        // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:50:52 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Wed Dec 10 16:52:13 2003-------*
    * @method  CoedtwDouble::ValueChangedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:52:13 2003------*/
    void setEventClassValue();
private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Fri Dec 12 10:35:37 2003-------*
    * @method  CoedtwDouble::SetReadOnly                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:35:37 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:24:32 2008--------*
    * @method  CoedtwDouble::CoedtwDouble                    // public                            *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 19:24:32 2008-----------*/
    CoedtwDouble( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:33:35 2012-------*
    * @method  CoedtwDouble::GetSearchWidget                 // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:33:35 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 14:00:31 2008--------*
    * @method  CoedtwDouble::AddQueryElement                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 14:00:31 2008-----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 20:26:59 2008-------*
    * @method  CoedtwDouble::SetSearchDeaultValue            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 20:26:59 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
};

#endif //
