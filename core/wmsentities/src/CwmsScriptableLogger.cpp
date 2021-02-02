/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptableMailer.h
 ** Started Implementation: 2012/11/09
 ** Description:
 ** 
 ** implements the script interface for js methods using logging
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 


// System and QT Includes
#include <qscriptcontext.h>
#include <QStringList>

// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "CwmsScriptableLogger.h"


/** +-=---------------------------------------------------------Mi 9. Okt 14:39:10 2013-----------*
 * @method  CwmsScriptableLogger::CwmsScriptableLogger       // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Okt 14:39:10 2013-----------*/
CwmsScriptableLogger::CwmsScriptableLogger()
{
}

/** +-=---------------------------------------------------------Mi 9. Okt 14:40:18 2013-----------*
 * @method  CwmsScriptableLogger::~CwmsScriptableLogger      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsScriptableLogger                                          *
 *----------------last changed: --------------------------------Mi 9. Okt 14:40:18 2013-----------*/
CwmsScriptableLogger::~CwmsScriptableLogger()
{
}

/** +-=---------------------------------------------------------Mi 9. Okt 14:44:45 2013-----------*
 * @method  CwmsScriptableLogger::Info                       // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Okt 14:44:45 2013-----------*/
void CwmsScriptableLogger::info(QString p_qstrMessage)
{
   CdmLogging::AddInfoLog("Javascript Output", p_qstrMessage, 0);
}

/** +-=---------------------------------------------------------Mi 9. Okt 14:44:31 2013-----------*
 * @method  CwmsScriptableLogger::Warning                    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Okt 14:44:31 2013-----------*/
void CwmsScriptableLogger::warning(QString p_qstrMessage)
{
   CdmLogging::AddWarningLog("Javascript Output", p_qstrMessage, 0);
}

/** +-=---------------------------------------------------------Mi 9. Okt 14:44:22 2013-----------*
 * @method  CwmsScriptableLogger::Error                      // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Okt 14:44:22 2013-----------*/
void CwmsScriptableLogger::error(QString p_qstrMessage)
{
   CdmLogging::AddErrorLog("Javascript Output", p_qstrMessage, 0);
}

/** +-=---------------------------------------------------------Mi 9. Okt 14:45:28 2013-----------*
 * @method  CwmsScriptableLogger::Fatal                      // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Okt 14:45:28 2013-----------*/
void CwmsScriptableLogger::fatal(QString p_qstrMessage)
{
   CdmLogging::AddFatalLog("Javascript Output", p_qstrMessage, 0);
}
