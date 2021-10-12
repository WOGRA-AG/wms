/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImport.cpp
 ** Started Implementation: 2008/10/21
 ** Description:
 ** 
 ** This class implements the unified import to wms.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QStringList>
#include <QApplication>

// Own Includes
#include "CwmsImport.h"
#include "CwmsImportSettings.h"
#include "CwmsImportSettingsColumn.h"
#include "CwmsImportParser.h"

// WMS Includes
#include "CdmMember.h"
#include "CdmValue.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmScheme.h"
#include "CdmLogging.h"


/** +-=---------------------------------------------------------Di 21. Okt 19:45:45 2008----------*
 * @method  CwmsImport::CwmsImport                           // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 19:45:45 2008----------*/
CwmsImport::CwmsImport()
: m_pParser(nullptr),
 m_bDisplayProgress(true)
{
}

/** +-=---------------------------------------------------------Di 21. Okt 19:45:54 2008----------*
 * @method  CwmsImport::~CwmsImport                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImport                                                    *
 *----------------last changed: --------------------------------Di 21. Okt 19:45:54 2008----------*/
CwmsImport::~CwmsImport()
{
   DELPTR(m_pParser);
}

/** +-=---------------------------------------------------------Do 28. Feb 12:39:08 2013----------*
 * @method  CwmsImport::SetDipslayProgress                   // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bDisplay                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 12:39:08 2013----------*/
void CwmsImport::SetDipslayProgress(bool p_bDisplay)
{
   m_bDisplayProgress = p_bDisplay;
}

/** +-=---------------------------------------------------------Do 28. Feb 12:39:33 2013----------*
 * @method  CwmsImport::GetDisplayProgress                   // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 12:39:33 2013----------*/
bool CwmsImport::GetDisplayProgress()
{
   return m_bDisplayProgress;
}

/** +-=---------------------------------------------------------Do 28. Feb 12:22:03 2013----------*
 * @method  CwmsImport::CreateParser                         // public                            *
 * @return  CwmsImportParser*                                //                                   *
 * @param   QString p_qstrSettingsFile                       //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 12:22:03 2013----------*/
CwmsImportParser* CwmsImport::CreateParser(QString p_qstrSettingsFile, CdmObjectContainer* p_pList)
{
   DELPTR(m_pParser);
   m_cCwmsImportSettings.LoadSettings(p_qstrSettingsFile, p_pList->GetClassId());
   m_pParser = CwmsImportParser::ParserFactory(&m_cCwmsImportSettings);
   return m_pParser;
}

/** +-=---------------------------------------------------------Do 28. Feb 12:36:12 2013----------*
 * @method  CwmsImport::CreateParser                         // public                            *
 * @return  CwmsImportParser*                                //                                   *
 * @param   CwmsImportSettings p_cwmsImportSettings          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 12:36:12 2013----------*/
CwmsImportParser* CwmsImport::CreateParser(CwmsImportSettings p_cwmsImportSettings)
{
   DELPTR(m_pParser);
   m_cCwmsImportSettings = p_cwmsImportSettings;
   m_pParser = CwmsImportParser::ParserFactory(&m_cCwmsImportSettings);
   return m_pParser;
}

/** +-=---------------------------------------------------------Do 7. Feb 09:19:23 2013-----------*
 * @method  CwmsImport::StartImport                          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSettingsFile                       //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment This method starts the import with the overgiven settingsfilename                     *
 *----------------last changed: --------------------------------Do 7. Feb 09:19:23 2013-----------*/
void CwmsImport::StartImport(QString p_qstrSettingsFile, CdmObjectContainer* p_pList)
{
   if (CHKPTR(p_pList))
   {
      if (!m_pParser)
      {
         CreateParser(p_qstrSettingsFile, p_pList);
      }
      
      if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeOverwrite)
      {
         p_pList->SetImportMode(false);
         p_pList->DeleteAllObjects();
         p_pList->Commit();
         p_pList->SetImportMode(true);
      }

      if (CHKPTR(m_pParser))
      {
         m_cCwmsImportSettings.SetObjectList(p_pList);
         m_pParser->ParseFile(this);
      }
   }
}

/** +-=---------------------------------------------------------Do 7. Feb 09:21:52 2013-----------*
 * @method  CwmsImport::StartImport                          // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  // the target objectlist.            *
 * @param   CwmsImportSettings p_cwmsImportSettings          //                                   *
 * @comment This method starts the import with the overgiven settingsfilename                     *
 *----------------last changed: --------------------------------Do 7. Feb 09:21:52 2013-----------*/
