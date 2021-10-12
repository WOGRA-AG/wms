/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsExportSettingsHandler.h
 ** Started Implementation: 2008/10/20
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSEXPORTSETTINGSHANDLER_H
#define CWMSEXPORTSETTINGSHANDLER_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <QString>
#include <QVariant>

// forwards
class CdmClass;


// Enumerations

enum EwmsImExportMode
{
   eWmsImExportModeImport,
   eWmsImExportModeExport
};


class CwmsImExportSettingsHandler
{
   private:
	   QString m_qstrName;
      QVariantMap m_qvData;

   /** +-=---------------------------------------------------------Mon Aug 26 21:33:56 2002-------*
    * @method  CwmsImExportSettingsHandler::CwmsImExportSettingsHandler          // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:33:56 2002------*/
   public:
      CwmsImExportSettingsHandler(  );

   /** +-=---------------------------------------------------------Mon Aug 26 21:34:09 2002-------*
    * @method  CwmsImExportSettingsHandler::~CwmsImExportSettingsHandler         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImExportSettingsHandler                                          *
    *                                                                                             *
    *---------------------------------------------------------------Mon Aug 26 21:34:09 2002------*/
   public:
      virtual ~CwmsImExportSettingsHandler(  );
   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 12:05:30 2013--------*
    * @method  CwmsImExportSettingsHandler::Load             // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QString p_qstrContent                         //                                   *
    * @comment Loads the Sessionfile.                                                             *
    *----------------last changed: -----------------------------Mi 6. Feb 12:05:30 2013-----------*/
    bool Load(QString p_qstrName, QString p_qstrContent);
   public:
   /** +-=---------------------------------------------------------Mi 6. Feb 11:44:17 2013--------*
    * @method  CwmsImExportSettingsHandler::Save             // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param  qint64 p_lCassId                                //                                   *
    * @param   EwmsImExportMode p_eMode                      //                                   *
    * @comment Save the Sessionfile under an other filename.                                      *
    *----------------last changed: -----------------------------Mi 6. Feb 11:44:17 2013-----------*/
    bool Save(QString p_qstrName, CdmClass* p_pClass, EwmsImExportMode p_eMode);

   /** +-=---------------------------------------------------------Fri Nov 1 09:43:06 2002--------*
    * @method  CwmsImExportSettingsHandler::AddKey                     // public                            *
    * @return  void                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @comment Adds a Key to the the session.                                                     *
    *---------------------------------------------------------------Fri Nov 1 09:43:06 2002-------*/
   public:
      void AddKey(  QString sKey );

   /** +-=---------------------------------------------------------Mon Aug 26 21:38:15 2002-------*
    * @method  CwmsImExportSettingsHandler::IsKey                      // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @comment returns if this is a key or not.                                                   *
    *---------------------------------------------------------------Mon Aug 26 21:38:15 2002------*/
   public:
      bool IsKey(  QString sKey );
   public:
   /** +-=---------------------------------------------------------Sa 21. Jun 11:58:22 2003*
    * @method  CwmsImExportSettingsHandler::SetString                  // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString sContent                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Sa 21. Jun 11:58:22 2003----------*/
bool SetString(  QString sKey, QString sValue, QString sContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:41:19 2002-------*
    * @method  CwmsImExportSettingsHandler::SetInteger                 // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   int nContent                                  //                                   *
    * @comment Sets the Integer value to session.                                                 *
    *---------------------------------------------------------------Mon Aug 26 21:41:19 2002------*/
   public:
      bool SetInteger(  QString sKey, QString sValue, int nContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:46:40 2002-------*
    * @method  CwmsImExportSettingsHandler::SetFloat                   // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   float fContent                                //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:46:40 2002------*/
   public:
      bool SetFloat(  QString sKey, QString sValue, float fContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:47:34 2002-------*
    * @method  CwmsImExportSettingsHandler::SetContent                 // private                           *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString sContent                              //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:47:34 2002------*/
   private:
      bool SetContent(  QString sKey, QString sValue, QString sContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:52:19 2002-------*
    * @method  CwmsImExportSettingsHandler::GetString                  // public                            *
    * @return  QString                                       //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString sReturn                               //                                   *
    * @comment returns the String of the Key and Value.                                           *
    *---------------------------------------------------------------Mon Aug 26 21:52:19 2002------*/
   public:
      QString GetString(  QString sKey, QString sValue, QString sReturn );

   /** +-=---------------------------------------------------------Mon Aug 26 21:53:08 2002-------*
    * @method  CwmsImExportSettingsHandler::GetInteger                 // public                            *
    * @return  int                                           //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   int nReturn                                   //                                   *
    * @comment returns the Integer at Key and Value.                                              *
    *---------------------------------------------------------------Mon Aug 26 21:53:08 2002------*/
   public:
      int GetInteger(  QString sKey, QString sValue, int nReturn );

   /** +-=---------------------------------------------------------Mon Aug 26 21:57:54 2002-------*
    * @method  CwmsImExportSettingsHandler::GetFloat                   // public                            *
    * @return  float                                         //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   float fReturn                                 //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:57:54 2002------*/
   public:
      float GetFloat(  QString sKey, QString sValue, float fReturn );
   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 14:04:47 2012-------*
    * @method  CwmsImExportSettingsHandler::GetContent         // private                           *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString& sContent                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 14:04:47 2012----------*/
    bool GetContent(QString sKey, QString sValue, QString& sContent);

 
};

#endif // //__SETTINGS_H
