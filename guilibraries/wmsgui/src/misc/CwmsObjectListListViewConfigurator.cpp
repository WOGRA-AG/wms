/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsObjectListListViewConfigurator.cpp
 ** Started Implementation: 2010/05/17
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QLinkedList>

// WMS Includes
#include "CdmManager.h"
 #include "CdmManagerFactory.h"
#include "CdmError.h"
#include "CdmObject.h"
#include "CdmObjectList.h"
#include "CdmObjectListManager.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmQuery.h"
#include "CdmQueryElement.h"
#include "CdmDictIntString.h"
#include "CdmDictStringString.h"

// Own Includes
#include "CwmsObjectListViewConfiguratorDlg.h"
#include "CwmsObjectListListView.h"
#include "CwmsObjectListListViewConfigurator.h"

/** +-=---------------------------------------------------------Mo 14. Feb 16:05:13 2011----------*
 * @method  CwmsObjectListListViewConfigurator::CwmsObjectListListViewConfigurator // public      *
 * @return                                                   //                                   *
 * @param   CwmsObjectListListView* p_pCwmsListView          //                                   *
 * @param   bool p_bUserSpecificConfig                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 14. Feb 16:05:13 2011----------*/
CwmsObjectListListViewConfigurator::CwmsObjectListListViewConfigurator(CwmsObjectListListView* p_pCwmsListView,
                                                                       bool p_bUserSpecificConfig)
   : m_rpCwmsListView(p_pCwmsListView),
  m_rpCdmObject(NULL),
  m_bUserSpecificConfiguration(p_bUserSpecificConfig)
{


}

/** +-=---------------------------------------------------------Mo 17. Mai 19:48:24 2010----------*
 * @method  CwmsObjectListListViewConfigurator::~CwmsObjectListListViewConfigurator // public, virtual*
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectListListViewConfigurator                            *
 *----------------last changed: --------------------------------Mo 17. Mai 19:48:24 2010----------*/
CwmsObjectListListViewConfigurator::~CwmsObjectListListViewConfigurator()
{

}

/** +-=---------------------------------------------------------So 23. Mai 10:49:14 2010----------*
 * @method  CwmsObjectListListViewConfigurator::OpenConfiguratorSlot // public, slots             *
 * @return  void                                             //                                   *
 * @comment opens the config dialog for column configuration.                                     *
 *----------------last changed: --------------------------------So 23. Mai 10:49:14 2010----------*/
void CwmsObjectListListViewConfigurator::OpenConfiguratorSlot()
{
   CwmsObjectListViewConfiguratorDlg::EditColumnConfiguration(m_rpCwmsListView, this);
   m_rpCwmsListView->FillListView();
}

/** +-=---------------------------------------------------------So 23. Mai 10:06:47 2010----------*
 * @method  CwmsObjectListListViewConfigurator::CustomizeListView // public                       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 10:06:47 2010----------*/
void CwmsObjectListListViewConfigurator::CustomizeListView()
{
   LoadConfiguration();
   ConfigureListView();
}

/** +-=---------------------------------------------------------Mo 17. Mai 19:05:16 2010----------*
 * @method  CwmsObjectListListViewConfigurator::LoadConfiguration // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 19:05:16 2010----------*/
void CwmsObjectListListViewConfigurator::LoadConfiguration()
{
   if (m_rpCdmObject)
   {
      return;
   }

   CdmObjectList* pCdmObjectList = LoadObjectList();

   if (CHKPTR(pCdmObjectList))
   {
      CdmQuery cCdmQuery;
      cCdmQuery.SetDataBaseSearch();
      cCdmQuery.SetObjectList(pCdmObjectList);

      CdmQueryElement* pCdmElementAnd = new CdmQueryElement(&cCdmQuery, eDmQueryElementTypeAnd);
      cCdmQuery.SetQueryElement(pCdmElementAnd);

      CdmQueryElement* pCdmElement = new CdmQueryElement(&cCdmQuery, eDmQueryElementTypeCompare, eDmQueryCompareTypeEqual);
      pCdmElement->SetComparisonValue("Id", m_rpCwmsListView->GetId());
      pCdmElementAnd->AddChild(pCdmElement);

      int iUserId = 0;
      if (m_bUserSpecificConfiguration)
      {
         iUserId = pCdmObjectList->GetUserId();
      }

      pCdmElement = new CdmQueryElement(&cCdmQuery, eDmQueryElementTypeCompare, eDmQueryCompareTypeEqual);
      pCdmElement->SetComparisonValue("User", iUserId);
      pCdmElementAnd->AddChild(pCdmElement);

      if (cCdmQuery.Execute() > 0)
      {
         QLinkedList<long> qllResults = cCdmQuery.GetResultList();

         if (qllResults.count() > 0)
         {
            QLinkedList<long>::iterator qllIt = qllResults.begin();
            m_rpCdmObject = pCdmObjectList->FindObjectById(*qllIt);
         }
         else
         {
            CreateObject();
         }
      }
   }
}

