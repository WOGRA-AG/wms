/******************************************************************************
 ** WOGRA Middleware Server Licence Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qapplication.h>
#include <QSqlError>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qlineedit.h>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmError.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsLicenceManagerIf.h"



/** +-=---------------------------------------------------------So 18. Aug 22:31:59 2013----------*
 * @method  CwmsLicenceManagerIf::CwmsLicenceManagerIf       // public                            *
 * @return                                                   //                                   *
 * @param   int p_iCurrentSessionId                          //                                   *
 * @param   QString p_qstrSoftware                           //                                   *
 * @param   QWidget* parent = NULL                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Aug 22:31:59 2013----------*/
CwmsLicenceManagerIf::CwmsLicenceManagerIf(int p_iCurrentSessionId,
                                           QString p_qstrSoftware,
                                           QWidget* parent)
   : QDialog(parent),
  m_cCdmSettings(p_qstrSoftware, eDmSettingsModeClient),
  m_qstrSoftware(p_qstrSoftware),
  m_iCurrentSessionId(p_iCurrentSessionId)
{
   setupUi(this);
   
   if (InitDatabase())
   {
      FillDialog();
   }
}


/** +-=---------------------------------------------------------Di 28. Sep 14:36:53 2010----------*
 * @method  CwmsLicenceManagerIf::CwmsLicenceManagerIf       // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrSoftware                           //                                   *
 * @param   QWidget* parent = NULL                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 14:36:53 2010----------*/
CwmsLicenceManagerIf::CwmsLicenceManagerIf(QString p_qstrSoftware, QWidget* parent)
   : QDialog(parent),
  m_cCdmSettings(p_qstrSoftware, eDmSettingsModeClient),
  m_qstrSoftware(p_qstrSoftware),
  m_iCurrentSessionId(0)
{
   setupUi(this);
   setWindowTitle(tr("WMS Lizenzverwaltung für ") + p_qstrSoftware);
   
   if (InitDatabase())
   {
     FillDialog();
   }
   else
   {
      CdmMessageManager::critical(tr("Verbindung zur Datenbank konnte nicht aufgebaut werden."), 
         tr("Di Verbindung zur Datenbank konnte nicht aufgebaut werden. Bitte überprüfen Sie Ihre Clienteinstellungen\n"
         "und versuchen es noch einmal."));
   }
}


/** +-=---------------------------------------------------------Mi 28. Dez 15:22:09 2005----------*
 * @method  CwmsLicenceManagerIf::~CwmsLicenceManagerIf      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsLicenceManagerIf                                          *
 *                                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Mi 28. Dez 15:22:09 2005----------*/
CwmsLicenceManagerIf::~CwmsLicenceManagerIf(  )
{
}

/** +-=---------------------------------------------------------Mi 28. Dez 15:22:31 2005----------*
 * @method  CwmsLicenceManagerIf::FillDialog                 // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog with the licencedata                                     *
 *----------------last changed: Wolfgang Graßhof----------------Mi 28. Dez 15:22:31 2005----------*/
void CwmsLicenceManagerIf::FillDialog(  )
{
   FillSessions();
   FillLicences();

   m_pqleSoftwareName->setText(m_qstrSoftware);
}

/** +-=---------------------------------------------------------Fr 30. Dez 12:49:51 2005----------*
 * @method  CwmsLicenceManagerIf::InitDatabase               // private                           *
 * @return  bool                                             //                                   *
 * @comment This method inits the database.                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Fr 30. Dez 12:49:51 2005----------*/
