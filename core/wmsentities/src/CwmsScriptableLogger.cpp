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


CwmsScriptableLogger::CwmsScriptableLogger()
{
}


CwmsScriptableLogger::~CwmsScriptableLogger()
{
}


void CwmsScriptableLogger::info(QString p_qstrMessage)
{
   CdmLogging::AddInfoLog("Javascript Output", p_qstrMessage, 0);
}


void CwmsScriptableLogger::warning(QString p_qstrMessage)
{
   CdmLogging::AddWarningLog("Javascript Output", p_qstrMessage, 0);
}


void CwmsScriptableLogger::error(QString p_qstrMessage)
{
   CdmLogging::AddErrorLog("Javascript Output", p_qstrMessage, 0);
}


void CwmsScriptableLogger::fatal(QString p_qstrMessage)
{
   CdmLogging::AddFatalLog("Javascript Output", p_qstrMessage, 0);
}
