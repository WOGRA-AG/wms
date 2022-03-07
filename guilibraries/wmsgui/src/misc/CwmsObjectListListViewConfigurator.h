/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsObjectListListViewConfigurator.h
 ** Started Implementation: 2010/05/17
 ** Description:
 ** 
 ** This class implements the configurator for the listview
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSOBJECTLISTLISTVIEWCONFIGURATOR_H
#define CWMSOBJECTLISTLISTVIEWCONFIGURATOR_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes
#include <QObject>

// Own Includes


// Forwards
class CwmsObjectListListView;
class CdmObject;
class CdmObjectList;
class CdmObjectListManager;
class CdmClassManager;
class CdmClass;
class CdmValueDictIntString;
class CdmValueDictStringString;

// Enumerations

/* 
 * This class implements the configurator for the listview
 */
class CwmsObjectListListViewConfigurator : public QObject
{
   private:
      CwmsObjectListListView* m_rpCwmsListView;
      CdmObject* m_rpCdmObject;
      bool m_bUserSpecificConfiguration;


   public:
   /** +-=---------------------------------------------------------Mo 14. Feb 16:05:13 2011-------*
    * @method  CwmsObjectListListViewConfigurator::CwmsObjectListListViewConfigurator // public   *
    * @return                                                //                                   *
    * @param   CwmsObjectListListView* p_pCwmsListView       //                                   *
    * @param   bool p_bUserSpecificConfig                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 14. Feb 16:05:13 2011----------*/
    CwmsObjectListListViewConfigurator( CwmsObjectListListView* p_pCwmsListView,
                                        bool p_bUserSpecificConfig);

   public:
   /** +-=---------------------------------------------------------Mo 17. Mai 19:48:24 2010-------*
    * @method  CwmsObjectListListViewConfigurator::~CwmsObjectListListViewConfigurator // public, virtual*
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectListListViewConfigurator                         *
    *----------------last changed: -----------------------------Mo 17. Mai 19:48:24 2010----------*/
    virtual ~CwmsObjectListListViewConfigurator( );