void CwmsImport::StartImport(CdmObjectContainer* p_pContainer,
                             CwmsImportSettings p_cwmsImportSettings)
{
   if (CHKPTR(p_pContainer))
   {
      m_cCwmsImportSettings = p_cwmsImportSettings;
      m_cCwmsImportSettings.SetObjectList(p_pContainer);

      if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeOverwrite)
      {
         p_pContainer->SetImportMode(false);
         p_pContainer->DeleteAllObjects();
         p_pContainer->Commit();
         p_pContainer->SetImportMode(true);
      }

      if (!m_pParser)
      {
         m_pParser = CreateParser(m_cCwmsImportSettings);
      }
      
      if (m_pParser)
      {
         m_pParser->ParseFile(this);
      }
   }
}

/** +-=---------------------------------------------------------Do 7. Feb 12:34:56 2013-----------*
 * @method  CwmsImport::GetSettings                          // public                            *
 * @return  CwmsImportSettings&                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Feb 12:34:56 2013-----------*/
CwmsImportSettings& CwmsImport::GetSettings()
{
   return m_cCwmsImportSettings;
}

/** +-=---------------------------------------------------------Mi 22. Okt 18:56:56 2008----------*
 * @method  CwmsImport::GetImportMessages                    // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Okt 18:56:56 2008----------*/
QString CwmsImport::GetImportMessages()
{
   return m_qstrImportMessages;
}

/** +-=---------------------------------------------------------Mi 22. Okt 18:36:55 2008----------*
 * @method  CwmsImport::GetObjectList                        // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment returns the objectlist for the import.                                                *
 *----------------last changed: --------------------------------Mi 22. Okt 18:36:55 2008----------*/
CdmObjectContainer* CwmsImport::GetObjectList()
{
   CdmObjectContainer* pContainer = nullptr;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->FindSchemeById(m_cCwmsImportSettings.GetDatabaseId());

      if (CHKPTR(pCdmDatabase))
      {
         CdmContainerManager* pContainerManager = pCdmDatabase->GetContainerManager();

         if (CHKPTR(pContainerManager))
         {
            pContainer = pContainerManager->FindContainerById(m_cCwmsImportSettings.GetObjectListId());

            if (CHKPTR(pContainer))
            {
               pContainer->SetImportMode(true);
            }
         }
      }
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Mi 22. Okt 19:01:39 2008----------*
 * @method  CwmsImport::GetObject                            // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param   QStringList qstrlParseData                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Okt 19:01:39 2008----------*/
CdmObject* CwmsImport::GetObject(QStringList qstrlParseData)
{
   CdmObject* pCdmObject = nullptr;
   if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeOverwrite ||
       m_cCwmsImportSettings.GetImportMode() == eWmsImportModeAppend)
   {
      CdmObjectContainer* pContainer = GetObjectList();

      if (CHKPTR(pContainer))
      {
         pCdmObject = pContainer->CreateNewObject();
      }

   }
   else if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeUpdate)
   {
      pCdmObject = ExecuteObjectQuery(qstrlParseData);
   }
   else
   {
      ERR("Wrong Mode!!!");
      m_qstrImportMessages += "<p>" + qApp->tr("Import Modus ist Unbekannt.") + "</p>";
   }

   return pCdmObject;
}

/** +-=---------------------------------------------------------Mi 22. Okt 19:01:22 2008----------*
 * @method  CwmsImport::ExecuteObjectQuery                   // private                           *
 * @return  CdmObject*                                       //                                   *
 * @param   QStringList p_rqstrlParseData                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Okt 19:01:22 2008----------*/
