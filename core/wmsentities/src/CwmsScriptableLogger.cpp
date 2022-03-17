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
