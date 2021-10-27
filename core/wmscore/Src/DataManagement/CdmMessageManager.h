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


#define MSG_CRIT(a,b) CdmMessageManager::critical(QString::fromUtf8(a), QString::fromUtf8(b))
#define MSG_WARN(a,b) CdmMessageManager::warning(QString::fromUtf8(a), QString::fromUtf8(b))
#define MSG_INFO(a,b) CdmMessageManager::information(QString::fromUtf8(a), QString::fromUtf8(b))
#define MSG_ASK(a,b) CdmMessageManager::Ask(QString::fromUtf8(a), QString::fromUtf8(b))

/* 
* This class implements the messagemanager.
*/
class WMSMANAGER_API CdmMessageManager
{
private:
   static IdmMessageManager* m_spCdmMessenger;


   public:
    static void InstallMessenger(IdmMessageManager* p_pMessernger);
    static IdmMessageManager* GetMessenger();
    static void critical(QString p_qstrTitle, QString p_qstrText);
    static void warning(QString p_qstrTitle, QString p_qstrText);
    static void information(QString p_qstrTitle, QString p_qstrText);
    static bool Ask(QString p_qstrHeader, QString p_qstrText);
    static void StatusBarMessage(QString p_qstrMessage);
    static QString GetPath(QString p_qstrMessage);
    static QString AskForInputText(QString p_qstrHeader, QString p_qstrText);
    static QString AskForInputStringList(QString p_qstrText, QStringList p_qstrlItems);
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
    static QVariantList AskForParameters(QList<CdmClassMethodParameter> &p_qlParameters);
};

#endif //
