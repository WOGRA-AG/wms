/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwTime.h,v 1.6 2006/01/06 20:19:33 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWTIME_H
#define COEDTWTIME_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QTimeEdit;
class QComboBox;
class QLabel;
class QCheckBox;

class CoedtwTime : public CoeValueWidget
{
   Q_OBJECT

   private:
      QTimeEdit* m_pqdeTime;
      // following member are needed for the search
      QComboBox* m_pqcbComboBox;
      QLabel*    m_pqlLabelFrom;
      QLabel*    m_pqlLabelTo;
      QTimeEdit* m_pqdDateEditFrom;
      QTimeEdit* m_pqdDateEditTo;
      QCheckBox* m_pqchbRelevant;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 10:59:30 2012-------*
    * @method  CoedtwTime::CoedtwTime                        // public                            *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 10:59:30 2012----------*/
    CoedtwTime( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwTime(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Thu Dec 11 14:35:01 2003-------*
    * @method  CoedtwTime::~CoedtwTime                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Thu Dec 11 14:35:01 2003------*/
   public:
      virtual ~CoedtwTime(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:48:46 2012-------*
    * @method  CoedtwTime::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:48:46 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Thu Dec 11 14:47:36 2003-------*
    * @method  CoedtwTime::ValueChangedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Thu Dec 11 14:47:36 2003------*/
    private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Thu Dec 11 14:47:39 2003-------*
    * @method  CoedtwTime::SetValue                          // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Thu Dec 11 14:47:39 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Fri Dec 12 10:38:35 2003-------*
    * @method  CoedtwTime::SetReadOnly                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:38:35 2003------*/
void setEventClassValue();
public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:32:12 2008--------*
    * @method  CoedtwTime::CoedtwTime                        // public                            *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 19:32:12 2008-----------*/
    CoedtwTime( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:49:14 2012-------*
    * @method  CoedtwTime::GetSearchWidget                   // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:49:14 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 18:30:19 2008--------*
    * @method  CoedtwTime::AddQueryElement                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 18:30:19 2008-----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

    private slots:
   /** +-=---------------------------------------------------------So 7. Sep 15:31:04 2008--------*
    * @method  CoedtwTime::CompareComboBoxIndexChangedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @param   int p_iIndex                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 7. Sep 15:31:04 2008-----------*/
void CompareComboBoxIndexChangedSlot( int p_iIndex);

   private:
   /** +-=---------------------------------------------------------Mo 8. Sep 18:29:51 2008--------*
    * @method  CoedtwTime::AddQueryElementTo                 // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @param   bool p_bUseFromEdit = true                    //                                   *
    * @comment comparison to to value                                                             *
    *----------------last changed: -----------------------------Mo 8. Sep 18:29:51 2008-----------*/
    void AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit = true);

   private:
   /** +-=---------------------------------------------------------Mo 8. Sep 18:30:00 2008--------*
    * @method  CoedtwTime::AddQueryElementFrom               // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment comparison to from value                                                           *
    *----------------last changed: -----------------------------Mo 8. Sep 18:30:00 2008-----------*/
    void AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent);

   private:
   /** +-=---------------------------------------------------------Mo 8. Sep 18:30:07 2008--------*
    * @method  CoedtwTime::AddQueryElementEqual              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment an comparison to equality.                                                         *
    *----------------last changed: -----------------------------Mo 8. Sep 18:30:07 2008-----------*/
    void AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent);

   private:
   /** +-=---------------------------------------------------------Mo 8. Sep 18:32:40 2008--------*
    * @method  CoedtwTime::AddQueryElementFromTo             // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment comparisonbetween from and to value.                                               *
    *----------------last changed: -----------------------------Mo 8. Sep 18:32:40 2008-----------*/
    void AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent);

    private slots:
   /** +-=---------------------------------------------------------Di 9. Sep 19:29:00 2008--------*
    * @method  CoedtwTime::RelevantCheckBoxClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 9. Sep 19:29:00 2008-----------*/
void RelevantCheckBoxClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 20:27:37 2008-------*
    * @method  CoedtwTime::SetSearchDeaultValue              // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 20:27:37 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
};

#endif //
