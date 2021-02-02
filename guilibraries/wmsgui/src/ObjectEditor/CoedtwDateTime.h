/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwDateTime.h,v 1.6 2006/01/06 20:19:26 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWDATETIME_H
#define COEDTWDATETIME_H

// System and QT Includes
#include <QDateTimeEdit>


// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QDateTimeEdit;
class QComboBox;
class QLabel;
class QCheckBox;

class CoedtwDateTime : public CoeValueWidget
{
   Q_OBJECT

   private:
      QDateTimeEdit* m_pqdeDateTime;
      // following member are needed for the search
      QComboBox*     m_pqcbComboBox;
      QLabel*        m_pqlLabelFrom;
      QLabel*        m_pqlLabelTo;
      QDateTimeEdit* m_pqdDateEditFrom;
      QDateTimeEdit* m_pqdDateEditTo;
      QCheckBox* m_pqchbRelevant;


   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:01:38 2012-------*
    * @method  CoedtwDateTime::CoedtwDateTime                // public                            *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:01:38 2012----------*/
    CoedtwDateTime( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwDateTime(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Thu Dec 11 14:35:23 2003-------*
    * @method  CoedtwDateTime::~CoedtwDateTime               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Thu Dec 11 14:35:23 2003------*/
   public:
      virtual ~CoedtwDateTime(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:32:03 2012-------*
    * @method  CoedtwDateTime::GetEditWidget                 // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:32:03 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Thu Dec 11 14:46:57 2003-------*
    * @method  CoedtwDateTime::ValueChangedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Thu Dec 11 14:46:57 2003------*/
    private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Thu Dec 11 14:47:00 2003-------*
    * @method  CoedtwDateTime::SetValue                      // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Thu Dec 11 14:47:00 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Fri Dec 12 10:35:24 2003-------*
    * @method  CoedtwDateTime::SetReadOnly                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:35:24 2003------*/
void setEventClassValue();
public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:22:24 2008--------*
    * @method  CoedtwDateTime::CoedtwDateTime                // public                            *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 19:22:24 2008-----------*/
    CoedtwDateTime( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:32:29 2012-------*
    * @method  CoedtwDateTime::GetSearchWidget               // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:32:29 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 14:00:55 2008--------*
    * @method  CoedtwDateTime::AddQueryElement               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 14:00:55 2008-----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

    private slots:
   /** +-=---------------------------------------------------------So 7. Sep 10:26:39 2008--------*
    * @method  CoedtwDateTime::CompareComboBoxIndexChangedSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @param   int p_iIndex                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 7. Sep 10:26:39 2008-----------*/
void CompareComboBoxIndexChangedSlot( int p_iIndex);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:27:10 2008--------*
    * @method  CoedtwDateTime::AddQueryElementFromTo         // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment comparisonbetween from and to value.                                               *
    *----------------last changed: -----------------------------So 7. Sep 10:27:10 2008-----------*/
    void AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:29:08 2008--------*
    * @method  CoedtwDateTime::AddQueryElementTo             // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @param   bool p_bUseFromEdit = true                    //                                   *
    * @comment comparison to to value                                                             *
    *----------------last changed: -----------------------------So 7. Sep 10:29:08 2008-----------*/
    void AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit = true);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:27:27 2008--------*
    * @method  CoedtwDateTime::AddQueryElementFrom           // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment comparison to from value                                                           *
    *----------------last changed: -----------------------------So 7. Sep 10:27:27 2008-----------*/
    void AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:27:34 2008--------*
    * @method  CoedtwDateTime::AddQueryElementEqual          // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment an comparison to equality.                                                         *
    *----------------last changed: -----------------------------So 7. Sep 10:27:34 2008-----------*/
    void AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent);

    private slots:
   /** +-=---------------------------------------------------------Di 9. Sep 18:07:59 2008--------*
    * @method  CoedtwDateTime::RelevantCheckBoxClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 9. Sep 18:07:59 2008-----------*/
void RelevantCheckBoxClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 20:26:40 2008-------*
    * @method  CoedtwDateTime::SetSearchDeaultValue          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 20:26:40 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
};

#endif //
