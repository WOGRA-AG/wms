/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CoedtwDate.h,v 1.6 2006/01/06 20:19:25 Entwicklung Exp $
 ******************************************************************************/

#ifndef COEDTWDATE_H
#define COEDTWDATE_H

// System and QT Includes



// own Includes
#include "CwmsDateEdit.h"
#include "CoeDataTypeWidget.h"

// forwards
class QDateEdit;
class QComboBox;
class QLabel;
class QCheckBox;

class CoedtwDate : public CoeValueWidget
{
   Q_OBJECT

   private:
     QDateEdit* m_pqdeDate;
      // folowing members are used for the search
      QComboBox* m_pqcbComboBox;
      QLabel*    m_pqlLabelFrom;
      QLabel*    m_pqlLabelTo;
      QDateEdit* m_pqdDateEditFrom;
      QDateEdit* m_pqdDateEditTo;
      QCheckBox* m_pqchbRelevant;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:01:51 2012-------*
    * @method  CoedtwDate::CoedtwDate                        // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:01:51 2012----------*/
    CoedtwDate( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwDate(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Thu Dec 11 14:33:11 2003-------*
    * @method  CoedtwDate::~CoedtwDate                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Thu Dec 11 14:33:11 2003------*/
   public:
      virtual ~CoedtwDate(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:31:21 2012-------*
    * @method  CoedtwDate::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:31:21 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Thu Dec 11 14:45:40 2003-------*
    * @method  CoedtwDate::ValueChangedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Thu Dec 11 14:45:40 2003------*/
    private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Thu Dec 11 14:45:43 2003-------*
    * @method  CoedtwDate::SetValue                          // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Thu Dec 11 14:45:43 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Fri Dec 12 10:35:16 2003-------*
    * @method  CoedtwDate::SetReadOnly                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:35:16 2003------*/
void setEventClassValue();
public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:21:33 2008--------*
    * @method  CoedtwDate::CoedtwDate                        // public                            *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 19:21:33 2008-----------*/
    CoedtwDate( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:31:38 2012-------*
    * @method  CoedtwDate::GetSearchWidget                   // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:31:38 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 14:01:45 2008--------*
    * @method  CoedtwDate::AddQueryElement                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 14:01:45 2008-----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

    private slots:
   /** +-=---------------------------------------------------------Sa 6. Sep 16:12:42 2008--------*
    * @method  CoedtwDate::CompareComboBoxIndexChangedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @param   int p_iIndex                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 16:12:42 2008-----------*/
void CompareComboBoxIndexChangedSlot( int p_iIndex);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:07:28 2008--------*
    * @method  CoedtwDate::AddQueryElementEqual              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment an comparison to equality.                                                         *
    *----------------last changed: -----------------------------So 7. Sep 10:07:28 2008-----------*/
    void AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:08:08 2008--------*
    * @method  CoedtwDate::AddQueryElementFrom               // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment comparison to from value                                                           *
    *----------------last changed: -----------------------------So 7. Sep 10:08:08 2008-----------*/
    void AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:30:13 2008--------*
    * @method  CoedtwDate::AddQueryElementTo                 // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @param   bool p_bUseFromEdit = true                    //                                   *
    * @comment comparison to to value                                                             *
    *----------------last changed: -----------------------------So 7. Sep 10:30:13 2008-----------*/
    void AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit = true);

   private:
   /** +-=---------------------------------------------------------So 7. Sep 10:09:02 2008--------*
    * @method  CoedtwDate::AddQueryElementFromTo             // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment comparisonbetween from and to value.                                               *
    *----------------last changed: -----------------------------So 7. Sep 10:09:02 2008-----------*/
    void AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent);

    private slots:
   /** +-=---------------------------------------------------------Di 9. Sep 18:03:49 2008--------*
    * @method  CoedtwDate::RelevantCheckBoxClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 9. Sep 18:03:49 2008-----------*/
void RelevantCheckBoxClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 20:26:19 2008-------*
    * @method  CoedtwDate::SetSearchDeaultValue              // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 20:26:19 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
};

#endif //
