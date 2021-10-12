/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportSettings.h
 ** Started Implementation: 2008/10/14
 ** Description:
 ** 
 ** This class implements the settings for the import.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORTSETTINGS_H
#define CWMSIMPORTSETTINGS_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <QList>
#include <QString>

// Own Includes
#include "basetools.h"

// Forwards
class CdmObjectContainer;
class CdmScheme;
class CwmsImportSettingsColumn;

// Enumerations
enum EwmsImportType
{
   eWmsImportTypeCsv,
   eWmsImportTypeText
};

enum EwmsLineBreak
{
   eWmsLineBreakWindows,
   eWmsLineBreakLinux
};

enum EwmsImportMode
{
   eWmsImportModeUpdate,
   eWmsImportModeAppend,
   eWmsImportModeOverwrite
};


/* 
 * This class implements the settings for the import.
 */
class BASETOOLS_API CwmsImportSettings
{

   private:
      EwmsImportMode m_eWmsImportMode;
      EwmsImportType m_eWmsImportType;
      EwmsLineBreak  m_eWmsLineBreak;

      QString m_qstrCsvSeparator;
      QString m_qstrStringEnclosing;
      QString m_qstrFilename;
      QString m_qstrApplication;
      QString m_qstrLogin;
      QString m_qstrPassword;
     qint64 m_lObjectListId;
     qint64 m_lDbId;
     qint64 m_lClassId;
      QString m_qstrDbName;
      QString m_qstrSettingsName;
      bool m_bIgnoreFirstLine;
      bool m_bIgnoreLastLine;
      QString m_qstrFunctionCall;
      QString m_qstrEncoding;
      QList<CwmsImportSettingsColumn*> m_qlColumns;
      



   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:20:34 2008-------*
    * @method  CwmsImportSettings::CwmsImportSettings        // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:20:34 2008----------*/
    CwmsImportSettings( );

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:20:43 2008-------*
    * @method  CwmsImportSettings::~CwmsImportSettings       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImportSettings                                         *
    *----------------last changed: -----------------------------Mo 20. Okt 19:20:43 2008----------*/
    virtual ~CwmsImportSettings( );

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:22:59 2008-------*
    * @method  CwmsImportSettings::SetImportMode             // public                            *
    * @return  void                                          //                                   *
    * @param   EwmsImportMode p_eWmsImportMode               //                                   *
    * @comment Tis method sets the import mode.                                                   *
    *----------------last changed: -----------------------------Mo 20. Okt 19:22:59 2008----------*/
    void SetImportMode(EwmsImportMode p_eWmsImportMode);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:23:23 2008-------*
    * @method  CwmsImportSettings::GetImportMode             // public                            *
    * @return  EwmsImportMode                                //                                   *
    * @comment This method returns the importmode.                                                *
    *----------------last changed: -----------------------------Mo 20. Okt 19:23:23 2008----------*/
    EwmsImportMode GetImportMode();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:24:44 2008-------*
    * @method  CwmsImportSettings::SetImportType             // public                            *
    * @return  void                                          //                                   *
    * @param   EwmsImportType p_eWmsIMportType               //                                   *
    * @comment This method returns the importtype.                                                *
    *----------------last changed: -----------------------------Mo 20. Okt 19:24:44 2008----------*/
    void SetImportType(EwmsImportType p_eWmsIMportType);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:25:16 2008-------*
    * @method  CwmsImportSettings::GetImportType             // public                            *
    * @return  EwmsImportType                                //                                   *
    * @comment This method returns the importtype.                                                *
    *----------------last changed: -----------------------------Mo 20. Okt 19:25:16 2008----------*/
    EwmsImportType GetImportType();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:26:31 2008-------*
    * @method  CwmsImportSettings::SetLineBreak              // public                            *
    * @return  void                                          //                                   *
    * @param   EwmsLineBreak p_eWmsLineBreak                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:26:31 2008----------*/
    void SetLineBreak(EwmsLineBreak p_eWmsLineBreak);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:26:51 2008-------*
    * @method  CwmsImportSettings::GetLineBreak              // public                            *
    * @return  EwmsLineBreak                                 //                                   *
    * @comment returns the linebreak.                                                             *
    *----------------last changed: -----------------------------Mo 20. Okt 19:26:51 2008----------*/
    EwmsLineBreak GetLineBreak();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:37:21 2008-------*
    * @method  CwmsImportSettings::SetCsvSeperator           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrSeperator                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:37:21 2008----------*/
    void SetCsvSeperator(QString p_qstrSeperator);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:37:33 2008-------*
    * @method  CwmsImportSettings::GetCsvSeperator           // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:37:33 2008----------*/
    QString GetCsvSeperator();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:38:12 2008-------*
    * @method  CwmsImportSettings::SetStringEnclosing        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrStringEnclosing                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:38:12 2008----------*/
    void SetStringEnclosing(QString p_qstrStringEnclosing);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:38:26 2008-------*
    * @method  CwmsImportSettings::GetStringEnclosing        // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:38:26 2008----------*/
    QString GetStringEnclosing();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:39:12 2008-------*
    * @method  CwmsImportSettings::SetFilename               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:39:12 2008----------*/
    void SetFilename(QString p_qstrFilename);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:39:29 2008-------*
    * @method  CwmsImportSettings::GetFilename               // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:39:29 2008----------*/
    QString GetFilename();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 19:40:20 2008-------*
    * @method  CwmsImportSettings::SetObjectList             // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 19:40:20 2008----------*/
    void SetObjectList(CdmObjectContainer* p_pContainer);

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 17:54:54 2008-------*
    * @method  CwmsImportSettings::GetObjectListId           // public                            *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 17:54:54 2008----------*/
   qint64 GetObjectListId();

