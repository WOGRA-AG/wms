/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsMessenger.h
 ** Started Implementation: 2009/10/09
 ** Description:
 **
 ** This class implements the messagemanager.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWMSMESSENGER_H
#define CWMSMESSENGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QString>

// Own Includes
#include "wmsgui.h"

// Interface include
#include "IdmMessageManager.h"

// Forwards
class QWidget;
class QStatusBar;
class QProgressDialog;

// Enumerations

/* 
 * This class implements the messagemanager.
 */
class WMSGUI_API CwmsMessenger : public IdmMessageManager, public QObject
{
private:
    QWidget* m_rpqwMainWindow;
    QStatusBar* m_rpqStatusBar;
    QStringList m_qlMessages;
    QStringList m_qlAsyncMessageCollection;
    bool m_bIsAsnyMessageCollectionRunning;
    QMap<QString, QProgressDialog*> m_qmProgressBars;

public:
    CwmsMessenger( QWidget* p_pqwMainWindow, QStatusBar* p_pqStatusBar);
    virtual ~CwmsMessenger( );
    void ErrorSync(QString p_qstrHead, QString p_qstrMessage);
    void ErrorAsync(QString p_qstrHead, QString p_qstrMessage);
    void WarningSync(QString p_qstrHead, QString p_qstrMessage);
    void WarningAsync(QString p_qstrHead, QString p_qstrMessage);
    void InfoSync(QString p_qstrHead, QString p_qstrMessage);
    void InfoAsync(QString p_qstrHead, QString p_qstrMessage);
    bool AskYesNo(QString p_qstrHead, QString p_qstrMessage);
    virtual void AddMessageToStatusBar(QString p_qstrMessage);
    QDateTime AskForInputTimestamp(QString p_qstrMessage);
    void SetStatusBar(QStatusBar* p_pStatusBar);
    void SetMainWindow(QWidget* p_pMainWindow);
    void ShowResultMessage(QString p_qstrResultCaption,
                           QString p_qstrResultText,
                           QString p_qstrResult);
    QString AskForSaveFile(QString p_qstrMessage, QString p_qstrPathToOpen = "", QString p_qstrFilter = "");
    QString AskForOpenFile(QString p_qstrMessage);
    int GetAsyncMessageCollectionCount();
    QString AskForOpenFile(QString p_qstrMessage, QString p_qstrPathToOpen, QString p_qstrFilter);
    QString AskForInputStringList(QString p_qstrMessage, QStringList p_qstrlItems);
    bool StartAsyncMessageCollection();
    bool EndAndShowAsyncMessageCollection();
    bool IsAsyncMessageCollectionRunning();
    bool StartProgressBar(QString p_qstrProgessBarName,
                          QString p_qstrWindowTitle,
                          QString p_qstrDisplayText,
                          int p_iSteps, bool p_bAbortPossible = false);
    bool SetProgress(QString p_qstrProgessBarName, QString p_qstrText, int p_iProgressSteps);
    bool CloseProgressBar(QString p_qstrProgessBarName);
    bool IsProgressAborted(QString p_qstrProgessBarName);
    QList<QString> GetMessageHistory();
    bool DeleteMessageHistory();
    bool SaveMessageHistory(QString p_qstrProgessBarName);
    QString AskForPath(QString p_qstrMessage);
    int AskForInputValue(QString p_qstrMessage);
    QDate AskForInputDate(QString p_qstrMessage);
    virtual QVariantList AskForParameters(QList<CdmClassMethodParameter>& p_qlParameters);

private:
    QString GetFileNameForSave();
    bool SaveFile(QString p_qstrFilename);
    QString AskForInputText(QString p_qstrMessage);
    QTime AskForInputTime(QString p_qstrMessage);
    void AddMessageToList(QString p_qstrHead, QString p_qstrMessage);
    void AddAsyncMessageToList(QString p_qstrHead, QString p_qstrMessage);

};

#endif //
