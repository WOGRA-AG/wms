
// System and Qt Includes
#include <QtQml>

// own Includes
#include "CwmsQmlApplicationController.h"
#include "CwmsqmlApplication.h"

CwmsqmlApplication::CwmsqmlApplication()
{
}

CwmsqmlApplication::~CwmsqmlApplication()
{
}

CsaObject *CwmsqmlApplication::getMainWindow()
{
     return CwmsQmlApplicationController::getController()->convertObject(m_App.GetMainWindow());
}

QStringList CwmsqmlApplication::getModuleList()
{
    return m_App.GetModuleList();
}

CsaObjectContainer *CwmsqmlApplication::getModules()
{
    return CwmsQmlApplicationController::getController()->convertContainer(m_App.GetModules());
}

CsaObject *CwmsqmlApplication::loadDefaultModule()
{
    return CwmsQmlApplicationController::getController()->convertObject(m_App.LoadDefaultModule());
}

CsaObject *CwmsqmlApplication::loadModule(int p_iId)
{
    return CwmsQmlApplicationController::getController()->convertObject(m_App.LoadModule(p_iId));
}

QString CwmsqmlApplication::getCurrentUserLanguageId()
{
    return m_App.GetCurrentUserLanguage();
}

void CwmsqmlApplication::setCurrentUserLanguage(QString p_iLanguageId)
{
    m_App.SetCurrentUserLanguage(p_iLanguageId);
}

CsaObjectContainer *CwmsqmlApplication::getLanguages()
{
    return CwmsQmlApplicationController::getController()->convertContainer(m_App.GetUserLanguages());
}

CsaObjectContainer *CwmsqmlApplication::getTranslations()
{
    return CwmsQmlApplicationController::getController()->convertContainer(m_App.GetTranslations());
}

QString CwmsqmlApplication::getEmail()
{
    return m_App.GetEmail();
}

QString CwmsqmlApplication::getHotline()
{
    return m_App.GetHotline();
}

QString CwmsqmlApplication::getManufacturer()
{
    return m_App.GetManufacturer();
}

QString CwmsqmlApplication::getLicence()
{
    return m_App.GetLicence();
}

QString CwmsqmlApplication::getHelp()
{
    return m_App.GetHelp();
}

int CwmsqmlApplication::getVersionBugfix()
{
    return m_App.GetVersionBugfix();
}

int CwmsqmlApplication::getVersionMinor()
{
    return m_App.GetVersionMinor();
}

int CwmsqmlApplication::getVersionMajor()
{
    return m_App.GetVersionMajor();
}

QString CwmsqmlApplication::getDescription()
{
    return m_App.GetDescription();
}

QString CwmsqmlApplication::getName()
{
    return m_App.GetName();
}

void CwmsqmlApplication::registerToQml()
{
    qmlRegisterType<CwmsqmlApplication>("com.wogra.wmsqml", 1, 0, "WmsApplication");
}

void CwmsqmlApplication::setApplication(CwmsApplication p_App)
{
    m_App = p_App;
}

QString CwmsqmlApplication::getModulesContainerName()
{
    return m_App.GetModulesContainerName();
}
