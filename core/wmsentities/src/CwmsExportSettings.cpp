/******************************************************************************
 ** WOGRA Middleware Tools Exportsettings Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qstring.h>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmQueryBuilder.h"


// own Includes
#include "CwmsImExportManager.h"
#include "CwmsImExportSettingsHandler.h"
#include "CwmsExportSettings.h"


/** +-=---------------------------------------------------------Do 15. Nov 23:12:40 2007----------*
 * @method  CwmsExportSettings::CwmsExportSettings           // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Do 15. Nov 23:12:40 2007----------*/
CwmsExportSettings::CwmsExportSettings()
    : m_lContainerId(0),
      m_bExportHeader(true),
      m_lSchemeId(0),
      m_lCassId(0)
{
}

/** +-=---------------------------------------------------------Do 15. Nov 23:12:50 2007----------*
 * @method  CwmsExportSettings::~CwmsExportSettings          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsExportSettings                                            *
 *----------------last changed: Wolfgang Graßhof----------------Do 15. Nov 23:12:50 2007----------*/
CwmsExportSettings::~CwmsExportSettings()
{
}

/** +-=---------------------------------------------------------Mi 9. Sep 17:55:41 2009-----------*
 * @method  CwmsExportSettings::SetExportList                // public                            *
 * @return  void                                             //                                   *
 * @param   QList<qint64> p_qllExportList                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Sep 17:55:41 2009-----------*/
void CwmsExportSettings::SetExportList(QList<qint64> p_qllExportList)
{
   m_qllExportList = p_qllExportList;
}

/** +-=---------------------------------------------------------Mi 9. Sep 18:07:15 2009-----------*
 * @method  CwmsExportSettings::GetExportList                // public                            *
 * @return  QList<qint64>                                //                                   *
 * @comment returns the exportlist.                                                               *
 *----------------last changed: --------------------------------Mi 9. Sep 18:07:15 2009-----------*/
