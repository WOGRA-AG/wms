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

CwmsImportParser::CwmsImportParser()
: m_pCwmsImportSettings(nullptr),
  m_pqDevice(nullptr)
{
}

CwmsImportParser::~CwmsImportParser()
{
}

void CwmsImportParser::SetImportSettings(CwmsImportSettings* p_pImportSettings)
{
   m_pCwmsImportSettings = p_pImportSettings;
}

void CwmsImportParser::SetDevice(QIODevice* p_pDevice)
{
   m_pqDevice = p_pDevice;
}

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

void CwmsImportParser::CloseDevice()
{
   if (CHKPTR(m_pqDevice))
   {
      m_pqDevice->close();
      DELPTR(m_pqDevice);
   }
}

void CwmsImportParser::ParseFile(CwmsImport* p_pCwmsImport)
{
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
      } 

      p_pCwmsImport->Commit();
      DELPTR(pqpdlgProgress);
      CloseDevice();

      if (pMessenger)
      {
         pMessenger->EndAndShowAsyncMessageCollection();
      }
   }
}

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
