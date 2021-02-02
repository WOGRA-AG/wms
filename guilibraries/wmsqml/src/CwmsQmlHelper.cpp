
// System and Qt Includes
#include <QtQml>

// WMS Includes
#include "CdmQueryModel.h"


// WMS Basetools Includes
#include "CwmsApplication.h"
#include "CwmsApplicationModule.h"

// own Includes
#include "CsaQmlRegistry.h"
#include "CwmsQmlWidget.h"
#include "CwqDocumentHandler.h"
#include "CwqObjectEditorController.h"
#include "CwmsQmlContainerEditor.h"
#include "CwmsQmlLogin.h"
#include "CwmsQmlHelper.h"
#include "CwmsqmlApplication.h"
#include "CwmsqmlApplicationModule.h"




void CwmsQmlHelper::registerTypes()
{
    CsaQmlRegistry::registerTypes();
    CwmsQmlContainerEditor::registerToQml();
    CwqObjectEditorController::registerToQml();
    CwmsQmlWidget::registerToQml();
    CwqDocumentHandler::registerToQml();
    CwmsQmlLogin::registerToQml();
    CwmsqmlApplication::registerToQml();
    CwmsQmlApplicationModule::registerToQml();
}
