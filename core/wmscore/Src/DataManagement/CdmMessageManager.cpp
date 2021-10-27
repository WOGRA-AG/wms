// System and QT Includes
#include <QCoreApplication>

// Own Includes
#include "CdmLogging.h"
#include "IdmMessageManager.h"
#include "CdmMessageManager.h"
#include "CdmEventLogger.h"
#include "CdmClassMethod.h"

IdmMessageManager* CdmMessageManager::m_spCdmMessenger = nullptr;


void CdmMessageManager::InstallMessenger(IdmMessageManager* p_pMessernger)
{
   if (m_spCdmMessenger)
   {
      DELPTR(m_spCdmMessenger);
   }

   m_spCdmMessenger = p_pMessernger;
}

IdmMessageManager* CdmMessageManager::GetMessenger()
{
   return m_spCdmMessenger;
}

void CdmMessageManager::critical(QString p_qstrTitle, QString p_qstrText)
{
   if (m_spCdmMessenger)
   {
      if (m_spCdmMessenger->IsAsyncMessageCollectionRunning())
      {
          m_spCdmMessenger->ErrorAsync(p_qstrTitle, p_qstrText);
      }
      else
      {
         m_spCdmMessenger->ErrorSync(p_qstrTitle, p_qstrText);
      }
   }
}

void CdmMessageManager::warning(QString p_qstrTitle, QString p_qstrText)
{
   if (m_spCdmMessenger)
   {
      if (m_spCdmMessenger->IsAsyncMessageCollectionRunning())
      {
         m_spCdmMessenger->WarningAsync(p_qstrTitle, p_qstrText);
      }
      else
      {
         m_spCdmMessenger->WarningSync(p_qstrTitle, p_qstrText);
      }
   }
}

void CdmMessageManager::information(QString p_qstrTitle, QString p_qstrText)
{
   if (m_spCdmMessenger)
   {
      if (m_spCdmMessenger->IsAsyncMessageCollectionRunning())
      {
         m_spCdmMessenger->InfoAsync(p_qstrTitle, p_qstrText);
      }
      else
      {
         m_spCdmMessenger->InfoSync(p_qstrTitle, p_qstrText);
      }
   }
}

bool CdmMessageManager::Ask(QString p_qstrHeader, QString p_qstrText)
{
   bool bRet = false;

   if (m_spCdmMessenger)
   {
      bRet = m_spCdmMessenger->AskYesNo(p_qstrHeader, p_qstrText);
   }

   return bRet;
}

QString CdmMessageManager::AskForInputText(QString p_qstrHeader, QString p_qstrText)
{
   QString qstrRet;
   Q_UNUSED(p_qstrHeader);

   if (m_spCdmMessenger)
   {
      qstrRet = m_spCdmMessenger->AskForInputText(p_qstrText);
   }

   return qstrRet;
}

QVariantList CdmMessageManager::AskForParameters(QList<CdmClassMethodParameter>& p_qlParameters)
{
    QVariantList qlPparams;
    if (m_spCdmMessenger)
    {
       qlPparams = m_spCdmMessenger->AskForParameters(p_qlParameters);
    }

    return qlPparams;
}

QString CdmMessageManager::AskForInputStringList(QString p_qstrText, QStringList p_qstrlItems)
{
    QString qstrRet;

    if(m_spCdmMessenger)
    {
        qstrRet = m_spCdmMessenger->AskForInputStringList(p_qstrText, p_qstrlItems);
    }

    return qstrRet;
}

void CdmMessageManager::StatusBarMessage(QString p_qstrMessage)
{
   if (m_spCdmMessenger)
   {
      m_spCdmMessenger->AddMessageToStatusBar(p_qstrMessage);
   }
}

QString CdmMessageManager::GetPath(QString p_qstrMessage)
{
   QString qstrPath;

   if (m_spCdmMessenger)
   {
      qstrPath = m_spCdmMessenger->AskForPath(p_qstrMessage);
   }

   return qstrPath;
}

QString CdmMessageManager::GetSaveFile(QString p_qstrMessage, QString p_qstrPathToOpen, QString p_qstrFilter)
{
   QString qstrPath;

   if (m_spCdmMessenger)
   {
      qstrPath = m_spCdmMessenger->AskForSaveFile(p_qstrMessage, p_qstrPathToOpen, p_qstrFilter);
   }

   return qstrPath;
}

QString CdmMessageManager::GetLoadFile(QString p_qstrMessage, QString p_qstrPathToOpen, QString p_qstrFilter)
{
   QString qstrPath;

   if (m_spCdmMessenger)
   {
      qstrPath = m_spCdmMessenger->AskForOpenFile(p_qstrMessage, p_qstrPathToOpen, p_qstrFilter);
   }

   return qstrPath;
}

void CdmMessageManager::ShowResult(QString p_qstrCaption,
                                   QString p_qstrResultText,
                                   QString p_qstrResult)
{
   if (m_spCdmMessenger)
   {
      m_spCdmMessenger->ShowResultMessage(p_qstrCaption, p_qstrResultText, p_qstrResult);
   }
}

bool CdmMessageManager::StartProgressBar(QString p_qstrProgessBarName,QString p_qstrTitle, QString p_qstrDisplayText, int p_iSteps)
{
    bool bRet = false;

    if (m_spCdmMessenger)
    {
        bRet =  m_spCdmMessenger->StartProgressBar(p_qstrProgessBarName, p_qstrTitle, p_qstrDisplayText, p_iSteps);
    }

    return bRet;
}

bool CdmMessageManager::SetProgress(QString p_qstrProgessBarName, QString p_qstrDisplayText, int p_iProgressSteps)
{
    bool bRet = false;

    if (m_spCdmMessenger)
    {
        bRet =  m_spCdmMessenger->SetProgress(p_qstrProgessBarName, p_qstrDisplayText, p_iProgressSteps);
        qApp->processEvents();
    }

    return bRet;
}

bool CdmMessageManager::CloseProgressBar(QString p_qstrProgessBarName)
{
    bool bRet = false;

    if (m_spCdmMessenger)
    {
        bRet =  m_spCdmMessenger->CloseProgressBar(p_qstrProgessBarName);
    }

    return bRet;
}

bool CdmMessageManager::StartAsyncMessageCollection()
{
    bool bRet = false;

    if (m_spCdmMessenger)
    {
        bRet =  m_spCdmMessenger->StartAsyncMessageCollection();
    }

    return bRet;
}

bool CdmMessageManager::EndAndShowAsyncMessageCollection()
{
    bool bRet = false;

    if (m_spCdmMessenger)
    {
        bRet =  m_spCdmMessenger->EndAndShowAsyncMessageCollection();
    }

    return bRet;
}

int CdmMessageManager::GetAsyncMessageCollectionCount()
{
    int iRet = 0;

    if (m_spCdmMessenger)
    {
        iRet =  m_spCdmMessenger->GetAsyncMessageCollectionCount();
    }

    return iRet;
}

bool CdmMessageManager::IsAsyncMessageCollectionRunning()
{
    bool bRet = false;

    if (m_spCdmMessenger)
    {
        bRet =  m_spCdmMessenger->IsAsyncMessageCollectionRunning();
    }

    return bRet;
}
