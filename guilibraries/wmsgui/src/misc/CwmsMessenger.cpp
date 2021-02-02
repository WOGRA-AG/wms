
// System and QT Includes
#include <QWidget>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QProgressDialog>

// WMS Includes
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsShowResultMessageDlg.h"
#include "CwmsShowMessageListDlg.h"
#include "CwmsMessenger.h"

CwmsMessenger::CwmsMessenger(QWidget* p_pqwMainWindow, QStatusBar* p_pqStatusBar)
: m_rpqwMainWindow(p_pqwMainWindow),
  m_rpqStatusBar(p_pqStatusBar),
  m_bIsAsnyMessageCollectionRunning(false)
{
   CdmMessageManager::InstallMessenger(this);
}

CwmsMessenger::~CwmsMessenger()
{
}

void CwmsMessenger::ErrorSync(QString p_qstrHead, QString p_qstrMessage)
{
   QMessageBox::critical(QApplication::activeWindow(), p_qstrHead, p_qstrMessage);
   AddMessageToList(tr("Fehler") + " " + p_qstrHead, p_qstrMessage);
}

void CwmsMessenger::ErrorAsync(QString p_qstrHead, QString p_qstrMessage)
{
   AddMessageToStatusBar(p_qstrMessage);
   AddAsyncMessageToList(tr("Fehler") + "|" + p_qstrHead, p_qstrMessage);
}

void CwmsMessenger::WarningSync(QString p_qstrHead, QString p_qstrMessage)
{
   QMessageBox::warning(QApplication::activeWindow(), p_qstrHead, p_qstrMessage);
   AddMessageToList(tr("Warnung") + "|" + p_qstrHead, p_qstrMessage);
}

void CwmsMessenger::WarningAsync(QString p_qstrHead, QString p_qstrMessage)
{
   AddMessageToStatusBar(p_qstrMessage);
   AddAsyncMessageToList(tr("Warnung") + "|" + p_qstrHead, p_qstrMessage);
}

void CwmsMessenger::InfoSync(QString p_qstrHead, QString p_qstrMessage)
{
   QMessageBox::information(/*QApplication::activeWindow()*/nullptr, p_qstrHead, p_qstrMessage);
   AddMessageToList(tr("Information") + "|" + p_qstrHead, p_qstrMessage);
}

void CwmsMessenger::InfoAsync(QString p_qstrHead, QString p_qstrMessage)
{
   AddMessageToStatusBar(p_qstrMessage);
   AddAsyncMessageToList(tr("Information") + "|" + p_qstrHead, p_qstrMessage);
}

bool CwmsMessenger::AskYesNo(QString p_qstrHead, QString p_qstrMessage)
{
   bool bRet = false;

   switch(QMessageBox::warning(QApplication::activeWindow(), p_qstrHead, p_qstrMessage, tr("Ja"), tr("Nein"), 0, 0, 1))
   {
   case 0: 
      bRet = true;
      break;
   case 1: 
      bRet = false;
      break;
   }

   AddMessageToList(tr("Abfrage") + " " + p_qstrHead, p_qstrMessage);

   if (bRet)
   {
      AddMessageToList(tr("Antwort"), tr("JA"));
   }
   else
   {
      AddMessageToList(tr("Antwort"), tr("NEIN"));
   }

   return bRet;
}

void CwmsMessenger::AddMessageToStatusBar(QString p_qstrMessage)
{
    Q_UNUSED(p_qstrMessage);
   if (m_rpqStatusBar)
   {
      // showing the message 3 seconds long
      //m_rpqStatusBar->showMessage(p_qstrMessage, 3000);
   }
}

void CwmsMessenger::AddMessageToList(QString p_qstrHead, QString p_qstrMessage)
{
   m_qlMessages.append(p_qstrHead + "|" + p_qstrMessage);
}

void CwmsMessenger::AddAsyncMessageToList(QString p_qstrHead, QString p_qstrMessage)
{
   if (IsAsyncMessageCollectionRunning())
   {
      m_qlAsyncMessageCollection.append(p_qstrHead + "|" + p_qstrMessage);
   }

   AddMessageToList(p_qstrHead, p_qstrMessage);
}

