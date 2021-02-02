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
      long GetModulesId();
      bool GetLicenceCheck();
      void SetLicenceCheck(bool p_bValue);
      bool GetWeb();
      void SetWeb(bool p_bValue);
      QString GetModulesContainerName();
      QString GetMain();
      void SetMain(QString p_qstrValue);

      CdmObject *LoadModule(long p_lObjectId);
      CdmObject *LoadDefaultModule();
public:
      static CwmsApplication Create();
   public:
      static bool Delete(CwmsApplication cCwmsApplication);

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:26:35 2012--------*
    * @method  CwmsApplication::GetCurrentUserLanguageId     // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:26:35 2012-----------*/
    QString GetCurrentUserLanguage();

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:27:39 2012--------*
    * @method  CwmsApplication::SetCurrentUserLanguage       // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iLanguage                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:27:39 2012-----------*/
    void SetCurrentUserLanguage(QString p_iLanguage);

   private:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:35:40 2012--------*
    * @method  CwmsApplication::CreateQuery                  // private                           *
    * @return  CdmQueryEnhanced*                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:35:40 2012-----------*/
    CdmQueryEnhanced* CreateQuery();

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:41:12 2012--------*
    * @method  CwmsApplication::HasApplicationRight          // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:41:12 2012-----------*/
    bool HasApplicationRight();

   public:
   /** +-=---------------------------------------------------------Di 26. Feb 10:29:13 2013-------*
    * @method  CwmsApplication::GetApplicationList           // public, static                    *
    * @return  QStringList                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 10:29:13 2013----------*/
    static QStringList GetApplicationList(bool p_bDesktop = true, bool p_bWeb = true, bool p_bMobile = true);

   public:
   /** +-=---------------------------------------------------------Di 26. Feb 10:37:29 2013-------*
    * @method  CwmsApplication::GetApplication               // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 26. Feb 10:37:29 2013----------*/
    static CdmObject* GetApplication(QString p_qstrApplication);

    public:
    void SetMainWindow(CdmObject* p_pObject);
    public:
    CdmObject* GetMainWindow();
    QStringList GetModuleList();
    QPixmap GetIcon();
    void SetIcon(QString p_qstrFilename);
    QString GetVersion();
};
#endif //
