#ifndef CWMSAPPLICATION_H
#define CWMSAPPLICATION_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <QPixmap>

// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "basetools.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsApplication: public CdmObjectAdaptor
{

public:
    CwmsApplication();
    explicit CwmsApplication(CdmObject* p_pCdmObject);
    CdmObjectContainer* GetModules();
    CdmObjectContainer* GetTranslations();
    CdmObjectContainer* GetUserLanguages();
    CdmObjectContainer* GetPlugins();
    virtual ~CwmsApplication();
    QString GetName();
    void SetName(QString p_qstrValue);
    QString GetDescription();
    void SetDescription(QString p_qstrValue);
    bool GetActive();
    void SetActive(bool p_bValue);
    int GetVersionMajor();
    void SetVersionMajor(int p_iValue);
    int GetVersionMinor();
    void SetVersionMinor(int p_iValue);
    int GetVersionBugfix();
    void SetVersionBugfix(int p_iValue);
    QString GetHelp();
    void SetHelp(QString p_qstrValue);
    QString GetLicence();
    void SetLicence(QString p_qstrValue);
    QString GetManufacturer();
    void SetManufacturer(QString p_qstrValue);
    QString GetHotline();
    void SetHotline(QString p_qstrValue);
    QString GetEmail();
    void SetEmail(QString p_qstrValue);
    QString GetWebaddress();
    void SetWebaddress(QString p_qstrValue);
    bool GetDesktop();
    void SetDesktop(bool p_bValue);
    bool GetMobile();
    void SetMobile(bool p_bValue);
    qint64 GetModulesId();
    bool GetLicenceCheck();
    void SetLicenceCheck(bool p_bValue);
    bool GetWeb();
    void SetWeb(bool p_bValue);
    QString GetModulesContainerName();
    QString GetMain();
    void SetMain(QString p_qstrValue);
    CdmObject *LoadModule(qint64 p_lObjectId);
    CdmObject *LoadDefaultModule();
    static CwmsApplication Create();
    bool HasApplicationRight();
    void SetMainWindow(CdmObject* p_pObject);
    CdmObject* GetMainWindow();
    QStringList GetModuleList();
    QPixmap GetIcon();
    void SetIcon(QString p_qstrFilename);
    QString GetVersion();
    QString GetCurrentUserLanguage();
    void SetCurrentUserLanguage(QString p_iLanguage);
    static bool Delete(CwmsApplication cCwmsApplication);
    static QStringList GetApplicationList(bool p_bDesktop = true, bool p_bWeb = true, bool p_bMobile = true);
    static CdmObject* GetApplication(QString p_qstrApplication);

private:
    CdmQuery* CreateQuery();

};
#endif //
