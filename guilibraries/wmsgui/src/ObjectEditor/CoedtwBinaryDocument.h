/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWBINARYDOCUMENT_H
#define COEDTWBINARYDOCUMENT_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QPushButton;

class CoedtwBinaryDocument : public CoeValueWidget
{
   Q_OBJECT

   private:
      QLineEdit* m_pqleFilename;
      QPushButton* m_pqpbOpen;
      QPushButton* m_pqpbSelect;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:02:32 2012-------*
    * @method  CoedtwBinaryDocument::CoedtwBinaryDocument    // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:02:32 2012----------*/
    CoedtwBinaryDocument( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwBinaryDocument(const CdmObject *pEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Mon Dec 8 16:29:15 2003--------*
    * @method  CoedtwBinaryDocument::~CoedtwBinaryDocument   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwBinaryDocument                                       *
    *                                                                                             *
    *---------------------------------------------------------------Mon Dec 8 16:29:15 2003-------*/
   public:
      virtual ~CoedtwBinaryDocument(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 13:54:48 2012-------*
    * @method  CoedtwBinaryDocument::GetEditWidget           // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 13:54:48 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   /** +-=---------------------------------------------------------Wed Dec 10 16:51:25 2003-------*
    * @method  CoedtwBinaryDocument::SetValue                // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method sets the value in the widget.                                          *
    *---------------------------------------------------------------Wed Dec 10 16:51:25 2003------*/
   protected slots:
       virtual void SetValue(  CdmValue* p_pCdmValue );
       virtual void setEventClassValue();
   /** +-=---------------------------------------------------------Wed Dec 10 16:51:46 2003-------*
    * @method  CoedtwBinaryDocument::ValueChangedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *---------------------------------------------------------------Wed Dec 10 16:51:46 2003------*/
    private slots:
void ValueChangedSlotByUser();

   /** +-=---------------------------------------------------------Fri Dec 12 10:34:46 2003-------*
    * @method  CoedtwBinaryDocument::SetReadOnly             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:34:46 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();
    private slots:
   /** +-=---------------------------------------------------------Sa 31. Mai 09:22:29 2008-------*
    * @method  CoedtwBinaryDocument::SelectClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to select a file from                   *
    *          fileselectionbox.                                                                  *
    *----------------last changed: -----------------------------Sa 31. Mai 09:22:29 2008----------*/
void SelectClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Sa 31. Mai 09:23:10 2008-------*
    * @method  CoedtwBinaryDocument::OpenClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to open the stored file.                *
    *----------------last changed: -----------------------------Sa 31. Mai 09:23:10 2008----------*/
void OpenClickedSlot( );
};

#endif //
