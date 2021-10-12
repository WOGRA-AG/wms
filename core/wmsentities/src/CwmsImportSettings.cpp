/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportSettings.cpp
 ** Started Implementation: 2008/10/14
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QString>

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmMember.h"

// Own Includes
#include "CwmsImExportManager.h"
#include "CwmsImExportSettingsHandler.h"
#include "CwmsImportSettings.h"
#include "CwmsImportSettingsColumn.h"

// DEFINES

#define IMPORT_MODE "Import"
#define DB_MODE "DB"

/** +-=---------------------------------------------------------Mo 20. Okt 19:20:34 2008----------*
 * @method  CwmsImportSettings::CwmsImportSettings           // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:20:34 2008----------*/
CwmsImportSettings::CwmsImportSettings()
: m_eWmsImportMode(eWmsImportModeOverwrite),
  m_eWmsImportType(eWmsImportTypeCsv),
  m_eWmsLineBreak(eWmsLineBreakWindows),
  m_lObjectListId(0),
  m_lDbId(0),
  m_bIgnoreFirstLine(false),
  m_bIgnoreLastLine(false)
{
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:20:43 2008----------*
 * @method  CwmsImportSettings::~CwmsImportSettings          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportSettings                                            *
 *----------------last changed: --------------------------------Mo 20. Okt 19:20:43 2008----------*/
CwmsImportSettings::~CwmsImportSettings()
{
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:22:59 2008----------*
 * @method  CwmsImportSettings::SetImportMode                // public                            *
 * @return  void                                             //                                   *
 * @param   EwmsImportMode p_eWmsImportMode                  //                                   *
 * @comment Tis method sets the import mode.                                                      *
 *----------------last changed: --------------------------------Mo 20. Okt 19:22:59 2008----------*/
void CwmsImportSettings::SetImportMode(EwmsImportMode p_eWmsImportMode)
{
   m_eWmsImportMode = p_eWmsImportMode;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:23:23 2008----------*
 * @method  CwmsImportSettings::GetImportMode                // public                            *
 * @return  EwmsImportMode                                   //                                   *
 * @comment This method returns the importmode.                                                   *
 *----------------last changed: --------------------------------Mo 20. Okt 19:23:23 2008----------*/
EwmsImportMode CwmsImportSettings::GetImportMode()
{
   return m_eWmsImportMode;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:24:44 2008----------*
 * @method  CwmsImportSettings::SetImportType                // public                            *
 * @return  void                                             //                                   *
 * @param   EwmsImportType p_eWmsIMportType                  //                                   *
 * @comment This method returns the importtype.                                                   *
 *----------------last changed: --------------------------------Mo 20. Okt 19:24:44 2008----------*/
void CwmsImportSettings::SetImportType(EwmsImportType p_eWmsIMportType)
{
   m_eWmsImportType = p_eWmsIMportType;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:25:16 2008----------*
 * @method  CwmsImportSettings::GetImportType                // public                            *
 * @return  EwmsImportType                                   //                                   *
 * @comment This method returns the importtype.                                                   *
 *----------------last changed: --------------------------------Mo 20. Okt 19:25:16 2008----------*/
EwmsImportType CwmsImportSettings::GetImportType()
{
   return m_eWmsImportType;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:26:31 2008----------*
 * @method  CwmsImportSettings::SetLineBreak                 // public                            *
 * @return  void                                             //                                   *
 * @param   EwmsLineBreak p_eWmsLineBreak                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:26:31 2008----------*/
void CwmsImportSettings::SetLineBreak(EwmsLineBreak p_eWmsLineBreak)
{
   m_eWmsLineBreak = p_eWmsLineBreak;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:26:51 2008----------*
 * @method  CwmsImportSettings::GetLineBreak                 // public                            *
 * @return  EwmsLineBreak                                    //                                   *
 * @comment returns the linebreak.                                                                *
 *----------------last changed: --------------------------------Mo 20. Okt 19:26:51 2008----------*/
EwmsLineBreak CwmsImportSettings::GetLineBreak()
{
   return m_eWmsLineBreak;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:37:21 2008----------*
 * @method  CwmsImportSettings::SetCsvSeperator              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSeperator                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:37:21 2008----------*/
void CwmsImportSettings::SetCsvSeperator(QString p_qstrSeperator)
{
   m_qstrCsvSeparator = p_qstrSeperator;
}

void CwmsImportSettings::SetEncoding(QString p_qstrEncoding)
{
   m_qstrEncoding = p_qstrEncoding;
}

QString CwmsImportSettings::GetEncoding()
{
   return m_qstrEncoding;
}


/** +-=---------------------------------------------------------Mo 20. Okt 19:37:33 2008----------*
 * @method  CwmsImportSettings::GetCsvSeperator              // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:37:33 2008----------*/
QString CwmsImportSettings::GetCsvSeperator()
{
   return m_qstrCsvSeparator;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:38:12 2008----------*
 * @method  CwmsImportSettings::SetStringEnclosing           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrStringEnclosing                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:38:12 2008----------*/
void CwmsImportSettings::SetStringEnclosing(QString p_qstrStringEnclosing)
{
   m_qstrStringEnclosing = p_qstrStringEnclosing;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:38:26 2008----------*
 * @method  CwmsImportSettings::GetStringEnclosing           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:38:26 2008----------*/
QString CwmsImportSettings::GetStringEnclosing()
{
   return m_qstrStringEnclosing;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:39:29 2008----------*
 * @method  CwmsImportSettings::GetFilename                  // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:39:29 2008----------*/
QString CwmsImportSettings::GetFilename()
{
   return m_qstrFilename;
}


/** +-=---------------------------------------------------------Mo 20. Okt 19:39:12 2008----------*
 * @method  CwmsImportSettings::SetFilename                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:39:12 2008----------*/
void CwmsImportSettings::SetFilename(QString p_qstrFilename)
{
   m_qstrFilename = p_qstrFilename;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:40:20 2008----------*
 * @method  CwmsImportSettings::SetObjectList                // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 19:40:20 2008----------*/
void CwmsImportSettings::SetObjectList(CdmObjectContainer* p_pContainer)
{
   if (CHKPTR(p_pContainer))
   {
      m_lObjectListId = p_pContainer->GetId();
      m_lDbId = p_pContainer->GetSchemeId();
      m_lClassId = p_pContainer->GetClassId();
      m_qstrDbName = p_pContainer->GetSchemeName();
   }
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:11:28 2013-----------*
 * @method  CwmsImportSettings::GetClassId                   // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 11:11:28 2013-----------*/
qint64 CwmsImportSettings::GetClassId()
{
   return m_lClassId;
}

/** +-=---------------------------------------------------------Di 21. Okt 17:54:54 2008----------*
 * @method  CwmsImportSettings::GetObjectListId              // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 17:54:54 2008----------*/
qint64 CwmsImportSettings::GetObjectListId()
{
   return m_lObjectListId;
}

/** +-=---------------------------------------------------------Do 7. Feb 10:26:37 2013-----------*
 * @method  CwmsImportSettings::GetObjectList                // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 10:26:37 2013-----------*/
CdmObjectContainer* CwmsImportSettings::GetObjectList()
{
   CdmObjectContainer* pList = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      pList = pManager->GetObjectContainer(GetDatabaseId(), GetObjectListId());
   }

   return pList;
}

/** +-=---------------------------------------------------------Di 21. Okt 17:55:21 2008----------*
 * @method  CwmsImportSettings::GetDatabaseId                // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 17:55:21 2008----------*/
qint64 CwmsImportSettings::GetDatabaseId()
{
   return m_lDbId;
}

/** +-=---------------------------------------------------------Di 21. Okt 17:55:34 2008----------*
 * @method  CwmsImportSettings::GetDatabaseName              // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 17:55:34 2008----------*/
QString CwmsImportSettings::GetDatabaseName()
{
   return m_qstrDbName;
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:41:38 2008----------*
 * @method  CwmsImportSettings::SetApplication               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:41:38 2008----------*/
void CwmsImportSettings::SetApplication(QString p_qstrApplication)
{
   m_qstrApplication = p_qstrApplication;
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:41:51 2008----------*
 * @method  CwmsImportSettings::GetApplication               // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:41:51 2008----------*/
QString CwmsImportSettings::GetApplication()
{
   return m_qstrApplication;
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:42:24 2008----------*
 * @method  CwmsImportSettings::SetLogin                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:42:24 2008----------*/
void CwmsImportSettings::SetLogin(QString p_qstrLogin)
{
   m_qstrLogin = p_qstrLogin;
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:42:37 2008----------*
 * @method  CwmsImportSettings::GetLogin                     // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:42:37 2008----------*/
QString CwmsImportSettings::GetLogin()
{
   return m_qstrLogin;
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:43:20 2008----------*
 * @method  CwmsImportSettings::SetPassword                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:43:20 2008----------*/
void CwmsImportSettings::SetPassword(QString p_qstrPassword)
{
   m_qstrPassword = p_qstrPassword;
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:43:35 2008----------*
 * @method  CwmsImportSettings::GetPassword                  // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:43:35 2008----------*/
QString CwmsImportSettings::GetPassword()
{
   return m_qstrPassword;
}

/** +-=---------------------------------------------------------Do 7. Feb 10:09:04 2013-----------*
 * @method  CwmsImportSettings::SetSettingName               // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 10:09:04 2013-----------*/
void CwmsImportSettings::SetSettingName(QString p_qstrName)
{
   m_qstrSettingsName = p_qstrName;
}

void CwmsImportSettings::SetFunctionCall(QString p_qstrFunction)
{
   m_qstrFunctionCall = p_qstrFunction;
}

QString CwmsImportSettings::GetFunctionCall() const
{
   return m_qstrFunctionCall;
}

/** +-=---------------------------------------------------------Do 7. Feb 10:09:08 2013-----------*
 * @method  CwmsImportSettings::GetSettingsName              // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 10:09:08 2013-----------*/
QString CwmsImportSettings::GetSettingsName() const
{
   return m_qstrSettingsName;
}

/** +-=---------------------------------------------------------Do 7. Feb 12:17:47 2013-----------*
 * @method  CwmsImportSettings::SetIgnoreFirstLine           // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bIgnore                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 12:17:47 2013-----------*/
void CwmsImportSettings::SetIgnoreFirstLine(bool p_bIgnore)
{
   m_bIgnoreFirstLine = p_bIgnore;
}

/** +-=---------------------------------------------------------Do 7. Feb 12:18:12 2013-----------*
 * @method  CwmsImportSettings::GetIgnoreFirstLine           // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 12:18:12 2013-----------*/
bool CwmsImportSettings::GetIgnoreFirstLine()
{
   return m_bIgnoreFirstLine;
}

/** +-=---------------------------------------------------------Do 7. Feb 12:18:36 2013-----------*
 * @method  CwmsImportSettings::SetIgnoreLastLine            // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bIgnore                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 12:18:36 2013-----------*/
void CwmsImportSettings::SetIgnoreLastLine(bool p_bIgnore)
{
   m_bIgnoreLastLine = p_bIgnore;
}

/** +-=---------------------------------------------------------Do 7. Feb 12:18:40 2013-----------*
 * @method  CwmsImportSettings::GetIgnoreLastLine            // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 12:18:40 2013-----------*/
bool CwmsImportSettings::GetIgnoreLastLine()
{
   return m_bIgnoreLastLine;
}

/** +-=---------------------------------------------------------So 26. Okt 13:44:29 2008----------*
 * @method  CwmsImportSettings::AddColumn                    // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsImportSettingsColumn* p_pCwmsColumn          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 13:44:29 2008----------*/
void CwmsImportSettings::AddColumn(CwmsImportSettingsColumn* p_pCwmsColumn)
{

   m_qlColumns.append(p_pCwmsColumn);
}

/** +-=---------------------------------------------------------So 26. Okt 13:44:21 2008----------*
 * @method  CwmsImportSettings::RemoveColumn                 // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iColumn                                    //                                   *
 * @comment removes the column.                                                                   *
 *----------------last changed: --------------------------------So 26. Okt 13:44:21 2008----------*/
void CwmsImportSettings::RemoveColumn(int p_iColumn)
{
   CwmsImportSettingsColumn* pColumn = m_qlColumns.takeAt(p_iColumn);

   if (pColumn)
   {
      DELPTR(pColumn);
   }
}

/** +-=---------------------------------------------------------So 26. Okt 13:44:12 2008----------*
 * @method  CwmsImportSettings::MoveUp                       // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iColumn                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 13:44:12 2008----------*/
void CwmsImportSettings::MoveUp(int p_iColumn)
{
   if (p_iColumn > 0)
   {
      CwmsImportSettingsColumn* pColumn = m_qlColumns.takeAt(p_iColumn);

      if (pColumn)
      {
         m_qlColumns.insert(p_iColumn - 1, pColumn);
      }
   }
}

/** +-=---------------------------------------------------------So 26. Okt 13:44:00 2008----------*
 * @method  CwmsImportSettings::MoveDown                     // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iColumn                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 13:44:00 2008----------*/
void CwmsImportSettings::MoveDown(int p_iColumn)
{
   if (p_iColumn < m_qlColumns.count() - 1)
   {
      CwmsImportSettingsColumn* pColumn = m_qlColumns.takeAt(p_iColumn);

      if (pColumn)
      {
         m_qlColumns.insert(p_iColumn + 1, pColumn);
      }
   }
}

/** +-=---------------------------------------------------------Mo 20. Okt 20:04:50 2008----------*
 * @method  CwmsImportSettings::GetColumns                   // public                            *
 * @return  void                                             //                                   *
 * @param   QList<CwmsImportSettingsColumn*>& p_rqlList      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Okt 20:04:50 2008----------*/
void CwmsImportSettings::GetColumns(QList<CwmsImportSettingsColumn*>& p_rqlList)
{
   p_rqlList = m_qlColumns;
}



/** +-=---------------------------------------------------------Mi 6. Feb 10:56:08 2013-----------*
 * @method  CwmsImportSettings::SaveSettings                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 10:56:08 2013-----------*/
void CwmsImportSettings::SaveSettings(QString p_qstrName)
{
   SetSettingName(p_qstrName);
   CwmsImExportSettingsHandler cCwmsImportSettingsHandler;
   cCwmsImportSettingsHandler.AddKey(IMPORT_MODE);
   cCwmsImportSettingsHandler.SetInteger(IMPORT_MODE, "Mode", m_eWmsImportMode);
   cCwmsImportSettingsHandler.SetInteger(IMPORT_MODE, "Type", m_eWmsImportType);
   cCwmsImportSettingsHandler.SetInteger(IMPORT_MODE, "Linebreak", m_eWmsLineBreak);
   cCwmsImportSettingsHandler.SetString(IMPORT_MODE, "Filename", m_qstrFilename);
   cCwmsImportSettingsHandler.SetString(IMPORT_MODE, "Csv-Separator", m_qstrCsvSeparator);
   cCwmsImportSettingsHandler.SetInteger(IMPORT_MODE, "Ignore-Firstline", m_bIgnoreFirstLine);
   cCwmsImportSettingsHandler.SetInteger(IMPORT_MODE, "Ignore-Lastline", m_bIgnoreLastLine);
   cCwmsImportSettingsHandler.SetString(IMPORT_MODE, "FunctionCall", m_qstrFunctionCall);
   cCwmsImportSettingsHandler.SetString(IMPORT_MODE, "Encoding", m_qstrEncoding);
   QString qstrStringEnclosing = m_qstrStringEnclosing;

   if (qstrStringEnclosing.contains("\""))
   {
      qstrStringEnclosing = qstrStringEnclosing.replace("\"", "\\\"");
   }

   cCwmsImportSettingsHandler.SetString( "Export","StringEnclosing", qstrStringEnclosing);


   cCwmsImportSettingsHandler.AddKey(DB_MODE);
   cCwmsImportSettingsHandler.SetInteger(DB_MODE,"DbId",           m_lDbId);
   cCwmsImportSettingsHandler.SetString(DB_MODE,"ApplicationName", m_qstrApplication);
   cCwmsImportSettingsHandler.SetString(DB_MODE,"Login",           m_qstrLogin);
   cCwmsImportSettingsHandler.SetString(DB_MODE,"Password",        m_qstrPassword);
   cCwmsImportSettingsHandler.SetInteger(DB_MODE, "Objectlist",     m_lObjectListId);
   cCwmsImportSettingsHandler.SetString(DB_MODE, "DbName",         m_qstrDbName);

   cCwmsImportSettingsHandler.AddKey("Members");
   cCwmsImportSettingsHandler.SetInteger("Members","Count", m_qlColumns.count());

   for (int iCounter = 0; iCounter < m_qlColumns.count(); ++iCounter)
   {
      QString qstrKey = "Member-" + QString::number(iCounter);
      cCwmsImportSettingsHandler.AddKey(qstrKey);
      CwmsImportSettingsColumn* pCwmsColumn = m_qlColumns[iCounter];
      cCwmsImportSettingsHandler.SetString(qstrKey,"MemberPos", pCwmsColumn->GetMember());
      cCwmsImportSettingsHandler.SetInteger(qstrKey, "StartPos", pCwmsColumn->GetStartPos());
      cCwmsImportSettingsHandler.SetInteger(qstrKey, "EndPos", pCwmsColumn->GetEndPos());
      cCwmsImportSettingsHandler.SetInteger(qstrKey, "UpdateCriteria", pCwmsColumn->IsUpdateCriteria());
   }

   CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

   if (CHKPTR(pClassManager))
   {
       CdmClass* pClass = pClassManager->FindClassById(m_lClassId);
       cCwmsImportSettingsHandler.Save(p_qstrName, pClass, eWmsImExportModeImport);
   }


}

/** +-=---------------------------------------------------------Mi 6. Feb 12:09:28 2013-----------*
 * @method  CwmsImportSettings::LoadSettings                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 12:09:28 2013-----------*/
void CwmsImportSettings::LoadSettings(QString p_qstrName,qint64 p_lClassId)
{
   SetSettingName(p_qstrName);
   CwmsImExportManager cManager;
   QString qstrConfig = cManager.GetImportConfiguration(p_qstrName, p_lClassId);
   LoadSettings(p_qstrName, qstrConfig);
}

/** +-=---------------------------------------------------------Mi 6. Feb 12:08:55 2013-----------*
 * @method  CwmsImportSettings::LoadSettings                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   QString p_qstrConfiguration                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 12:08:55 2013-----------*/
void CwmsImportSettings::LoadSettings(QString p_qstrName, QString p_qstrConfiguration)
{
   SetSettingName(p_qstrName);
   CwmsImExportSettingsHandler cCwmsSettingsHandler;
   cCwmsSettingsHandler.Load(p_qstrName, p_qstrConfiguration);

   if (m_lDbId == 0)
   {
      m_lDbId =            cCwmsSettingsHandler.GetInteger(DB_MODE,"DbId",         0);
   }
   
   if (m_lObjectListId == 0)
   {
      m_lObjectListId =    cCwmsSettingsHandler.GetInteger(DB_MODE, "Objectlist",   0);
   }
   m_qstrDbName =          cCwmsSettingsHandler.GetString(DB_MODE, "DbName",          0);
   m_qstrApplication =     cCwmsSettingsHandler.GetString(DB_MODE, "ApplicationName", "");
   m_qstrLogin =           cCwmsSettingsHandler.GetString(DB_MODE, "Login",           "");
   m_qstrPassword =        cCwmsSettingsHandler.GetString(DB_MODE, "Password",        "");


   m_eWmsImportMode = (EwmsImportMode)cCwmsSettingsHandler.GetInteger(IMPORT_MODE, "Mode", eWmsImportModeOverwrite);
   m_eWmsImportType = (EwmsImportType)cCwmsSettingsHandler.GetInteger(IMPORT_MODE, "Type", eWmsImportTypeCsv);
   m_eWmsLineBreak  = (EwmsLineBreak)cCwmsSettingsHandler.GetInteger(IMPORT_MODE, "Linebreak", eWmsLineBreakWindows);
   m_qstrFilename   = cCwmsSettingsHandler.GetString(IMPORT_MODE, "Filename", "");
   m_qstrCsvSeparator = cCwmsSettingsHandler.GetString(IMPORT_MODE, "Csv-Separator", ";");
   m_qstrStringEnclosing = cCwmsSettingsHandler.GetString(IMPORT_MODE, "String-Enclosing", "\"");
   m_bIgnoreFirstLine = cCwmsSettingsHandler.GetInteger(IMPORT_MODE, "Ignore-Firstline", 0);
   m_bIgnoreLastLine = cCwmsSettingsHandler.GetInteger(IMPORT_MODE, "Ignore-Lastline", 0);
   m_qstrFunctionCall   = cCwmsSettingsHandler.GetString(IMPORT_MODE, "FunctionCall", "");
   m_qstrEncoding =        cCwmsSettingsHandler.GetString(IMPORT_MODE, "Encoding", "");

   int iCount = cCwmsSettingsHandler.GetInteger("Members", "Count", 0);
   ClearMembers();

   for (int iCounter = 0; iCounter < iCount; ++iCounter)
   {
      QString qstrKey = "Member-" + QString::number(iCounter);
      QString qstrMember = cCwmsSettingsHandler.GetString(qstrKey,"MemberPos", "");
      int iStartPos = cCwmsSettingsHandler.GetInteger(qstrKey, "StartPos", 0);
      int iEndPos = cCwmsSettingsHandler.GetInteger(qstrKey, "EndPos", 0);
      bool bUpdateCriteria = cCwmsSettingsHandler.GetInteger(qstrKey, "UpdateCriteria", 0);

      CwmsImportSettingsColumn* pCwmsColumn = new CwmsImportSettingsColumn(qstrMember, iStartPos, iEndPos, bUpdateCriteria);
      m_qlColumns.append(pCwmsColumn);
   }
}

/** +-=---------------------------------------------------------Di 21. Okt 18:17:43 2008----------*
 * @method  CwmsImportSettings::ClearMembers                 // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 18:17:43 2008----------*/
void CwmsImportSettings::ClearMembers()
{
   for (int iCounter = 0; iCounter < m_qlColumns.count(); ++iCounter)
   {
      CwmsImportSettingsColumn* pCwmsColumn = m_qlColumns[iCounter];
      DELPTR(pCwmsColumn);
   }

   m_qlColumns.clear();
}

/** +-=---------------------------------------------------------Di 4. Nov 18:07:46 2008-----------*
 * @method  CwmsImportSettings::ColumnsValidForTextImport    // public                            *
 * @return  bool                                             //                                   *
 * @comment This method checks if all columns are valid for textimports.                          *
 *----------------last changed: --------------------------------Di 4. Nov 18:07:46 2008-----------*/
bool CwmsImportSettings::ColumnsValidForTextImport()
{
   bool bRet = true;

   for (int iCounter = 0; iCounter < m_qlColumns.count(); ++iCounter)
   {
      CwmsImportSettingsColumn* pCwmsColumn = m_qlColumns[iCounter];

      if (pCwmsColumn)
      {
         if (pCwmsColumn->GetEndPos() <= pCwmsColumn->GetStartPos())
         {
            bRet = false;
            break;
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Di 4. Nov 18:10:10 2008-----------*
 * @method  CwmsImportSettings::HasUpdateRelevantColumn      // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Nov 18:10:10 2008-----------*/
bool CwmsImportSettings::HasUpdateRelevantColumn()
{
   bool bRet = false;

   for (int iCounter = 0; iCounter < m_qlColumns.count(); ++iCounter)
   {
      CwmsImportSettingsColumn* pCwmsColumn = m_qlColumns[iCounter];

      if (pCwmsColumn && pCwmsColumn->IsUpdateCriteria())
      {
         bRet = true;
         break;
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Di 4. Nov 18:12:19 2008-----------*
 * @method  CwmsImportSettings::HasNonUpdateRelevantColumn   // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Nov 18:12:19 2008-----------*/
bool CwmsImportSettings::HasNonUpdateRelevantColumn()
{
   bool bRet = false;

   for (int iCounter = 0; iCounter < m_qlColumns.count(); ++iCounter)
   {
      CwmsImportSettingsColumn* pCwmsColumn = m_qlColumns[iCounter];

      if (pCwmsColumn && !pCwmsColumn->IsUpdateCriteria())
      {
         bRet = true;
         break;
      }
   }

   return bRet;
}
