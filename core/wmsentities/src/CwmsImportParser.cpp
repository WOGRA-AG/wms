/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportParser.cpp
 ** Started Implementation: 2008/10/14
 ** Description:
 ** 
 ** This class implements the parserbaseclass
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#ifdef WOGRA_DEBUG
#include <time.h>
#endif //

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QProgressDialog>
#include <QApplication>

// WMS Includes
#include "IdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsImport.h"
#include "CwmsImportSettings.h"
#include "CwmsImportParser.h"
#include "CwmsImportParserCsv.h"
#include "CwmsImportParserText.h"
#include "CwmsImportParserXml.h"

/** +-=---------------------------------------------------------Di 14. Okt 20:57:45 2008----------*
 * @method  CwmsImportParser::CwmsImportParser               // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Okt 20:57:45 2008----------*/
CwmsImportParser::CwmsImportParser()
: m_pCwmsImportSettings(nullptr),
  m_pqDevice(nullptr)
{
}

/** +-=---------------------------------------------------------Di 14. Okt 20:57:53 2008----------*
 * @method  CwmsImportParser::~CwmsImportParser              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportParser                                              *
 *----------------last changed: --------------------------------Di 14. Okt 20:57:53 2008----------*/
CwmsImportParser::~CwmsImportParser()
{
}

/** +-=---------------------------------------------------------Di 21. Okt 18:49:24 2008----------*
 * @method  CwmsImportParser::SetImportSettings              // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsImportSettings* p_pImportSettings            //                                   *
 * @comment stes the importsettings.                                                              *
 *----------------last changed: --------------------------------Di 21. Okt 18:49:24 2008----------*/
void CwmsImportParser::SetImportSettings(CwmsImportSettings* p_pImportSettings)
{
   m_pCwmsImportSettings = p_pImportSettings;
}

/** +-=---------------------------------------------------------Do 28. Feb 12:13:43 2013----------*
 * @method  CwmsImportParser::SetDevice                      // public                            *
 * @return  void                                             //                                   *
 * @param   QIODevice* p_pDevice                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 12:13:43 2013----------*/
void CwmsImportParser::SetDevice(QIODevice* p_pDevice)
{
   m_pqDevice = p_pDevice;
}

/** +-=---------------------------------------------------------Di 21. Okt 19:09:56 2008----------*
 * @method  CwmsImportParser::OpenDevice                       // private                         *
 * @return  bool                                             //                                   *
 * @comment This method opens the file.                                                           *
 *----------------last changed: --------------------------------Di 21. Okt 19:09:56 2008----------*/