bool CwmsMessenger::StartAsyncMessageCollection()
{
   bool bRet = false;

   if (!IsAsyncMessageCollectionRunning())
   {
      m_qlAsyncMessageCollection.clear();
      m_bIsAsnyMessageCollectionRunning = true;
      bRet = true;
   }

   return bRet;
}

bool CwmsMessenger::EndAndShowAsyncMessageCollection()
{
   bool bRet = true;

   if (m_qlAsyncMessageCollection.count() > 0)
   {
      CwmsShowMessageListDlg::ShowMessages(m_qlAsyncMessageCollection, nullptr);
   }

   m_bIsAsnyMessageCollectionRunning = false;
   m_qlAsyncMessageCollection.clear();
   return bRet;
}

int CwmsMessenger::GetAsyncMessageCollectionCount()
{
    return m_qlAsyncMessageCollection.count();
}

bool CwmsMessenger::IsAsyncMessageCollectionRunning()
{
   return m_bIsAsnyMessageCollectionRunning;
}

bool CwmsMessenger::StartProgressBar(QString p_qstrProgessBarName,
                                     QString p_qstrWindowTitle,
                                     QString p_qstrDisplayText,
                                     int p_iSteps)
{
   bool bRet = false;

   if (!m_qmProgressBars.contains(p_qstrProgessBarName))
   {
      QProgressDialog* pQProgressDialog = new QProgressDialog(QApplication::activeWindow());
      pQProgressDialog->setWindowTitle(p_qstrWindowTitle);
      pQProgressDialog->setLabelText(p_qstrDisplayText);
      pQProgressDialog->setMinimum(0);
      pQProgressDialog->setMaximum(p_iSteps);
      pQProgressDialog->show();
      m_qmProgressBars.insert(p_qstrProgessBarName, pQProgressDialog);
      qApp->processEvents();
   }

   return bRet;
}

bool CwmsMessenger::SetProgress(QString p_qstrProgessBarName,
                                QString p_qstrText,
                                int p_iProgressSteps)
{
   bool bRet = false;

   if (m_qmProgressBars.contains(p_qstrProgessBarName))
   {
      QProgressDialog* pQProgressDialog = m_qmProgressBars[p_qstrProgessBarName];

      if (pQProgressDialog)
      {
         pQProgressDialog->setLabelText(p_qstrText);
         pQProgressDialog->setValue(p_iProgressSteps);

         if (p_iProgressSteps == pQProgressDialog->maximum())
         {
            bRet = CloseProgressBar(p_qstrProgessBarName);
         }
         else
         {
            bRet = true;
         }
      }
   }

   qApp->processEvents();
   return bRet;
}

bool CwmsMessenger::CloseProgressBar(QString p_qstrProgessBarName)
{
   bool bRet = false;

   if (m_qmProgressBars.contains(p_qstrProgessBarName))
   {
      QProgressDialog* pQProgressDialog = m_qmProgressBars[p_qstrProgessBarName];

      if (pQProgressDialog)
      {
         delete pQProgressDialog;
         m_qmProgressBars.remove(p_qstrProgessBarName);
         bRet = true;
      }
   }
 
   qApp->processEvents();
   return bRet;
}

bool CwmsMessenger::IsProgressAborted(QString p_qstrProgessBarName)
{
   bool bRet = false;

   if (m_qmProgressBars.contains(p_qstrProgessBarName))
   {
      QProgressDialog* pQProgressDialog = m_qmProgressBars[p_qstrProgessBarName];

      if (pQProgressDialog)
      {
         bRet = pQProgressDialog->wasCanceled();
      }
   }

   return bRet;
}

QList<QString> CwmsMessenger::GetMessageHistory()
{
   return m_qlMessages;
}

bool CwmsMessenger::DeleteMessageHistory()
{
   bool bRet = false;

   if (m_qlMessages.count() > 0)
   {
      m_qlMessages.clear();
   }
   
   return bRet;
}

bool CwmsMessenger::SaveMessageHistory(QString p_qstrProgessBarName)
{
    Q_UNUSED(p_qstrProgessBarName);
   bool bRet = false;

   QString qstrFileName = GetFileNameForSave();

   if (!qstrFileName.isEmpty())
   {
      bRet = SaveFile(qstrFileName);
   }

   return bRet;
}

