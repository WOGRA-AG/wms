/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <QDir>
#include <QCoreApplication>
#include <QSettings>

// WMS Commons Includes
#include "CwmsSettingsStoreFactory.h"
#include "wmsdefines.h"

// own Includes
#include "CdmSettings.h"


/** +-=---------------------------------------------------------Fri Dec 16 11:32:34 2005----------*
 * @method  CdmSettings::CdmSettings                         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrApplicationName                    //                                   *
 * @param   EdmSettingsMode p_eDmSettingsMode                //                                   *
 * @comment The constructor of the settings. dependent from the choosen settingsmode it will      *
 *          be loaded the correct settings from registry.                                         *
 *---------------------------------------------------------------Fri Dec 16 11:32:34 2005---------*/
CdmSettings::CdmSettings(EdmSettingsMode p_eDmSettingsMode)
: m_pSettings(nullptr),
  m_eDmSettingsMode(p_eDmSettingsMode)
{
    if (p_eDmSettingsMode == eDmSettingsModeClient)
    {
        m_pSettings = CwmsSettingsStoreFactory::GenerateClientSettings();
    }
    else
    {
        m_pSettings = CwmsSettingsStoreFactory::GenerateServerSettings();
    }
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:48:47 2005----------*
 * @method  CdmSettings::~CdmSettings                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmSettings                                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:48:47 2005----------*/
CdmSettings::~CdmSettings(  )
{
    delete m_pSettings;
}

/** +-=---------------------------------------------------------So 10. Feb 10:21:02 2013----------*
 * @method  CdmSettings::IsWriteable                         // public, const                     *
 * @return  bool                                             //                                   *
 * @comment returns if the user has writeaccess to registry.                                      *
 *----------------last changed: --------------------------------So 10. Feb 10:21:02 2013----------*/
bool CdmSettings::IsWriteable() const
{
   return m_pSettings->isWritable();
}

/** +-=---------------------------------------------------------So 10. Feb 10:21:55 2013----------*
 * @method  CdmSettings::GetSettingsMode                     // public, const                     *
 * @return  EdmSettingsMode                                  //                                   *
 * @comment returns the settingsmode of the settings.                                             *
 *----------------last changed: --------------------------------So 10. Feb 10:21:55 2013----------*/
EdmSettingsMode CdmSettings::GetSettingsMode() const
{
   return m_eDmSettingsMode;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:00:09 2005----------*
 * @method  CdmSettings::SetValue                            // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:00:09 2005----------*/
void CdmSettings::SetValue(QString p_qstrKeyname, QString p_qstrValue)
{
   m_pSettings->setValue(p_qstrKeyname, p_qstrValue);
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:00:13 2005----------*
 * @method  CdmSettings::SetValue                            // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool p_bValue                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:00:13 2005----------*/
void CdmSettings::SetValue(QString p_qstrKeyname, bool p_bValue)
{
   m_pSettings->setValue(p_qstrKeyname, p_bValue);
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:00:17 2005----------*
 * @method  CdmSettings::SetValue                            // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:00:17 2005----------*/
void CdmSettings::SetValue(QString p_qstrKeyname, int p_iValue)
{
   m_pSettings->setValue(p_qstrKeyname, p_iValue);
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:00:21 2005----------*
 * @method  CdmSettings::SetValue                            // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:00:21 2005----------*/
void CdmSettings::SetValue(QString p_qstrKeyname, double p_dValue)
{
   m_pSettings->setValue(p_qstrKeyname, p_dValue);
}

/** +-=---------------------------------------------------------So 10. Feb 10:22:07 2013----------*
 * @method  CdmSettings::GetValue                            // private, const                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   QString& p_qstrValue                             //                                   *
 * @comment returns the settings string value.                                                    *
 *----------------last changed: --------------------------------So 10. Feb 10:22:07 2013----------*/
void CdmSettings::GetValue(QString p_qstrKey, QString& p_qstrValue) const
{
   p_qstrValue = m_pSettings->value(p_qstrKey).toString();
}

/** +-=---------------------------------------------------------So 10. Feb 10:22:15 2013----------*
 * @method  CdmSettings::GetValue                            // private, const                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   bool& p_bValue                                   //                                   *
 * @comment returns the settings string value.                                                    *
 *----------------last changed: --------------------------------So 10. Feb 10:22:15 2013----------*/
void CdmSettings::GetValue(QString p_qstrKey, bool& p_bValue) const
{
   p_bValue = m_pSettings->value(p_qstrKey).toBool();
}

/** +-=---------------------------------------------------------So 10. Feb 10:22:22 2013----------*
 * @method  CdmSettings::GetValue                            // private, const                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   int& p_iValue                                    //                                   *
 * @comment returns the settings string value.                                                    *
 *----------------last changed: --------------------------------So 10. Feb 10:22:22 2013----------*/
void CdmSettings::GetValue(QString p_qstrKey, int& p_iValue) const
{
   p_iValue = m_pSettings->value(p_qstrKey, -1).toInt();
}

/** +-=---------------------------------------------------------So 10. Feb 10:22:45 2013----------*
 * @method  CdmSettings::GetValue                            // private, const                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   double& p_dValue                                 //                                   *
 * @comment returns the settings string value.                                                    *
 *----------------last changed: --------------------------------So 10. Feb 10:22:45 2013----------*/
void CdmSettings::GetValue(QString p_qstrKey, double& p_dValue) const
{
   p_dValue = m_pSettings->value(p_qstrKey).toDouble();
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:00:45 2005----------*
 * @method  CdmSettings::SetTemporaryBinaryDirectory         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDirectory                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:00:45 2005----------*/
void CdmSettings::SetTemporaryBinaryDirectory(QString p_qstrDirectory)
{
   SetValue(BINARY_DIRECTORY, p_qstrDirectory);
}

/** +-=---------------------------------------------------------So 10. Feb 10:22:57 2013----------*
 * @method  CdmSettings::GetTemporaryBinaryDirectory         // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:22:57 2013----------*/
QString CdmSettings::GetTemporaryBinaryDirectory() const
{
   QString qstrRet;
   
   GetValue(BINARY_DIRECTORY, qstrRet);

   if (qstrRet.isEmpty())
   {
      qstrRet = QDir::tempPath();
      (const_cast<CdmSettings*>(this))->SetTemporaryBinaryDirectory(qstrRet);
   }

   return qstrRet;
}

void CdmSettings::SetPassword(QString p_qstrPassword)
{
   SetValue(PASSWORD, p_qstrPassword);
}

QString CdmSettings::GetPassword() const
{
   QString qstrValue;
   GetValue(PASSWORD, qstrValue);

   return qstrValue;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:02:33 2005----------*
 * @method  CdmSettings::SetStoreWmsLogin                    // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bLogin                                    //                                   *
 * @comment This method sets if the wms login should be stored or not.                            *
 *----------------last changed: --------------------------------Sa 20. Aug 11:02:33 2005----------*/
void CdmSettings::SetStoreWmsLogin(bool p_bLogin)
{
   SetValue(STORE_WMS_LOGIN, p_bLogin);
}

/** +-=---------------------------------------------------------So 10. Feb 10:27:23 2013----------*
 * @method  CdmSettings::GetStoreWmsLogin                    // public, const                     *
 * @return  bool                                             //                                   *
 * @comment This method returns if the WMS Login should be stored or not.                         *
 *----------------last changed: --------------------------------So 10. Feb 10:27:23 2013----------*/
bool CdmSettings::GetStoreWmsLogin() const
{
   bool bRet = false;
   GetValue(STORE_WMS_LOGIN, bRet);
   return bRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:02:39 2005----------*
 * @method  CdmSettings::SetWmsLogin                         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrWmsLogin                           //                                   *
 * @comment This method sets the Wms Login.                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:02:39 2005----------*/
void CdmSettings::SetWmsLogin(QString p_qstrWmsLogin)
{
   SetValue(WMS_LOGIN, p_qstrWmsLogin);
}

/** +-=---------------------------------------------------------So 10. Feb 10:27:49 2013----------*
 * @method  CdmSettings::GetWmsLogin                         // public, const                     *
 * @return  QString                                          //                                   *
 * @comment This method returns the stored Wms Login                                              *
 *----------------last changed: --------------------------------So 10. Feb 10:27:49 2013----------*/
QString CdmSettings::GetWmsLogin() const
{
   QString qstrRet;
   GetValue(WMS_LOGIN, qstrRet);
   return qstrRet;
}

void CdmSettings::setIsLdapActive(bool b_ldap_active)
{
    SetValue(LDAP_ACTIVE, b_ldap_active);
}

bool CdmSettings::getIsLdapActive() const
{
    bool rc = false;
    GetValue(LDAP_ACTIVE, rc);
    return rc;
}

void CdmSettings::setIsLdapConfigured(bool b_ldap_config)
{
    SetValue(LDAP_CONFIG,b_ldap_config);
}

int CdmSettings::getDaemonServerPort()
{
    int rc = 0;
    GetValue(DAEMON_SERVER_PORT, rc);
    return rc;
}

bool CdmSettings::getIsLdapConfigured() const
{
    bool rc = false;
    GetValue(LDAP_CONFIG,rc);
    return rc;
}

void CdmSettings::setLdapHost(QString str_host){
    SetValue(LDAP_HOST, str_host);
}

QString CdmSettings::getLdapHost() const{
    QString rc = "";
    GetValue(LDAP_HOST, rc);
    return rc;
}

void CdmSettings::setRegistrationAllowed(QString str_host){
    SetValue(REGISTRATION_ALLOWED, str_host);
}

QString CdmSettings::getRegistratonAllowed() const{
    QString rc = "";
    GetValue(REGISTRATION_ALLOWED, rc);
    return rc;
}

void CdmSettings::setCompanyRegistrationAllowed(QString str_host){
    SetValue(COMPANY_REGISTRATION_ALLOWED, str_host);
}

QString CdmSettings::getCompanyRegistratonAllowed() const{
    QString rc = "";
    GetValue(COMPANY_REGISTRATION_ALLOWED, rc);
    return rc;
}

void CdmSettings::setLdapPort(QString str_port){
    SetValue(LDAP_PORT, str_port);
}

QString CdmSettings::getLdapPort() const{
    QString rc = "";
    GetValue(LDAP_PORT, rc);
    return rc;
}

void CdmSettings::setLdapBaseDN(QString str_basedn){
    SetValue(LDAP_BASE_DN, str_basedn);
}

QString CdmSettings::getLdapBaseDN() const{
    QString rc = "";
    GetValue(LDAP_BASE_DN, rc);
    return rc;
}

void CdmSettings::setLdapAdmin(QString str_admin){
    SetValue(LDAP_ADMIN, str_admin);
}

QString CdmSettings::getLdapAdmin() const{
    QString rc = "";
    GetValue(LDAP_ADMIN, rc);
    return rc;
}

void CdmSettings::setLdapPasswd(QString str_passwd){
    SetValue(LDAP_PASSWORD, str_passwd);
}

QString CdmSettings::getLdapPasswd() const{
    QString rc = "";
    GetValue(LDAP_PASSWORD, rc);
    return rc;
}

void CdmSettings::setLdapAdminGroup(QString str_admin_group){
    SetValue(LDAP_ADMIN_GROUP, str_admin_group);
}

QString CdmSettings::getLdapAdminGroup() const{
    QString rc = "";
    GetValue(LDAP_ADMIN_GROUP, rc);
    return rc;
}

void CdmSettings::setLdapUserGroup(QString str_user_group){
    SetValue(LDAP_USER_GROUP, str_user_group);
}

QString CdmSettings::getLdapUserGroup() const{
    QString rc = "";
    GetValue(LDAP_USER_GROUP, rc);
    return rc;
}

QString CdmSettings::GetHost()
{
    QString rc = "";
    GetValue(WMS_URL_SERVER_HOST, rc);
    return rc;
}

void CdmSettings::SetHost(QString p_qstrHost)
{
     SetValue(WMS_URL_SERVER_HOST, p_qstrHost);
}

int CdmSettings::GetPort()
{
    int rc = 0;
    GetValue(WMS_URL_SERVER_PORT, rc);
    return rc;
}

void CdmSettings::SetPort(int p_iPort)
{
    SetValue(WMS_URL_SERVER_PORT, p_iPort);
}

QString CdmSettings::GetPath()
{
    QString rc = "";
    GetValue(WMS_URL_SERVER_PATH, rc);
    return rc;
}

void CdmSettings::SetPath(QString p_qstrPath)
{
    SetValue(WMS_URL_SERVER_PATH, p_qstrPath);
}

void CdmSettings::SetSchemeBasedUserManagement(bool p_bActive)
{
    SetValue(SCHEME_BASED_USERMANAGEMENT, p_bActive);
}

bool CdmSettings::IsSchemeBasedUserManagementAcive() const
{
    bool bRet;
    GetValue(SCHEME_BASED_USERMANAGEMENT, bRet);
    return bRet;
}

QVariantMap CdmSettings::getValueMap()
{
    QVariantMap qvMap = CwmsSettingsStoreFactory::RetrieveValuesFromSettings(*m_pSettings);
    getMapInitValues(qvMap);
    return qvMap;
}

void CdmSettings::getMapInitValues(QVariantMap& p_rqMap)
{
    addMissingValue(p_rqMap, LDAP_USER_GROUP, QVariant());
    addMissingValue(p_rqMap, LDAP_ADMIN_GROUP, QVariant(0));
    addMissingValue(p_rqMap, LDAP_PASSWORD, QVariant(false));
    addMissingValue(p_rqMap, LDAP_ADMIN, QVariant(false));
    addMissingValue(p_rqMap, LDAP_BASE_DN, QVariant());
    addMissingValue(p_rqMap, LDAP_PORT, QVariant());
    addMissingValue(p_rqMap, LDAP_HOST, QVariant(true));
    addMissingValue(p_rqMap, LDAP_CONFIG, QVariant());
    addMissingValue(p_rqMap, LDAP_ACTIVE, QVariant());
    addMissingValue(p_rqMap, WMS_LOGIN, QVariant());
    addMissingValue(p_rqMap, STORE_WMS_LOGIN, QVariant());
    addMissingValue(p_rqMap, BINARY_DIRECTORY, QVariant());
    addMissingValue(p_rqMap, COMPANY_REGISTRATION_ALLOWED, QVariant(false));
    addMissingValue(p_rqMap, REGISTRATION_ALLOWED, QVariant(false));
    addMissingValue(p_rqMap, WMS_URL_SERVER_HOST, QVariant("localhost"));
    addMissingValue(p_rqMap, WMS_URL_SERVER_PORT, QVariant(8383));
    addMissingValue(p_rqMap, WMS_URL_SERVER_PATH, QVariant(""));
    addMissingValue(p_rqMap, SCHEME_BASED_USERMANAGEMENT, QVariant(false));
}

void CdmSettings::addMissingValue(QVariantMap& p_rqMap, QString p_qstrKey, QVariant p_qValue)
{
    if (!p_rqMap.contains(p_qstrKey))
    {
        p_rqMap[p_qstrKey] = p_qValue;
    }
}

void CdmSettings::setValueMap(QVariantMap& p_rqMap)
{
    CwmsSettingsStoreFactory::SetValuesFromMapToSettings(p_rqMap, *m_pSettings);
    Synchronize();
}

void CdmSettings::Synchronize()
{
    m_pSettings->sync();
}
