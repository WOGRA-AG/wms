/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWUSERGROUP_H
#define COEDTWUSERGROUP_H

// System and QT Includes
#include <QPushButton>


// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwUserGroup : public CoeValueWidget
{
      Q_OBJECT

   private:
      QPushButton* m_pqbButton;
      QLineEdit* m_qleGroup;
     qint64 m_lCurrentGroupId;

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:33:23 2012-------*
    * @method  CoedtwUserGroup::CoedtwUserGroup              // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constructor for valueediting.                                                  *
    *----------------last changed: -----------------------------Di 28. Aug 15:33:23 2012----------*/
    CoedtwUserGroup( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwUserGroup(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:33:31 2012-------*
    * @method  CoedtwUserGroup::CoedtwUserGroup              // public, virtual                   *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Constuctor for searching.                                                      *
    *----------------last changed: -----------------------------Di 28. Aug 15:33:31 2012----------*/
    CoedtwUserGroup( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:33:41 2012-------*
    * @method  CoedtwUserGroup::~CoedtwUserGroup             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *----------------last changed: -----------------------------Di 28. Aug 15:33:41 2012----------*/
    virtual ~CoedtwUserGroup( );

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:33:48 2012-------*
    * @method  CoedtwUserGroup::GetEditWidget                // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 15:33:48 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   protected slots:
   /** +-=---------------------------------------------------------Di 28. Aug 15:33:57 2012-------*
    * @method  CoedtwUserGroup::SetValue                     // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Di 28. Aug 15:33:57 2012----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);

    void setEventClassValue();
private slots:
   /** +-=---------------------------------------------------------Di 28. Aug 15:34:14 2012-------*
    * @method  CoedtwUserGroup::ValueChangedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *----------------last changed: -----------------------------Di 28. Aug 15:34:14 2012----------*/
void ValueChangedSlotByUser( );
void openNewWindow();
   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:34:24 2012-------*
    * @method  CoedtwUserGroup::SetReadOnly                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                         *
    *----------------last changed: -----------------------------Di 28. Aug 15:34:24 2012----------*/
    virtual void SetReadOnly();
    virtual void SetEditable();

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:34:34 2012-------*
    * @method  CoedtwUserGroup::GetSearchWidget              // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 15:34:34 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 15:34:41 2012-------*
    * @method  CoedtwUserGroup::AddQueryElement              // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement* p_pCdmQueryElementParent     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 15:34:41 2012----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);
};

#endif //
