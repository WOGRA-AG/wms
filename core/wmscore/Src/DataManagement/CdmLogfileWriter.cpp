/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qstring.h>
#include <QThread>
#include <qfile.h>
#include <qdatetime.h>
#include <QDir>

// own Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogfileWriter.h"


/** +-=---------------------------------------------------------Fr 19. Aug 23:28:46 2005----------*
 * @method  CdmErrorLogfileWriter::CdmErrorLogfileWriter                               // private                           *
 * @return                                                   //                                   *
 * @param   QString p_qstrFilename                       //                                   *
 * @param   QString p_qstrApplicationName               //                                   *
 * @param   QString p_qstrVersion                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 19. Aug 23:28:46 2005----------*/
CdmLogfileWriter::CdmLogfileWriter(QString p_qstrFilename, QString p_qstrApplicationName, QString p_qstrVersion)
{
    m_qstrOutputFormat = "%1;%2;%3;%4;%5;%6\n";

    if (p_qstrFilename.isEmpty())
    {
        p_qstrFilename = QDir::tempPath() + "/wms.log";
    }

   if (p_qstrApplicationName.isEmpty())
   {
      p_qstrApplicationName = "WMS Client Or Server";
   }

   if (p_qstrVersion.isEmpty())
   {
      p_qstrVersion = "Unknown Version";
   }

   m_LogFile.setFileName(p_qstrFilename);

   if (m_LogFile.open(QIODevice::WriteOnly | QIODevice::Append))
   {
      QTextStream qtsStream(&m_LogFile);
      QDateTime qdCurrent = QDateTime::currentDateTime();
      QString qstrStartText = p_qstrApplicationName + " Logging of Version " + p_qstrVersion +"\n";
      qstrStartText += "on " + qdCurrent.toString() + "\n";
      qtsStream << qstrStartText;
   }
}


/** +-=---------------------------------------------------------Fr 19. Aug 23:28:50 2005----------*
 * @method  CdmErrorLogfileWriter::~CdmErrorLogfileWriter                              // private                           *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmErrorLogfileWriter                                                      *
 *----------------last changed: --------------------------------Fr 19. Aug 23:28:50 2005----------*/
CdmLogfileWriter::~CdmLogfileWriter(  )
{
   QDateTime qdCurrent = QDateTime::currentDateTime();
   QString qstrEndText = "Logging ended \n";
   qstrEndText += "on " + qdCurrent.toString();
   if (m_LogFile.isOpen())
   {
      QTextStream qtsStream(&m_LogFile);
      qtsStream << qstrEndText;
      m_LogFile.close();
   }
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:29:24 2005----------*
 * @method  CdmErrorLogfileWriter::WriteEvent                  // private                            *
 * @return  void                                             //                                   *
 * @param   EdmErrorSeverity p_eDmErrorSeverity              //                                   *
 * @param   QString p_qstrErrorModule                        //                                   *
 * @param   QString p_qstrEventText                          //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment This method adds a error event in the queue.                                          *
 *----------------last changed: --------------------------------Fr 19. Aug 23:29:24 2005----------*/
void CdmLogfileWriter::WriteEvent(CdmLogEntry& p_eEntry)
{
   QString qstrMessage;
   qint64 lThreadPtr = reinterpret_cast<qint64> (QThread::currentThread());
   qstrMessage = QString(m_qstrOutputFormat)
           .arg(lThreadPtr)
           .arg(p_eEntry.GetTimestamp().toString())
           .arg(p_eEntry.GetSeverityAsString())
           .arg(p_eEntry.GetErrorModule())
           .arg(p_eEntry.GetLine())
           .arg(p_eEntry.GetEventText());

   WriteToLogFile(qstrMessage);
}

/** +-=---------------------------------------------------------So 15. Mai 13:11:15 2011----------*
 * @method  CdmErrorLogfileWriter::WriteToLogFile                         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Mai 13:11:15 2011----------*/
void CdmLogfileWriter::WriteToLogFile(QString p_qstrMessage)
{
   SYNCHRONIZED;
   if (m_LogFile.isOpen() ||
       m_LogFile.open(QIODevice::WriteOnly | QIODevice::Append))
   {
       QTextStream qtsStream(&m_LogFile);
       qtsStream << p_qstrMessage;
       qtsStream.flush();
   }
}

void CdmLogfileWriter::AddInfo(CdmLogEntry& p_eEntry)
{
    WriteEvent(p_eEntry);
}

void CdmLogfileWriter::AddWarning(CdmLogEntry& p_eEntry)
{
   WriteEvent(p_eEntry);
}

void CdmLogfileWriter::AddError(CdmLogEntry& p_eEntry)
{
   WriteEvent(p_eEntry);
}

void CdmLogfileWriter::AddFatal(CdmLogEntry& p_eEntry)
{
    WriteEvent(p_eEntry);
}

void CdmLogfileWriter::AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode)
{
    Q_UNUSED(p_qdtTimeStamp);
    Q_UNUSED(p_iCode);
}


QString CdmLogfileWriter::GetOutputFormat() const
{
    return m_qstrOutputFormat;
}

void CdmLogfileWriter::SetOutputFormat(const QString &qstrOutputFormat)
{
    m_qstrOutputFormat = qstrOutputFormat;
}