bool CwmsLicenceManagerIf::InitDatabase(  )
{
   bool bRet = true;
   QString qstrDatabaseName;

   if(m_cCdmSettings.GetAccessMode() == eDmDatabase)
   {
      m_pqsqlDatabase = QSqlDatabase::addDatabase("QODBC3");
      m_pqsqlDatabase.setDatabaseName(m_cCdmSettings.GetDbName());
      m_pqsqlDatabase.setHostName(m_cCdmSettings.GetServername());
      m_pqsqlDatabase.setUserName(m_cCdmSettings.GetDbLogin());
      m_pqsqlDatabase.setPassword(m_cCdmSettings.GetDbPassword());
   }
   else if(m_cCdmSettings.GetAccessMode() == eDmFile)
   {
      m_pqsqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
     
      qstrDatabaseName = m_cCdmSettings.GetDbFilePath() + "/" + m_cCdmSettings.GetDbName();

      m_pqsqlDatabase.setDatabaseName(qstrDatabaseName);
      m_pqsqlDatabase.setUserName("");
      m_pqsqlDatabase.setPassword("");
      m_pqsqlDatabase.setHostName("localhost");
   }

   if(!m_pqsqlDatabase.open())
   {
      bRet = false;
      CdmMessageManager::critical(tr("Datenbank konnte nicht initialisiert werden."), 
                             qstrDatabaseName);
      ERR("Unable to open database");
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 28. Dez 16:41:45 2005----------*
 * @method  CwmsLicenceManagerIf::FillSessions               // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the session lsitview.                                               *
 *----------------last changed: Wolfgang Graßhof----------------Mi 28. Dez 16:41:45 2005----------*/
void CwmsLicenceManagerIf::FillSessions(  )
{
   m_pqlvSessions->clear();

   if(m_pqsqlDatabase.isOpen())
   {
      QString qstrQuery;

      if(m_cCdmSettings.GetAccessMode() == eDmDatabase)
      {
         qstrQuery = QString("select us.SessionId, us.UserId, us.LoginDate, um.login from WMS_UM_SESSION us, WMS_UM_USER um "
                             "where um.userid = us.userid and state = true and Application = '%1'")
                            .arg(m_qstrSoftware);
      }
      else if(m_cCdmSettings.GetAccessMode() == eDmFile)
      {
         qstrQuery = QString("select us.SessionId, us.UserId, us.LoginDate, um.login from WMS_UM_SESSION us, WMS_UM_USER um " 
                             "where um.userid = us.userid and state = 1 and Application = '%1'")
                            .arg(m_qstrSoftware);
      }

      QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

      if(!qsqlQuery.isActive())
      {
         QString qstrError = m_pqsqlDatabase.lastError().text();
         CdmMessageManager::critical(tr("Datenbankfehler"), tr("Datenbankfehler beim Laden der Anwendersitzungen"));
      }
      else
      {
         qsqlQuery.first();

         while(qsqlQuery.isValid())
         {
            QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvSessions);

            pqlviItem->setText(0, qsqlQuery.value(0).toString());
            pqlviItem->setText(1, qsqlQuery.value(1).toString());
            pqlviItem->setText(2, qsqlQuery.value(3).toString());
            pqlviItem->setText(3, qsqlQuery.value(2).toDateTime().toString(Qt::SystemLocaleShortDate));
            
            qsqlQuery.next();
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 28. Dez 16:43:38 2005----------*
 * @method  CwmsLicenceManagerIf::FillLicences               // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the licencelistview                                                 *
 *----------------last changed: Wolfgang Graßhof----------------Mi 28. Dez 16:43:38 2005----------*/
void CwmsLicenceManagerIf::FillLicences(  )
{ 
   int iLicenceCount = 0;
   int iLicenceSum = 0;
   m_pqlvLicences->clear();
   QString qstrVersion;
   QMap<QString, int> qmLicences;
   
   if(m_pqsqlDatabase.isOpen())
   {
      QString qstrQuery = QString("select Licensee, LicenseKey from WMS_UM_LICENSEKEY where Application = '%1'")
                                  .arg(m_qstrSoftware);

      QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

      if(!qsqlQuery.isActive())
      {
         CdmMessageManager::critical(tr("Datenbankfehler"), tr("Datenbankfehler beim Laden der Lizenzen"));
      }
      else
      {
         qsqlQuery.first();

         while(qsqlQuery.isValid())
         {
            QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvLicences);

            QString qstrLicensee = qsqlQuery.value(0).toString();
            QString qstrLicenseKey = qsqlQuery.value(1).toString();



            pqlviItem->setText(0, qstrLicensee);
            pqlviItem->setText(1, qstrLicenseKey);
            pqlviItem->setText(2, m_qstrSoftware);
            int iModules = 0;

            iLicenceCount = CdmDataAccessHelper::ValidateLicence(m_qstrSoftware, 
                                                           qstrLicensee, 
                                                           qstrLicenseKey,
                                                           iModules,
                                                           QString("-1"));

            if(!qmLicences.contains(qstrLicensee))
            {
               if(iLicenceCount > 0)
               {
                  iLicenceSum += iLicenceCount;
               }

               qmLicences.insert(qstrLicensee, iLicenceCount);
               pqlviItem->setText(3, QString::number(iLicenceCount)); 
            }
            else
            {
               pqlviItem->setText(3, tr("Mehr als einmal hinzguefügt.")); 
            }

            QDate qdExpires = CdmDataAccessHelper::GetLicenceExpirationDate(qstrLicenseKey);

            if(qdExpires.isValid())
            {
               pqlviItem->setText(4, qdExpires.toString(Qt::SystemLocaleShortDate));
            }
            else
            {
               pqlviItem->setText(4, tr("Kein Ablaufdatum")); 
            }

            qsqlQuery.next();
         }
      }
   }
   

   m_pqleValidLicences->setText(QString::number(iLicenceSum));
}

/** +-=---------------------------------------------------------Mi 28. Dez 15:36:13 2005----------*
 * @method  CwmsLicenceManagerIf::AddClickedSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the add button was clicked. it adds a new licence to the licencemanager.*
 *----------------last changed: Wolfgang Graßhof----------------Mi 28. Dez 15:36:13 2005----------*/
void CwmsLicenceManagerIf::AddClickedSlot(  )
{
   QString qstrLicencee = m_pqleLicencee->text().trimmed();
   QString qstrLicenceKey = m_pqleLicenceKey->text().trimmed();
   int iModules = 0;
   QString qstrVersion;

   if(CdmDataAccessHelper::ValidateLicence(m_qstrSoftware, qstrLicencee, qstrLicenceKey, iModules, QString("-1")) > 0)
   {
      if (CheckUnique(m_qstrSoftware, qstrLicencee))
      {
         QString qstrQuery = QString("insert into WMS_UM_LICENSEKEY (Application, Licensee, LicenseKey) "
                                     "values('%1', '%2', '%3')")
                                     .arg(m_qstrSoftware)
                                     .arg(qstrLicencee)
                                     .arg(qstrLicenceKey);

         QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

         if(!qsqlQuery.isActive())
         {
            CdmMessageManager::critical(tr("Datenbankfehler"), tr("Aufgrund eines Problems in der Datenbank konnte die "
                                                                  "Lizenz nicht gespeichert werden."));
         }
         else
         {
            m_pqsqlDatabase.commit();
            m_pqleLicencee->setText("");
            m_pqleLicenceKey->setText("");
            FillLicences();
         }
      }
   }
   else
   {
      CdmMessageManager::critical(tr("Ungültige Lizenz"), 
                            tr("Die eingetragene Lizenz ist ungültig oder abgelaufen."));
   }
}

/** +-=---------------------------------------------------------Mi 28. Dez 15:37:15 2005----------*
 * @method  CwmsLicenceManagerIf::FinishSessionClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called to finish a session                                          *
 *----------------last changed: Wolfgang Graßhof----------------Mi 28. Dez 15:37:15 2005----------*/
void CwmsLicenceManagerIf::FinishSessionClickedSlot(  )
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvSessions);

   if(pqlviItem)
   {
      QString qstrSession = pqlviItem->text(0);
      long lSession = qstrSession.toInt();

      if (m_iCurrentSessionId != lSession)
      {
         if(m_pqsqlDatabase.isOpen())
         {
            QString qstrQuery;

            if(m_cCdmSettings.GetAccessMode() == eDmDatabase)
            {
               qstrQuery = QString("update WMS_UM_SESSION set State = false where SessionId = %1")
                                   .arg(lSession);
            }
            else if(m_cCdmSettings.GetAccessMode() == eDmFile)
            {
               qstrQuery = QString("update WMS_UM_SESSION set State = 0 where SessionId = %1")
                                   .arg(lSession);
            }
         
            QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

            if(!qsqlQuery.isActive())
            {
               CdmMessageManager::critical(tr("Datenbankfehler"), tr("Datenbankfehler beim Aktalisieren der Anwendersitzungen"));
            }
            else
            {
               m_pqsqlDatabase.commit();
               FillSessions();
            }
         }
      }
      else
      {
         CdmMessageManager::critical(tr("Diese Session kann von Ihnen nicht beendet werden."), 
                               tr("Sie wollen Ihre eigene Session beenden, das ist nicht möglich.\n"
                                  "Beenden Sie das stattdessen das Programm um diese Sesion zu beenden."));
      }
   }
}

/** +-=---------------------------------------------------------Do 29. Dez 11:44:53 2005----------*
 * @method  CwmsLicenceManagerIf::CheckUnique                // private                           *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrSoftware                           //                                   *
 * @param   QString p_qstrLicencee                           //                                   *
 * @comment This method checks if the licence is unique.                                          *
 *----------------last changed: Wolfgang Graßhof----------------Do 29. Dez 11:44:53 2005----------*/
bool CwmsLicenceManagerIf::CheckUnique(  QString p_qstrSoftware, QString p_qstrLicencee )
{
   bool bRet = false;

   if(m_pqsqlDatabase.isOpen())
   {
      QString qstrQuery = QString("select Licensee from WMS_UM_LICENSEKEY where Application = '%1' and Licensee = '%2'")
                                  .arg(p_qstrSoftware)
                                  .arg(p_qstrLicencee);


      QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

      if(!qsqlQuery.isActive())
      {
         CdmMessageManager::critical(tr("Datenbankfehler"), tr("Datenbankfehler beim überprüfen der Eindeutigkeit der Lizenz.\n"
                                                           "Lizenz kann nicht gespeichert werden"));
      }
      else
      {
         qsqlQuery.first();

         // check if no dataset exists if not
         // there is no dataset like this inserted
         if(!qsqlQuery.isValid())
         {
            bRet = true;
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 29. Dez 12:23:25 2005----------*
 * @method  CwmsLicenceManagerIf::RefreshClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method refreshes all views.                                                      *
 *----------------last changed: Wolfgang Graßhof----------------Do 29. Dez 12:23:25 2005----------*/
void CwmsLicenceManagerIf::RefreshClickedSlot(  )
{
   FillLicences();
   FillSessions();
}

/** +-=---------------------------------------------------------Do 29. Dez 12:23:49 2005----------*
 * @method  CwmsLicenceManagerIf::DeleteLicenceClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method deletes the selcetd licence.                                              *
 *----------------last changed: Wolfgang Graßhof----------------Do 29. Dez 12:23:49 2005----------*/
void CwmsLicenceManagerIf::DeleteLicenceClickedSlot(  )
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvLicences);

   if(pqlviItem)
   {
      QString qstrLicencee = pqlviItem->text(0);

      QString qstrQuery = QString("delete from WMS_UM_LICENSEKEY where Licensee = '%1' and Application = '%2'")
                                  .arg(qstrLicencee)
                                  .arg(m_qstrSoftware);

      QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

      if(!qsqlQuery.isActive())
      {
         CdmMessageManager::critical(tr("Datenbankfehler"), tr("Datenbankfehler beim Löschen der Lizenz"));
      }
      else
      {
         m_pqsqlDatabase.commit();
         FillLicences();
      }

   }
}

/** +-=---------------------------------------------------------Sa 6. Jun 19:00:19 2009-----------*
 * @method  CwmsLicenceManagerIf::StopAllSessionsClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to stop all sesions.                       *
 *----------------last changed: --------------------------------Sa 6. Jun 19:00:19 2009-----------*/
void CwmsLicenceManagerIf::StopAllSessionsClickedSlot()
{
   QString qstrQuery;
   if(m_cCdmSettings.GetAccessMode() == eDmDatabase)
   {
      if (m_iCurrentSessionId == 0)
      {
         qstrQuery = QString("update WMS_UM_SESSION set State = false");
      }
      else
      {
         qstrQuery = QString("update WMS_UM_SESSION set State = false where SessionId <> %1")
            .arg(m_iCurrentSessionId);
      }
      
   }
   else if(m_cCdmSettings.GetAccessMode() == eDmFile)
   {
      if (m_iCurrentSessionId == 0)
      {
         qstrQuery = QString("update WMS_UM_SESSION set State = 0");
      }
      else
      {
         qstrQuery = QString("update WMS_UM_SESSION set State = 0 where SessionId <> %1")
            .arg(m_iCurrentSessionId);
      }
   }

   QSqlQuery qsqlQuery = m_pqsqlDatabase.exec(qstrQuery);

   if(!qsqlQuery.isActive())
   {
      CdmMessageManager::critical(tr("Datenbankfehler"), 
                            tr("Datenbankfehler beim Aktalisieren der Anwendersitzungen"));
   }
   else
   {
      m_pqsqlDatabase.commit();
      FillSessions();
   }
}

