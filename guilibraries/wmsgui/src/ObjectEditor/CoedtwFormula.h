/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CoedtwFormula_H
#define CoedtwFormula_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwFormula : public CoeValueWidget
{
      Q_OBJECT

   private:
      QLineEdit* m_pqleEdit;

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:24:49 2012-------*
    * @method  CoedtwFormula::CoedtwFormula                // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constructor for valueediting.                                                  *
    *----------------last changed: -----------------------------Di 28. Aug 14:24:49 2012----------*/
    CoedtwFormula( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwFormula(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:24:54 2012-------*
    * @method  CoedtwFormula::CoedtwFormula                // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constuctor for searching.                                                      *
    *----------------last changed: -----------------------------Di 28. Aug 14:24:54 2012----------*/
    CoedtwFormula( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:24:59 2012-------*
    * @method  CoedtwFormula::~CoedtwFormula               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *----------------last changed: -----------------------------Di 28. Aug 14:24:59 2012----------*/
    virtual ~CoedtwFormula( );

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:25:06 2012-------*
    * @method  CoedtwFormula::GetEditWidget                 // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 14:25:06 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   protected slots:
   /** +-=---------------------------------------------------------Di 28. Aug 14:25:15 2012-------*
    * @method  CoedtwFormula::SetValue                      // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Di 28. Aug 14:25:15 2012----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);

    void setEventClassValue();
private slots:
   /** +-=---------------------------------------------------------Di 28. Aug 14:25:25 2012-------*
    * @method  CoedtwFormula::ValueChangedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *----------------last changed: -----------------------------Di 28. Aug 14:25:25 2012----------*/
void ValueChangedSlotByUser( );

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 14:25:42 2012-------*
    * @method  CoedtwFormula::SetReadOnly                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                         *
    *----------------last changed: -----------------------------Di 28. Aug 14:25:42 2012----------*/
    virtual void SetReadOnly();
    virtual void SetEditable();

};

#endif //