   public:
   /** +-=---------------------------------------------------------So 26. Okt 13:44:29 2008-------*
    * @method  CwmsImportSettings::AddColumn                 // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsImportSettingsColumn* p_pCwmsColumn       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 13:44:29 2008----------*/
    void AddColumn(CwmsImportSettingsColumn* p_pCwmsColumn);

   public:
   /** +-=---------------------------------------------------------So 26. Okt 13:44:21 2008-------*
    * @method  CwmsImportSettings::RemoveColumn              // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iColumn                                 //                                   *
    * @comment removes the column.                                                                *
    *----------------last changed: -----------------------------So 26. Okt 13:44:21 2008----------*/
    void RemoveColumn(int p_iColumn);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:04:50 2008-------*
    * @method  CwmsImportSettings::GetColumns                // public                            *
    * @return  void                                          //                                   *
    * @param   QList<CwmsImportSettingsColumn*>& p_rqlList   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:04:50 2008----------*/
    void GetColumns(QList<CwmsImportSettingsColumn*>& p_rqlList);

   public:
   /** +-=---------------------------------------------------------So 26. Okt 13:44:12 2008-------*
    * @method  CwmsImportSettings::MoveUp                    // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iColumn                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 13:44:12 2008----------*/
    void MoveUp(int p_iColumn);

