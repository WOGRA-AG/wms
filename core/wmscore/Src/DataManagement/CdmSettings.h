/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMSETTINGS_H
#define CDMSETTINGS_H

// System and QT Includes
#include <QString>
#include <QVariant>

// own Includes
#include "datamanager.h"

enum EdmSettingsMode
{
   eDmSettingsModeNone,
   eDmSettingsModeServer,
   eDmSettingsModeClient
};


// forwards
class QSettings;


/*
 * This class iplements the loading and saving
 * of settings in home directory(unix) or registry
 * (windows).
 */
class WMSMANAGER_API CdmSettings
{

   private:
      /*
       * Access to registry or home directory
       */
      QSettings* m_pSettings;
      
      /*
       * The Mode of the settings
       */
      EdmSettingsMode m_eDmSettingsMode;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:48:47 2005*
    * @method  CdmSettings::~CdmSettings                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmSettings                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 12:48:47 2005----------*/
virtual ~CdmSettings();

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:00:09 2005*
    * @method  CdmSettings::SetValue                         // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:00:09 2005----------*/
void SetValue(QString p_qstrKeyname, QString p_qstrValue);

   private:
   /** +-=---------------------------------------------------------So 10. Feb 10:22:07 2013-------*
    * @method  CdmSettings::GetValue                         // private, const                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   QString& p_qstrValue                          //                                   *
    * @comment returns the settings string value.                                                 *
    *----------------last changed: -----------------------------So 10. Feb 10:22:07 2013----------*/
    void GetValue(QString p_qstrKey, QString& p_qstrValue) const;

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:00:21 2005*
    * @method  CdmSettings::SetValue                         // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:00:21 2005----------*/
void SetValue(QString p_qstrKeyname, double p_dValue);

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:00:17 2005*
    * @method  CdmSettings::SetValue                         // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:00:17 2005----------*/
void SetValue(QString p_qstrKeyname, int p_iValue);

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:00:13 2005*
    * @method  CdmSettings::SetValue                         // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool p_bValue                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:00:13 2005----------*/
void SetValue(QString p_qstrKeyname, bool p_bValue);

   private:
   /** +-=---------------------------------------------------------So 10. Feb 10:22:45 2013-------*
    * @method  CdmSettings::GetValue                         // private, const                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   double& p_dValue                              //                                   *
    * @comment returns the settings string value.                                                 *
    *----------------last changed: -----------------------------So 10. Feb 10:22:45 2013----------*/
    void GetValue(QString p_qstrKey, double& p_dValue) const;

   private:
   /** +-=---------------------------------------------------------So 10. Feb 10:22:22 2013-------*
    * @method  CdmSettings::GetValue                         // private, const                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   int& p_iValue                                 //                                   *
    * @comment returns the settings string value.                                                 *
    *----------------last changed: -----------------------------So 10. Feb 10:22:22 2013----------*/
    void GetValue(QString p_qstrKey, int& p_iValue) const;

   private:
   /** +-=---------------------------------------------------------So 10. Feb 10:22:15 2013-------*
    * @method  CdmSettings::GetValue                         // private, const                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   bool& p_bValue                                //                                   *
    * @comment returns the settings string value.                                                 *
    *----------------last changed: -----------------------------So 10. Feb 10:22:15 2013----------*/
    void GetValue(QString p_qstrKey, bool& p_bValue) const;

    void addMissingValue(QVariantMap &p_rqMap, QString p_qstrKey, QVariant p_qValue);
public:
   /** +-=---------------------------------------------------------So 10. Feb 10:22:57 2013-------*
    * @method  CdmSettings::GetTemporaryBinaryDirectory      // public, const                     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:22:57 2013----------*/
    QString GetTemporaryBinaryDirectory() const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:00:45 2005*
    * @method  CdmSettings::SetTemporaryBinaryDirectory      // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDirectory                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:00:45 2005----------*/
void SetTemporaryBinaryDirectory(  QString p_qstrDirectory );


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:02:33 2005*
    * @method  CdmSettings::SetStoreWmsLogin                 // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bLogin                                 //                                   *
    * @comment This method sets if the wms login should be stored or not.                         *
    *----------------last changed: -----------------------------Sa 20. Aug 11:02:33 2005----------*/
    void SetStoreWmsLogin(bool p_bLogin);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:27:23 2013-------*
    * @method  CdmSettings::GetStoreWmsLogin                 // public, const                     *
    * @return  bool                                          //                                   *
    * @comment This method returns if the WMS Login should be stored or not.                      *
    *----------------last changed: -----------------------------So 10. Feb 10:27:23 2013----------*/
    bool GetStoreWmsLogin() const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:02:39 2005*
    * @method  CdmSettings::SetWmsLogin                      // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrWmsLogin                        //                                   *
    * @comment This method sets the Wms Login.                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:02:39 2005----------*/
void SetWmsLogin(QString p_qstrWmsLogin);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:27:49 2013-------*
    * @method  CdmSettings::GetWmsLogin                      // public, const                     *
    * @return  QString                                       //                                   *
    * @comment This method returns the stored Wms Login                                           *
    *----------------last changed: -----------------------------So 10. Feb 10:27:49 2013----------*/
    QString GetWmsLogin() const;

   public:
      CdmSettings(EdmSettingsMode p_eDmSettingsMode);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:21:55 2013-------*
    * @method  CdmSettings::GetSettingsMode                  // public, const                     *
    * @return  EdmSettingsMode                               //                                   *
    * @comment returns the settingsmode of the settings.                                          *
    *----------------last changed: -----------------------------So 10. Feb 10:21:55 2013----------*/
    EdmSettingsMode GetSettingsMode() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:21:02 2013-------*
    * @method  CdmSettings::IsWriteable                      // public, const                     *
    * @return  bool                                          //                                   *
    * @comment returns if the user has writeaccess to registry.                                   *
    *----------------last changed: -----------------------------So 10. Feb 10:21:02 2013----------*/
    bool IsWriteable() const;

    void setIsLdapActive(bool b_ldap_active);
    bool getIsLdapActive() const;
    void setIsLdapConfigured(bool b_ldap_config);
    bool getIsLdapConfigured() const;
    void setLdapHost(QString str_host);
    QString getLdapHost() const;
    void setLdapPort(QString str_port);
    QString getLdapPort() const;
    void setLdapBaseDN(QString str_basedn);
    QString getLdapBaseDN() const;
    void setLdapAdmin(QString str_admin);
    QString getLdapAdmin() const;
    void setLdapPasswd(QString str_passwd);
    QString getLdapPasswd() const;
    void setLdapAdminGroup(QString str_admin_group);
    QString getLdapAdminGroup() const;
    void setLdapUserGroup(QString str_user_group);
    QString getLdapUserGroup() const;
    QVariantMap getValueMap();
    void setValueMap(QVariantMap &p_rqMap);
    void getMapInitValues(QVariantMap& qMap);
    void Synchronize();
    void SetPassword(QString p_qstrPassword);
    QString GetPassword() const;
    QString getCompanyRegistratonAllowed() const;
    void setCompanyRegistrationAllowed(QString str_host);
    void setRegistrationAllowed(QString str_host);
    QString getRegistratonAllowed() const;
    void SetPort(int p_iPort);
    int GetPort();
    void SetHost(QString p_qstrHost);
    QString GetHost();
    QString GetPath();
    void SetPath(QString p_qstrPath);
    bool IsSchemeBasedUserManagementAcive() const;
    void SetSchemeBasedUserManagement(bool p_bActive);
    int getDaemonServerPort();
};

#endif //
