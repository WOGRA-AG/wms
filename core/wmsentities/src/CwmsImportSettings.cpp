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

CwmsImportSettings::CwmsImportSettings()
: m_eWmsImportMode(eWmsImportModeOverwrite),
  m_eWmsImportType(eWmsImportTypeCsv),
  m_eWmsLineBreak(eWmsLineBreakWindows),
  m_lContainerId(0),
  m_lDbId(0),
  m_bIgnoreFirstLine(false),
  m_bIgnoreLastLine(false)
{
}

CwmsImportSettings::~CwmsImportSettings()
{
}

void CwmsImportSettings::SetImportMode(EwmsImportMode p_eWmsImportMode)
{
   m_eWmsImportMode = p_eWmsImportMode;
}

EwmsImportMode CwmsImportSettings::GetImportMode()
{
   return m_eWmsImportMode;
}

void CwmsImportSettings::SetImportType(EwmsImportType p_eWmsIMportType)
{
   m_eWmsImportType = p_eWmsIMportType;
}

EwmsImportType CwmsImportSettings::GetImportType()
{
   return m_eWmsImportType;
}

void CwmsImportSettings::SetLineBreak(EwmsLineBreak p_eWmsLineBreak)
{
   m_eWmsLineBreak = p_eWmsLineBreak;
}

EwmsLineBreak CwmsImportSettings::GetLineBreak()
{
   return m_eWmsLineBreak;
}

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

QString CwmsImportSettings::GetCsvSeperator()
{
   return m_qstrCsvSeparator;
}

void CwmsImportSettings::SetStringEnclosing(QString p_qstrStringEnclosing)
{
   m_qstrStringEnclosing = p_qstrStringEnclosing;
}

QString CwmsImportSettings::GetStringEnclosing()
{
   return m_qstrStringEnclosing;
}

QString CwmsImportSettings::GetFilename()
{
   return m_qstrFilename;
}

void CwmsImportSettings::SetFilename(QString p_qstrFilename)
{
   m_qstrFilename = p_qstrFilename;
}

void CwmsImportSettings::SetContainer(CdmObjectContainer* p_pContainer)
{
   if (CHKPTR(p_pContainer))
   {
      m_lContainerId = p_pContainer->GetId();
      m_lDbId = p_pContainer->GetSchemeId();
      m_lClassId = p_pContainer->GetClassId();
      m_qstrDbName = p_pContainer->GetSchemeName();
   }
}

qint64 CwmsImportSettings::GetClassId()
{
   return m_lClassId;
}

qint64 CwmsImportSettings::GetContainerId()
{
   return m_lContainerId;
}

CdmObjectContainer* CwmsImportSettings::GetContainer()
{
   CdmObjectContainer* pList = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      pList = pManager->GetObjectContainer(GetDatabaseId(), GetContainerId());
   }

   return pList;
}

qint64 CwmsImportSettings::GetDatabaseId()
{
   return m_lDbId;
}

QString CwmsImportSettings::GetDatabaseName()
{
   return m_qstrDbName;
}

void CwmsImportSettings::SetApplication(QString p_qstrApplication)
{
   m_qstrApplication = p_qstrApplication;
}

QString CwmsImportSettings::GetApplication()
{
   return m_qstrApplication;
}

void CwmsImportSettings::SetLogin(QString p_qstrLogin)
{
   m_qstrLogin = p_qstrLogin;
}

QString CwmsImportSettings::GetLogin()
{
   return m_qstrLogin;
}

void CwmsImportSettings::SetPassword(QString p_qstrPassword)
{
   m_qstrPassword = p_qstrPassword;
}

QString CwmsImportSettings::GetPassword()
{
   return m_qstrPassword;
}

void CwmsImportSettings::SetSettingName(QString p_qstrName)
{
   m_qstrSettingsName = p_qstrName;
}

void CwmsImportSettings::SetPreprocessorCall(QString p_qstrFunction)
{
   m_qstrPreProcessorCall = p_qstrFunction;
}

QString CwmsImportSettings::GetPreprocessorCall() const
{
    return m_qstrPreProcessorCall;
}

void CwmsImportSettings::SetPostprocessorCall(QString p_qstrFunction)
{
    m_qstrPostProcessorCall = p_qstrFunction;
}

QString CwmsImportSettings::GetPostprocessorCall() const
{
    return m_qstrPostProcessorCall;
}

QString CwmsImportSettings::GetSettingsName() const
{
   return m_qstrSettingsName;
}

void CwmsImportSettings::SetIgnoreFirstLine(bool p_bIgnore)
{
   m_bIgnoreFirstLine = p_bIgnore;
}

bool CwmsImportSettings::GetIgnoreFirstLine()
{
   return m_bIgnoreFirstLine;
}

void CwmsImportSettings::SetIgnoreLastLine(bool p_bIgnore)
{
   m_bIgnoreLastLine = p_bIgnore;
}

bool CwmsImportSettings::GetIgnoreLastLine()
{
   return m_bIgnoreLastLine;
}

void CwmsImportSettings::AddColumn(CwmsImportSettingsColumn* p_pCwmsColumn)
{
   m_qlColumns.append(p_pCwmsColumn);
}

void CwmsImportSettings::RemoveColumn(int p_iColumn)
{
   CwmsImportSettingsColumn* pColumn = m_qlColumns.takeAt(p_iColumn);

   if (pColumn)
   {
      DELPTR(pColumn);
   }
}

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

void CwmsImportSettings::GetColumns(QList<CwmsImportSettingsColumn*>& p_rqlList)
{
   p_rqlList = m_qlColumns;
}

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
   cCwmsImportSettingsHandler.SetString(IMPORT_MODE, "PreprocessorCall", m_qstrPreProcessorCall);
   cCwmsImportSettingsHandler.SetString(IMPORT_MODE, "PostprocessorCall", m_qstrPostProcessorCall);
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
   cCwmsImportSettingsHandler.SetInteger(DB_MODE, "Objectlist",     m_lContainerId);
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

void CwmsImportSettings::LoadSettings(QString p_qstrName,qint64 p_lClassId)
{
   SetSettingName(p_qstrName);
   CwmsImExportManager cManager;
   QString qstrConfig = cManager.GetImportConfiguration(p_qstrName, p_lClassId);
   LoadSettings(p_qstrName, qstrConfig);
}

void CwmsImportSettings::LoadSettings(QString p_qstrName, QString p_qstrConfiguration)
{
   SetSettingName(p_qstrName);
   CwmsImExportSettingsHandler cCwmsSettingsHandler;
   cCwmsSettingsHandler.Load(p_qstrName, p_qstrConfiguration);

   if (m_lDbId == 0)
   {
      m_lDbId =            cCwmsSettingsHandler.GetInteger(DB_MODE,"DbId",         0);
   }
   
   if (m_lContainerId == 0)
   {
      m_lContainerId =    cCwmsSettingsHandler.GetInteger(DB_MODE, "Objectlist",   0);
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
   m_qstrPreProcessorCall   = cCwmsSettingsHandler.GetString(IMPORT_MODE, "PreprocessorCall", "");
   m_qstrPostProcessorCall   = cCwmsSettingsHandler.GetString(IMPORT_MODE, "PostprocessorCall", "");
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

void CwmsImportSettings::ClearMembers()
{
   for (int iCounter = 0; iCounter < m_qlColumns.count(); ++iCounter)
   {
      CwmsImportSettingsColumn* pCwmsColumn = m_qlColumns[iCounter];
      DELPTR(pCwmsColumn);
   }

   m_qlColumns.clear();
}

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
