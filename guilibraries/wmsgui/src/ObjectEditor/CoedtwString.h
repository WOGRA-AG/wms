/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwString.h,v 1.7 2006/01/20 22:54:12 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWSTRING_H
#define COEDTWSTRING_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwString : public CoeValueWidget
{

      Q_OBJECT

   private:
      QLineEdit* m_pqleEdit;
      // following member are needed for the search
      QComboBox* m_pqcbComboBox;


   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 10:59:39 2012-------*
    * @method  CoedtwString::CoedtwString                    // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constructor for valueediting.                                                  *
    *----------------last changed: -----------------------------Mi 22. Aug 10:59:39 2012----------*/
    CoedtwString( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwString(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:49:02 2003--------*
    * @method  CoedtwString::~CoedtwString                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Mon Dec 8 16:49:02 2003-------*/
   public:
      virtual ~CoedtwString(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:44:57 2012-------*
    * @method  CoedtwString::GetEditWidget                   // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:44:57 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Wed Dec 10 16:50:34 2003-------*
    * @method  CoedtwString::SetValue                        // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:50:34 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Wed Dec 10 16:52:49 2003-------*
    * @method  CoedtwString::ValueChangedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:52:49 2003------*/
    private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Fri Dec 12 10:36:26 2003-------*
    * @method  CoedtwString::SetReadOnly                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:36:26 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

    private slots:
   /** +-=---------------------------------------------------------Fr 20. Jan 23:18:54 2006*
    * @method  CoedtwString::SearchClickedSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the search button was clicked.                         *
    *----------------last changed: Wolfgang Graßhof-------------Fr 20. Jan 23:18:54 2006----------*/
void SearchClickedSlot(  );

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:24:58 2008--------*
    * @method  CoedtwString::CoedtwString                    // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constuctor for searching.                                                      *
    *----------------last changed: -----------------------------Mo 8. Sep 19:24:58 2008-----------*/
    CoedtwString( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:48:15 2012-------*
    * @method  CoedtwString::GetSearchWidget                 // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:48:15 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 14:00:11 2008--------*
    * @method  CoedtwString::AddQueryElement                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 14:00:11 2008-----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 20:27:16 2008-------*
    * @method  CoedtwString::SetSearchDeaultValue            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 20:27:16 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
    virtual void setEventClassValue();
};

#endif //
