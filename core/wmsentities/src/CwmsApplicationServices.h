#ifndef CWMSAPPLICATIONSERVICES_H
#define CWMSAPPLICATIONSERVICES_H

// System and Qt Includes

// WMS Include


// Own Includes
#include "basetools.h"

// Forwards
class CdmScheme;
class CdmExecutorAddOnManager;

// MACROS
#define WDFFILESPATH "/wdf"
#define FUNCTIONPLUGINPATH "/functions"
#define PRINTINGPLUGINPATH "/printing"
#define UIPLUGINPATH "/ui"
#define SERVERPLUGIN "/server"


class BASETOOLS_API CwmsApplicationServices
{
public:

    static void InstallFunctionsAndPlugins();
    static void InstallTranslationFiles();
    static void InitCurrentScheme();
    static void InstallDeploymentFilesFromDirectory();
};

#endif // CWMSAPPLICATIONSERVICES_H