    public slots:
         /** +-=---------------------------------------------------------So 23. Mai 10:49:14 2010-------*
    * @method  CwmsObjectListListViewConfigurator::OpenConfiguratorSlot // public, slots          *
    * @return  void                                          //                                   *
    * @comment opens the config dialog for column configuration.                                  *
    *----------------last changed: -----------------------------So 23. Mai 10:49:14 2010----------*/
void OpenConfiguratorSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 08:41:41 2010-------*
    * @method  CwmsObjectListListViewConfigurator::ConfigureListView // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 08:41:41 2010----------*/
    void ConfigureListView();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 08:44:14 2010-------*
    * @method  CwmsObjectListListViewConfigurator::CreateObjectList // private                    *
    * @return  CdmObjectList*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 08:44:14 2010----------*/
    CdmObjectList* CreateObjectList();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 08:44:51 2010-------*
    * @method  CwmsObjectListListViewConfigurator::LoadObjectList // private                      *
    * @return  CdmObjectList*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 08:44:51 2010----------*/
    CdmObjectList* LoadObjectList();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 08:47:44 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetObjectListManager // private                *
    * @return  CdmObjectListManager*                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 08:47:44 2010----------*/
    CdmObjectListManager* GetObjectListManager();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 08:48:03 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetClassManager // private                     *
    * @return  CdmClassManager*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 08:48:03 2010----------*/
    CdmClassManager* GetClassManager();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 18:03:31 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetClass  // private                           *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 18:03:31 2010----------*/
    CdmClass* GetClass();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 18:08:25 2010-------*
    * @method  CwmsObjectListListViewConfigurator::CreateClass // private                         *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 18:08:25 2010----------*/
    CdmClass* CreateClass();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 18:10:24 2010-------*
    * @method  CwmsObjectListListViewConfigurator::AddClassMembers // private                     *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 18:10:24 2010----------*/
    void AddClassMembers(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 18:27:38 2010-------*
    * @method  CwmsObjectListListViewConfigurator::CreateObject // private                        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 18:27:38 2010----------*/
    void CreateObject();

   private:
   /** +-=---------------------------------------------------------Mo 17. Mai 19:05:16 2010-------*
    * @method  CwmsObjectListListViewConfigurator::LoadConfiguration // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Mai 19:05:16 2010----------*/
    void LoadConfiguration();



   public:
   /** +-=---------------------------------------------------------Di 18. Mai 18:25:52 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetDisplayColumns // public                    *
    * @return  void                                          //                                   *
    * @param   QMap<int, QString> & p_rqmDisplayColumns      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Mai 18:25:52 2010----------*/
    void GetDisplayColumns(QMap<int, QString> & p_rqmDisplayColumns);

   public:
   /** +-=---------------------------------------------------------Di 18. Mai 18:27:41 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetColumnNames // public                       *
    * @return  void                                          //                                   *
    * @param   QMap<QString, QString> & p_rqmColumnNames     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Mai 18:27:41 2010----------*/
    void GetColumnNames(QMap<QString, QString> & p_rqmColumnNames);

   public:
   /** +-=---------------------------------------------------------Fr 21. Mai 18:04:56 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetListViewClass // public                     *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 18:04:56 2010----------*/
    CdmClass* GetListViewClass();

   public:
   /** +-=---------------------------------------------------------Fr 21. Mai 18:38:53 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetColumnNameByKeyname // public               *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 18:38:53 2010----------*/
    QString GetColumnNameByKeyname(QString p_qstrKeyname);

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 18:43:33 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetColumnNameByKeynameFromClass // private     *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 18:43:33 2010----------*/
    QString GetColumnNameByKeynameFromClass(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Fr 21. Mai 20:23:41 2010-------*
    * @method  CwmsObjectListListViewConfigurator::ClearMaps // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 20:23:41 2010----------*/
    void ClearMaps();

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 20:24:08 2010-------*
    * @method  CwmsObjectListListViewConfigurator::ClearColumnNamesMap // private                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 20:24:08 2010----------*/
    void ClearColumnNamesMap();

   private:
   /** +-=---------------------------------------------------------Fr 21. Mai 20:24:21 2010-------*
    * @method  CwmsObjectListListViewConfigurator::ClearDisplayColumnsMap // private              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Mai 20:24:21 2010----------*/
    void ClearDisplayColumnsMap();

   private:
   /** +-=---------------------------------------------------------Sa 22. Mai 13:20:15 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetColumnNamesDict // private                  *
    * @return  CdmValueDictStringString*                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 22. Mai 13:20:15 2010----------*/
    CdmValueDictStringString* GetColumnNamesDict();

   private:
   /** +-=---------------------------------------------------------Sa 22. Mai 13:20:03 2010-------*
    * @method  CwmsObjectListListViewConfigurator::GetDisplayColumnsDict // private               *
    * @return  CdmValueDictIntString*                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 22. Mai 13:20:03 2010----------*/
    CdmValueDictIntString* GetDisplayColumnsDict();

   public:
   /** +-=---------------------------------------------------------Sa 22. Mai 13:32:03 2010-------*
    * @method  CwmsObjectListListViewConfigurator::AddDisplayColumn // public                     *
    * @return  void                                          //                                   *
    * @param   int p_iPos                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 22. Mai 13:32:03 2010----------*/
    void AddDisplayColumn(int p_iPos, QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Sa 22. Mai 13:31:58 2010-------*
    * @method  CwmsObjectListListViewConfigurator::AddColumnName // public                        *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 22. Mai 13:31:58 2010----------*/
    void AddColumnName(QString p_qstrKeyname, QString p_qstrCaption);

   public:
   /** +-=---------------------------------------------------------Sa 22. Mai 13:31:35 2010-------*
    * @method  CwmsObjectListListViewConfigurator::Save      // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 22. Mai 13:31:35 2010----------*/
    void Save();

   public:
   /** +-=---------------------------------------------------------So 23. Mai 10:06:47 2010-------*
    * @method  CwmsObjectListListViewConfigurator::CustomizeListView // public                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 10:06:47 2010----------*/
    void CustomizeListView();

   private:
   /** +-=---------------------------------------------------------So 23. Mai 10:16:13 2010-------*
    * @method  CwmsObjectListListViewConfigurator::ConfigureDisplayColumns // private             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 10:16:13 2010----------*/
    void ConfigureDisplayColumns();

   private:
   /** +-=---------------------------------------------------------So 23. Mai 10:16:46 2010-------*
    * @method  CwmsObjectListListViewConfigurator::ConfigureColumnNames // private                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Mai 10:16:46 2010----------*/
    void ConfigureColumnNames();
};

#endif