/** +-=---------------------------------------------------------Di 18. Mai 18:20:56 2010----------*
 * @method  CwmsObjectListListViewConfigurator::ConfigureListView // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Mai 18:20:56 2010----------*/
void CwmsObjectListListViewConfigurator::ConfigureListView()
{
   if (CHKPTR(m_rpCwmsListView) && CHKPTR(m_rpCdmObject))
   {
      ConfigureDisplayColumns();
      ConfigureColumnNames();
   }
}

/** +-=---------------------------------------------------------So 23. Mai 10:16:13 2010----------*
 * @method  CwmsObjectListListViewConfigurator::ConfigureDisplayColumns // private                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 10:16:13 2010----------*/
void CwmsObjectListListViewConfigurator::ConfigureDisplayColumns()
{
   QMap<int, QString> qmDisplayColumns;
   GetDisplayColumns(qmDisplayColumns);

   if (qmDisplayColumns.count() > 0)
   {
      QMap<QString, CwmsObjectListListViewProxy*> qmProxies = m_rpCwmsListView->GetColumnProxies();
      m_rpCwmsListView->ClearColumns();

      QMap<int, QString>::iterator qmIt = qmDisplayColumns.begin();
      QMap<int, QString>::iterator qmItEnd = qmDisplayColumns.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CwmsObjectListListViewProxy* pProxy = NULL;

         if (qmProxies.contains(qmIt.value()))
         {
            pProxy = qmProxies[qmIt.value()];
         }

         if (pProxy)
         {
            m_rpCwmsListView->AddColumn(qmIt.value(), pProxy);
         }
         else
         {
            m_rpCwmsListView->AddColumn(qmIt.value());
         }
      }
   }
}

/** +-=---------------------------------------------------------So 23. Mai 10:16:46 2010----------*
 * @method  CwmsObjectListListViewConfigurator::ConfigureColumnNames // private                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 10:16:46 2010----------*/
void CwmsObjectListListViewConfigurator::ConfigureColumnNames()
{
   QMap<int, QString> qmDisplayColumns;
   GetDisplayColumns(qmDisplayColumns);
   QMap<QString, QString> qmColumnNames;
   GetColumnNames(qmColumnNames);
   QMap<QString, QString>::iterator qmItString = qmColumnNames.begin();
   QMap<QString, QString>::iterator qmItStringEnd = qmColumnNames.end();

   for (; qmItString != qmItStringEnd; ++qmItString)
   {
      int iPos = qmDisplayColumns.key(qmItString.key(), -1);

      if (iPos >= 0)
      {
         m_rpCwmsListView->setColumnText(iPos, qmItString.value());
      }
   }
}

/** +-=---------------------------------------------------------Di 18. Mai 18:27:41 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetColumnNames // public                          *
 * @return  void                                             //                                   *
 * @param   QMap<QString, QString> & p_rqmColumnNames        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Mai 18:27:41 2010----------*/