CdmObject* CwmsImport::ExecuteObjectQuery(QStringList p_rqstrlParseData)
{
   CdmObject* pCdmObject = nullptr;
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      CdmQuery cCdmQuery;
      cCdmQuery.SetContainer(pContainer);
      CreateQuery(cCdmQuery, p_rqstrlParseData);

      if (cCdmQuery.Execute() > 0)
      {
         QList<qint64> qvlResults;
         qvlResults = cCdmQuery.GetResultList();

         if (qvlResults.count() > 0)
         {
            QList<qint64>::iterator qvlIt = qvlResults.begin();
            QList<qint64>::iterator qvlItEnd = qvlResults.end();

            for (; qvlIt != qvlItEnd; ++qvlIt)
            {
              qint64 lId = (*qvlIt);

               pCdmObject = pContainer->FindObjectById(lId);

               if (pCdmObject)
               {
                  break;
               }
            }

            if (qvlResults.count() > 1)
            {
               m_qstrImportMessages += "<p>" + qApp->tr("Mehr als einen Datensatz gefunden verwende den ersten.") + "</p>";
            }
         }
      }
   }

   return pCdmObject;
}

/** +-=---------------------------------------------------------Mi 22. Okt 19:21:48 2008----------*
 * @method  CwmsImport::CreateQuery                          // private                           *
 * @return  void                                             //                                   *
 * @param   CdmQuery& p_rCdmQuery                            //                                   *
 * @param   QStringList p_qstrlParseData                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Okt 19:21:48 2008----------*/
void CwmsImport::CreateQuery(CdmQuery& p_rCdmQuery, QStringList p_qstrlParseData)
{
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      const CdmClass* pCdmClass = pContainer->GetClass();

      if (CHKPTR(pCdmClass))
      {
         QList<CwmsImportSettingsColumn*> qlColumns;
         m_cCwmsImportSettings.GetColumns(qlColumns);
         CdmQueryElement* pCdmQueryElementRoot = new CdmQueryElement(&p_rCdmQuery,
                                                                     eDmQueryElementTypeAnd);

         p_rCdmQuery.ResetQueryElement(pCdmQueryElementRoot);

         for (int iPos = 0; iPos < qlColumns.count(); ++iPos)
         {
            CwmsImportSettingsColumn* pColumn = qlColumns[iPos];

            if (CHKPTR(pColumn) && pColumn->IsUpdateCriteria())
            {
               QString qstrValue = p_qstrlParseData[iPos];
               const CdmMember* pCdmMember = pCdmClass->FindMember(pColumn->GetMember());

               if (pCdmMember)
               {
                  CdmQueryElement* pCdmQueryElement = new CdmQueryElement(&p_rCdmQuery,
                                                                           eDmQueryElementTypeCompare,
                                                                           eDmQueryCompareTypeEqual);

                  switch(pCdmMember->GetValueType())
                  {
                  case eDmValueBool:
                     if (qstrValue == "1" || qstrValue == "true")
                     {
                        pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), true);
                     }
                     else
                     {
                        pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), false);
                     }
                     break;
                  case eDmValueString:
                  case eDmValueCharacterDocument:
                     pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qstrValue);
                     break;
                  case eDmValueCounter:
                  case eDmValueInt:
                  case eDmValueLong:
                  case eDmValueContainerRef:
                  case eDmValueObjectRef:
                     pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qstrValue.toInt());
                     break;
                  case eDmValueDate:
                     {
                        QDate qdCompareDate = QDate::fromString(qstrValue);
                        pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qdCompareDate);
                     }

                     break;
                  case eDmValueDateTime:
                     {
                        QDateTime qdtCompareDate = QDateTime::fromString(qstrValue);
                        pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qdtCompareDate);
                     }
                     
                     break;
                  case eDmValueDouble:
                  case eDmValueFloat:
                     pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), (float)qstrValue.toDouble());
                     break;
                  case eDmValueTime:
                     {
                        QTime qtCompareDate = QTime::fromString(qstrValue);
                        pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qtCompareDate);
                     }

                     break;
                  default:
                     ERR("Unsupported Type");
                     m_qstrImportMessages += "<p>" + qApp->tr("Der Typ dieses Members wird nicht untersttzt: ") + pColumn->GetMember() + "</p>";
                  }

                  pCdmQueryElementRoot->AddChild(pCdmQueryElement);
               }
               else
               {
                  m_qstrImportMessages += "<p>" + qApp->tr("Member wurde nicht gefunden: ") + pColumn->GetMember() + "</p>";
               }
            }
         }
      }   
   }
}


/** +-=---------------------------------------------------------Fr 8. Feb 14:12:03 2013-----------*
 * @method  CwmsImport::CreateData                           // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param   QStringList p_qsrlParsedData                     //                                   *
 * @comment This method saves the parsed data to the wems dependent from the settings.            *
 *----------------last changed: --------------------------------Fr 8. Feb 14:12:03 2013-----------*/
