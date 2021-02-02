/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWUSER_H
#define COEDTWUSER_H

// System and QT Includes
#include <QPushButton>
#include <QTreeWidget>

// own Includes
#include "CoeDataTypeWidget.h"
#include "CumUser.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwUser : public CoeValueWidget
{
      Q_OBJECT

   private:
      QPushButton* m_pqbButton;
      QLineEdit* m_pqleUser;
      long m_lCurrentUserId;

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:06:06 2012-------*
    * @method  CoedtwUser::CoedtwUser                        // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constructor for valueediting.                                                  *
    *----------------last changed: -----------------------------Di 28. Aug 15:06:06 2012----------*/
    CoedtwUser( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwUser(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:06:15 2012-------*
    * @method  CoedtwUser::CoedtwUser                        // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constuctor for searching.                                                      *
    *----------------last changed: -----------------------------Di 28. Aug 15:06:15 2012----------*/
    CoedtwUser( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:06:20 2012-------*
    * @method  CoedtwUser::~CoedtwUser                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *----------------last changed: -----------------------------Di 28. Aug 15:06:20 2012----------*/
    virtual ~CoedtwUser( );

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:06:32 2012-------*
    * @method  CoedtwUser::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 15:06:32 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   protected slots:
   /** +-=---------------------------------------------------------Di 28. Aug 15:09:33 2012-------*
    * @method  CoedtwUser::SetValue                          // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Di 28. Aug 15:09:33 2012----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);

    void setEventClassValue();
private slots:
   /** +-=---------------------------------------------------------Di 28. Aug 15:09:40 2012-------*
    * @method  CoedtwUser::ValueChangedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *----------------last changed: -----------------------------Di 28. Aug 15:09:40 2012----------*/
void ValueChangedSlotByUser( );
void openNewWindow();
   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:09:47 2012-------*
    * @method  CoedtwUser::SetReadOnly                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                         *
    *----------------last changed: -----------------------------Di 28. Aug 15:09:47 2012----------*/
    virtual void SetReadOnly();
    virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:09:52 2012-------*
    * @method  CoedtwUser::GetSearchWidget                   // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 15:09:52 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:09:57 2012-------*
    * @method  CoedtwUser::AddQueryElement                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 15:09:57 2012----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

};

#endif //
