/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: IdmMessageManager.h
 ** Started Implementation: 2009/10/09
 ** Description:
 ** 
 ** This is a interface for displaying messages over all libs and apps
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IDMMESSAGEMANAGER_H
#define IDMMESSAGEMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include <QList>
#include <QDateTime>


// Forwards
class QStatusBar;
class QWidget;

// Enumerations

/* 
 * This is a interface for displaying messages over all libs and apps.
 */
class IdmMessageManager
{
public:
     virtual ~IdmMessageManager(){}
     virtual void ErrorSync(QString p_qstrHead, QString p_qstrMessage) = 0;
	 virtual void ErrorAsync(QString p_qstrHead, QString p_qstrMessage) = 0;
	 virtual void WarningSync(QString p_qstrHead, QString p_qstrMessage) = 0;
	 virtual void WarningAsync(QString p_qstrHead, QString p_qstrMessage) = 0;
	 virtual void InfoSync(QString p_qstrHead, QString p_qstrMessage) = 0;
	 virtual void InfoAsync(QString p_qstrHead, QString p_qstrMessage) = 0;
	 virtual bool AskYesNo(QString p_qstrHead, QString p_qstrMessage) = 0;
	
	 virtual bool StartAsyncMessageCollection() = 0;
    virtual int GetAsyncMessageCollectionCount() = 0;
	 virtual bool EndAndShowAsyncMessageCollection() = 0;
	 virtual bool IsAsyncMessageCollectionRunning() = 0;
	 virtual bool StartProgressBar(QString p_qstrProgessBarName,QString p_qstrTitle, QString p_qstrDisplayText, int p_iSteps) = 0;
	 virtual bool SetProgress(QString p_qstrProgessBarName, QString p_qstrDisplayText, int p_iProgressSteps) = 0;
	 virtual bool CloseProgressBar(QString p_qstrProgessBarName) = 0;
	 virtual bool IsProgressAborted(QString p_qstrProgessBarName) = 0;
	 virtual QList<QString> GetMessageHistory() = 0;
	 virtual bool DeleteMessageHistory() = 0;
	 virtual bool SaveMessageHistory(QString p_qstrFilename) = 0;
    virtual void AddMessageToStatusBar(QString p_qstrMessage) = 0;
    virtual QString AskForPath(QString p_qstrMessage) = 0;
    virtual QString AskForInputText(QString p_qstrMessage) = 0;
    virtual int AskForInputValue(QString p_qstrMessage) = 0;
    virtual QDate AskForInputDate(QString p_qstrMessage) = 0;
    virtual QTime AskForInputTime(QString p_qstrMessage) = 0;
    virtual QString AskForSaveFile(QString p_qstrMessage, QString p_qstrPathToOpen = "", QString p_qstrFilter = "") = 0;
    virtual QDateTime AskForInputTimestamp(QString p_qstrMessage) = 0;
    virtual QString AskForOpenFile(QString p_qstrMessage, QString p_qstrPathToOpen = "", QString p_qstrFilter = "") = 0;
    virtual void SetStatusBar(QStatusBar* p_pStatusBar) = 0;
    virtual void SetMainWindow(QWidget* p_pMainWindow) = 0;
    virtual void ShowResultMessage(QString p_qstrResultCaption, QString p_qstrResultText, QString p_qstrResult) = 0;
    virtual QString AskForInputStringList(QString p_qstrMessage, QStringList p_qstrlItems) = 0;
};

#endif //
