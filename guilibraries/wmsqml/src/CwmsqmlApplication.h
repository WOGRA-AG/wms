#ifndef CWMSQMLAPPLICATION_H
#define CWMSQMLAPPLICATION_H

// System and Qt Includes

// Base tools Includes
#include "CwmsApplication.h"

// own includes
#include "wmsqml_global.h"

// forwards
class CsaObject;
class CsaObjectContainer;

class WMSQML_EXPORT CwmsqmlApplication : public QObject
{
    Q_OBJECT

private:
   CwmsApplication m_App;

public:
    CwmsqmlApplication();
    ~CwmsqmlApplication();
    static void registerToQml();
    void setApplication(CwmsApplication p_App);
public slots:
    CsaObject* getMainWindow();
    QStringList getModuleList();
    CsaObjectContainer* getModules();
    CsaObject* loadDefaultModule();
    CsaObject* loadModule(int p_iId);
    QString getCurrentUserLanguageId();
    void setCurrentUserLanguage(QString p_iLanguageId);
    CsaObjectContainer* getLanguages();
    CsaObjectContainer* getTranslations();
    QString getEmail();
    QString getHotline();
    QString getManufacturer();
    QString getLicence();
    QString getHelp();
    int getVersionBugfix();
    int getVersionMinor();
    int getVersionMajor();
    QString getDescription();
    QString getName();
    QString getModulesContainerName();
};

#endif // CWMSQMLAPPLICATION_H
