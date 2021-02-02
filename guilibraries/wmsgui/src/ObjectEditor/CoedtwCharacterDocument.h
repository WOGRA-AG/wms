/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWCHARACTERDOCUMENT_H
#define COEDTWCHARACTERDOCUMENT_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QTextEdit;
class QPushButton;
class CoeTextEditMainWindow;

class CoedtwCharacterDocument : public CoeValueWidget
{
   Q_OBJECT

   private:
      QTextEdit* m_pqteTextEdit;
      CoeTextEditMainWindow* m_pTextEdit;
      QPushButton* m_pqpbEdit;
      

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:02:02 2012-------*
    * @method  CoedtwCharacterDocument::CoedtwCharacterDocument // public                         *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:02:02 2012----------*/
    CoedtwCharacterDocument( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwCharacterDocument(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:44:46 2003--------*
    * @method  CoedtwCharacterDocument::~CoedtwCharacterDocument // public, virtual               *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *---------------------------------------------------------------Mon Dec 8 16:44:46 2003-------*/
   public:
      virtual ~CoedtwCharacterDocument(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 13:58:29 2012-------*
    * @method  CoedtwCharacterDocument::GetEditWidget        // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_qwParent                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 13:58:29 2012----------*/
    QWidget* GetEditWidget(QWidget* p_qwParent);

   /** +-=---------------------------------------------------------Wed Dec 10 16:50:57 2003-------*
    * @method  CoedtwCharacterDocument::SetValue             // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:50:57 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );

   /** +-=---------------------------------------------------------Wed Dec 10 16:52:03 2003-------*
    * @method  CoedtwCharacterDocument::ValueChangedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:52:03 2003------*/
    void setEventClassValue();
private slots:
void ValueChangedSlotByUser(  );

   /** +-=---------------------------------------------------------Fri Dec 12 10:35:07 2003-------*
    * @method  CoedtwCharacterDocument::SetReadOnly          // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:35:07 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();

    private slots:
   /** +-=---------------------------------------------------------Mi 4. Jun 19:45:44 2008--------*
    * @method  CoedtwCharacterDocument::EditClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the edit button was clicked. it opens the edit         *
    *          dialog.                                                                            *
    *----------------last changed: -----------------------------Mi 4. Jun 19:45:44 2008-----------*/
void EditClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:55:14 2012--------*
    * @method  CoedtwCharacterDocument::GetTabEditWidget     // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:55:14 2012-----------*/
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);
};

#endif //
