/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsbtSessionManager.h
 ** Started Implementation: 26.8.02
 ** Description:
 **
 ** implements the sessiondata store
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

#ifndef CWMSBTSESSIONMANAGER_H
#define CWMSBTSESSIONMANAGER_H

// System and QT Includes
#include <QString>
#include <QPair>
#include <QList>
#include <QHash>


// own Includes
#include "basetools.h"

// forwards

typedef QPair<QString,QString> StringPair;
typedef QList<StringPair>      KeyItem;
typedef QHash<QString, KeyItem>  MyDict;

class BASETOOLS_API CwmsbtSessionManager
{

   private:
      MyDict m_dictKey;
	   QString m_sFile;

   /** +-=---------------------------------------------------------Mon Aug 26 21:33:56 2002-------*
    * @method  CwmsbtSessionManager::CwmsbtSessionManager          // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:33:56 2002------*/
   public:
      CwmsbtSessionManager(  );

   /** +-=---------------------------------------------------------Mon Aug 26 21:34:09 2002-------*
    * @method  CwmsbtSessionManager::~CwmsbtSessionManager         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsbtSessionManager                                          *
    *                                                                                             *
    *---------------------------------------------------------------Mon Aug 26 21:34:09 2002------*/
   public:
      virtual ~CwmsbtSessionManager(  );

   /** +-=---------------------------------------------------------Sat Oct 26 23:33:22 2002-------*
    * @method  CwmsbtSessionManager::Load                       // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sFile                                 //                                   *
    * @comment Loads the Sessionfile.                                                             *
    *---------------------------------------------------------------Sat Oct 26 23:33:22 2002------*/
   public:
      bool Load(  QString sFile );

   /** +-=---------------------------------------------------------Mon Aug 26 21:35:55 2002-------*
    * @method  CwmsbtSessionManager::Save                       // public                            *
    * @return  bool                                          //                                   *
    * @comment saves the Sessionfile.                                                             *
    *---------------------------------------------------------------Mon Aug 26 21:35:55 2002------*/
   public:
      bool Save(  );

   /** +-=---------------------------------------------------------Mon Aug 26 21:36:54 2002-------*
    * @method  CwmsbtSessionManager::SaveAs                     // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sFile                                 //                                   *
    * @comment Save the Sessionfile under an other filename.                                      *
    *---------------------------------------------------------------Mon Aug 26 21:36:54 2002------*/
   public:
      bool SaveAs(  QString sFile );

   /** +-=---------------------------------------------------------Fri Nov 1 09:43:06 2002--------*
    * @method  CwmsbtSessionManager::AddKey                     // public                            *
    * @return  void                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @comment Adds a Key to the the session.                                                     *
    *---------------------------------------------------------------Fri Nov 1 09:43:06 2002-------*/
   public:
      void AddKey(  QString sKey );

   /** +-=---------------------------------------------------------Mon Aug 26 21:38:15 2002-------*
    * @method  CwmsbtSessionManager::IsKey                      // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @comment returns if this is a key or not.                                                   *
    *---------------------------------------------------------------Mon Aug 26 21:38:15 2002------*/
   public:
      bool IsKey(  QString sKey );
   public:
   /** +-=---------------------------------------------------------Sa 21. Jun 11:58:22 2003*
    * @method  CwmsbtSessionManager::SetString                  // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString sContent                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Sa 21. Jun 11:58:22 2003----------*/
bool SetString(  QString sKey, QString sValue, QString sContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:41:19 2002-------*
    * @method  CwmsbtSessionManager::SetInteger                 // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   int nContent                                  //                                   *
    * @comment Sets the Integer value to session.                                                 *
    *---------------------------------------------------------------Mon Aug 26 21:41:19 2002------*/
   public:
      bool SetInteger(  QString sKey, QString sValue, int nContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:46:40 2002-------*
    * @method  CwmsbtSessionManager::SetFloat                   // public                            *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   float fContent                                //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:46:40 2002------*/
   public:
      bool SetFloat(  QString sKey, QString sValue, float fContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:47:34 2002-------*
    * @method  CwmsbtSessionManager::SetContent                 // private                           *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString sContent                              //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:47:34 2002------*/
   private:
      bool SetContent(  QString sKey, QString sValue, QString sContent );

   /** +-=---------------------------------------------------------Mon Aug 26 21:52:19 2002-------*
    * @method  CwmsbtSessionManager::GetString                  // public                            *
    * @return  QString                                       //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString sReturn                               //                                   *
    * @comment returns the String of the Key and Value.                                           *
    *---------------------------------------------------------------Mon Aug 26 21:52:19 2002------*/
   public:
      QString GetString(  QString sKey, QString sValue, QString sReturn );

   /** +-=---------------------------------------------------------Mon Aug 26 21:53:08 2002-------*
    * @method  CwmsbtSessionManager::GetInteger                 // public                            *
    * @return  int                                           //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   int nReturn                                   //                                   *
    * @comment returns the Integer at Key and Value.                                              *
    *---------------------------------------------------------------Mon Aug 26 21:53:08 2002------*/
   public:
      int GetInteger(  QString sKey, QString sValue, int nReturn );

   /** +-=---------------------------------------------------------Mon Aug 26 21:57:54 2002-------*
    * @method  CwmsbtSessionManager::GetFloat                   // public                            *
    * @return  float                                         //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   float fReturn                                 //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:57:54 2002------*/
   public:
      float GetFloat(  QString sKey, QString sValue, float fReturn );

   /** +-=---------------------------------------------------------Mon Aug 26 21:59:04 2002-------*
    * @method  CwmsbtSessionManager::GetContent                 // private                           *
    * @return  bool                                          //                                   *
    * @param   QString sKey                                  //                                   *
    * @param   QString sValue                                //                                   *
    * @param   QString& sContent                             //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Mon Aug 26 21:59:04 2002------*/
   private:
      bool GetContent(  QString sKey, QString sValue, QString& sContent );

 
};

#endif // //__SETTINGS_H