   public:
   /** +-=---------------------------------------------------------So 26. Okt 13:44:00 2008-------*
    * @method  CwmsImportSettings::MoveDown                  // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iColumn                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 26. Okt 13:44:00 2008----------*/
    void MoveDown(int p_iColumn);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 10:56:08 2013--------*
    * @method  CwmsImportSettings::SaveSettings              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 10:56:08 2013-----------*/
    void SaveSettings(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 12:08:55 2013--------*
    * @method  CwmsImportSettings::LoadSettings              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QString p_qstrConfiguration                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 12:08:55 2013-----------*/
    void LoadSettings(QString p_qstrName, QString p_qstrConfiguration);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:41:38 2008-------*
    * @method  CwmsImportSettings::SetApplication            // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:41:38 2008----------*/
    void SetApplication(QString p_qstrApplication);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:41:51 2008-------*
    * @method  CwmsImportSettings::GetApplication            // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:41:51 2008----------*/
    QString GetApplication();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:42:24 2008-------*
    * @method  CwmsImportSettings::SetLogin                  // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:42:24 2008----------*/
    void SetLogin(QString p_qstrLogin);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:42:37 2008-------*
    * @method  CwmsImportSettings::GetLogin                  // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:42:37 2008----------*/
    QString GetLogin();

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:43:20 2008-------*
    * @method  CwmsImportSettings::SetPassword               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:43:20 2008----------*/
    void SetPassword(QString p_qstrPassword);

   public:
   /** +-=---------------------------------------------------------Mo 20. Okt 20:43:35 2008-------*
    * @method  CwmsImportSettings::GetPassword               // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Okt 20:43:35 2008----------*/
    QString GetPassword();

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 17:55:21 2008-------*
    * @method  CwmsImportSettings::GetDatabaseId             // public                            *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 17:55:21 2008----------*/
   qint64 GetDatabaseId();

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 17:55:34 2008-------*
    * @method  CwmsImportSettings::GetDatabaseName           // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 17:55:34 2008----------*/
    QString GetDatabaseName();

   private:
   /** +-=---------------------------------------------------------Di 21. Okt 18:17:43 2008-------*
    * @method  CwmsImportSettings::ClearMembers              // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 18:17:43 2008----------*/
    void ClearMembers();

   public:
   /** +-=---------------------------------------------------------Di 4. Nov 18:07:46 2008--------*
    * @method  CwmsImportSettings::ColumnsValidForTextImport // public                            *
    * @return  bool                                          //                                   *
    * @comment This method checks if all columns are valid for textimports.                       *
    *----------------last changed: -----------------------------Di 4. Nov 18:07:46 2008-----------*/
    bool ColumnsValidForTextImport();

   public:
   /** +-=---------------------------------------------------------Di 4. Nov 18:10:10 2008--------*
    * @method  CwmsImportSettings::HasUpdateRelevantColumn   // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Nov 18:10:10 2008-----------*/
    bool HasUpdateRelevantColumn();

   public:
   /** +-=---------------------------------------------------------Di 4. Nov 18:12:19 2008--------*
    * @method  CwmsImportSettings::HasNonUpdateRelevantColumn // public                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Nov 18:12:19 2008-----------*/
    bool HasNonUpdateRelevantColumn();

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 11:11:28 2013--------*
    * @method  CwmsImportSettings::GetClassId                // public                            *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 11:11:28 2013-----------*/
   qint64 GetClassId();

   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 12:09:28 2013--------*
    * @method  CwmsImportSettings::LoadSettings              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 12:09:28 2013-----------*/
    void LoadSettings(QString p_qstrName,qint64 p_lClassId);

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 10:09:04 2013--------*
    * @method  CwmsImportSettings::SetSettingName            // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 10:09:04 2013-----------*/
    void SetSettingName(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 10:09:08 2013--------*
    * @method  CwmsImportSettings::GetSettingsName           // public, const                     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 10:09:08 2013-----------*/
    QString GetSettingsName() const;

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 10:26:37 2013--------*
    * @method  CwmsImportSettings::GetObjectList             // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 10:26:37 2013-----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 12:17:47 2013--------*
    * @method  CwmsImportSettings::SetIgnoreFirstLine        // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bIgnore                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 12:17:47 2013-----------*/
    void SetIgnoreFirstLine(bool p_bIgnore);

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 12:18:12 2013--------*
    * @method  CwmsImportSettings::GetIgnoreFirstLine        // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 12:18:12 2013-----------*/
    bool GetIgnoreFirstLine();

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 12:18:36 2013--------*
    * @method  CwmsImportSettings::SetIgnoreLastLine         // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bIgnore                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 12:18:36 2013-----------*/
    void SetIgnoreLastLine(bool p_bIgnore);

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 12:18:40 2013--------*
    * @method  CwmsImportSettings::GetIgnoreLastLine         // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 12:18:40 2013-----------*/
    bool GetIgnoreLastLine();
    void SetFunctionCall(QString p_qstrFunction);
    QString GetFunctionCall() const;
    void SetEncoding(QString p_qstrEncoding);
    QString GetEncoding();
};

#endif //
