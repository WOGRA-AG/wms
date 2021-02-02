/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWENUM_H
#define COEDTWENUM_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwEnum : public CoeValueWidget
{
      Q_OBJECT

   private:
      QComboBox* m_pqcbComboBox;

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:37:26 2012-------*
    * @method  CoedtwEnum::CoedtwEnum                        // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constructor for valueediting.                                                  *
    *----------------last changed: -----------------------------Di 28. Aug 14:37:26 2012----------*/
    CoedtwEnum( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwEnum(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:37:31 2012-------*
    * @method  CoedtwEnum::CoedtwEnum                        // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constuctor for searching.                                                      *
    *----------------last changed: -----------------------------Di 28. Aug 14:37:31 2012----------*/
    CoedtwEnum( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:37:37 2012-------*
    * @method  CoedtwEnum::~CoedtwEnum                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *----------------last changed: -----------------------------Di 28. Aug 14:37:37 2012----------*/
    virtual ~CoedtwEnum( );

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:37:47 2012-------*
    * @method  CoedtwEnum::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 14:37:47 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   protected slots:
   /** +-=---------------------------------------------------------Di 28. Aug 14:37:52 2012-------*
    * @method  CoedtwEnum::SetValue                          // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Di 28. Aug 14:37:52 2012----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);


    void setEventClassValue();
private slots:
   /** +-=---------------------------------------------------------Di 28. Aug 14:38:08 2012-------*
    * @method  CoedtwEnum::ValueChangedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *----------------last changed: -----------------------------Di 28. Aug 14:38:08 2012----------*/
void ValueChangedSlotByUser( );

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:38:21 2012-------*
    * @method  CoedtwEnum::SetReadOnly                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                         *
    *----------------last changed: -----------------------------Di 28. Aug 14:38:21 2012----------*/
    virtual void SetReadOnly();
    virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:38:31 2012-------*
    * @method  CoedtwEnum::GetSearchWidget                   // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 14:38:31 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:38:43 2012-------*
    * @method  CoedtwEnum::AddQueryElement                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 14:38:43 2012----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);


   private:
   /** +-=---------------------------------------------------------So 7. Okt 13:31:14 2012--------*
    * @method  CoedtwEnum::AddSelectionValuesToComboBox      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 7. Okt 13:31:14 2012-----------*/
    void AddSelectionValuesToComboBox();
};

#endif //
