/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMERRORLOGFILEWRITER_H
#define CDMERRORLOGFILEWRITER_H

// Sytsem and QT Includes
#include <QString>
#include <QList>
#include <QTextStream>
#include <QFile>
#include <QMutex>


// own Includes
#include "CdmLogEntry.h"
#include "CdmLoggingAdaptor.h"
#include "datamanager.h"


// forwards
class QString;
class QTextStream;



// forwards




/**
 * This class is for error handling and locking of wms
 * all received events will be stored there and written to file.
 */
class WMSMANAGER_API CdmLogfileWriter : public CdmLoggingAdaptor
{
   private:
      /*
       * The log file pointer
       */
      QFile m_LogFile;

private:
      /*
       * The format of the ouputstring
       */
      QString m_qstrOutputFormat;
      QTextStream m_qtsStream;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:28:46 2005*
    * @method  CdmErrorLogfileWriter::CdmErrorLogfileWriter                            // public                           *
    * @return                                                //                                   *
    * @param   QString p_qstrFilename               //                                   *
    * @param   QString p_qstrApplicationName = ""            //                                   *
    * @param   QString p_qstrVersion = ""                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 19. Aug 23:28:46 2005----------*/
CdmLogfileWriter(QString p_qstrFilename,
                      QString p_qstrApplicationName,
                      QString p_qstrVersion);

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:28:50 2005*
    * @method  CdmErrorLogfileWriter::~CdmErrorLogfileWriter                           // public                           *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmErrorLogfileWriter                                                   *
    *----------------last changed: -----------------------------Fr 19. Aug 23:28:50 2005----------*/
~CdmLogfileWriter(  );

    public:
     virtual void AddError(CdmLogEntry& p_eEntry);
     virtual void AddInfo(CdmLogEntry& p_eEntry);
     virtual void AddWarning(CdmLogEntry& p_eEntry);
     virtual void AddFatal(CdmLogEntry& p_eEntry);
     virtual void AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode);



    QString GetOutputFormat() const;
    void SetOutputFormat(const QString &qstrOutputFormat);

private:
/** +-=---------------------------------------------------------So 15. Mai 13:11:15 2011-------*
    * @method  CdmErrorLogfileWriter::WriteToLogFile                      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Mai 13:11:15 2011----------*/
    void WriteToLogFile(QString p_qstrMessage);

    void WriteEvent(CdmLogEntry& p_eEntry);
};

#endif //