QList<qint64> CwmsExportSettings::GetExportList()
{
   return m_qllExportList;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:10:19 2007----------*
 * @method  CwmsExportSettings::SetExportType                // public                            *
 * @return  void                                             //                                   *
 * @param   EwmsExportType p_eWmsExportType                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:10:19 2007----------*/
void CwmsExportSettings::SetExportType(EwmsExportType p_eWmsExportType)
{
   m_eWmsExportType = p_eWmsExportType;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:28:24 2007----------*
 * @method  CwmsExportSettings::GetExportType                // public, const                     *
 * @return  EwmsExportType                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:28:24 2007----------*/
EwmsExportType CwmsExportSettings::GetExportType() const
{
   return m_eWmsExportType;
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:39:47 2013-----------*
 * @method  CwmsExportSettings::SetClassId                   // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lCassId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 11:39:47 2013-----------*/
void CwmsExportSettings::SetClassId(qint64 p_lCassId)
{
	m_lCassId = p_lCassId;
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:39:59 2013-----------*
 * @method  CwmsExportSettings::GetClassId                   // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 11:39:59 2013-----------*/
qint64 CwmsExportSettings::GetClassId()
{
   return m_lCassId;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:11:23 2007----------*
 * @method  CwmsExportSettings::SetObjectListId              // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:11:23 2007----------*/
void CwmsExportSettings::SetContainerId(qint64 p_lObjectListId)
{
   m_lContainerId = p_lObjectListId;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:28:16 2007----------*
 * @method  CwmsExportSettings::GetObjectListId              // public, const                     *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:28:16 2007----------*/
qint64 CwmsExportSettings::GetContainerId() const
{
   return m_lContainerId;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:12:21 2007----------*
 * @method  CwmsExportSettings::SetExportHeader              // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bExport                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:12:21 2007----------*/
void CwmsExportSettings::SetExportHeader(bool p_bExport)
{
   m_bExportHeader = p_bExport;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:27:58 2007----------*
 * @method  CwmsExportSettings::GetExportHeader              // public, const                     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:27:58 2007----------*/
bool CwmsExportSettings::GetExportHeader() const
{
   return m_bExportHeader;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:13:09 2007----------*
 * @method  CwmsExportSettings::SetDatabaseId                // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:13:09 2007----------*/
void CwmsExportSettings::SetSchemeId(qint64 p_lDbId)
{
   m_lSchemeId = p_lDbId;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:27:52 2007----------*
 * @method  CwmsExportSettings::GetDatabaseId                // public, const                     *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:27:52 2007----------*/
qint64 CwmsExportSettings::GetSchemeId() const
{
   return m_lSchemeId;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:15:16 2007----------*
 * @method  CwmsExportSettings::SetFilename                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:15:16 2007----------*/
void CwmsExportSettings::SetFilename(QString p_qstrFilename)
{
   m_qstrFilename = p_qstrFilename;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:27:46 2007----------*
 * @method  CwmsExportSettings::GetFilename                  // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:27:46 2007----------*/
QString CwmsExportSettings::GetFilename() const
{
   return m_qstrFilename;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:16:07 2007----------*
 * @method  CwmsExportSettings::SetCsvSeperator              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSeperator                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:16:07 2007----------*/
void CwmsExportSettings::SetCsvSeperator(QString p_qstrSeperator)
{
   m_qstrCsvSeperator = p_qstrSeperator;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:28:39 2007----------*
 * @method  CwmsExportSettings::GetCsvSeperator              // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:28:39 2007----------*/
QString CwmsExportSettings::GetCsvSeperator() const
{
   return m_qstrCsvSeperator;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:20:37 2007----------*
 * @method  CwmsExportSettings::SetCsvStringEnclosing        // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCsvStringEnclosing                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:20:37 2007----------*/
void CwmsExportSettings::SetCsvStringEnclosing(QString p_qstrCsvStringEnclosing)
{
   m_qstrCsvStringEnclosing = p_qstrCsvStringEnclosing;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:27:24 2007----------*
 * @method  CwmsExportSettings::GetCsvStringEnclosing        // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:27:24 2007----------*/
QString CwmsExportSettings::GetCsvStringEnclosing() const
{
   return m_qstrCsvStringEnclosing;
}

QString CwmsExportSettings::GetEncoding() const
{
   return m_qstrEncoding;
}

void CwmsExportSettings::SetEncoding(QString p_qstrName)
{
   m_qstrEncoding = p_qstrName;
}


/** +-=---------------------------------------------------------Sa 17. Nov 13:21:55 2007----------*
 * @method  CwmsExportSettings::SetDatabaseName              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:21:55 2007----------*/
void CwmsExportSettings::SetSchemeName(QString p_qstrName)
{
   m_qstrDatabaseName = p_qstrName;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:28:50 2007----------*
 * @method  CwmsExportSettings::GetDatabaseName              // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:28:50 2007----------*/
QString CwmsExportSettings::GetSchemeName() const
{
   return m_qstrDatabaseName;
}

/** +-=---------------------------------------------------------Mi 6. Feb 16:44:35 2013-----------*
 * @method  CwmsExportSettings::ClearMembers                 // public                            *
 * @return  void                                             //                                   *
 * @comment Adds an member of the object to export.                                               *
 *----------------last changed: --------------------------------Mi 6. Feb 16:44:35 2013-----------*/
void CwmsExportSettings::ClearMembers()
{
   m_qvlMembers.clear();
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:22:35 2007----------*
 * @method  CwmsExportSettings::AddMember                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment Adds an member of the object to export.                                               *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:22:35 2007----------*/
void CwmsExportSettings::AddMember(QString p_qstrMember)
{
   if  (!m_qvlMembers.contains(p_qstrMember))
   {
      m_qvlMembers.append(p_qstrMember);
   }
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:29:46 2007----------*
 * @method  CwmsExportSettings::GetMemberList                // public, const                     *
 * @return  const QValueList<QString>&                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:29:46 2007----------*/
const QList<QString>& CwmsExportSettings::GetMemberList() const
{
   return m_qvlMembers;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:23:53 2007----------*
 * @method  CwmsExportSettings::SetQuery                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrQuery                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:23:53 2007----------*/
void CwmsExportSettings::SetQuery(QString p_qstrQuery)
{
   m_qstrQuery = p_qstrQuery;
}

/** +-=---------------------------------------------------------Mo 19. Nov 20:52:36 2007----------*
 * @method  CwmsExportSettings::SetQuery                     // public                            *
 * @return  void                                             //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Mo 19. Nov 20:52:36 2007----------*/
void CwmsExportSettings::SetQuery(CdmQuery* p_pCdmQuery)
{
   if(p_pCdmQuery)
   {
       m_qstrQuery = CdmQueryBuilder::BuildString(p_pCdmQuery);
   }
}

/** +-=---------------------------------------------------------Mo 19. Nov 20:52:54 2007----------*
 * @method  CwmsExportSettings::GetQueryObject               // public                            *
 * @return  CdmQuery*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Mo 19. Nov 20:52:54 2007----------*/
CdmQuery* CwmsExportSettings::GetQueryObject()
{
  CdmQuery* pQuery = CdmQueryBuilder::BuildQuery(m_qstrQuery);

  if (!pQuery)
  {
    ERR("Query \"" + m_qstrQuery + "\" is invalid");
  }

  return pQuery;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:26:29 2007----------*
 * @method  CwmsExportSettings::GetQuery                     // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:26:29 2007----------*/
QString CwmsExportSettings::GetQuery() const
{
   return m_qstrQuery;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:24:51 2007----------*
 * @method  CwmsExportSettings::SetLogin                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:24:51 2007----------*/
void CwmsExportSettings::SetLogin(QString p_qstrLogin)
{
   m_qstrLogin = p_qstrLogin;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:26:21 2007----------*
 * @method  CwmsExportSettings::GetLogin                     // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:26:21 2007----------*/
QString CwmsExportSettings::GetLogin()
{
   return m_qstrLogin;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:25:46 2007----------*
 * @method  CwmsExportSettings::SetPassword                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:25:46 2007----------*/
void CwmsExportSettings::SetPassword(QString p_qstrPassword)
{
    m_qstrPassword = p_qstrPassword;
}

/** +-=---------------------------------------------------------Sa 17. Nov 13:25:58 2007----------*
 * @method  CwmsExportSettings::GetPassword                  // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:25:58 2007----------*/
QString CwmsExportSettings::GetPassword() const
{
   return m_qstrPassword;
}

/** +-=---------------------------------------------------------So 18. Nov 10:02:06 2007----------*
 * @method  CwmsExportSettings::SetApplicationName           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 10:02:06 2007----------*/
void CwmsExportSettings::SetApplicationName(QString p_qstrName)
{
   m_qstrApplicationName = p_qstrName;
}

/** +-=---------------------------------------------------------So 18. Nov 10:02:38 2007----------*
 * @method  CwmsExportSettings::GetApplicationName           // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 10:02:38 2007----------*/
QString CwmsExportSettings::GetApplicationName() const
{
   return m_qstrApplicationName;
}

/** +-=---------------------------------------------------------Mi 6. Feb 16:10:35 2013-----------*
 * @method  CwmsExportSettings::SetSettingName               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 16:10:35 2013-----------*/
void CwmsExportSettings::SetSettingName(QString p_qstrName)
{
   m_qstrSettingsName = p_qstrName;
}

/** +-=---------------------------------------------------------Mi 6. Feb 16:10:52 2013-----------*
 * @method  CwmsExportSettings::GetSettingsName              // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 16:10:52 2013-----------*/
QString CwmsExportSettings::GetSettingsName() const
{
   return m_qstrSettingsName;
}

/** +-=---------------------------------------------------------Mo 21. Apr 18:28:27 2008----------*
 * @method  CwmsExportSettings::Save                         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstFilename                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Apr 18:28:27 2008----------*/
void CwmsExportSettings::Save(QString p_qstFilename)
{
   SetSettingName(p_qstFilename);
   CwmsImExportSettingsHandler cCwmsSettingsHandler;

   cCwmsSettingsHandler.AddKey("DB");

   cCwmsSettingsHandler.SetInteger("DB","DbId",            this->GetSchemeId());
   cCwmsSettingsHandler.SetString( "DB","DbName",          this->GetSchemeName());
   cCwmsSettingsHandler.SetString( "DB","ApplicationName", this->GetApplicationName());
   cCwmsSettingsHandler.SetString( "DB","Login",           this->GetLogin());
   cCwmsSettingsHandler.SetString( "DB","Password",        this->GetPassword());

   cCwmsSettingsHandler.AddKey("Export");
   
   cCwmsSettingsHandler.SetString( "Export","ExportFile",      this->GetFilename());
   cCwmsSettingsHandler.SetString( "Export","Query",           this->GetQuery());
   cCwmsSettingsHandler.SetInteger("Export","ExportType",      this->GetExportType());
   cCwmsSettingsHandler.SetInteger("Export","ObjectListId",    this->GetContainerId());
   cCwmsSettingsHandler.SetInteger("Export","ExportHeader",    this->GetExportHeader());
   cCwmsSettingsHandler.SetString( "Export","Seperator",       this->GetCsvSeperator());
   cCwmsSettingsHandler.SetString( "Export","Encoding",       this->GetEncoding());
   QString qstrStringEnclosing = this->GetCsvStringEnclosing();

//   if (qstrStringEnclosing.contains("\""))
//   {
//      qstrStringEnclosing = qstrStringEnclosing.replace("\"", "\\\"");
//   }

   cCwmsSettingsHandler.SetString( "Export","StringEnclosing", qstrStringEnclosing);
   
   
   cCwmsSettingsHandler.AddKey("Members");

   cCwmsSettingsHandler.SetInteger("Members","Count", m_qvlMembers.count());

   QList<QString>::iterator qvlIt = m_qvlMembers.begin();
   QList<QString>::iterator qvlItEnd = m_qvlMembers.end();
   
   int iCounter = 1; // for easier use by manual editing

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      
      cCwmsSettingsHandler.SetString("Members",QString::number(iCounter), (*qvlIt));
      ++iCounter;
   }

   CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

   if (CHKPTR(pClassManager))
   {
       CdmClass* pClass = pClassManager->FindClassById(m_lCassId);
       cCwmsSettingsHandler.Save(p_qstFilename, pClass, eWmsImExportModeExport);
   }
}

/** +-=---------------------------------------------------------Mi 6. Feb 14:18:25 2013-----------*
 * @method  CwmsExportSettings::Load                         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstFilename                            //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 14:18:25 2013-----------*/
void CwmsExportSettings::Load(QString p_qstFilename,qint64 p_lClassId)
{
   SetSettingName(p_qstFilename);
   CwmsImExportSettingsHandler cCwmsSettingsHandler;
   CwmsImExportManager cManager;
   QString qstrConfiguration = cManager.GetExportConfiguration(p_qstFilename, p_lClassId);
   Load(p_qstFilename, qstrConfiguration);
}


/** +-=---------------------------------------------------------Mi 6. Feb 14:16:24 2013-----------*
 * @method  CwmsExportSettings::Load                         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstFilename                            //                                   *
 * @param   QString p_qstrConfiguration                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 14:16:24 2013-----------*/
void CwmsExportSettings::Load(QString p_qstFilename, QString p_qstrConfiguration)
{
   CwmsImExportSettingsHandler cCwmsSettingsHandler;
   cCwmsSettingsHandler.Load(p_qstFilename, p_qstrConfiguration);

   m_lSchemeId =         cCwmsSettingsHandler.GetInteger("DB","DbId",             0);
   m_qstrDatabaseName =    cCwmsSettingsHandler.GetString( "DB","DbName",          "");
   m_qstrApplicationName = cCwmsSettingsHandler.GetString( "DB","ApplicationName", "");
   m_qstrLogin =           cCwmsSettingsHandler.GetString( "DB","Login",           "");
   m_qstrPassword =        cCwmsSettingsHandler.GetString( "DB","Password",        "");


   m_qstrFilename =    cCwmsSettingsHandler.GetString( "Export","ExportFile",      "");
   m_qstrQuery = cCwmsSettingsHandler.GetString( "Export","Query",           "");
   m_qstrEncoding = cCwmsSettingsHandler.GetString( "Export","Encoding",           "");
   

   m_eWmsExportType = (EwmsExportType)cCwmsSettingsHandler.GetInteger("Export","ExportType",       0);
   m_lContainerId =   cCwmsSettingsHandler.GetInteger("Export","ObjectListId",     0);
   
   if (cCwmsSettingsHandler.GetInteger("Export","ExportHeader",     0)  != 0)
   {
      m_bExportHeader = true;
   }
   else
   {
      m_bExportHeader = false;
   }

   m_qstrCsvSeperator = cCwmsSettingsHandler.GetString( "Export","Seperator",       "");
   m_qstrCsvStringEnclosing = cCwmsSettingsHandler.GetString( "Export","StringEnclosing", "");

   int iCount = cCwmsSettingsHandler.GetInteger("Members","Count", 0);
   m_qvlMembers.clear();

   for (int iCounter = 1; iCounter <= iCount; ++iCounter)
   {
      QString qstrMember = cCwmsSettingsHandler.GetString("Members", QString::number(iCounter), "");

      if (qstrMember.length() > 0)
      {
         m_qvlMembers.append(qstrMember);
      }
   }
}
