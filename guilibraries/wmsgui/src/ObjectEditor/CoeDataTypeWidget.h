/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEValueWIDGET_H
#define COEValueWIDGET_H


// System and QT Includes
#include <QObject>
#include <QFormLayout>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// own Includes
#include "wmsgui.h"

// forwards
class QHBoxLayout;
class QLabel;
class QLineEdit;
class CdmValue;
class QWidget;
class CdmMember;


class WMSGUI_API CoeValueWidget : public QObject
{
   Q_OBJECT

   protected:
      EdmStringDisplayType m_eOeDisplayType;
      CdmValue* m_rpCdmValue;
      const CdmMember* m_rpCdmMember;
      QString m_qstrKeyname;
      QLineEdit* m_rpqleCaption;
      QHBoxLayout* m_pqhbLayout;
      static QList<CdmValue*> m_qlEventClassValues;

   private:
      QLabel* m_pqlLabel;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 10:53:03 2012-------*
    * @method  CoeValueWidget::CoeValueWidget                // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 10:53:03 2012----------*/
    CoeValueWidget(CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoeValueWidget(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = NULL);
   /** +-=---------------------------------------------------------Fri Dec 5 16:39:01 2003--------*
    * @method  CoeValueWidget::~CoeValueWidget         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoeValueWidget.                                         *
    *---------------------------------------------------------------Fri Dec 5 16:39:01 2003-------*/
   public:
      virtual ~CoeValueWidget(  );

   public slots:
   /** +-=---------------------------------------------------------Fri Dec 5 16:42:42 2003--------*
    * @method  CoeValueWidget::ValueChangedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Fri Dec 5 16:42:42 2003-------*/

virtual void ValueChangedSlotByUser(  );
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:53:37 2012-------*
    * @method  CoeValueWidget::GetEditWidget                 // public, p virtual                 *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment This method returns the Edit widget for this Value.                                *
    *----------------last changed: -----------------------------Mi 22. Aug 14:53:37 2012----------*/
    virtual QWidget* GetEditWidget(QWidget* p_pqwParent)= 0;
   
	public slots:
   /** +-=---------------------------------------------------------Di 28. Sep 09:05:28 2010-------*
    * @method  CoeValueWidget::SetValue                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmValue* #p_pCdmValue                        //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Di 28. Sep 09:05:28 2010----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);
   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 12:54:44 2008--------*
    * @method  CoeValueWidget::CreateValueWidget             // public, static                    *
    * @return  CoeValueWidget*                               //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment Factory method which creates the correct widgets fror the object editor.           *
    *----------------last changed: -----------------------------Sa 6. Sep 12:54:44 2008-----------*/
    static CoeValueWidget* CreateValueWidget(CdmValue* p_pCdmValue, QWidget* p_pqwParent);
    static CoeValueWidget* CreateEventValueWidget(CdmValue* p_pCdmEventValue, QWidget* p_pqwParent, const CdmObject *p_EventObject);

   /** +-=---------------------------------------------------------Fri Dec 12 10:34:30 2003-------*
    * @method  CoeValueWidget::SetReadOnly                // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                      *
    *---------------------------------------------------------------Fri Dec 12 10:34:30 2003------*/
   public:
      virtual void SetReadOnly(  );
      virtual void SetEditable();
   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 13:51:29 2012-------*
    * @method  CoeValueWidget::CreateWidget                  // public                            *
    * @return  void                                          //                                   *
    * @param   QFormLayout* p_qLayout                        //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 13:51:29 2012----------*/
    void CreateWidget(QFormLayout* p_qLayout, QWidget* p_pqwParent);
    void CreateEventWidget(QFormLayout* p_qLayout, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 16:27:30 2012--------*
    * @method  CoeValueWidget::SetDisplayType                // public                            *
    * @return  void                                          //                                   *
    * @param   EdmStringDisplayType p_eOeDisplayType         //                                   *
    * @comment This method sets the displaytype of the widget.                                    *
    *----------------last changed: -----------------------------Mo 3. Sep 16:27:30 2012-----------*/
    void SetDisplayType(EdmStringDisplayType p_eOeDisplayType);

   public:
   /** +-=---------------------------------------------------------Di 8. Mai 20:53:05 2007--------*
    * @method  CoeValueWidget::SetCaptionLineEdit            // public                            *
    * @return  void                                          //                                   *
    * @param   QLineEdit* p_pqleCaption                      //                                   *
    * @comment This method sets the caption lineedit with makes it possible that every change     *
    *          of this widget will be set to the caption lineedit.                                *
    *----------------last changed: Wolfgang Graßhof-------------Di 8. Mai 20:53:05 2007-----------*/
    void SetCaptionLineEdit(QLineEdit* p_pqleCaption);

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:03:39 2013-------*
    * @method  CoeValueWidget::CreateSearchValueWidget       // public, static                    *
    * @return  CoeValueWidget*                               //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment Factory method which creates the correct widgets fror the object editor.           *
    *----------------last changed: -----------------------------Mo 11. Feb 11:03:39 2013----------*/
    static CoeValueWidget* CreateSearchValueWidget(const CdmMember* p_pCdmMember,
                                                   QString p_qstrKeyname,
                                                   QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 15:23:18 2012-------*
    * @method  CoeValueWidget::GetSearchWidget               // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget*# p_pqwParent                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 15:23:18 2012----------*/
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 13:53:55 2012-------*
    * @method  CoeValueWidget::CreateSearchWidget            // public                            *
    * @return  void                                          //                                   *
    * @param   QFormLayout* p_pqLayout                       //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment creates the searchwidget from this value.                                          *
    *----------------last changed: -----------------------------Mi 22. Aug 13:53:55 2012----------*/
    void CreateSearchWidget(QFormLayout* p_pqLayout, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:35:58 2008--------*
    * @method  CoeValueWidget::CoeValueWidget                // public                            *
    * @return                                                //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 8. Sep 19:35:58 2008-----------*/
    CoeValueWidget( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 28. Sep 09:05:06 2010-------*
    * @method  CoeValueWidget::AddQueryElement               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmQueryElement*# p_pCdmQueryElementParent    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 09:05:06 2010----------*/
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 19:27:22 2008-------*
    * @method  CoeValueWidget::SetCaption                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @comment Sets a new caption to the value.                                                   *
    *----------------last changed: -----------------------------Mi 10. Sep 19:27:22 2008----------*/
    void SetCaption(QString p_qstrCaption);

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 19:28:14 2008-------*
    * @method  CoeValueWidget::SetSearchDeaultValue          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDefault                         //                                   *
    * @comment This method sets the search default value in a searchwidget.                       *
    *----------------last changed: -----------------------------Mi 10. Sep 19:28:14 2008----------*/
    virtual void SetSearchDeaultValue(QString p_qstrDefault);

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 15:13:22 2012-------*
    * @method  CoeValueWidget::CreateCaptionLabel            // private                           *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 15:13:22 2012----------*/
    QWidget* CreateCaptionLabel(QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 14:09:19 2012--------*
    * @method  CoeValueWidget::CreateTabWidget               // public                            *
    * @return  bool                                          //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @param   QVBoxLayout* p_pqlLayout                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 14:09:19 2012-----------*/
    bool CreateTabWidget(QWidget* p_pqwParent, QVBoxLayout* p_pqlLayout);

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:33:44 2012--------*
    * @method  CoeValueWidget::GetTabEditWidget              // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:33:44 2012-----------*/
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);

    public:
    /** methods that get overwritten by the specific class. They do not need to implemented from every class!
    * those methods are meant for EventSourcing
    */
    virtual void setEventClassValue();
    virtual void SetEventValueInTab(CdmValue *pCdmValue, CdmObject *pEventObject);
    QList<CdmValue*> getEventClassValues() const;
};

#endif //
