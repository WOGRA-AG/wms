/******************************************************************************
** WOGRA technologies GmbH & Co KG Modul Information
** Modulename: CdmMessageManager.cpp
** Started Implementation: 2009/10/09
** Description:
** 
** This class implements the messagemanager.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
**(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
*****************************************************************************/ 

// System and QT Includes
#include <QCoreApplication>

// Own Includes
#include "CdmLogging.h"
#include "IdmMessageManager.h"
#include "CdmMessageManager.h"
#include "CdmEventLogger.h"
#include "CdmClassMethod.h"

IdmMessageManager* CdmMessageManager::m_spCdmMessenger = nullptr;


/** +-=---------------------------------------------------------Do 13. Sep 13:35:05 2012----------*
 * @method  CdmMessageManager::InstallMessenger              // public, static                    *
 * @return  void                                             //                                   *
 * @param   IdmMessageManager* p_pMessernger                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:35:05 2012----------*/
void CdmMessageManager::InstallMessenger(IdmMessageManager* p_pMessernger)
{
   if (m_spCdmMessenger)
   {
      DELPTR(m_spCdmMessenger);
   }

   m_spCdmMessenger = p_pMessernger;
}

/** +-=---------------------------------------------------------Do 13. Sep 13:35:31 2012----------*
 * @method  CdmMessageManager::GetMessenger                  // public, static                    *
 * @return  IdmMessageManager*                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:35:31 2012----------*/
IdmMessageManager* CdmMessageManager::GetMessenger()
{
   return m_spCdmMessenger;
}

/** +-=---------------------------------------------------------Do 13. Sep 13:35:39 2012----------*
 * @method  CdmMessageManager::critical                      // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:35:39 2012----------*/
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

      //CdmEventLogger::AddLog(p_qstrTitle, p_qstrText);
   }
}

/** +-=---------------------------------------------------------Do 13. Sep 13:35:49 2012----------*
 * @method  CdmMessageManager::warning                       // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:35:49 2012----------*/
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

      //CdmEventLogger::AddLog(p_qstrTitle, p_qstrText);
   }
}

/** +-=---------------------------------------------------------Do 13. Sep 13:35:56 2012----------*
 * @method  CdmMessageManager::information                   // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:35:56 2012----------*/
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

      //CdmEventLogger::AddLog(p_qstrTitle, p_qstrText);
   }
}

/** +-=---------------------------------------------------------Do 13. Sep 13:36:01 2012----------*
 * @method  CdmMessageManager::Ask                           // public, static                    *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrHeader                             //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:36:01 2012----------*/
bool CdmMessageManager::Ask(QString p_qstrHeader, QString p_qstrText)
{
   bool bRet = false;

   if (m_spCdmMessenger)
   {
      bRet = m_spCdmMessenger->AskYesNo(p_qstrHeader, p_qstrText);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 20. Sep 09:41:25 2012----------*
 * @method  CdmMessageManager::AskForInputText               // public, static                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrHeader                             //                                   *
 * @param   QString p_qstrText                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 09:41:25 2012----------*/
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

/** +-=---------------------------------------------------------Do 13. Sep 13:36:08 2012----------*
 * @method  CdmMessageManager::StatusBarMessage              // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:36:08 2012----------*/
void CdmMessageManager::StatusBarMessage(QString p_qstrMessage)
{
   if (m_spCdmMessenger)
   {
      m_spCdmMessenger->AddMessageToStatusBar(p_qstrMessage);
   }
}

/** +-=---------------------------------------------------------Do 13. Sep 13:36:13 2012----------*
 * @method  CdmMessageManager::GetPath                       // public, static                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 13:36:13 2012----------*/
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

/** +-=---------------------------------------------------------Fr 8. Feb 15:06:30 2013-----------*
 * @method  CdmMessageManager::ShowResult                    // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @param   QString p_qstrResultText                         //                                   *
 * @param   QString p_qstrResult                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 15:06:30 2013-----------*/
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