bool CwmsImportParser::OpenDevice()
{
   bool bRet = false;
   IdmMessageManager* pMessenger = CdmMessageManager::GetMessenger();
   QString qstrFilename;

   if (!m_pqDevice)
   {
        qstrFilename = m_pCwmsImportSettings->GetFilename();

        if (qstrFilename.isEmpty())
        {
            qstrFilename = pMessenger->AskForOpenFile(QObject::tr("Bitte wählen Sie die zu importierende Datei aus."));
        }
   }

   if (!qstrFilename.isEmpty() || m_pqDevice)
   {
       if (m_pCwmsImportSettings)
       {
          if (!m_pqDevice)
          {
             m_pqDevice = new QFile(qstrFilename);
          }

          bRet = m_pqDevice->open(QIODevice::ReadOnly);
       }
   }
   else
   {
        ERR("No filename selected");
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 7. Mrz 14:06:05 2013-----------*
 * @method  CwmsImportParser::CloseDevice                    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 7. Mrz 14:06:05 2013-----------*/
void CwmsImportParser::CloseDevice()
{
   if (CHKPTR(m_pqDevice))
   {
      m_pqDevice->close();
      DELPTR(m_pqDevice);
   }
}

/** +-=---------------------------------------------------------Di 21. Okt 19:58:01 2008----------*
 * @method  CwmsImportParser::ParseFile                      // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsImport* p_pCwmsImport                        //                                   *
 * @comment This mehtod parses the complete file.                                                 *
 *----------------last changed: --------------------------------Di 21. Okt 19:58:01 2008----------*/
void CwmsImportParser::ParseFile(CwmsImport* p_pCwmsImport)
{
#ifdef WOGRA_DEBUG
   double dTimeSum = 0.0;
   double dTimeStartSum = clock(); 
#endif //

   IdmMessageManager* pMessenger = CdmMessageManager::GetMessenger();

   if (pMessenger)
   {
      pMessenger->StartAsyncMessageCollection();
   }

   if (OpenDevice() && CHKPTR(p_pCwmsImport))
   {
      QTextStream qtsStream(m_pqDevice);

      if (!m_pCwmsImportSettings->GetEncoding().isEmpty())
      {
          qtsStream.setCodec(m_pCwmsImportSettings->GetEncoding().toLocal8Bit());
      }

      QString qstrLine;
      QString qstrFileContent = qtsStream.readAll();
      QProgressDialog* pqpdlgProgress = nullptr;

      QStringList qstrlContent = qstrFileContent.split("\n", QString::SkipEmptyParts);
      int iLineCount = qstrlContent.count();

      if (p_pCwmsImport->GetDisplayProgress())
      {
         pqpdlgProgress = new QProgressDialog(qApp->tr("Importiere Daten..."), qApp->tr("Abbrechen"), 0, iLineCount, nullptr);
         pqpdlgProgress->setWindowModality(Qt::WindowModal);
         pqpdlgProgress->show();
         qApp->processEvents();
      }

      int iCounter = 0;
      CwmsImportSettings cSettings = p_pCwmsImport->GetSettings();
      
      if (cSettings.GetIgnoreFirstLine())
      {
         ++iCounter;
      }

      if (cSettings.GetIgnoreLastLine())
      {
         --iLineCount;
      }


      for (; iCounter < iLineCount; ++iCounter)
      {
#ifdef WOGRA_DEBUG
         double dTimeComp = 0.0;
         double dTimeStartComp = clock(); 
#endif //

         qstrLine = qstrlContent[iCounter];

         if (!qstrLine.isEmpty())
         {
            QStringList qstrlResult = ParseLine(qstrLine);
            if (!p_pCwmsImport->CreateData(qstrlResult))
            {
                QString qstrMessage = qApp->tr("Die Zeile ") + QString::number(iCounter) + " enthielt Fehler und konnte nicht importiert werden.\n"
                                                    "Der Import wird mit der nächsten Zeile fortgesetzt.";
               MSG_CRIT("Importzeile fehlerhaft", qstrMessage.toUtf8());
            }
            
            if (iCounter % 10 == 0 && p_pCwmsImport->GetDisplayProgress())
            {
               pqpdlgProgress->setValue(iCounter);
               qApp->processEvents();  
            }
         }

#ifdef WOGRA_DEBUG
         dTimeComp = clock() - dTimeStartComp;
         dTimeComp = dTimeComp / CLOCKS_PER_SEC;

         INFO("Dauer eine ObjectErzeugung: " + QString::number(dTimeComp));
#endif //
      } 

#ifdef WOGRA_DEBUG
      double dTime = 0.0;
      double dTimeStart = clock(); 
#endif //

      p_pCwmsImport->Commit();
      DELPTR(pqpdlgProgress);
      CloseDevice();

#ifdef WOGRA_DEBUG
      dTime = clock() - dTimeStart;
      dTime = dTime / CLOCKS_PER_SEC;

      INFO("Dauer Commit: " + QString::number(dTime));

      dTimeSum = clock() - dTimeStartSum;
      dTimeSum = dTimeSum / CLOCKS_PER_SEC;

      INFO("Dauer Commit: " + QString::number(dTimeSum));
#endif //

      if (pMessenger)
      {
         pMessenger->EndAndShowAsyncMessageCollection();
      }
   }
}

/** +-=---------------------------------------------------------Di 21. Okt 18:51:24 2008----------*
 * @method  CwmsImportParser::ParserFactory                  // public, static                    *
 * @return  CwmsImportParser*                                //                                   *
 * @param   CwmsImportSettings* p_pImportSettings            //                                   *
 * @comment This method creates the correct importparser dependent from ImportSettings.           *
 *----------------last changed: --------------------------------Di 21. Okt 18:51:24 2008----------*/
CwmsImportParser* CwmsImportParser::ParserFactory(CwmsImportSettings* p_pImportSettings)
{
   CwmsImportParser* pParser = nullptr;

   if (p_pImportSettings)
   {
      switch(p_pImportSettings->GetImportType())
      {
      case eWmsImportTypeText:
         pParser = new CwmsImportParserText();
         break;
      case eWmsImportTypeCsv:
      default:
         pParser = new CwmsImportParserCsv();

      }

      pParser->SetImportSettings(p_pImportSettings);
   }

   return pParser;
}
