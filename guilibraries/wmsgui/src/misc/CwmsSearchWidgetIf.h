/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsSearchWidgetIf.h
 ** Started Implementation: 2008/09/06
 ** Description:
 ** 
 ** This class implements the simple search gui for searching the wms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSEARCHWIDGETIF_H
#define CWMSSEARCHWIDGETIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>
#include <QList>
#include <QList>
#include <QPointer>
#include <QStringList>
#include <QString>

// WMS Manager Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsSearchWidgetIf.h"


// Forwards
class CdmObjectContainer;
class CdmQuery;
class CoeValueWidget;
class QWidget;

// Enumerations

// namespaces

/* 
 * This class implements the simple search gui for searching the wms
 */
class WMSGUI_API CwmsSearchWidgetIf : public QWidget, public Ui::CwmsSearchWidgetIfClass
{
    Q_OBJECT

private:
   QStringList m_qstrlSearchMembers;
   QStringList m_qstrlHiddenSearchMembers;
   QPointer<CdmClass> m_rpClass = {};
   QPointer<CdmObjectContainer> m_rpContainer = {};
   CdmQuery m_cCdmQuery;
   QWidget* m_pqwContent = {};
   QList<CoeValueWidget*> m_qlValueWidgets;
   QMap<QString, QString> m_qmSearchDefaultValues;
   QMap<QString, QString> m_qmSearchAliases;

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 09:19:05 2008--------*
    * @method  CwmsSearchWidgetIf::CwmsSearchWidgetIf        // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Sep 09:19:05 2008-----------*/
    CwmsSearchWidgetIf( QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 09:19:38 2008--------*
    * @method  CwmsSearchWidgetIf::~CwmsSearchWidgetIf       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsSearchWidgetIf                                         *
    *----------------last changed: -----------------------------Sa 6. Sep 09:19:38 2008-----------*/
    virtual ~CwmsSearchWidgetIf( );

public:
    CdmObjectContainer* GetObjectList();
    void SetObjectList(CdmObjectContainer* p_pContainer);

    CdmClass *GetClass();
    void SetClass(CdmClass *p_pClass);

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 19:22:04 2008-------*
    * @method  CwmsSearchWidgetIf::AddSearchMember           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrAlias = ""                      //                                   *
    * @comment Adds a further search member to the search. this search members will be            *
    *          displayed in the gui and the user can enter searchcriterias to this members.       *
    *----------------last changed: -----------------------------Mi 10. Sep 19:22:04 2008----------*/
    void AddSearchMember(QString p_qstrKeyname, QString p_qstrAlias = "");

   private:
   /** +-=---------------------------------------------------------Sa 6. Sep 09:42:27 2008--------*
    * @method  CwmsSearchWidgetIf::CreateQuery               // private                           *
    * @return  void                                          //                                   *
    * @comment creates the query with the settings.                                               *
    *----------------last changed: -----------------------------Sa 6. Sep 09:42:27 2008-----------*/
    void CreateQuery();

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 09:43:20 2008--------*
    * @method  CwmsSearchWidgetIf::FillWidget                // public                            *
    * @return  void                                          //                                   *
    * @comment Fills the widget for displaying the search widget                                  *
    *----------------last changed: -----------------------------Sa 6. Sep 09:43:20 2008-----------*/
    void FillWidget();

   public:
   /** +-=---------------------------------------------------------Di 9. Sep 08:18:25 2008--------*
    * @method  CwmsSearchWidgetIf::GetDisplayList            // public                            *
    * @return  void                                          //                                   *
    * @param   QList<qint64>& p_rqvlResults              // The list of objects or objectlists*
    *                                                        //  which can be used                *
    * @comment This is the abstract method which must be overwritten be the derived class. the    *
    *          gui components which uses proxies uses the list of results for displaying their    *
    *          contents.                                                                          *
    *----------------last changed: -----------------------------Di 9. Sep 08:18:25 2008-----------*/
    void GetDisplayList(QList<qint64>& p_rqvlResults);

    private slots:
   /** +-=---------------------------------------------------------Sa 6. Sep 09:44:34 2008--------*
    * @method  CwmsSearchWidgetIf::SearchClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the search button was clicked.                         *
    *----------------last changed: -----------------------------Sa 6. Sep 09:44:34 2008-----------*/
void SearchClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Sa 6. Sep 09:45:06 2008--------*
    * @method  CwmsSearchWidgetIf::SearchSignal              // private, signals                  *
    * @return  void                                          //                                   *
    * @comment This signal will be emitted if the user presses the search button.                 *
    *----------------last changed: -----------------------------Sa 6. Sep 09:45:06 2008-----------*/
    signals:
       void SearchSignal( );

   public:
   /** +-=---------------------------------------------------------Mo 8. Sep 19:57:01 2008--------*
    * @method  CwmsSearchWidgetIf::Clear                     // public                            *
    * @return  void                                          //                                   *
    * @comment This method clears the widget. After this call it can be created new.              *
    *----------------last changed: -----------------------------Mo 8. Sep 19:57:01 2008-----------*/
    void Clear();

   public:
   /** +-=---------------------------------------------------------Mi 10. Sep 19:22:55 2008-------*
    * @method  CwmsSearchWidgetIf::AddSearchDefaultValue     // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrDefaultValue                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 10. Sep 19:22:55 2008----------*/
    void AddSearchDefaultValue(QString p_qstrKeyname, QString p_qstrDefaultValue);

   public:
   /** +-=---------------------------------------------------------Do 11. Sep 18:54:28 2008-------*
    * @method  CwmsSearchWidgetIf::SetSearchMemberAsHidden   // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Sep 18:54:28 2008----------*/
    void SetSearchMemberAsHidden(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Sa 21. Feb 11:13:28 2009-------*
    * @method  CwmsSearchWidgetIf::SetSearchCaption          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 21. Feb 11:13:28 2009----------*/
    void SetSearchCaption(QString p_qstrCaption);

   private:
   /** +-=---------------------------------------------------------Mi 19. Aug 18:29:44 2009-------*
    * @method  CwmsSearchWidgetIf::AddAllSearchMembers       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Aug 18:29:44 2009----------*/
    void AddAllSearchMembers();

   private:
   /** +-=---------------------------------------------------------Mi 19. Aug 18:34:22 2009-------*
    * @method  CwmsSearchWidgetIf::IsMemberSearchable        // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Aug 18:34:22 2009----------*/
    bool IsMemberSearchable(CdmMember* p_pCdmMember);

   public:
   /** +-=---------------------------------------------------------Do 20. Aug 18:09:04 2009-------*
    * @method  CwmsSearchWidgetIf::SetSearchButtonVisibility // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bVisiible                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Aug 18:09:04 2009----------*/
    void SetSearchButtonVisibility(bool p_bVisiible);

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:03:12 2013-------*
    * @method  CwmsSearchWidgetIf::FillDefaultMembers        // private                           *
    * @return  void                                          //                                   *
    * @param   const CdmClass* p_pCdmClass                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:03:12 2013----------*/
    void FillDefaultMembers();

   public:
   /** +-=---------------------------------------------------------Do 6. Sep 19:12:21 2012--------*
    * @method  CwmsSearchWidgetIf::CreateQuery               // public                            *
    * @return  void                                          //                                   *
    * @param   CdmQuery& p_rCdmQuery                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 19:12:21 2012-----------*/
    void CreateQuery(CdmQuery& p_rCdmQuery);
};

#endif // // CWMSSEARCHWIDGETIF_H
