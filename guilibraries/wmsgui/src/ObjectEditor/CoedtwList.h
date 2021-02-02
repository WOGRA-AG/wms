/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef COEDTWLIST_H
#define COEDTWLIST_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"
#include "wmsgui.h"

// forwards
class QTreeWidget;
class QTextEdit;
class QPushButton;

class WMSGUI_API CoedtwList : public CoeValueWidget
{
   Q_OBJECT

   private:
      QTreeWidget* m_pqtwTreeWidget;
      QPushButton* m_pqpbEdit;
      QPushButton* m_pqpbAdd;
      QPushButton* m_pqpbRemove;
      QWidget* m_pqwParent;


    private slots:
   /** +-=---------------------------------------------------------Do 4. Sep 18:58:44 2008--------*
    * @method  CoedtwList::AddClickedSlot                    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment adds a new item to the list.                                                       *
    *----------------last changed: -----------------------------Do 4. Sep 18:58:44 2008-----------*/
void AddClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 4. Sep 18:58:51 2008--------*
    * @method  CoedtwList::RemoveClickedSlot                 // private, slots                    *
    * @return  void                                          //                                   *
    * @comment removes the selected items from list.                                              *
    *----------------last changed: -----------------------------Do 4. Sep 18:58:51 2008-----------*/
void RemoveClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:00:58 2012-------*
    * @method  CoedtwList::CoedtwList                        // public                            *
    * @return                                                //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:00:58 2012----------*/
    CoedtwList( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwList(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Do 4. Sep 18:57:29 2008--------*
    * @method  CoedtwList::~CoedtwList                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoedtwList                                                 *
    *----------------last changed: -----------------------------Do 4. Sep 18:57:29 2008-----------*/
    virtual ~CoedtwList( );

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 14:34:48 2012-------*
    * @method  CoedtwList::GetEditWidget                     // public                            *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 14:34:48 2012----------*/
    QWidget* GetEditWidget(QWidget* p_pqwParent);

   public slots:
   /** +-=---------------------------------------------------------Mi 18. Jan 18:59:24 2012-------*
    * @method  CoedtwList::SetValue                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment This method sets the value in the widget.                                          *
    *----------------last changed: -----------------------------Mi 18. Jan 18:59:24 2012----------*/
    virtual void SetValue(CdmValue* p_pCdmValue);

    private slots:
   /** +-=---------------------------------------------------------Do 4. Sep 18:58:11 2008--------*
    * @method  CoedtwList::ValueChangedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the value has changed.                                 *
    *----------------last changed: -----------------------------Do 4. Sep 18:58:11 2008-----------*/
void ValueChangedSlotByUser( );

   public:
   /** +-=---------------------------------------------------------Do 4. Sep 18:58:18 2008--------*
    * @method  CoedtwList::SetReadOnly                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method sets the current Value widget in ReadOnlymode.                         *
    *----------------last changed: -----------------------------Do 4. Sep 18:58:18 2008-----------*/
    virtual void SetReadOnly();
    virtual void SetEditable();

    private slots:
   /** +-=---------------------------------------------------------Do 4. Sep 18:58:24 2008--------*
    * @method  CoedtwList::EditClickedSlot                   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the edit button was clicked. it opens the edit         *
    *          dialog.                                                                            *
    *----------------last changed: -----------------------------Do 4. Sep 18:58:24 2008-----------*/
void EditClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:18:18 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<int, double> p_rqmIntDouble              //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:18:18 2008-----------*/
    void FillTreeWidget(QMap<int, double> p_rqmIntDouble);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:18:12 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<int, QString> p_rqmIntDouble             //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:18:12 2008-----------*/
    void FillTreeWidget(QMap<int, QString> p_rqmIntDouble);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:18:02 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<int, int> p_rqmIntDouble                 //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:18:02 2008-----------*/
    void FillTreeWidget(QMap<int, int> p_rqmIntDouble);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:17:57 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<QString, int> p_rqmIntDouble             //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:17:57 2008-----------*/
    void FillTreeWidget(QMap<QString, int> p_rqmIntDouble);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:17:50 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<QString, double> p_rqmIntDouble          //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:17:50 2008-----------*/
    void FillTreeWidget(QMap<QString, double> p_rqmIntDouble);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:17:43 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<QString, QString> p_rqmIntDouble         //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:17:43 2008-----------*/
    void FillTreeWidget(QMap<QString, QString> p_rqmIntDouble);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:17:37 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QLinkedList<double> p_rqvlList                //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:17:37 2008-----------*/
    void FillTreeWidget(QLinkedList<double> p_rqvlList);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:17:23 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QLinkedList<QString> p_rqvlList               //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:17:23 2008-----------*/
    void FillTreeWidget(QLinkedList<QString> p_rqvlList);

   private:
   /** +-=---------------------------------------------------------Do 4. Sep 19:17:31 2008--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QLinkedList<int> p_rqvlList                   //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Do 4. Sep 19:17:31 2008-----------*/
    void FillTreeWidget(QLinkedList<int> p_rqvlList);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 11:00:35 2012-------*
    * @method  CoedtwList::CoedtwList                        // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 11:00:35 2012----------*/
    CoedtwList( QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:35:22 2012--------*
    * @method  CoedtwList::GetTabEditWidget                  // public, virtual                   *
    * @return  QWidget*                                      //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:35:22 2012-----------*/
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);

   private:
   /** +-=---------------------------------------------------------Mi 9. Jan 14:53:12 2013--------*
    * @method  CoedtwList::FillTreeWidget                    // private                           *
    * @return  void                                          //                                   *
    * @param   QLinkedList<CdmObject*> p_rqvlList            //                                   *
    * @comment This method fills the treewidget.                                                  *
    *----------------last changed: -----------------------------Mi 9. Jan 14:53:12 2013-----------*/
    void FillTreeWidget(QLinkedList<CdmObject*> p_rqvlList);
    CdmClass *getListObjectClass(CdmValue *pCdmValue);
    void FillValueList(CdmClass *pListObjectClass);
    CdmClass *findListObjectClassInPackage(QString qstrClassKeyname);
};

#endif //