QString CwmsMessenger::AskForPath(QString p_qstrMessage)
{
   QString qstrDirectory =
      QFileDialog::getExistingDirectory(QApplication::activeWindow(), 
                                        p_qstrMessage);

   return qstrDirectory;
}

QString CwmsMessenger::AskForOpenFile(QString p_qstrMessage, QString p_qstrPathToOpen, QString p_qstrFilter)
{
   QString qstrDirectory =
      QFileDialog::getOpenFileName(QApplication::activeWindow(),
                                        p_qstrMessage,
                                        p_qstrPathToOpen,
                                        p_qstrFilter);

   return qstrDirectory;
}

QString CwmsMessenger::AskForSaveFile(QString p_qstrMessage, QString p_qstrPathToOpen, QString p_qstrFilter)
{
   QString qstrDirectory =
      QFileDialog::getSaveFileName(QApplication::activeWindow(),
                                   p_qstrMessage,
                                   p_qstrPathToOpen,
                                   p_qstrFilter);

   return qstrDirectory;
}

QString CwmsMessenger::AskForOpenFile(QString p_qstrMessage)
{
    QString qstrDirectory =AskForOpenFile(p_qstrMessage,
                                          "",
                                          "");

    return qstrDirectory;
}


QString CwmsMessenger::GetFileNameForSave()
{
   QString qstrFileName =
      QFileDialog::getSaveFileName(QApplication::activeWindow(), 
                                   tr("Bitte geben Sie den Dateinamen zur Speicherung der Meldung an."), 
                                   "", "*.txt");

   if (!qstrFileName.isEmpty())
   {
      if (!qstrFileName.contains("."))
      {
         qstrFileName += ".txt";
      }
   }

   return qstrFileName;
}

bool CwmsMessenger::SaveFile(QString p_qstrFilename)
{
   bool bRet = false;

   if (!p_qstrFilename.isEmpty())
   {
      QFile qFile(p_qstrFilename);

      if (qFile.open(QIODevice::WriteOnly))
      {
         QTextStream qTextStream(&qFile);

         for (int iCounter = 0; iCounter < m_qlMessages.count(); ++iCounter)
         {
            qTextStream << m_qlMessages.at(iCounter);
         }

         qFile.close();
         bRet = true;
      }
      else
      {
         ErrorSync(tr("Speichern nicht möglich"), 
                   tr("Datei kann nicht zum Speichern geöffnet werden. Evtl. fehlt die Schreibberechtigung"));
      }
   }

   return bRet;
}

QString CwmsMessenger::AskForInputText(QString p_qstrMessage)
{
   return QInputDialog::getText(nullptr, tr("Eingabe erforderlich"), p_qstrMessage);;
}

QString CwmsMessenger::AskForInputStringList(QString p_qstrMessage, QStringList p_qstrlItems)
{
    return QInputDialog::getItem(NULL, tr("Auswahl erforderlich"), p_qstrMessage, p_qstrlItems, 0, false);
}

int CwmsMessenger::AskForInputValue(QString p_qstrMessage)
{
   return QInputDialog::getInt(nullptr, tr("Eingabe erforderlich"), p_qstrMessage);;;
}

QDate CwmsMessenger::AskForInputDate(QString p_qstrMessage)
{
   Q_UNUSED(p_qstrMessage);
   return QDate();
}

QTime CwmsMessenger::AskForInputTime(QString p_qstrMessage)
{
   Q_UNUSED(p_qstrMessage);
   return QTime();
}

QDateTime CwmsMessenger::AskForInputTimestamp(QString p_qstrMessage)
{
   Q_UNUSED(p_qstrMessage);
   return QDateTime();
}

void CwmsMessenger::ShowResultMessage(QString p_qstrResultCaption,
                                      QString p_qstrResultText,
                                      QString p_qstrResult)
{
   CwmsShowResultMessageDlg::ShowResult(p_qstrResultCaption, p_qstrResultText, p_qstrResult, nullptr);
}

void CwmsMessenger::SetStatusBar(QStatusBar* p_pStatusBar)
{
   m_rpqStatusBar = p_pStatusBar;
}

void CwmsMessenger::SetMainWindow(QWidget* p_pMainWindow)
{
   m_rpqwMainWindow = p_pMainWindow;
}
