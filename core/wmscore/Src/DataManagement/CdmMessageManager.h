/******************************************************************************
** WOGRA technologies GmbH & Co KG Modul Information
** Modulename: CwmsMessageManager.h
** Started Implementation: 2009/10/09
** Description:
** 
** This class implements the messagemanager.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
**(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
*****************************************************************************/ 

#ifndef CWMSMESSAGEMANAGER_H
#define CWMSMESSAGEMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QString>

// Own Includes
#include "datamanager.h"

// Interface include
#include "IdmMessageManager.h"

// Forwards
class QWidget;
class QStatusBar;

// Enumerations

/* 
* This class implements the messagemanager.
*/
class WMSMANAGER_API CdmMessageManager
{
private:
   static IdmMessageManager* m_spCdmMessenger;


   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:35:05 2012-------*
    * @method  CdmMessageManager::InstallMessenger           // public, static                    *
    * @return  void                                          //                                   *
    * @param   IdmMessageManager* p_pMessernger              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:35:05 2012----------*/
    static void InstallMessenger(IdmMessageManager* p_pMessernger);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:35:31 2012-------*
    * @method  CdmMessageManager::GetMessenger               // public, static                    *
    * @return  IdmMessageManager*                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:35:31 2012----------*/
    static IdmMessageManager* GetMessenger();

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:35:39 2012-------*
    * @method  CdmMessageManager::critical                   // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:35:39 2012----------*/
    static void critical(QString p_qstrTitle, QString p_qstrText);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:35:49 2012-------*
    * @method  CdmMessageManager::warning                    // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:35:49 2012----------*/
    static void warning(QString p_qstrTitle, QString p_qstrText);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:35:56 2012-------*
    * @method  CdmMessageManager::information                // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:35:56 2012----------*/
    static void information(QString p_qstrTitle, QString p_qstrText);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:36:01 2012-------*
    * @method  CdmMessageManager::Ask                        // public, static                    *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrHeader                          //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:36:01 2012----------*/
    static bool Ask(QString p_qstrHeader, QString p_qstrText);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:36:08 2012-------*
    * @method  CdmMessageManager::StatusBarMessage           // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:36:08 2012----------*/
    static void StatusBarMessage(QString p_qstrMessage);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 13:36:13 2012-------*
    * @method  CdmMessageManager::GetPath                    // public, static                    *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 13:36:13 2012----------*/
    static QString GetPath(QString p_qstrMessage);

   public:
   /** +-=---------------------------------------------------------Do 20. Sep 09:41:25 2012-------*
    * @method  CdmMessageManager::AskForInputText            // public, static                    *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrHeader                          //                                   *
    * @param   QString p_qstrText                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 20. Sep 09:41:25 2012----------*/
    static QString AskForInputText(QString p_qstrHeader, QString p_qstrText);
    static QString AskForInputStringList(QString p_qstrText, QStringList p_qstrlItems);

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 15:06:30 2013--------*
    * @method  CdmMessageManager::ShowResult                 // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @param   QString p_qstrResultText                      //                                   *
    * @param   QString p_qstrResult                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 15:06:30 2013-----------*/
    static void ShowResult(QString p_qstrCaption, QString p_qstrResultText, QString p_qstrResult);
    static bool StartProgressBar(QString p_qstrProgessBarName, QString p_qstrTitle, QString p_qstrDisplayText, int p_iSteps);
    static bool SetProgress(QString p_qstrProgessBarName, QString p_qstrDisplayText, int p_iProgressSteps);
    static bool CloseProgressBar(QString p_qstrProgessBarName);
    static bool StartAsyncMessageCollection();
    static bool EndAndShowAsyncMessageCollection();
    static bool IsAsyncMessageCollectionRunning();
    static int GetAsyncMessageCollectionCount();
    static QString GetLoadFile(QString p_qstrMessage, QString p_qstrPathToOpen = "", QString p_qstrFilter = "");
    static QString GetSaveFile(QString p_qstrMessage, QString p_qstrPathToOpen = "", QString p_qstrFilter = "");
};

#endif //