bool CwmsImport::CreateData(QStringList p_qsrlParsedData)
{
   bool bRet = false;
   CdmObject* pCdmObject = GetObject(p_qsrlParsedData);

   if (pCdmObject)
   {
      SetDefaultValuesToObject(pCdmObject);
      QList<CwmsImportSettingsColumn*> qlColumns;
      m_cCwmsImportSettings.GetColumns(qlColumns);

      for (int iPos = 0; iPos < qlColumns.count(); ++iPos)
      {
         CwmsImportSettingsColumn* pColumn = qlColumns[iPos];

         if (CHKPTR(pColumn) && !pColumn->IsIgnored() && iPos < p_qsrlParsedData.count())
         {
            QString qstrValue = p_qsrlParsedData[iPos];

            CdmValue* pCdmValue = pCdmObject->GetValue(pColumn->GetMember());

            if (pCdmValue)
            {
               pCdmValue->SetValue(qstrValue.simplified(),"");
            }
            else
            {
               m_qstrImportMessages += "<p>" + qApp->tr("Member wurde nicht gefunden: ") + pColumn->GetMember()+ "</p>";
            }
         }
      }

      if (pCdmObject->Commit() <= 0)
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
      }
      else
      {
         bRet = true;
      }
   }

   return bRet;
}


/** +-=---------------------------------------------------------Sa 1. Nov 10:38:27 2008-----------*
 * @method  CwmsImport::SetDefaultValuesToObject             // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment This method sets the default values to the object.                                    *
 *----------------last changed: --------------------------------Sa 1. Nov 10:38:27 2008-----------*/
void CwmsImport::SetDefaultValuesToObject(CdmObject* p_pCdmObject)
{

   if (CHKPTR(p_pCdmObject))
   {
      QMap<QString, TStringPair>::iterator qmIt = m_qmDefaultValues.begin();
      QMap<QString, TStringPair>::iterator qmItEnd = m_qmDefaultValues.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         QString qstrKeyname = qmIt.key();
         TStringPair tStringPair = qmIt.value();

         CdmValue* pCdmValue = p_pCdmObject->GetValue(qstrKeyname);

         if (pCdmValue)
         {
            pCdmValue->SetValue(tStringPair.first, tStringPair.second);
         }
         else
         {
            m_qstrImportMessages += "<p>" + qApp->tr("Standardwert nicht gefunden: ") + qstrKeyname + "</p>";
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 31. Okt 18:14:45 2008----------*
 * @method  CwmsImport::AddHiddenMember                      // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment This method adds hidden members for the import.                                       *
 *----------------last changed: --------------------------------Fr 31. Okt 18:14:45 2008----------*/
void CwmsImport::AddHiddenMember(QString p_qstrMember)
{
   if (!m_qstrlHiddenMembers.contains(p_qstrMember))
   {
      m_qstrlHiddenMembers.append(p_qstrMember);
   }
}

/** +-=---------------------------------------------------------Fr 31. Okt 18:16:23 2008----------*
 * @method  CwmsImport::GetHiddenMembersList                 // public                            *
 * @return  QStringList                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 31. Okt 18:16:23 2008----------*/
QStringList CwmsImport::GetHiddenMembersList()
{
   return m_qstrlHiddenMembers;
}

/** +-=---------------------------------------------------------Sa 1. Nov 11:01:11 2008-----------*
 * @method  CwmsImport::AddDefaultValues                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrValue1                             //                                   *
 * @param   QString p_qstrValue2                             //                                   *
 * @comment This method adds the default values for importing values.                             *
 *----------------last changed: --------------------------------Sa 1. Nov 11:01:11 2008-----------*/
void CwmsImport::AddDefaultValues(QString p_qstrKeyname, QString p_qstrValue1, QString p_qstrValue2)
{
   TStringPair tStringPair(p_qstrValue1, p_qstrValue2);
   m_qmDefaultValues.insert(p_qstrKeyname, tStringPair);
}

/** +-=---------------------------------------------------------Sa 10. Jan 14:12:19 2009----------*
 * @method  CwmsImport::Commit                               // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method saves the import.                                                         *
 *----------------last changed: --------------------------------Sa 10. Jan 14:12:19 2009----------*/
void CwmsImport::Commit()
{
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      pContainer->SetImportMode(false);
      pContainer->Commit();
   }
}
