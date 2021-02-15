/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmSystemVariables.cpp
 ** Started Implementation: 2012/09/13
 ** Description:
 **
 ** implements functions for returning system values
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QDateTime>

// own Includes
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdmDataProvider.h"
#include "CdmSystemVariables.h"


QStringList CdmSystemVariables::m_sqstrlVariables;
QString CdmSystemVariables::m_sqstrOpen = "${";
QString CdmSystemVariables::m_sqstrClose = "}";


void CdmSystemVariables::FillVariablesInList()
{
   m_sqstrlVariables.append("USER");
   m_sqstrlVariables.append("SESSION");
   m_sqstrlVariables.append("CURRENTYEAR");
   m_sqstrlVariables.append("CURRENTMONTH");
   m_sqstrlVariables.append("CURRENTDAYOFMONTH");
   m_sqstrlVariables.append("CURRENTDAYOFWEEK");
   m_sqstrlVariables.append("CURRENTWEEKNUMBER");
   m_sqstrlVariables.append("CURRENTDATE");
   m_sqstrlVariables.append("CURRENTTIME");
   m_sqstrlVariables.append("CURRENTTIMESTAMP");
   m_sqstrlVariables.append("CURRENTLANGUAGE");
   m_sqstrlVariables.append("CURRENTDATABASE");
}

QStringList CdmSystemVariables::GetSystemVariables()
{
    if (m_sqstrlVariables.isEmpty())
    {
       FillVariablesInList();
    }

    return m_sqstrlVariables;
}

bool CdmSystemVariables::IsSystemValue(QString p_qstrValue)
{
   bool bRet = false;

   if (m_sqstrlVariables.isEmpty())
   {
      FillVariablesInList();
   }

   if (RemoveBraces(p_qstrValue))
   {
      if (m_sqstrlVariables.contains(p_qstrValue.toUpper()))
      {
         bRet = true;
      }
   }

   return bRet;
}

bool CdmSystemVariables::RemoveBraces(QString& p_qstrValue)
{
   bool bRet = false;

   if (p_qstrValue.startsWith(m_sqstrOpen))
   {
      bRet = true;
      p_qstrValue = p_qstrValue.remove(m_sqstrOpen);
      p_qstrValue = p_qstrValue.remove(m_sqstrClose);
   }

   return bRet;
}

QString CdmSystemVariables::GetValueAsString(QString p_qstrVariable)
{
   QString qstrRet;

   if (RemoveBraces(p_qstrVariable))
   {
      if (p_qstrVariable.toUpper() == "USER")
      {
         CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

         if (pCdmManager)
         {
            qstrRet = QString::number(pCdmManager->GetUserId());
         }
      }
      if (p_qstrVariable.toUpper() == "SESSION")
      {
         CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

         if (pCdmManager)
         {
            qstrRet = QString::number(pCdmManager->GetSessionId());
         }
      }
      else if (p_qstrVariable.toUpper() == "CURRENTYEAR")
      {
         qstrRet = QString::number(QDate::currentDate().year());
      }
      else if (p_qstrVariable.toUpper() == "CURRENTMONTH")
      {
         qstrRet = QString::number(QDate::currentDate().month());
      }
      else if (p_qstrVariable.toUpper() == "CURRENTDAYOFMONTH")
      {
         qstrRet = QString::number(QDate::currentDate().day());
      }
      else if (p_qstrVariable.toUpper() == "CURRENTDAYOFWEEK")
      {
         qstrRet = QString::number(QDate::currentDate().dayOfWeek());
      }
      else if (p_qstrVariable.toUpper() == "CURRENTWEEKNUMBER")
      {
         qstrRet = QString::number(QDate::currentDate().dayOfWeek());
      }
      else if (p_qstrVariable.toUpper() == "CURRENTDATE")
      {
         qstrRet = QDate::currentDate().toString("yyyy-MM-dd");
      }
      else if (p_qstrVariable.toUpper() == "CURRENTTIME")
      {
         qstrRet = QTime::currentTime().toString("hh-mm-ss");
      }
      else if (p_qstrVariable.toUpper() == "CURRENTTIMESTAMP")
      {
         qstrRet = QDateTime::currentDateTime().toString(Qt::ISODate);
      }
      else if (p_qstrVariable.toUpper() == "CURRENTLANGUAGE")
      {
         CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

         if (pCdmManager)
         {
            qstrRet = pCdmManager->GetCurrentLanguage();
         }
      }
      else if (p_qstrVariable.toUpper() == "CURRENTDATABASE")
      {
         CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

         if (pCdmManager&& pCdmManager->GetCurrentScheme())
         {
            qstrRet = QString::number(pCdmManager->GetCurrentScheme()->GetId());
         }
      }
   }

   return qstrRet;
}