void CwmsObjectListListViewConfigurator::GetColumnNames(QMap<QString, QString> & p_rqmColumnNames)
{
   CdmValueDictStringString* pCdmValueDict = GetColumnNamesDict();

   if (CHKPTR(pCdmValueDict))
   {
      p_rqmColumnNames = pCdmValueDict->GetDict();
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 18:38:53 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetColumnNameByKeyname // public                  *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 18:38:53 2010----------*/
QString CwmsObjectListListViewConfigurator::GetColumnNameByKeyname(QString p_qstrKeyname)
{
   QString qstrRet;
   QMap<QString, QString> p_rqmColumnNames;
   GetColumnNames(p_rqmColumnNames);

   if (p_rqmColumnNames.contains(p_qstrKeyname))
   {
      qstrRet = p_rqmColumnNames[p_qstrKeyname];
   }
   else
   {
      qstrRet = GetColumnNameByKeynameFromClass(p_qstrKeyname);
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Fr 21. Mai 18:43:33 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetColumnNameByKeynameFromClass // private        *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 18:43:33 2010----------*/
QString CwmsObjectListListViewConfigurator::GetColumnNameByKeynameFromClass(QString p_qstrKeyname)
{
   QString qstrRet;
   CdmClass* pCdmClass = GetListViewClass();

   if (CHKPTR(pCdmClass))
   {
      CdmMember* pCdmMember = pCdmClass->FindMember(p_qstrKeyname, 0);

      if (CHKPTR(pCdmMember))
      {
         qstrRet = pCdmMember->GetCaption();
      }
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 22. Mai 13:32:03 2010----------*
 * @method  CwmsObjectListListViewConfigurator::AddDisplayColumn // public                        *
 * @return  void                                             //                                   *
 * @param   int p_iPos                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 22. Mai 13:32:03 2010----------*/
void CwmsObjectListListViewConfigurator::AddDisplayColumn(int p_iPos, QString p_qstrKeyname)
{
   CdmValueDictIntString* pCdmDict = GetDisplayColumnsDict();

   if (CHKPTR(pCdmDict))
   {
      pCdmDict->SetValue(p_iPos, p_qstrKeyname);
   }
}

/** +-=---------------------------------------------------------Sa 22. Mai 13:31:58 2010----------*
 * @method  CwmsObjectListListViewConfigurator::AddColumnName // public                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 22. Mai 13:31:58 2010----------*/
void CwmsObjectListListViewConfigurator::AddColumnName(QString p_qstrKeyname, QString p_qstrCaption)
{
   CdmValueDictStringString* pCdmDict = GetColumnNamesDict();

   if (CHKPTR(pCdmDict))
   {
      pCdmDict->SetValue(p_qstrKeyname, p_qstrCaption);
   }
}

/** +-=---------------------------------------------------------Sa 22. Mai 13:31:35 2010----------*
 * @method  CwmsObjectListListViewConfigurator::Save         // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 22. Mai 13:31:35 2010----------*/
void CwmsObjectListListViewConfigurator::Save()
{
   if (CHKPTR(m_rpCdmObject))
   {
      m_rpCdmObject->Commit();
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 20:23:41 2010----------*
 * @method  CwmsObjectListListViewConfigurator::ClearMaps    // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 20:23:41 2010----------*/
void CwmsObjectListListViewConfigurator::ClearMaps()
{
   ClearColumnNamesMap();
   ClearDisplayColumnsMap();
}

/** +-=---------------------------------------------------------Sa 22. Mai 13:20:15 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetColumnNamesDict // private                     *
 * @return  CdmValueDictStringString*                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 22. Mai 13:20:15 2010----------*/
CdmValueDictStringString* CwmsObjectListListViewConfigurator::GetColumnNamesDict()
{
   CdmValueDictStringString* pCdmValueDict = NULL;

   if (CHKPTR(m_rpCdmObject))
   {
      CdmValue* pCdmValue = m_rpCdmObject->GetValue("Column_Names");

      if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictStringString)
      {
         if (CHKPTR(m_rpCwmsListView) && CHKPTR(m_rpCdmObject))
         {
            pCdmValueDict = ((CdmValueDictStringString*)pCdmValue);
         }
      }
   }

   return pCdmValueDict;
}

/** +-=---------------------------------------------------------Fr 21. Mai 20:24:08 2010----------*
 * @method  CwmsObjectListListViewConfigurator::ClearColumnNamesMap // private                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 20:24:08 2010----------*/
void CwmsObjectListListViewConfigurator::ClearColumnNamesMap()
{
   CdmValueDictStringString* pCdmValueDict = GetColumnNamesDict();

   if (CHKPTR(pCdmValueDict))
   {
      pCdmValueDict->ClearDict();
   }
}

/** +-=---------------------------------------------------------Sa 22. Mai 13:20:03 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetDisplayColumnsDict // private                  *
 * @return  CdmValueDictIntString*                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 22. Mai 13:20:03 2010----------*/
CdmValueDictIntString* CwmsObjectListListViewConfigurator::GetDisplayColumnsDict()
{
   CdmValueDictIntString* pCdmValueDict = NULL;

   if (CHKPTR(m_rpCdmObject))
   {
      CdmValue* pCdmValue = m_rpCdmObject->GetValue("Display_Columns");

      if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueDictIntString)
      {
         if (CHKPTR(m_rpCwmsListView) && CHKPTR(m_rpCdmObject))
         {
            pCdmValueDict = ((CdmValueDictIntString*)pCdmValue);
         }
      }
   }

   return pCdmValueDict;
}

/** +-=---------------------------------------------------------Fr 21. Mai 20:24:21 2010----------*
 * @method  CwmsObjectListListViewConfigurator::ClearDisplayColumnsMap // private                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 20:24:21 2010----------*/
void CwmsObjectListListViewConfigurator::ClearDisplayColumnsMap()
{
   CdmValueDictIntString* pCdmValueDict = GetDisplayColumnsDict();

   if (CHKPTR(pCdmValueDict))
   {
      pCdmValueDict->ClearDict();
   }
}

/** +-=---------------------------------------------------------Di 18. Mai 18:25:52 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetDisplayColumns // public                       *
 * @return  void                                             //                                   *
 * @param   QMap<int, QString> & p_rqmDisplayColumns         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Mai 18:25:52 2010----------*/
void CwmsObjectListListViewConfigurator::GetDisplayColumns(QMap<int, QString> & p_rqmDisplayColumns)
{
   CdmValueDictIntString* pCdmValueDict = GetDisplayColumnsDict();

   if (CHKPTR(pCdmValueDict))
   {
      p_rqmDisplayColumns = pCdmValueDict->GetDict();
   }
}

/** +-=---------------------------------------------------------Mo 17. Mai 18:27:38 2010----------*
 * @method  CwmsObjectListListViewConfigurator::CreateObject // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 18:27:38 2010----------*/
void CwmsObjectListListViewConfigurator::CreateObject()
{
   CdmObjectList* pCdmObjectList = LoadObjectList();

   if (CHKPTR(pCdmObjectList))
   {
      m_rpCdmObject = pCdmObjectList->CreateNewObject();
      m_rpCdmObject->SetValue("Id", m_rpCwmsListView->GetId());
      m_rpCdmObject->SetValue("User", pCdmObjectList->GetUserId());
      m_rpCdmObject->Commit();
   }
}

/** +-=---------------------------------------------------------Mo 17. Mai 08:44:51 2010----------*
 * @method  CwmsObjectListListViewConfigurator::LoadObjectList // private                         *
 * @return  CdmObjectList*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 08:44:51 2010----------*/
CdmObjectList* CwmsObjectListListViewConfigurator::LoadObjectList()
{
   CdmObjectList* pCdmObjectList = NULL;

   CdmObjectListManager* pCdmOLManager = GetObjectListManager();

   if (CHKPTR(pCdmOLManager))
   {
      pCdmObjectList = pCdmOLManager->FindEmptyObjectListByKeyname("ObjectListViewColumnsConfigurations");

      if (!pCdmObjectList)
      {
         pCdmObjectList = CreateObjectList();
      }
   }

   return pCdmObjectList;
}

/** +-=---------------------------------------------------------Mo 17. Mai 08:47:44 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetObjectListManager // private                   *
 * @return  CdmObjectListManager*                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 08:47:44 2010----------*/
CdmObjectListManager* CwmsObjectListListViewConfigurator::GetObjectListManager()
{
   CdmObjectListManager* pCdmOLManager = NULL;

   if (CHKPTR(m_rpCwmsListView))
   {
      CdmObjectList* pCdmObjectListLV = m_rpCwmsListView->GetObjectList();

      if (CHKPTR(pCdmObjectListLV))
      {
         pCdmOLManager  = pCdmObjectListLV->GetObjectListManager();
      }
   }

   return pCdmOLManager;
}

/** +-=---------------------------------------------------------Mo 17. Mai 08:48:03 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetClassManager // private                        *
 * @return  CdmClassManager*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 08:48:03 2010----------*/
CdmClassManager* CwmsObjectListListViewConfigurator::GetClassManager()
{
   CdmClassManager* pCdmClassManager = NULL;

   if (CHKPTR(m_rpCwmsListView))
   {
      CdmObjectList* pCdmObjectListLV = m_rpCwmsListView->GetObjectList();

      if (CHKPTR(pCdmObjectListLV))
      {
         pCdmClassManager  = pCdmObjectListLV->GetClassManager();
      }
   }

   return pCdmClassManager;
}

/** +-=---------------------------------------------------------Mo 17. Mai 08:44:14 2010----------*
 * @method  CwmsObjectListListViewConfigurator::CreateObjectList // private                       *
 * @return  CdmObjectList*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 08:44:14 2010----------*/
CdmObjectList* CwmsObjectListListViewConfigurator::CreateObjectList()
{
   CdmObjectList* pCdmObjectList = NULL;
   CdmObjectListManager* pCdmOLManager = GetObjectListManager();
   CdmClass* pCdmClass = GetClass();

   if (CHKPTR(pCdmOLManager) && CHKPTR(pCdmClass))
   {
      QString qstrKeyname = "ObjectListViewColumnsConfigurations";
      pCdmOLManager->CreateObjectList(pCdmClass, qstrKeyname);
      pCdmObjectList = pCdmOLManager->FindEmptyObjectListByKeyname(qstrKeyname);
   }

   return pCdmObjectList;
}

/** +-=---------------------------------------------------------Mo 17. Mai 18:03:31 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetClass     // private                           *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 18:03:31 2010----------*/
CdmClass* CwmsObjectListListViewConfigurator::GetClass()
{
   CdmClass* pCdmClass = NULL;
   CdmClassManager* pCdmClassManager = GetClassManager();

   if (CHKPTR(pCdmClassManager))
   {
      pCdmClass = pCdmClassManager->FindClassByKeyname("ListView_Column_Configurator");

      if (!pCdmClass)
      {
         pCdmClass = CreateClass();
      }
   }

   return pCdmClass;
}

/** +-=---------------------------------------------------------Mo 17. Mai 18:08:25 2010----------*
 * @method  CwmsObjectListListViewConfigurator::CreateClass  // private                           *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 18:08:25 2010----------*/
CdmClass* CwmsObjectListListViewConfigurator::CreateClass()
{
   CdmClass* pCdmClass = NULL;
   CdmClassManager* pCdmClassManager = GetClassManager();

   if (CHKPTR(pCdmClassManager))
   {
      pCdmClassManager->CreateClass("ListView_Column_Configurator");
      pCdmClass = pCdmClassManager->FindClassByKeyname("ListView_Column_Configurator");
      AddClassMembers(pCdmClass);
   }

   return pCdmClass;
}

/** +-=---------------------------------------------------------Mo 17. Mai 18:10:24 2010----------*
 * @method  CwmsObjectListListViewConfigurator::AddClassMembers // private                        *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Mai 18:10:24 2010----------*/
void CwmsObjectListListViewConfigurator::AddClassMembers(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetCaption(tr("Listview Spalten Konfiguration"));
      p_pCdmClass->SetComment(tr("Klasse zur Speicherung der Spaltenkonfiguration eines Listviews."));

      CdmMember* pCdmMember = NULL;

      pCdmMember = p_pCdmClass->CreateMember("Id", 
                                             eDmValueInt, 
                                             FALSE, 
                                             0);
 
      if(CHKPTR(pCdmMember))
      {
         pCdmMember->SetComment(tr("Die Id des Konfigurationsobjekts."));
         pCdmMember->SetCaption(tr("Id"));
      }

      pCdmMember = p_pCdmClass->CreateMember("User", 
                                             eDmValueUser, 
                                             FALSE, 
                                             0);

      if(CHKPTR(pCdmMember))
      {
         pCdmMember->SetComment(tr("Der Anwender zu dem die Konfigurations gespeichert wurde"));
         pCdmMember->SetCaption(tr("Anwender"));
      }

      pCdmMember = p_pCdmClass->CreateMember("Column_Names", 
                                             eDmValueDictStringString, 
                                             FALSE, 
                                             0);

      if(CHKPTR(pCdmMember))
      {
         pCdmMember->SetComment(tr("Die Zuorndung der Spaltennamen"));
         pCdmMember->SetCaption(tr("Spaltennamen"));
      }

      pCdmMember = p_pCdmClass->CreateMember("Display_Columns", 
                                             eDmValueDictIntString, 
                                             FALSE, 
                                             0);

      if(CHKPTR(pCdmMember))
      {
         pCdmMember->SetComment(tr("Die dargestellten Spalten in entsprechender Reihenfolge"));
         pCdmMember->SetCaption(tr("Spaltendarstellung"));
      }

      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 18:04:56 2010----------*
 * @method  CwmsObjectListListViewConfigurator::GetListViewClass // public                        *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 18:04:56 2010----------*/
CdmClass* CwmsObjectListListViewConfigurator::GetListViewClass()
{
   CdmClass* pCdmClass = NULL;

   if (CHKPTR(m_rpCwmsListView))
   {
      CdmObjectList* pCdmObjectList = m_rpCwmsListView->GetObjectList();

      if (CHKPTR(pCdmObjectList))
      {
         pCdmClass = pCdmObjectList->GetClassPtr();
      }
   }

   return pCdmClass;
}